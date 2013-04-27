// $Id: 
// Include files 

#include <Graphics.h>
#include <d2sigmaCC_NC.h>

#include <sstream>
#include "sys/stat.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int iargv, char **argv) {
    
  //.........................................................................................

  double xx[2];
  xx[0] = 1.0;
  xx[1] = 0.5;
  
  dsigmaCC_dQdy * f1 = new dsigmaCC_dQdy();
  
  f1->DoEval(xx);
  
  delete f1;
  

  //.........................................................................................

  return 1;
  
}

#include "LHAPDF/FortranWrappers.h"
#ifdef FC_DUMMY_MAIN
int FC_DUMMY_MAIN() { return 1; }
#endif
