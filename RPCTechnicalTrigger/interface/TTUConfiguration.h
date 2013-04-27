// $Id: $
#ifndef INTERFACE_TTUCONFIGURATION_H 
#define INTERFACE_TTUCONFIGURATION_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/TTUPaC.h"

/** @class TTUConfiguration TTUConfiguration.h interface/TTUConfiguration.h
 *  
 *
 *  Configuration Interface: Deals with configuration of TTU hardware
 * 
 *
 *  @author Andres Osorio
 *  @date   2008-10-29
 */
class TTUConfiguration {
public: 

  virtual bool initialise()=0;
  
  TTUPaC * m_ttupac;
  
protected:

private:

};
#endif // INTERFACE_TTUCONFIGURATION_H
