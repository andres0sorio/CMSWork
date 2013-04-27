// $Id: $
#ifndef RPCPROCESSTESTSIGNAL_H 
#define RPCPROCESSTESTSIGNAL_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCInput.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RPCData.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/ProcessInputSignal.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <cmath>
#include <vector>
#include <map>

/** @class RPCProcessTestSignal RPCProcessTestSignal.h
 *  
 * 
 *
 *
 *
 *  @author Andres Osorio
 *  @date   2008-11-14
 */
class RPCProcessTestSignal : public ProcessInputSignal {
public: 
  /// Standard constructor
  RPCProcessTestSignal( ) : ProcessInputSignal()  { }; 
  
  RPCProcessTestSignal( const char * );
  
  virtual ~RPCProcessTestSignal( ); ///< Destructor
  
  int  next();
  
  void rewind();
  
  void showfirst();
  
  void retrievedata( std::map<int,RBCInput*> & );
  
  void reset();
  
  void mask() {};
  
  void force() {};
  
  
protected:
  
private:
  
  std::ifstream * m_in;
  
  RPCData * m_block;
  
  std::vector<RPCData*> m_vecdata;
    
};
#endif // RPCPROCESSTESTSIGNAL_H
