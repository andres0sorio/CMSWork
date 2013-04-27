// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/src/Dimension.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Dimension
//
// 2008-10-26 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Dimension::Dimension( const char *_title, long int _key ) {
  
  m_pkey = _key;
  m_name = std::string(_title);
  m_oss = new std::ostringstream(std::ostringstream::app);
}

