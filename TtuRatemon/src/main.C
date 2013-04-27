// $Id: main.C,v 1.2 2007/10/16 12:24:54 aosorio Exp $
// Include files 


#include "CommonIncludes.h"
#include "TtuRates.h"
#include <TApplication.h>
#include <TGClient.h>

int main(int iargv, const char **argv) {

  const char *infile = argv[1];

  TApplication theApp("App", 0, 0);

  TFile *f1 = new TFile( infile, "READ");
  
  TtuRates * h1 = new TtuRates( f1 );
  
  h1->Loop();
  
  theApp.Run();
  
  delete h1;
  return 1;
  
}
