// -*- C++ -*-
//
// Package:    DTRecSeg2DAnalysis
// Class:      DTRecSeg2DAnalysis
// 
/**\class DTRecSeg2DAnalysis DTRecSeg2DAnalysis.cc DTWork/DTRecSeg2DAnalysis/src/DTRecSeg2DAnalysis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Osorio
//         Created:  Tue Sep  6 14:33:54 COT 2011
// $Id$
//
//


// system include files
#include <memory>

//...Framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/ServiceRegistry/interface/Service.h>

//...ROOT and File servies

#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
//...Tracker
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/TrackReco/interface/TrackExtraFwd.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"

//...DT
#include "DataFormats/DTDigi/interface/DTDigiCollection.h"
#include "DataFormats/DTDigi/interface/DTLocalTriggerCollection.h"
#include <DataFormats/DTRecHit/interface/DTRecHit1D.h>

//...Muon
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "RecoMuon/TrackingTools/interface/MuonSegmentMatcher.h"
#include "RecoMuon/TrackingTools/interface/MuonServiceProxy.h"
#include "RecoMuon/MuonIdentification/interface/TimeMeasurementSequence.h"

// Geometry Tools + DT Geometry
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/DTGeometry/interface/DTLayer.h"
#include "Geometry/DTGeometry/interface/DTTopology.h"

//...Det/MuonDet
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"

//...Geometry
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include <DataFormats/GeometryVector/interface/GlobalPoint.h>
#include <DataFormats/GeometryVector/interface/Pi.h>
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometrySurface/interface/Surface.h>

//...GenParticle
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

//
// class declaration
//

class MuonServiceProxy;

class DTRecSeg2DAnalysis : public edm::EDAnalyzer {
public:
  
  explicit DTRecSeg2DAnalysis(const edm::ParameterSet&);
  ~DTRecSeg2DAnalysis();
  
  
private:
  
  virtual void beginJob() ;
  virtual void beginRun(const edm::Run& , const edm::EventSetup&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  

  // ----------member data ---------------------------

  edm::InputTag m_trackLabel;
  
  edm::InputTag m_muonLabel;

  edm::InputTag m_DTSegmentLabel;

  edm::InputTag m_partLabel;
  
  std::vector<int> m_hscpId;

  MuonServiceProxy * m_MuonServiceProxy;
  
  MuonSegmentMatcher * m_MuonSegMatcher;
  
  edm::ESHandle<DTGeometry> m_DTGeom;

  TH1D * h_beta;
  TH1D * h_momentum;
  TH1D * h_phi;
  TH1D * h_eta;
  TH1D * h_momentumtrans;
  TH1D * h_energy;

  TH1D * h_beta_beta;
  TH1D * h_momentum_beta;
  TH1D * h_phi_beta;
  TH1D * h_eta_beta;
  TH1D * h_momentumtrans_beta;
   
  TH1D * h_mass;

  TH1D * h_tseg_station1;
  TH1D * h_tseg_station2;
  TH1D * h_tseg_station3;
  TH1D * h_tseg_station4;
  TH1D * h_t0seg_st1;
  TH1D * h_t0seg_st2;
  TH1D * h_t0seg_st3;
  TH1D * h_t0seg_st4;

  TH1D * h_chi2;

  TH1F * h_mcbeta;
  TH1F * h_mceta;
  TH1F * h_mcphi;
  TH1F * h_mcpt;
  TH1F * h_mcmm;
  TH1F * h_mce;
  TH1F * h_mcmagp;

  TH1F * h_diffphi;
  TH1F * h_diffeta;
  TH1F * h_diffbeta;
  TH1F * h_diffp;
  TH1F * h_diffphi_beta;
  TH1F * h_diffeta_beta;
  TH1F * h_diffbeta_beta;
  TH1F * h_diffp_beta;

  bool m_debug;
  

};

