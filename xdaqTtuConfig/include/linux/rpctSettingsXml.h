// $Id: $
#ifndef ADVANCED_RPCTSETTINGSXML_H 
#define ADVANCED_RPCTSETTINGSXML_H 1

// Include files

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>

/** @class rpctSettingsXml rpctSettingsXml.h Advanced/rpctSettingsXml.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-05-11
 */

XERCES_CPP_NAMESPACE_USE

class Register {
public:
  Register(){};
  ~Register(){};
  
  std::string regName;
  std::string regValue;
  
};


class TabRegister {
public:  
  TabRegister(){};
  ~TabRegister(){};
  
  std::string regName;
  std::string size;
  
  class ValuesTab {
  public:
    ValuesTab(){};
    ~ValuesTab(){};
    std::string index;
    std::string regValue;
  };
  
  std::vector<ValuesTab> v_valuesTab;
    
};  

class Device {
public:
  
  Device(){};
  ~Device(){};
  
  std::string id;
  std::string name;

  std::vector<Register> v_register;
  std::vector<TabRegister> v_tabregister;
  
};

  
class Board {
public:

  Board(){};
  ~Board(){};
  
  std::string id;
  std::string name;
  
  std::vector<Device> v_device;

  friend std::ostream& operator << (std::ostream &, Board  &);
  
    
};

class WheelConfig {
 public:
  
  WheelConfig() {};
  ~WheelConfig() {}
  
  int m_wheelId;
  int m_ttuAssoc;
  
  std::vector<Register> v_Optoregister;
  std::vector<TabRegister> v_Optotabregister;
  
  std::vector<Register> v_Triggregister;
  std::vector<TabRegister> v_Triggtabregister;
  
  
 private:
  
  
  
};

#endif // ADVANCED_RPCTSETTINGSXML_H
