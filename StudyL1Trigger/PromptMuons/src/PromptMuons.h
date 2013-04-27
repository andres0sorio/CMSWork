// -*- C++ -*-
//
// Package:    PromptMuons
// Class:      PromptMuons
// 
/**\class PromptMuons PromptMuons.cc StudyL1Trigger/PromptMuons/src/PromptMuons.h

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Sun Nov 29 21:50:06 CET 2009
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
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Math/interface/LorentzVector.h"

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


//GT
#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h>
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

//GMT
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"
#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h>

//Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TH1D.h"
#include "TH2D.h"

class PromptMuons : public edm::EDAnalyzer {
public:
  explicit PromptMuons(const edm::ParameterSet&);
  ~PromptMuons();
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  void lookatRpcRecHits(const edm::Event& iEvent, const edm::EventSetup& iSetup);
    
  int getBarrelLayer( const int & _layer, const int & _station );
  
  // ----------member data ---------------------------
  TH1D * m_bxDistEvent;
  TH1D * m_bxDist[10];
  TH2D * m_bxWindowDist[10];
  
  //RPC plots
  
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



  edm::InputTag m_gtReadoutLabel;

  int m_maxttBits;
  std::vector<unsigned> m_ttBits;
  
  std::vector<bool> ttVec;


};

