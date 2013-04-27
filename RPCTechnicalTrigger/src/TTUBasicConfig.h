// $Id: $
#ifndef INTERFACE_TTUBASICCONFIG_H 
#define INTERFACE_TTUBASICCONFIG_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/TTUConfiguration.h"

/** @class TTUBasicConfig TTUBasicConfig.h interface/RPCBasicConfig.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-10-29
 */
class TTUBasicConfig : public TTUConfiguration {
public: 
  /// Standard constructor
  TTUBasicConfig( ) { };

  TTUBasicConfig( const char * );
  
  virtual ~TTUBasicConfig( ); ///< Destructor

  bool initialise();
  
protected:

private:

};
#endif // INTERFACE_TTUBASICCONFIG_H
