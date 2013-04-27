// $Id: $
// Include files 


// local
#include "L1Trigger/RPCTechnicalTrigger/src/RPCProcessTestSignal.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RPCProcessTestSignal
//
// 2008-11-17 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RPCProcessTestSignal::RPCProcessTestSignal( const char * f_name ) 
  : ProcessInputSignal() {
  
  m_in = new std::ifstream();
  m_in->open(f_name);
  
  if(!m_in->is_open()) {
    std::cout << "RPCProcessTestSignal> cannot open file" << std::endl;
  } else { 
    std::cout << "RPCProcessTestSignal> file is now open" << std::endl;
  }
  
}
//=============================================================================
// Destructor
//=============================================================================
RPCProcessTestSignal::~RPCProcessTestSignal() {} 

//=============================================================================
int RPCProcessTestSignal::next()
{
  
  
  reset();
  
  if ( m_in->fail() ) return 0;
  
  for(int j=0; j < 5; ++j) {
    
    m_block = new RPCData();
    (*m_in) >> (*m_block);
    m_vecdata.push_back( m_block );
  }
  
  if ( m_in->eof() ) return 0;
  return 1;
  
}

void RPCProcessTestSignal::showfirst() 
{
  rewind();
  std::vector<RPCData*>::iterator itr;
  for(itr=m_vecdata.begin();itr!=m_vecdata.end();++itr)
    std::cout << (*(*itr));
  rewind();
  
}

void RPCProcessTestSignal::rewind() 
{ 
  m_in->clear();
  m_in->seekg(0,std::ios::beg); 
}

void RPCProcessTestSignal::reset()
{
  
  std::vector<RPCData*>::iterator itr;
  for(itr=m_vecdata.begin();itr!=m_vecdata.end();++itr)
    delete *itr;
  m_vecdata.clear();
  
}

void RPCProcessTestSignal::retrievedata( std::map<int,RBCInput*> &_data) 
{
  
  int _code(0);
  
  std::vector<RPCData*>::iterator itr;
  
  for(itr = m_vecdata.begin(); itr != m_vecdata.end(); ++itr)
  {
    _code = 10000*(*itr)->m_wheel
      + 100*(*itr)->m_sec1
      + 1*(*itr)->m_sec2;
    RBCInput * _signal = (*itr)->m_orsignals;
    _data.insert( std::make_pair( _code , _signal) );
    
  }
  
  
}

