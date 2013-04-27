// -*- C++ -*-
//
// Package:    PATCosmicStudy
// Class:      PATCosmicStudy
// 
/**\class PATCosmicStudy PATCosmicStudy.cc StudyL1Trigger/PATCosmicStudy/src/PATCosmicStudy.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Tue Sep  8 22:52:40 CEST 2009
// $Id$
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
//#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//
#include "DataFormats/Common/interface/OwnVector.h"
#include "DataFormats/Common/interface/AssociationVector.h"

//#include "DataFormats/PatCandidates/interface/TriggerPrimitive.h"

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

//root 

#include "TH1D.h"
#include "TH2D.h"

//

class PATCosmicStudy : public edm::EDAnalyzer {

public:
  explicit PATCosmicStudy(const edm::ParameterSet&);
  ~PATCosmicStudy();
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  edm::InputTag m_muonLabel;
  edm::InputTag m_jetsLabel;

  edm::InputTag m_rpcDigiLabel;
  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_gmtReadoutLabel;
  edm::InputTag m_rpcTechTrigEmu;
  
  int m_maxttBits;
  std::vector<unsigned> m_ttBits;
  
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
    
  TH1D * m_HMuonPt[8];
  TH1D * m_HMuonEta[8];
  TH2D * m_HMuonEtaPhi[8];
  TH1D * m_HMuonPhi[8];
  TH1D * m_HMuonChi2DoF[8];
  TH1D * m_HMuond0dist[8];
  TH1D * m_HMuondszdist[8];
  TH1D * m_HMuond0dist_GBL[8];
  TH1D * m_HMuondszdist_GBL[8];

  TH1D * NumberJetsEvt;
  TH2D * JetsEtaPhi;
  TH2D * JetsEtaPt;
    
};

