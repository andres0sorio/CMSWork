// $Id: $
#ifndef LINUX_RBCCONTROLQUICKSYNC_H 
#define LINUX_RBCCONTROLQUICKSYNC_H 1

// Include files
#include "CommonIncludes.h"
#include <bitset>

//...From xdaq/cgicc

#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include <cgicc/HTMLClasses.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLElement.h>

//... From XDAQ
#include "xdaq/WebApplication.h"
#include "xdata/UnsignedLong.h"

/** @class RbcControlQuickSync RbcControlQuickSync.h linux/RbcControlQuickSync.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-02-24
 */

class RbcControlQuickSync {
  
 public: 
  
  RbcControlQuickSync() {};
  
  RbcControlQuickSync( const std::map<std::string, int> & );
  
  void Default(xgi::Input * in, xgi::Output * out, const std::string & );
  
  int  IntFromBool( bool selRegister[8] );
  
  bool BoolFromInt( int integer, int i  );
  
  int setRegisterMap( const char * );
  
  int readSectorMasks( const char * );

  bool isSectorInTower( int , const std::string & );

  int m_wheel;
  
  bool m_isDone;
  bool m_sentTestCtrl;

  std::vector<int> m_wheelid;
  std::vector<int> m_sectorid;
  std::map<int,std::string> m_sectors;
  std::map<std::string, int> m_RbcInstances;
  std::map<std::string, int> m_RegisterAddressFromName;
  
  std::map<int, std::bitset<6> > m_RbcMasks; 

  std::map<int, std::string> m_towerAssociation;
  
 protected:
  
private:
    
  std::ifstream * m_in;
    
};
#endif // LINUX_RBCCONTROLQUICKSYNC_H
