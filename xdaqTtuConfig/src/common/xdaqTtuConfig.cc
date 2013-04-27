// $Id: $
// Include files 



// local
#include "xdaqTtuConfig.h"
#include <boost/filesystem/operations.hpp>

namespace bf = boost::filesystem;

//-----------------------------------------------------------------------------
// Implementation file for class : xdaqTtuConfig
//
// 2009-02-25 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

XDAQ_INSTANTIATOR_IMPL(xdaqTtuConfig)

//=============================================================================

xdaqTtuConfig::xdaqTtuConfig(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception): xdaq::Application(s)
 ,dbServiceClient(this), lboxAccessClient(this)
{
  
  xgi::bind(this,&xdaqTtuConfig::Default, "Default");
  
  xgi::bind(this,&xdaqTtuConfig::ActionBar  , "ActionBar");
  xgi::bind(this,&xdaqTtuConfig::CenterFrame, "CenterFrame");
  xgi::bind(this,&xdaqTtuConfig::LeftFrame  , "LeftFrame");
  xgi::bind(this,&xdaqTtuConfig::RightFrame , "RightFrame");
  xgi::bind(this,&xdaqTtuConfig::SetPreset  , "SetPreset");
  
  xgi::bind(this,&xdaqTtuConfig::SetTtuConfiguration    , "SetTtuConfiguration");
  xgi::bind(this,&xdaqTtuConfig::SetRbcConfiguration    , "SetRbcConfiguration");
  xgi::bind(this,&xdaqTtuConfig::UpdateTtuConfiguration , "UpdateTtuConfiguration");
  xgi::bind(this,&xdaqTtuConfig::UpdateRbcConfiguration , "UpdateRbcConfiguration");
  xgi::bind(this,&xdaqTtuConfig::ExecuteConfiguration   , "ExecuteConfiguration");
  xgi::bind(this,&xdaqTtuConfig::WriteRbcData           , "WriteRbcData");
  
  //initialize parameter to a default value

  m_debug = false;
  m_hasPreset = false;
  m_isTtuConfigured = false;
  m_wheel = -10;
  m_PresetConfig = 0;
  m_ttufileready = false;
  m_ttuconfigdone = false;
  
  m_default_cfg_path= std::string("/nfshome0/rpcdev/bin/config/ttuOri/");
  
  m_ttuscript = std::string("/nfshome0/rpcdev/rpct/xdaqTtuConfig/bin/linux/x86/executeConfig.py");
  
  getApplicationInfoSpace()->fireItemAvailable("", &m_PresetConfig);
  
  m_numUrl = 4;
  std::string tmp("/");
  for(int i=0; i < m_numUrl; ++i) m_app_urls.push_back(tmp);
  
  m_moduleNames.push_back("/ActionBar");
  m_moduleNames.push_back("/LeftFrame");
  m_moduleNames.push_back("/CenterFrame");
  m_moduleNames.push_back("/RightFrame");
  
  m_ActionFrame = new TtuConfigActionFrame  ("ActionBar") ;
  m_LeftFrame   = new TtuConfigLeftFrame    ("LeftFrame") ;
  m_CenterFrame = new TtuConfigCenterFrame  ("CenterFrame") ;
  m_RightFrame  = new TtuConfigRightFrame   ("RightFrame") ;
  
  m_ttuconfig   = new TTUBoardSpecsIO();
  m_rbcconfig   = new RBCBoardSpecsIO();
  
  //... m_RbcInstances
  rpct::xdaqutils::XdaqDbServiceClient::RbcInfoVector rbcs;
  
  typedef std::vector<rpct::RbcInfo>::iterator rbcs_iter;
  
  m_ptr_Rbcs = dbServiceClient.getAllRbcsInfo();
  
  std::map<std::string, int> rbcInstances;
  
  for (rbcs::iterator irbc = m_ptr_Rbcs->begin(); irbc != m_ptr_Rbcs->end(); ++irbc) {
    rbcInstances[(std::string)(irbc->bag.getLinkBoxName())] = irbc->bag.getXdaqAppInstance();
  }
  
  m_RbcControl = new RbcControlQuickSync( rbcInstances );
  
  rbcInstances.clear();
  
  LOG4CPLUS_INFO(this->getApplicationLogger(),"Objects initialized");
  
}

void xdaqTtuConfig::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  
  LOG4CPLUS_INFO(this->getApplicationLogger(),"Default: starts");
  
  //... This is the default application: will only run at the begining
  //... xdaq::ApplicationDescriptor * appDescriptor = getApplicationDescriptor();
  
  out->getHTTPResponseHeader().addHeader("Content-Type", "text/html");
  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eFrames) << std::endl;
  *out << cgicc::head( cgicc::title("RPC Technical Trigger Configuration") ) << std::endl;
  *out << cgicc::html() << std::endl;
  
  //. set the style of the interface
  
  *out << cgicc::title("RPC Technical Trigger Xdaq") << std::endl;
  
  //. build the main objects and set the frames
  //. the front panel is designed with 4 frames (actions, left, center, right)
  
  setApplicationURLS();
  
  *out << cgicc::frameset().set("rows","34%,66%") << std::endl; 
  *out << cgicc::frame().set("noresize","noresize").set("frameborder","0").
    set("src",m_app_urls[0].c_str()).set("name","actions") << std::endl;
  
  *out << "<frameset cols=\"25%,37%,37%\" >" << std::endl;
  
  *out << cgicc::frame().set("noresize","noresize").set("frameborder","0").
    set("src",m_app_urls[1].c_str()).set("name","left")   << std::endl;
  *out << cgicc::frame().set("noresize","noresize").set("frameborder","0").
    set("src",m_app_urls[2].c_str()).set("name","center") << std::endl;
  *out << cgicc::frame().set("noresize","noresize").set("frameborder","0").
    set("src",m_app_urls[3].c_str()).set("name","right")  << std::endl;
  
  *out << "</frameset>\n" << "</frameset>" << std::endl;
  
  *out << cgicc::html();
  
  LOG4CPLUS_INFO(this->getApplicationLogger(),"Default: done");
	
}

void xdaqTtuConfig::setApplicationURLS()
{

  LOG4CPLUS_INFO(this->getApplicationLogger(),"setAppURLS: starts");
  
  if( m_app_urls[0] == std::string("/") ) 
    for(int i=0; i < m_numUrl ; ++i){
      m_app_urls[i] += getApplicationDescriptor()->getURN();
      m_app_urls[i] += m_moduleNames[i];
      LOG4CPLUS_INFO(this->getApplicationLogger(), m_app_urls[i].c_str() ); 
    }
  
  LOG4CPLUS_INFO(this->getApplicationLogger(),"setAppURLS: done");
  
}

void xdaqTtuConfig::ActionBar(xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) {
  
  m_ActionFrame->initialize( );

  std::string methodOne   = toolbox::toString("/%s/ExecuteConfiguration",getApplicationDescriptor()->getURN().c_str());
  
  //std::string methodTwo   = toolbox::toString("/%s/ExecuteConfiguration",getApplicationDescriptor()->getURN().c_str());
  //std::string methodThree = toolbox::toString("/%s/ExecuteConfiguration",getApplicationDescriptor()->getURN().c_str());
  
  m_ActionFrame->process( in , out , methodOne);
  
}

void xdaqTtuConfig::LeftFrame(xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) {
  
  
  //bool status = checkStatus( );
  
  m_LeftFrame->initialize( );
  
  m_LeftFrame->process( in , out );
  
}

void xdaqTtuConfig::CenterFrame(xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) {
  
  m_CenterFrame->initialize( );
  
  if ( !m_hasPreset ) {
    std::string method = toolbox::toString("/%s/SetPreset",getApplicationDescriptor()->getURN().c_str());
    m_CenterFrame->process( in , out , method );
    
  } else {
    std::string methodOne = toolbox::toString("/%s/SetTtuConfiguration",getApplicationDescriptor()->getURN().c_str());
    std::string methodTwo = toolbox::toString("/%s/SetRbcConfiguration",getApplicationDescriptor()->getURN().c_str());
    
    std::string methodThr = toolbox::toString("/%s/WriteRbcData",getApplicationDescriptor()->getURN().c_str());
    
    m_CenterFrame->process( in , out , methodOne, methodTwo, methodThr, m_ttuConfigFiles, m_ttuconfig, m_RbcControl );
    
  }
  
}

void xdaqTtuConfig::RightFrame(xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) {
  
  m_RightFrame->initialize( );
  
  if ( !m_hasPreset ) {
    
    m_RightFrame->process( in , out );
    
  } else {
    std::string methodOne = toolbox::toString("/%s/UpdateRbcConfiguration",getApplicationDescriptor()->getURN().c_str());
    m_RightFrame->process( in , out , m_wheel , methodOne , m_rbcconfig );
    
  }

}

//......................

void  xdaqTtuConfig::SetPreset( xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) 
{
  
  try {
    
    cgicc::Cgicc cgi(in);
		
    m_ttufile = cgi["ttufile"]->getStrippedValue(256);
    m_ttuConfigFiles.push_back( m_ttufile );
    
    std::string cfgfile;
    
    cfgfile = cgi["wm2file"]->getStrippedValue(256);
    m_ttuConfigFiles.push_back( cfgfile );
    
    cfgfile = cgi["wm1file"]->getStrippedValue(256);
    m_ttuConfigFiles.push_back( cfgfile );
    
    cfgfile = cgi["w0file"]->getStrippedValue(256);
    m_ttuConfigFiles.push_back( cfgfile );
    
    cfgfile = cgi["wp1file"]->getStrippedValue(256);
    m_ttuConfigFiles.push_back( cfgfile );
    
    cfgfile = cgi["wp2file"]->getStrippedValue(256);
    m_ttuConfigFiles.push_back( cfgfile );
    
    cfgfile = cgi["bpfile"]->getStrippedValue(256);
    m_ttuConfigFiles.push_back( cfgfile );

    cfgfile = cgi["fastfile"]->getStrippedValue(256);
    m_ttuConfigFiles.push_back( cfgfile );
    
    m_rbcfile = cgi["rbcfile"]->getStrippedValue(256);
         
    bool status = ReadXMLPresetConfig( );
    
    if ( status ) {
      // re-display form page
      m_hasPreset = true;
      this->CenterFrame(in,out);		
    } else {
      m_hasPreset = false;
      this->CenterFrame(in,out);
      
    }
    
  }
  
  catch (const std::exception & e) {
    
    XCEPT_RAISE(xgi::exception::Exception, e.what());
    
  }	
  
}

//......................

void  xdaqTtuConfig::SetTtuConfiguration( xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) 
{
  
  try {
    
    cgicc::Cgicc cgi(in);
    m_useTtuConfigFiles.clear();
    std::ostringstream usefile;
    int maxfiles = m_ttuConfigFiles.size();
    for( int k=1; k <= maxfiles; ++k){ 
      usefile << "usefile" << k; 
      bool checked = cgi.queryCheckbox( usefile.str().c_str() );
      m_useTtuConfigFiles.push_back( checked );
      std::cout << checked << std::endl;
      usefile.str("");
    }
        
    m_isTtuConfigured = true;
    this->CenterFrame(in,out);		
    
  }
  
  catch (const std::exception & e) {
    
    XCEPT_RAISE(xgi::exception::Exception, e.what());
    
  }	
  
}

void  xdaqTtuConfig::SetRbcConfiguration( xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) 
{
  
  try {
    
    cgicc::Cgicc cgi(in);
    m_wheel = cgi["Wheel"]->getIntegerValue();
    
    std::ostringstream logmess;
    logmess << "Will configure RBCs for wheel " << m_wheel;
    LOG4CPLUS_INFO(this->getApplicationLogger(), logmess.str() );
    
    this->RightFrame(in,out);
    
  }
  
  catch (const std::exception & e) {
    
    XCEPT_RAISE(xgi::exception::Exception, e.what());
    
  }	
  
}

void  xdaqTtuConfig::UpdateTtuConfiguration( xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) 
{
  
  try {
    cgicc::Cgicc cgi(in);
    
    LOG4CPLUS_INFO(this->getApplicationLogger(), "Updated RBC configuration!!!" );
    
  }
  
  catch (const std::exception & e) {
    
    XCEPT_RAISE(xgi::exception::Exception, e.what());
    
  }	
  
}



void  xdaqTtuConfig::UpdateRbcConfiguration( xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception) 
{
  
  try {
    cgicc::Cgicc cgi(in);
    
    LOG4CPLUS_INFO(this->getApplicationLogger(), "Updated RBC configuration!!!" );
    
  }
  
  catch (const std::exception & e) {
    
    XCEPT_RAISE(xgi::exception::Exception, e.what());
    
  }	
  
}

//......................

bool  xdaqTtuConfig::ReadPresetConfig() 
{
  
  m_in = new std::ifstream();
  
  std::ostringstream asciicfg;
  asciicfg << "/nfshome0/rpcdev/TriDAS/rpct/xdaqTtuConfig/" << "data/hardware-pseudoconfig.txt";
  
  m_in->open( asciicfg.str().c_str() );
  
  if(!m_in->is_open()) {
    LOG4CPLUS_INFO(this->getApplicationLogger(),"ReadPresetConfig> cannot open file " << asciicfg.str() );
    return false;
  }
  
  RBCBoardSpecs::RBCBoardConfig * rbcboard;
  for( int i=0; i < 30; i++) {
    
    rbcboard = new RBCBoardSpecs::RBCBoardConfig();
    (*m_in) >> (*rbcboard);
    m_rbcconfig->v_boardspecs.push_back( *rbcboard );
    
  };
  
  TTUBoardSpecs::TTUBoardConfig * ttuboard;
  for(int i=0; i < 3; i++){
    
    ttuboard = new TTUBoardSpecs::TTUBoardConfig();
    (*m_in) >> (*ttuboard);
    m_ttuconfig->m_boardspecs.push_back( *ttuboard );
    
  };

  LOG4CPLUS_INFO(this->getApplicationLogger(),"ReadPresetConfig> (from ascii) done");
  
  asciicfg.str("");
  
  return true;
  
}

bool  xdaqTtuConfig::ReadXMLPresetConfig() 
{
  
  //. check if files are available ... if not then go back and type again
  bool status (false);

  int m_maxcfgfiles= m_ttuConfigFiles.size();
  std::ostringstream target;
  
  for(int k=0; k < m_maxcfgfiles; ++k) {
 
    target << m_default_cfg_path << m_ttuConfigFiles[k];
    
    bf::path configttufile( target.str().c_str() );
    
    if(bf::exists(configttufile)) {
      LOG4CPLUS_INFO(this->getApplicationLogger(),"ReadXMLPresetConfig/TTU> ttu file configuration found");
      m_ttufileready = true;
    } else {
      LOG4CPLUS_INFO(this->getApplicationLogger(),"ReadXMLPresetConfig/TTU> cannot open file " << target.str() );
      m_ttufileready = false;
      m_ttuConfigFiles.clear();
      return false;
    }
    
    target.str("");

  }

  //. here do the same for rbc system
  
  bool m_ignoreRbc = true;

  if ( ! m_ignoreRbc ) {
    
    bf::path configrbcfile( m_rbcfile.c_str() );
    
    if(bf::exists(configrbcfile)) {
      LOG4CPLUS_INFO(this->getApplicationLogger(),"ReadXMLPresetConfig> rbc file configuration found");
      m_rbcfileready = true;
    } else {
      LOG4CPLUS_INFO(this->getApplicationLogger(),"ReadXMLPresetConfig> cannot open file" << m_rbcfile.c_str() );
      m_rbcfileready = false;
      return false;
    }
    
  }
  
  //... temporary fix : use the plain ascii file configuration
  //... status = ReadPresetConfig();
  
  //... Parse XML configuration files
  
  for(int k=0; k < m_maxcfgfiles; ++k) {
    
    target << m_default_cfg_path << m_ttuConfigFiles[k];
    
    if ( m_debug ) std::cout << "Parsing file: " << target.str() << std::endl;

    status = ParseTtuConfigurationFile( target.str().c_str() );
    
    target.str("");
    
  }
  
  std::vector<DOMDocument *>::iterator itr;
  int counter(0);
  for( itr = m_xmlDocuments.begin(); itr != m_xmlDocuments.end(); ++itr ) {

    if ( m_debug ) std::cout << (*itr) << std::endl;
    
    *(*itr) >> (*m_ttuconfig);
    
    ++counter;
    
    //if ( counter >= 1 ) break;
    
  }
  
  if ( m_debug ) std::cout << (*m_ttuconfig);
  
  //  not functional
  //  ParseRbcConfigurationFile();
  
  LOG4CPLUS_INFO(this->getApplicationLogger(),"ReadXMLPresetConfig> done");
  
  return true;

}


void xdaqTtuConfig::ExecuteConfiguration( xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception)  
{
  
  try {
    
    cgicc::Cgicc cgi(in);
    
    LOG4CPLUS_INFO(this->getApplicationLogger(),"ExecuteConfiguration> starts here ...");
    
    //... execute script
    int m_maxcfgfiles = m_useTtuConfigFiles.size();
    int counter=0;
    for( int k=0; k < m_maxcfgfiles; ++k) {
      
      std::ostringstream execcmd;
      
      if ( ! m_useTtuConfigFiles[k] ) continue;
      
#ifndef _AOTEST 
      
      execcmd << m_ttuscript << " " << m_ttuConfigFiles[k];
      system( execcmd.str().c_str() ); 
#else      
      execcmd << m_ttuscript << " " << "mytest.xml";
      std::cout << "system( execcmd.str().c_str() );" << std::endl;
      
#endif
      
      ++counter;
      
    }
    
    m_ttuconfigdone = true;
    
    std::cout << "ExecuteConfiguration> total files processed: "  << counter << std::endl;
    
    LOG4CPLUS_INFO(this->getApplicationLogger(),"ExecuteConfiguration> done");
    
    this->ActionBar(in,out);	
    
  }
  
  catch (const std::exception & e) {
    
    XCEPT_RAISE(xgi::exception::Exception, e.what());
    
  }
  
}

bool xdaqTtuConfig::ParseTtuConfigurationFile( const char * infile )
{
  
  if ( m_debug ) std::cout << " Infile :" << std::string(infile) << std::endl;

  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
                              << "  Exception message:"
                              << StrX(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
    return false;
  }
  
  // Build Parser
  
  XercesDOMParser *parser = new XercesDOMParser;
  parser->setValidationScheme(gValScheme);
  parser->setDoNamespaces(gDoNamespaces);
  parser->setDoSchema(gDoSchema);
  parser->setValidationSchemaFullChecking(gSchemaFullChecking);
  parser->setCreateEntityReferenceNodes(gDoCreate);
  
  DOMTreeErrorReporter *errReporter = new DOMTreeErrorReporter();
  parser->setErrorHandler(errReporter);
  
  //..... parse xml file and catch all possible errors
  
  bool errorsOccured = false;
  try
  {
    parser->parse( infile );
  }
  catch (const OutOfMemoryException&)
  {
    XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
    errorsOccured = true;
  }
  catch (const XMLException& e)
  {
    XERCES_STD_QUALIFIER cerr << "An error occurred during parsing\n   Message: "
                              << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
    errorsOccured = true;
  }
  
  catch (const DOMException& e)
  {
    const unsigned int maxChars = 2047;
    XMLCh errText[maxChars + 1];
    
    XERCES_STD_QUALIFIER cerr << "\nDOM Error during parsing: '" << gXmlFile << "'\n"
                              << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
    
    if (DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
      XERCES_STD_QUALIFIER cerr << "Message is: " << StrX(errText) << XERCES_STD_QUALIFIER endl;
    
    errorsOccured = true;
  }
  
  catch (...)
  {
    XERCES_STD_QUALIFIER cerr << "An error occurred during parsing\n " << XERCES_STD_QUALIFIER endl;
    errorsOccured = true;
  }
  
  //...now process tree
  
  if ( !errorsOccured && !errReporter->getSawErrors() ) {
    
    DOMDocument *doc = parser->getDocument();

    m_xmlDocuments.push_back( doc );
 
    m_xmlParsers.push_back( parser );
    
        
  }
  
  delete errReporter;
  
  //delete parser;
  //XMLPlatformUtils::Terminate();
  //XMLString::release(&gOutputEncoding);
  
  LOG4CPLUS_INFO(this->getApplicationLogger(),"ParseTtuConfigurationFile> done");

  return true;
  
}

void xdaqTtuConfig::WriteRbcData(xgi::Input * in, xgi::Output * out ) 
  throw (xgi::exception::Exception)
{
  
  try
    {
      cgicc::Cgicc cgi(in);
      std::ostringstream secStr;
      std::ostringstream wheelStr;
      std::vector<int>::const_iterator secItr;
      std::vector<int>::const_iterator wheelItr;
      std::map<int, std::bitset<6> >::iterator maskItr;

      bool syncword[8];
      syncword[0] = 0;
      syncword[1] = 0;
      syncword[2] = 0;
      syncword[3] = 0;
      syncword[4] = 0;
      syncword[5] = 0;
      syncword[6] = 1;
      syncword[7] = 0;
      
      // retrieve value and update exported variable
      m_RbcControl->m_wheel = cgi["Wheel"]->getIntegerValue();

      std::string tower = cgi("tower");
      
      bool sendTestCtrl (false);
      bool removeTestCtrl (false);
      
      sendTestCtrl = cgi.queryCheckbox( "testpat" );
      
      if ( m_RbcControl->m_sentTestCtrl )
	removeTestCtrl = cgi.queryCheckbox( "rmtestpat" );
      
      std::cout << "sendTestCtrl:   "    << sendTestCtrl   << std::endl;
      std::cout << "RMsendTestCtrl: "    << removeTestCtrl << std::endl;
      std::cout << m_RbcControl->m_wheel << std::endl;
      
      if ( m_RbcControl->m_wheel == 100 ) {
	
	for( wheelItr = m_RbcControl->m_wheelid.begin(); wheelItr != m_RbcControl->m_wheelid.end(); ++wheelItr ){
	  
	  if ( (*wheelItr) <= 0 )
	    wheelStr << (*wheelItr);
	  else wheelStr << "+" << (*wheelItr);
	  
	  int pos(0);
	  
	  for ( secItr = m_RbcControl->m_sectorid.begin(); secItr != m_RbcControl->m_sectorid.end(); ++secItr) {
	    
	    secStr.str("");
	    secStr << (*secItr);
	    
	    maskItr = m_RbcControl->m_RbcMasks.find( (int)(*wheelItr) );
	    
	    std::cout << "mask: " << pos << " " << (*maskItr).second[pos] << " ";
	    
	    if ( (*maskItr).second[pos] ) {
	      secStr.str("");
	      ++pos;
	      continue; //if 1=mask
	    }
	    
	    if ( sendTestCtrl ) {
	      
	      std::cout << " okey now sending Ctrl word " << std::endl;
	      
	      bool testword[8];
	      testword[0] = 0;
	      testword[1] = 0;
	      testword[2] = 0;
	      testword[3] = 0;
	      testword[4] = 1;
	      testword[5] = 0;
	      testword[6] = 0;
	      testword[7] = 0;
	      
	      WriteRbcRegister( std::string ("Ctrl"), wheelStr.str(), secStr.str(), testword );
	      
	      m_RbcControl->m_sentTestCtrl = sendTestCtrl;
	      
	    }
	    
	    if ( removeTestCtrl ) {
	      
	      //...reset Ctrl
	      bool resetword[8];
	      for(int j=0; j< 8; ++j)
		resetword[j] = 0;
	      
	      WriteRbcRegister( std::string ("Ctrl"), wheelStr.str(), secStr.str(), resetword );
	      m_RbcControl->m_sentTestCtrl = false;
	      secStr.str("");
	      ++pos;
	      
	      continue;
	      
	    }
	    
	    WriteRbcRegister( std::string ("Gol"), wheelStr.str(), secStr.str(), syncword );
	    secStr.str("");
	    ++pos;
	    
	  }
	  
	  wheelStr.str("");
	  
	}
	
      } else {
	
	if ( m_RbcControl->m_wheel <= 0 )
	  wheelStr << m_RbcControl->m_wheel;
        else wheelStr << "+" << m_RbcControl->m_wheel;
	
	int pos(0);
	
	std::cout << "sentting sync for wheel " << m_RbcControl->m_wheel << std::endl;
	
	for ( secItr = m_RbcControl->m_sectorid.begin(); secItr != m_RbcControl->m_sectorid.end(); ++secItr) {
	  
	  secStr.str("");
	  secStr << (*secItr);
	  
	  maskItr = m_RbcControl->m_RbcMasks.find( m_wheel );
	  
	  std::cout << "mask: " << pos << " " << (*maskItr).second[pos] << " ";
	  
	  if ( (*maskItr).second[pos] ) {
	    secStr.str("");
	    ++pos;
	    continue; //if 1=mask
	  }
	  
	  if ( ! m_RbcControl->isSectorInTower( (*secItr) , tower ) ) {
	    secStr.str("");
	    ++pos;
	    continue;
	  }
	  
	  if ( sendTestCtrl ) {
	    
	    std::cout << " okey now sending Ctrl word " << std::endl;
	    
	    bool testword[8];
	    testword[0] = 0;
	    testword[1] = 0;
	    testword[2] = 0;
	    testword[3] = 0;
	    testword[4] = 1;
	    testword[5] = 0;
	    testword[6] = 0;
	    testword[7] = 0;
	    
	    WriteRbcRegister( std::string ("Ctrl"), wheelStr.str(), secStr.str(), testword );
	    
	    m_RbcControl->m_sentTestCtrl = sendTestCtrl;
	    
	  } 
	  
	  if ( removeTestCtrl ) {
	    
	    //...reset Ctrl
	    bool resetword[8];
	    for(int j=0; j< 8; ++j)
	      resetword[j] = 0;
	    
	    WriteRbcRegister( std::string ("Ctrl"), wheelStr.str(), secStr.str(), resetword );
	    m_RbcControl->m_sentTestCtrl = false;
	    secStr.str("");
	    ++pos;
	    
	    continue;
	    
	  }
	  
	  
	  WriteRbcRegister( std::string ("Gol"), wheelStr.str(), secStr.str(), syncword );
	  secStr.str("");
	  ++pos;
	  
	}
	
      }
      
      m_RbcControl->m_isDone = true;
      
      //re-display form page 
      this->CenterFrame(in,out);		
    }
  
  
  catch (const std::exception & e)
    {
      m_RbcControl->m_isDone = false;
      XCEPT_RAISE(xgi::exception::Exception, e.what());
    }	
  
}

void xdaqTtuConfig::WriteRbcRegister( std::string selRegister, std::string wheel, std::string sector, bool * registerBool )
{
  
  std::string linkBoxName = "LBB_RB" + wheel + "_S" + sector;         
  
  int address             = m_RbcControl->m_RegisterAddressFromName[selRegister];
  
  int registerInt         = m_RbcControl->IntFromBool( registerBool );
  
  int instanceNumber      = m_RbcControl->m_RbcInstances[linkBoxName];
  
  std::cout << "==============================WRITING================================"  << std::endl;
  std::cout << "Register......................" << selRegister                          << std::endl;
  std::cout << "Wheel........................." << wheel                                << std::endl;
  std::cout << "Sector........................" << sector                               << std::endl;
  
  std::cout << "Instance Number..............." << instanceNumber                       << std::endl;
  std::cout << "Register Address.............." << address                              << std::endl;
  std::cout << "Integer Register Written......" << registerInt                          << std::endl;
  
  std::cout << "Operation.....................writeRbcRegister(\"" 
            << linkBoxName << "\"," 
            << address << ","
            << registerInt  <<"," 
            << instanceNumber <<")"<< std::endl;  
  
  std::cout << "Hexadecimal Register Written.." << std::hex << registerInt << std::dec <<std::endl; 
  
  std::cout << "Byte Written..................{";
  
  for( int i=0; i<8; ++i) {
    std::cout << registerBool[i]; 
    if(i!=7) std::cout << ",";
  }
  
  std::cout << "}" << std::endl;            
  
  //.... avoid crash if the access to LBox fails
  
  try {
    
#ifndef _AOTEST
    std::cout << "Writting to LBAccessClient" << std::endl;
    //.... send write message to lbbox
    lboxAccessClient.writeRbcRegister(linkBoxName,address,registerInt,instanceNumber);

#else
    std::cout << "Writting to LBAccessClient" << std::endl;
#endif
    
  } catch( int k ) {
    
    std::cout << "xdaqTtuConfig::WriteRbcRegister> Cannot access LBoxAccessClient (possible CCU error)" << k << std::endl;    
    
  }
  
}
