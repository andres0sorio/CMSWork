// -*- C++ -*-
//
// Package:    ZPlotsAnalyzer
// Class:      ZPlotsAnalyzer
// 
/**\class ZPlotsAnalyzer ZPlotsAnalyzer.cc PATTutorial/ZPlotsAnalyzer/src/ZPlotsAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Thu Jan 29 17:27:36 CET 2009
// $Id$
//
//

#include "PATTutorial/ZPlotsAnalyzer/src/ZPlotsAnalyzer.h"



ZPlotsAnalyzer::ZPlotsAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  histo = new ZPlots( fs , "BaselineSel");
  
}


ZPlotsAnalyzer::~ZPlotsAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called to for each event  ------------

using namespace edm;

void ZPlotsAnalyzer::analyze(const Event& iEvent, const EventSetup& iSetup)
{
  
  float trkpt = 100.00;
  histo->tracksPt->Fill( trkpt );

  
#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif
  
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif

}


// ------------ method called once each job just before starting event loop  ------------
void 
ZPlotsAnalyzer::beginJob(const edm::EventSetup&)
{
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ZPlotsAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZPlotsAnalyzer);
