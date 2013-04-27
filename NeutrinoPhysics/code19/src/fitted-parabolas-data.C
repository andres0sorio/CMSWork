// $Id: $
// Include files 

#include "logpar_interp.h"

void getdata( double xmin, double xmax, double dx) 
{
  
  logpar_interp * fobj = new logpar_interp("../data/1959-650-1ES-data/log-parabolas-fit-data-points-v4.txt.csv");

  TF1 * f2 = new TF1("f", fobj, xmin, xmax, 0,"logpar_interp");
  f2->Draw();
    
  double xx = xmin;
  
  for (int k = 0; k < npoints; ++k) {
    
    std::cout << xx << " " << f2->Eval( xx ) << std::endl;
    
    xx += dx;
    
  }
  
}

void getdata( double xmin, double xmax, int npoints) 
{
  
  logpar_interp * fobj = new logpar_interp("../data/1959-650-1ES-data/log-parabolas-fit-data-points-v4.txt.csv");

  TF1 * f2 = new TF1("f", fobj, xmin, xmax, 0,"logpar_interp");
  f2->Draw();
    
  double xx = xmin;
  double dx = (xmax - xmin) / ((float)npoints);

  for (int k = 0; k < npoints; ++k) {
    
    std::cout << xx << " " << f2->Eval( xx ) << std::endl;
    
    xx += dx;
    
  }
  
}
