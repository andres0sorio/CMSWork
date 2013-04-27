// user include files
#include "StudyL1Trigger/TTUEmulatorSkim/src/TTUEmulatorSkim.h"

//... HLT
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//

TTUEmulatorSkim::TTUEmulatorSkim(const edm::ParameterSet& iConfig)
{
  
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers");
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_makeCoincidenceTT  = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceTT");

  //m_hltResultsLabel    = iConfig.getParameter<edm::InputTag>("TriggerResultsLabel");
  //m_lumiSection        = iConfig.getUntrackedParameter<int>("LumiSection", 0);
  //m_makeCoincidenceAlg = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceAlgo");
  //m_makeCoincidenceHLT = iConfig.getParameter< std::vector<std::string> >("MakeCoincidenceHLT");
  //m_disableTTUbits     = iConfig.getUntrackedParameter<bool>("DisableTTUBits", 0);
  //m_processName        = iConfig.getUntrackedParameter<std::string>("ProcessName", "HLT");

  m_totalEvts = 0;
  
  m_totalFilter = 0;
  
}

TTUEmulatorSkim::~TTUEmulatorSkim()
{
 

}

// ------------ method called on each new Event  ------------
bool
TTUEmulatorSkim::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //..............................................................................................
  
  ++m_totalEvts;
  
  //..............................................................................................

  edm::Handle< L1GtTechnicalTriggerRecord > gtRecord;
  iEvent.getByLabel( m_gtReadoutLabel , gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "L1GtTechTrig" << "can't find L1GtTechnicalTriggerRecord with label: " 
              << "rpcTechnicalTrigger" << '\n';
    return false;
  }

  //..............................................................................................
  
  //..............................................................................................

  bool hasTTInCoincidence = false;
  
  std::vector<unsigned>::iterator bitItr;
  std::vector<L1GtTechnicalTrigger>::const_iterator ttItr;
  
  ttVec = gtRecord->gtTechnicalTrigger();
  
  if ( ttVec.size() <= 0 ) return false;

  for( bitItr = m_makeCoincidenceTT.begin(); bitItr != m_makeCoincidenceTT.end(); ++bitItr) {
    bool ttBitResult = ttVec.at( (*bitItr) - 24 ).gtTechnicalTriggerResult();
    hasTTInCoincidence |= ttBitResult;
  }
  
  //..............................................................................................

  //..............................................................................................
  
  bool hasTTUbits             = true;
  bool hasAlgBitInCoincidence = true;
  bool m_HLTBits              = true;
  
  if ( hasTTUbits && hasTTInCoincidence && hasAlgBitInCoincidence && m_HLTBits ) {
    ++m_totalFilter;
    return true;
  }
  
  //..............................................................................................
  
  return false;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
TTUEmulatorSkim::beginJob()
{
  m_hltConfig.init( m_processName );
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TTUEmulatorSkim::endJob() {

  std::cout << "TTUEmulatorSkim::endJob> T:" 
            << m_totalEvts << " F:"
            << m_totalFilter << "\n";
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(TTUEmulatorSkim);
