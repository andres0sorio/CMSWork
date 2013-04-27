// $Id: $
// Include files 


// local
#include "TrigRates.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TrigRates
//
// 2010-02-28 : Andres Osorio
//-----------------------------------------------------------------------------

std::istream& operator>>(std::istream &istr, TrigRates &rhs) {

  int rate;
  
  for( int k=0; k < 65; ++k) 
  {
    istr >> rate;
    
    //if ( rate < 0 ) 
    // {
    //  rhs.hasStop = true;
    //  break;
    // }
    ///else rhs.hasStop = false;

    rhs.rates.push_back( std::abs(rate) );
  
  }
  
  return istr;

}
