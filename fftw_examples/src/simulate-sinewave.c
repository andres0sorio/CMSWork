// $Id: $
// Include files 

#include "CommonIncludes.h"
#include "TRandom3.h"
#include "TMath.h"

int main(int iargv, const char **argv) {
  
  double xmin(1.0);
  double xmax(100.0);
  double dx(0.);
  double x(0.);
  double y(0.);
    
  std::ofstream *m_out = new std::ofstream("simdata-sinewave.dat",ofstream::out);
  
  dx = (xmax - xmin) / 100.0;
  
  dx = 1.0;
    
  for(int i=0; i < 100; ++i) 
  {
    
    x  = xmin + dx*i;
    y  = TMath::Sin( x );
    
    if ( i < 10 ) std::cout << "x:  " << x
                            << '\t'
                            << "y:  " << y
                            << '\n';
    
    (*m_out) << x << '\t' << y << '\n';
    
  }
  
  m_out->close();
  
  delete m_out;
  
  return 1;
  
}
