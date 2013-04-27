// -*- C++ -*-
//
// Package:    TTUTiming
// Class:      TTUTiming
// 
/**\class TTUTiming TTUTiming.cc StudyL1Trigger/TTUTiming/src/TTUTiming.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Mon Feb  1 13:46:59 CET 2010
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
//
// class decleration
//

class TTUTiming : public edm::EDAnalyzer {
   public:
      explicit TTUTiming(const edm::ParameterSet&);
      ~TTUTiming();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
};

