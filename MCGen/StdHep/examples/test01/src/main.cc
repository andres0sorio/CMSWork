// WARNING: typically one needs 25 MB/100 events at the LHC.
// Therefore large event samples may be impractical.

#include "Pythia.h"

using namespace Pythia8; 

int main() {
  
  // Generator. Process selection. LHC initialization. Histogram.
  Pythia pythia;
  
  // Read in commands from external file.
  pythia.readFile("ttbar01.cmnd");    
  
  int nEvent   = pythia.mode("Main:numberOfEvents");
  
  pythia.init();
  
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    
    if (!pythia.next()) continue;
    
    //if (iEvent < 1) {pythia.info.list(); pythia.event.list();} 
    //HepMC::GenEvent* hepmcevt = new HepMC::GenEvent(HepMC::Units::GEV, HepMC::Units::MM);
    // Fill HepMC event, including PDF info.
    //ToHepMC.fill_next_event( pythia, hepmcevt );
    // End of event loop. Statistics. Histogram. 

  }
  
  pythia.statistics();
  
  // Done.
  return 0;

}
