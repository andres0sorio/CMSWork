// $Id: $
#ifndef RBCPAC_H 
#define RBCPAC_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/src/LogicTool.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/PaC.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCLogic.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCInput.h"

#include <bitset>

/** @class RBCPaC RBCPaC.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-10-25
 */

class RBCPaC : public PaC {
public: 
  /// Standard constructor
  RBCPaC( ) : PaC() {}; 
  
  RBCPaC( const char * );
  
  virtual ~RBCPaC( ); ///< Destructor
  
  bool initialise();
  
  bool setlogic( const char * );
  
  void run( const RBCInput & , std::bitset<2> & );
  
  std::bitset<6> * getlayersignal(int _idx) { return m_layersignal[_idx]; };
  
protected:
  
private:
  
  
  RBCLogic * m_logic;
  std::string m_logtype;
  LogicTool<RBCLogic> * m_logtool;
  
  std::bitset<6> * m_layersignal[2];
  
};
#endif // RBCPAC_H
