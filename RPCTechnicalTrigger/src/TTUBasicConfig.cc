// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/src/TTUBasicConfig.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TTUBasicConfig
//
// 2008-10-31 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TTUBasicConfig::TTUBasicConfig( const char * _logic  ) {

  m_ttupac = new TTUPaC( _logic );
  
}
//=============================================================================
// Destructor
//=============================================================================
TTUBasicConfig::~TTUBasicConfig() {

  if (m_ttupac) delete m_ttupac;
  
} 

//=============================================================================
bool TTUBasicConfig::initialise()
{
  


  return 1;
  
}
