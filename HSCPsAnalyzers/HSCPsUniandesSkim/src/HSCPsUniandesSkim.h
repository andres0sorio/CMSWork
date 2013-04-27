// -*- C++ -*-
//
// Package:    HSCPsUniandesSkim
// Class:      HSCPsUniandesSkim
// 
/**\class HSCPsUniandesSkim HSCPsUniandesSkim.cc HSCPsAnalyzers/HSCPsUniandesSkim/src/HSCPsUniandesSkim.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Andres Osorio
//         Created:  Thu Feb 16 12:43:41 COT 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


//Trigger

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

//
// class declaration
//

class HSCPsUniandesSkim : public edm::EDFilter {
public:
  explicit HSCPsUniandesSkim(const edm::ParameterSet&);
  ~HSCPsUniandesSkim();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:

  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual bool beginRun(edm::Run&, edm::EventSetup const&);
  virtual bool endRun(edm::Run&, edm::EventSetup const&);
  virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
  virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

  // ----------member data ---------------------------

  /// module config parameters
  std::string   m_processName;
  std::string   m_triggerName;
  edm::InputTag m_triggerResultsTag;
  edm::InputTag m_triggerEventTag;
  
  /// additional class data memebers
  edm::Handle<edm::TriggerResults> m_triggerResultsHandle;
  edm::Handle<trigger::TriggerEvent> m_triggerEventHandle;
  HLTConfigProvider m_hltConfig;

};

