// $Id: $
#ifndef LINUX_RBCCONTROLQUICKSYNC_H 
#define LINUX_RBCCONTROLQUICKSYNC_H 1

// Include files
#include "CommonIncludes.h"

//#include "xdaq/WebApplication.h"
//#include "xgi/Method.h"
//#include "xdata/UnsignedLong.h"
//#include "cgicc/HTMLClasses.h"

//...From xdaq
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
#include "xdata/String.h"
#include "xdata/UnsignedLong.h"

#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//...From RPC
#ifndef _AOTEST

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
#include "rpct/devices/System.h"
#include "rpct/devices/System.h"
#include "rpct/devices/XmlSystemBuilder.h"
#include "rpct/xdaqutils/XdaqDbServiceClient.h"
#include "rpct/xdaqlboxaccess/XdaqLBoxAccessClient.h"

#include "xdata/rpctsoap/Serializer.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/fsm/FailedEvent.h"

#endif


/** @class RbcControlQuickSync RbcControlQuickSync.h linux/RbcControlQuickSync.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-02-24
 */

#ifndef _AOTEST 
typedef rpct::xdaqutils::XdaqDbServiceClient::RbcInfoVector rbcs;
typedef std::vector<rpct::RbcInfo>::iterator rbcs_iter;
#endif

class RbcControlQuickSync : public xdaq::Application {
public: 
  
  XDAQ_INSTANTIATOR();
	
  RbcControlQuickSync(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
  
  void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
  void writeData(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  
  void WriteRegister( std::string selRegister, std::string wheel, std::string sector, bool registerBool[8] );
  
  int  IntFromBool( bool selRegister[8] );
  
  bool BoolFromInt( int integer, int i  );
  
  int setRegisterMap( const char * );
  
protected:
  
private:
  
#ifndef _AOTEST 
  rpct::xdaqutils::XdaqDbServiceClient dbServiceClient;	
  rbcs* myrbcs;
  rpct::XdaqLBoxAccessClient lboxAccessClient;
#endif
  
  int m_wheel;
  bool m_isDone;
  std::ifstream * m_in;
  
  std::vector<int> m_wheelid;
  std::vector<int> m_sectorid;
  std::map<std::string, int> m_RbcInstances;
  std::map<std::string, int> m_RegisterAddressFromName;


};
#endif // LINUX_RBCCONTROLQUICKSYNC_H
