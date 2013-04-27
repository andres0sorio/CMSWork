// $Id: $
// Include files
// local
#include "DSCReader.h"

//-----------------------------------------------------------------------------
// Implementation file for class : DSCReader
//
// 2012-03 : Andres Osorio/Iván Caicedo
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
DSCReader::DSCReader( const char * f_name ) {
  
  //Creates a stream that contains the name of the dsc source file
  m_in = new std::ifstream();
  //Opens the dsc file and confirms if it can be used
  m_in->open(f_name);
  if (!m_in) std::cout << "DSCReader> could not open input file" << std::endl;
   
}
//=============================================================================
// Destructor
//=============================================================================
DSCReader::~DSCReader() {
  
  m_in->close();
  delete m_in;
  
} 

//=============================================================================

//Reads the dsc files and extracts the information about the acquisition start time of the detector
void DSCReader::Read() 
{
  
  char info[256];
  //Gets the value of the start time of the acquisition
  //Note: The maximum value of i is the number of the line at the dsc file where the start time is located. It varies depending on
  //the format.
  for(int i=1; i < 54; ++i ) {
    (*m_in).getline( info , 256 );
  }

  std::string time;
  
  (*m_in ) >> time;
  int pos = time.find(".");
  
  //Extracts the integer (1) and decimal (2) parts from the start time
  std::string part1 = time.substr(0,pos);
  std::string part2 = time.substr(pos+1,time.size());
  m_timeBase = atof( part1.c_str() );
  m_timeNs = atof( part2.c_str() ) * 1000;
}



//Returns the integer part of the start time
double DSCReader::GetTimeBase( )
{

  return m_timeBase;
  
}



//Returns the decimal part of the start time in nanoseconds
double DSCReader::GetTimeNs( ) 
{
  
  return m_timeNs;
    
}
