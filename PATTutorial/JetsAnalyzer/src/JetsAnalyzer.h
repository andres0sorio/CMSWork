// -*- C++ -*-
//
// Package:    JetsAnalyzer
// Class:      JetsAnalyzer
// 
/**\class JetsAnalyzer JetsAnalyzer.cc PATTutorial/JetsAnalyzer/src/JetsAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Sat Jan 31 15:39:08 CET 2009
// $Id$
//
//


// system include files
#include <memory>
#include <map>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/InputTag.h"

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

// from ROOT

#include "TH1D.h"


//
// class decleration
//

class JetsAnalyzer : public edm::EDAnalyzer {

public:

  explicit JetsAnalyzer(const edm::ParameterSet&);
  ~JetsAnalyzer();
  
  
private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  TH1D * njets;
  TH1D * njetscut;
  TH1D * nelectrons;
  TH1D * deltaR;
  TH1D * eclosestEl;
  TH1D * eclosertEloJet;
  TH1D * emfraction;
  TH1D * trkisolation;
  TH1D * totaljetenergy;
  TH1D * totaljetenergysum;
  TH1D * overlapjet;
  
  edm::InputTag eleLabel_;
  edm::InputTag muoLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag tauLabel_;
  edm::InputTag metLabel_;
  edm::InputTag phoLabel_;

  int findClosest( const std::vector<float> & );

  void doExercise1( const edm::Event&, const edm::EventSetup&);

  void doExercise2( const edm::Event&, const edm::EventSetup&);
  
  bool m_useflaggedJets;
    
};

