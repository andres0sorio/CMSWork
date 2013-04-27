// -*- C++ -*-
//
// Package:    MCTTUSkim
// Class:      MCTTUSkim
// 
/**\class MCTTUSkim MCTTUSkim.cc StudyL1Trigger/MCTTUSkim/src/MCTTUSkim.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Tue Dec 22 12:27:49 CET 2009
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

class MCTTUSkim : public edm::EDAnalyzer {
   public:
      explicit MCTTUSkim(const edm::ParameterSet&);
      ~MCTTUSkim();


   private:
      virtual void beginJob() ;
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
MCTTUSkim::MCTTUSkim(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


MCTTUSkim::~MCTTUSkim()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MCTTUSkim::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
MCTTUSkim::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MCTTUSkim::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCTTUSkim);
