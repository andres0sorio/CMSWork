// -*- C++ -*-
//
// Package:    TTUTimingSkim
// Class:      TTUTimingSkim
// 
/**\class TTUTimingSkim TTUTimingSkim.cc StudyL1Trigger/TTUTimingSkim/src/TTUTimingSkim.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Wed Dec  9 15:12:07 CET 2009
// $Id$
//
//

// system include files
#include <memory>
#include <bitset>
#include <map>
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/TriggerNames.h"

//.. L1 GT Trigger
#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h>
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"
#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h>

//Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

//.. Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//
// class declaration
//

class TTUTimingSkim : public edm::EDFilter {
public:
  explicit TTUTimingSkim(const edm::ParameterSet&);
  ~TTUTimingSkim();
  
private:
  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  
  int  discriminateGMT( const edm::Event& iEvent, const edm::EventSetup& iSetup );

  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_gmtReadoutLabel;

  unsigned int m_lumiSection;
  
  int m_selectedBit;
  int m_selectedBX;
  int m_detector;
  
  int m_totalEvts;
  int m_totalFilter;
  
  std::vector<int> m_GMTcandidatesBx;
  std::vector<int> m_DTcandidatesBx;

  bool m_rpcTrigger;
  bool m_dtTrigger;

  bool m_debug;
  
    
};

