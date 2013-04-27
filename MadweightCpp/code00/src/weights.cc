// $Id: 
// Include files 


#include <WeightsAnalyzer.h>

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {

  WeightsAnalyzer * wreader = new WeightsAnalyzer("weights.out");

  int events = 0;
    
  while ( wreader->Next() > 0 ) {

    ++events;
    
  }

  std::cout << "total events " << events << std::endl;
  
  delete wreader;
    
  ///////////////////////////////////////////////////

  return 1;
    
}
