//$Id: $
#ifndef RBCEMULATOR_H 
#define RBCEMULATOR_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/src/RBCId.h"
#include "L1Trigger/RPCTechnicalTrigger/src/LogicTool.h"
#include "L1Trigger/RPCTechnicalTrigger/src/RBCProcessTestSignal.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCInput.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCConfiguration.h"

/** @class RBCEmulator RBCEmulator.h
 *  
 *
 *  @author Andres Osorio, Flavio Loddo, Marcello Maggi
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-10
 */

class RBCEmulator {
public: 
  /// Standard constructor
  RBCEmulator( ) { }; 
  
  RBCEmulator( const char * ); 
  
  RBCEmulator( const char * , const char * ); 
  
  RBCEmulator( const char * , const char * , int, int *); 
  
  virtual ~RBCEmulator( ); ///< Destructor
  
  bool initialise();
  
  bool setlogic( const char * );
  
  void setid( int , int * );
  
  void emulate();

  void emulate( RBCInput * );
  
  std::bitset<6> * getlayersignal( int _idx ) { return m_layersignal[_idx];};
  
  void printinfo();
  
  void printlayerinfo();

  RBCId          * m_rbcinfo;
  
protected:
  
private:
  
  RBCProcessTestSignal * m_signal;
  
  RBCConfiguration     * m_rbcconf;
  
  RBCInput       * m_input;
    
  std::bitset<6> * m_layersignal[2];
  
  //...
  
  int m_bx;
  
  std::string m_logtype;
  
};
#endif // RBCEMULATOR_H
