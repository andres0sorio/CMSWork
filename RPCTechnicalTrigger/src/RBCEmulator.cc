// $Id: $
// Include files 

// local
#include "RBCEmulator.h"
#include "RBCBasicConfig.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RBCEmulator
//
// 2008-10-10 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RBCEmulator::RBCEmulator( const char * logic_type ) {
  
  m_signal  = NULL;
  m_logtype = std::string( logic_type );
  m_input   = new RBCInput();
  m_rbcinfo = new RBCId();
  m_rbcconf = dynamic_cast<RBCConfiguration*> (new RBCBasicConfig(logic_type));
  
}

RBCEmulator::RBCEmulator( const char * f_name  , const char * logic_type ) {
  
  m_signal  = new RBCProcessTestSignal( f_name );
  m_logtype = std::string( logic_type );
  m_input   = new RBCInput();
  m_rbcinfo = new RBCId();
  m_rbcconf = dynamic_cast<RBCConfiguration*> (new RBCBasicConfig(logic_type));
  
}

//=============================================================================
// Destructor
//=============================================================================
RBCEmulator::~RBCEmulator() {
  
  if (m_signal)  delete m_signal;
  if (m_rbcconf) delete m_rbcconf;
  if (m_rbcinfo) delete m_rbcinfo;
  if (m_input)   delete m_input;
  
} 

//=============================================================================
bool RBCEmulator::initialise() 
{
  
  bool status(true);
  
  status = m_rbcconf->initialise();
  
  if ( !status ) { 
    std::cout << "RBCEmulator> Problem initialising the Configuration \n"; 
    return 0; };

  std::cout << "RBCEmulator> Initialising succeded \n";
  
  return 1;
  
}

bool RBCEmulator::setlogic( const char * _logic )
{
  
  bool status(true);
  
  status = m_rbcconf->m_rbcpac->setlogic( _logic );
  if ( ! status ) return 0;
  
  return 1;
  
}

void RBCEmulator::setid( int _wh, int * _sec)
{
  m_rbcinfo->setid ( _wh, _sec);
}

void RBCEmulator::emulate() 
{
  
  std::cout << "RBCEmulator> starting test emulation" << std::endl;
  
  std::bitset<2> _decision;
  
  while ( m_signal->next() ) 
  {
    (*m_input) =  (* m_signal->getdata() );
    
    m_rbcconf->m_rbcpac->run( (*m_input) , _decision );
    
    m_layersignal[0] = m_rbcconf->m_rbcpac->getlayersignal( 0 );
    m_layersignal[1] = m_rbcconf->m_rbcpac->getlayersignal( 1 );
    
    printlayerinfo();
    
    std::cout << _decision[0] << " " << _decision[1] << std::endl;
    
  }
  
  std::cout << "RBCEmulator> end test emulation" << std::endl;
  
}

void RBCEmulator::emulate( RBCInput * _in )
{
  
  std::cout << "RBCEmulator> starting emulation" << std::endl;
  
  std::bitset<2> _decision;
  
  (*m_input) =  (*_in);
  
  m_rbcconf->m_rbcpac->run( (*m_input) , _decision );
  
  m_layersignal[0] = m_rbcconf->m_rbcpac->getlayersignal( 0 );
  m_layersignal[1] = m_rbcconf->m_rbcpac->getlayersignal( 1 );
  
  printlayerinfo();
  
  std::cout << _decision[0] << " " << _decision[1] << std::endl;
  
  std::cout << "RBCEmulator> end emulation" << std::endl;
  
}

void RBCEmulator::printinfo()
{
  std::cout << "RBC --> \n";
  m_rbcinfo->printinfo();

}

void RBCEmulator::printlayerinfo()
{
  std::cout << "Sector summary by layer: \n";
  for(int i=0; i < 6; ++i)
    std::cout << (*m_layersignal[0])[i] << '\t' 
              << (*m_layersignal[1])[i] << '\n';  
  
}
