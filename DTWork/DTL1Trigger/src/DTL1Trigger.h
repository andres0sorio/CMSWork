// -*- C++ -*-
//
// Package:    DTL1Trigger
// Class:      DTL1Trigger
// 
/**\class DTL1Trigger DTL1Trigger.cc DTWork/DTL1Trigger/src/DTL1Trigger.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Osorio,,,
//         Created:  Thu Mar 10 06:50:15 COT 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>

#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/MakerMacros.h>

#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include <FWCore/ServiceRegistry/interface/Service.h>
#include <CommonTools/UtilAlgos/interface/TFileService.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include "EventInfo.h"

//...FOR L1 trigger access
#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h>

#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h>
#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h>
#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h>

#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"

#include "DataFormats/DTDigi/interface/DTLocalTriggerCollection.h"

//Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

//...FOR HLT trigger access
#include <HLTrigger/HLTcore/interface/HLTConfigProvider.h>

//#include <FWCore/Framework/interface/TriggerNames.h>
#include <DataFormats/Common/interface/TriggerResults.h>

//...Tracker
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"

//...DT
#include "DataFormats/DTDigi/interface/DTDigiCollection.h"
#include "DataFormats/DTDigi/interface/DTLocalTriggerCollection.h"
#include <DataFormats/DTRecHit/interface/DTRecHit1D.h>

//#include "DQM/DTMonitorModule/interface/DTTrigGeomUtils.h"
#include "DTTrigGeomUtilsExt.h"

// DT Geometry
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/DTGeometry/interface/DTLayer.h"
#include "Geometry/DTGeometry/interface/DTTopology.h"

//... Det/MuonDet
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"

//... Geometry

#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include <DataFormats/GeometryVector/interface/GlobalPoint.h>
#include <DataFormats/GeometryVector/interface/Pi.h>
#include <DataFormats/GeometrySurface/interface/LocalError.h>
#include <DataFormats/GeometrySurface/interface/Surface.h>

//
// class declaration
//

class DTL1Trigger : public edm::EDAnalyzer {
public:
  explicit DTL1Trigger(const edm::ParameterSet&);
  ~DTL1Trigger();
  
  
private:
  virtual void beginJob() ;
  virtual void beginRun(const edm::Run& , const edm::EventSetup&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  TH1D * h_rpcBx;
  TH1D * h_dtBx;
  TH1D * h_dtQual;
  TH1D * h_dtTime;
  TH1D * h_diffBxAssignment;
  TH2D * h_diffBxAssignmentVsQual;

  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_gmtReadoutLabel;
  edm::InputTag m_hltResultsLabel;
  edm::InputTag m_trackLabel;
  edm::InputTag m_dtChambPhLabel;
  edm::InputTag m_dtlocaltrigLabel;
  
  bool m_debug;
  bool m_noL1info;
  bool m_noHLTinfo;
  bool m_noGMTinfo;
  bool m_noTrackinfo;
  
  edm::ESHandle<DTGeometry> muonGeom;

  DTTrigGeomUtilsExt* trigGeomUtils;

  TTree *m_tree;
  TFile *m_outFile;

  float m_xi;
  float m_yi;
  float m_lr;
  float m_time;
  int   m_trk;
  int   m_wh;
  int   m_st;
  int   m_sc;
  int   m_lyr;
  int   m_sly;
  float m_trkchi2;
  int   m_trkchg;

  unsigned int m_evt;

};
