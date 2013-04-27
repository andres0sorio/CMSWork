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

  Initialize();

}
//=============================================================================
// Destructor
//=============================================================================
Data::~Data() {
  
  m_in->close();
  delete m_in;
  
} 

//=============================================================================
void Data::Initialize()
{
  
  for(int i=0; i < 256; ++i) 
  {
    
    for(int j=0; j < 256; ++j) 
    {
      matrix[i][j] = -1;
    }
    
  }
      
}


void Data::Read()
{
 
  int x1 = 0;
  
  for(int i=0; i < 256; ++i) 
  {
    
    for(int j=0; j < 256; ++j) 
    {
      (*m_in) >> x1;
      matrix[i][j] = x1;
    }
    
  }
    
}

void Data::Show( int i )
{

  std::cout << i << ": ";
    
  for(int j=0; j < 256; ++j) 
  {
    std::cout << matrix[i][j] << " ";
  }
  
  std::cout << '\n';
  
}
