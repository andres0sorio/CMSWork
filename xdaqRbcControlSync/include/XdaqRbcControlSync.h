#ifndef _XdaqRbcControlSync_h_
#define _XdaqRbcControlSync_h_

#include <map>
#include "rpct/devices/fsb.h"
#include "rpct/devices/hsb.h"
#include "rpct/devices/FebInstanceManager.h"

#include "rpct/devices/IHardwareBuilder.h" 
#include "rpct/devices/LinkBox.h" 
#include "rpct/devices/tcsort.h" 
#include "rpct/devices/TMemoryMapLB.h" 
#include "rpct/devices/TMemoryMapLBWrapper.h" 

#include "rpct/devices/LinkBoard.h"
#include "rpct/devices/cb.h"
#include "rpct/xdaqutils/XdaqDbServiceClient.h"
#include "rpct/xdaqlboxaccess/XdaqLBoxAccessClient.h"
#include "rpct/devices/System.h"
#include "rpct/devices/System.h"
#include "rpct/devices/XmlSystemBuilder.h"

#include "xdaq/Application.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationStub.h"
#include "xdaq/exception/Exception.h" 
#include "xdaq/NamespaceURI.h"
#include "xdaq/WebApplication.h" 
#include "xdaq/ApplicationGroup.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/Method.h"
#include "xoap/domutils.h"

#include "xdata/soap/NamespaceURI.h"
#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"
#include "xdata/XStr.h"   
#include "xdata/Float.h"
#include "xdata/Bag.h"
#include "xdata/Boolean.h"          
#include "xdata/Integer.h"
#include "xdata/rpctsoap/Serializer.h"
#include "xdata/String.h"
#include "xdata/UnsignedLong.h"

#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/fsm/FailedEvent.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include <stdio.h>
#include <fstream>
#include <log4cplus/configurator.h>
#include <sstream>           
#include <time.h>
#include <sstream>
#include <iostream>
#include <string>

#include <math.h>

using namespace cgicc;
using namespace std;

std::string url[]={"/","/","/","/","/","/"};
std::string ModulesName[]={"/LeftFrame","/CenterFrame","/RightFrame","/menuBlue","/redBul","/liteBlue"};
int numUrl=sizeof(url)/sizeof(url[1]);

std::string RegisterName[]={"Temperature","Ctrl", "Conf", "Status", "Majority", "Delay", 
"Shape","Config_in","Gol","Qpll","Goltest1","Goltest2","Goltest3","Goltest4","Ncyc_pulse","Mask","Del_OR0", "Del_0R1","Force", "Prom_reg","Prom_status","FW_VER","BC0_oddA", "BC0_oddB", "BC0_evenA", "BC0_evenB"};
int RegisterAddress[]={0,0,1,2,3,4,5,6,7,8,10,11,12,13,14,16,21,22,32,36,37,64,80,81,82,83};
int numReg=sizeof(RegisterName)/sizeof(RegisterName[1]);//numero di registri e indirizzi corrispondenti

string bigap[15]={"RB1_IN_FW","RB1_IN_BW","RB1_OUT_FW","RB1_OUT_BW","RB2/2_FW","RB2/2_BW","RB2/3_FW","RB2/3_MID","RB2/3_BW","RB3_FW","RB3_BW","RB4+_FW","RB4+_BW","RB4-_FW","RB4-_BW"};

string styleCenter="<style type=\"text/css\">H1{FONT-WEIGHT: bold; FONT-SIZE: 16px; BACKGROUND: white; COLOR: #09c; FONT-FAMILY: Arial, Helvetica, Geneva, Swiss, SunSans-Regular, sans-serif} TD {color: black; FONT-SIZE: 12px; FONT-FAMILY: Arial,Helvetica, Geneva, Swiss, SunSans-Regular, sans-serif}</style>";

string styleLeft= "<style type=\"text/css\">BODY {MARGIN: 6px; }A {FONT-WEIGHT: bold; FONT-SIZE: 10pt; COLOR: white; FONT-FAMILY: Arial, Helvetica, Geneva, Swiss, SunSans-Regular; TEXT-DECORATION: none; }H1 { FONT-WEIGHT: bold; FONT-SIZE: 10pt; MARGIN: 0pt; COLOR: #09c; FONT-FAMILY: Arial, Helvetica, Geneva, Swiss, SunSans-Regular;}BIG { FONT-WEIGHT: bold; FONT-SIZE: 10pt; MARGIN: 0pt; COLOR: #09c; FONT-FAMILY: Arial, Helvetica, Geneva, Swiss, SunSans-Regular;}P, TABLE, TD {	FONT-WEIGHT: normal; FONT-SIZE: 10pt; COLOR: white; FONT-FAMILY: Arial, Helvetica, Geneva, Swiss, SunSans-Regular,sans-serif;}</style>";
string numbers[15]={"[0]","[1]","[2]","[3]","[4]","[5]","[6]","[7]","[8]","[9]","[10]","[11]","[12]","[13]","[14]"};//stringe di controllo

typedef rpct::xdaqutils::XdaqDbServiceClient::RbcInfoVector rbcs;
typedef std::vector<rpct::RbcInfo>::iterator rbcs_iter;

std::map<string,int> rbcInstances;
std::map<string,int> RegisterAddressFromName;

class XdaqRbcControlSync: public xdaq::Application
{
private: 
 rpct::xdaqutils::XdaqDbServiceClient dbServiceClient;	
 rbcs* myrbcs;
 rpct::XdaqLBoxAccessClient lboxAccessClient;
		
public:

 XDAQ_INSTANTIATOR();
	
 XdaqRbcControlSync(xdaq::ApplicationStub * s)               throw (xdaq::exception::Exception);

 void Default(xgi::Input * in, xgi::Output * out )       throw (xgi::exception::Exception);

 //void LeftFrame(xgi::Input * in, xgi::Output * out)      throw (xgi::exception::Exception);
 //void CenterFrame(xgi::Input * in, xgi::Output * out)    throw (xgi::exception::Exception);
 //void RightFrame(xgi::Input * in, xgi::Output * out )    throw (xgi::exception::Exception);

 int ReadRegister(string Register,string wheel, string sector);

 void WriteRegister(string Register,string wheel, string sector,bool RegisterBool[8]);

 int IntFromBool(bool Register[8]);

 bool BoolFromInt(int integer, int i);
 
 void liteBlue(xgi::Input * in, xgi::Output * out )    throw (xgi::exception::Exception);
 
 void menuBlue(xgi::Input * in, xgi::Output * out )    throw (xgi::exception::Exception);
 
 void redBul(xgi::Input * in, xgi::Output * out )    throw (xgi::exception::Exception);
 
};

#endif

