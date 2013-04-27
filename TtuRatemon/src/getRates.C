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
#include <time.h>

std::string getDateTime( struct tm * timeinfo )
{
  
  std::string strtime( asctime (timeinfo) );

  int pos = int( strtime.find(":") );
  while ( pos > 0 ) 
  {
    strtime.replace(pos,1,"-");
    pos = int( strtime.find(":") );

  }
  
  pos = int( strtime.find(" ") );
  while ( pos > 0 ) 
  {
    strtime.replace(pos,1,"_");
    pos = int( strtime.find(" ") );

  }
  
  pos = int( strtime.find("\n") );
  strtime.replace(pos,1,".");

  return strtime;
  
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

  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  
  std::ostringstream fname;
  fname << "/rpctdata/ttumon/ttuRateMon_" << getDateTime(timeinfo) << "root";

  //
  int counter = 0;
  TtuRates * h1 = new TtuRates( fname.str().c_str() );

  GuiHistoRates * main = new GuiHistoRates(gClient->GetRoot(), 800, 500);
  
  while(1) {
    
    TrigRates * rateReader = new TrigRates();
    std::cin >> (*rateReader);
    
    rateReader->hasStop = main->m_terminate;
    
    if ( rateReader->hasStop ) 
    {
      delete rateReader;
      break;
    }
    
    h1->Fill( rateReader );
    h1->Time = counter;
    
    main->DoDraw( h1 );
    
    ++counter;
    
    gSystem->Sleep(100);
    gSystem->ProcessEvents();
    
    delete rateReader;
    
  }
  
  //........................................................

  delete h1;
  
  gApplication->Terminate(0);

  return 1;

}
