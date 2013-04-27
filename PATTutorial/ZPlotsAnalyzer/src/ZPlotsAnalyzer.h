// -*- C++ -*-
//
// Package:    ZPlotsAnalyzer
// Class:      ZPlotsAnalyzer
// 
/**\class ZPlotsAnalyzer ZPlotsAnalyzer.cc PATTutorial/ZPlotsAnalyzer/src/ZPlotsAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Thu Jan 29 17:27:36 CET 2009
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
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "PATTutorial/ZPlotsAnalyzer/src/ZPlots.h"

//
// class declaration
//

class ZPlotsAnalyzer : public edm::EDAnalyzer {
public:
  explicit ZPlotsAnalyzer(const edm::ParameterSet&);
  ~ZPlotsAnalyzer();
  
  
private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  ZPlots *histo;
  
  
};

