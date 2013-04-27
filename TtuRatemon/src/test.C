// $Id: main.C,v 1.2 2007/10/16 12:24:54 aosorio Exp $
// Include files 


#include "CommonIncludes.h"
#include <iostream>
#include "TrigRates.h"

int main(int iargv, const char **argv) {

  TrigRates * h1 = new TrigRates();
  
  std::cin >> (*h1);
  
  std::cout << h1->rates.size() << std::endl;
  
  for(int i=0; i < 65; ++i) 
    std::cout << h1->rates[i] << ',';
   
  std::cout << '\n';
  std::cout << "done." << std::endl;

  delete h1;
      
}
