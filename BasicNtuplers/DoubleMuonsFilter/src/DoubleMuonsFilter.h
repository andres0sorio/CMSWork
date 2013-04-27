// -*- C++ -*-
//
// Package:    DoubleMuonsFilter
// Class:      DoubleMuonsFilter
// 
/**\class DoubleMuonsFilter DoubleMuonsFilter.cc BasicNtuplers/DoubleMuonsFilter/src/DoubleMuonsFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Osorio
//         Created:  Tue May 29 08:07:31 COT 2012
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

class DoubleMuonsFilter : public edm::EDFilter {
   public:
      explicit DoubleMuonsFilter(const edm::ParameterSet&);
      ~DoubleMuonsFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
};
