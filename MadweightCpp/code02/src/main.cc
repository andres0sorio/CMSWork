// $Id: 
// Include files 


#include <LHEAnalyzer.h>

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {

  LHEAnalyzer * lhe = new LHEAnalyzer("input.root");
  
  lhe->Loop();
  
  delete lhe;
  
  ///////////////////////////////////////////////////

  return 1;
    
}
