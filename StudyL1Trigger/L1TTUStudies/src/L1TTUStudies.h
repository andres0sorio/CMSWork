// -*- C++ -*-
//
// Package:    L1TTUStudies
// Class:      L1TTUStudies
// 
/**\class L1TTUStudies L1TTUStudies.cc StudyL1Trigger/L1TTUStudies/src/L1TTUStudies.cc

 Description: <one line class summary>

 Implementation:
 
 This is based on the StudyL1Trigger/L1GtTtuAnalyzer

*/


//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Wed Jun 17 14:46:35 CEST 2009
// $Id$
//

// system include files
#include <memory>
#include <bitset>
#include <map>
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"

#include "DataFormats/RPCDigi/interface/RPCDigi.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

//... For Track Study
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"

#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"

#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h>
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"
#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h>

//Technical trigger bits and HLT
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "FWCore/Framework/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "TLorentzVector.h"

#include <DataFormats/MuonDetId/interface/DTChamberId.h>
#include <DataFormats/MuonReco/interface/MuonChamberMatch.h>
#include <DataFormats/MuonDetId/interface/MuonSubdetId.h>

#include "StudyL1Trigger/L1TTUStudies/src/TTUHistograms.h"



//
// class declaration
//

//class L1TTUStudies : public edm::EDAnalyzer {

class L1TTUStudies : public edm::EDFilter {

public:
  explicit L1TTUStudies(const edm::ParameterSet&);
  ~L1TTUStudies();
  
  
private:
  
  virtual void beginJob();
  virtual void beginRun(const edm::EventSetup&);
  
  virtual void endJob() ;
  
  //virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
  virtual bool filter( edm::Event&, const edm::EventSetup&);

  // ----------member data ---------------------------
  
  void initialize();
  
  bool applyMuonCuts ( const reco::Muon & );
  
  unsigned int m_firstEvt;
  unsigned int m_lastEvt;
  unsigned int m_nevt;
  unsigned int m_lumiSection;
  
  int m_maxttBits;  
  int m_maxttBitsTrigger;
  int m_maxAlgBitsTrigger;
  double m_maxMuonPt;
  double m_muonPtcut;
  int m_muonTypeSection;
  
  bool m_isBit31_matched;
  
  edm::InputTag m_rpcDigiLabel;
  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_gmtReadoutLabel;
  edm::InputTag m_recoMuonLabel;
  edm::InputTag m_recoTracksLabel;
  edm::InputTag m_hltResultsLabel;
  edm::InputTag m_recoSiStripLabel;
  edm::InputTag m_recoPixelLabel;
  
  HLTConfigProvider m_hltConfig;
  
  std::vector<std::string> m_checkhltPaths;

  std::vector<unsigned> m_ttBits;
  std::vector<unsigned> m_ttBitsCollisions;
  std::vector<unsigned> m_makeCoincidenceTT;
  std::vector<unsigned> m_makeCoincidenceAlg;
  std::vector<int> m_selectedBx;
  
  int m_trkSelectionCuts;
  
  std::bitset<10> m_trkCuts;
  
  std::string m_processName;
  
  double m_trackerLength;
  double m_trackerHeight;
    
  bool m_debug;
  bool m_tracker_activity;
  bool m_rpcTrigger;
  bool m_dtTrigger;
  bool m_hasActivity_DT;

  std::map<int, bool> m_ttu_results;

  std::map<int,int> m_kSectorMin;
  std::map<int,int> m_kSectorMax;

  std::map<int,int> m_kRingLeft;
  std::map<int,int> m_kRingRight;
  
  TTUHistograms * m_Histograms;

  int m_GoodMuonSelection;
      
  //
  
  bool lookatRecoMuons(const edm::Event & iEvent ,
                       const edm::EventSetup& iSetup,
                       const edm::Handle< L1GlobalTriggerReadoutRecord > & gtRecord ) ;

  int getBarrelLayer( int , int);
  
};//
