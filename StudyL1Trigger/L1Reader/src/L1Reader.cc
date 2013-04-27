// -*- C++ -*-
//
// Package:    L1Reader
// Class:      L1Reader
// 
/**\class L1Reader L1Reader.cc StudyL1Trigger/L1Reader/src/L1Reader.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Fri Feb  6 09:10:11 CET 2009
// $Id$
//
//
#include "StudyL1Trigger/L1Reader/src/L1Reader.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

//
// constructors and destructor
//

L1Reader::L1Reader(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  
}


L1Reader::~L1Reader()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}

//
// member functions
//

// ------------ method called to for each event  ------------
void L1Reader::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  std::cout << "L1Reader> looking at event: " << std::endl;


  //...method one:
  //bool algResult = l1AlgorithmResult(iEvent, iSetup, algoName);
  //std::cout << "L1Reader>: L1GMT algorithm results:" << algResult << std::endl;
  
  //...method two:
  
  edm::ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
  const L1GtTriggerMenu* menu = menuRcd.product();

  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( edm::InputTag("gtDigis"), gtRecord);
  const DecisionWord dWord = gtRecord->decisionWord();  
  // this will get the decision word *before* masking disabled bits

  std::cout << "L1Reader> DecisionWord size(): " << dWord.size() << std::endl;

  std::vector<bool>::const_iterator itr;
  
  for(itr=dWord.begin(); itr!=dWord.end();++itr){
    
    std::cout << "L1Reader> DecisionWord: \t"
              << (*itr) << '\n';
        
  }
  
  //...example: all muon related bits:
  //bool l1SingleEG15 = menu->gtAlgorithmResult( "L1_SingleEG15", dWord);

  const TechnicalTriggerWord tWord = gtRecord->technicalTriggerWord();
  
  std::cout << "TechnicalTriggerWord: \t"
            << tWord.at(24) << '\t'
            << tWord.at(25) << '\t'
            << tWord.at(26) << '\t'
            << tWord.at(27) << '\t'
            << tWord.at(28) << '\t';
  
  std::cout << '\n';

  std::cout << "L1Reader> end of event processing" << std::endl;
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
L1Reader::beginJob(const edm::EventSetup& evSetup)
{
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1Reader::endJob() {

}

//define this as a plug-in
DEFINE_FWK_MODULE(L1Reader);
