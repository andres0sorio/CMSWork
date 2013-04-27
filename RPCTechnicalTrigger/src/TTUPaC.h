// $Id: $
#ifndef TTUPAC_H 
#define TTUPAC_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/PaC.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/TTULogic.h"
#include "L1Trigger/RPCTechnicalTrigger/src/LogicTool.h"

/** @class TTUPaC TTUPaC.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-10-25
 */
class TTUPaC : public PaC {
public: 
  /// Standard constructor
  TTUPaC( ) : PaC() {};
  
  TTUPaC( const char * );
  
  virtual ~TTUPaC( ); ///< Destructor
  
protected:
  
private:
  
  std::string m_logtype;
  
  TTULogic             * m_logic;
  LogicTool<TTULogic>  * m_logtool;
  
};
#endif // TTUPAC_H
