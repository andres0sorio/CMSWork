#include "DoubleMuonsFilter.h"

//

DoubleMuonsFilter::DoubleMuonsFilter(const edm::ParameterSet& iConfig)
{

  

}


DoubleMuonsFilter::~DoubleMuonsFilter()
{
 

}


// ------------ method called on each new Event  ------------
bool
DoubleMuonsFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  

  
  
  
  return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
DoubleMuonsFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DoubleMuonsFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
DoubleMuonsFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
DoubleMuonsFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
DoubleMuonsFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
DoubleMuonsFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DoubleMuonsFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(DoubleMuonsFilter);
