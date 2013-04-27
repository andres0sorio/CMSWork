// $Id: $
// Include files 

#include <iterator>
#include <iostream>
#include <cstdlib>

//#include "LHAPDF/FortranWrappers.h"
//#ifdef FC_DUMMY_MAIN
//int FC_DUMMY_MAIN() { return 1; }
//#endif


// local
#include "d2sigmaCC_NC.h"

//-----------------------------------------------------------------------------
// Implementation file for class : d2sigmaCC_NC
//
// 2012-06-13 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

//=============================================================================
double dsigmaCC_dQdy::DoEval(const double * x) const{
  
  double xx = x[0];
  double Q = x[1];
  
  if( xx < 1.0E-6) LHAPDF::extrapolate(true);
  
  double xu =  LHAPDF::xfx(xx, Q, -2);
  double xd =  LHAPDF::xfx(xx, Q, -1);
  
  double val = (xu + xd ) / 2.0;
    
  //std::cout << "x=" << xx << ", Q=" << Q << ", f=0: " << val << std::endl;
   
  return val;
  
  
}

double dsigmaCC_dQdy::Validate(const double * x) const{

  double xx = x[0];
  double Q = x[1];
  int fv = (int)x[2];
    
  if( xx < 1.0E-6) LHAPDF::extrapolate(true);
  
  double val =  LHAPDF::xfx(xx, Q, fv);
  
  return val;
  
}

