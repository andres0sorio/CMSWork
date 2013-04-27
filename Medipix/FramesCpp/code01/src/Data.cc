// $Id: $
// Include files 
// local
#include "Data.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Data
//
// 2012-03  : Andres Osorio/Iván Caicedo
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Data::Data( const char * f_name ) {
  
  //Creates a stream that contains the name of the data source file
  m_in = new std::ifstream();
  //Opens the file and confirms if it can be used
  m_in->open(f_name);
  if (!m_in) std::cout << "Data> could not open input file" << std::endl;
  
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

//Creates a 256*256 matrix full of zeros (This matrix will be filled with the counts from the source files afterwards)
void Data::Initialize()
{
  
  for(int i=0; i < 256; ++i) 
  {
    
    for(int j=0; j < 256; ++j) 
    {
      matrix[i][j] = 0;
    }
    
  }
      
}



//Sets the time stamp from the dsc files for this matrix
void Data::SetTimestamp( double input )
{
  m_timestamp = input;   
}



//Fills the 256*256 matrix with the counts from the data file. It converts from a "Two column format" (Number of pixel-Counts)
//to a "Matrix format" (X,Y and counts)
void Data::Read()
{
  int col1;
  int col2;
  double time;
  
  while(1) {
    
    if( !m_in->good() ) break;

    (*m_in) >> col1 >> col2;

    if( m_in->eof() ) break;
    
    col1 += 1;
    
    int x = col1 % 256;
    int y = col1 / 256;
        
    if ( x > 0 ) y+=1;
    else x = 256;
    
    time = Process( col2 );
    
    matrix[y-1][x-1] = int(time);
    
  } 
}



double Data::Process( int value ) 
{
  return (m_timestamp + value*100.0);   
}



//Shows the matrix
void Data::Show()
{

  for(int i=0; i < 256; ++i ) {
    
    for(int j=0; j < 256; ++j) 
    {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << '\n';
  }
  
}
