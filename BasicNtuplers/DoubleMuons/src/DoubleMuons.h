// -*- C++ -*-
//
// Package:    DoubleMuons
// Class:      DoubleMuons
// 
/**\class DoubleMuons DoubleMuons.cc BasicNtuplers/DoubleMuons/src/DoubleMuons.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Osorio
//         Created:  Mon May 28 13:32:18 COT 2012
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
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//...ROOT and File servies
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>

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

//
// class declaration
//

const int kMaxparticles = 5;

class DoubleMuons : public edm::EDAnalyzer {
public:
  explicit DoubleMuons(const edm::ParameterSet&);
  ~DoubleMuons();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  // ----------member data ---------------------------

  TH1F * h_nMuons;
  TH1F * h_MuonsInv;

  edm::InputTag m_trackLabel;
  edm::InputTag m_muonLabel; 

  bool m_debug;

  TTree * m_tree;
  
  TFile * m_outfile;
  
  int nmuons;
  float muons_fPx[5];     //[muons_]
  float muons_fPy[5];     //[muons_]
  float muons_fPz[5];     //[muons_]
  float muons_fE[5];      //[muons_]
  float muons_fC[5];      //[muons_]
  float muons_fEta[5];    //[muons_]

};
