// -*- C++ -*-
//
// Package:    L1GtTechTrig
// Class:      L1GtTechTrig
// 
/**\class L1GtTechTrig L1GtTechTrig.cc StudyL1Trigger/L1GtTechTrig/src/L1GtTechTrig.cc

 Description: This is a class to run a full analysis on objects from the L1 technical trigger bits

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Wed May 27 21:52:40 CEST 2009
// $Id$
//
//

// system include files
#include <memory>
#include <bitset>
#include <cmath>
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandMatchMap.h"

#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

//physics tools
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Common/interface/View.h"

//... RPC information
#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "DataFormats/RPCDigi/interface/RPCDigi.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>

//... L1 information

#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h>
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"

//Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

//... For Track Study
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"

#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"

//add simhit info
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"

//--- for SimHit
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

//simtrack
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

//#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH2D.h"

#include <StudyL1Trigger/L1GtExtractInfo/interface/gzstream.h>

//
//

class L1GtTechTrig : public edm::EDAnalyzer {
public:
  explicit L1GtTechTrig(const edm::ParameterSet&);
  ~L1GtTechTrig();
  
  
private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  void lookatPATCandidates( const edm::Event& iEvent, const edm::EventSetup& iSetup);
  
  void lookatMuonCandidates( const edm::Event& iEvent, const edm::EventSetup& iSetup );
  
  void lookatPSimHits( const edm::Event& iEvent, const edm::EventSetup& iSetup );
  
  void lookatPSimHitsWithTracker( const edm::Event& iEvents, const edm::EventSetup& iSetup );
  
  void lookatGeneralTracks( const edm::Event& iEvent, const edm::EventSetup& iSetup );

  void lookatRpcRecHits( const edm::Event& iEvent, const edm::EventSetup& iSetup );

  int  getBarrelLayer( const int & _layer, const int & _station );
    
  // ----------member data ---------------------------
  
  long double m_currentTime;
  long double m_previousTime;
  long double m_totalTime;
  long double m_elapsedTime;

  bool isTriggeredBy25;
  bool wasTriggeredBy[8];

  TH1D * m_ttBitsResults;
  
  TH1D * m_NOttBits;
  
  TH1D * MuonPt;
  TH1D * MuonEta;
  TH2D * MuonEtaPhi;
  TH2D * MuonEtaPhi_GBL;
  TH1D * MuonPhi;
  TH1D * MuonChi2DoF;
  TH1D * Muond0dist_STA;
  TH1D * Muondszdist_STA;
  TH1D * Muond0dist_GBL;
  TH1D * Muondszdist_GBL;
  TH1D * MuonType;
  TH1D * NumberMuonsEvt;
  TH1D * MuonCaloCompatibility;
  TH1D * MuonPt_GBL;
  TH1D * MuonPt_GBL_bit25;
  TH1D * m_pointingTrack;
  TH1D * m_pointingNoRecoTrack;
  
  TH1D * m_HMuonPt_Bit[8];
  TH2D * m_HMuonEtaPhi_Bit[8];
  TH1D * m_HMuonPhi_Bit[8];
  TH1D * m_HMuonChi2DoF_Bit[8];
  TH1D * m_HMuond0dist_Bit[8];
  TH1D * m_HMuondszdist_Bit[8];

  TH1D * NumberSimTracks;
  TH1D * SimTracksPDG;
  TH1D * SimTracksPDG_Muon;
  
  TH1D * NumberSimHitsTrack;
  TH1D * NumberSimHitsTOB;
  TH1D * NumberSimHitsTEC;
  
  TH1D * NumberJetsEvt;
  TH2D * JetsEtaPhi;
  TH2D * JetsEtaPt;

  TH1D * TrackParticle_Pt;
  TH2D * TrackParticle_EtaPhi;
  
  TH1D * TrackParticle_Pt_TOB;
  TH2D * TrackParticle_EtaPhi_TOB;
  
  TH1D * TrackParticle_Pt_TEC;
  TH2D * TrackParticle_EtaPhi_TEC;
  
  TH1D * TrackParticle_Pt_TOBTEC;
  TH2D * TrackParticle_EtaPhi_TOBTEC;
  
  TH1D * TrackParticle_Pt_TOB_Bit[10];
  TH1D * TrackParticle_Pt_TEC_Bit[10];
  TH1D * TrackParticle_Pt_TOE_Bit[10];
  
  TH2D * TrackParticle_etaphi_TOB_Bit[10];
  TH2D * TrackParticle_etaphi_TEC_Bit[10];
  TH2D * TrackParticle_etaphi_TOE_Bit[10];
  
  TH2D * m_hh_xy_outer[10];
  TH2D * m_hh_yz_outer[10];
  TH2D * m_hh_xy_inner[10];
  TH2D * m_hh_yz_inner[10];

  TH2D * m_hh_xy_outer_All;
  TH2D * m_hh_yz_outer_All;
  TH2D * m_hh_xy_inner_All;
  TH2D * m_hh_yz_inner_All;

  TH2D * m_hh_xy_rpc_rechit[10];
  TH2D * m_hh_yz_rpc_rechit[10];
  
  TH1D * m_h_RpcHits_Layer[10];
  TH1D * m_h_RpcHits_Sector[10];
  TH1D * m_h_RpcHits_Wheel[10];

  TH2D * m_hh_xy_rpc_rechit_All;
  TH2D * m_hh_yz_rpc_rechit_All;
  
  TH1D * m_h_RpcHits_Layer_All;
  TH1D * m_h_RpcHits_Sector_All;
  TH1D * m_h_RpcHits_Wheel_All;
  
  TH1D * m_h_RpcHits_FracStation[4];
  
  int m_bxFinal;
  int m_maxNBx;
  int m_bxNumMin;
  int m_bxNumMax;
  int m_useCompression;
  int m_writeMode;
  int m_precision;
  int m_maxRate;
  int m_flag;
  double m_muonPtcut;

  std::vector<L1GtTechnicalTrigger> ttVec;

  bool m_trackParticles;
  bool m_patData;
  bool m_generalTracks;
  
  unsigned int m_firstEvt;
  unsigned int m_lastEvt;
  unsigned int m_nevt;
  
  edm::InputTag m_ltcDigiLabel;
  edm::InputTag m_muonLabel;
  edm::InputTag m_recoMuonLabel;
  edm::InputTag m_recoTracksLabel;
  
  int m_maxttBits;
  std::vector<unsigned> m_ttBits;
  
  edm::ParameterSet m_conf;
  
  int  m_selFilter;
  int  m_EvtWindow;
  
  bool m_debug;
  bool m_trackInTOB    ;
  bool m_trackInTEC    ;
  bool m_trackInTOBTEC ;

  double m_maxPt;
    
  const TrackerGeometry* theTracker;

  gz::ogzstream * gzfileDump;
  
};

