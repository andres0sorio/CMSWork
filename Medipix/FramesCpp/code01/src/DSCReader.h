// $Id: $
#ifndef DSCREADER_H 
#define DSCREADER_H 1

// Include files
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <stdio.h>
#include <math.h>

/** @class DSCReader DSCReader.h
 *  
 *
 *  @author Andres Osorio/Iván Caicedo
 *  @date   2012-03
 */

//Initializes the DSCReader Class
class DSCReader {
public: 
  //Constructor of the DSCReader Class
  DSCReader( ) { }; 
  DSCReader(const char*);
  //Destructor of the DSCReader Class
  virtual ~DSCReader( ); 
  //Extracts the integer (1) and decimal (2) parts from the start time
  void Read();
  //Returns the integer part of the start time
  double GetTimeBase( );
  //Returns the decimal part of the start time in nanoseconds
  double GetTimeNs( );
    
protected:
  
private:

  double m_timeBase;
  double m_timeNs;
  std::ifstream * m_in;

};
#endif // DSCREADER_H
