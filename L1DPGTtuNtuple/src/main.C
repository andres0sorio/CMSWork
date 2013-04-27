// $Id: main.C,v 1.2 2007/10/16 12:24:54 aosorio Exp $
// Include files 


#include "CommonIncludes.h"
#include "RunAnalysis.h"

int main(int iargv, const char **argv) {

  
  const char *infileA = argv[1];
  const char *infileB = argv[2];

  //RunAnalysis * h1 = new RunAnalysis( infile );
  RunAnalysis * h1 = new RunAnalysis( infileA , infileB  );
  
  //bool useTTUtree = true;
  
  h1->Initialize();
  h1->Loop(-1);
  
  delete h1;
  return 1;
    
}
