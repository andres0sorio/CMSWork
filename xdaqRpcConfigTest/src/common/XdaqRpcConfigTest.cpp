/*
 *  Author: Michal Pietrusinski, William Whitacher & Giovanni Polese
 *  Modified by: Andres Osorio on 2009/3/30
 *  Version: $Id: XdaqRpcConfig.cpp,v 1.21 2008/09/11 09:15:13 tb Exp $
 *
 */

#include "XdaqRpcConfigTest.h"

#include "xdaq/ApplicationGroup.h"

#include "xdata/soap/NamespaceURI.h"
#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"
#include "xdata/XStr.h"
#include "xdata/Float.h"
#include "xdata/Bag.h"
#include "xdata/Boolean.h"
#include "xdata/Integer.h"

#include "xoap/domutils.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "rpct/devices/System.h"
#include "rpct/devices/XmlSystemBuilder.h"
#include <log4cplus/configurator.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;
using namespace rpct;
using namespace rpct::xdaqutils;
using namespace cgicc;


XDAQ_INSTANTIATOR_IMPL(XdaqRpcConfigTest);


const char* XdaqRpcConfigTest::RPCT_RPC_CONFIG_NS = "urn:rpct-rpc-config:1.0";
const char* XdaqRpcConfigTest::RPCT_RPC_CONFIG_PREFIX = "rrc";


XdaqRpcConfigTest::XdaqRpcConfigTest(xdaq::ApplicationStub * s)
        : xdaq::Application(s), dbServiceClient(this), lboxAccessClient(this) {

  LOG4CPLUS_INFO(getApplicationLogger(),"Hello World!");
  //getApplicationLogger().setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
  m_flagHTML = false;
  xgi::bind(this,&XdaqRpcConfigTest::Default, "Default");
  xgi::bind(this,&XdaqRpcConfigTest::configDemo, "configDemo");
  
  xoap::bind(this, &XdaqRpcConfigTest::onRpcConfigDemo, "rpcConfigDemo", RPCT_RPC_CONFIG_NS);
  
  ////////////////////// F S M /////////////////////////
  xoap::bind(this, &XdaqRpcConfigTest::fireEvent, "Configure", XDAQ_NS_URI );
  xoap::bind(this, &XdaqRpcConfigTest::fireEvent, "Start", XDAQ_NS_URI );
  xoap::bind(this, &XdaqRpcConfigTest::fireEvent, "Pause", XDAQ_NS_URI );
  xoap::bind(this, &XdaqRpcConfigTest::fireEvent, "Resume", XDAQ_NS_URI );
  xoap::bind(this, &XdaqRpcConfigTest::fireEvent, "Halt", XDAQ_NS_URI );
  xoap::bind(this, &XdaqRpcConfigTest::reset, "Reset", XDAQ_NS_URI );
  
  
  fsm.addState('H', "Halted", this, &XdaqRpcConfigTest::stateChanged);
  fsm.addState('C', "Configured", this, &XdaqRpcConfigTest::stateChanged);
  fsm.addState('R', "Running", this, &XdaqRpcConfigTest::stateChanged);
  fsm.addState('P', "Paused", this, &XdaqRpcConfigTest::stateChanged);
  
  fsm.addStateTransition('H', 'C', "Configure", this, &XdaqRpcConfigTest::ConfigureAction);
  fsm.addStateTransition('C', 'R', "Start", this,&XdaqRpcConfigTest::EnableAction);
  fsm.addStateTransition('R', 'P', "Pause",this, &XdaqRpcConfigTest::SuspendAction);
  fsm.addStateTransition('P', 'R', "Resume",this, &XdaqRpcConfigTest::ResumeAction);
  
  fsm.addStateTransition('H', 'H', "Halt", this, &XdaqRpcConfigTest::HaltAction);
  fsm.addStateTransition('C', 'H', "Halt", this, &XdaqRpcConfigTest::HaltAction);
  fsm.addStateTransition('R', 'H', "Halt", this, &XdaqRpcConfigTest::HaltAction);
  fsm.addStateTransition('P', 'H', "Halt", this, &XdaqRpcConfigTest::HaltAction);
  
  // Failure state setting
  fsm.setFailedStateTransitionAction(this, &XdaqRpcConfigTest::failedTransition);
  fsm.setFailedStateTransitionChanged(this, &XdaqRpcConfigTest::stateChanged);
  
  fsm.setInitialState('H');
  fsm.setStateName('F', "Failed"); // give a name to the 'F' state
  
  fsm.reset();
  
  // Export a "State" variable that reflects the state of the state machine
  getApplicationInfoSpace()->fireItemAvailable("stateName", &stateName);
  getApplicationInfoSpace()->fireItemAvailable("GLOBAL_CONF_KEY", &globalConfKey);
  
  ///////////////////////// F S M   E N D ////////////////////

  m_outfile = new ofstream("readbacktest-AO.dat", ofstream::out );

  m_isBarrel = false;
  m_isEndcap = false;
  
}

XdaqRpcConfigTest::~XdaqRpcConfigTest() {

}

void XdaqRpcConfigTest::ReadBack( xgi::Output* out, instanceReadMap & instanceForReadLBBox, int sum){
  
  LOG4CPLUS_INFO(getApplicationLogger(),"New Size Endcap:");
  //int csa1=0;
  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::title("Command Receive Message") << std::endl;
  std::string url = "/";
  url += getApplicationDescriptor()->getURN();
  url += "/Default";
  
  *out << cgicc::h2().set("align","center").set("font color","#347C17").set("font size","6")
       << "RPC Configuration Completed" 
       << cgicc::h2()<< std::endl;
  
  *out << cgicc::h4().set("align","left").set("font color","#0000FF").set("font size","6")
       << "Total Number of Febs configured: "
       << sum<<cgicc::h4()<< std::endl;
  
  *out << cgicc::a("Return to settings menu").set("href",url) << std::endl;
  
  
    // INSERISCI QUI LA TABELLA DI VISUALIZZAZIONE
  
  ofstream prova;
  time_t rawtime;
  time(&rawtime);
  const char* nome = "febSet.list";
  
  prova.open(nome,ios::app);
  prova<<ctime(&rawtime)<<endl;
  
  for(instanceReadMap::iterator iMap = instanceForReadLBBox.begin(); iMap != instanceForReadLBBox.end(); ++iMap){
    
    MassiveReadResponse& readResponse = instanceForReadLBBox[iMap->first]->bag;
    FebProperties& props = readResponse.getProperties();
    
    *out << "<p>" << std::endl;
    *out << cgicc::table().set("width", "600").set("align","left").set("border", "2").
      set("bordercolor", "#000066").set("cellpadding", "6").set("cellspacing", "2");
    *out << cgicc::tr();
    *out << cgicc::td();
    *out << cgicc::div().set("align", "center") << "Chamber" << cgicc::div();
    *out << cgicc::td();
    *out << cgicc::td();
    *out << cgicc::div().set("align", "center") << "Local Partition" << cgicc::div();
    *out << cgicc::td();
    *out << cgicc::td();
    *out << cgicc::div().set("align", "center") << "CCU Address" << cgicc::div();
    *out << cgicc::td();
    *out << cgicc::td();
    *out << cgicc::div().set("align", "center") << "CB Channel" << cgicc::div();
    *out << cgicc::td();
    *out << cgicc::td();
    *out << cgicc::div().set("align", "center") << "I2C Local Number" << cgicc::div();
    *out << cgicc::td();
    
    for (FebProperties::iterator iProp = props.begin(); iProp != props.end(); ++iProp) {
      *out << cgicc::td();
      *out << cgicc::div().set("align", "center") << (string)(*iProp) << cgicc::div();
      *out << cgicc::td();
    }
    
    *out << cgicc::tr();
    
    FebValuesVector& valuesVector = readResponse.getFebValues();
  
    for (FebValuesVector::iterator iVal = valuesVector.begin(); iVal != valuesVector.end(); ++iVal) {
      FebValues& febValues = iVal->bag;
      FebInfo& febInfo = febValues.getFeb().bag;
      *out << cgicc::tr()
           << cgicc::td()
           << cgicc::div().set("align", "center") << (string)febInfo.getChamberLocationName() << cgicc::div()
           << cgicc::td()
           << cgicc::td()
           << cgicc::div().set("align", "center") << (string)febInfo.getFebLocalEtaPartition() << cgicc::div()
           << cgicc::td()
           << cgicc::td()
           << cgicc::div().set("align", "center") << febInfo.getCcuAddress() << cgicc::div()
           << cgicc::td()
           << cgicc::td()
           << cgicc::div().set("align", "center") << febInfo.getChannel() << cgicc::div()
           << cgicc::td()
           << cgicc::td()
           << cgicc::div().set("align", "center") << febInfo.getAddress() << cgicc::div()
           << cgicc::td();
      
      prova<<(string)febInfo.getChamberLocationName()<<"\t";
      
      FebValues::Values& values = febValues.getValues();
      for (FebValues::Values::iterator iValue = values.begin(); iValue != values.end(); ++iValue) {
        prova<<(*iValue)<<"\t";
        *out << cgicc::td() << cgicc::div().set("align", "center") << (*iValue) << cgicc::div() << cgicc::td();
      }
      *out << cgicc::tr();
      
      prova<<endl;
    }
    
    FebErrorsVector& errorsVector = readResponse.getFebErrors();
    
    for (FebErrorsVector::iterator iErr = errorsVector.begin(); iErr != errorsVector.end(); ++iErr) {
      FebErrors& febErrors = iErr->bag;
      FebInfo& febInfo = febErrors.getFeb().bag;
      *out << cgicc::tr()
           << cgicc::td()
           << cgicc::div().set("align", "center") << (string)febInfo.getChamberLocationName() << cgicc::div()
           << cgicc::td()
           << cgicc::td()
           << cgicc::div().set("align", "center") << (string)febInfo.getFebLocalEtaPartition() << cgicc::div()
           << cgicc::td()
           << cgicc::td()
           << cgicc::div().set("align", "center") << febInfo.getCcuAddress() << cgicc::div()
           << cgicc::td()
           << cgicc::td()
           << cgicc::div().set("align", "center") << febInfo.getChannel() << cgicc::div()
           << cgicc::td()
           << cgicc::td()
           << cgicc::div().set("align", "center") << febInfo.getAddress() << cgicc::div()
           << cgicc::td();
      
      prova<<(string)febInfo.getChamberLocationName() << "\t" << febErrors.getError() << "\t";
      
      *out << cgicc::td().set("colspan", rpct::toString(props.size())) << cgicc::div().set("align", "center") 
           << febErrors.getError() << cgicc::div() << cgicc::td();
      *out << cgicc::tr();
      
      prova<<endl;
      
    }
    
    *out<< cgicc::table();
    delete instanceForReadLBBox[iMap->first];
  }
  
  //delete lastMassiveWriteResponse;
  
  m_flagHTML=false;
  prova<<endl;
  prova.close();

}

void XdaqRpcConfigTest::Default(xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception) {
  
  
  ////FACILE
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::title("Send SOAP Message") << std::endl;
  ///FINE FACILE
  
  m_flagHTML = true;
  
  xgi::Utils::getPageHeader(
                            out,
                            "RPC Configuration Program",
                            getApplicationDescriptor()->getContextDescriptor()->getURL(),
                            getApplicationDescriptor()->getURN(),
                            "/daq/xgi/images/Application.jpg"
                            );
  
  // HTML PAGE
  std::string url = "/";
  url += getApplicationDescriptor()->getURN();
  url += "/configDemo";
  
  *out <<cgicc::h1().set("align","center").set("font size","6")<< "RPC Configuration Application" << cgicc::h1()<< std::endl;
  *out << cgicc::form().set("method","POST").set("action", url).set("enctype","multipart/form-data") << std::endl;
  
  *out << cgicc::table().set("width", "600").set("align","center").set("border", "1").set("bordercolor", "#000066")<< std::endl;
  
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td().set("width", "300").set("cellspacing", "2").set("align","center")<< std::endl;
  *out <<  "<input type=\"checkbox\" name=\"isCheckBarrel\" id=\"isCheckBarrel\" value=\"Barrel\" > Barrel"<< std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::td().set("cellspacing", "2").set("align","center")<< std::endl;
  *out << "<input type=\"checkbox\" name=\"isCheckEndcap\" id=\"isCheckEndcap\" value=\"Endcap\" > Endcap"<< std::endl;
  *out << cgicc::td()<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::tr()<< std::endl;
  *out << cgicc::td().set("cellspacing", "2")<< std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Wheel</font>" << std::endl;
  
  *out << "  <select name=\"wheel\" size=\"1\" id=\"wheel\">" << std::endl;
  *out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"-2\">-2</option>" << std::endl;
  *out << "    <option value=\"-1\">-1</option>" << std::endl;
  *out << "    <option value=\"0\">0</option>" << std::endl;
  *out << "    <option value=\"1\">+1</option>" << std::endl;
  *out << "    <option value=\"2\">+2</option>" << std::endl;
  *out << "  </select></p>"<< std::endl;
  
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Sector</font>" << std::endl;
  *out << "  <select name=\"bSector\" size=\"1\" id=\"bSector\">" << std::endl;
  *out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"1\">Sector 01</option>" << std::endl;
  *out << "    <option value=\"2\">Sector 02</option>" << std::endl;
  *out << "    <option value=\"3\">Sector 03</option>" << std::endl;
  *out << "    <option value=\"4\">Sector 04</option>" << std::endl;
  *out << "    <option value=\"5\">Sector 05</option>" << std::endl;
  *out << "    <option value=\"6\">Sector 06</option>" << std::endl;
  *out << "    <option value=\"7\">Sector 07</option>" << std::endl;
  *out << "    <option value=\"8\">Sector 08</option>" << std::endl;
  *out << "    <option value=\"9\">Sector 09</option>" << std::endl;
  *out << "    <option value=\"10\">Sector 10</option>" << std::endl;
  *out << "    <option value=\"11\">Sector 11</option>" << std::endl;
  *out << "    <option value=\"12\">Sector 12</option>" << std::endl;
  *out << "  </select></p>"<< std::endl;
  
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Chamber</font>"<< std::endl;
  *out << "  <select name=\"chamber\" size=\"1\" id=\"chamber\">" << std::endl;
  *out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"1\">RB1in</option>" << std::endl;
  *out << "    <option value=\"2\">RB1out</option>" << std::endl;
  *out << "    <option value=\"3\">RB2in</option>" << std::endl;
  *out << "    <option value=\"4\">RB2out</option>" << std::endl;
  *out << "    <option value=\"5\">RB3-</option>" << std::endl;
  *out << "    <option value=\"6\">RB3+</option>" << std::endl;
  *out << "    <option value=\"7\">RB4-</option>" << std::endl;
  *out << "    <option value=\"8\">RB4+</option>" << std::endl;
  *out << "    <option value=\"9\">RB4--</option>" << std::endl;
  *out << "    <option value=\"10\">RB4++</option>" << std::endl;
  *out << "    <option value=\"11\">RB4</option>" << std::endl;
  *out << "  </select> </p>" << std::endl;
  
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Eta Partition</font>" << std::endl;

  *out << "  <select name=\"posOnChambB\" size=\"1\" id=\"posOnChambB\">" << std::endl;
  *out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"1\">Forward</option>" << std::endl;
  *out << "    <option value=\"2\">Central</option>" << std::endl;
  *out << "    <option value=\"3\">Backward</option>" << std::endl;
  *out << "  </select></p>"<< std::endl;
  
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Local Partition</font>" << std::endl;

  *out << "  <select name=\"febPos\" size=\"1\" id=\"febPos\">" << std::endl;
  //*out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"1\">0</option>" << std::endl;
  *out << "    <option value=\"2\">1</option>" << std::endl;
  *out << "    <option value=\"3\">2</option>" << std::endl;
  *out << "    <option value=\"4\">3</option>" << std::endl;
  *out << "    <option value=\"5\">4</option>" << std::endl;
  *out << "    <option value=\"6\">5</option>" << std::endl;
  *out << "  </select></p>"<< std::endl;
  
  *out  << cgicc::td();
  *out  << cgicc::td().set("cellspacing", "2");
  
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Disk</font>"<< std::endl;
  *out << "  <select name=\"disk\" size=\"1\" id=\"disk\">" << std::endl;
  *out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"-4\">-4</option>" << std::endl;
  *out << "    <option value=\"-3\">-3</option>" << std::endl;
  *out << "    <option value=\"-2\">-2</option>" << std::endl;
  *out << "    <option value=\"-1\">-1</option>" << std::endl;
  *out << "    <option value=\"0\">0</option>" << std::endl;
  *out << "    <option value=\"1\">+1</option>" << std::endl;
  *out << "    <option value=\"2\">+2</option>" << std::endl;
  *out << "    <option value=\"3\">+3</option>" << std::endl;
  *out << "    <option value=\"4\">+4</option>" << std::endl;
  *out << "  </select> </p>" << std::endl;
  
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Layer</font>" << std::endl;
  
  *out << "  <select name=\"layer\" size=\"1\" id=\"layer\">" << std::endl;
  *out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"1\">Layer 01</option>" << std::endl;
  *out << "    <option value=\"2\">Layer 02</option>" << std::endl;
  *out << "    <option value=\"3\">Layer 03</option>" << std::endl;
  *out << "    <option value=\"4\">Layer 04</option>" << std::endl;
  *out << "    <option value=\"5\">Layer 05</option>" << std::endl;
  *out << "    <option value=\"6\">Layer 06</option>" << std::endl;
  *out << "  </select> </p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Sector</font>" << std::endl;
  *out << "  <select name=\"eSector\" size=\"1\" id=\"eSector\">" << std::endl;
  *out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"1\">Sector 01</option>" << std::endl;
  *out << "    <option value=\"2\">Sector 02</option>" << std::endl;
  *out << "    <option value=\"3\">Sector 03</option>" << std::endl;
  *out << "    <option value=\"4\">Sector 04</option>" << std::endl;
  *out << "    <option value=\"5\">Sector 05</option>" << std::endl;
  *out << "    <option value=\"6\">Sector 06</option>" << std::endl;
  *out << "    <option value=\"7\">Sector 07</option>" << std::endl;
  *out << "    <option value=\"8\">Sector 08</option>" << std::endl;
  *out << "    <option value=\"9\">Sector 09</option>" << std::endl;
  *out << "    <option value=\"10\">Sector 10</option>" << std::endl;
  *out << "    <option value=\"11\">Sector 11</option>" << std::endl;
  *out << "    <option value=\"12\">Sector 12</option>" << std::endl;
  *out << "    <option value=\"13\">Sector 13</option>" << std::endl;
  *out << "    <option value=\"14\">Sector 14</option>" << std::endl;
  *out << "    <option value=\"15\">Sector 15</option>" << std::endl;
  *out << "    <option value=\"16\">Sector 16</option>" << std::endl;
  *out << "    <option value=\"17\">Sector 17</option>" << std::endl;
  *out << "    <option value=\"18\">Sector 18</option>" << std::endl;
  *out << "    <option value=\"19\">Sector 19</option>" << std::endl;
  *out << "    <option value=\"20\">Sector 20</option>" << std::endl;
  *out << "    <option value=\"21\">Sector 21</option>" << std::endl;
  *out << "    <option value=\"22\">Sector 22</option>" << std::endl;
  *out << "    <option value=\"23\">Sector 23</option>" << std::endl;
  *out << "    <option value=\"24\">Sector 24</option>" << std::endl;
  *out << "    <option value=\"25\">Sector 25</option>" << std::endl;
  *out << "    <option value=\"26\">Sector 26</option>" << std::endl;
  *out << "    <option value=\"27\">Sector 27</option>" << std::endl;
  *out << "    <option value=\"28\">Sector 28</option>" << std::endl;
  *out << "    <option value=\"29\">Sector 29</option>" << std::endl;
  *out << "    <option value=\"30\">Sector 30</option>" << std::endl;
  *out << "    <option value=\"31\">Sector 31</option>" << std::endl;
  *out << "    <option value=\"32\">Sector 32</option>" << std::endl;
  *out << "    <option value=\"33\">Sector 33</option>" << std::endl;
  *out << "    <option value=\"34\">Sector 34</option>" << std::endl;
  *out << "    <option value=\"35\">Sector 35</option>" << std::endl;
  *out << "    <option value=\"36\">Sector 36</option>" << std::endl;
  *out << "  </select></p>" << std::endl;
  
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\" face=\"Times New Roman, Times, serif\">Eta Partition</font>" << std::endl;
  
  *out << "  <select name=\"posOnChambE\" size=\"1\" id=\"posOnChambE\">" << std::endl;
  *out << "    <option value=\"99\">All</option>" << std::endl;
  *out << "    <option value=\"1\">A</option>" << std::endl;
  *out << "    <option value=\"2\">B</option>" << std::endl;
  *out << "    <option value=\"3\">C</option>" << std::endl;
  *out << "  </select></p>"<< std::endl;
  *out << cgicc::td();
 
  *out << cgicc::tr();
  *out << cgicc::tr();
  *out << cgicc::td().set("border", "0").set("width", "300").set("cellspacing", "2")<< std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\"  face=\"Times New Roman, Times, serif\"> Choose Threshold: </font></p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"3\"  face=\"Times New Roman, Times, serif\">VTH1  </font>" << std::endl;
  *out << "<input type=\"text\"  size=\"5\" id=\"VTH1\" name=\"VTH1\" value =\"210\"></input> </p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"3\" face=\"Times New Roman, Times, serif\">VTH2  </font>" << std::endl;
  *out << "<input type=\"text\"  size=\"5\" id=\"VTH2\" name=\"VTH2\" value =\"210\"> </input> </p>" << std::endl;
  *out << "<p>only for endcap:</p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"3\"  face=\"Times New Roman, Times, serif\">VTH3  </font>" << std::endl;
  *out << "<input type=\"text\"  size=\"5\" id=\"VTH3\" name=\"VTH3\" value =\"210\"></input> </p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"3\" face=\"Times New Roman, Times, serif\">VTH4  </font>" << std::endl;
  *out << "<input type=\"text\"  size=\"5\" id=\"VTH4\" name=\"VTH4\" value =\"210\"> </input> </p>" << std::endl;
  *out << cgicc::td();
  *out << cgicc::td().set("border", "0").set("width", "300").set("cellspacing", "2");
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\"  face=\"Times New Roman, Times, serif\"> Choose Pulse width: </font></p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"3\" face=\"Times New Roman, Times, serif\">VMON1  </font>" << std::endl;
  *out << "<input type=\"text\"  size=\"5\" id=\"VMON1\" name=\"VMON1\" value =\"3500\"> </input>  </p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"3\" face=\"Times New Roman, Times, serif\">VMON2  </font>" << std::endl;
  *out << "<input type=\"text\"  size=\"5\" id=\"VMON2\" name=\"VMON2\" value =\"3500\"> </input> </p>" << std::endl;
  *out << "<p>only for endcap:</p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"3\" face=\"Times New Roman, Times, serif\">VMON3  </font>" << std::endl;
  *out << "<input type=\"text\"  size=\"5\" id=\"VMON3\" name=\"VMON3\" value =\"3500\"> </input>  </p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << "  <font size=\"3\" face=\"Times New Roman, Times, serif\">VMON4  </font>" << std::endl;
  *out << "<input type=\"text\"  size=\"5\" id=\"VMON4\" name=\"VMON4\" value =\"3500\"> </input> </p>" << std::endl;
  *out << cgicc::td();
  *out << cgicc::tr();
  *out << cgicc::tr();
  
  *out << cgicc::td().set("border", "0").set("align","center").set("width", "600").set("cellspacing", "2").set("colspan","2");
  *out << "<p>" << std::endl;
  *out << "  <font size=\"4\"  face=\"Times New Roman, Times, serif\"> </font></p>" << std::endl;
  *out << "<p>" << std::endl;
  *out << cgicc::p().set("align","center") << std::endl;

  // ...
  *out << "Fast "    << cgicc::input().set("type","radio").set("name","wmode").set("value","Fast")  << std::endl;
  *out << "Precise " << cgicc::input().set("type","radio").set("name","wmode").set("value","Precise")  << std::endl;
  *out << cgicc::input().set("type","submit").set("align","center").set("name", "send").set("value","Write")  << std::endl;
  
  *out << cgicc::p() << std::endl;
  *out << cgicc::td();
  *out << cgicc::tr();
  *out << cgicc::table();
  
  
  *out << cgicc::form() << std::endl;
	LOG4CPLUS_INFO(getApplicationLogger(),"Fine Default ");
	xgi::Utils::getPageFooter(*out);

}

void XdaqRpcConfigTest::config(xgi::Output* out, int * infoVector, bool writePrecise ) {
  
  XdaqSoapAccess::TSOAPParamList paramList;
  
  // connect to DBService - get information about which Febs should be contacted
  // and how
  
  LOG4CPLUS_INFO(getApplicationLogger(),"F :" << infoVector[1]<<infoVector[2]<< infoVector[3]<<infoVector[4]);
  LOG4CPLUS_INFO(getApplicationLogger(),"E :" << infoVector[5]<<infoVector[6]<< infoVector[7]<<infoVector[8] 
                 << infoVector[9]<<infoVector[10]);
  
  int boe = 0;
  int sum = 0;
  
  FAIV* febAccessInfoVector=0;
  FAIV* febAccessInfoVectorEndcap=0;
  
  if( this->m_isBarrel )  {
    boe++;
    setFebAccessForBarrel( infoVector, febAccessInfoVector , sum );
  }
  
  if( this->m_isEndcap ) {
    boe+=2;
    setFebAccessForEndcap( infoVector, febAccessInfoVectorEndcap , sum );
  }
  
  instanceMap instanceForLBBox;
  
  //--------------------------------------------------------------------------
  // WriteToBarrel
  if( this->m_isBarrel )  {
    WriteToBarrel ( infoVector, febAccessInfoVector, instanceForLBBox );
  }
  
  LOG4CPLUS_INFO(getApplicationLogger(),"FAIV barrel ready:");
  
  // WriteToEndcap
  if( this->m_isEndcap ) {
    WriteToEndcap( infoVector, febAccessInfoVectorEndcap, instanceForLBBox );
  }

  LOG4CPLUS_INFO(getApplicationLogger(),"FAIV Endcap ready:");
  
  //--------------------------------------------------------------------------
  
  LOG4CPLUS_INFO(getApplicationLogger(),"Sending data (1) ... ");
  //XdaqLBoxAccessClient::MassiveWriteResponseBag* lastMassiveWriteResponse;
  
  instanceReadMap instanceForReadLBBox;
  
  for(instanceMap::iterator iMap = instanceForLBBox.begin(); iMap != instanceForLBBox.end(); ++iMap){
    
    LOG4CPLUS_INFO(getApplicationLogger()," Map number "<< iMap->first);
    
    try {
      instanceForReadLBBox[iMap->first] = lboxAccessClient.massiveWrite(iMap->second, iMap->first);
    }
    catch (exception& e) {
      LOG4CPLUS_ERROR(getApplicationLogger(), "std exception: " << e.what());
    }
    
  }
  LOG4CPLUS_INFO(getApplicationLogger(),"Completed" );
  
  //--------------------------------------------------------------------------
  //
  if ( ! writePrecise ) {
    
    if(m_flagHTML)
      ReadBack(out, instanceForReadLBBox, sum);
    
    delete febAccessInfoVector;
    delete febAccessInfoVectorEndcap;
      
    return; //. nothing more to do
    
  }
  
  //--------------------------------------------------------------------------
  // Apply correction to thresold values
  
  //delete febAccessInfoVector;
  //delete febAccessInfoVectorEndcap;
  
  //if( this->m_isBarrel )  {
  //  setFebAccessForBarrel( infoVector, febAccessInfoVector , sum );
  //}
  
  //if( this->m_isEndcap ) {
  //  setFebAccessForEndcap( infoVector, febAccessInfoVectorEndcap , sum );
  //}
  
  //--------------------------------------------------------------------------

  //. Read first and get the current thresolds
  std::vector<int> currentInfoValues;
  std::vector<int> correctInfoValues;
  
  ReadBack( instanceForReadLBBox, currentInfoValues );
  
  //.. evaluate corrections
  EvalThresoldCorretion( infoVector, currentInfoValues, correctInfoValues); //change to EvalThresoldCorrection
  
  instanceMap instanceTwoForLBBox;

  //... write again to FEBs
  if( this->m_isBarrel ) {
    WriteToBarrel ( infoVector, correctInfoValues, febAccessInfoVector, instanceTwoForLBBox );
  }
  
  LOG4CPLUS_INFO(getApplicationLogger(),"FAIV barrel ready (1)");
  
  if( this->m_isEndcap ) {
    WriteToEndcap( infoVector, correctInfoValues, febAccessInfoVectorEndcap, instanceTwoForLBBox );
  }
  
  LOG4CPLUS_INFO(getApplicationLogger(),"FAIV Endcap ready (2)");
  
  //--------------------------------------------------------------------------
  //
  LOG4CPLUS_INFO(getApplicationLogger(),"Sending data (2) ...");
  // XdaqLBoxAccessClient::MassiveWriteResponseBag* lastMassiveWriteResponse;
  // instanceReadMap instanceForReadLBBox;
  
  instanceReadMap instanceTwoForReadLBBox;

  for(instanceMap::iterator iMap = instanceTwoForLBBox.begin(); iMap != instanceTwoForLBBox.end(); ++iMap){
    
    LOG4CPLUS_INFO(getApplicationLogger()," Map number "<< iMap->first);
    
    try {
      instanceTwoForReadLBBox[iMap->first] = lboxAccessClient.massiveWrite(iMap->second, iMap->first);
    }
    catch (exception& e) {
      LOG4CPLUS_ERROR(getApplicationLogger(), "std exception: " << e.what());
    }
    
  }
  
  LOG4CPLUS_INFO(getApplicationLogger(),"Completed" );
  
  if(m_flagHTML)
    ReadBack(out, instanceTwoForReadLBBox, sum);
  
  delete febAccessInfoVector;
  delete febAccessInfoVectorEndcap;
  
}


void XdaqRpcConfigTest::configDemo(xgi::Input* in, xgi::Output* out)
  throw (xgi::exception::Exception) {
  
  int infoVector[18];
  
  m_isBarrel = false;
  m_isEndcap = false;
  
  try {
    
    Cgicc formData(in);
    form_iterator iDisk = formData.getElement("disk");
    form_iterator iLayer = formData.getElement("layer");
    form_iterator ieSector = formData.getElement("eSector");
    form_iterator iWheel = formData.getElement("wheel");
    form_iterator ibSector = formData.getElement("bSector");
    form_iterator iChamber = formData.getElement("chamber");
    form_iterator ibEta = formData.getElement("posOnChambB");
    form_iterator ieEta = formData.getElement("posOnChambE");
    form_iterator ifeb = formData.getElement("febPos");
    form_iterator ivth1 = formData.getElement("VTH1");
    form_iterator ivth2 = formData.getElement("VTH2");
    form_iterator ivth3 = formData.getElement("VTH3");
    form_iterator ivth4 = formData.getElement("VTH4");
    form_iterator ivmon1 = formData.getElement("VMON1");
    form_iterator ivmon2 = formData.getElement("VMON2");
    form_iterator ivmon3 = formData.getElement("VMON3");
    form_iterator ivmon4 = formData.getElement("VMON4");
    
    vector<FormEntry> endc;
    vector<FormEntry> barr;

    m_isBarrel = formData.getElement("isCheckBarrel",barr);
    m_isEndcap = formData.getElement("isCheckEndcap",endc);

    if ( m_isBarrel && m_isEndcap ) m_isEndcap = false; //set a default in case both items are checked
    
    string wmode = formData("wmode");
    bool writePrecise(false);
    
    if ( wmode == string("Fast") ) writePrecise = false;
    else if ( wmode == string("Precise") ) writePrecise = true;
    else {
      LOG4CPLUS_ERROR(getApplicationLogger(), "Write mode not identified");
    }
    
    if (iDisk != formData.getElements().end()) {
      
      infoVector[1] = iDisk->getIntegerValue();
      infoVector[2] = iLayer->getIntegerValue();
      infoVector[3] = ieSector->getIntegerValue();
      infoVector[4] = iWheel->getIntegerValue();
      infoVector[5] = ibSector->getIntegerValue();
      infoVector[6] = iChamber->getIntegerValue();
      infoVector[7] = ivth1->getIntegerValue();
      infoVector[8] = ivth2->getIntegerValue();
      infoVector[9] = ivmon1->getIntegerValue();
      infoVector[10] = ivmon2->getIntegerValue();
      infoVector[11] = ibEta->getIntegerValue();
      infoVector[12] = ieEta->getIntegerValue();
      infoVector[13] = ifeb->getIntegerValue();
      infoVector[14] = ivth3->getIntegerValue();
      infoVector[15] = ivth4->getIntegerValue();
      infoVector[16] = ivmon3->getIntegerValue();
      infoVector[17] = ivmon4->getIntegerValue();
      
      LOG4CPLUS_INFO(getApplicationLogger(),"Barrel: " << m_isBarrel << " Endcap: " << m_isEndcap );
      
      config(out, infoVector, writePrecise ); 
      
    }
    
  }
  
  catch (xdaq::exception::Exception& e) {
    LOG4CPLUS_ERROR(getApplicationLogger(), "Error");
    XCEPT_RETHROW(xgi::exception::Exception, "Cannot send message", e);
  }
  
  catch (std::exception& e) {
    LOG4CPLUS_ERROR(getApplicationLogger(), "Error1");
    XCEPT_RAISE(xgi::exception::Exception, string("Cannot send message ") + e.what());
  }
  
  catch (...) {
    LOG4CPLUS_ERROR(getApplicationLogger(), "Error2");
    XCEPT_RAISE(xgi::exception::Exception, "Cannot send message - unknown reason");
  }

  
}


xoap::MessageReference XdaqRpcConfigTest::onRpcConfigDemo(xoap::MessageReference msg)
  throw (xoap::exception::Exception) {
  
  xgi::Output* out = NULL;
  
  try {
    
    int infoVector[18];
    
    infoVector[1] = 99;
    infoVector[2] = 1;
    infoVector[3] = 1;
    infoVector[4] = 99;
    infoVector[5] = 1;
    infoVector[6] = 1;
    infoVector[7] = 210;
    infoVector[8] = 210;
    infoVector[9] = 3500;
    infoVector[10] = 3500;
    infoVector[11] = 1;
    infoVector[12] = 1;
    infoVector[13] = 1;
    infoVector[14] = 210;
    infoVector[15] = 210;
    infoVector[16] = 3500;
    infoVector[17] = 3500;

    config(out, infoVector, false );
    return xoap::createMessage();
  
  }
  catch (TException& e) {
    LOG4CPLUS_ERROR(getApplicationLogger(), e.what());
    XCEPT_RAISE(xoap::exception::Exception, e.what());
  }

}

xoap::MessageReference XdaqRpcConfigTest::fireEvent (xoap::MessageReference msg)
  throw (xoap::exception::Exception) {
  
  xoap::SOAPPart part = msg->getSOAPPart();
  xoap::SOAPEnvelope env = part.getEnvelope();
  xoap::SOAPBody body = env.getBody();

  DOMNode* node = body.getDOMNode();
  DOMNodeList* bodyList = node->getChildNodes();
  
  for (unsigned int i = 0; i < bodyList->getLength(); i++) {
    DOMNode* command = bodyList->item(i);
    
    if (command->getNodeType() == DOMNode::ELEMENT_NODE) {
      
      std::string commandName = xoap::XMLCh2String (command->getLocalName());
      
      try {
        toolbox::Event::Reference e(new toolbox::Event(commandName,this));
        fsm.fireEvent(e);
      }
      catch (toolbox::fsm::exception::Exception & e)	{
        XCEPT_RETHROW(xoap::exception::Exception, "invalid command", e);
      }
      
      xoap::MessageReference reply = xoap::createMessage();
      xoap::SOAPEnvelope envelope = reply->getSOAPPart().getEnvelope();
      xoap::SOAPName responseName = envelope.createName( commandName +"Response", "xdaq", XDAQ_NS_URI);
      // xoap::SOAPBodyElement e = envelope.getBody().addBodyElement ( responseName );
      (void) envelope.getBody().addBodyElement ( responseName );
      return reply;
    }
  }
  
  XCEPT_RAISE(xcept::Exception, "command not found");
  
}

xoap::MessageReference XdaqRpcConfigTest::reset(xoap::MessageReference msg) throw (xoap::exception::Exception)
{
  LOG4CPLUS_INFO (getApplicationLogger(), "New state before reset is: " << fsm.getStateName (fsm.getCurrentState()) );

  fsm.reset();
  stateName = fsm.getStateName (fsm.getCurrentState());
  
  xoap::MessageReference reply = xoap::createMessage();
  xoap::SOAPEnvelope envelope = reply->getSOAPPart().getEnvelope();
  xoap::SOAPName responseName = envelope.createName("ResetResponse", "xdaq", XDAQ_NS_URI);
  // xoap::SOAPBodyElement e = envelope.getBody().addBodyElement ( responseName );
  (void) envelope.getBody().addBodyElement ( responseName );
  
  LOG4CPLUS_INFO (getApplicationLogger(), "New state after reset is: " << fsm.getStateName(fsm.getCurrentState()));
  
  return reply;

}

void XdaqRpcConfigTest::ReadBack( instanceReadMap & instanceForReadLBBox, std::vector<int> & readvalues ) {
  
  
  LOG4CPLUS_INFO(getApplicationLogger(),"Read back current values");
  
  readvalues.clear();
  
  time_t rawtime;
  time(&rawtime);
  
  (*m_outfile) << ctime(&rawtime) << endl;

  (*m_outfile) << "instanceForReadLBBox .start ReadBack. size(): " << instanceForReadLBBox.size() << endl;

  int nmaxvth(0);
  if ( this->m_isBarrel ) nmaxvth = 2;
  if ( this->m_isEndcap ) nmaxvth = 4;
  
  for(instanceReadMap::iterator iMap = instanceForReadLBBox.begin(); iMap != instanceForReadLBBox.end(); ++iMap){
    (*m_outfile) << "+-" << endl;
    
    MassiveReadResponse& readResponse = instanceForReadLBBox[iMap->first]->bag;
    
    FebProperties& props = readResponse.getProperties();
    
    for (FebProperties::iterator iProp = props.begin(); iProp != props.end(); ++iProp) {
      *m_outfile << (string)(*iProp) << endl;
    }
    
    FebValuesVector& valuesVector = readResponse.getFebValues();
    
    for (FebValuesVector::iterator iVal = valuesVector.begin(); iVal != valuesVector.end(); ++iVal) {
      FebValues& febValues = iVal->bag;
      FebInfo& febInfo = febValues.getFeb().bag;
      
      *m_outfile << " +FebInfo+ "
               << " | "
               << (string)febInfo.getChamberLocationName() 
               << " | "
               << " | "
               << (string)febInfo.getFebLocalEtaPartition() 
               << " | "
               << " | "
               << febInfo.getCcuAddress() 
               << " | "
               << " | "
               << febInfo.getChannel() 
               << " | "
               << " | "
               << febInfo.getAddress() 
               << " | ";
      
      (*m_outfile) << (string)febInfo.getChamberLocationName() << "\n" ;
      
      FebValues::Values& values = febValues.getValues();
      
      int counter=0;
      for (FebValues::Values::iterator iValue = values.begin(); iValue != values.end(); ++iValue) {
        //This one stores the values given to thresolds
        *m_outfile << " +FebVals+ " << (*iValue) << "\t";
        if ( counter < nmaxvth )
          readvalues.push_back((*iValue));
        ++counter;
	
      }
      
      (*m_outfile) << endl;
      
    }
    
    (*m_outfile) << "+FebVals total: " << readvalues.size() << endl;
    
    FebErrorsVector& errorsVector = readResponse.getFebErrors();
    
    for (FebErrorsVector::iterator iErr = errorsVector.begin(); iErr != errorsVector.end(); ++iErr) {
      
      FebErrors& febErrors = iErr->bag;
      FebInfo& febInfo = febErrors.getFeb().bag;
      
      *m_outfile << " + "
               << " | "
               << (string)febInfo.getChamberLocationName() 
               << " | "
               << " | "
               << (string)febInfo.getFebLocalEtaPartition() 
               << " | "
               << " | "
               << febInfo.getCcuAddress() 
               << " | "
               << " | "
               << febInfo.getChannel() 
               << " | "
               << " | "
               << febInfo.getAddress() 
               << " | ";
      
      *m_outfile << (string)febInfo.getChamberLocationName() << "\t" << febErrors.getError() << "\t";
      
      *m_outfile << " | " << febErrors.getError() << " | ";
      
      *m_outfile << endl;
      
    }
    
    *m_outfile << '\n';
    
    delete instanceForReadLBBox[iMap->first];
    
  }
  
  (*m_outfile) << "instanceForReadLBBox .end ReadBack. size(): " << instanceForReadLBBox.size() << endl;
  
  //delete lastMassiveWriteResponse;
  
  (*m_outfile) << "End of ReadBack. Mission completed." << endl;
  
  m_outfile->flush();

  //m_outfile->close();
  //delete m_outfile;
  
}

void XdaqRpcConfigTest::EvalThresoldCorretion( int * inval, std::vector<int> & currentval, std::vector<int> & outval )
{
  
  LOG4CPLUS_INFO (getApplicationLogger(), "Evaluate thresold correction" );
  
  outval.clear();
  
  //....
  // Make a copy of original values into the outval vector
  std::vector<int>::iterator itr;
  for( itr = currentval.begin(); itr != currentval.end(); ++itr)
    outval.push_back( (*itr) );
  
  (*m_outfile) << " " << endl;
  (*m_outfile) << "EvalThresoldCorretion>" << endl;
  (*m_outfile) << "current vals: " << currentval.size() 
	       << '\t'
	       << "correct vals: " << outval.size()
	       << '\n';
  
  // Note: this function should check if the read value is within 1s
  // and return some flag. however we are writing everything back again
  // need to correct this in future
  
  int V0(0);
  int Vr(0);
  int nmaxvals = currentval.size();
  bool iswithin1S(false);
  int nmaxvth(0);
  int readpos(0);
  
  if ( this->m_isBarrel ) nmaxvth = 2;
  if ( this->m_isEndcap ) nmaxvth = 4;
  
  nmaxvals = nmaxvals / nmaxvth;

  for ( int j=0; j < nmaxvals; ++j ) {
    
    for ( int k=7; k < (7+nmaxvth); ++k ) {
      
      V0 = inval[k];
      readpos = (j*nmaxvth)+(k-7);
      
      Vr = currentval[ readpos ];
      
      float m1S = (float)V0 - 2.4437;
      float p1S = (float)V0 + 2.4437;
      
      iswithin1S = false;
      if ( Vr >  m1S && Vr < p1S ) iswithin1S = true;
      
      if ( ! iswithin1S )  {
        int Vf = (2 * V0) - Vr;
        outval[ readpos ] = Vf;
      }
      
      (*m_outfile) << " current vth" << (k-7) << '\t' << currentval[ readpos ] ;
      (*m_outfile) << " corrected vth" << (k-7) << '\t' << outval[ readpos ] << endl;
      
    }
    
  }

  LOG4CPLUS_INFO (getApplicationLogger(), "Evaluate thresold correction: done." );
  
}

void XdaqRpcConfigTest::ConfigureAction (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception) {
  
  LOG4CPLUS_INFO (getApplicationLogger(), e->type());
  
}

void XdaqRpcConfigTest::EnableAction (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception) {
  LOG4CPLUS_INFO (getApplicationLogger(), e->type());
}

void XdaqRpcConfigTest::SuspendAction (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception) {
  LOG4CPLUS_INFO (getApplicationLogger(), e->type());
  // a failure is forced here
  //XCEPT_RAISE(toolbox::fsm::exception::Exception, "error in suspend");
}

void XdaqRpcConfigTest::ResumeAction (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception) {
  LOG4CPLUS_INFO (getApplicationLogger(), e->type());
}

void XdaqRpcConfigTest::HaltAction (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception) {
  LOG4CPLUS_INFO (getApplicationLogger(), e->type());
}

void XdaqRpcConfigTest::stateChanged (toolbox::fsm::FiniteStateMachine & fsm) throw (toolbox::fsm::exception::Exception) {
  // Reflect the new state
  stateName = fsm.getStateName (fsm.getCurrentState());
  LOG4CPLUS_INFO (getApplicationLogger(), "New state is:" << fsm.getStateName (fsm.getCurrentState()) );
}

void XdaqRpcConfigTest::failedTransition (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception) {
  toolbox::fsm::FailedEvent & fe = dynamic_cast<toolbox::fsm::FailedEvent&>(*e);
  LOG4CPLUS_INFO (getApplicationLogger(), "Failure occurred when performing transition from: "  <<
                  fe.getFromState() <<  " to: " << fe.getToState() << " exception: " << fe.getException().what() );
}

void XdaqRpcConfigTest::WriteToBarrel( int * infoVector, FAIV * febAccessInfoVector,  instanceMap & instanceForLBBox )
{
  
  for (FAIV::iterator iFAI = febAccessInfoVector->begin(); iFAI != febAccessInfoVector->end(); ++iFAI) {
    FebAccessInfo& febAccessInfo = iFAI->bag;
    
    int xdaqInstanceNumber = febAccessInfo.getXdaqAppInstance();
    
    MassiveWriteRequest& writeRequest = instanceForLBBox[xdaqInstanceNumber].bag;
    
    if(instanceForLBBox[xdaqInstanceNumber].bag.getProperties().empty())
    {
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH1);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH2);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON1);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON2);
    }
    xdata::Bag<FebValues> valuesBag;
    valuesBag.bag.getFeb().bag.setCcuAddress(febAccessInfo.getCcuAddress());
    valuesBag.bag.getFeb().bag.setChannel(febAccessInfo.getI2cChannel());
    valuesBag.bag.getFeb().bag.setAddress(febAccessInfo.getFebAddress());
    valuesBag.bag.getFeb().bag.setChamberLocationName(febAccessInfo.getChamberLocationName());
    valuesBag.bag.getFeb().bag.setFebLocalEtaPartition(febAccessInfo.getFebLocalEtaPartition());
    valuesBag.bag.getFeb().bag.setEndcap(false);

    valuesBag.bag.getValues().push_back(infoVector[7]);  // vth1
    valuesBag.bag.getValues().push_back(infoVector[8]);  // vth2

    valuesBag.bag.getValues().push_back(infoVector[9]);  // vmon1
    valuesBag.bag.getValues().push_back(infoVector[10]); // vmon2
    
    writeRequest.getFebValues().push_back(valuesBag);    //queue value to be writen to FEBs
    
  }
  
  
}

void XdaqRpcConfigTest::WriteToEndcap( int * infoVector, FAIV * febAccessInfoVectorEndcap,  instanceMap & instanceForLBBox )
{
  

  for (FAIV::iterator iFAI = febAccessInfoVectorEndcap->begin(); 
       iFAI != febAccessInfoVectorEndcap->end(); ++iFAI) {
    
    FebAccessInfo& febAccessInfo = iFAI->bag;
    
    //in febaccessInfo c'e la chiave xdaqAppInstance ccome base per la mappa
    // valueBag legge e setta i parametri da scrivere sulle LLBox
    
    int xdaqInstanceNumber = febAccessInfo.getXdaqAppInstance();
    
    MassiveWriteRequest& writeRequest = instanceForLBBox[xdaqInstanceNumber].bag;
    
    if(instanceForLBBox[xdaqInstanceNumber].bag.getProperties().empty())
    {
      
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH1);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH2);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH3);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH4);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON1);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON2);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON3);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON4);
    }
    xdata::Bag<FebValues> valuesBag;
    valuesBag.bag.getFeb().bag.setCcuAddress(febAccessInfo.getCcuAddress());
    valuesBag.bag.getFeb().bag.setChannel(febAccessInfo.getI2cChannel());
    valuesBag.bag.getFeb().bag.setAddress(febAccessInfo.getFebAddress());
    valuesBag.bag.getFeb().bag.setChamberLocationName(febAccessInfo.getChamberLocationName());
    valuesBag.bag.getFeb().bag.setFebLocalEtaPartition(febAccessInfo.getFebLocalEtaPartition());
    valuesBag.bag.getFeb().bag.setEndcap(true);

    valuesBag.bag.getValues().push_back(infoVector[7]);  // vth1
    valuesBag.bag.getValues().push_back(infoVector[8]);  // vth2
    valuesBag.bag.getValues().push_back(infoVector[14]); // vth3
    valuesBag.bag.getValues().push_back(infoVector[15]); // vth4

    valuesBag.bag.getValues().push_back(infoVector[9]);  // vmon1
    valuesBag.bag.getValues().push_back(infoVector[10]); // vmon2
    valuesBag.bag.getValues().push_back(infoVector[16]); // vmon3
    valuesBag.bag.getValues().push_back(infoVector[17]); // vmon4
    
    writeRequest.getFebValues().push_back(valuesBag);    //write to FEBs
    
  }
  
  
}

//... Methods to write -> read -> write correction

void XdaqRpcConfigTest::WriteToBarrel( int * infoVector, 
				       const std::vector<int> & correctVector, 
				       FAIV * febAccessInfoVector,
				       instanceMap & instanceForLBBox ) {
  
  int readpos(0);
  
  for (FAIV::iterator iFAI = febAccessInfoVector->begin(); iFAI != febAccessInfoVector->end(); ++iFAI) {
    FebAccessInfo& febAccessInfo = iFAI->bag;
    
    int xdaqInstanceNumber = febAccessInfo.getXdaqAppInstance();
    
    MassiveWriteRequest& writeRequest = instanceForLBBox[xdaqInstanceNumber].bag;
    
    if(instanceForLBBox[xdaqInstanceNumber].bag.getProperties().empty()) {
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH1);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH2);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON1);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON2);
    }
    
    xdata::Bag<FebValues> valuesBag;
    valuesBag.bag.getFeb().bag.setEndcap(false);
    
    valuesBag.bag.getValues().push_back(correctVector[(readpos*2)+0]);  // vth1
    valuesBag.bag.getValues().push_back(correctVector[(readpos*2)+1]);  // vth2
    
    valuesBag.bag.getValues().push_back(infoVector[9]);  // vmon1
    valuesBag.bag.getValues().push_back(infoVector[10]); // vmon2
    
    writeRequest.getFebValues().push_back(valuesBag);    //write to FEBs
    
    ++readpos;
    
  }
  
}

void XdaqRpcConfigTest::WriteToEndcap( int * infoVector, 
				       const std::vector<int> & correctVector, 
				       FAIV * febAccessInfoVectorEndcap,
				       instanceMap & instanceForLBBox )
{
  
  int readpos(0);
  
  for (FAIV::iterator iFAI = febAccessInfoVectorEndcap->begin(); 
       iFAI != febAccessInfoVectorEndcap->end(); ++iFAI) {
    
    FebAccessInfo& febAccessInfo = iFAI->bag;
    
    int xdaqInstanceNumber = febAccessInfo.getXdaqAppInstance();
    
    MassiveWriteRequest& writeRequest = instanceForLBBox[xdaqInstanceNumber].bag;
    
    if(instanceForLBBox[xdaqInstanceNumber].bag.getProperties().empty()) {
	
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH1);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH2);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH3);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VTH4);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON1);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON2);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON3);
      writeRequest.getProperties().push_back(MassiveWriteRequest::PROP_VMON4);
    }
    xdata::Bag<FebValues> valuesBag;
    
    valuesBag.bag.getValues().push_back(correctVector[(readpos*4)+0]);  // vth1
    valuesBag.bag.getValues().push_back(correctVector[(readpos*4)+1]);  // vth2
    valuesBag.bag.getValues().push_back(correctVector[(readpos*4)+2]);  // vth3
    valuesBag.bag.getValues().push_back(correctVector[(readpos*4)+3]);  // vth4
    
    valuesBag.bag.getValues().push_back(infoVector[9]);  // vmon1
    valuesBag.bag.getValues().push_back(infoVector[10]); // vmon2
    valuesBag.bag.getValues().push_back(infoVector[16]); // vmon3
    valuesBag.bag.getValues().push_back(infoVector[17]); // vmon4
    
    writeRequest.getFebValues().push_back(valuesBag);    //write to FEBs

    ++readpos;

  }
         
}

void XdaqRpcConfigTest::setFebAccessForBarrel( int * infoVector, FAIV & * febAccessInfoVector, int & sum) {
  
  if(infoVector[4]==99) {
    febAccessInfoVector = dbServiceClient.getFebsByBarrelOrEndcap(XdaqDbServiceClient::BARREL);
  }
  else if(infoVector[5]==99) {
    febAccessInfoVector = dbServiceClient.getFebsByDiskOrWheel(infoVector[4],XdaqDbServiceClient::BARREL);
  }
  else if(infoVector[6]==99) {
    febAccessInfoVector =dbServiceClient.getFebsBySector(infoVector[4],infoVector[5],XdaqDbServiceClient::BARREL);
  }
  else if(infoVector[11]==99) {
    //LOG4CPLUS_INFO(getApplicationLogger(),"Dss:"<<infoVector[6]);
    if(infoVector[6]<=4)
      febAccessInfoVector =dbServiceClient.getFebsByChamberLocation(infoVector[4],infoVector[6],infoVector[5],"",
								    XdaqDbServiceClient::BARREL);
    else {
      
      int value = infoVector[6];
      switch (value){
      case 5: febAccessInfoVector =dbServiceClient.getFebsByChamberLocation(infoVector[4],5,infoVector[5],"-",
									    XdaqDbServiceClient::BARREL);break;
      case 6: febAccessInfoVector =dbServiceClient.getFebsByChamberLocation(infoVector[4],5,infoVector[5],"+",
									    XdaqDbServiceClient::BARREL);break;
      case 7: febAccessInfoVector =dbServiceClient.getFebsByChamberLocation(infoVector[4],6,infoVector[5],"-",
									    XdaqDbServiceClient::BARREL);break;
      case 8: febAccessInfoVector =dbServiceClient.getFebsByChamberLocation(infoVector[4],6,infoVector[5],"+",
									    XdaqDbServiceClient::BARREL);break;
      case 9: febAccessInfoVector =dbServiceClient.getFebsByChamberLocation(infoVector[4],6,infoVector[5],"--",
									    XdaqDbServiceClient::BARREL);break;
      case 10: febAccessInfoVector =dbServiceClient.getFebsByChamberLocation(infoVector[4],6,infoVector[5],"++",
									     XdaqDbServiceClient::BARREL);break;
      case 11: febAccessInfoVector =dbServiceClient.getFebsByChamberLocation(infoVector[4],6,infoVector[5],"",
									     XdaqDbServiceClient::BARREL);break;
      
      }
      
    }
    
  } else {
    
    std::string febPosition;
    switch(infoVector[11]) {
    case 1: febPosition = "Forward";break;
    case 2: febPosition = "Central";break;
    case 3: febPosition = "Backward";break;
      
    }
    
    if(infoVector[6]<=4)
      febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(infoVector[4],
								       infoVector[6],
								       infoVector[5],"",
								       "Barrel",febPosition,infoVector[13]);
    else
      switch (infoVector[6]){
      case 5: febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(infoVector[4],5,infoVector[5],"-",
									       "Barrel",febPosition,infoVector[13]);break;
      case 6: febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(infoVector[4],5,infoVector[5],"+",
									       "Barrel",febPosition,infoVector[13]);break;
      case 7: febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(infoVector[4],6,infoVector[5],"-",
									       "Barrel",febPosition,infoVector[13]);break;
      case 8: febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(infoVector[4],6,infoVector[5],"+",
									       "Barrel",febPosition,infoVector[13]);break;
      case 9: febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(infoVector[4],6,infoVector[5],"--",
									       "Barrel",febPosition,infoVector[13]);break;
      case 10: febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(infoVector[4],6,infoVector[5],"++",
										"Barrel",febPosition,infoVector[13]);break;
      case 11: febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(infoVector[4],6,infoVector[5],"",
										"Barrel",febPosition,infoVector[13]);break;
      }
    }
  
  //febAccessInfoVector =dbServiceClient.getSingleFebByLocParameters(1,1,1,"","Barrel","Forward",1);
  int csa =febAccessInfoVector->size();
  sum +=csa;
  LOG4CPLUS_INFO(getApplicationLogger(), "Size Barrel: " << csa  );
  
}

void XdaqRpcConfigTest::setFebAccessForEndcap( int * infoVector, FAIV  & * febAccessInfoVectorEndcap, int  & sum) {
  
  if(infoVector[1]==99)
    febAccessInfoVectorEndcap = dbServiceClient.getFebsByBarrelOrEndcap(XdaqDbServiceClient::ENDCAP);
  else if(infoVector[2]==99)
    febAccessInfoVectorEndcap = dbServiceClient.getFebsByDiskOrWheel(infoVector[1],XdaqDbServiceClient::ENDCAP);
  else if(infoVector[3]==99)
    febAccessInfoVectorEndcap =dbServiceClient.getFebsByLayer(infoVector[1],infoVector[2],XdaqDbServiceClient::ENDCAP);
  else if(infoVector[12]==99)
    febAccessInfoVectorEndcap =dbServiceClient.getFebsByChamberLocation(infoVector[1],infoVector[2],infoVector[3],"",
									XdaqDbServiceClient::ENDCAP);
  else
    {
      string febPosition;
      switch(infoVector[12]){
      case 1: febPosition = "A";break;
      case 2: febPosition = "B";break;
      case 3: febPosition = "C";break;
      }
      
      febAccessInfoVectorEndcap =dbServiceClient.getSingleFebByLocParameters(infoVector[1],
									     infoVector[2],
									     infoVector[3],"",
                                                                             "Endcap",febPosition,1);
    }
  
  int csa1 =febAccessInfoVectorEndcap->size();
  sum +=csa1;
  LOG4CPLUS_INFO(getApplicationLogger(),"Size Endcap:" << csa1  );
  
}

