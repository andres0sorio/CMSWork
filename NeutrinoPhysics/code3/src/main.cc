// $Id: 
// Include files 

#include "nuN_interpxsec.h"

int main(int iargv, const char **argv) {
  

  Interpolation * interp = new Interpolation( argv[1] );

  double x = 1.00;
  double dx = 0.10;

  std::cout << "#m=0,S=2" << std::endl;

  interp->showPointsCC();

  std::cout << "#m=0,S=2" << std::endl;

  interp->showPointsNC();


  std::cout << "#m=1,S=1" << std::endl;

  while ( x < 12 ) {

    double val1 = interp->evaluateNC( x );
    std::cout << x << '\t' << val1 << '\n';

    x = x + dx;

  }
  
  x = 1.00;
  
  std::cout << "#m=1,S=1" << std::endl;
  
  while ( x < 12 ) {
    
    double val1 = interp->evaluateCC( x );
    std::cout << x << '\t' << val1 << '\n';
    
    x = x + dx;

  }

  delete interp;

  return 1;
    
}
