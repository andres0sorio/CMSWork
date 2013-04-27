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


// user include files


#include "HLTfilters/PointingCosmic/interface/PointingCosmic.h"

//
// constructors and destructor
//
PointingCosmic::PointingCosmic(const edm::ParameterSet& iConfig)
{
  
  
  
}


PointingCosmic::~PointingCosmic()
{
  
}

// ------------ method called on each new Event  ------------
bool
PointingCosmic::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  
  
  return true;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
PointingCosmic::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void 
PointingCosmic::endJob() 
{

}

//define this as a plug-in
DEFINE_FWK_MODULE(PointingCosmic);
