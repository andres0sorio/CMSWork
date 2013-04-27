// $Id: $
// Include files 
#include "logpar_interp.h"


void plotInterpolation() 
{
  
  logpar_interp * fobj = new logpar_interp("../data/1959-650-1ES-data/log-parabolas-fit-data-points-v4.txt.csv");

  TF1 * f2 = new TF1("f", fobj, 11, 27, 0,"logpar_interp");
  f2->Draw();
  
  int npoints = 300;
  double xmin = 18.0;
  double xmax = 21.0;
  double dx = (xmax - xmin) / ((float)npoints);
  
  double xx = xmin;
    
  for (int k = 0; k < npoints; ++k) {
    
    std::cout << xx << " " << f2->Eval( xx ) << std::endl;
    
    xx += dx;
    
  }
    
}
