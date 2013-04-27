// $Id: $
// Include files 

#include "CommonIncludes.h"
#include "TRandom3.h"

int main(int iargv, const char **argv) {
  
  double xmin(0.0);
  double xmax(100.0);
  double dx(0.);
  double dt1(0.);
  double dt2(0.);
  double x(0.);
  double y(0.);
  double y0=5.0;
  
  TRandom3 *r1 = new TRandom3(0);
  
  std::ofstream *m_out = new std::ofstream("simdata.dat",ofstream::out);
  
  dx = (xmax - xmin) / 100.0;
  
  for(int i=0; i < 100; ++i) 
  {
    
    x  = xmin + dx*i;
    y  = y0 + 20.0*r1->Rndm();
    dt1 = dt1+dx;
    dt2 = dt2+dx;
    
    //add spikes
    if ( dt1 >= 10.0 ) {
      y  = y+200.0;
      dt1 = 0.0;
    }
    
    if ( dt2 >= 20.0 ) {
      y  = y+50.0;
      dt2 = 0.0;
    }
    
    if ( i < 10 ) std::cout << "x:  " << x
                            << '\t'
                            << "y:  " << y
                            << '\t'
                            << "dt: " << dt1
                            << '\t'
                            << "dt: " << dt2
                            << '\n';
    
    (*m_out) << x << '\t' << y << '\n';
    
  }
  
  m_out->close();
  delete m_out;
  
  return 1;
  
}
