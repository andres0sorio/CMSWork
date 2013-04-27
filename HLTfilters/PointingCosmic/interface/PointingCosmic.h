// -*- C++ -*-
//
// Package:    PointingCosmic
// Class:      PointingCosmic
// 
/**\class PointingCosmic PointingCosmic.cc HLTfilters/PointingCosmic/src/PointingCosmic.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Felipe Osorio Oliveros,512 1-009,+41227670491,
//         Created:  Tue Mar 16 22:35:31 CET 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//
// class declaration
//

class PointingCosmic : public edm::EDFilter {
   public:
      explicit PointingCosmic(const edm::ParameterSet&);
      ~PointingCosmic();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
};

