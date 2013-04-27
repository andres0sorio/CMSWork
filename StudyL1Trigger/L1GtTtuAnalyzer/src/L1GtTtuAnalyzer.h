// -*- C++ -*-
//
// Package:    L1GtTtuAnalyzer
// Class:      L1GtTtuAnalyzer
// 
/**\class L1GtTtuAnalyzer L1GtTtuAnalyzer.cc StudyL1Trigger/L1GtTtuAnalyzer/src/L1GtTtuAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/

//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Wed Jun 17 14:46:35 CEST 2009
// $Id$
//
//

// system include files
#include <memory>
#include <bitset>
#include <map>
#include <sstream>

#include "boost/date_time/local_time/local_time.hpp"

#include <StudyL1Trigger/L1GtExtractInfo/interface/gzstream.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
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

//Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH2D.h"

#include "StudyL1Trigger/L1GtExtractInfo/interface/L1GtExtractedInfo.h"
#include "StudyL1Trigger/L1GtTtuAnalyzer/src/L1TTUTree.h"

//
// class declaration
//
using namespace boost::gregorian;
using namespace boost::local_time;
using namespace boost::posix_time;

namespace
{
  const ptime EPOCH(date(1970,1,1));  
}

class L1GtTtuAnalyzer : public edm::EDAnalyzer {

public:
  explicit L1GtTtuAnalyzer(const edm::ParameterSet&);
  ~L1GtTtuAnalyzer();
  
  
private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------

  boost::uint64_t m_timestamp;

  int  discriminateGMT( const edm::Event& iEvent, const edm::EventSetup& iSetup );
  
  long double evaluateTime( unsigned int , unsigned int );
  
  void getRpcInfo( const edm::Event&, const edm::EventSetup& );
  
  void lookatTracks( const edm::Event& );

  void lookatRecoMuons( const edm::Event&, const edm::Handle< L1GlobalTriggerReadoutRecord > & );
    
  int getBarrelLayer( const int & , const int &  );
  
  void getRpcTechTriggerBits( const edm::Event & , const edm::EventSetup& );

  void lookatRpcRecHits(const edm::Event& iEvent, const edm::EventSetup& iSetup);
  
  int evaluateDistance( const std::vector<double> & , const std::vector<double> & );

  void lookatMinBiasTracks(const edm::Event & iEvent );

  void applySelection( const edm::Event & iEvent , const edm::Handle< L1GlobalTriggerReadoutRecord > & );
      
  std::vector<int> m_muonType;
    
  std::map<int,int> m_combinations;

  //............................................................................................

  L1TTUTree * m_ntuple;
  
  //............................................................................................
  
  TH1D * m_ttBitsDecision;
  TH1D * m_bxDist;
  TH1D * m_bxNumber;
  TH1D * m_bxDistDiff;
  TH1D * m_qfGMT;
  TH1D * m_gmtFilterDist;
  TH1D * m_bxGTdist;
  TH1D * m_bxGTdistBit24;
  TH1D * m_bxGTdistBit25;
  TH1D * m_bxGTdistSelBit[8];
  TH1D * m_bxDistDiffPac[8];
  TH1D * m_bxDistDiffDt[8];
  TH1D * m_bxGTdistBit[8];
  TH1D * m_trigRateDist[8];
  TH1D * m_trigRateHz[8];
  TH1D * m_bxNumberClose;
  TH1D * m_bxInRpc;
  TH1D * m_bxDistNdecTtu;
  TH1D * m_bxDistDiffPacIC[8];
  TH1D * m_bxDistDiffDtIC[8];
  TH1D * m_bxDistDiffDTPacIC;
  
  TH1D * m_pointingTrack;
  TH1D * m_pointingTrack_0mu;
  TH1D * m_pointingTrack_1mu;
  TH1D * m_pointingTrack_2mu;
  TH1D * m_pointingTrack_3mu;
  TH1D * m_pointingMuon_0mu;
  TH1D * m_pointingMuon_1mu;
  TH1D * m_pointingMuon_2mu;
  TH1D * m_pointingNoRecoTrack;
  TH1D * h_mumu_InvMm;

  TH1D * MuonPt_STA;
  TH1D * MuonEta_STA;
  TH2D * MuonEtaPhi_STA;
  TH1D * MuonPhi_STA;
  TH1D * MuonChi2DoF_STA;
  TH1D * Muond0dist_STA;
  TH1D * Muondszdist_STA;

  TH1D * MuonPt_GBL;
  TH1D * MuonEta_GBL;
  TH2D * MuonEtaPhi_GBL;
  TH1D * MuonPhi_GBL;
  TH1D * MuonChi2DoF_GBL;
  TH1D * Muond0dist_GBL;
  TH1D * Muondszdist_GBL;
  TH1D * MuonPt_GBL_bit25;

  TH1D * MuonPt_TRK;
  TH1D * MuonEta_TRK;
  TH2D * MuonEtaPhi_TRK;
  TH1D * MuonPhi_TRK;
  TH1D * MuonChi2DoF_TRK;
  TH1D * Muond0dist_TRK;
  TH1D * Muondszdist_TRK;
  TH1D * MuonPt_TRK_bit25;
  
  TH1D * MuonType;
  TH1D * NumberMuonsEvt;
  TH1D * MuonCaloCompatibility;



  
  TH1D * m_HMuonSTAPt_Bit[8];
  TH2D * m_HMuonSTAEtaPhi_Bit[8];
  TH1D * m_HMuonSTAPhi_Bit[8];
  TH1D * m_HMuonSTAChi2DoF_Bit[8];
  TH1D * m_HMuonSTAd0dist_Bit[8];
  TH1D * m_HMuonSTAdszdist_Bit[8];
  
  TH1D * m_HMuonGBLPt_Bit[8];
  TH2D * m_HMuonGBLEtaPhi_Bit[8];
  TH1D * m_HMuonGBLPhi_Bit[8];
  TH1D * m_HMuonGBLChi2DoF_Bit[8];
  TH1D * m_HMuonGBLd0dist_Bit[8];
  TH1D * m_HMuonGBLdszdist_Bit[8];

  TH1D * m_HMuonTRKPt_Bit[8];
  TH2D * m_HMuonTRKEtaPhi_Bit[8];
  TH1D * m_HMuonTRKPhi_Bit[8];
  TH1D * m_HMuonTRKChi2DoF_Bit[8];
  TH1D * m_HMuonTRKd0dist_Bit[8];
  TH1D * m_HMuonTRKdszdist_Bit[8];

  TH1D * TrackParticle_Pt;
  TH2D * TrackParticle_EtaPhi;

  TH1D * NumberTracksEvt;
  TH1D * NumberPointingTracksEvt;
  TH1D * NumberPointingTracksEvtBy25;
  TH1D * NumberPointingHitsTrackerEvtByEvt25;

  TH1D * m_total_bit25_triggers;
  TH1D * m_total_bit25_cosmics;

  TH1D * m_pointingTrkCode;
  TH1D * m_pointingTrkCodeIn;

  TH1D * TrackerPt_In_bit25;
  TH1D * TrackerPt_Out_bit25;
  TH1D * TrackerPt_In_CTF_bit25;
  TH1D * TrackerPt_Out_CTF_bit25;
  TH1D * TrackerPt_All_bit25;
  TH1D * m_bxDist2528;
  
  TH2D * m_h_RpcHits_WheelBx[5][7];
  TH2D * m_h_RpcHits_WheelBxTop[5];
  TH2D * m_h_RpcHits_WheelBxBot[5];
  TH2D * m_hh_eta_phi_all_bit25;
  TH2D * m_hh_eta_phi_trk_bit25;
  TH2D * m_hh_eta_phi_ctf_bit25;
  TH2D * m_hh_eta_phi_matchLeg_trk_bit25;
  TH2D * m_hh_eta_phi_matchLeg_ctf_bit25;
  TH2D * m_hh_d0_dz_all_bit25;
  TH2D * m_hh_d0_dz_trk_bit25;
  TH2D * m_hh_d0_dz_ctf_bit25;
  TH2D * m_hh_d0_dz_matchLeg_trk_bit25;
  TH2D * m_hh_d0_dz_matchLeg_ctf_bit25;
  TH2D * m_hh_TwoLegsDifference_bit24;
  TH2D * m_hh_TwoLegsDifference_bit25;
  TH2D * m_hh_xy_inner_bit24;
  TH2D * m_hh_xy_outer_bit24;
  TH2D * m_hh_xy_inner_bit25;
  TH2D * m_hh_xy_outer_bit25;
  TH2D * m_hh_yz_inner_bit24;
  TH2D * m_hh_yz_outer_bit24;
  TH2D * m_hh_yz_inner_bit25;
  TH2D * m_hh_yz_outer_bit25;
  TH2D * m_hh_xy_rpc_rechit[10];
  TH2D * m_hh_yz_rpc_rechit[10];
  TH2D * m_hh_xy_rpc_rechit_All;
  TH2D * m_hh_yz_rpc_rechit_All;
  TH2D * m_hh_bx_rpc_rechit_Bit[10];
  TH2D * m_hh_bx_rpc_rechit_NoBit[10];
  TH2D * m_hh_bx_rpc_rechit_All;
  TH2D * m_hh_bx_rpc_rechit_wheel_Bit[10];
  TH2D * m_bxGTdistTTBits;

  

  TH1D * m_bxDistDiffDTPac;
  TH1D * m_bxDist31;
  TH1D * m_h_RpcHits_Layer[10];
  TH1D * m_h_RpcHits_Sector[10];
  TH1D * m_h_RpcHits_Wheel[10];
  TH1D * m_h_RpcHits_FracStation[4];
  TH1D * m_h_RpcHits_Layer_All;
  TH1D * m_h_RpcHits_Sector_All;
  TH1D * m_h_RpcHits_Wheel_All;
  TH1D * m_bxGTdistTT;
  TH1D * m_bxGTdistTTInTrigger[10];
  TH1D * m_bxGTdistAlg;
  TH1D * m_bxGTdistAlgInTrigger[10];

  TH1D * m_h_pt_HLT_STA;
  TH1D * m_h_pt_TTU_STA;
  
  TH1D * m_h_pt_HLT_GBL;
  TH1D * m_h_pt_TTU_GBL;

  TH1D * m_h_pt_HLT_TRK;
  TH1D * m_h_pt_TTU_TRK;

  TH2D * m_hh_pt_GBL;
  TH2D * m_hh_pt_STA;
  TH2D * m_hh_pt_TRK;
  
  TH1D * m_h_bx_failed_STA;
  TH1D * m_h_bx_failed_GBL;
  TH1D * m_h_bx_failed_TRK;
  

  TH1D * m_h_bit31_Compare[2];

  TH2D * m_bxDistMu55TT25[10];
  
  //............................................................................................

  bool m_hasCoincidence;

  bool m_hasCoincidenceAlgBit;

  bool m_hasActivity_DT;
  
  bool m_was_triggered_Bit31;
  
  int m_maxttBitsTrigger;
  
  int m_maxAlgBitsTrigger;
  
  std::vector<bool> ttVec;

  double m_maxPt;
  
  int m_bxGMT;
  int m_bxFinal;
  int m_maxNBx;
  int m_bxNumMin;
  int m_bxNumMax;
  int m_selFilter;
  bool m_applyFilter;
  int m_EvtWindow;
  int m_useCompression;
  int m_writeMode;
  int m_precision;
  int m_maxRate;
  int m_flag;
  int m_BxWindow;
  int m_maxttBits;
  int m_IsStreamExpress;
  int m_BPTX;

  bool m_tracker_activity;
  
  std::vector<unsigned> m_ttBits;
  std::vector<unsigned> m_ttBitsCollisions;
  std::vector<unsigned> m_makeCoincidenceTT;
  std::vector<unsigned> m_makeCoincidenceAlg;

  int m_readRpcTTEmu;
  
  std::vector<int> m_ntrigger;

  std::vector<int> m_GMTcandidatesBx;
  std::vector<int> m_DTcandidatesBx;
  std::vector<int> m_RPCcandidatesBx;
  
  bool m_wasTtuTrig;

  bool m_has_STA_Muon;
  bool m_has_Global_Muon;
  bool m_has_TRK_Muon;
  
  unsigned int m_firstEvt;
  unsigned int m_lastEvt;
  unsigned int m_nevt;
  unsigned int m_lumiSectionA;
  unsigned int m_lumiSectionB;
  
  double m_muonPtcut;
  
  edm::InputTag m_rpcDigiLabel;
  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_gmtReadoutLabel;
  edm::InputTag m_rpcTechTrigEmu;
  edm::InputTag m_recoMuonLabel;
  edm::InputTag m_recoTracksLabel;
  edm::InputTag m_recoCosmicsLabel;
  edm::InputTag m_hltResultsLabel;

  edm::InputTag m_recoSiStripLabel;
  edm::InputTag m_recoPixelLabel;
    
  std::bitset<9> m_gmtfilter;
  
  std::map<int, std::bitset<4> > m_gmtFlags;
  std::map<int, std::bitset<9> > m_gmtDiscrimination;
  
  HLTConfigProvider m_hltConfig;
  std::vector<std::string> m_checkhltPaths;
  
  std::string m_processName;
  
  std::vector<bool> m_rpcTechBits;
    
  long double m_currentTime;
  long double m_previousTime;
  long double m_totalTime;
  long double m_elapsedTime;

  double m_trackerLength;
  double m_trackerHeight;
    
  bool m_debug;

  bool m_rpcTrigger;
  bool m_dtTrigger;
    
  L1GtExtractedInfo * m_infoObj;

  std::ofstream * fileDump;

  gz::ogzstream * gzfileDump;

  bool m_has_Hits_in_Tracker;
  bool m_apply_Cosmic_Veto;
    
  int m_totalBit25;
  int m_totalBit25Muon;

  int m_GMTproblem;
  std::vector<int> m_singleMuBits;
  int m_maxAlgBits;
  
  TH1D * m_runSummaryA;

  TH1D * m_runSummaryB;
  
  class TrackCone {
  public:

    TrackCone() {;};
    ~TrackCone() {;};
    
    //const math::XYZPoint coneAppex;
    //const math::XYZPoint coneEndPoint;
    //float coneRadius;
    
    
  };//
  
  
};

