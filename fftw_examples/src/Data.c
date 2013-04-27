// $Id: $
// Include files 



// local
#include "Data.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Data
//
// 2008-04-29 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Data::Data( const char * f_name ) {

  m_in = new std::ifstream();
  
  m_in->open(f_name);
  
  if(!m_in->is_open()) {
    std::cout << "Data> cannot open file" << std::endl;
  } else { 
    std::cout << "Data> file is now open" << std::endl;
  }
  
  
}
//=============================================================================
// Destructor
//=============================================================================
Data::~Data() {
  
  m_in->close();
  delete m_in;
  
} 

//=============================================================================
int Data::next()
{
  if ( m_in->fail()) return 0;
  
  (*m_in) >> m_x1 >> m_x2;
  
  if ( m_in->eof() ) return 0;
  
  return 1;
}

void Data::showfirst()
{
  
  rewind();
  
  (*m_in) >> m_x1 >> m_x2;
  std::cout << m_x1 << '\t' << m_x2 << '\n';
  
  rewind();
  
    
}
