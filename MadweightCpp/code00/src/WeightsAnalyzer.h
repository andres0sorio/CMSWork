// $Id: $
#ifndef WEIGHTSANALYZER_H 
#define WEIGHTSANALYZER_H 1

// Include files

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <map>


/** @class WeightsAnalyzer WeightsAnalyzer.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-09-14
 */

struct EventWeights {

  // io functions
  friend std::ifstream& operator>>(std::ifstream &istr,  EventWeights &rhs);
  //friend std::ostream& operator<<(std::ostream &ostr, EventWeights &rhs);
  
  EventWeights ( ) { };
  virtual ~EventWeights( ) { m_perm_weight.clear(); m_perm_weightErr.clear(); };
  
  int m_event;
  std::map<int, double> m_perm_weight;
  std::map<int, double> m_perm_weightErr;
  
};

class WeightsAnalyzer {
public: 
  /// Standard constructor
  WeightsAnalyzer( ) { }; 
  
  WeightsAnalyzer(const char * ); 
  
  virtual ~WeightsAnalyzer( ); ///< Destructor

  int Next();
  
  void Reset() { delete m_eventweight; };
  
  EventWeights * m_eventweight;
  
protected:
  
private:
  
  
  std::ifstream * m_in;
  
  
  
};
#endif // WEIGHTSANALYZER_H
