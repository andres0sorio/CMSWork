// -*- C++ -*-
//
// Package:    MCHSCPAnalysis
// Class:      MCHSCPAnalysis
// 
/**\class MCHSCPAnalysis MCHSCPAnalysis.cc DTWork/MCHSCPAnalysis/src/MCHSCPAnalysis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Osorio
//         Created:  Thu Jun 30 10:25:30 COT 2011
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
#include "TH1.h"
#include "TH2.h"

//MC data
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

//
// class declaration
//

class MCHSCPAnalysis : public edm::EDAnalyzer {
public:
  explicit MCHSCPAnalysis(const edm::ParameterSet&);
  ~MCHSCPAnalysis();
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------

  edm::InputTag m_mcpartLabel;
  int m_hscpId;
  
  //Histogramas

  TH1F * h_mcbeta;
  TH1F * h_mceta;
  TH1F * h_mcphi;
  TH1F * h_mcpt;
  TH1F * h_mcmm;
  TH1F * h_mce;
  TH1F * h_mcmagp;

};

