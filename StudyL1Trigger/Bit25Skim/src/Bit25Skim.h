// -*- C++ -*-
//
// Package:    Bit25Skim
// Class:      Bit25Skim
// 
/**\class Bit25Skim Bit25Skim.cc StudyL1Trigger/Bit25Skim/src/Bit25Skim.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Felipe Osorio Oliveros,512 1-009,+41227670491,
//         Created:  Fri May 21 11:27:01 CEST 2010
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

#include "DataFormats/DetId/interface/DetId.h"


//... For Track Study
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//
// class declaration
//

class Bit25Skim : public edm::EDFilter {

public:
  explicit Bit25Skim(const edm::ParameterSet&);
  ~Bit25Skim();
  
private:
  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  
  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_hltResultsLabel;
  edm::InputTag m_recoTracksLabel;
  
  unsigned int m_lumiSection;
  
  std::vector<unsigned> m_ttBits;
  std::vector<unsigned> m_makeCoincidenceTT;
  std::vector<std::string> m_makeCoincidenceHLT;
  
  HLTConfigProvider m_hltConfig;
  
  std::bitset<10> m_TTUBits[3];
  
  int m_totalEvts;
  
  int m_totalFilter;
  
  bool m_Trkc;
  bool m_disableTTUbits;
  bool m_requireTracker;
  
  std::string m_processName;
  

};

