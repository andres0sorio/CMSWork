// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/src/RBCBasicConfig.h"
#include "L1Trigger/RPCTechnicalTrigger/src/AccessConfigMySQL.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RBCBasicConfig
//
// 2008-10-31 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RBCBasicConfig::RBCBasicConfig( const char * _logic ) {
  
  m_rbcpac  = new RBCPaC( _logic );
  
#ifdef AOSORIO_T61
  m_rbcconf = dynamic_cast<RPCAccessConfig*>(new AccessConfigMySQL("configfile.txt"));
#endif

  
}
//=============================================================================
// Destructor
//=============================================================================
RBCBasicConfig::~RBCBasicConfig() {
  
  if ( m_rbcpac ) delete m_rbcpac;

}

//=============================================================================
bool RBCBasicConfig::initialise() 
{
  
  bool status(true);
  
  status = m_rbcpac->initialise();
  
  if ( !status ) { 
    std::cout << "RBCConfiguration> Problem initialising the Configuration\n"; 
    return 0; };

#ifdef AOSORIO_T61  
  status = m_rbcconf->read();

  if ( !status ) { 
    std::cout << "RBCConfiguration> Problem reading the Database \n"; 
    return 0; };
#endif
  
  return 1;
  
}

