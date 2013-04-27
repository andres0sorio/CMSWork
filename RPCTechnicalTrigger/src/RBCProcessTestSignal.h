// $Id: $
#ifndef RBCPROCESSTESTSIGNAL_H 
#define RBCPROCESSTESTSIGNAL_H 1


// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCInput.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/ProcessInputSignal.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <cmath>

/** @class RBCProcessTestSignal RBCProcessTestSignal.h
 *  
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-10
 */
class RBCProcessTestSignal : public ProcessInputSignal {
public: 
  /// Standard constructor
  RBCProcessTestSignal( ) { }; 
  
  RBCProcessTestSignal( const char * ); 
  
  virtual ~RBCProcessTestSignal( ); ///< Destructor
  
  int  next();
  
  void mask() {};
  
  void force() {};
  
  void rewind();
  
  void showfirst();
  
  RBCInput * getdata() { return m_input; };
  
protected:
  
private:
  
  std::ifstream * m_in;
  
  RBCInput * m_input;
  
};
#endif // RBCPROCESSTESTSIGNAL_H
