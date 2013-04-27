// $Id: $
// Include files 

// local
#include "L1Trigger/RPCTechnicalTrigger/interface/RBCInput.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RBCInput
//
// 2008-10-10 : Andres Osorio
//-----------------------------------------------------------------------------

std::istream& operator>>(std::istream &istr , RBCInput & rhs) {
  
  int _ks=0;
  
  for(int i=0 ; i < 30; ++i) { 
    istr >> rhs.input[i];
    if ( i < 15 ) _ks = 0;
    else _ks = 1;
    rhs.input_sec[_ks].set(i-(15*_ks), rhs.input[i]);
  }
  return istr;
}

std::ostream& operator<<(std::ostream &ostr , RBCInput & rhs) {
  
  for(int i=0; i < 15; ++i) ostr << rhs.input_sec[0][i];
  ostr << '\t';
  for(int i=0; i < 15; ++i) ostr << rhs.input_sec[1][i];
  ostr << '\n';
  
  return ostr;
  
}

void RBCInput::printinfo() 
{
  std::cout << "RBCInput: " << (*this);
}
