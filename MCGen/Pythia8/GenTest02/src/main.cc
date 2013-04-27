// main31.cc is a part of the PYTHIA event generator.
// Copyright (C) 2011 Mikhail Kirsanov, Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program.
// It illustrates how HepMC can be interfaced to Pythia8.
// It studies the charged multiplicity distribution at the LHC.
// HepMC events are output to the hepmcout31.dat file.
// Written by Mikhail Kirsanov based on main01.cc.

// WARNING: typically one needs 25 MB/100 events at the LHC.
// Therefore large event samples may be impractical.

#include "Pythia.h"
#include "HepMCInterface.h"

#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"
#include "HepMC/IO_HEPEVT.h"
#include "HepMC/Units.h" ///from HepMC v.2.04+

using namespace Pythia8; 

int main() {
  
  // Interface for conversion from Pythia8::Event to HepMC one. 
  HepMC::I_Pythia8 ToHepMC;

  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io("hepmcout31.dat", std::ios::out);

  HepMC::IO_HEPEVT hep_io;
  
  // Generator. Process selection. LHC initialization. Histogram.
  Pythia pythia;
  
  // Read in commands from external file.
  pythia.readFile("ttbar01.cmnd");    
  
  int nEvent   = pythia.mode("Main:numberOfEvents");
  
  pythia.init();
  
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    
    if (!pythia.next()) continue;
    
    if (iEvent < 1) {pythia.info.list(); pythia.event.list();} 

    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent(HepMC::Units::GEV, HepMC::Units::MM);
    
    // Fill HepMC event, including PDF info.
    ToHepMC.fill_next_event( pythia, hepmcevt );
    
    


    
    delete hepmcevt;
    
    // End of event loop. Statistics. Histogram. 
  }
  
  pythia.statistics();
  
  // Done.
  return 0;

}
