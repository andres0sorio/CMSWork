// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCPaC.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RBCPaC
//
// 2008-10-25 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RBCPaC::RBCPaC( const char * logic_type ) : PaC() {

  m_logtool = new LogicTool<RBCLogic>();
  m_logtype = std::string( logic_type );
 
}
//=============================================================================
// Destructor
//=============================================================================
RBCPaC::~RBCPaC() {
  
  if (m_logtool) {
    if ( m_logtool->endjob() )
      delete m_logtool;
  }
  
} 

//=============================================================================
bool RBCPaC::initialise() 
{
  
  bool status(true);
  
  status = m_logtool->initialise();
  if ( !status ) { 
    std::cout << "RBCPaC> Problem initialising LogicTool \n"; 
    return 0; };
  
  m_logic  = dynamic_cast<RBCLogic*> ( m_logtool->retrieve(m_logtype) );
  
  if ( ! m_logic ) { 
    std::cout << "RBCPaC> No logic found \n"; 
    return 0; };
  
  return 1;
  
}

bool RBCPaC::setlogic( const char * _logic )
{
  
  m_logic  = m_logtool->retrieve( std::string(_logic) );
  if ( ! m_logic ) return 0;
  return 1;
  
}


void RBCPaC::run( const RBCInput & _input , std::bitset<2> & _decision )
{
  
  m_logic->process( _input , _decision );
  m_layersignal[0] = m_logic->getlayersignal( 0 );
  m_layersignal[1] = m_logic->getlayersignal( 1 );
 
}
