
#include <iostream>
#include <sstream>
#include "Pythia.h"

using namespace Pythia8; 

int main( int argc, char* argv[] ) {
  
  int nEvent  = 1000;
  
  // Generator.
  Pythia pythia;
  Event& event = pythia.event;

  if ( argc < 2 ) 
  {
    std::cout << "Not enough parameters" << std::endl;
    exit(1);

  }
  
  std::stringstream randomseed;
  std::stringstream lhapdf;
  
  randomseed << "Random:seed = " << argv[1];
  lhapdf   << "SLHA:file = " << argv[2];
  
  std::cout << randomseed.str() << std::endl;
  std::cout << lhapdf.str() << std::endl;
  
  pythia.readString("SUSY:qqbar2chi+-chi0 = on");
  pythia.readString(lhapdf.str().c_str());

  pythia.readString("PDF:useLHAPDF = on");
  pythia.readString("PDF:LHAPDFset = cteq6l.LHpdf " );
  
  pythia.readString("Random:setSeed = on");
  pythia.readString(randomseed.str().c_str());

  pythia.readString("SUSY:idA        = 1000023");
  pythia.readString("SUSY:idB        = 1000024");
  
  pythia.readString("1000023:onMode = off");
  pythia.readString("1000024:onMode = off");
  
  pythia.readString("1000023:onIfMatch = 1000022 23");
  pythia.readString("1000024:onIfMatch = 1000022 24");
  
  pythia.readString("24:onMode = off");
  pythia.readString("24:onIfMatch = -13 14");
  pythia.readString("23:onMode = off");
  pythia.readString("23:onIfMatch = 13 -13");
  
  pythia.readString("PartonLevel:MI = off "); // ! no multiple interactions
  pythia.readString("PartonLevel:ISR = off "); // ! no initial-state radiation 
  pythia.readString("PartonLevel:FSR = off "); // ! no final-state radiation
  pythia.readString("HadronLevel:Hadronize = off "); // ! no hadronization

  pythia.init( 2212,  2212, 8000.0);
  
  pythia.settings.listChanged();
  
  // Begin event loop.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    
    // Generate events.  Skip if error.
    if ( !pythia.next() ) continue;
    
  } // End of event loop.
  
  // Statistics. 
  pythia.statistics( true );
  
  // Done.
  return 0;
  
}
