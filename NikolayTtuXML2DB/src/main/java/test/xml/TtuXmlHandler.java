package test.xml;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import org.apache.log4j.Logger;
import org.apache.xmlbeans.XmlException;

import rpct.db.DataAccessException;
import rpct.db.domain.configuration.IntArray;
import rpct.db.domain.configuration.LocalConfigKey;
import rpct.db.domain.configuration.StaticConfiguration;
import rpct.db.domain.configuration.TtuFinalConf;
import rpct.db.domain.configuration.TtuTrigConf;
import rpct.db.domain.equipment.Chip;
import rpct.testAndUtils.ConfUtil;
import rpct.util.xml.config.RpctSettingsXmlDocument;
import rpct.util.xml.config.RpctSettingsXmlDocument.RpctSettingsXml;
import rpct.xdaq.axis.Binary;

public class TtuXmlHandler {
    private static final Logger logger = Logger.getLogger(TtuXmlHandler.class);

	private boolean saveToDb;
	private String fileName;
	private String localConfigKey;
	
	private RpctSettingsXmlDocument settingsDoc;

	public static void main(String[] args) throws DataAccessException, FileNotFoundException, IOException, XmlException {
		final TtuXmlHandler handler = new TtuXmlHandler();

		handler.init();

		try {
			handler.processXml();
		} catch (Exception e) {
			e.printStackTrace();
			ConfUtil.rollbackDb();
		}
        finally {
            ConfUtil.DbHandler.context.closeSession();
        }

		System.out.println("Done.");
	}

	private void init() throws DataAccessException, IOException, XmlException, FileNotFoundException {
		fileName = ConfUtil.getProperty("xml");
		if (fileName == null) {
			logger.error("xml file is not defined! Use \"java -Dxml=path/to/file\"");
			System.exit(4);
		}

		File file = new File(fileName);
		
		settingsDoc = RpctSettingsXmlDocument.Factory.parse(file);

		saveToDb =  ConfUtil.getBooleanProperty("saveToDb");

		try {
			localConfigKey = ConfUtil.getProperty("localConfigKey").toUpperCase();
		}
		catch (NullPointerException e) {
			logger.error("localConfigKey not defined (use \"java -DlocalConfigKey=aKey\")");
			System.exit(4);
		}
		
		if (saveToDb) {
			System.out.println("The xml config will be saved to DB!");
			if (!ConfUtil.proceed("Proceed?")) {
				System.exit(2);
			}
		} else {
			System.out.println("WARNING: Config will NOT be saved to DB, simulation only!");
		}
		
		logger.info("localConfigKey = " + localConfigKey);
		logger.info("saveToDb = " + saveToDb);

		//if (saveToDb) {
		ConfUtil.DbHandler.setInputConfigKey(localConfigKey);
		ConfUtil.DbHandler.setOutputConfigKey(localConfigKey);
		final LocalConfigKey dBLck = ConfUtil.DbHandler.getInputConfigKey();
		if (dBLck == null) {
		    logger.error("localConfigKey " + localConfigKey + " not found!");
		    System.exit(1);
		}
		logger.debug("DB localConfigKey: " + dBLck.getClass() + " (" + dBLck.getId() + ", " + dBLck.getName() + ")");
		//}
	}

	// TODO: Generalize the method by making XMLREGISTER_FIELD its argument
	private void processXml() throws DataAccessException, RuntimeException, InstantiationException, IllegalAccessException, NoSuchMethodException, InvocationTargetException {
		RpctSettingsXml settings = settingsDoc.getRpctSettingsXml();

		rpct.util.xml.config.Board[] boards = settings.getBoardArray();
		System.out.println("Settings have " + boards.length + " boards.");

		for (rpct.util.xml.config.Board board : boards) {
			System.out.println(" XmlBoard: id " + board.getId() + ", name "
					+ board.getName());
			final int xmlBoardId = board.getId().intValue();
			
			for (rpct.util.xml.config.Chip xmlChip : board.getChipArray()) {
				System.out.println(" \t XmlChip: id " + xmlChip.getId() + ", name "
						+ xmlChip.getName());
				
				Chip chip = ConfUtil.DbHandler.equipmentDAO.getChips(Collections.singletonList(xmlChip.getId().intValue()), true, false).get(0);
				logger.debug(chip);
				if (xmlBoardId != chip.getBoard().getId()) {
					logger.error("xml board id " + xmlBoardId + " != DB board id " + chip.getBoard().getId() + "!");
					ConfUtil.rollbackDb();
					System.exit(3);
				}

				StaticConfiguration configuration = null;
				try {
					if (logger.isInfoEnabled()) {
						System.out.println("=> DB has");
						ConfUtil.print(chip);
						System.out.println("-ao----------------------------------------------------------------");
					}
					System.out.println("-ao get chip config");
					final StaticConfiguration oldConfiguration = ConfUtil.getChipConf(chip);
					System.out.println("-ao----------------------------------------------------------------");

					// Clone the configuration
					switch (chip.getType()) {
					case TTUTRIG:
					    System.out.println("-ao- In: " + fileName + " > Found TTUTRIG chip");
					    configuration = new TtuTrigConf((TtuTrigConf) oldConfiguration);
					    break;
					case TTUFINAL:
					    System.out.println("-ao- " + fileName + " > Found TTUFINAL chip");
					    configuration = new TtuFinalConf((TtuFinalConf) oldConfiguration);
					    break;
					default:
						logger.error("Cannot handle ChipType " + chip.getType() + "!");
						ConfUtil.rollbackDb();
						System.exit(1);
					}
				}
				catch (NullPointerException e) {
					logger.warn("No configuration found in DB. Trying to instatiate one.");
					switch (chip.getType()) {
					case TTUTRIG:
					    System.out.println("-ao- newConfiguration> Found TTUTRIG chip");
					    configuration = new TtuTrigConf();
					    break;
					case TTUFINAL:
					    System.out.println("-ao- newConfiguration> Found TTUFINAL chip");
					    configuration = new TtuFinalConf();
					    break;
					default:
						logger.error("Cannot handle ChipType " + chip.getType() + "!");
						ConfUtil.rollbackDb();
						System.exit(1);
					}
				}
				
				/// The map of xml attributes to setter methods
				final Map<String, Method> attrToSetter = new HashMap<String, Method>();
				for (Method method: configuration.getClass().getDeclaredMethods()) {
					if (method.getName().startsWith("set")) {
						logger.debug("Got setter " + method.getName());
						for (String attr: XMLREGISTER_FIELD.keySet()) {
							final String field = XMLREGISTER_FIELD.get(attr);
							if (method.getName().equals("set" + field.substring(0, 1).toUpperCase() + field.substring(1))) {
								attrToSetter.put(attr, method);
								logger.debug(attr + " mapped to " + method.getName());
								break;
							}
						}
					}
				}

				/// Will save the new configuration if only it differs from 
				/// what we have in the DB
				boolean configurationChanged = false;
				
				for (rpct.util.xml.config.Register register : xmlChip.getRegisterArray()) {
					final String xmlName = register.getRegName();
					final String xmlValue= register.getRegValue();
					System.out.println(" \t\t XmlRegister: name " + xmlName + 
							", value " + xmlValue);

					final Method setter = attrToSetter.get(register.getRegName());
					if (setter == null) {
						logger.error("xml attribute " + xmlName + " is not mapped to Config field!");
						ConfUtil.rollbackDb();
						System.exit(5);
					}
					final Class<?> argClass = setter.getParameterTypes()[0];
					Object arg = null;
					final Object confValue = valueForSetter(configuration,
							setter);
					
					/// Note: xmlValue is hexadecimal
					if (argClass.equals(int.class)) {
						arg = Integer.parseInt(xmlValue, 16);
					}
					else if (argClass.getSimpleName().equals("byte[]")) {
						/// REC_MUX_{CLC90, CLC_INV, REG_ADD} have the same number of bytes
						arg = new Binary(xmlValue, 48).getBytes();
					}
					
					if (!confValue.equals(arg)) {
						try {
							setter.invoke(configuration, arg);
							logger.debug("Called " + setter.getName() + "(" + arg + ")");
						} catch (Exception e) {
							logger.error("Failed to invoke " + setter.getName() + "(" + arg + ")!");
							throw new RuntimeException(e);
						}
						configurationChanged = true;
					}
				}

				/// TabRegister is a complex type stored in its own table
				for (rpct.util.xml.config.TabRegister tabRegister : xmlChip.getTabRegisterArray()) {
					final String xmlName = tabRegister.getRegName();
					final int xmlSize= tabRegister.getSize().intValue();
					System.out.println(" \t\t XmlTabRegister: name " + xmlName +
							", size " + xmlSize);

					final Method setter = attrToSetter.get(tabRegister.getRegName());
					if (setter == null) {
						throw new IllegalStateException("xml attribute " + xmlName + " is not mapped to Config field!");
					}
					
					final IntArray arg = (IntArray) valueForSetter(configuration, setter);
					for (rpct.util.xml.config.TabValue tabValue : tabRegister.getTabValueArray()) {
					    
						final int xmlIndex = tabValue.getIndex().intValue();
						final String xmlValue = tabValue.getRegValue();
						System.out.println(" \t\t\t XmlTabValue: index " + xmlIndex + 
								", value " + xmlValue);
						
						/// Note: xmlValue is hexadecimal
						final int value = Integer.parseInt(xmlValue, 16);
						//System.out.println("-ao-: new value: " + xmlName + " " + value + " old: "  + arg.getValue(xmlIndex) );
						
						//if (arg.getValue(xmlIndex) != value) { // ... this seems not working
						arg.setValue(xmlIndex, value);
						configurationChanged = true;
						//}							
					}
					
					// and finally set the tabRegister value
					try {
						setter.invoke(configuration, arg);
						logger.debug("Called " + setter.getName() + "(" + Arrays.toString(arg.getValues()) + ")");
					} catch (Exception e) {
						logger.error("Failed to invoke " + setter.getName() + "(" + Arrays.toString(arg.getValues()) + ")!");
						throw new RuntimeException(e);
					}
				}

				if (logger.isInfoEnabled()) {
					System.out.println("=> New config from xml:");
					logger.info(configuration);
				}
				
				if (saveToDb) {

				    if (! configurationChanged) {
						logger.info("Configuration is not changed - not saving to DB!");
					}
					else {
						logger.debug("Trying to save configuration to DB ...");
						ConfUtil.DbHandler.configurationDAO.saveObject(configuration);
						ConfUtil.DbHandler.configurationManager.assignConfiguration(chip,
								configuration, ConfUtil.DbHandler.getOutputConfigKey().getName());
						logger.info("Configuration is saved.");
						logger.info(" for lck " + ConfUtil.DbHandler.getOutputConfigKey().getName());
					}
				} else {
				    logger.info("Configuration NOT saved (simulation ONLY)");
				    logger.info(" for lck " + ConfUtil.DbHandler.getOutputConfigKey().getName());
				}
				
			}
		}
	}

	/**
	 * @param configuration
	 * @param setter
	 * @return Value the getter corresponding to the setter returns
	 * @throws NoSuchMethodException
	 * @throws SecurityException
	 * @throws InvocationTargetException 
	 * @throws IllegalAccessException 
	 * @throws IllegalArgumentException 
	 */
	private static Object valueForSetter(StaticConfiguration configuration,
			final Method setter) throws NoSuchMethodException,
			SecurityException, IllegalArgumentException, IllegalAccessException, InvocationTargetException {
		final Method getter = configuration.getClass().getDeclaredMethod("get" + setter.getName().substring(3)); 
		final Object value = getter.invoke(configuration);
		// TODO: add toString() to IntArray
		logger.debug("Call " + getter.getName() + " returned " + value);

		return value;
	}

	private static final Map<String, String> XMLREGISTER_FIELD = new HashMap<String, String>() {
		private static final long serialVersionUID = 1L;
		{
			/// TTU_TRIG
			put("REC_MUX_CLK90", "recMuxClk90");
			put("REC_MUX_CLK_INV", "recMuxClkInv");
			put("REC_MUX_REG_ADD", "recMuxRegAdd");
			put("REC_MUX_DELAY", "recMuxDelay");
			put("REC_DATA_DELAY", "recDataDelay");
			put("TA_TRG_DELAY", "taTrgDelay");
			put("TA_TRG_TOFF", "taTrgToff");
			put("TA_TRG_SELECT", "taTrgSelect");
			put("TA_TRG_CNTR_GATE", "taTrgCntrGate");
			put("TA_SECTOR_DELAY", "taSectorDelay");
			put("TA_FORCE_LOGIC_0", "taForceLogic0");
			put("TA_FORCE_LOGIC_1", "taForceLogic1");
			put("TA_FORCE_LOGIC_2", "taForceLogic2");
			put("TA_FORCE_LOGIC_3", "taForceLogic3");
			put("TRIG_CONFIG", "trigConfig");
			put("TRIG_MASK", "trigMask");
			put("TRIG_FORCE", "trigForce");
			put("TRIG_MAJORITY", "trigMajority");
			put("SECTOR_MAJORITY", "sectorMajority");
			put("SECTOR_TRIG_MASK", "sectorTrigMask");
			put("SECTOR_THRESHOLD", "sectorThreshold");
			put("TOWER_THRESHOLD", "towerThreshold");
			put("WHEEL_THRESHOLD", "wheelThreshold");
			put("SECT_TRG_SEL", "sectTrgSel");
			put("TA_CONFIG2", "taConfig2");
			/// TTU_FINAL
			put("TRIG_CONFIG", "trigConfig"); ///present in TTU_TRIG too
			put("TRIG_CONFIG2", "trigConfig2");
			put("MASK_TTU", "maskTtu");
			put("MASK_POINTING", "maskPointing");
			put("MASK_BLAST", "maskBlast");
			put("DELAY_TTU", "delayTtu");
			put("DELAY_POINTING", "delayPointing");
			put("DELAY_BLAST", "delayBlast");
			put("SHAPE_TTU", "shapeTtu");
			put("SHAPE_POINTING", "shapePointing");
			put("SHAPE_BLAST", "shapeBlast");
		}
	};
}
