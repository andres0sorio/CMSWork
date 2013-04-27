// -*- C++ -*-
//
// Package:    UTAnalyzer
// Class:      UTAnalyzer
// 
/**\class UTAnalyzer UTAnalyzer.cc SUSYAnalyzers/UTAnalyzer/src/UTAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Osorio
//         Created:  Thu Jul  7 23:20:42 COT 2011
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
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"

//
// class declaration
//

class UTAnalyzer : public edm::EDAnalyzer {
public:
  explicit UTAnalyzer(const edm::ParameterSet&);
  ~UTAnalyzer();
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------

  // histograms
  std::map<std::string, TH1F*> h_1DHistContainer;
  std::map<std::string, TH2F*> h_2DHistContainer;
  
  // input tags
  edm::InputTag m_muonSrc;
  edm::InputTag m_jetSrc;
  edm::InputTag m_metSrc;

  
};

