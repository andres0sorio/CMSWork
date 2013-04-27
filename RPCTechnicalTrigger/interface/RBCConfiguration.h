// $Id: $
#ifndef INTERFACE_RBCCONFIGURATION_H 
#define INTERFACE_RBCCONFIGURATION_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCPaC.h"

/** @class RBCConfiguration RBCConfiguration.h interface/RBCConfiguration.h
 *  
 *
 *  Configuration Interface: Deals with configuration of RBC hardware
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-10-29
 */
class RBCConfiguration {
public: 
  
  virtual bool initialise()=0;
  
  RBCPaC * m_rbcpac;

protected:

private:

};
#endif // INTERFACE_RBCCONFIGURATION_H
