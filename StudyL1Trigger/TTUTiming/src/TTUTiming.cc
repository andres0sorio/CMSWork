// system include files
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//
//
TTUTiming::TTUTiming(const edm::ParameterSet& iConfig)
{

  //now do what ever initialization is needed

}


TTUTiming::~TTUTiming()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TTUTiming::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  
  
}
// ------------ method called once each job just before starting event loop  ------------
void 
TTUTiming::beginJob()
{
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TTUTiming::endJob() {

}

//define this as a plug-in
DEFINE_FWK_MODULE(TTUTiming);
