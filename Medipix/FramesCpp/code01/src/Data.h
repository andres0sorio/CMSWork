// $Id: $
#ifndef DATA_H 
#define DATA_H 1
// Include files
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <cmath>

/** @class Data Data.h 3.7/Data.h
 *  
 *
 *  @author Andres Osorio/Iván Caicedo
 *  @date   2012-03
 */

//Initializes the Data Class
class Data {
public: 
  //Constructor of the Data Class
  Data( ) { }; 
  Data(const char*);
  //Destructor of the Data Class
  virtual ~Data( );

  void Initialize();
  //Fills the 256*256 matrix with the counts from the data file. It converts from a "Two column format" (Number of pixel-Counts)
//to a "Matrix format" (X,Y and counts)
  void Read();
  //Shows the matrix
  void Show( );
  //Sets the time stamp from the dsc files for this matrix
  double Process( int );
  void SetTimestamp( double );
  
  int matrix[256][256];
  
protected:
  
private:
  
  //Variable of the timestamp, extracted from the dsc files
  double m_timestamp;
  std::ifstream * m_in;
  
};
#endif // DATA_H

