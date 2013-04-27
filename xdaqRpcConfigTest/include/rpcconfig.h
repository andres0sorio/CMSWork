#ifndef _RPCCONFIG_H_
#define _RPCCONFIG_H_

#include <map>
#include <string>

#include "rpct/xdaqutils/XdaqDbServiceClient.h"
#include "rpct/xdaqlboxaccess/XdaqLBoxAccessClient.h"
#include "rpct/xdaqlboxaccess/MassiveWriteRequest.h"
#include "rpct/xdaqlboxaccess/MassiveReadRequest.h"

#include "xdata/Vector.h"
#include "xdata/Bag.h"
#include "xdata/Float.h"

namespace rpcconfig {
  
  const int Linksectors_ = 12;
  const int WheelsMinMax_[2][2] = {{-2,2},{-4,4}}; // barrel, endcap
  const std::string Towers_[3] = {"near","far","both"};
  const std::string BarrelLayerName_[7] = {"", "1in", "1out", "2in", "2out", "3", "4"};
  const std::string BarrelSubsectorName_[5] = {"", "--", "-", "+", "++"};
  const std::string PartitionName_[2][4] = {{"backward","central","forward",""},{"A","B","C","D"}};
  const std::string BarrelOrEndcapName_[2] = {"barrel", "endcap"};
  const rpct::xdaqutils::XdaqDbServiceClient::BarrelOrEndcap BoeArr_[2] = {rpct::xdaqutils::XdaqDbServiceClient::BARREL, rpct::xdaqutils::XdaqDbServiceClient::ENDCAP};

  const int DefaultVth_ = 210;
  const int DefaultVmon_ = 3500;
  const int MaxTemp_ = 32;

  const int WriteableFebProps_[2] = {4,8};
  const int ReadableFebProps_[2] = {5,10};
  const int PropertiesNum_[2][3] = {{2,2,1},{4,4,2}};
  const char* Properties_[3][4] = 
    {
      {
	rpct::MassiveWriteRequest::PROP_VTH1,
	rpct::MassiveWriteRequest::PROP_VTH2,
	rpct::MassiveWriteRequest::PROP_VTH3,
	rpct::MassiveWriteRequest::PROP_VTH4
      },
      {
	rpct::MassiveWriteRequest::PROP_VMON1,
	rpct::MassiveWriteRequest::PROP_VMON2,
	rpct::MassiveWriteRequest::PROP_VMON3,
	rpct::MassiveWriteRequest::PROP_VMON4
      },
      {
	rpct::MassiveReadRequest::PROP_TEMPERATURE,
	rpct::MassiveReadRequest::PROP_TEMPERATURE2,
	"",
	""
      }
    };
  const std::string PropertyNames_[3][4] =
    {
      {
	"Vth 1",
	"Vth 2",
	"Vth 3",
	"Vth 4"
      },
      {
	"Vmon 1",
	"Vmon 2",
	"Vmon 3",
	"Vmon 4"
      },
      {
	"Temp 1",
	"Temp 2",
	"",
	""
      }
    };
  const int ChipsPerFeb_[2] = {2,4}; // barrel, endcap
  const int TempsPerFeb_[2] = {1,2};
  
  typedef xdata::Bag<rpct::FebAccessInfo> FebAccessInfoBag;
  typedef xdata::Bag<rpct::FebInfo>       FebInfoBag;
  typedef xdata::Bag<rpct::FebValues>     FebValuesBag;
  typedef xdata::Vector<xdata::Float>     FebFloatValues;

  typedef rpct::XdaqLBoxAccessClient::MassiveWriteRequestBag  MassiveWriteRequestBag;
  typedef rpct::XdaqLBoxAccessClient::MassiveWriteResponseBag MassiveWriteResponseBag;
  typedef rpct::XdaqLBoxAccessClient::MassiveReadRequestBag   MassiveReadRequestBag;
  typedef rpct::XdaqLBoxAccessClient::MassiveReadResponseBag  MassiveReadResponseBag;
  
  typedef std::map<int,MassiveWriteRequestBag>  InstanceWriteRequestMap;
  typedef std::map<int,MassiveWriteResponseBag> InstanceWriteResponseMap;
  typedef std::map<int,MassiveReadRequestBag>   InstanceReadRequestMap;
  typedef std::map<int,MassiveReadResponseBag>  InstanceReadResponseMap;
  
  void getLocationFromName(std::string name, bool &barrelOrEndcap, int &wheel, int &layer, int &sector, int &subsector){
    
    barrelOrEndcap = (name.find("W") == name.npos);
    
    int string_pos[6];
    if (barrelOrEndcap){ // RE_wheel_/_layer_/_sector
      string_pos[0] = name.find("RE")+2;
      string_pos[1] = name.find("/");
      string_pos[2] = string_pos[1]+1;
      string_pos[3] = name.rfind("/");
      string_pos[4] = string_pos[3]+1;
      string_pos[5] = name.length();
      
      // setting subsector and layer
      subsector = 0;
      layer  = atoi((name.substr(string_pos[2], string_pos[3]-string_pos[2])).c_str());
    }
    else{ // W_wheel_/RB_layerstring_/_sector_subsectorstring
      string_pos[0] = name.find("W")+1;
      string_pos[1] = name.find("/RB");
      string_pos[2] = string_pos[1]+3;
      string_pos[3] = name.rfind("/");
      string_pos[4] = string_pos[3]+1;
      // setting subsector
      std::string temp_name = name.substr(string_pos[3],name.npos);
      int plus = (int)temp_name.find("+");
      int min = (int)temp_name.find("-");
      int pos;
      if (plus == min){
	subsector = 0;
	pos = temp_name.length();
      }
      else if (plus == (int)temp_name.npos){
	pos = min;
	if (temp_name.find("--") != temp_name.npos)
	  subsector = 1;
	else
	  subsector = 2;
      }
      else {
	pos = plus;
	if (temp_name.find("++") != temp_name.npos)
	  subsector =4;
	else
	  subsector =3;
      }
      string_pos[5] = pos + string_pos[3];
      
      // setting layer
      layer = atoi((name.substr(string_pos[2], 1)).c_str());
      if (layer > 2)
	layer += 2;
      else{
	if (name.find("in") != name.npos)
	  layer = 2*layer-1;
	else
	  layer *= 2;
      }
    }
    // setting wheel and sector
    wheel  = atoi((name.substr(string_pos[0], string_pos[1]-string_pos[0])).c_str());
    sector = atoi((name.substr(string_pos[4], string_pos[5]-string_pos[4])).c_str());
  }
  
  /**************************************************
   ** Feb                                          **
   **************************************************/
  
  class Feb {
  private:
  protected:
    bool barrelOrEndcap;
    int wheel, layer, sector, subsector, partition;
    FebInfoBag febInfoBag;
    
  public:
    Feb(){};
    Feb(FebAccessInfoBag febAccessInfoBag){
      getLocationFromName(febAccessInfoBag.bag.getChamberLocationName(), barrelOrEndcap, wheel, layer, sector, subsector);

      febInfoBag.bag.setFebId(febAccessInfoBag.bag.getFebId());
      febInfoBag.bag.setFebLocalEtaPartition(febAccessInfoBag.bag.getFebLocalEtaPartition());
      febInfoBag.bag.setChamberLocationName(febAccessInfoBag.bag.getChamberLocationName());
      febInfoBag.bag.setCcuAddress(febAccessInfoBag.bag.getCcuAddress());
      febInfoBag.bag.setChannel(febAccessInfoBag.bag.getI2cChannel());
      febInfoBag.bag.setAddress(febAccessInfoBag.bag.getFebAddress());
      febInfoBag.bag.setEndcap(barrelOrEndcap);
      febInfoBag.bag.setXdaqAppInstance(febAccessInfoBag.bag.getXdaqAppInstance());      
      
      std::string partitionstring = (std::string)(febInfoBag.bag.getFebLocalEtaPartition());
      if (barrelOrEndcap)
	{
	  if (partitionstring.find("D") != partitionstring.npos)
	    partition=3;
	  else if (partitionstring.find("C") != partitionstring.npos)
	    partition=2;
	  else if (partitionstring.find("B") != partitionstring.npos)
	    partition=1;
	  else
	    partition=0;
	}
      else
	{
	  if (partitionstring.find("C") != partitionstring.npos)
	    partition=1; // central
	  else if (partitionstring.find("F") != partitionstring.npos)
	    partition=2; // forward
	  else // backward
	    partition=0;
	}
    }
    ~Feb(){};
    
    // get functions
    int getXdaqAppInstance() const{
      return (int)(getFebInfoBag().bag.getXdaqAppInstance());
    }
    int getEtaPartition() const{
      return partition;
    }
    std::string getEtaPartitionName() const{
      return (std::string)(getFebInfoBag().bag.getFebLocalEtaPartition());
    }
    int getCcuAddress() const{
      return (int)(getFebInfoBag().bag.getCcuAddress());
    }
    int getI2cChannel() const{
      return (int)(getFebInfoBag().bag.getChannel());
    }
    int getFebAddress() const{
      return (int)(getFebInfoBag().bag.getAddress());
    }
    int getWheel() const{
      return wheel;
    }
    int getDisk(){
      return this->getWheel();
    }
    int getLayer() const{
      return layer;
    }
    std::string getLayerName() const{
      if (layer > -1 && layer <= 6)
	return rpcconfig::BarrelLayerName_[layer];
      else
	return "";
    }
    int getRing() const{
      return this->getLayer();
    }
    int getSector() const{
      return sector;
    }
    int getSubsector() const{
      return subsector;
    }
    bool isEndcap() const{
      return barrelOrEndcap;
    }
    bool isBarrel() const{
      return !barrelOrEndcap;
    }
    rpct::xdaqutils::XdaqDbServiceClient::BarrelOrEndcap boe(){
      return rpcconfig::BoeArr_[(int)barrelOrEndcap];
    }
    std::string getSubsectorName(){
      if (subsector > -1 && subsector <= 4)
	return rpcconfig::BarrelSubsectorName_[subsector];
      else
	return "";
    }
    std::string getName(){
      return (std::string)(getFebInfoBag().bag.getChamberLocationName());
    }
    
    // for write request
    FebValuesBag getFebValuesBag(FebFloatValues febFloatValues){
      FebValuesBag febValuesBag;
      febValuesBag.bag.getFeb() = febInfoBag;
      febValuesBag.bag.getValues() = febFloatValues;
      return febValuesBag;
    }
    void fillFebFloatValues(const float (&values)[8], int length, FebFloatValues &febFloatValues){
      for (int i=0;i<length;i++)
	febFloatValues.push_back(values[i]);
    }
    FebValuesBag getFebValuesBag(const float (&values)[8], int length){
      FebValuesBag febValuesBag;
      febValuesBag.bag.getFeb() = febInfoBag;
      fillFebFloatValues(values, length, febValuesBag.bag.getValues());
      return febValuesBag;
    }
    // for read request
    FebInfoBag getFebInfoBag() const{
      return febInfoBag;
    }
  };
  bool operator<(const rpcconfig::Feb febOne, const rpcconfig::Feb febTwo) {
    return (
	    febOne.isEndcap()      < febTwo.isEndcap()      &&
	    febOne.getWheel()      < febTwo.getWheel()      &&
	    febOne.getLayer()      < febTwo.getLayer()      &&
	    febOne.getSector()     < febTwo.getSector()     &&
	    febOne.getSubsector()  < febTwo.getSubsector()  &&
	    febOne.getCcuAddress() < febTwo.getCcuAddress() && // CB
	    febOne.getI2cChannel() < febTwo.getI2cChannel() && // I2C connector in CB
	    febOne.getFebAddress() < febTwo.getFebAddress()    // Feb Address after distribution board
	    );
  }
  bool operator==(const rpcconfig::Feb febOne, const rpcconfig::Feb febTwo) {
    return (
	    febOne.isEndcap()      == febTwo.isEndcap()      &&
	    febOne.getWheel()      == febTwo.getWheel()      &&
	    febOne.getLayer()      == febTwo.getLayer()      &&
	    febOne.getSector()     == febTwo.getSector()     &&
	    febOne.getSubsector()  == febTwo.getSubsector()  &&
	    febOne.getCcuAddress() == febTwo.getCcuAddress() &&
	    febOne.getI2cChannel() == febTwo.getI2cChannel() &&
	    febOne.getFebAddress() == febTwo.getFebAddress()
	    );
  }
  class TimedStatus{
  protected:
    time_t start_t, stop_t;
    bool ready;
  public:
    TimedStatus(){
      ready   = false;
      start_t = time(NULL);
      stop_t  = start_t;
    }
    ~TimedStatus(){}
    void start(){
      start_t = time(NULL);
      stop_t  = start_t;
      ready   = false;
    }
    void stop(){
      stop_t = time(NULL);
      ready  = true;
    }
    void setStatus(bool status){
      ready = status;
    }
    bool getStatus() const{
      return ready;
    }
    time_t getStartTime() const{
      return start_t;
    }
    time_t getEndTime() const{
      return stop_t;
    }
  };
}

#endif
