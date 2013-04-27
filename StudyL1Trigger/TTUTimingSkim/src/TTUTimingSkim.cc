// user include files
#include "StudyL1Trigger/TTUTimingSkim/src/TTUTimingSkim.h"

//... HLT
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//

TTUTimingSkim::TTUTimingSkim(const edm::ParameterSet& iConfig)
{
  
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>( "GTReadoutRcd");
  m_gmtReadoutLabel    = iConfig.getParameter<edm::InputTag>("GMTReadoutRcd");
  m_lumiSection        = iConfig.getUntrackedParameter<int>(   "LumiSection", 0);
  m_selectedBit        = iConfig.getUntrackedParameter<int>(   "SelectedBit", 24);
  m_selectedBX         = iConfig.getUntrackedParameter<int>(    "SelectedBX", 0);
  m_detector           = iConfig.getUntrackedParameter<int>(     "Dectector", 1);
  m_totalEvts = 0;
  m_totalFilter = 0;

  m_debug = true;
  
  
  
}

TTUTimingSkim::~TTUTimingSkim()
{
 

}

// ------------ method called on each new Event  ------------
bool
TTUTimingSkim::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //..............................................................................................
  
  unsigned int lumiSec = iEvent.luminosityBlock();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564

  if ( lumiSec < m_lumiSection )
    return false;

  ++m_totalEvts;
  
  //..............................................................................................
  
  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( m_gtReadoutLabel, gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "TTUTimingSkim" << "can't find L1GlobalTriggerRecord with label: " 
              << m_gtReadoutLabel << '\n';
    return false;
  }
  
  //..............................................................................................
  bool keepEvent = false;

  //..............................................................................................
  
  int dGMT(0);
  dGMT = discriminateGMT( iEvent , iSetup );

  std::map<int,bool> ttuDec;
  std::map<int,bool>::iterator decItr;
  
  for( int iebx=0; iebx < 5; iebx++) {
    
    const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(iebx-2);
    ttuDec[iebx-2] = gtTTWord[ m_selectedBit ];
    
  }
  
  if (m_debug) std::cout << "requested: " << m_selectedBX << std::endl;
  
  if ( m_rpcTrigger && m_detector == 1 ) {
    int bx1 = (bxX - m_GMTcandidatesBx[0]);
    for( decItr = ttuDec.begin(); decItr != ttuDec.end(); ++decItr ){
      if ( (*decItr).second ) {
        int bx2 = (*decItr).first;
        float bxdiffPacTT = 1.0*( bx1 - bx2);
        if ( bxdiffPacTT == m_selectedBX ) {
          if (m_debug) std::cout << "keep this event " << bxdiffPacTT 
                                 << " requested " << m_selectedBX
                                 << std::endl;
          keepEvent = true;
        } else keepEvent = false;
      }
    }
  }
  
  if ( m_dtTrigger && m_detector == 2) {
    int bx1 = (bxX - m_DTcandidatesBx[0]);
    for( decItr = ttuDec.begin(); decItr != ttuDec.end(); ++decItr ){
      if ( (*decItr).second ) {
        int bx2 = (*decItr).first;
        float bxdiffDtTT = 1.0*( bx1 - bx2);
        if ( bxdiffDtTT == m_selectedBX ) {
          if (m_debug) std::cout << "keep this event " << bxdiffDtTT 
                                 << " requested " << m_selectedBX
                                 << std::endl;
          keepEvent = true;
        } else keepEvent = false;
      }
    }
  }
  
  ttuDec.clear();
  
  m_GMTcandidatesBx.clear();
  
  //..............................................................................................
  //... use additional selection
  
  



  
  //..............................................................................................
  
  return keepEvent;
  
}

int TTUTimingSkim::discriminateGMT( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
  
  //.............................................................................................
  
  edm::Handle<L1MuGMTReadoutCollection> pCollection;
  iEvent.getByLabel(m_gmtReadoutLabel, pCollection);
  
  if ( !pCollection.isValid() ) {
    std::cout << "TTUTimingSkim" << " can't find L1MuGMTReadoutCollection with label "
              << m_gmtReadoutLabel << '\n';
    return -1;
  }
  
  //.............................................................................................
  
  int gmtDec(0);
  bool rpcBar_l1a  = false;
  bool dtBar_l1a   = false;
  
  m_dtTrigger  = false;
  m_rpcTrigger = false;
  
  // get GMT readout collection
  const L1MuGMTReadoutCollection * gmtRC = pCollection.product();
  
  // get record vector
  std::vector<L1MuGMTReadoutRecord>::const_iterator RRItr;
  std::vector<L1MuGMTReadoutRecord> gmt_records = gmtRC->getRecords();
  
  edm::LogInfo("DiscriminateGMT") << "nRecords: " << gmt_records.size() << '\n';
  
  for( RRItr = gmt_records.begin(); RRItr != gmt_records.end(); RRItr++ ) {
    
    int BxInEvent = RRItr->getBxInEvent();
    int BxInEventNew = RRItr->getBxNr();
  
    // RPC barrel muon candidates
    int nrpcB = 0;
    int ndtB  = 0;
    
    std::vector<L1MuRegionalCand> BrlRpcCands = RRItr->getBrlRPCCands();
    std::vector<L1MuRegionalCand> BrlDtCands  = RRItr->getDTBXCands ();
    
    std::vector<L1MuRegionalCand>::const_iterator RCItr;
    
    for( RCItr = BrlRpcCands.begin(); RCItr !=BrlRpcCands.end(); ++RCItr) {
      if ( !(*RCItr).empty() ) {
        
        if( m_debug) std::cout << "Found " << nrpcB << " valid barrel RPC candidates in bx wrt. L1A = "
                               << (*RCItr).bx() << '\t'
                               << BxInEvent << '\t'
                               << BxInEventNew << std::endl;
        
        m_GMTcandidatesBx.push_back( BxInEventNew );
        nrpcB++;
  
      }
    }
    
    for( RCItr = BrlDtCands.begin(); RCItr !=BrlDtCands.end(); ++RCItr) {
      if ( !(*RCItr).empty() ) {
        
        if( m_debug) std::cout << "Found " << ndtB << " valid barrel DT candidates in bx wrt. L1A = "
                               << (*RCItr).bx() << '\t'
                               << BxInEvent << '\t'
                               << BxInEventNew << std::endl;
        
        m_DTcandidatesBx.push_back( BxInEventNew );
        
        ndtB++;
      }
    }
    
    if( nrpcB > 0) 
      
      if( m_debug) std::cout << "Found " << nrpcB << " valid barrel RPC candidates in bx wrt. L1A = " 
                             << BxInEvent << '\t'
                             << BxInEventNew << std::endl;
    
    if( BxInEvent == 0 && nrpcB > 0) rpcBar_l1a = true;
    
    if( ndtB > 0) 
      
      if( m_debug) std::cout << "Found " << ndtB << " valid barrel DT candidates in bx wrt. L1A = " 
                             << BxInEvent << '\t'
                             << BxInEventNew << std::endl;
    
    if( BxInEvent == 0 && ndtB > 0) dtBar_l1a = true;
    
  }
  
  
  if( rpcBar_l1a ) { 
    if (m_debug) std::cout << "barrel RPC trigger" << std::endl;
    gmtDec = 1;
    m_rpcTrigger = true;
    
  }
  
  if( dtBar_l1a ) { 
    if (m_debug) std::cout << "barrel DT trigger" << std::endl;
    gmtDec = 2;
    m_dtTrigger = true;
  }
  
  return gmtDec;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
TTUTimingSkim::beginJob()
{
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TTUTimingSkim::endJob() {

  std::cout << "TTUTimingSkim::endJob> T:" 
            << m_totalEvts << " F:"
            << m_totalFilter << "\n";
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(TTUTimingSkim);
