// -*- C++ -*-
//
// Package:    Bit25Skim
// Class:      Bit25Skim
// 
/**\class Bit25Skim Bit25Skim.cc StudyL1Trigger/Bit25Skim/src/Bit25Skim.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Felipe Osorio Oliveros,512 1-009,+41227670491,
//         Created:  Fri May 21 11:27:01 CEST 2010
// $Id$
//
//

#include "StudyL1Trigger/Bit25Skim/src/Bit25Skim.h"

//... HLT
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//
// constructors and destructor
//

Bit25Skim::Bit25Skim(const edm::ParameterSet& iConfig)
{
  
  //now do what ever initialization is needed
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_hltResultsLabel    = iConfig.getParameter<edm::InputTag>("TriggerResultsLabel");
  m_recoTracksLabel    = iConfig.getParameter<edm::InputTag>("TrackerLabel");
  
  m_lumiSection        = iConfig.getUntrackedParameter<int>("LumiSection", 0);
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers");
  m_makeCoincidenceTT  = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceTT");
  m_makeCoincidenceHLT = iConfig.getParameter< std::vector<std::string> >("MakeCoincidenceHLT");
  m_disableTTUbits     = iConfig.getUntrackedParameter<bool>("DisableTTUBits", 0);
  m_requireTracker     = iConfig.getUntrackedParameter<bool>("RequireTrackerInfo", 0);
  m_processName        = iConfig.getUntrackedParameter<std::string>("ProcessName", "HLT");
  
  m_totalEvts = 0;
  m_totalFilter = 0;

}


Bit25Skim::~Bit25Skim()
{
 

}

// ------------ method called on each new Event  ------------
bool
Bit25Skim::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //..............................................................................................
  //... check first if thers is Bit25 trigger

  unsigned int lumiSec = iEvent.luminosityBlock();
  
  if ( lumiSec < m_lumiSection )
    return false;

  ++m_totalEvts;

  //..............................................................................................

  // HLT selection

  edm::Handle< edm::TriggerResults > triggerResultsHandle;
  iEvent.getByLabel( m_hltResultsLabel, triggerResultsHandle);
  
  if ( !triggerResultsHandle.isValid()) {
    std::cout << "Bit25Skim> can't find TriggerResults with label: " 
              <<  m_hltResultsLabel << '\n';
    return false;
  }
  
  //..............................................................................................
  
  bool m_HLTBits = false;
  
  std::vector<std::string> triggerNames;
  const edm::TriggerResults *triggerResults = triggerResultsHandle.product();
  std::vector<std::string>::iterator hltItr;

  int AcceptsSum = 0;
  
  for(uint i=0; i< m_hltConfig.size(); ++i){
    std::string trigger = m_hltConfig.triggerName(i);
    for( hltItr = m_makeCoincidenceHLT.begin(); hltItr != m_makeCoincidenceHLT.end(); ++hltItr) {
      if( trigger.find ( (*hltItr) ) != std::string::npos)
        triggerNames.push_back(trigger);
    }
  }
  
  for( hltItr = triggerNames.begin(); hltItr != triggerNames.end(); ++hltItr) {
    
    const unsigned int triggerIndex( m_hltConfig.triggerIndex( (*hltItr) )); 
    if (triggerIndex < m_hltConfig.size() ) {
      AcceptsSum += triggerResults->accept(triggerIndex);
    }
    
  }
  
  if ( AcceptsSum >= 1 ) m_HLTBits = true;
  triggerNames.clear();

  //std::cout << "Bit25Skim> tracker cosmic accepted: " << m_HLTBits << std::endl;
    
  if ( m_makeCoincidenceHLT.size() <= 0 ) m_HLTBits = true;

  //..............................................................................................
  //... is there tracker info
  
  //
  // Tracker: Only for Cosmics samples
  
  edm::Handle< edm::View<reco::Track> > tracksHandle;
  iEvent.getByLabel(m_recoTracksLabel, tracksHandle);
  
  if ( ! tracksHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the tracks Handle"  << std::endl;
    return false;
  }
  
  //.................................................................................................................
  
  //bool isInTracker(false);
  
  if ( tracksHandle->size() > 0 ) m_Trkc = true;
  else m_Trkc = false;
    
  if ( ! m_requireTracker ) m_Trkc = ! m_Trkc; //flip the if there is no tracker info
  
  bool final_result = m_HLTBits && ( m_Trkc );
  
  return final_result;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
Bit25Skim::beginJob()
{

  m_hltConfig.init( m_processName );

}

// ------------ method called once each job just after ending the event loop  ------------
void 
Bit25Skim::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(Bit25Skim);
