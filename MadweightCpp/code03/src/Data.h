// $Id: $
#ifndef DATA_H 
#define DATA_H 1

// Include files
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <math.h>

/** @class Data Data.h 3.7/Data.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-08-08
 */

class MadWeightResults {
public:
  
  MadWeightResults() {}
  
  virtual ~MadWeightResults( ) { 
    m_weights.clear(); 
    m_weightsErr.clear(); 
  }
  
  int m_ID;
  std::vector<double> m_weights;
  std::vector<double> m_weightsErr;
  
};

class Data {
public: 
  
  /// Standard constructor
  Data( ) { }; 
  Data(const char*);
  
  virtual ~Data( ); ///< Destructor
  
  void Read();
  void Show();
  
  std::vector<MadWeightResults*> m_Results;

protected:
  
private:
  
  std::ifstream * m_in;
  
};
#endif // DATA_H

