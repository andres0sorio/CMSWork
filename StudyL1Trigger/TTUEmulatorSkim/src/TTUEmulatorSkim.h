// -*- C++ -*-
//
// Package:    TTUEmulatorSkim
// Class:      TTUEmulatorSkim
// 
/**\class TTUEmulatorSkim TTUEmulatorSkim.cc StudyL1Trigger/TTUEmulatorSkim/src/TTUEmulatorSkim.cc

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
//#include "FWCore/Framework/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerNames.h"

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

class TTUEmulatorSkim : public edm::EDFilter {
public:
  explicit TTUEmulatorSkim(const edm::ParameterSet&);
  ~TTUEmulatorSkim();
  
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

  std::vector<L1GtTechnicalTrigger> ttVec;

  HLTConfigProvider m_hltConfig;

  std::bitset<10> m_TTUBits[3];
  
  int m_totalEvts;
  
  int m_totalFilter;

  bool m_disableTTUbits;

  std::string m_processName;
  

};

