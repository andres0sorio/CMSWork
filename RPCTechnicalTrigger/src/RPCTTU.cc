// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/src/RPCTTU.h"
#include "L1Trigger/RPCTechnicalTrigger/src/TTUBasicConfig.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RPCTTU
//
// 2008-10-15 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RPCTTU::RPCTTU( int _id, const char * rbclogic_type, const char * ttulogic_type, int _mxw  ) 
{
  
  m_id        = _id;
  m_maxwheels = _mxw;
  int tmp[5]  = {2, 1, 0, -1, -2};
  
  for( int k=0; k < 5; ++k) m_wheelids[k]=tmp[k];
  
  for( int k=0; k < m_maxwheels; ++k ) 
    m_Wheels[k] = new RPCWheel( m_wheelids[(_id*2)+(k-2)], rbclogic_type );
  
  m_ttuin[0] = new TTUInput();
  m_ttuin[1] = new TTUInput();

  //m_ttupac   = new TTUPaC( ttulogic_type );
  m_ttuconf   = dynamic_cast<TTUConfiguration*> (new TTUBasicConfig (ttulogic_type));
  
}

RPCTTU::RPCTTU( int _id, const char * f_name, const char * rbclogic_type, 
                const char * ttulogic_type, int _mxw  ) 
{
  
  m_id        = _id;
  m_maxwheels = _mxw;
  int tmp[5]  = {2, 1, 0, -1, -2};
  
  for( int k=0; k < 5; ++k) m_wheelids[k]=tmp[k];
  
  for( int k=0; k < m_maxwheels; ++k ) 
    m_Wheels[k] = new RPCWheel( m_wheelids[(_id*2)+(k-2)], f_name, rbclogic_type );
  
  m_ttuin[0] = new TTUInput();
  m_ttuin[1] = new TTUInput();
  
  //m_ttupac   = new TTUPaC( ttulogic_type );
  m_ttuconf   = dynamic_cast<TTUConfiguration*> (new TTUBasicConfig (ttulogic_type));
  
}

//=============================================================================
// Destructor
//=============================================================================
RPCTTU::~RPCTTU() {
  
  //if ( m_ttupac ) delete m_ttupac;

  if ( m_ttuconf ) delete m_ttuconf;
  
  if ( m_ttuin  ) 
    for (int k=0; k < 2; ++k) 
      delete m_ttuin[k];
  
  if ( m_Wheels ) 
    for (int k=0; k  < m_maxwheels; ++k )
      delete m_Wheels[k];
  
} 

//=============================================================================
bool RPCTTU::initialise()
{
  
  bool status(false);
  for( int k=0; k < m_maxwheels; ++k)
    status = m_Wheels[k]->initialise( );
  return status;
  
}

void RPCTTU::emulate() 
{
  
  //... only for testing
  for( int k=0; k < m_maxwheels; ++k ) 
    m_Wheels[k]->emulate();
  
}

void RPCTTU::process( const std::map<int,RBCInput*> & _data ) 
{
  
  for( int k=0; k < m_maxwheels; ++k )
  {
    
    m_Wheels[k]->process( _data );
    
    //... m_Wheels[k]->retrieveWheelMap( (*m_ttuin[k]) );
    //... execute here the Tracking Algorithm (get all output) 
    //... and produce a Wheel level trigger
    
  }
  
}

//.................................................................

void RPCTTU::printinfo() 
{
  
  std::cout << "RPCTTU: " << m_id << '\n';
  for( int k=0; k < m_maxwheels; ++k ) 
    m_Wheels[k]->printinfo();
  
}
