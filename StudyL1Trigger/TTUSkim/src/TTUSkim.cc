// user include files
#include "StudyL1Trigger/TTUSkim/src/TTUSkim.h"

//... HLT
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//

TTUSkim::TTUSkim(const edm::ParameterSet& iConfig)
{
  
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_hltResultsLabel    = iConfig.getParameter<edm::InputTag>("TriggerResultsLabel");
  m_lumiSection        = iConfig.getUntrackedParameter<int>("LumiSection", 0);
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers");
  m_makeCoincidenceTT  = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceTT");
  m_makeCoincidenceAlg = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceAlgo");
  m_makeCoincidenceHLT = iConfig.getParameter< std::vector<std::string> >("MakeCoincidenceHLT");
  m_disableTTUbits     = iConfig.getUntrackedParameter<bool>("DisableTTUBits", 0);
  m_processName        = iConfig.getUntrackedParameter<std::string>("ProcessName", "HLT");

  m_totalEvts = 0;
  
  m_totalFilter = 0;
  
}

TTUSkim::~TTUSkim()
{
 

}

// ------------ method called on each new Event  ------------
bool
TTUSkim::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //..............................................................................................
  
  unsigned int lumiSec = iEvent.luminosityBlock();
  
  if ( lumiSec < m_lumiSection )
    return false;

  ++m_totalEvts;
  
  //..............................................................................................
  
  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( m_gtReadoutLabel, gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "L1GtTtuAnalyzer" << "can't find L1GlobalTriggerRecord with label: " 
              << m_gtReadoutLabel << '\n';
    return false;
  }
  
  //..............................................................................................
  
  m_TTUBits[0].reset();
  m_TTUBits[1].reset();
  m_TTUBits[2].reset();

  std::vector<unsigned>::iterator bitItr;
  
  for( int iebx=0; iebx < 5; iebx++) {
    
    const TechnicalTriggerWord wTWord = gtRecord->technicalTriggerWord( iebx-2 );
    
    int k=0;
    for( bitItr = m_ttBits.begin(); bitItr != m_ttBits.end(); ++bitItr) {
      bool ttBitResult = wTWord.at( (*bitItr) );
      m_TTUBits[iebx].set( k, ttBitResult );
      ++k;
    }
    
  }
  
  //..............................................................................................

  //... use additional selection
  
  //.. on technical trigger bits
  bool hasTTInCoincidence = false;

  const TechnicalTriggerWord ttWord = gtRecord->technicalTriggerWord(); // before Mask, size=64
  
  if ( m_makeCoincidenceTT.size() <= 0 )
    hasTTInCoincidence = true;
  
  for( bitItr = m_makeCoincidenceTT.begin(); bitItr != m_makeCoincidenceTT.end(); ++bitItr) {
    bool ttBitResult = ttWord.at( (*bitItr) );
    hasTTInCoincidence |= ttBitResult;
  }
  
  //.. on algo trigger bits
  
  const DecisionWord unmaskedAlgWord = gtRecord->decisionWord();
  
  bool hasAlgBitInCoincidence = false;
  
  if ( m_makeCoincidenceAlg.size() <= 0 )
    hasAlgBitInCoincidence = true;
  
  for( bitItr = m_makeCoincidenceAlg.begin(); bitItr != m_makeCoincidenceAlg.end(); ++bitItr ) {
    bool bitResult = unmaskedAlgWord.at( (*bitItr) );
    hasAlgBitInCoincidence |= bitResult;
  }

  //..............................................................................................
  
  //... keep only events where TTU fired a trigger in the [-1,1] window
  bool hasTTUbits = false;
  
  for( int iebx=0; iebx<=2; iebx++) {
    if( m_TTUBits[iebx].any() )
      hasTTUbits |= true;
    
  }

  if( m_disableTTUbits ) hasTTUbits = true;

  //..............................................................................................
  // HLT selection

  edm::Handle< edm::TriggerResults > triggerResultsHandle;
  iEvent.getByLabel( m_hltResultsLabel, triggerResultsHandle);
  
  if ( !triggerResultsHandle.isValid()) {
    std::cout << "L1GtTtuAnalyzer" << "can't find TriggerResults with label: " 
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
  
  if ( m_makeCoincidenceHLT.size() <= 0 ) m_HLTBits = true;
  
  //std::cout << hasTTUbits << " " 
  //          << hasTTInCoincidence << " "
  //          << hasAlgBitInCoincidence << " "
  //          << m_HLTBits << '\n';
  
  //..............................................................................................
  
  if ( hasTTUbits && hasTTInCoincidence && hasAlgBitInCoincidence && m_HLTBits ) {
    ++m_totalFilter;
    return true;
  }
  
  //..............................................................................................
  
  return false;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
TTUSkim::beginJob()
{
  m_hltConfig.init( m_processName );
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TTUSkim::endJob() {

  std::cout << "TTUSkim::endJob> T:" 
            << m_totalEvts << " F:"
            << m_totalFilter << "\n";
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(TTUSkim);
