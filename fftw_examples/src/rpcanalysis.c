// $Id: $
// Include files
#include <fftw3.h>

#include "Data.h"

int main(int iargv, const char **argv) {

  if(iargv < 2 ) {
    std::cout << "usage : rpcanalysis> [maxdata]" << std::endl;
    return 0;
  }
    
  const int MAXDATA = atoi(argv[1]);
  
  double * in = new double[MAXDATA];
  fftw_complex *out = new fftw_complex[MAXDATA];
  fftw_plan p;
  
  Data * dd = new Data("rpcdata.dat");
  std::ofstream *m_out;
  
  int k = 0;
  while ( dd->next() )
  {
    in[k] = dd->X2();
    if ( k<5 ) std::cout << dd->X1() << '\t' << in[k] << std::endl;
    ++k;
  }
  
  delete dd;
  
  for(int i=0; i < MAXDATA; ++i )
  {
    out[i][0] = 0.0;
    out[i][1] = 0.0;
  }
  
  p = fftw_plan_dft_r2c_1d(MAXDATA, in, out, FFTW_ESTIMATE);
  
  fftw_execute(p); /* repeat as needed */
  
  m_out = new std::ofstream("fftwresults.dat",ofstream::out);
  
  std::cout << "........." << '\n';
  std::cout << "Re.\t\t.Im." << '\n';
  
  for( k=0; k < MAXDATA; ++k) 
  {
    if ( k < 10 ) std::cout << out[k][0] << '\t' << '\t'  
                            << out[k][1] << '\t' << '\t'
                            << sqrt(out[k][0]*out[k][0] + out[k][1]*out[k][1]) 
                            << std::endl;
    
    (*m_out) << out[k][0] << '\t' << out[k][1] << std::endl;
    
  }
  
  fftw_destroy_plan(p);
  
  m_out->close();
  delete m_out;
  
  delete[] in;
  delete[] out;
  
  
}

