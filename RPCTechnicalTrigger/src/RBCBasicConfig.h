// $Id: $
#ifndef INTERFACE_RBCBASICCONFIG_H 
#define INTERFACE_RBCBASICCONFIG_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/RPCAccessConfig.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCConfiguration.h" 


/** @class RBCBasicConfig RBCBasicConfig.h interface/RBCBasicConfig.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-10-29
 */
class RBCBasicConfig : public RBCConfiguration {
public: 
  /// Standard constructor
  RBCBasicConfig( ) {}; 
  
  RBCBasicConfig( const char *); 
  
  virtual ~RBCBasicConfig( ); ///< Destructor
  
  bool initialise();
  
protected:
  
private:

  
  RPCAccessConfig * m_rbcconf;
  

};
#endif // INTERFACE_RBCBASICCONFIG_H
