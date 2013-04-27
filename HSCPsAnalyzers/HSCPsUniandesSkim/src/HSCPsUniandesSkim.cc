
#include "HSCPsAnalyzers/HSCPsUniandesSkim/src/HSCPsUniandesSkim.h"

//////

HSCPsUniandesSkim::HSCPsUniandesSkim(const edm::ParameterSet& iConfig)
{

  m_processName = ps.getParameter<std::string>("processName");
  m_triggerName = ps.getParameter<std::string>("triggerName");
  m_triggerResultsTag = ps.getParameter<edm::InputTag>("triggerResults");
  m_triggerEventTag = ps.getParameter<edm::InputTag>("triggerEvent");

}


HSCPsUniandesSkim::~HSCPsUniandesSkim()
{
 

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
HSCPsUniandesSkim::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{




   return true;

}

// ------------ method called once each job just before starting event loop  ------------
void 
HSCPsUniandesSkim::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HSCPsUniandesSkim::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
HSCPsUniandesSkim::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
HSCPsUniandesSkim::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
HSCPsUniandesSkim::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
HSCPsUniandesSkim::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HSCPsUniandesSkim::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(HSCPsUniandesSkim);
