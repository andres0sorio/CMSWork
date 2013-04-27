// -*- C++ -*-
//
// Package:    TestWriter
// Class:      TestWriter
// 
/**\class TestWriter TestWriter.cc StudyL1Trigger/TestWriter/src/TestWriter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Thu May  7 18:59:19 CEST 2009
// $Id$
//
//


// system include files
#include <memory>

// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"


#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>


//
// class decleration
//

class TestWriter : public edm::EDAnalyzer {
   public:
      explicit TestWriter(const edm::ParameterSet&);
      ~TestWriter();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
};

//
// constructors and destructor
//

TestWriter::TestWriter(const edm::ParameterSet& iConfig)

{

  




}


TestWriter::~TestWriter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TestWriter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  std::cout << "TestWriter> looking at event: " << std::endl;

  edm::Handle<L1GtTechnicalTriggerRecord> gtRecord;
  iEvent.getByLabel( edm::InputTag("myProducerLabel"), gtRecord);
  
  std::vector<bool>::const_iterator itr;

  if (!gtRecord.isValid()) {
    std::cout << "requested in configuration, but not found in the event"
              << std::endl;
  } else {

    const std::vector<L1GtTechnicalTrigger>& ttVec =
      gtRecord->gtTechnicalTrigger();
    size_t ttVecSize = ttVec.size();

    std::cout << "ttVec size: " << ttVecSize << std::endl;
    
    for (size_t i = 0; i < ttVecSize; ++i) {

      const L1GtTechnicalTrigger& ttBxRecord = ttVec[i];
      int ttBxInEvent = ttBxRecord.bxInEvent();

      if (ttBxInEvent == 0) {
        int ttBitNumber = ttBxRecord.gtTechnicalTriggerBitNumber();
        bool ttResult = ttBxRecord.gtTechnicalTriggerResult();
        std::cout << "ttBitNum: " <<  ttBitNumber << " result: " << ttResult << std::endl;
        
      }
            
    }
    
  }
  
  
  std::cout << "TestWriter> end of event processing" << std::endl;


}


// ------------ method called once each job just before starting event loop  ------------
void 
TestWriter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TestWriter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TestWriter);
