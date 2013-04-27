
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
  std::stringstream higgmass;
  
  randomseed << "Random:seed = " << argv[1];
  higgmass   << "25:m0 = " << argv[2];
  
  std::cout << randomseed.str() << std::endl;
  std::cout << higgmass.str() << std::endl;
  
  pythia.readString("HiggsSM:gg2H = on");
  
  pythia.readString("PDF:useLHAPDF = on");
  pythia.readString("PDF:LHAPDFset = cteq6l.LHpdf " );
  
  pythia.readString("Random:setSeed = on");
  pythia.readString(randomseed.str().c_str());
  pythia.readString(higgmass.str().c_str());

  pythia.readString("25:onMode = off"); // esta opcion apaga todos los modos de decaimiento posibles para el Higgs
  pythia.readString("25:onIfMatch = 23 23"); // esta opcion enciende el decaimiento a 25 (H0) ->23 (Z) 23(Z) 
  
  //Caso 2: queremos Z0 -> mu- mu+
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
