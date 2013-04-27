#ifndef _XDAQRPCCONFIGTEST_H_
#define _XDAQRPCCONFIGTEST_H_


#include "xdaq/Application.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationStub.h"
#include "xdaq/exception/Exception.h" 
#include "xdaq/NamespaceURI.h"
 
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/Method.h"

#include "xdata/Serializable.h"
#include "xdata/rpctsoap/Serializer.h"
#include "xdata/String.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/fsm/FailedEvent.h"

#include "rpct/xdaqlboxaccess/XdaqLBoxAccessClient.h"
#include "rpct/xdaqutils/XdaqDbServiceClient.h"

 
class XdaqRpcConfigTest: public xdaq::Application { 
private:
 
  rpct::xdaqutils::XdaqDbServiceClient dbServiceClient;

  rpct::XdaqLBoxAccessClient lboxAccessClient;
  
  typedef std::map<int , rpct::XdaqLBoxAccessClient::MassiveWriteResponseBag*> instanceReadMap;
  
  typedef rpct::xdaqutils::XdaqDbServiceClient::FebAccessInfoVector FAIV;

  typedef std::map<int , rpct::XdaqLBoxAccessClient::MassiveWriteRequestBag > instanceMap;

  void config(xgi::Output * out, int * infoVectors, bool writePrecise);
  
  void ReadBack(xgi::Output* , instanceReadMap & , int );
  
  void ReadBack(instanceReadMap & , std::vector<int> &);
  
  void EvalThresoldCorretion( int *, std::vector<int> &, std::vector<int> &);
  
  void WriteToBarrel( int *, FAIV * ,  instanceMap & );
  
  void WriteToEndcap( int *, FAIV * ,  instanceMap & );
  
  void WriteToBarrel( int *, const std::vector<int> &, FAIV * , instanceMap & );
  
  void WriteToEndcap( int *, const std::vector<int> &, FAIV * , instanceMap & );

  void setFebAccessForBarrel( int * , FAIV & * , int & );

  void setFebAccessForEndcap( int * , FAIV & * , int & );
  
  toolbox::fsm::FiniteStateMachine fsm; 
  xdata::String stateName; 
  xdata::String globalConfKey;
  
  bool m_flagHTML;
  ofstream * m_outfile;
  bool m_isBarrel;
  bool m_isEndcap;
  
public:

  static const char* RPCT_RPC_CONFIG_NS;
  static const char* RPCT_RPC_CONFIG_PREFIX;
  
  XDAQ_INSTANTIATOR();    
  
  XdaqRpcConfigTest(xdaq::ApplicationStub * s);      
  virtual ~XdaqRpcConfigTest();
  
  void Default(xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);
  
  void configDemo(xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);
  
  xoap::MessageReference onRpcConfigDemo(xoap::MessageReference msg) throw (xoap::exception::Exception);
    
  //
  // SOAP Callback trigger state change 
  //
  xoap::MessageReference fireEvent (xoap::MessageReference msg) 
    throw (xoap::exception::Exception);
  
  //
  // SOAP Callback to reset the state machine
  //
  xoap::MessageReference reset (xoap::MessageReference msg) 
    throw (xoap::exception::Exception);
  
  //
  // Finite State Machine action callbacks
  //
  void ConfigureAction (toolbox::Event::Reference e) 
    throw (toolbox::fsm::exception::Exception);
  
  void EnableAction (toolbox::Event::Reference e) 
    throw (toolbox::fsm::exception::Exception);
  
  void SuspendAction (toolbox::Event::Reference e) 
    throw (toolbox::fsm::exception::Exception);
  
  void ResumeAction (toolbox::Event::Reference e) 
    throw (toolbox::fsm::exception::Exception);
  
  void HaltAction (toolbox::Event::Reference e) 
    throw (toolbox::fsm::exception::Exception);
  
  void failedTransition (toolbox::Event::Reference e) 
    throw (toolbox::fsm::exception::Exception);
  
  //
  // Finite State Machine callback for entring state
  //
  
  void stateChanged (toolbox::fsm::FiniteStateMachine & fsm) 
    throw (toolbox::fsm::exception::Exception);		
  
};

#endif 
