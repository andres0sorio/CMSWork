// -*- C++ -*-
//
// Package:    ZMuMuAnalyzer
// Class:      ZMuMuAnalyzer
// 
/**\class ZMuMuAnalyzer ZMuMuAnalyzer.cc PATTutorial/ZMuMuAnalyzer/src/ZMuMuAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Sun Feb  8 19:50:51 CET 2009
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
#include "FWCore/ParameterSet/interface/InputTag.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

// from physics Tools:

#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

// dataformats
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/Common/interface/View.h"

//from ROOT
#include "TH1.h"

//
// class declaration
//

class ZMuMuAnalyzer : public edm::EDAnalyzer {
public:
  explicit ZMuMuAnalyzer(const edm::ParameterSet&);
  ~ZMuMuAnalyzer();
  
  
private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  TH1D * m_hdeltaR; 
  TH1D * m_hdeltaPt;
  TH1D * m_hnmuons;
  
  edm::InputTag muoLabel_;
  



};

