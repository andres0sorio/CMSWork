// $Id: 
// Include files 


#include <PGSAnalyzer.h>

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {

  PGSAnalyzer * parser = new PGSAnalyzer("input.lhco");
  
  parser->SetMaxEvents(400);
  parser->SetPermutations("permutations.out");
  parser->SetWeights("weights.out");
  parser->AnalyzePermutations();
  
  delete parser;

  ///////////////////////////////////////////////////

  return 1;
    
}
