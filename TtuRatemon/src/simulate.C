// $Id: main.C,v 1.2 2007/10/16 12:24:54 aosorio Exp $
// Include files 


#include "CommonIncludes.h"
#include <TRandom3.h>
#include "TUnixSystem.h"
#include <fstream>

int main(int iargv, const char **argv) {

  /////
  //... simulate the output from java application with rates

  TRandom3 * rdn = new TRandom3(0);

  //........................................................
  //.... start with the header from the java application

  std::ifstream * header = new std::ifstream("check-header.txt",std::ifstream::in);
  while (1) {
    std::string output;
    (*header) >> output;
    if (! header->good() ) break;
    std::cout << output << '\n';
  } 
  
  std::cout << "===START===" << std::endl;
  
  //........................................................

  float wfactor=1;
  
  for( int i=0; i < 1100; ++i) 
  //  while(1)
  {
    //TTU_1
    for(int ttu=1; ttu <= 3; ++ttu) 
    {
      
      for( int trig=8; trig <= 9; ++trig) 
      {
        
        if (ttu == 2 && trig == 9 )
          continue;
  
        if (ttu == 3 && trig == 9 )
          wfactor = 5.0;
        else wfactor = 1.0;
                      
        int wheel = (int) 100 + wfactor*trig*( (rdn->Rndm()) * ( 2.0 ));
        std::cout << wheel << " ";
        
        for( int k=0; k<12; ++k ) 
        {
          int sector = (int) (k+5) + 10*wfactor*( (rdn->Rndm()) * ( .8 ));
          
          std::cout << sector << " ";
          
        }
        
        std::cout << '\n';
        
      }
      
    }
    
    gSystem->Sleep(1);

  }
  
  //std::cout << -1 << '\n';
    
  return 1;
  

}
