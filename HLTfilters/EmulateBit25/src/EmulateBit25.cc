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

#include "HLTfilters/EmulateBit25/interface/EmulateBit25.h"

//
// constructors and destructor
//
EmulateBit25::EmulateBit25(const edm::ParameterSet& iConfig)
{

  //register your products
  /* Examples
     produces<ExampleData2>();
     
     //if do put with a label
     produces<ExampleData2>("label");
  */
  //now do what ever other initialization is needed
  
}


EmulateBit25::~EmulateBit25()
{
  
}


// ------------ method called to produce the data  ------------
void
EmulateBit25::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  using namespace edm;
  /* This is an event example
  //Read 'ExampleData' from the Event
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
  
  //Use the ExampleData to create an ExampleData2 which 
  // is put into the Event
  std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
  iEvent.put(pOut);
  */
  
  /* this is an EventSetup example
  //Read SetupData from the SetupRecord in the EventSetup
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
  */
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
EmulateBit25::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void 
EmulateBit25::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(EmulateBit25);
