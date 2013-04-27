// $Id: main.C,v 1.2 2007/10/16 12:24:54 aosorio Exp $
// Include files 


#include "CommonIncludes.h"
#include "TtuRates.h"
#include "TrigRates.h"
#include "TCanvas.h"
#include "GuiHistoRates.h"

#include <TApplication.h>
#include <TGClient.h>
#include "TThread.h"


Bool_t finished;

void *handle1(void * arg)
{

  int counter = 0;
  finished = false;
  GuiHistoRates * mainGui = new GuiHistoRates(gClient->GetRoot(), 500, 500);

  while(!finished) {
    
    TrigRates * rateReader = new TrigRates();
    std::cin >> (*rateReader);
    
    if ( rateReader->hasStop ) 
    {
      delete rateReader;
      finished = true;
      break;
    }
    
    TtuRates * h1 = (TtuRates*)arg;
    
    h1->Fill( rateReader );
    h1->Time = counter;
    mainGui->DoDraw( h1 );

    ++counter;
    
    delete rateReader;

  }

  //TApplication * p1 = (TApplication*) app;
  //p1->Run();
  //return 0;
  
}

int main(int iargv, char **argv) {
  
  TApplication theApp("App", 0, 0);

  //........................................................
  //start only when data is ready to transmit rates

  std::string start("===START===");

  while(1) 
  {
    std::string header;
    std::cin >> header;
        
    if ( header.compare( start) == 0 ) 
    {
      break;
    }
    
  }
  //........................................................
  
  TtuRates * h1 = new TtuRates( "testRates.root" );
  
  
  
  TThread * t1 = new TThread("t0", handle1, (void*) h1 );
  t1->Run();
  
  while(!finished) {
    
    gSystem->Sleep(100);
    gSystem->ProcessEvents();
    
  }
  
  //........................................................

  delete h1;

  delete t1;
  
  return 1;

}
