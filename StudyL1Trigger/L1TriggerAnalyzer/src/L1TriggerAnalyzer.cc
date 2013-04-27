///
//

#include "L1TriggerAnalyzer.h"

L1TriggerAnalyzer::L1TriggerAnalyzer(const edm::ParameterSet& iConfig) {
  
  m_debug           = iConfig.getParameter<bool>("DebugMode");
  m_gtReadoutLabel  = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_gmtReadoutLabel = iConfig.getParameter<edm::InputTag>("GMTReadoutRcd");
  m_bitsVec         = iConfig.getParameter< std::vector<int> >("PhysicsTBits");
  
}


L1TriggerAnalyzer::~L1TriggerAnalyzer()
{


}

//
// member functions
//

// ------------ method called for each event  ------------
void
L1TriggerAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //iEvent information - uncomment if needed
  //unsigned int  runidX = iEvent.run();
  //unsigned int ieventX = iEvent.id().event();
  //unsigned int iorbitX = iEvent.orbitNumber();
  //int              bxX = iEvent.bunchCrossing();
  //unsigned int lumiSec = iEvent.luminosityBlock();

  edm::Handle<LumiDetails> lumiDetails;
  iEvent.getLuminosityBlock().getByLabel("lumiProducer",lumiDetails); 

  // Check that there is something
  
  if (!lumiDetails.isValid()) { 
    LogDebug("L1TriggerAnalyzer")
      << "\n\n Error: no LumiDetails found \n\n" << std::endl;
    if(m_debug) std::cout << "No Lumidetails Found: " << std::endl;
  }
  else {
    float mybxlumi = lumiDetails->lumiValue(LumiDetails::kOCC1, iEvent.bunchCrossing())*6.37;
    std::cout << "Lumidetails: " << mybxlumi << std::endl;
  }

  // Get L1GlobalTriggerReadoutRecord
  
  edm::Handle<L1GlobalTriggerReadoutRecord> gtRecord;
  iEvent.getByLabel(m_gtReadoutLabel, gtRecord);
  
  if (!gtRecord.isValid()) {
    LogDebug("L1TriggerAnalyzer")
      << "\n\n Error: no L1GlobalTriggerReadoutRecord found with input tag " << m_gtReadoutLabel
      << "\n Returning empty L1GlobalTriggerRecord.\n\n"
      << std::endl;
    if(m_debug) std::cout << "L1GlobalTriggerReadoutRecor> Not a valid input tag: " << m_gtReadoutLabel << std::endl;
    return;
  }
  
  DecisionWord algoDecisionWord = gtRecord->decisionWord();    
  
  for (std::vector<int>::iterator itBit = m_bitsVec.begin();
       itBit != m_bitsVec.end(); ++itBit) {
    
    bool algoTrigger = algoDecisionWord.at( (*itBit) );
    
    if (algoTrigger) { 
      h_1DHistContainer["muonTriggerDec"]->Fill( (*itBit), 1 );
    }
    
  }

  //.............................................................................................
  
  //L1 GMT analysis

  edm::Handle<L1MuGMTReadoutCollection> gmtRecord;
  iEvent.getByLabel(m_gmtReadoutLabel, gmtRecord);
  
  if ( !gmtRecord.isValid() ) {
    LogDebug("L1TriggerAnalyzer")
      << "\n\n Error: can't find L1MuGMTReadoutCollection with label " << m_gmtReadoutLabel
      << "\n Returning empty L1GlobalTriggerRecord.\n\n"
      << std::endl;
    if(m_debug) std::cout << "L1MuGMTReadoutCollection> Not a valid input tag: " << m_gmtReadoutLabel << std::endl;
    return;
  }
  
  //.............................................................................................
  
  bool rpcBar_l1a  = false;
  bool rpcFwd_l1a  = false;
  bool dtBar_l1a   = false;

  // get GMT readout collection
  const L1MuGMTReadoutCollection * gmtRC = gmtRecord.product();
  
  // get record vector
  std::vector<L1MuGMTReadoutRecord>::const_iterator RRItr;
  std::vector<L1MuGMTReadoutRecord> gmt_records = gmtRC->getRecords();
  
  edm::LogInfo("L1TriggerAnalyzer") << "nRecords: " << gmt_records.size() << '\n';
  
  for( RRItr = gmt_records.begin(); RRItr != gmt_records.end(); RRItr++ ) {
    
    int BxInEvent = RRItr->getBxInEvent();
    int BxInEventNew = RRItr->getBxNr();
    
    // RPC barrel muon candidates
    int nrpcB = 0;
    int nrpcF = 0;
    int ndtB  = 0;
    
    std::vector<L1MuRegionalCand> BrlRpcCands = RRItr->getBrlRPCCands();
    std::vector<L1MuRegionalCand> FwdRpcCands = RRItr->getFwdRPCCands();
    std::vector<L1MuRegionalCand> BrlDtCands  = RRItr->getDTBXCands ();
    
    std::vector<L1MuRegionalCand>::const_iterator RCItr;
    
    for( RCItr = BrlRpcCands.begin(); RCItr !=BrlRpcCands.end(); ++RCItr) {
      if ( !(*RCItr).empty() ) {
        
        if( m_debug) std::cout << "Found " << nrpcB << " valid barrel RPC candidates in bx wrt. L1A = "
                               << (*RCItr).bx() << '\t'
                               << BxInEvent << '\t'
                               << BxInEventNew << '\t' 
                               << (*RCItr).phiValue() << std::endl;
        
        nrpcB++;
      }
    }
    
    for( RCItr = FwdRpcCands.begin(); RCItr !=FwdRpcCands.end(); ++RCItr) {
      if ( !(*RCItr).empty() ) {
        
        if( m_debug) std::cout << "Found " << nrpcF << " valid FWD RPC candidates in bx wrt. L1A = "
                               << (*RCItr).bx() << '\t'
                               << BxInEvent << '\t'
                               << BxInEventNew << std::endl;
        
        nrpcF++;
      }
    }
    
    for( RCItr = BrlDtCands.begin(); RCItr !=BrlDtCands.end(); ++RCItr) {
      if ( !(*RCItr).empty() ) {
        
        if( m_debug) std::cout << "Found " << ndtB << " valid barrel DT candidates in bx wrt. L1A = "
                               << (*RCItr).bx() << '\t'
                               << BxInEvent << '\t'
                               << BxInEventNew << std::endl;
        
        ndtB++;
      }
    }
    
    if( nrpcB > 0) 
      
      if( m_debug) std::cout << "Found " << nrpcB << " valid barrel RPC candidates in bx wrt. L1A = " 
                             << BxInEvent << '\t'
                             << BxInEventNew << std::endl;
    
    if( BxInEvent == 0 && nrpcB > 0) rpcBar_l1a = true;
    
    if( nrpcF > 0) 
      
      if( m_debug) std::cout << "Found " << nrpcF << " valid forward RPC candidates in bx wrt. L1A = " 
                             << BxInEvent << '\t'
                             << BxInEventNew << std::endl;
    
    if( BxInEvent == 0 && nrpcF > 0) rpcFwd_l1a = true;


    if( ndtB > 0) 
      
      if( m_debug) std::cout << "Found " << ndtB << " valid barrel DT candidates in bx wrt. L1A = " 
                             << BxInEvent << '\t'
                             << BxInEventNew << std::endl;
    
    if( BxInEvent == 0 && ndtB > 0) dtBar_l1a = true;
    
  }
  
  
  if( rpcBar_l1a || rpcFwd_l1a ) { 
    if (m_debug) std::cout << "barrel RPC trigger" << std::endl;
  }
  
  if( dtBar_l1a ) { 
    if (m_debug) std::cout << "barrel DT trigger" << std::endl;
  }
  
  
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
L1TriggerAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  
  h_1DHistContainer["muonTriggerDec"] = fs->make<TH1F>("muonTriggerDec",   "muon trigger decisions", 125, 0,  125);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1TriggerAnalyzer::endJob() 
{

}

// ------------ method called when starting to processes a run  ------------
void 
L1TriggerAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{

  
  


}

// ------------ method called when ending the processing of a run  ------------
void 
L1TriggerAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{

}

// ------------ method called when starting to processes a luminosity block  ------------
void 
L1TriggerAnalyzer::beginLuminosityBlock(const edm::LuminosityBlock & lumiblock, const edm::EventSetup & esetup)
{

  edm::Handle<LumiSummary> lSummary;
  lumiblock.getByLabel("lumiProducer", lSummary); 

  // Check that there is something

  if (!lSummary.isValid()) {
    std::cout << "LumiSummary is no valid" << std::endl;
    return;
  }
  
  //use l
  float myavginstlumi=lSummary->avgInsDelLumi();

  std::cout << "avg inst Lumi: " << myavginstlumi << std::endl;
  
 
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
L1TriggerAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
  
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
L1TriggerAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TriggerAnalyzer);
