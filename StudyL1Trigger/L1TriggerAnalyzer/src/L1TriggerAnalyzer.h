// -*- C++ -*-
//
// Package:    L1TriggerAnalyzer
// Class:      L1TriggerAnalyzer
// 
/**\class L1TriggerAnalyzer L1TriggerAnalyzer.cc StudyL1Trigger/L1TriggerAnalyzer/src/L1TriggerAnalyzer.cc

 Description: [one line class summary]

 Implementation: Skeleton for a L1 Trigger analyzer (access Algo Bits + GMT trigger information)
     
*/
//
// Original Author:  Andres Osorio
//         Created:  Mon Mar  5 09:41:41 COT 2012
// $Id$
//
//


// system include files
#include <memory>
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/ServiceRegistry/interface/Service.h>

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"

#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>

//
// class declaration
//

class L1TriggerAnalyzer : public edm::EDAnalyzer {

public:
  explicit L1TriggerAnalyzer(const edm::ParameterSet&);
  ~L1TriggerAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);

  virtual void beginLuminosityBlock(const edm::LuminosityBlock &, const edm::EventSetup &);

  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  // ----------member data ---------------------------

  bool m_debug;
  
  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_gmtReadoutLabel;
  
  std::vector<int> m_bitsVec;
  std::map< std::string, TH1F * > h_1DHistContainer;


};

