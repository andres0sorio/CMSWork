#ifndef _XDAQRPCCONNECTIVITYTEST_H_
#define _XDAQRPCCONNECTIVITYTEST_H_

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
#include "rpct/xdaqdiagaccess/XdaqDiagAccessClient.h"

using namespace rpct;
using namespace rpct::xdaqutils;
using namespace rpct::xdaqdiagaccess;
 
class XdaqRpcConnectivityTest: public xdaq::Application { 

 private:

  rpct::xdaqutils::XdaqDbServiceClient dbServiceClient;
  rpct::XdaqLBoxAccessClient lboxAccessClient;
  rpct::xdaqdiagaccess::XdaqDiagAccessClient diagAccessClient;
  typedef XdaqDbServiceClient::FebAccessInfoVector FAIV;
  typedef std::vector<XdaqDbServiceClient::FebAccessInfoVector> FAIVV;
  typedef std::map<int ,rpct::XdaqLBoxAccessClient::MassiveWriteRequestBag  > instanceRequestMap;
  typedef std::map<int ,rpct::XdaqLBoxAccessClient::MassiveWriteResponseBag*> instanceResponseMap;
  typedef std::map<int ,rpct::XdaqLBoxAccessClient::MassiveReadRequestBag   > instanceReadRequestMap;
  typedef std::map<int ,rpct::XdaqLBoxAccessClient::MassiveReadResponseBag* > instanceReadResponseMap;

  FAIVV FAIVVector;
  std::string selectedChambers;
  std::string mainTitle;
  std::string subTitle;

 private:
  void PageHeader(xgi::Input * in, xgi::Output * out, std::string mainTitle_, std::string subTitle_) throw (xgi::exception::Exception);
  void PageFooter(xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);

  void SelectChambersGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void SelectChambersFormData(xgi::Input * in, bool &barrelOrEndcap, int &wheel, int &secOrTow, int &tower, int &lSector, int &sector, int &layer) throw (xgi::exception::Exception);
  void SelectChambersAction(bool &barrelOrEndcap, int &wheel, int &secOrTow, int &tower, int &lSector, int &sector, int &layer) throw (xoap::exception::Exception);

  void SetFebValuesGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void SetFebValuesFormData(xgi::Input * in, int VTH[], int VMON[]) throw (xgi::exception::Exception);
  void SetFebValuesAction(xgi::Input * in, xgi::Output * out, int VTH[], int VMON[], instanceResponseMap &lbbAppMapResponse) throw (xoap::exception::Exception);
  void SetFebValuesResult(xgi::Input * in, xgi::Output * out, instanceResponseMap lbbAppMapResponse) throw (xgi::exception::Exception);

  void ReadFebValuesGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void ReadFebValuesAction(xgi::Input * in, xgi::Output * out) throw (xoap::exception::Exception);
  void ReadFebValuesResult(xgi::Input * in, xgi::Output * out, instanceReadResponseMap lbbAppMapResponse) throw (xgi::exception::Exception);

  /*
  void ReadNoiseGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void ReadNoiseFormData(xgi::Input * in) throw (xgi::exception::Exception);
  void ReadNoiseAction(xgi::Input * in, xgi::Output * out) throw (xoap::exception::Exception);
  void ReadNoiseResult(xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
  */
  void ConnectivityTestGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void ConnectivityTestFormData(xgi::Input * in, int &VTHlow, int &VTHhigh) throw (xgi::exception::Exception);
  void ConnectivityTestAction(xgi::Input * in, xgi::Output * out, int VTHlow, int VTHhigh) throw (xoap::exception::Exception);
  //  void ConnectivityTestResult(xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
  
  void getLocationFromName(std::string name, bool &barrelOrEndcap, XdaqDbServiceClient::BarrelOrEndcap boe, int &wheel, int &layer, int &sector, std::string &subsector);

  rpct::XdaqLBoxAccessClient::MassiveWriteResponseBag* SetSingleFebValues(FebAccessInfo febAccessInfo, bool barrelOrEndcap, int arr_VTH[], int arr_VMON[]);
  void ReadSingleChamberNoiseToFile(std::ofstream &ofile, XdaqDbServiceClient::BarrelOrEndcap boe, int wheel, int layer, int sector, std::string subsector);
  void linkBoardCounters(int instance, int chipId, double rate[96]);


 public:
  static const char* RPCT_RPC_CONFIG_NS;
  static const char* RPCT_RPC_CONFIG_PREFIX;
  static const std::string bsubsectors[];
  static const std::string blayers[];
  static const std::string str_barrelOrEndcap[];
  static const char* prop_vth[];
  static const char* prop_vmon[];
  static const char* prop_temp[];
  static const XdaqDbServiceClient::BarrelOrEndcap boe_arr[];
  static const int DEFAULT_VMON = 3500;
  static const int CHIPS_PER_SIGNALCABLE = 2;
  static const int partitions[2][3];
  static const int feb_locations[2][4][6]; // barrelOrEndcap, disk, order
  static const unsigned long SECOND_IN_BX = 40000000;
  XDAQ_INSTANTIATOR();    
 
  XdaqRpcConnectivityTest(xdaq::ApplicationStub * s);      

  virtual ~XdaqRpcConnectivityTest();
                
  void Default(xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);
  void SelectChambers(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void SetFebValues(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void ReadFebValues(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  //  void ReadNoise(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void ConnectivityTest(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  void Reset(xgi::Input * in, xgi::Output * out)throw (xgi::exception::Exception);

};

const std::string XdaqRpcConnectivityTest::bsubsectors[] = {"--", "-", "+", "++"};
const std::string XdaqRpcConnectivityTest::blayers[] = {"","1in", "1out", "2in", "2out", "3", "4"};
const std::string XdaqRpcConnectivityTest::str_barrelOrEndcap[] = {"barrel", "endcap"};
const XdaqDbServiceClient::BarrelOrEndcap XdaqRpcConnectivityTest::boe_arr[] = {XdaqDbServiceClient::BARREL, XdaqDbServiceClient::ENDCAP};

const char* XdaqRpcConnectivityTest::prop_vth[] = {MassiveWriteRequest::PROP_VTH1, MassiveWriteRequest::PROP_VTH2, MassiveWriteRequest::PROP_VTH3, MassiveWriteRequest::PROP_VTH4};
const char* XdaqRpcConnectivityTest::prop_vmon[] = {MassiveWriteRequest::PROP_VMON1, MassiveWriteRequest::PROP_VMON2, MassiveWriteRequest::PROP_VMON3, MassiveWriteRequest::PROP_VMON4};
const char* XdaqRpcConnectivityTest::prop_temp[] = {MassiveReadRequest::PROP_TEMPERATURE, MassiveReadRequest::PROP_TEMPERATURE2};

const int XdaqRpcConnectivityTest::partitions[2][3] = {{0,1,2},{2,1,0}};
const int XdaqRpcConnectivityTest::feb_locations[2][4][6] = 
  {
    {
      {0,1,0,1,0,1},
      {0,1,0,1,0,1},
      {0,1,0,1,0,1},
      {0,1,0,1,0,1}
    },
    {
      {0,1,1,0,1,0},
      {0,1,0,1,1,0},
      {0,1,0,1,1,0},
      {0,1,0,1,1,0}
    }
  };
// endcap, A1,A2,B1,B2,C1,C2

#endif
