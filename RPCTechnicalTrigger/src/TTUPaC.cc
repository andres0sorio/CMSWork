// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/interface/TTUPaC.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TTUPaC
//
// 2008-10-25 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TTUPaC::TTUPaC( const char * logic_type ) : PaC () {

  m_logtool = new LogicTool<TTULogic>();
  m_logtype = std::string( logic_type );
  
}
//=============================================================================
// Destructor
//=============================================================================
TTUPaC::~TTUPaC() {
  
  if (m_logtool) {
    if ( m_logtool->endjob() )
      delete m_logtool;
  }

} 

//=============================================================================
