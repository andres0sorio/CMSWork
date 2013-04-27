// -*- C++ -*-
//
// Package:    TTUSkim
// Class:      TTUSkim
// 
/**\class TTUSkim TTUSkim.cc StudyL1Trigger/TTUSkim/src/TTUSkim.cc

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

//.. Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//
// class declaration
//

class TTUSkim : public edm::EDFilter {
public:
  explicit TTUSkim(const edm::ParameterSet&);
  ~TTUSkim();
  
private:
  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  
  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_hltResultsLabel;
    
  unsigned int m_lumiSection;
  
  std::vector<unsigned> m_ttBits;
  std::vector<unsigned> m_makeCoincidenceTT;
  std::vector<unsigned> m_makeCoincidenceAlg;
  std::vector<std::string> m_makeCoincidenceHLT;

  HLTConfigProvider m_hltConfig;

  std::bitset<10> m_TTUBits[3];
  
  int m_totalEvts;
  
  int m_totalFilter;

  bool m_disableTTUbits;

  std::string m_processName;
  

};

