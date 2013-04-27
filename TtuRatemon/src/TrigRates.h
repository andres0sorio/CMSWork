// $Id: $
#ifndef TRIGRATES_H 
#define TRIGRATES_H 1

// Include files
#include "CommonIncludes.h"
#include <iostream>
#include <vector>

/** @class TrigRates TrigRates.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-02-28
 */

class TrigRates {
public: 
  /// Standard constructor
  TrigRates( ){ hasStop = false; };
  
  virtual ~TrigRates( ) { rates.clear(); }; ///< Destructor

  std::vector<int> rates;
  friend std::istream& operator>>(std::istream &istr, TrigRates &rhs);
  //friend std::istream& operator>>(std::istream &istr, TrigRates &rhs);
  
  bool hasStop;
  
protected:
  
private:

};
#endif // TRIGRATES_H
