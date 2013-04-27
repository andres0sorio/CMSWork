// -*- C++ -*-
//
// Package:    DQMTtuAnalyzer
// Class:      DQMTtuAnalyzer
// 
/**\class DQMTtuAnalyzer DQMTtuAnalyzer.cc StudyL1Trigger/DQMTtuAnalyzer/src/DQMTtuAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Wed Sep 30 09:32:55 CEST 2009
// $Id: DQMTtuAnalyzer.h,v 1.1 2009/10/08 15:12:10 aosorio Exp $
//
//


// system include files
#include <memory>

//... User include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


//... L1Trigger

#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h>
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"
#include <DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h>

//... Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

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

//...
#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TList.h"
//
// class declaration
//

class DQMTtuAnalyzer : public edm::EDAnalyzer {
public:
  explicit DQMTtuAnalyzer(const edm::ParameterSet&);
  ~DQMTtuAnalyzer();
  
  int  discriminateGMT( const edm::Event& iEvent, const edm::EventSetup& iSetup );

  void discriminateDecision( bool ,  bool , int );
  
  void setCanvasOptions( TCanvas * );
    
private:
  virtual void beginJob();
  virtual void beginRun(const edm::EventSetup&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  

  TH1D * m_ttBitsDecisionData;
  TH1D * m_ttBitsDecisionEmulator;
  TH1D * m_bxDistDiffPac[8];
  TH1D * m_bxDistDiffDt[8];
  TH1D * m_dataVsemulator[8];
  
  TCanvas * m_combinedTTbits;
  
  int m_maxttBits;
  std::vector<unsigned> m_ttBits;

  bool m_dtTrigger;
  bool m_rpcTrigger;

  std::vector<int> m_GMTcandidatesBx;
  std::vector<int> m_DTcandidatesBx;
  std::vector<int> m_RPCcandidatesBx;

  edm::InputTag m_rpcDigiLabel;
  edm::InputTag m_gtReadoutLabel;
  edm::InputTag m_gmtReadoutLabel;
  edm::InputTag m_rpcTechTrigEmu;
  
};

