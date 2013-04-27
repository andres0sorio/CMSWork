// $Id: 
// Include files 


#include <PGSAnalyzer.h>

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {

  PGSAnalyzer * parser = new PGSAnalyzer("input.lhco");
  parser->Loop();
  delete parser;
  
  ///////////////////////////////////////////////////

  return 1;
    
}
