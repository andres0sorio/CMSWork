// -*- C++ -*-
//
// Package:    Digi2Reco
// Class:      Digi2Reco
// 
/**\class Digi2Reco Digi2Reco.cc RPCDigiAnalyzer/Digi2Reco/src/Digi2Reco.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Osorio
//         Created:  Sat Mar  7 15:56:24 CET 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class decleration
//

class Digi2Reco : public edm::EDAnalyzer {
   public:
      explicit Digi2Reco(const edm::ParameterSet&);
      ~Digi2Reco();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
Digi2Reco::Digi2Reco(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


Digi2Reco::~Digi2Reco()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
Digi2Reco::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;



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
Digi2Reco::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Digi2Reco::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(Digi2Reco);
