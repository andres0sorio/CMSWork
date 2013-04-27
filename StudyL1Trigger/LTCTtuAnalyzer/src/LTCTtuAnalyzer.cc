// system include files
#include "StudyL1Trigger/LTCTtuAnalyzer/src/LTCTtuAnalyzer.h"
//

#include "DataFormats/LTCDigi/interface/LTCDigi.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "DataFormats/RPCDigi/interface/RPCDigi.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

//Technical trigger bits
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h>
#include <DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h>

//.......................................................................

LTCTtuAnalyzer::LTCTtuAnalyzer(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  
  m_debug = false;
  
  m_rpcDigiLabel       = iConfig.getParameter<edm::InputTag>("RPCDigiLabel");
  m_ltcDigiLabel       = iConfig.getParameter<edm::InputTag>("LTCDigiLabel");
  m_rpcTechTrig        = iConfig.getParameter<edm::InputTag>("L1TTBitsLabel");
  
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers"); //<- select the TTbit used in Run
  
  m_readRpcTT          = iConfig.getUntrackedParameter<int>("ReadRpcTTbits", 0);

  m_selFilter          = iConfig.getUntrackedParameter<int>("SelectFilter", 1);
  m_maxNBx             = iConfig.getUntrackedParameter<int>("MaxNBx", 2);
  m_bxNumMin           = iConfig.getUntrackedParameter<int>("MinBxNum", 70);
  m_bxNumMax           = iConfig.getUntrackedParameter<int>("MaxBxNum", 270);
  m_EvtWindow          = iConfig.getUntrackedParameter<int>("EventWindow", 10);
  m_useCompression     = iConfig.getUntrackedParameter<int>("UseCompression", 1);
  m_writeMode          = iConfig.getUntrackedParameter<int>("WriteMode", 1);
  m_precision          = iConfig.getUntrackedParameter<int>("Precision", 10);
  m_maxRate            = iConfig.getUntrackedParameter<int>("MaxRate", 300);

  if ( m_selFilter < 0 ) 
    m_applyFilter = false;
  else m_applyFilter = true;
  
  m_infoObj = new L1GtExtractedInfo("ltcinformation.txt.gz");
  
  if (m_useCompression <= 0) m_infoObj->NoCompression();
  m_infoObj->SetMode( m_writeMode );
  m_infoObj->SetPrecision( m_precision );
  
  m_bxFinal  = 0;
  m_nevtTrg  = 0;
  m_firstEvt = 0;
  m_lastEvt  = 0;
  m_nevt     = 0;
  
  m_totalTime = 0.0;
  m_elapsedTime = 0.0;
  m_previousTime = 0.0;
  
  for( int k=0; k < 8; ++k)
    m_ntrigger.push_back( 0 );
  
  m_maxttBits = m_ttBits.size();

}

LTCTtuAnalyzer::~LTCTtuAnalyzer()
{
    
  if (m_infoObj) {
    m_infoObj->Close();
    delete m_infoObj;
  }
  
}

//.......................................................................

void
LTCTtuAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  
  //..............................................................................................
  
  edm::Handle< LTCDigiCollection > gtRecord;
  iEvent.getByLabel( m_ltcDigiLabel , gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "LTCTtuAnalyzer" << "can't find LTCTtuAnalyzer with label: " 
              << m_ltcDigiLabel << '\n';
    return;
  }
  
  //..............................................................................................
  
  m_bxFinal  = 0;
  m_flag = -1;
  
  std::vector<LTCDigi>::const_iterator ltcItr ;
    
  double deltaTime(0.0);
  
  for ( ltcItr = gtRecord->begin(); ltcItr != gtRecord->end(); ++ltcItr ){
    
    unsigned int ieventLTC = (*ltcItr).eventID();
    unsigned int iorbitLTC = (*ltcItr).orbitNumber();
    int bxLTC              = (*ltcItr).bunchNumber();
    unsigned long long timeStamp = iEvent.time().value();
      
    if (m_debug) std::cout << timeStamp << std::endl;
    
    //...
    m_infoObj->m_ievent = ieventLTC;
    
    m_bxNumber->Fill( bxLTC );
    
    //....Get time information
    m_currentTime = evaluateTime ( iorbitLTC , bxLTC  );
    
    //...deltaTime = (m_currentTime - m_previousTime);
    
    deltaTime = fabs(m_currentTime - m_previousTime);
    if ( deltaTime > 1.0 ) deltaTime = 0;
    
    if ( m_elapsedTime < 0 ) 
      deltaTime = m_currentTime - 0.0;
    
    m_totalTime   += deltaTime;
    m_elapsedTime += deltaTime;
    
    if ( m_elapsedTime > 1.0 ) { 
      
      m_trigRateHz->Fill( m_totalTime, m_ntrigger[0] );
      m_trigRateDist->Fill( m_ntrigger[0] );
      
      //...
      m_infoObj->m_outputRate = true;
      m_infoObj->m_ntriggered[0] = m_ntrigger[0];
      
      m_elapsedTime = 0;
      m_ntrigger[0] = 0;
      
    } else m_infoObj->m_outputRate = false;
    
    m_previousTime = m_currentTime;
    
    for(int k=0; k < 5; ++k) { // LTC up to 5 bits: it has in fact 5 lines to connect
      
      if ( (*ltcItr).HasTriggered(k) ) 
        m_hasTrigger->Fill(k);
      
    }
    
    m_infoObj->m_flag = m_flag;
    m_infoObj->m_time = m_totalTime;
    
    if ( m_readRpcTT == 0 ) {
      
      ++m_ntrigger[0];
      m_infoObj->setTechnicalTriggerBits( bxLTC, 2, (*ltcItr).HasTriggered(2) );
      
    } else {
      
      getRpcTechTriggerBits( iEvent , iSetup ); // <- read Rpc Technical Trigger Emulator
      
    }
    
    //...Get RPC digi information
    
    getRpcInfo ( iEvent , iSetup );
    
    if ( bxLTC >= m_bxNumMin && bxLTC < m_bxNumMax ) {
      
      std::string fake;
      
      m_bxNumberClose->Fill( bxLTC );
      
      if ( m_infoObj->m_rpcNdigis < 6 ) fake = std::string("fake");
      else fake = std::string("notfake");
      
      std::cout << "Lookfor data in: " 
                << ieventLTC  << " "
                << iorbitLTC  << " " 
                << bxLTC << " " 
                << m_infoObj->m_rpcNdigis << " "
                << m_totalTime << " "
                << fake
                << std::endl;
      
      m_flag = 1;
      
    } else m_flag = 0;
    
    m_flag = -1;
    
    m_infoObj->m_maxttBits = m_maxttBits;
    m_infoObj->m_ievent = ieventLTC;
    m_infoObj->Write();
    m_infoObj->reset();
    
  }
  
  
  ++m_nevt;
  
}

long double LTCTtuAnalyzer::evaluateTime ( unsigned int iorbit, unsigned int ibunch )
{
  
  unsigned long long time_Bx = ( 3564 * iorbit ) + ibunch;
  unsigned long long time_ns = ( ( 3564 * iorbit ) + ibunch ) * 25 ;
  
  int time_sec = ( time_ns ) / 1000000000;
  
  long double rmder = std::fmod( (long double) time_ns, (long double) 1000000000 );
  
  int rmder_ms = (int) std::floor (rmder / 1000000.0);

  long double fftime = (double) time_sec + (double) rmder_ms/1000.0;
  
  if ( m_debug ) std::cout << iorbit << " "
                           << ibunch << " "
                           << time_Bx << " " 
                           << time_ns << " " 
                           << time_sec << " " 
                           << rmder << " " 
                           << rmder_ms << " "
                           << fftime
                           << std::endl;
  
  m_infoObj->m_iorbit      = iorbit;
  m_infoObj->m_bunchNumber = ibunch;
  m_infoObj->m_time_bx     = time_Bx;
  m_infoObj->m_time_ns     = time_ns;
  
  return fftime;
  
}

void LTCTtuAnalyzer::getRpcInfo( const edm::Event & iEvent , const edm::EventSetup& iSetup)
{
  
  int ndigis     = 0;
  int currentBx  = 0;
  
  std::map<int, int> bx_ndigis;
  std::map<int, std::bitset<5> >  bx_wheel;
  std::map<int, std::bitset<6> >  bx_layer;
  std::map<int, std::bitset<12> > bx_sector;
  
  std::map<int, int>::iterator itrBx;
  std::map<int, std::bitset<12>  >::iterator itrSec;
  
  //..............................................................................................
  
  edm::Handle<RPCDigiCollection> m_ptr_digiColl;
  iEvent.getByLabel(m_rpcDigiLabel, m_ptr_digiColl);
  
  if ( ! m_ptr_digiColl.isValid() ) {
    std::cout << "can't find  with label RPCDigiCollection: " << m_rpcDigiLabel << '\n';
    return;
  }
  
  edm::ESHandle<RPCGeometry> m_ptr_rpcGeom;
  iSetup.get<MuonGeometryRecord>().get( m_ptr_rpcGeom );
  
  //..............................................................................................
  
  RPCDigiCollection::const_iterator m_digiItr;
  RPCDigiCollection::DigiRangeIterator m_detUnitItr;
  
  for (m_detUnitItr = (m_ptr_digiColl)->begin();
       m_detUnitItr != (m_ptr_digiColl)->end(); ++m_detUnitItr ) {
    
    m_digiItr = (*m_detUnitItr ).second.first;
    
    const RPCDetId & id  = (*m_detUnitItr).first;
    const RPCRoll * roll = dynamic_cast<const RPCRoll* >( (m_ptr_rpcGeom)->roll(id));
    
    if((roll->isForward())) {
      //std::cout << "TTUAnalyzer: roll is forward" << std::endl;
      continue;
    }
    
    currentBx  = (*m_digiItr).bx();
    
    int wheel   = roll->id().ring();                    // -2,-1,0,+1,+2
    int sector  = roll->id().sector();                  // 1 to 12
    int layer   = roll->id().layer();                   // 1,2
    int station = roll->id().station();                 // 1-4
    int blayer  = getBarrelLayer( layer, station );     // 1 to 6
    
    itrBx = bx_ndigis.find( currentBx );
    
    if ( itrBx != bx_ndigis.end() ) {
      itrBx->second += 1;
      bx_wheel[ currentBx  ].set ( wheel +2, true);
      
      int bxsign(1);
      if ( currentBx != 0 ) bxsign = ( currentBx / abs(currentBx) );
      else bxsign = 1;
      
      int code = bxsign * ( 1000*abs(currentBx) + (wheel+2) );
      
      bx_sector[ code ].set ( sector-1, true);
      bx_layer [ code ].set ( blayer-1, true);
      
    } else {
      bx_ndigis[ currentBx ] = 1;
      
      std::bitset<5>  wheelbits;
      std::bitset<12> sectrbits;
      std::bitset<6>  layerbits;
      
      wheelbits.reset();
      sectrbits.reset();
      layerbits.reset(); 
      
      int bxsign(1);
      if ( currentBx != 0 ) bxsign = ( currentBx / abs(currentBx) );
      else bxsign = 1;
      
      int code = bxsign * ( 1000*abs(currentBx) + (wheel+2) );
      
      wheelbits.set ( wheel +2, true);
      sectrbits.set ( sector-1, true);
      layerbits.set ( blayer-1, true);
      
      bx_wheel [ currentBx  ] = wheelbits;
      bx_sector[ code ] = sectrbits;
      bx_layer [ code ] = layerbits;
      
    }
    
    
    ++ndigis;
    
  }
  
  if ( bx_ndigis.size() > 0 ) {
    m_infoObj->m_hasRpcInfo = true;
    if ( m_debug ) std::cout << "Checking size of ndigis" << bx_ndigis.size() << std::endl;
  }
  else {
    m_infoObj->m_hasRpcInfo = false;
    return;
  }
  
  //for the moment only stored information related to BX=0
  
  currentBx = 0;
  itrBx = bx_ndigis.find( currentBx ); 
  
  if ( itrBx != bx_ndigis.end() ) {
    
    if ( m_debug ) std::cout << "bx: " 
                             << (*itrBx).second << '\t'
                             << bx_wheel[ currentBx ].to_ulong() << '\n';
    
    m_infoObj->m_bxInRpcEvent = currentBx;
    m_infoObj->m_rpcNdigis = (*itrBx).second;
    m_infoObj->m_wheel = (int) bx_wheel[ currentBx ].to_ulong();
    
    for( int k=0; k < 5; ++k ) {
      
      int bxsign(1);
      if ( currentBx != 0 ) bxsign = ( currentBx / abs(currentBx) );
      else bxsign = 1;
      
      int code = bxsign * ( 1000*abs(currentBx) + k );
      
      itrSec = bx_sector.find ( code );
      
      if ( itrSec != bx_sector.end() ) {
        
        int sec = (int) bx_sector[ code ].to_ulong();
        int lay = (int) bx_layer[ code ].to_ulong();
        
        if ( m_debug ) std::cout << "sector: " << sec << '\t'
                                 << "layer: "  << lay << '\n';
        m_infoObj->setRpcSectorLayer( sec, lay );
        
      } else {
        if ( m_debug) std::cout << "sector: " << 0 << '\t'
                                << "layer: "  << 0 << '\n';
        
        m_infoObj->setRpcSectorLayer( 0, 0);
        
      }
      
    }
    
  } else {
    
    m_infoObj->m_hasRpcInfo = false;
    
    if ( m_debug) std::cout << "bx: "     << 0 << '\t'
                            << "wheel: "  << 0 << '\t'
                            << "sector: " << 0 << '\t'
                            << "layer: "  << 0 << '\n';
    
  }
  
  bx_ndigis.clear();
  bx_wheel.clear();
  bx_sector.clear();
  bx_layer.clear();
  
}

int LTCTtuAnalyzer::getBarrelLayer( const int & _layer, const int & _station )
{
  
  //... Calculates the generic Barrel Layer (1 to 6)
  int blayer(0);
  
  if ( _station < 3 ) {
    blayer = ( (_station-1) * 2 ) + _layer;
  }
  else {
    blayer = _station + 2;
  }
  
  return blayer;
  
}

void LTCTtuAnalyzer::getRpcTechTriggerBits( const edm::Event & iEvent , const edm::EventSetup& iSetup ) 
{
  
  //... This method reads the information created by the Rpc Technical Trigger Emulator
  
  edm::Handle< L1GtTechnicalTriggerRecord > gtRecord;
  iEvent.getByLabel( m_rpcTechTrig , gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "RPCTechnicalTrigger" << "can't find L1GtTechnicalTriggerRecord with label: " 
              << "rpcTechnicalTrigger" << '\n';
    return;
  }
  
  std::vector<L1GtTechnicalTrigger> ttVec;
  
  ttVec = gtRecord->gtTechnicalTrigger();
  
  if ( m_debug ) std::cout << "Size of technical trigger vector" << ttVec.size() << std::endl;
  
  std::vector<L1GtTechnicalTrigger>::const_iterator ttItr;
  
  bool wasEventTriggered(false);
 
  unsigned int selttBit = m_ttBits[0] - 24;
  
  //for( ttItr = ttVec.begin(); ttItr != ttVec.end(); ++ttItr) {
  
  if ( m_debug ) std::cout << "L1GtTechnicalTrigger> " 
                           << ttVec[selttBit].bxInEvent() << '\t'
                           << ttVec[selttBit].gtTechnicalTriggerBitNumber() << '\t'
                           << ttVec[selttBit].gtTechnicalTriggerResult() << '\n';
  
  m_infoObj->setTechnicalTriggerBits( ttVec[selttBit].gtTechnicalTriggerBitNumber(),
                                      ttVec[selttBit].bxInEvent(),
                                      ttVec[selttBit].gtTechnicalTriggerResult() );
  
  if ( ttVec[selttBit].gtTechnicalTriggerResult() == 1 ) {
    wasEventTriggered = true;
    ++m_ntrigger[0];
  }
    

}

// ------------ method called once each job just before starting event loop  ------------
void 
LTCTtuAnalyzer::beginJob()
{

  edm::Service<TFileService> fservice;
  
  m_bxDist = fservice->make<TH1D>("BX.distribution.Final",
                                  "Bx distribution",
                                  7, -3, 3);
  
  m_bxNumber = fservice->make<TH1D>("BX.Num.Distribution",
                                    "Bx distribution",
                                    4000, 0, 4000);
  
  m_bxNumberClose = fservice->make<TH1D>("BX.Num.Distribution.in.Range",
                                         "Bx distribution",
                                         1000, m_bxNumMin, (m_bxNumMax+1) );
  
  m_hasTrigger = fservice->make<TH1D>("LTC.HasTrigger",
                                      "LTC HasTrigger (5 bits)",
                                      6,0,6);
  
  m_trigRateHz = fservice->make<TH1D>("Trigger.Rate",
                                      "Trigger rate [Hz]",
                                      10000, 0,10000);
  
  
  m_trigRateDist = fservice->make<TH1D>("Trigger.Rate.Dist",
                                        "Trigger rate [Hz]",
                                        m_maxRate, 0, m_maxRate);
  
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
LTCTtuAnalyzer::endJob() 
{
  
  std::cout << "total time: " << m_totalTime << " "
            << "total elapsed time: " << m_elapsedTime << std::endl;
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(LTCTtuAnalyzer);
