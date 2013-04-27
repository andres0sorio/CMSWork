// $Id: 
// Include files 


#include <WeightsAnalyzer.h>

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {

  WeightsAnalyzer * wreader = new WeightsAnalyzer("weights.out");

  int events = 0;
    
  while ( 1 ) {

    int output = wreader->Next(); 

    if (output == -1 ) break;
    
    if (output == -2 ) {
    
      wreader->Reset();
      ++events;
      continue; 
      
    }
    
    wreader->Reset();

    ++events;
    
  }

  std::cout << "total events " << events << std::endl;
  
  delete wreader;
    
  ///////////////////////////////////////////////////

  return 1;
    
}
