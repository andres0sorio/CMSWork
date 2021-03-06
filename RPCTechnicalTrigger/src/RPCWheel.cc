// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/src/RPCWheel.h"


//-----------------------------------------------------------------------------
// Implementation file for class : RPCWheel
//
// 2008-10-15 : Andres Osorio
//-----------------------------------------------------------------------------
void print_wheel (const TTUInput & _wmap )
{
  for( int i=0; i < 12; ++i) std::cout << '\t' << (i+1);
  std::cout << std::endl;
  for( int k=5; k >= 0; --k )
  {
    std::cout << (k+1) << '\t';
    for( int j=0; j < 12; ++j)
      std::cout << _wmap.input_sec[j][k] << '\t';
    std::cout << std::endl;
  }
  
}
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RPCWheel::RPCWheel( int _wid, const char * logic_type) {
  
  m_id = _wid; 
  int _bisector[2];
  
  for( int k=0; k < 6; ++k )
  {
    _bisector[0]= (k*2)+1;
    _bisector[1]= (k*2)+2;
    m_RBCE[k] = new RBCEmulator( logic_type ); 
    m_RBCE[k]->setid( _wid, _bisector );
  }
  
}

RPCWheel::RPCWheel( int _wid, const char * f_name, const char * logic_type) {
  
  m_id = _wid; 
  int _bisector[2];
  
  for( int k=0; k < 6; ++k )
  {
    _bisector[0]= (k*2)+1;
    _bisector[1]= (k*2)+2;
    m_RBCE[k] = new RBCEmulator( f_name, logic_type ); 
    m_RBCE[k]->setid( _wid, _bisector );
  }
  
}

//=============================================================================
// Destructor
//=============================================================================
RPCWheel::~RPCWheel() {
  
  //destroy all rbc objects associated
  if ( m_RBCE )
    for( int k=0; k < 6; ++k ) delete m_RBCE[k];
  
} 

//=============================================================================
bool RPCWheel::initialise()
{
  
  bool status(false);
  for( int k=0; k < 6; ++k )
    status = m_RBCE[k]->initialise();
  return status;
  
}

void RPCWheel::emulate() 
{
  //This is a test emulation
  for( int k=0; k < 6; ++k )
  {
    m_RBCE[k]->emulate();
  }
}

void RPCWheel::process( const std::map<int,RBCInput*> & _data )
{
  
  std::map<int,RBCInput*>::const_iterator itr;
  
  for(int k=0; k < 6; ++k) {
    
    int _pos = m_RBCE[k]->m_rbcinfo->wheel()*10000 
      + m_RBCE[k]->m_rbcinfo->sector()[0]*100
      + m_RBCE[k]->m_rbcinfo->sector()[1];
    
    itr = _data.find( _pos );
    
    if ( itr != _data.end() )  {
      m_RBCE[k]->emulate( ( itr->second ) );
    } else {
      // handle error
    }
    
  }
  
}

//..............................................................

void RPCWheel::createWheelMap()
{
  
  std::bitset<6> * m_layersignal;
  
  for( int k=0; k < 6; ++k )
  {
    m_layersignal       = m_RBCE[k]->getlayersignal( 0 );
    m_wheelmap[k*2]     = m_layersignal;
    m_layersignal       = m_RBCE[k]->getlayersignal( 1 );
    m_wheelmap[(k*2)+1] = m_layersignal;
  }
  
}

void RPCWheel::retrieveWheelMap( TTUInput & _output) 
{
  
  _output.reset();
  
  for(int i=0; i < 12; ++i ) {
    for( int j=0; j < 6; ++j ) 
    {
      _output.input_sec[i].set(j, (*m_wheelmap[i])[j]);
    }
  }
  
  print_wheel( _output );
  
}

//..............................................................

void RPCWheel::printinfo() 
{
  
  std::cout << "Wheel -> " << m_id << '\n';
  for( int k=0; k < 6; ++k )
  {
    m_RBCE[k]->printinfo();
  }
  
}
