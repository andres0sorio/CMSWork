// -*- C++ -*-
//
// Package:    L1Writer
// Class:      L1Writer
// 
/**\class L1Writer L1Writer.cc StudyL1Trigger/L1Writer/src/L1Writer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Wed May  6 13:38:20 CEST 2009
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

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"

#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

//
// class decleration
//

class L1Writer : public edm::EDProducer {
public:
  explicit L1Writer(const edm::ParameterSet&);
  ~L1Writer();
  
private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  
  std::vector<unsigned> ttBits_;
  std::vector<std::string> names_;
  
  int nevt;
  
};

L1Writer::L1Writer(const edm::ParameterSet& iConfig)
{
  
  nevt = 0;
  
  ttBits_=iConfig.getParameter< std::vector<unsigned> >("bitNumbers");
  names_= iConfig.getParameter< std::vector<std::string> >("bitNames");

  //register your products, and/or set an "alias" label
  produces<L1GtTechnicalTriggerRecord>();
  
}


L1Writer::~L1Writer()
{
 
   //
  
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
L1Writer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //Use the ExampleData to create an ExampleData2 which 
  //is put into the Event

  std::cout << "loop over event starts: " << ttBits_.size() << std::endl;
    
  std::vector<L1GtTechnicalTrigger> ttVec(ttBits_.size());

  //edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  //iEvent.getByLabel( edm::InputTag("gtDigis"), gtRecord);
  //const TechnicalTriggerWord tWord = gtRecord->technicalTriggerWord();
  
  std::auto_ptr<L1GtTechnicalTriggerRecord> output(new L1GtTechnicalTriggerRecord());
  
  int bx = 0;
  bool bit = true;
  
  for(int i = 0; i < 5; ++i) {
    std::cout << "writing to ttVec starts" << std::endl;
    std::cout << names_.at(i) << " " << ttBits_.at(i) << " " << bx << " " << bit << std::endl;
    ttVec.at(i)=L1GtTechnicalTrigger(names_.at(i), ttBits_.at(i), bx, bit) ;
    std::cout << "writing to ttVec ends" << std::endl;
  }
  
  output->setGtTechnicalTrigger(ttVec);    
  
  std::cout << "put to event: " << &output << std::endl;
  
  iEvent.put(output);
  
  std::cout << "loop over event ends" << std::endl;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
L1Writer::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1Writer::endJob() {

}

//define this as a plug-in
DEFINE_FWK_MODULE(L1Writer);
