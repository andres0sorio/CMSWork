// -*- C++ -*-
//
// Package:    EmulateBit25
// Class:      EmulateBit25
// 
/**\class EmulateBit25 EmulateBit25.cc HLTfilters/EmulateBit25/src/EmulateBit25.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Felipe Osorio Oliveros,512 1-009,+41227670491,
//         Created:  Tue Mar 16 22:41:26 CET 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


//
// class declaration
//

class EmulateBit25 : public edm::EDProducer {
   public:
      explicit EmulateBit25(const edm::ParameterSet&);
      ~EmulateBit25();

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
};

