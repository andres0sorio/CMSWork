// system include files
#include "StudyL1Trigger/L1GtTtuAnalyzer/src/L1GtTtuAnalyzer.h"
#include <cmath>
#include "DataFormats/DetId/interface/DetId.h"

#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"

#include "FWCore/Framework/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"


#include "TLorentzVector.h"

L1GtTtuAnalyzer::L1GtTtuAnalyzer(const edm::ParameterSet& iConfig)
{
  
  //now do what ever initialization is needed
  m_debug = false;
  
  m_rpcDigiLabel       = iConfig.getParameter<edm::InputTag>("RPCDigiLabel");
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_gmtReadoutLabel    = iConfig.getParameter<edm::InputTag>("GMTReadoutRcd");
  m_rpcTechTrigEmu     = iConfig.getParameter<edm::InputTag>("L1TTEmuBitsLabel");
  m_recoMuonLabel      = iConfig.getParameter<edm::InputTag>("RecoMuonLabel");
  m_recoTracksLabel    = iConfig.getParameter<edm::InputTag>("RecoTracksLabel");
  m_recoCosmicsLabel   = iConfig.getParameter<edm::InputTag>("RecoCosmicsLabel");
  m_recoSiStripLabel   = iConfig.getParameter<edm::InputTag>("RecoSiStripLabel");
  m_recoPixelLabel     = iConfig.getParameter<edm::InputTag>("RecoPixelLabel");
  m_hltResultsLabel    = iConfig.getParameter<edm::InputTag>("TriggerResultsLabel");

  m_muonPtcut          = iConfig.getUntrackedParameter<double>("MuonPtCut", 4.0);
  m_IsStreamExpress    = iConfig.getUntrackedParameter<int>("IsStreamExpress", 0);
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers");
  m_ttBitsCollisions   = iConfig.getParameter< std::vector<unsigned> >("BitCollisions");

  m_lumiSectionA        = iConfig.getUntrackedParameter<int>("LumiSectionA",  0);
  m_lumiSectionB        = iConfig.getUntrackedParameter<int>("LumiSectionB", -1);

  m_makeCoincidenceTT  = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceTT");
  m_makeCoincidenceAlg = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceAlgo");
  m_checkhltPaths      = iConfig.getParameter< std::vector<std::string> >("CheckHLTPaths");
  m_processName        = iConfig.getUntrackedParameter<std::string>("ProcessName", "HLT");
  
  m_readRpcTTEmu       = iConfig.getUntrackedParameter<int>("ReadRpcTTEmuBits", 0);
  m_selFilter          = iConfig.getUntrackedParameter<int>("SelectFilter", 1);
  m_maxNBx             = iConfig.getUntrackedParameter<int>("MaxNBx", 2);
  m_bxNumMin           = iConfig.getUntrackedParameter<int>("MinBxNum", 70);
  m_bxNumMax           = iConfig.getUntrackedParameter<int>("MaxBxNum", 270);
  m_EvtWindow          = iConfig.getUntrackedParameter<int>("EventWindow", 10);
  m_BxWindow           = iConfig.getUntrackedParameter<int>("BxWindow", 0);
  m_useCompression     = iConfig.getUntrackedParameter<int>("UseCompression", 1);
  m_writeMode          = iConfig.getUntrackedParameter<int>("WriteMode", 1);
  m_precision          = iConfig.getUntrackedParameter<int>("Precision", 10);
  m_maxRate            = iConfig.getUntrackedParameter<int>("MaxRate", 300);
  m_maxPt              = iConfig.getUntrackedParameter<double>("MaxPt", 200);
  m_trackerLength      = iConfig.getUntrackedParameter<double>("TrackerLength", 200);
  m_trackerHeight      = iConfig.getUntrackedParameter<double>("TrackerHeight", 200);

  if ( m_selFilter < 0 ) 
    m_applyFilter = false;
  else m_applyFilter = true;
  
  m_infoObj = new L1GtExtractedInfo("l1Gtinformation.txt.gz");

  //fileDump = new std::ofstream("l1Gtinformation.csv", ofstream::out);
  gzfileDump = new gz::ogzstream( "l1Gtinformation.csv.gz" );

  if (m_useCompression <= 0) m_infoObj->NoCompression();
  m_infoObj->SetMode( m_writeMode );
  m_infoObj->SetPrecision( m_precision );
  
  m_bxFinal      = 0;
  m_firstEvt     = 0;
  m_lastEvt      = 0;
  m_nevt         = 0;
  m_totalTime    = 0.0;
  m_elapsedTime  = 0.0;
  m_previousTime = 0.0;

  m_totalBit25   = 0;
  m_totalBit25Muon = 0;
    
  for( int k=0; k < 8; ++k)
    m_ntrigger.push_back( 0 );
  
  m_maxttBits = m_ttBits.size();

  m_maxttBitsTrigger  = m_makeCoincidenceTT.size();
  
  m_maxAlgBitsTrigger = m_makeCoincidenceAlg.size();
  
  m_combinations[1] = 0x3;
  m_combinations[2] = 0x5;
  m_combinations[3] = 0x6;

  m_tracker_activity = false;
  
  m_GMTproblem = 0;

  // Muon trigger algos

  m_singleMuBits.push_back(55); // L1_SingleMuOpen
  m_singleMuBits.push_back(56); // L1_SingleMu0
  m_singleMuBits.push_back(57); // L1_SingleMu3
  m_singleMuBits.push_back(58); // L1_SingleMu5
  m_singleMuBits.push_back(59); // L1_SingleMu7
  m_singleMuBits.push_back(60); // L1_SingleMu10
  m_singleMuBits.push_back(61); // L1_SingleMu14
  m_singleMuBits.push_back(62); // L1_SingleMu20

  m_maxAlgBits = m_singleMuBits.size();
      
}

L1GtTtuAnalyzer::~L1GtTtuAnalyzer()
{
  
  if (m_infoObj) {
    m_infoObj->Close();
    delete m_infoObj;
  }

  //fileDump->close();
  //delete fileDump;
  
  if ( gzfileDump ) {
    gzfileDump->close();
    delete gzfileDump;
  }
  
}

//.......................................................................

void
L1GtTtuAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  unsigned int runidX  = iEvent.run();
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
  unsigned int lumiSec = iEvent.luminosityBlock();

  m_timestamp = iEvent.time().value();

  //time_t ts = tstamp >> 32; //sec
  //time_t tus = tstamp & 0xFFFFFFFF; //musec
  //std::cout << ts << " " << tus << std::endl;
  
  if ( lumiSec < m_lumiSectionA )
    return;

  if ( m_lumiSectionB > 0 && ( lumiSec > m_lumiSectionB) )
    return;
  
  //...TTUTree
  m_ntuple->reset();
  m_ntuple->runn = runidX;
  m_ntuple->eventn = ieventX;
  m_ntuple->lumi = lumiSec;
  m_ntuple->maxBits = m_maxttBits;
  m_ntuple->timest = m_timestamp;
  
  //...TTUTree
  m_ntuple->hasRPCB = m_rpcTrigger;
  m_ntuple->hasDT = m_dtTrigger;

  //..............................................................................................
  
  m_bxGTdist->Fill( bxX );
  
  //..............................................................................................
  
  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( m_gtReadoutLabel, gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "L1GtTtuAnalyzer" << "can't find L1GlobalTriggerRecord with label: " 
              << m_gtReadoutLabel << '\n';
    return;
  }
  
  //..............................................................................................
  //

  edm::Handle< edm::TriggerResults > triggerResultsHandle;
  iEvent.getByLabel( m_hltResultsLabel, triggerResultsHandle);
  
  if ( !triggerResultsHandle.isValid()) {
    std::cout << "L1GtTtuAnalyzer" << "can't find TriggerResults with label: " 
              <<  m_hltResultsLabel << '\n';
    return;
  }
  

  //..............................................................................................
  // HLT Information
  
  m_hasActivity_DT = false;
  
  std::vector<std::string> triggerNames;
  const edm::TriggerResults *triggerResults = triggerResultsHandle.product();
  std::vector<std::string>::iterator hltItr;
  int AcceptsSum = 0;
  
  for(uint i=0; i< m_hltConfig.size(); ++i){
    std::string trigger = m_hltConfig.triggerName(i);
    if( trigger.find ("Activity_DT") != std::string::npos)
      triggerNames.push_back(trigger);
  }
  
  for( hltItr = triggerNames.begin(); hltItr != triggerNames.end(); ++hltItr) {
    
    const unsigned int triggerIndex( m_hltConfig.triggerIndex( (*hltItr) )); 
    if (triggerIndex < m_hltConfig.size() ) {
      AcceptsSum += triggerResults->accept(triggerIndex);
    }
    
  }
  
  if ( AcceptsSum >= 1 ) m_hasActivity_DT = true;
  triggerNames.clear();
  
  //..............................................................................................
  //..............................................................................................
  
  m_bxFinal  = 0;
  m_gmtfilter.reset();
  
  m_rpcTechBits.clear();
  
  if ( m_nevt == 0 ) m_firstEvt = ieventX;
  
  const TechnicalTriggerWord tWord = gtRecord->technicalTriggerWord(); //size=64
  TechnicalTriggerWord::const_iterator GTtbitItr;

  int dbitNumber = 0;

  for(GTtbitItr = tWord.begin(); GTtbitItr != tWord.end(); GTtbitItr++) {
    if (*GTtbitItr) {
      m_ntuple->gttt |= (1LL<<dbitNumber);
    }
    dbitNumber++;
  }

  //..............................................................................................
  
  std::vector<unsigned>::iterator selectItr;
  
  const TechnicalTriggerWord unmaskedTTWord = gtRecord->technicalTriggerWord(); // before Mask, size=64
  
  m_hasCoincidence = true;
  (*gzfileDump) << ieventX << " " << bxX << " TtC: ";
  
  int selbit=0;
  for( selectItr = m_makeCoincidenceTT.begin(); selectItr != m_makeCoincidenceTT.end(); ++selectItr ) {
    (*gzfileDump) << (*selectItr) << "= " << unmaskedTTWord.at( (*selectItr) ) << " ";
    m_hasCoincidence &= unmaskedTTWord.at( (*selectItr) ); //... if any of the bits in the list fired
    if( unmaskedTTWord.at( (*selectItr) ) ) m_bxGTdistTTInTrigger[selbit]->Fill( bxX );
    ++selbit;
  }
  (*gzfileDump) << " HasC:" << m_hasCoincidence << '\n';
  
  if ( m_hasCoincidence ) m_bxGTdistTT->Fill( bxX );
  
  //..............................................................................................
  
  const DecisionWord unmaskedAlgWord = gtRecord->decisionWord();
  
  m_hasCoincidenceAlgBit = false;
  (*gzfileDump) << ieventX << " " << bxX << " AlgC: ";
  
  selbit=0;
  for( selectItr = m_makeCoincidenceAlg.begin(); selectItr != m_makeCoincidenceAlg.end(); ++selectItr ) {
    (*gzfileDump) << (*selectItr) << "= " << unmaskedAlgWord.at( (*selectItr) ) << " ";
    m_hasCoincidenceAlgBit |= unmaskedAlgWord.at( (*selectItr) ); //... if any of the bits in the list fired
    if( unmaskedAlgWord.at( (*selectItr) ) ) m_bxGTdistAlgInTrigger[selbit]->Fill( bxX );
    ++selbit;
  }
  (*gzfileDump) << " HasC:" << m_hasCoincidenceAlgBit << " ";

  m_was_triggered_Bit31 = false;
  m_was_triggered_Bit31 = tWord.at(31);

  (*gzfileDump) << " HasCbit31: " << (m_hasCoincidenceAlgBit && m_was_triggered_Bit31) <<  '\n';
  
  //..............................................................................................

  if ( m_hasCoincidenceAlgBit ) m_bxGTdistAlg->Fill( bxX );
  
  //..............................................................................................
  
  std::vector<unsigned>::const_iterator ttbItr;
  
  (*gzfileDump) << ieventX   << " "
                << iorbitX   << " "
                << bxX       << " TT:";
  
  for( ttbItr = m_ttBitsCollisions.begin(); ttbItr != m_ttBitsCollisions.end(); ++ttbItr ) {
    
    bool wasfired = tWord.at( (*ttbItr) );
    if ( wasfired )
      m_bxGTdistTTBits->Fill( bxX , (*ttbItr), 1);
    
    (*gzfileDump) << (*ttbItr) << "= "
                  << wasfired << " ";
        
   }
  
  (*gzfileDump) << '\n';

  //..............................................................................................
  
  bool techTrigger24 = tWord.at(24);
  bool techTrigger25 = tWord.at(25);
  
  bool wasEventTriggered(false);
  wasEventTriggered = gtRecord->decision();
  
  if ( m_debug) std::cout << "event was triggered: " << wasEventTriggered << std::endl;
  
  //..............................................................................................
  
  if ( m_readRpcTTEmu == 0 ) {
    
    wasEventTriggered = false;
    
    std::vector<unsigned>::iterator bitsItr;
    int k = 0;
    
    for ( bitsItr = m_ttBits.begin(); bitsItr != m_ttBits.end(); ++bitsItr ) {
      
      m_infoObj->setTechnicalTriggerBits( bxX , (*bitsItr) , tWord.at( (*bitsItr) ));
      
      //...
      int firstBx = -1*m_BxWindow; //m_BxWindow cannot be > 1 by construction of the TTword
      firstBx = -2;
      for( int iebx = firstBx; iebx < 3; ++iebx) {
        const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(iebx);
        wasEventTriggered |= gtTTWord.at( (*bitsItr) );
        
      }
      
      m_ttBitsDecision->Fill( (*bitsItr) , (int) tWord.at( (*bitsItr) ) ); // bx=0
      
      m_rpcTechBits.push_back( tWord.at( (*bitsItr) ) );
      
      if ( wasEventTriggered ) ++m_ntrigger[k];
      
      ++k;
      wasEventTriggered = false;
            
    }
    
  } else {
    
    ///use this if the emulator is used in the previous step
    getRpcTechTriggerBits( iEvent , iSetup ); 
    
  }
  
  //..............................................................................................
  
  int dGMT(0);
  
  dGMT = discriminateGMT( iEvent , iSetup );
  
  //TTUTree....
  if ( dGMT < 0 ) {
    lookatRpcRecHits( iEvent , iSetup );
    m_ntuple->fill();
    return;
  }
  
  //..............................................................................................
  
  std::map<int,bool> ttuDec;
  std::map<int,bool> ttuDec25;
  std::map<int,bool> ttuDec28;
  std::map<int,bool> ttuDec31;
  
  std::map<int,bool>::iterator decItr;
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    for( int iebx=0; iebx < 5; iebx++) {
      
      const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(iebx-2);
      
      ttuDec[iebx-2] = gtTTWord[ 24+k ];
      
      //......................................................................
      
      if ( (24+k) == 25 ) {
        ttuDec25[iebx-2] = gtTTWord[ 24+k ];
      }
      
      if ( (24+k) == 28 ) {
        ttuDec28[iebx-2] = gtTTWord[ 24+k ];
      }

      if ( (24+k) == 31 ) {
        ttuDec31[iebx-2] = gtTTWord[ 24+k ];
      }
      
      //......................................................................
      
      if (m_debug) std::cout << (iebx-2) << '\t'
                             << gtTTWord[ 24+k ] << '\n';
      if (m_debug) std::cout << bxX << std::endl; //... bxX is equivalent to gmtRecord->getBxNr()

      if ( gtTTWord[ 24+k ] )
        m_bxDist->Fill( (iebx-2) );
      
    }
    
    if ( m_rpcTrigger ) {
      
      int ndec(0);
      int bx1 = (bxX - m_GMTcandidatesBx[0]);
      for( decItr = ttuDec.begin(); decItr != ttuDec.end(); ++decItr ){
        if ( (*decItr).second ) {
          int bx2 = (*decItr).first;
          float bxdiffPacTT = 1.0*( bx1 - bx2);
          (*gzfileDump) << "timing: " <<  bx1 << " " << bx2 << '\n';
          m_bxDistDiffPac[k]->Fill( bxdiffPacTT );
          //TTUTree...
          m_ntuple->pacTTU[k] = bxdiffPacTT;
          //................................
          //if ( m_hasCoincidence || m_hasCoincidenceAlgBit) m_bxDistDiffPacIC[k]->Fill( bxdiffPacTT );
          if ( bxdiffPacTT == 0 && (24+k) == 25 )
            (*gzfileDump) << "pac-25-0k: " << ieventX << " " << iorbitX << " " << bxX << " " << lumiSec << '\n';
          ++ndec;
        }
      }
      m_bxDistNdecTtu->Fill(ndec);
    }

    //........................
    
    if ( m_dtTrigger ) {
      int ndec(0);
      int bx1 = (bxX - m_DTcandidatesBx[0]);
      for( decItr = ttuDec.begin(); decItr != ttuDec.end(); ++decItr ){
        if ( (*decItr).second ) {
          int bx2 = (*decItr).first;
          float bxdiffDtTT = 1.0*( bx1 - bx2);
          m_bxDistDiffDt[k]->Fill( bxdiffDtTT );
          //TTUTree...
          m_ntuple->dtTTU[k] = bxdiffDtTT;
          //................................
          //if ( m_hasCoincidence || m_hasCoincidenceAlgBit ) m_bxDistDiffDtIC[k]->Fill( bxdiffDtTT );
          ++ndec;
        }
      }
    }
    
    ttuDec.clear();
    
  }
  
  //..............................................................................................
  
  std::map<int,bool>::iterator decItr2;
  
  for( decItr =  ttuDec25.begin(); decItr != ttuDec25.end(); ++decItr) {
    if ( (*decItr).second ) {
      for( decItr2= ttuDec28.begin(); decItr2 != ttuDec28.end(); ++decItr2 ){
        if ( (*decItr2).second ) {
          int bx1 = (*decItr).first;
          int bx2 = (*decItr2).first;
          float bxdiffTT25 = 1.0*( bx1 - bx2);
          m_bxDist2528->Fill( bxdiffTT25 );
          (*gzfileDump) << "timing 25: " <<  bx1 << " " << bx2 <<  " " << bxdiffTT25 << " "
                        << ieventX << " " << iorbitX << " " << bxX << " " << lumiSec << '\n';
        }
      }
    }
  }
  
  //..............................................................................................
  
  for( decItr =  ttuDec31.begin(); decItr != ttuDec31.end(); ++decItr) {
    if ( (*decItr).second ) {
      int bx1 = (*decItr).first;
      int bx2 = 0;
      float bxdiffTT31 = 1.0*( bx1 - bx2);
      m_bxDist31->Fill( bxdiffTT31 );
      (*gzfileDump) << "timing 31: " <<  bx1 << " " << bx2 <<  " " << bxdiffTT31 << " " 
                    << ieventX << " " << iorbitX << " " << bxX <<  " " << lumiSec << '\n';
    }
  }
  
  //..............................................................................................
  
  if ( m_dtTrigger && m_rpcTrigger ) {
    
    int bx1dt  = (bxX - m_DTcandidatesBx[0]);
    int bx2rpc = (bxX - m_GMTcandidatesBx[0]);
    
    float bxdiffDtPac = 1.0*( bx1dt - bx2rpc);
    m_bxDistDiffDTPac->Fill( bxdiffDtPac );
    if ( m_hasCoincidence || m_hasCoincidenceAlgBit ) m_bxDistDiffDTPacIC->Fill( bxdiffDtPac );
    
  }
  
  //..............................................................................................
  
  std::bitset<5> pattern;
  pattern.reset();
  
  for( int iebx=0; iebx < 5; iebx++) {
    
    const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(iebx-2);
    bool decision = gtTTWord[ 25 ];
    pattern.set( 4-iebx, decision); //reverse the order

    for ( int kebx=0; kebx < 5; kebx++) {
      
      const DecisionWord gtAlgWord = gtRecord->decisionWord( kebx-2 );
            
      for( int k = 0; k < m_maxAlgBits; ++k ) {
        
        bool mu55decision = gtAlgWord[ m_singleMuBits[k] ];
        
        if ( decision && mu55decision ) {
          m_bxDistMu55TT25[k]->Fill( iebx-2, kebx-2 );
        }
        
      }
            
    }
          
  }

  std::string bit25bxpat = pattern.to_string<char,std::char_traits<char>,std::allocator<char> >();

  if ( pattern.any() )
    (*gzfileDump) << "Pattern for Bit25: "  << bit25bxpat << " " << ieventX << " " << bxX << '\n';

  //std::cout << "Pattern for Bit25: "  << pattern.to_string() << 'n';
  
  //..............................................................................................

  
  //..............................................................................................
  
  double deltaTime(0.0);
  
  //... check that we had triggers from TTU/RBC
  m_wasTtuTrig = false;
  
  if( techTrigger24 || techTrigger25 ) {
    //m_bxDist->Fill( bxX );
    m_wasTtuTrig = true;
  }
  
  //..............................................................................................
  
  for( int iebx=0; iebx < 5; iebx++) {
    
    const TechnicalTriggerWord wTWord = gtRecord->technicalTriggerWord( iebx-2 );
    
    (*gzfileDump) << "TriggersByTTU: " 
                  << ieventX    << " "
                  << iorbitX    << " "
                  << bxX        << " "
                  << lumiSec    << " "
                  << "iebx: "   << ( iebx-2 ) << " ";
    
    for( int k=0; k < m_maxttBits; ++k) {
      
      bool ttBitResult = wTWord.at(24+k);
      (*gzfileDump) << ( 24+k ) << "= " << ttBitResult << " ";
      
    }
    
    if ( m_dtTrigger  ) (*gzfileDump) << "Dt: "  <<  (bxX - m_DTcandidatesBx[0])  << " ";
    if ( m_rpcTrigger ) (*gzfileDump) << "Pac: " <<  (bxX - m_GMTcandidatesBx[0]) << " ";
    
    (*gzfileDump) << '\n';
    
  }
  
  //..............................................................................................
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    bool ttBitResult = tWord.at(24+k);
    if ( ttBitResult ) {
      m_bxGTdistSelBit[k]->Fill( bxX );
      m_bxGTdistTTBits->Fill( bxX , 24+k , 1);
    }
    
    ttVec.push_back( ttBitResult );
    
  }
  
  if ( techTrigger24 )
    m_bxGTdistBit24->Fill( bxX );
  
  if ( techTrigger25 )
    m_bxGTdistBit25->Fill( bxX );
  
  if ( bxX >= m_bxNumMin && bxX < m_bxNumMax ) {
    
    if ( m_debug ) std::cout << std::setprecision(m_precision) << "Lookfor data in: " 
                             << ieventX  << " "
                             << iorbitX  << " " 
                             << bxX << " " 
                             << lumiSec << " "
                             << techTrigger24 << " "
                             << techTrigger25 << " "
                             << std::endl;
  }
  
  //..............................................................................................
  
  m_flag = 0;
  
  //..............................................................................................
  
  //....Get time information
  m_currentTime = evaluateTime ( iorbitX , bxX  );
  
  deltaTime = fabs(m_currentTime - m_previousTime);
  
  if ( deltaTime > 1.0 ) deltaTime = 0;
  
  m_totalTime   += deltaTime;
  m_elapsedTime += deltaTime;
  
  if ( m_elapsedTime > 1.0 ) { 
    
    m_infoObj->m_outputRate = true;
    
    for( int k=0; k < m_maxttBits; ++k) {
      
      m_trigRateHz[k]->Fill( m_totalTime, m_ntrigger[k] );
      m_trigRateDist[k]->Fill( m_ntrigger[k] );
      m_infoObj->m_ntriggered[k] = m_ntrigger[k];
      m_ntrigger[k] = 0;
      
    }
    
    m_elapsedTime = 0;
    
    
  } else m_infoObj->m_outputRate = false;
  
  (*gzfileDump) << "TTbits response: 24: " <<  techTrigger24 << " 25: " << techTrigger25
                << "timeinfo: "   << " "
                << m_totalTime    << " " 
                << deltaTime      << " "
                << m_elapsedTime  << " "
                << m_currentTime  << " "
                << m_previousTime << '\n';
  
  m_previousTime = m_currentTime;
  
  m_infoObj->m_flag = m_flag;
  
  m_infoObj->m_time = m_totalTime;
  
  //..............................................................................................
  
  lookatTracks( iEvent );
  
  lookatRecoMuons( iEvent , gtRecord );
  
  lookatRpcRecHits( iEvent , iSetup );
  
  lookatMinBiasTracks( iEvent );
  
  applySelection( iEvent, gtRecord);
  
  //..............................................................................................
  
  if ( m_hasCoincidenceAlgBit && m_was_triggered_Bit31 ) {
    
    (*gzfileDump) << "runId: " << runidX    << " "
                  << "evt: "   << ieventX   << " "
                  << "orbit: " << iorbitX   << " "
                  << "bxN: "   << bxX       << " "
                  << "Lum: "   << lumiSec   << " "
                  << "124: "   << m_hasCoincidenceAlgBit << " "
                  << "TT31: "  << m_was_triggered_Bit31 << " "
                  << "Tkr: "   << m_tracker_activity << '\n';
    
  }
  
  /////////////////////////////////////////////
  //Bit 31 History side by side:

  if ( m_was_triggered_Bit31 ) m_h_bit31_Compare[0]->Fill( 1 );
  if ( m_was_triggered_Bit31 && m_hasCoincidenceAlgBit ) m_h_bit31_Compare[0]->Fill( 2 );
  if ( m_was_triggered_Bit31 && m_hasCoincidenceAlgBit && m_tracker_activity ) m_h_bit31_Compare[0]->Fill( 3 );

  //Muons:
  if ( m_was_triggered_Bit31 && m_hasCoincidenceAlgBit && m_tracker_activity && m_has_STA_Muon ) 
    m_h_bit31_Compare[0]->Fill( 4 );
  
  if ( m_was_triggered_Bit31 && m_hasCoincidenceAlgBit && m_tracker_activity && m_has_Global_Muon ) 
    m_h_bit31_Compare[0]->Fill( 5 );

  //HLT_DT
    
  if ( m_was_triggered_Bit31 && m_hasActivity_DT ) m_h_bit31_Compare[1]->Fill( 6 );
  if ( m_was_triggered_Bit31 && m_hasActivity_DT &&  m_hasCoincidenceAlgBit ) m_h_bit31_Compare[1]->Fill( 7 );
  if ( m_was_triggered_Bit31 && m_hasActivity_DT &&  m_hasCoincidenceAlgBit &&  m_tracker_activity ) 
    m_h_bit31_Compare[1]->Fill( 8 );

  //Muons:
  if ( m_was_triggered_Bit31 && m_hasActivity_DT && m_hasCoincidenceAlgBit && m_tracker_activity  && m_has_STA_Muon ) 
    m_h_bit31_Compare[1]->Fill( 9 );

  if ( m_was_triggered_Bit31 && m_hasActivity_DT && m_hasCoincidenceAlgBit && m_tracker_activity && m_has_Global_Muon ) 
    m_h_bit31_Compare[1]->Fill( 10 );

  //...........

  if ( m_was_triggered_Bit31 && m_hasCoincidenceAlgBit && (!m_hasActivity_DT) )
  {
   
    (*gzfileDump) << "Bit31:yes DT:no "
                  << "runId: " << runidX    << " "
                  << "evt: "   << ieventX   << " "
                  << "orbit: " << iorbitX   << " "
                  << "bxN: "   << bxX       << " "
                  << "Lum: "   << lumiSec   << " "
                  << "124: "   << m_hasCoincidenceAlgBit << " "
                  << "TT31: "  << m_was_triggered_Bit31 << " "
                  << "Tkr: "   << m_tracker_activity << '\n'; 
        
  } else if ( m_hasActivity_DT && m_hasCoincidenceAlgBit && !(m_was_triggered_Bit31) )
  {
   
    (*gzfileDump) << "Bit31:no DT:yes "
                  << "runId: " << runidX    << " "
                  << "evt: "   << ieventX   << " "
                  << "orbit: " << iorbitX   << " "
                  << "bxN: "   << bxX       << " "
                  << "Lum: "   << lumiSec   << " "
                  << "124: "   << m_hasCoincidenceAlgBit << " "
                  << "TT31: "  << m_was_triggered_Bit31 << " "
                  << "Tkr: "   << m_tracker_activity << '\n'; 
    
  } else {}
              
  /////////////////////////////////////////////
  
  //Run history
  
  m_runSummaryA->Fill(1, 1); // evt counter
  m_runSummaryB->Fill(1, 1); // evt counter

  if ( techTrigger25 ) 
    m_runSummaryA->Fill(2, 1); // bit 25 at Bx=0

  const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(1);
  bool decision = gtTTWord[ 25 ];

  if ( decision ) 
    m_runSummaryA->Fill(3, 1); // bit 25 at Bx=1

  const DecisionWord gtAlgWord = gtRecord->decisionWord();

  for( int k=0; k < m_maxAlgBits; ++k ) {

    bool mu55decision = gtAlgWord[ m_singleMuBits[k] ];
        
    if ( mu55decision ) {
      m_runSummaryA->Fill( 4+k, 1 );
    }

    if ( techTrigger25 && mu55decision ) {
      m_runSummaryB->Fill( 4+k, 1 );
    }
    
  }
  

  /////////////////////////////////////////////
  
  ++m_nevt;  
  m_flag = -1;
  m_infoObj->m_maxttBits = m_maxttBits;
  m_infoObj->m_ievent = ieventX;
  m_infoObj->Write();
  m_infoObj->reset();

  m_GMTcandidatesBx.clear();
  m_DTcandidatesBx.clear();
  
  ttVec.clear();
  
  ttuDec25.clear();
  ttuDec28.clear();
  ttuDec31.clear();

  m_ntuple->fill();
      
}

int L1GtTtuAnalyzer::discriminateGMT( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
  
  //.............................................................................................
  
  edm::Handle<L1MuGMTReadoutCollection> pCollection;
  iEvent.getByLabel(m_gmtReadoutLabel, pCollection);
  
  if ( !pCollection.isValid() ) {
    std::cout << "L1GtTtuAnalyzer" << " can't find L1MuGMTReadoutCollection with label "
              << m_gmtReadoutLabel << '\n';
    ++m_GMTproblem;
    m_dtTrigger  = false;
    m_rpcTrigger = false;
    return -1;
    
  }
  
  //.............................................................................................
  
  int gmtDec(0);
  
  bool rpcBar_l1a  = false;
  bool rpcFwd_l1a  = false;
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
  
    m_bxNumber->Fill(BxInEvent);
      
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
                               << BxInEventNew << std::endl;
        
        m_GMTcandidatesBx.push_back( BxInEventNew );
        
        nrpcB++;
      }
    }

    for( RCItr = FwdRpcCands.begin(); RCItr !=FwdRpcCands.end(); ++RCItr) {
      if ( !(*RCItr).empty() ) {
        
        if( m_debug) std::cout << "Found " << nrpcF << " valid FWD RPC candidates in bx wrt. L1A = "
                               << (*RCItr).bx() << '\t'
                               << BxInEvent << '\t'
                               << BxInEventNew << std::endl;
        
        m_GMTcandidatesBx.push_back( BxInEventNew );
        
        nrpcF++;
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

long double L1GtTtuAnalyzer::evaluateTime ( unsigned int iorbit, unsigned int ibunch )
{
  
  unsigned long long time_Bx = ( 3564 * iorbit ) + ibunch;
  unsigned long long time_ns = ( ( 3564 * iorbit ) + ibunch ) * 25 ;
  
  int time_sec = ( time_ns ) / 1000000000;
  
  long double rmder = std::fmod( (long double) time_ns, (long double) 1000000000 );
  
  int rmder_ms = (int) std::floor (rmder / 1000000.0);

  long double fftime = (double) time_sec + (double) rmder_ms/1000.0;
  
  if (m_debug) std::cout << iorbit << " "
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

void L1GtTtuAnalyzer::getRpcInfo( const edm::Event & iEvent , const edm::EventSetup& iSetup)
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
      if ( m_debug ) std::cout << "TTUAnalyzer: roll is forward" << std::endl;
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
  
  if ( m_wasTtuTrig ) {
    for( itrBx = bx_ndigis.begin(); itrBx != bx_ndigis.end(); ++itrBx)
      m_bxInRpc->Fill ( (*itrBx).first );
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

int L1GtTtuAnalyzer::getBarrelLayer( const int & _layer, const int & _station )
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

void L1GtTtuAnalyzer::getRpcTechTriggerBits( const edm::Event & iEvent , const edm::EventSetup& iSetup ) 
{
  
  edm::Handle< L1GtTechnicalTriggerRecord > gtRecord;
  iEvent.getByLabel( m_rpcTechTrigEmu , gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "RPCTechnicalTrigger" << "can't find L1GtTechnicalTriggerRecord with label: " 
              << "rpcTechnicalTrigger" << '\n';
    return;
  }
  
  std::vector<L1GtTechnicalTrigger> m_ttVec;
  
  m_ttVec = gtRecord->gtTechnicalTrigger();
  
  //std::cout << "Size of technical trigger vector" << m_ttVec.size() << std::endl;
  
  std::vector<L1GtTechnicalTrigger>::const_iterator ttItr;
  
  bool wasEventTriggered(false);
  
  int k = 0;
  
  for( ttItr = m_ttVec.begin(); ttItr != m_ttVec.end(); ++ttItr) {
    
    if ( m_debug ) std::cout << "L1GtTechnicalTrigger> " 
                             << (*ttItr).bxInEvent() << '\t'
                             << (*ttItr).gtTechnicalTriggerBitNumber() << '\t'
                             << (*ttItr).gtTechnicalTriggerResult() << '\n';
    
    m_infoObj->setTechnicalTriggerBits( (*ttItr).gtTechnicalTriggerBitNumber(),
                                        (*ttItr).bxInEvent(),
                                        (*ttItr).gtTechnicalTriggerResult() );
    
    m_ttBitsDecision->Fill( (*ttItr).gtTechnicalTriggerBitNumber(), (int) (*ttItr).gtTechnicalTriggerResult() );
    
    wasEventTriggered = (*ttItr).gtTechnicalTriggerResult();

    m_rpcTechBits.push_back( wasEventTriggered );
    
    if ( wasEventTriggered ) ++m_ntrigger[k];
    
    ++k;
    
  }
    
  
}

void L1GtTtuAnalyzer::lookatRecoMuons(const edm::Event & iEvent , const edm::Handle< L1GlobalTriggerReadoutRecord > & gtRecord ) 
{

  //
  unsigned int runidX  = iEvent.run();
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
  unsigned int lumiSec = iEvent.luminosityBlock();
  
  edm::Handle< edm::View<reco::Muon> > muonHandle;
  iEvent.getByLabel(m_recoMuonLabel, muonHandle);
  
  if ( ! muonHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the muon Handle"  << std::endl;
    return;
  }
  
  edm::View<reco::Muon>::const_iterator muon;
  
  //.................................................................................................................
  
  m_muonType.clear();
  
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  double x0 = beamSpot.x0();
  double y0 = beamSpot.y0();
  
  int num_Mu(0);
  
  if ( m_rpcTechBits.size() <= 0 ) return;
  
  bool isTriggeredBy25 = m_rpcTechBits[1];
  
  m_pointingTrack->Fill( (int) isTriggeredBy25 ); //all bits in all the events

  std::vector<reco::Muon> candidates;

  m_has_STA_Muon = false;
  m_has_Global_Muon = false;
  m_has_TRK_Muon = false;
  
  for( muon=muonHandle->begin(); muon != muonHandle->end(); ++muon) {
    
    ++num_Mu;
    
    int mu_type(0);
    
    if(muon->isStandAloneMuon())
      if(muon->isGlobalMuon())
        if(muon->isTrackerMuon()) mu_type = 1;  // 1= STA + GLB + TM
        else mu_type = 2;                       // 2= STA + GLB
      else 
        if(muon->isTrackerMuon()) mu_type = 3;  // 3= STA + TM
        else mu_type = 5;                       // 5= STA
    else
      if(muon->isTrackerMuon()) mu_type = 4;    // 4= TM
    
    MuonType->Fill( mu_type );
    
    m_muonType.push_back( mu_type );
    
    //....................................................................
    
    (*gzfileDump) << "runId: " << runidX    << " "
                  << "evt: "   << ieventX   << " "
                  << "orbit: " << iorbitX   << " "
                  << "bxN: "   << bxX       << " "
                  << "Lum: "   << lumiSec   << " "
                  << "124: "   << m_hasCoincidenceAlgBit << " "
                  << "Tkr: "   << m_tracker_activity << " "
                  << "Muon Type: " << mu_type << '\n';
    
    //....................................................................
    /// look at pure STA muons
    
    if ( mu_type == 5 ) {
      
      float Muond0_STA  = muon->standAloneMuon()->d0() 
        - x0*sin( muon->standAloneMuon()->phi() ) 
        - y0*cos( muon->standAloneMuon()->phi() );
      float Muondsz_STA = muon->standAloneMuon()->dsz();
      float MuonChi2 = muon->standAloneMuon()->normalizedChi2 ();
      
      //...
      MuonEta_STA->Fill( muon->standAloneMuon()->eta() );
      MuonPhi_STA->Fill( muon->standAloneMuon()->phi() );
      MuonPt_STA->Fill( muon->standAloneMuon()->pt() );
      MuonEtaPhi_STA->Fill(  muon->standAloneMuon()->eta(), muon->standAloneMuon()->phi() );
      Muond0dist_STA->Fill( Muond0_STA );
      Muondszdist_STA->Fill( Muondsz_STA );
      MuonChi2DoF_STA->Fill( MuonChi2 );
      
      m_has_STA_Muon |= true;

      for( int k=0; k < m_maxttBits; ++k ) {
        if ( m_rpcTechBits[k] ) {
          m_HMuonSTAPt_Bit[k]->Fill( muon->standAloneMuon()->pt() );
          m_HMuonSTAEtaPhi_Bit[k]->Fill( muon->standAloneMuon()->eta(), muon->standAloneMuon()->phi() );
          m_HMuonSTAd0dist_Bit[k]->Fill( Muond0_STA );
          m_HMuonSTAdszdist_Bit[k]->Fill( Muondsz_STA );
          
        }
        
      }
      
      if( m_hasActivity_DT ) m_h_pt_HLT_STA->Fill( muon->standAloneMuon()->pt() );
      
      if( m_was_triggered_Bit31 ) m_h_pt_TTU_STA->Fill( muon->standAloneMuon()->pt() );
      
      if( m_hasActivity_DT && m_was_triggered_Bit31 ) {
        m_hh_pt_STA->Fill( muon->standAloneMuon()->pt(), muon->standAloneMuon()->pt() );
      }
      else if ( m_hasActivity_DT && !(m_was_triggered_Bit31) )  { //this is the bx=0 bit 31
        m_hh_pt_STA->Fill( muon->standAloneMuon()->pt(), 0.0 );
        
        for( int iebx=0; iebx< 5; iebx++) {
          const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(iebx-2);
          bool triggerAt = gtTTWord[31];
          if ( triggerAt ) m_h_bx_failed_STA->Fill( iebx-2 );
        }
        
      }
      else if ( !(m_hasActivity_DT) && m_was_triggered_Bit31 ) {
        m_hh_pt_STA->Fill( 0.0, muon->standAloneMuon()->pt() );
      }
      else {}
      
    }
    
    //....................................................................
    /// look at pure GBL muons

    else if ( mu_type == 1 ) {
      
      candidates.push_back( (*muon) );
      
      float Muond0_GBL =  muon->globalTrack()->d0() 
        - x0*sin( muon->globalTrack()->phi() ) 
        - y0*cos( muon->globalTrack()->phi() );
      float Muondsz_GBL = muon->globalTrack()->dsz();
      float MuonChi2 = muon->globalTrack()->normalizedChi2 ();
      
      //...
      MuonPt_GBL->Fill( muon->globalTrack()->pt() );
      MuonEtaPhi_GBL->Fill( muon->globalTrack()->eta(), muon->globalTrack()->phi() );
      Muond0dist_GBL->Fill( Muond0_GBL );
      Muondszdist_GBL->Fill( Muondsz_GBL );
      MuonChi2DoF_GBL->Fill( MuonChi2 );
      
  
      for( int k=0; k < m_maxttBits; ++k ) {
        if ( m_rpcTechBits[k] ) {
          m_HMuonGBLPt_Bit[k]->Fill( muon->globalTrack()->pt() );
          m_HMuonGBLEtaPhi_Bit[k]->Fill( muon->globalTrack()->eta(), muon->globalTrack()->phi() );
          m_HMuonGBLd0dist_Bit[k]->Fill( Muond0_GBL );
          m_HMuonGBLdszdist_Bit[k]->Fill( Muondsz_GBL );
          
        }
        
      }
      
      m_has_Global_Muon |= true; //has at least a global muon

      if( m_hasActivity_DT ) m_h_pt_HLT_GBL->Fill( muon->globalTrack()->pt() );
      
      if( m_was_triggered_Bit31 ) m_h_pt_TTU_GBL->Fill( muon->globalTrack()->pt());
      
      if( m_hasActivity_DT && m_was_triggered_Bit31 ) {
        m_hh_pt_GBL->Fill( muon->standAloneMuon()->pt(), muon->standAloneMuon()->pt() );
      }
      else if ( m_hasActivity_DT && !(m_was_triggered_Bit31) ) {

        m_hh_pt_GBL->Fill( muon->standAloneMuon()->pt(), 0.0 );

        for( int iebx=0; iebx < 5; iebx++) {
          const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(iebx-2);
          bool triggerAt = gtTTWord[31];
          if ( triggerAt ) m_h_bx_failed_GBL->Fill( iebx-2 );
        }
        
      }
      else if ( !(m_hasActivity_DT) && m_was_triggered_Bit31 ) {
        m_hh_pt_GBL->Fill( 0.0, muon->standAloneMuon()->pt() );
      }
      else {}
      

    } 

    //....................................................................
    /// look at pure TRK muons

    else if ( muon->isTrackerMuon() ) {
      
      candidates.push_back( (*muon) );
      
      float Muond0_TRK =  muon->track()->d0() 
        - x0*sin( muon->track()->phi() ) 
        - y0*cos( muon->track()->phi() );
      float Muondsz_TRK = muon->track()->dsz();
      float MuonChi2 = muon->track()->normalizedChi2 ();
      
      //...
      MuonPt_TRK->Fill( muon->track()->pt() );
      MuonEtaPhi_TRK->Fill( muon->track()->eta(), muon->track()->phi() );
      Muond0dist_TRK->Fill( Muond0_TRK );
      Muondszdist_TRK->Fill( Muondsz_TRK );
      MuonChi2DoF_TRK->Fill( MuonChi2 );
      
      
      for( int k=0; k < m_maxttBits; ++k ) {
        if ( m_rpcTechBits[k] ) {
          m_HMuonTRKPt_Bit[k]->Fill( muon->track()->pt() );
          m_HMuonTRKEtaPhi_Bit[k]->Fill( muon->track()->eta(), muon->track()->phi() );
          m_HMuonTRKd0dist_Bit[k]->Fill( Muond0_TRK);
          m_HMuonTRKdszdist_Bit[k]->Fill( Muondsz_TRK );
          
        }
        
      }
      
      m_has_TRK_Muon |= true; 

      if( m_hasActivity_DT ) m_h_pt_HLT_TRK->Fill( muon->track()->pt() );
      
      if( m_was_triggered_Bit31 ) m_h_pt_TTU_TRK->Fill( muon->track()->pt());
      
      if( m_hasActivity_DT && m_was_triggered_Bit31 ) {
        m_hh_pt_TRK->Fill( muon->track()->pt(), muon->track()->pt() );
      }
      else if ( m_hasActivity_DT && !(m_was_triggered_Bit31) ) {

        m_hh_pt_TRK->Fill( muon->track()->pt(), 0.0 );

        for( int iebx=0; iebx < 5; iebx++) {
          const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(iebx-2);
          bool triggerAt = gtTTWord[31];
          if ( triggerAt ) m_h_bx_failed_TRK->Fill( iebx-2 );
        }
        
      }
      else if ( !(m_hasActivity_DT) && m_was_triggered_Bit31 ) {
        m_hh_pt_TRK->Fill( 0.0, muon->standAloneMuon()->pt() );
      }
      else {}
      
    }

    else { 
      // not in use subcategory 
    }
        
  }
  
  NumberMuonsEvt->Fill(num_Mu);
  
  //.................................................................................................................
  
  if ( m_muonType.size() == 0 )
    m_pointingTrack_0mu->Fill( (int) isTriggeredBy25 );
  
  else if ( m_muonType.size() == 1 ) {
    
    if ( ( m_muonType[0] != 1 ) )
      m_pointingTrack_1mu->Fill( (int) isTriggeredBy25 );
    
  }
  
  else if ( m_muonType.size() == 2 ) {
    
    if ( ( m_muonType[0] != 1  && m_muonType[1] != 1 ) || 
         ( m_muonType[0] != 1  || m_muonType[1] != 1 )    )
      m_pointingTrack_2mu->Fill( (int) isTriggeredBy25 );
    
  } else {}
  
  
  if ( candidates.size() == 2 ) {
    
    double Minv = ( candidates[0].p4() + candidates[1].p4() ).mass();
    h_mumu_InvMm->Fill(Minv);
    
  }
  
  candidates.clear();
  
  //.................................................................................................................

}

void L1GtTtuAnalyzer::lookatTracks(const edm::Event & iEvent ) 
{
  
  //
  // Tracker: Only for Cosmics samples
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
 
  edm::Handle< edm::View<reco::Track> > tracksHandle;
  iEvent.getByLabel(m_recoTracksLabel, tracksHandle);
  
  if ( ! tracksHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the tracks Handle"  << std::endl;
    return;
  }

  edm::Handle< edm::View<reco::Track> > cosmicsHandle;
  iEvent.getByLabel(m_recoCosmicsLabel, cosmicsHandle);
  
  if ( ! cosmicsHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the cosmics Handle"  << std::endl;
    return;
  } 
  
  edm::View<reco::Track>::const_iterator track;
  edm::View<reco::Track>::const_iterator cosmic;
  
  //.................................................................................................................
  
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  double x0 = beamSpot.x0();
  double y0 = beamSpot.y0();
  
  int num_Tks(0);
  
  if ( m_rpcTechBits.size() <= 0 ) return;

  bool isTriggeredBy24 = m_rpcTechBits[0];
  bool isTriggeredBy25 = m_rpcTechBits[1];
  //bool isTriggeredBy31 = m_rpcTechBits[7];
  
  m_pointingTrack->Fill( (int) isTriggeredBy25 ); //all bits in all the events
  std::vector<bool> TrackLocation;
  
  std::vector<double> TrackMomentum;
  std::vector<double> TrackPhi;
  std::vector<double> TrackEta;
  std::vector<double> TrackD0;
  std::vector<double> TrackDz;
  
  bool isInTracker(false);
  
  int num_Tks_in_Tracker(0);
  int num_Tks_in_Tracker_By25(0);
  int num_Hits_in_Tracker_By25(0);

  bool  has_Hits_in_Tracker(false);
  
  if ( tracksHandle->size() > 0 ) has_Hits_in_Tracker = true;
  
  int max_cosmics = cosmicsHandle->size();
  
  for( cosmic=cosmicsHandle->begin(); cosmic != cosmicsHandle->end(); ++cosmic) {
    
    ++num_Tks;
    
    // select only those in the region of the tracker
    //.
    const DetId detid( (*cosmic).outerDetId() );
    //std::cout << "detID: " << (*cosmic).outerDetId() << " " << detid.det() << std::endl;
    
    float Trackd0 =  cosmic->d0() 
      - x0*sin( cosmic->phi() ) 
      - y0*cos( cosmic->phi() );
    
    float Tracksz = cosmic->dsz();

    double trkPt    = cosmic->pt();
    double trkPhi   = cosmic->phi();
    double trkEta   = cosmic->eta();
    double trkD0    = Trackd0;
    double trkDz    = Tracksz;
    
    //if ( isTriggeredBy25 && max_cosmics == 2)
    //  
    
    if ( fabs( Trackd0 ) < m_trackerHeight )
      if ( fabs( Tracksz ) < m_trackerLength )
        isInTracker = true;
    
    if ( isInTracker ) 
      ++num_Tks_in_Tracker;
    
    if ( isInTracker && isTriggeredBy25 ) 
      ++num_Tks_in_Tracker_By25;

    if ( isInTracker && isTriggeredBy25 && has_Hits_in_Tracker )
      ++num_Hits_in_Tracker_By25;

    const math::XYZPoint trackInpos = cosmic->innerPosition();
    const math::XYZPoint trackOutpos = cosmic->outerPosition();
    
    float sf = 1.3;
    
    if (  isTriggeredBy25 ) {
      m_hh_xy_inner_bit25->Fill( trackInpos.x(), trackInpos.y() );
      m_hh_xy_outer_bit25->Fill( trackOutpos.x(), trackOutpos.y() );

      m_hh_yz_inner_bit25->Fill( trackInpos.z()*sf, trackInpos.y() );
      m_hh_yz_outer_bit25->Fill( trackOutpos.z()*sf, trackOutpos.y() );
    
      (*gzfileDump) << "InnerOuterPos25: " 
                    << trackInpos.x()  << " "
                    << trackInpos.y()  << " "
                    << trackInpos.z()*sf << " " 
                    << trackOutpos.x() << " "
                    << trackOutpos.y() << " " 
                    << trackOutpos.z()*sf << " " 
                    << max_cosmics     << '\n';
      
    } else if ( isTriggeredBy24 ) {
      m_hh_xy_inner_bit24->Fill( trackInpos.x(), trackInpos.y() );
      m_hh_xy_outer_bit24->Fill( trackOutpos.x(), trackOutpos.y() );
      
      m_hh_yz_inner_bit24->Fill( trackInpos.z()*sf, trackInpos.y() );
      m_hh_yz_outer_bit24->Fill( trackOutpos.z()*sf, trackOutpos.y() );
    
      (*gzfileDump) << "InnerOuterPos24: "
                    << trackInpos.x()  << " "
                    << trackInpos.y()  << " "
                    << trackInpos.z()*sf  << " "
                    << trackOutpos.x() << " "
                    << trackOutpos.y() << " "
                    << trackOutpos.z()*sf << " " 
                    << max_cosmics     << '\n';
    } else {}
    
    (*gzfileDump) << ieventX   << " "
                  << iorbitX   << " "
                  << bxX       << " "
                  << "Tkc: "   << isInTracker << " "
                  << "B25: "   << isTriggeredBy25 << " "
                  << "InTkc: " << has_Hits_in_Tracker << " "
                  << "Ncm: "   << max_cosmics << '\n';
    
    TrackLocation.push_back( isInTracker );
    TrackMomentum.push_back( trkPt );
    TrackPhi.push_back( trkPhi );
    TrackEta.push_back( trkEta );
    TrackD0.push_back(  trkD0 );
    TrackDz.push_back(  trkDz );
    
    isInTracker = false;
    
  }
  
  NumberTracksEvt->Fill(num_Tks);
  
  if( num_Tks >= 1 ) {
     
    NumberPointingTracksEvt->Fill(num_Tks_in_Tracker);
    NumberPointingTracksEvtBy25->Fill(num_Tks_in_Tracker_By25);
    NumberPointingHitsTrackerEvtByEvt25->Fill(num_Hits_in_Tracker_By25);
    
  }

  //.................................................................................................................
  
  if( isTriggeredBy25 ) {
    
    ++m_totalBit25;
    m_total_bit25_triggers->Fill(1); //Total.Bit.25.triggers
    
    if ( max_cosmics > 0 ) {
      ++m_totalBit25Muon;
      m_total_bit25_cosmics->Fill(2); //Total.Bit.25.Any.Cosmics
    }
    
    for ( int i = 0; i < num_Tks; ++i) {
      TrackerPt_All_bit25->Fill( TrackMomentum[i] );             //TrackPt.ALL.bit.25
      m_hh_eta_phi_all_bit25->Fill( TrackEta[i],TrackPhi[i] );   //Cosmic.Eta.Phi.All
      m_hh_d0_dz_all_bit25->Fill( TrackDz[i], TrackD0[i] );      //Cosmic.d0.dz.All
    }
    
  }
  
  //.................................................................................................................

  if ( num_Tks == 0 ) {
    m_pointingTrack_0mu->Fill( (int) isTriggeredBy25 );
    if ( isTriggeredBy25 )
      m_pointingTrkCode->Fill( 1 );
  }
  
  else if ( num_Tks == 1 ) {
    if ( ! TrackLocation[0] ) {

      m_pointingTrack_1mu->Fill( (int) isTriggeredBy25 );

      if ( isTriggeredBy25 ) {
        m_pointingTrkCode->Fill( 3 );
        
      }
      
    } else {
      if ( isTriggeredBy25 ) {
        
        m_pointingTrkCodeIn->Fill( 4 );
        TrackerPt_In_bit25->Fill( TrackMomentum[0] );
        
        if ( has_Hits_in_Tracker ) {
          TrackerPt_In_CTF_bit25->Fill( TrackMomentum[0] );
        }
      }
    }
  } 
  else if ( num_Tks == 2 ) {

    double ptdiff = TrackMomentum[0]-TrackMomentum[1];
    
    m_hh_TwoLegsDifference_bit25->Fill( ptdiff , TrackDz[0] - TrackDz[1] );
    
    if ( fabs( ptdiff ) < 100.0 ) 
      (*gzfileDump) << "LegDiffs: "
                    << TrackMomentum[0] << " "
                    << TrackMomentum[1] << " "
                    << TrackMomentum[0]-TrackMomentum[1] << " "
                    << TrackDz[0] - TrackDz[1] << " "
                    << TrackD0[0] - TrackD0[1] << '\n';
    
    if ( ( ! TrackLocation[0] && ! TrackLocation[1] ) ) {
      
      m_pointingTrack_2mu->Fill( (int) isTriggeredBy25 );
      
      if ( isTriggeredBy25 ) {
        
        m_pointingTrkCode->Fill( 5 );
        TrackerPt_Out_bit25->Fill( TrackMomentum[0] );
        TrackerPt_Out_bit25->Fill( TrackMomentum[1] );
        
        if ( has_Hits_in_Tracker ) {
          TrackerPt_Out_CTF_bit25->Fill( TrackMomentum[0] );
          TrackerPt_Out_CTF_bit25->Fill( TrackMomentum[1] );
        }
      }
    } else {
      if ( isTriggeredBy25 ) {
        m_pointingTrkCodeIn->Fill( 6 );
        
        TrackerPt_In_bit25->Fill( TrackMomentum[0] );
        TrackerPt_In_bit25->Fill( TrackMomentum[1] );
        m_hh_eta_phi_trk_bit25->Fill( TrackEta[0],TrackPhi[0] );
        m_hh_eta_phi_trk_bit25->Fill( TrackEta[1],TrackPhi[1] );
        m_hh_d0_dz_trk_bit25->Fill( TrackDz[0],TrackD0[0] );
        m_hh_d0_dz_trk_bit25->Fill( TrackDz[1],TrackD0[1] );
        
        if ( has_Hits_in_Tracker ) {
          
          TrackerPt_In_CTF_bit25->Fill( TrackMomentum[0] );
          TrackerPt_In_CTF_bit25->Fill( TrackMomentum[1] );
          m_hh_eta_phi_ctf_bit25->Fill( TrackEta[0],TrackPhi[0] );
          m_hh_eta_phi_ctf_bit25->Fill( TrackEta[1],TrackPhi[1] );
          m_hh_d0_dz_ctf_bit25->Fill( TrackDz[0],TrackD0[0] );
          m_hh_d0_dz_ctf_bit25->Fill( TrackDz[1],TrackD0[1] );
          
        }
      }
    }
  }

  else if ( num_Tks >= 3 ) {
    if ( ( ! TrackLocation[0] && ! TrackLocation[1] ) || 
         ( ! TrackLocation[0] && ! TrackLocation[2] ) ||
         ( ! TrackLocation[1] && ! TrackLocation[2] ) ) {
      m_pointingTrack_3mu->Fill( (int) isTriggeredBy25 );
      
      if ( isTriggeredBy25 ) {
        m_pointingTrkCode->Fill( 7 );
        
        ///
      }
      
    } else {
      if ( isTriggeredBy25 ) {
        
        m_pointingTrkCodeIn->Fill( 8 );
        ///
        int bestPar = evaluateDistance( TrackMomentum, TrackDz );
        std::bitset<8> comb = m_combinations[ bestPar ];
        
        for( int k=0; k < 3 ; ++k) {
          if ( comb[k] ) {
            
            TrackerPt_In_bit25->Fill( TrackMomentum[k] );
            m_hh_eta_phi_trk_bit25->Fill( TrackEta[k],TrackPhi[k] );
            m_hh_d0_dz_trk_bit25->Fill( TrackDz[k],TrackD0[k] );
            
            if ( has_Hits_in_Tracker ) {
              
              TrackerPt_In_CTF_bit25->Fill( TrackMomentum[k] );
              m_hh_eta_phi_ctf_bit25->Fill( TrackEta[k],TrackPhi[k] );
              m_hh_d0_dz_ctf_bit25->Fill( TrackDz[k],TrackD0[k] );
          
            }
          }
        }
      }
    }
  } 
  
  else { }
  
  //.................................................................................................................
  
  TrackLocation.clear();
  TrackMomentum.clear();
  TrackPhi.clear();
  TrackEta.clear();
  TrackD0.clear();
  TrackDz.clear();
    
}

void 
L1GtTtuAnalyzer::lookatMinBiasTracks(const edm::Event & iEvent ) 
{

  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
  //unsigned int lumiSec = iEvent.luminosityBlock();

  //.................................................................................................................
  edm::Handle< edm::View<reco::Track> > tracksHandle;
  iEvent.getByLabel(m_recoTracksLabel, tracksHandle);
  
  if ( ! tracksHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the tracks Handle"  << std::endl;
    return;
  }
  
  edm::View<reco::Track>::const_iterator track;
  //.................................................................................................................
  
  //.................................................................................................................
  edm::Handle< edmNew::DetSetVector<SiStripCluster> > siStripHandle;
  iEvent.getByLabel(m_recoSiStripLabel, siStripHandle);
  
  if ( ! siStripHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the SiStripCluster Handle"  << std::endl;
    return;
  }
  
  edm::View< edmNew::DetSetVector<SiStripCluster> >::const_iterator strip;
  //.................................................................................................................
  
  //.................................................................................................................
  edm::Handle< edmNew::DetSetVector<SiPixelCluster> > siPixelHandle;
  iEvent.getByLabel(m_recoPixelLabel, siPixelHandle);
  
  if ( ! siPixelHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the SiPixelCluster Handle"  << std::endl;
    return;
  }
  
  edm::View< edmNew::DetSetVector<SiPixelCluster> >::const_iterator pixel;
  //.................................................................................................................

  int max_strip_clusters = (*siStripHandle).size();
  int max_pixel_clusters = (*siPixelHandle).size();
  
  if ( max_strip_clusters > 0 || max_pixel_clusters > 0 ) m_tracker_activity = true;
  else m_tracker_activity = false;
  
  //std::cout <<  (*siStripHandle).size()  <<  std::endl;
  //std::cout <<  (*siPixelHandle).size()  <<  std::endl;
  
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  double x0 = beamSpot.x0();
  double y0 = beamSpot.y0();
  
  //int num_Tks(0);
  int max_tracks(0);
  
  if ( m_rpcTechBits.size() <= 0 ) return;
  
  bool isTriggeredBy31 = m_rpcTechBits[7];
  
  //   std::vector<bool> TrackLocation;
  
  std::vector<double> TrackMomentum;
  std::vector<double> TrackPhi;
  std::vector<double> TrackEta;
  std::vector<double> TrackD0;
  std::vector<double> TrackDz;
  
  bool isInTracker(false);
  
  //int num_Tks_in_Tracker(0);
  //int num_Tks_in_Tracker_By31(0);
  //int num_Hits_in_Tracker_By31(0);
  
  m_has_Hits_in_Tracker = false;
  
  max_tracks = tracksHandle->size();
  
  if ( max_tracks > 0 ) m_has_Hits_in_Tracker = true;
  
  for( track=tracksHandle->begin(); track != tracksHandle->end(); ++track) {
    
    // select only those in the region of the tracker
    //.
    const DetId detid( (*track).outerDetId() );
        
    float Trackd0 =  track->d0() 
      - x0*sin( track->phi() ) 
      - y0*cos( track->phi() );
    
    float  Tracksz  = track->dsz();
    //double trkPt    = track->pt();
    //double trkPhi   = track->phi();
    //double trkEta   = track->eta();
    //double trkD0    = Trackd0;
    //double trkDz    = Tracksz;
    
    if ( fabs( Trackd0 ) < m_trackerHeight )
      if ( fabs( Tracksz ) < m_trackerLength )
        isInTracker = true;
    
    const math::XYZPoint trackInpos = track->innerPosition();
    const math::XYZPoint trackOutpos = track->outerPosition();
    
    (*gzfileDump) << ieventX   << " "
                  << iorbitX   << " "
                  << bxX       << " "
                  << "Tkc: "   << isInTracker << " "
                  << "B31: "   << isTriggeredBy31 << " "
                  << "InTkc: " << m_has_Hits_in_Tracker << " "
                  << "Ncm: "   << max_tracks << '\n';
    
  }
    
}

int L1GtTtuAnalyzer::evaluateDistance( const std::vector<double> & tksPt, const std::vector<double> & tksDz )
{
  
  int max_comb = m_combinations.size();
  int max_tracks = tksPt.size();

  (*gzfileDump) << "Diff+3tracks: ";
  int sel_comb = 0;
  double dist=0.0;
  double mindist=0.0;
  
  for ( int i=0; i < max_comb; ++i ) {
    
    std::bitset<8> comb = m_combinations[i+1];
    double ptdiff = 0.0;
    double dzdiff = 0.0;
    
    for( int k=0; k < max_tracks; ++k) {
      if ( comb[k] ) {
        ptdiff=tksPt[k] - ptdiff;
        dzdiff=tksDz[k] - dzdiff;
      }
      (*gzfileDump) << tksPt[k] << " " << tksDz[k] << " ";
    }
    
    dist = sqrt( ptdiff*ptdiff + dzdiff*dzdiff);
    if ( i == 0 ) mindist = dist;
    if ( dist < mindist ) sel_comb = (i+1);
    
    (*gzfileDump) << ptdiff << " " << dzdiff << " ";
    
  }
  
  (*gzfileDump) << "selComb: " << sel_comb << '\n';
  
  return sel_comb;
  
}

void
L1GtTtuAnalyzer::lookatRpcRecHits(const edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  
  //.................................................................................................................
  
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
  unsigned int lumiSec = iEvent.luminosityBlock();
  
  //.................................................................................................................
  edm::Handle<RPCRecHitCollection> rpcRecHits; 
  iEvent.getByLabel("rpcRecHits","",rpcRecHits);
  
  if ( ! rpcRecHits.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the RPC RecHits Handle"  << std::endl;
    return;
  }
  
  //.................................................................................................................  
  
  edm::ESHandle<RPCGeometry> geom;
  iSetup.get<MuonGeometryRecord> ().get (geom);
  
  if ( ! geom.isValid () ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the RPC Geometry Handler"  << std::endl;
    return;
  }
  
  //.................................................................................................................  
  // count the number of RPC rechits
  int nRPC = 0;
  int nRPC_in_Station[4];
  nRPC_in_Station[0] = 0;
  nRPC_in_Station[1] = 0;
  nRPC_in_Station[2] = 0;
  nRPC_in_Station[3] = 0;
    
  RPCRecHitCollection::const_iterator rpcIt;
  
  bool has_Hits_Station_1  = false;
  bool has_Hits_Station_34 = false;
  int has_Hits_Station_1_Wheel = -100;
  int has_Hits_Station_34_Wheel = -100;
  int ri = 0;
  int nRecHits = 0;
  int riE = 0;
  int nRecHitsEndcap = 0;
  
  m_apply_Cosmic_Veto = false;

  //.................................................................................................................  
  
  for (rpcIt = rpcRecHits->begin(); rpcIt != rpcRecHits->end(); ++rpcIt) {

    LocalPoint rhitlocal = (*rpcIt).localPosition();
    RPCDetId id  = (RPCDetId)(*rpcIt).rpcId();
    int kRegion  = id.region();

    const GeomDetUnit *det = geom->idToDetUnit ( id );
    
    GlobalPoint gp = det->toGlobal( rhitlocal );
    
    float xg = gp.x ();
    float yg = gp.y ();
    float zg = gp.z ();
    
    int kStation = id.station();
    int kRing    = id.ring();
    int kSector  = id.sector();
    int kLayer   = id.layer();
    
    if ( kRegion == 0 ) {
      
      int blayer   = getBarrelLayer( kLayer, kStation );     // 1 to 6
      
      //TTU ntuple
      if ( ri < m_ntuple->MAX_RHITS ) {
        
        m_ntuple->rpcHit_BX[ ri ] = (*rpcIt).BunchX();
        m_ntuple->rpcHit_Station[ ri ] = kStation;
        m_ntuple->rpcHit_Ring[ ri ] = kRing;
        m_ntuple->rpcHit_Sector[ ri ] = kSector;
        m_ntuple->rpcHit_Layer[ ri ] = blayer;
        m_ntuple->rpcHit_X[ ri ] = xg;
        m_ntuple->rpcHit_Y[ ri ] = yg;
        m_ntuple->rpcHit_Z[ ri ] = zg;
        
        ++nRecHits; //Rechits in Barrel
        ++ri; // index for ntuple
        
      }
      
      if ( (*rpcIt).BunchX() == 0 ) {
        
        m_h_RpcHits_Layer_All->Fill( blayer );
        m_h_RpcHits_Sector_All->Fill ( kSector );
        m_h_RpcHits_Wheel_All->Fill( kRing );
        m_hh_xy_rpc_rechit_All->Fill( xg, yg );
        m_hh_yz_rpc_rechit_All->Fill( zg, yg );
        
        if ( ttVec.size() > 0 ) {
          
          for( int k=0; k < m_maxttBits; ++k) {
            
            if ( ttVec[k] ) {
              
              m_h_RpcHits_Layer[k]->Fill( blayer );
              m_h_RpcHits_Sector[k]->Fill( kSector );
              
              m_h_RpcHits_Wheel[k]->Fill( kRing );
              m_hh_xy_rpc_rechit[k]->Fill( xg, yg );
              m_hh_yz_rpc_rechit[k]->Fill( zg, yg );
              
            }
          }
        }
        
        for ( int k=1; k< 5; ++k)
          if ( kStation == k )
            ++nRPC_in_Station[k-1];
        
        ++nRPC;
        
      }

      //.................................................................................................................

      
      if ( kStation == 1 && ( (*rpcIt).BunchX() == 0) ) { has_Hits_Station_1 = true; has_Hits_Station_1_Wheel = kRing; }
      else if ( kStation == 3 || kStation == 4) { has_Hits_Station_34 = true; has_Hits_Station_34_Wheel = kRing; }
      else {}
      
      //... std::cout << "rpcRecHits: apply_veto: " << ieventX << " " << kStation << " " << m_apply_Cosmic_Veto << '\n';
      //....................................
      
      (*gzfileDump) << "RecHitInfo: evt=" << ieventX 
                    << " W=" << kRing 
                    << " S=" << kSector
                    << " St=" << kStation 
                    << " L=" << blayer
                    << " P=" << kLayer
                    << " bx=" << (*rpcIt).BunchX() << '\n' ;
      
      if ( ttVec.size() > 0 ) {
        for( int k=0; k < m_maxttBits; ++k) {
          if ( ttVec[k] ) {
            m_hh_bx_rpc_rechit_Bit[k]->Fill( (*rpcIt).BunchX(), kStation );
            if( has_Hits_Station_1_Wheel ==  has_Hits_Station_34_Wheel ) {
              m_hh_bx_rpc_rechit_wheel_Bit[k]->Fill( (*rpcIt).BunchX(), kStation );
            }
            
          } else {
            m_hh_bx_rpc_rechit_NoBit[k]->Fill( (*rpcIt).BunchX(), kStation );
          }
        }
      }
      
      m_hh_bx_rpc_rechit_All->Fill( (*rpcIt).BunchX(), kStation );
    
      ///....more detailed histograms:
      bool isTriggeredBy31 = m_rpcTechBits[7];
      
      if ( isTriggeredBy31 ) {
        
        for( int k= -2; k <= 2; ++k ) {
          
          if( kRing == k ) { 
            
            if ( kSector > 1 && kSector < 7 ) 
              m_h_RpcHits_WheelBxTop[k+2]->Fill( (*rpcIt).BunchX() , blayer , 1 );
            else
              m_h_RpcHits_WheelBxBot[k+2]->Fill( (*rpcIt).BunchX() , blayer , 1 );
            
            for( int bx = -3; bx <=3; ++bx ) {
              
              if( kRing == k && ( (*rpcIt).BunchX() == bx ) )
                m_h_RpcHits_WheelBx[k+2][bx+3]->Fill( xg, yg );
              
            }
            
          }
          
        }
        
      }
      
    } else if ( abs( kRegion ) == 1 ) {

      //.................................................................................................................
      //TTU ntuple
      if ( riE < m_ntuple->MAX_RHITS ) {
        
        m_ntuple->rpcHit_BX_E[ riE ] = (*rpcIt).BunchX();
        m_ntuple->rpcHit_Station_E[ riE ] = kStation;
        m_ntuple->rpcHit_Ring_E[ riE ] = kRing;
        m_ntuple->rpcHit_Sector_E[ riE ] = kSector;
        m_ntuple->rpcHit_Layer_E[ riE ] = kLayer;
        m_ntuple->rpcHit_X_E[ riE ] = xg;
        m_ntuple->rpcHit_Y_E[ riE ] = yg;
        m_ntuple->rpcHit_Z_E[ riE ] = zg;
        
        ++nRecHitsEndcap; //Rechits in Barrel
        ++riE; // index for ntuple
        
      }
      
    } else { }
    
  }
  
  //TTU Ntuple
  m_ntuple->nRpcHits = nRecHits;
  m_ntuple->nRpcHitsEndcap = nRecHitsEndcap;
  
  if ( nRecHits >= m_ntuple->MAX_RHITS ) std::cout << "TTUTree> will have problem because RecHits > MAX_HITS " << std::endl;
  
  if ( has_Hits_Station_1 && has_Hits_Station_34 ) m_apply_Cosmic_Veto = true;
  
  //std::cout << ieventX << "rpcRecHits: apply_veto: final: " << m_apply_Cosmic_Veto << '\n';
  
  (*gzfileDump) << "RPC rechits: " 
                << ieventX   << " "
                << iorbitX   << " "
                << bxX       << " "
                << lumiSec   << " "
                << nRPC      << '\n';
  
  //... Fraction of RPC RecHit in Stations
  
  if ( nRPC != 0 ) {
    for ( int k=0; k< 4; ++k) {
      float fraction = (float)nRPC_in_Station[k]/(float)nRPC;
      m_h_RpcHits_FracStation[k]->Fill( fraction );
      
    }
  }
  
  nRecHits = 0;
  nRecHitsEndcap = 0;
  
  
}

void L1GtTtuAnalyzer::applySelection( const edm::Event& iEvent , const edm::Handle< L1GlobalTriggerReadoutRecord > & gtRecord ) 
{
  
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
  unsigned int lumiSec = iEvent.luminosityBlock();
  
  //....................................
  bool isTriggeredBy31 = m_rpcTechBits[7];
  
  if ( isTriggeredBy31 && ! m_apply_Cosmic_Veto && m_tracker_activity ) {
    
    for( int iebx=0; iebx < 5; iebx++) {
    
      const TechnicalTriggerWord wTWord = gtRecord->technicalTriggerWord( iebx-2 );
      
      (*gzfileDump) << "TriggersByTTU (cosmic Veto & tracker activity): " 
                    << ieventX    << " "
                    << iorbitX    << " "
                    << bxX        << " "
                    << lumiSec    << " "
                    << "iebx: "   << ( iebx-2 ) << " ";
      
      for( int k=0; k < m_maxttBits; ++k) {
        
        bool ttBitResult = wTWord.at(24+k);
        (*gzfileDump) << ( 24+k ) << "= " << ttBitResult << " ";
        
        if ( m_dtTrigger  ) (*gzfileDump) << "Dt: "  <<  (bxX - m_DTcandidatesBx[0])  << " ";
        if ( m_rpcTrigger ) (*gzfileDump) << "Pac: " <<  (bxX - m_GMTcandidatesBx[0]) << " ";
        
      }
      
      (*gzfileDump) << '\n';
      
    }
    
    //look for track in a cone
    
    
  }
  
  //....................................
  
}

// ------------ method called once each job just before starting event loop  ------------
void L1GtTtuAnalyzer::beginJob()
{
 
  m_hltConfig.init( m_processName );

  edm::Service<TFileService> fservice;

  m_ntuple = new L1TTUTree(fservice);
  
  TFileDirectory patcan     = fservice->mkdir( "PATCandidates" );
  TFileDirectory muoncand   = fservice->mkdir( "MuonCandidates" );
  TFileDirectory generaltks = fservice->mkdir( "GeneralTracks" );
  TFileDirectory l1trigger  = fservice->mkdir( "L1TechnicalTrigger" );
  TFileDirectory rpcrechits = fservice->mkdir( "RPCRecHits" );
  
  double max_x = 600.0;
  double max_y = 400.0;
  
  m_runSummaryA         =  l1trigger.make<TH1D>("Run.Summary.A","Run summary", 13,0,13);

  m_runSummaryB         =  l1trigger.make<TH1D>("Run.Summary.B","Run summary", 13,0,13);

  m_pointingTrack      =  generaltks.make<TH1D>("Bit.25.All","Bit 25 performance",2,0,2);
  
  m_pointingTrack_0mu  =  generaltks.make<TH1D>("Bit.25.0.Tracks","Bit 25 performance",2,0,2);
  
  m_pointingTrack_1mu  =  generaltks.make<TH1D>("Bit.25.1.Tracks","Bit 25 performance",2,0,2);
  
  m_pointingTrack_2mu  =  generaltks.make<TH1D>("Bit.25.2.Tracks","Bit 25 performance",2,0,2);
  
  m_pointingTrack_3mu  =  generaltks.make<TH1D>("Bit.25.3.Tracks","Bit 25 performance",2,0,2);
  
  m_pointingMuon_0mu   =  generaltks.make<TH1D>("Bit.25.0.Muons","Bit 25 performance",2,0,2);
  
  m_pointingMuon_1mu   =  generaltks.make<TH1D>("Bit.25.1.Muon","Bit 25 performance",2,0,2);
  
  m_pointingMuon_2mu   =  generaltks.make<TH1D>("Bit.25.2.Muons","Bit 25 performance",2,0,2);
  
  m_ttBitsDecision = l1trigger.make<TH1D>("TechTrigger.Bits",
                                           "Technical Trigger bits : Summary",
                                          10, 23, 33 );

    
  m_bxDist = l1trigger.make<TH1D>("BX.distribution.Final",
                                  "Bx distribution",
                                  7, -3.5, 3.5);
  
  m_bxInRpc = l1trigger.make<TH1D>("BX.distribution.RpcEvent",
                                   "Bx distribution",
                                   7, -3.5, 3.5);
  
  m_bxNumber = l1trigger.make<TH1D>("BX.Distribution.L1A",
                                     "Bx distribution",
                                     100, 0, 100);
  
  m_bxNumberClose = l1trigger.make<TH1D>("BX.Num.Distribution.in.Range",
                                         "Bx distribution",
                                         1000, m_bxNumMin, (m_bxNumMax+1) );
  
  
  m_qfGMT = l1trigger.make<TH1D>("L1.Qs.from.GMT",
                                  "Quality scale from GMT",
                                  8, 0, 8);
  
  
  m_gmtFilterDist = l1trigger.make<TH1D>("Dist.of.GMT.Filter.Triggers",
                                          "Distribution of the GMT discriminated triggers by detector",
                                          10, 0, 10);
  
  m_bxDist2528 = l1trigger.make<TH1D>("BX.Diff.25.28",
                                      "Timing difference between bit 25 and bit 28",
                                      7, -3.5, 3.5);
  
  m_bxDist31 = l1trigger.make<TH1D>("BX.Diff.31.Beam",
                                    "Timing difference between of 31 and Beam Trigger",
                                    7, -3.5, 3.5);

  m_bxGTdist = l1trigger.make<TH1D>("Dist.of.bx.Number",
                                    "Bx number",
                                    4000, 0, 4000);
  
  m_bxGTdistBit24 = l1trigger.make<TH1D>("Dist.of.bx.Number.24",
                                          "Bx number",
                                          4000, 0, 4000);
  
  m_bxGTdistBit25 = l1trigger.make<TH1D>("Dist.of.bx.Number.25",
                                         "Bx number",
                                         4000, 0, 4000);

  m_bxDistNdecTtu = l1trigger.make<TH1D>("Number.of.Ttu.Decisions",
                                         "Ttu decisions per event",
                                         4, 0, 4);

  m_bxGTdistTTBits = l1trigger.make<TH2D>("Dist.of.bx.Number.TT.Bits",
                                          "TT bits decision vs Bx number",
                                          4000, 0, 4000, 65, 0, 65);
  
  m_bxGTdistTT = l1trigger.make<TH1D>("Dist.of.bx.Number.TT.Bit.In.Concidence.TT",
                                      "Bx number",
                                      4000, 0, 4000);
  
  m_bxGTdistAlg = l1trigger.make<TH1D>("Dist.of.bx.Number.TT.Bit.In.Concidence.Alg.",
                                       "Bx number",
                                       4000, 0, 4000);


  for( int k=0; k < m_maxttBitsTrigger; ++k) {

    std::ostringstream hname;
    
    hname.str("");
    hname << "Dist.of.bx.Number.TT.Bits.In.Trigger." << m_makeCoincidenceTT[k];
    m_bxGTdistTTInTrigger[k] = l1trigger.make<TH1D>(hname.str().c_str(),
                                                    "Bx number",
                                                    4000, 0, 4000);
    
  }
  
  for( int k=0; k < m_maxAlgBitsTrigger; ++k) {
    
    std::ostringstream hname;
    hname.str("");
    hname << "Dist.of.bx.Number.Alg.Bit.In.Trigger." << m_makeCoincidenceAlg[k];
    m_bxGTdistAlgInTrigger[k] = l1trigger.make<TH1D>(hname.str().c_str(),
                                                     "Bx number",
                                                     4000, 0, 4000);
  }
  
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    std::ostringstream hname;
    
    hname << "Trigger.Rate." << m_ttBits[k];
    
    m_trigRateHz[k]   = l1trigger.make<TH1D>( hname.str().c_str(),
                                              "Trigger rate [Hz]",
                                              10000, 0,10000);
    
    hname.str("");
    
    hname << "Trigger.Rate.Dist." << m_ttBits[k];
    
    m_trigRateDist[k] = l1trigger.make<TH1D>( hname.str().c_str(),
                                              "Trigger rate [Hz]",
                                              m_maxRate, 0, m_maxRate);
    
    hname.str("");
    hname << "Dist.of.bx.Number.TT.Bit." << m_ttBits[k];
    
    m_bxGTdistSelBit[k] = l1trigger.make<TH1D>(hname.str().c_str(),
                                               "Bx number",
                                               4000, 0, 4000);
    
    hname.str("");
    hname << "BX.diff.PAC-TTU.bit." << m_ttBits[k];
    m_bxDistDiffPac[k] = l1trigger.make<TH1D>(hname.str().c_str(),
                                              "Timing difference between PAC and TTU",
                                              7, -3.5, 3.5);
    
    hname.str("");
    hname << "BX.diff.DT-TTU.bit." << m_ttBits[k];
    m_bxDistDiffDt[k] = l1trigger.make<TH1D>(hname.str().c_str(),
                                             "Timing difference between DT and TTU",
                                             7, -3.5, 3.5);

    hname.str("");
    
  }
  
  m_bxDistDiffDTPac = l1trigger.make<TH1D>("BX.diff.DT-PAC",
                                           "Timing difference between DT and PAC",
                                           7, -3.5, 3.5);
  
  m_bxDistDiffDTPacIC = l1trigger.make<TH1D>("BX.diff.DT-PAC.In.Coincidence",
                                             "Timing difference between DT and PAC (in coincidence)",
                                             7, -3.5, 3.5);
  
  //For tracks info:
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    std::ostringstream hname;
    

    /////  STA

    hname << "Selected.MuonSTA.Pt.Bit." << m_ttBits[k];
    
    m_HMuonSTAPt_Bit[k] = muoncand.make<TH1D>( hname.str().c_str(),"Selected muon Pt bit", 100, 0.0, m_maxPt);
    m_HMuonSTAPt_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonSTA.EtaPhi.Bit." << m_ttBits[k];
    
    m_HMuonSTAEtaPhi_Bit[k] = muoncand.make<TH2D>(hname.str().c_str(),"Selected muon eta/phi bit", 60, -5.0, 5.0, 60, -4.0, 4.0 );
    m_HMuonSTAEtaPhi_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonSTA.do.Bit." << m_ttBits[k];
    
    m_HMuonSTAd0dist_Bit[k] = muoncand.make<TH1D>(hname.str().c_str(),"Selected muon d0", 200, -1000.0 , 1000.0 );
    m_HMuonSTAd0dist_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonSTA.dz.Bit." << m_ttBits[k];
    
    m_HMuonSTAdszdist_Bit[k] = muoncand.make<TH1D>(hname.str().c_str(),"Selected muon dz", 200, -1000.0 , 1000.0 );
    m_HMuonSTAdszdist_Bit[k]->Sumw2();

    /////  GBL

    hname << "Selected.MuonGBL.Pt.Bit." << m_ttBits[k];
    
    m_HMuonGBLPt_Bit[k] = muoncand.make<TH1D>( hname.str().c_str(),"Selected muon Pt bit", 100, 0.0, m_maxPt);
    m_HMuonGBLPt_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonGBL.EtaPhi.Bit." << m_ttBits[k];
    
    m_HMuonGBLEtaPhi_Bit[k] = muoncand.make<TH2D>(hname.str().c_str(),"Selected muon eta/phi bit", 60, -5.0, 5.0, 60, -4.0, 4.0 );
    m_HMuonGBLEtaPhi_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonGBL.do.Bit." << m_ttBits[k];
    
    m_HMuonGBLd0dist_Bit[k] = muoncand.make<TH1D>(hname.str().c_str(),"Selected muon d0", 200, -1000.0 , 1000.0 );
    m_HMuonGBLd0dist_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonGBL.dz.Bit." << m_ttBits[k];
    
    m_HMuonGBLdszdist_Bit[k] = muoncand.make<TH1D>(hname.str().c_str(),"Selected muon dz", 200, -1000.0 , 1000.0 );
    m_HMuonGBLdszdist_Bit[k]->Sumw2();


    /////  TRK

    hname << "Selected.MuonTRK.Pt.Bit." << m_ttBits[k];
    
    m_HMuonTRKPt_Bit[k] = muoncand.make<TH1D>( hname.str().c_str(),"Selected muon Pt bit", 100, 0.0, m_maxPt);
    m_HMuonTRKPt_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonTRK.EtaPhi.Bit." << m_ttBits[k];
    
    m_HMuonTRKEtaPhi_Bit[k] = muoncand.make<TH2D>(hname.str().c_str(),"Selected muon eta/phi bit", 60, -5.0, 5.0, 60, -4.0, 4.0 );
    m_HMuonTRKEtaPhi_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonTRK.do.Bit." << m_ttBits[k];
    
    m_HMuonTRKd0dist_Bit[k] = muoncand.make<TH1D>(hname.str().c_str(),"Selected muon d0", 200, -1000.0 , 1000.0 );
    m_HMuonTRKd0dist_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.MuonTRK.dz.Bit." << m_ttBits[k];
    
    m_HMuonTRKdszdist_Bit[k] = muoncand.make<TH1D>(hname.str().c_str(),"Selected muon dz", 200, -1000.0 , 1000.0 );
    m_HMuonTRKdszdist_Bit[k]->Sumw2();

    
    //....... RPC RecHits ...........

    hname.str("");
    hname << "Track.XY.Rpc.RecHit.bit." << m_ttBits[k];
    
    m_hh_xy_rpc_rechit[k] = rpcrechits.make<TH2D>( hname.str().c_str(), "Tracks XY Rpc RecHit", 
                                                   100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
    
    hname.str("");
    hname << "Track.YZ.Rpc.RecHit.bit." << m_ttBits[k];
    
    m_hh_yz_rpc_rechit[k] = rpcrechits.make<TH2D>( hname.str().c_str(), "Tracks YZ Rpc RecHit", 
                                                  100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
    
    hname.str("");
    hname << "Rpc.Hits.Layer.bit." << m_ttBits[k];
    
    m_h_RpcHits_Layer[k]  = rpcrechits.make<TH1D>(hname.str().c_str(),"RPC RecHits Layer", 10, 0.0, 10);
    
    hname.str("");
    hname << "Rpc.Hits.Sector.bit." << m_ttBits[k];
    
    m_h_RpcHits_Sector[k] = rpcrechits.make<TH1D>(hname.str().c_str(),"RPC RecHits Sector", 14, 0.0, 14);
    
    hname.str("");
    hname << "Rpc.Hits.Wheel.bit." << m_ttBits[k];
    m_h_RpcHits_Wheel[k]  = rpcrechits.make<TH1D>(hname.str().c_str(),"RPC RecHits Wheel", 11, -5.5, 5.5);
    
    hname.str("");
    hname << "Rpc.RecHit.BX.Station.bit." << m_ttBits[k];
    m_hh_bx_rpc_rechit_Bit[k] = rpcrechits.make<TH2D>( hname.str().c_str() , "RPC RecHits BX per station",
                                                       11, -5.5, 5.5, 6, 0, 6 ); 
    
    hname.str("");
    hname << "Rpc.RecHit.BX.Station.Weel.bit." << m_ttBits[k];
    m_hh_bx_rpc_rechit_wheel_Bit[k] = rpcrechits.make<TH2D>( hname.str().c_str() , "RPC RecHits BX per station/same wheel",
                                                             11, -5.5, 5.5, 6, 0, 6 );



    
    hname.str("");
    hname << "Rpc.RecHit.BX.Station.no.bit." << m_ttBits[k];
    m_hh_bx_rpc_rechit_NoBit[k] = rpcrechits.make<TH2D>( hname.str().c_str() , "RPC RecHits BX per station",
                                                         11, -5.5, 5.5, 6, 0, 6 ); 



  
  }

  NumberTracksEvt     = generaltks.make<TH1D>("NumberTracksEvt","Number of tracks per event", 15, 0.0, 15.0);
  
  NumberPointingTracksEvt  = generaltks.make<TH1D>("NumberPointingTracksEvt","Number of pointing tracks per event", 15, 0.0, 15.0);

  NumberPointingTracksEvtBy25  = generaltks.make<TH1D>("NumberPointingTracksEvtBy25",
                                                       "Number of pointing tracks per event + Bit 25", 15, 0.0, 15.0);
  
  NumberPointingHitsTrackerEvtByEvt25 = generaltks.make<TH1D>("NumberPointingHitsEvtBy25",
                                                              "Number of pointing hits in tracker per event + Bit 25", 
                                                              15, 0.0, 15.0);
  
  // Muons general Information

  MuonType           = generaltks.make<TH1D>("MuonType","Muon Type", 7, 0.0, 7.0);
  
  NumberMuonsEvt     = generaltks.make<TH1D>("NumberMuonsEvt","Number of muons per event", 15, 0.0, 15.0);

  h_mumu_InvMm       = generaltks.make<TH1D>("MuMuInvMass","Di muon mass", 50, 0.0, 15.0);
  h_mumu_InvMm->Sumw2();

  //... STA Muons information:

  MuonEta_STA        = generaltks.make<TH1D>("MuonEta.STA","Muon Eta", 60, -5.0, 5.0);
  MuonPhi_STA        = generaltks.make<TH1D>("MuonPhi.STA","Muon Phi", 60,  -4.0, 4.0);
  
  MuonEtaPhi_STA     = generaltks.make<TH2D>("Muon.Eta.Phi.STA","Muon Eta vs Phi",       60, -5.0, 5.0, 60, -4.0, 4.0 );
  MuonChi2DoF_STA    = generaltks.make<TH1D>("MuonChi2DoF.STA","Muon Track Chi2/DoF",   100,0.0,12.0);
  Muond0dist_STA     = generaltks.make<TH1D>("Muond0.STA","Muon d0", 50, -1.0 , 1.0);
  Muondszdist_STA    = generaltks.make<TH1D>("Muondsz.STA","Muon dsz", 50, -1000.0 , 1000.0);
  MuonPt_STA         = generaltks.make<TH1D>("MuonPt.STA","Muon Pt", 100,  0.0, m_maxPt);
  
  MuonPt_STA->Sumw2();
  MuonChi2DoF_STA->Sumw2();
  
  m_h_pt_HLT_STA     = generaltks.make<TH1D>("MuonPt.HLT.STA","Muon Pt", 100,  0.0, m_maxPt);
  m_h_pt_HLT_STA->Sumw2();
  m_h_pt_TTU_STA     = generaltks.make<TH1D>("MuonPt.TTU.STA","Muon Pt", 100,  0.0, m_maxPt);
  m_h_pt_TTU_STA->Sumw2();
    
  m_hh_pt_STA   = generaltks.make<TH2D>("MuonPt.HLT.TTU.STA","Muon Pt", 
                                        50,  0.0, m_maxPt,
                                        50,  0.0, m_maxPt );
  
  m_h_bx_failed_STA     = generaltks.make<TH1D>("Bit.31.Failed.STA.Bx","In case bit 31 did not triggered: check bx of decision"
                                                , 7,  -3.5, 3.5);
  
  
  //... GBL Muons information:
  
  MuonEtaPhi_GBL     = generaltks.make<TH2D>("Muon.Eta.Phi.GBL","Muon Eta vs Phi of GL", 60, -5.0, 5.0, 60, -4.0, 4.0 );
  MuonChi2DoF_GBL    = generaltks.make<TH1D>("MuonChi2DoF.GBL","Muon Track Chi2/DoF",   100,0.0,12.0);
  Muond0dist_GBL     = generaltks.make<TH1D>("Muond0.GBL","Muon d0", 200, -1000.0 , 1000.0);
  Muondszdist_GBL    = generaltks.make<TH1D>("Muondsz.GBL","Muon dsz", 200, -1000.0 , 1000.0);
  MuonPt_GBL         = generaltks.make<TH1D>("MuonPt.GBL","Global Muon Pt", 100,0.0, m_maxPt);
  
  MuonPt_GBL->Sumw2();
  MuonChi2DoF_GBL->Sumw2();
  
  MuonPt_GBL_bit25   = generaltks.make<TH1D>("MuonPt.GBL.bit.25","Global Muon Pt: triggered by RPC-TT", 100,0.0, m_maxPt);
  MuonPt_GBL_bit25->Sumw2();
  
  m_h_pt_HLT_GBL     = generaltks.make<TH1D>("MuonPt.HLT.GBL","Muon Pt", 100,  0.0, m_maxPt);
  m_h_pt_HLT_GBL->Sumw2();
  m_h_pt_TTU_GBL     = generaltks.make<TH1D>("MuonPt.TTU.GBL","Muon Pt", 100,  0.0, m_maxPt);
  m_h_pt_TTU_GBL->Sumw2();
  
  m_hh_pt_GBL   = generaltks.make<TH2D>("MuonPt.HLT.TTU.GBL","Muon Pt", 
                                        50,  0.0, m_maxPt,
                                        50,  0.0, m_maxPt );
  
  m_h_bx_failed_GBL     = generaltks.make<TH1D>("Bit.31.Failed.GBL.Bx","In case bit 31 did not triggered: check bx of decision"
                                                , 7,  -3.5, 3.5);

  
  //... TRK Muons information:
  
  MuonEtaPhi_TRK     = generaltks.make<TH2D>("Muon.Eta.Phi.TRK","Muon Eta vs Phi of GL", 60, -5.0, 5.0, 60, -4.0, 4.0 );
  MuonChi2DoF_TRK    = generaltks.make<TH1D>("MuonChi2DoF.TRK","Muon Track Chi2/DoF",   100,0.0,12.0);
  Muond0dist_TRK     = generaltks.make<TH1D>("Muond0.TRK","Muon d0", 200, -1000.0 , 1000.0);
  Muondszdist_TRK    = generaltks.make<TH1D>("Muondsz.TRK","Muon dsz", 200, -1000.0 , 1000.0);
  MuonPt_TRK         = generaltks.make<TH1D>("MuonPt.TRK","Global Muon Pt", 100,0.0, m_maxPt);
  
  MuonPt_TRK->Sumw2();
  MuonChi2DoF_TRK->Sumw2();
  
  MuonPt_TRK_bit25   = generaltks.make<TH1D>("MuonPt.TRK.bit.25","Global Muon Pt: triggered by RPC-TT", 100,0.0, m_maxPt);
  MuonPt_TRK_bit25->Sumw2();
  
  m_h_pt_HLT_TRK     = generaltks.make<TH1D>("MuonPt.HLT.TRK","Muon Pt", 100,  0.0, m_maxPt);
  m_h_pt_HLT_TRK->Sumw2();
  m_h_pt_TTU_TRK     = generaltks.make<TH1D>("MuonPt.TTU.TRK","Muon Pt", 100,  0.0, m_maxPt);
  m_h_pt_TTU_TRK->Sumw2();
  
  m_hh_pt_TRK   = generaltks.make<TH2D>("MuonPt.HLT.TTU.TRK","Muon Pt", 
                                        50,  0.0, m_maxPt,
                                        50,  0.0, m_maxPt );
  
  m_h_bx_failed_TRK     = generaltks.make<TH1D>("Bit.31.Failed.TRK.Bx","In case bit 31 did not triggered: check bx of decision"
                                                , 7,  -3.5, 3.5);

  ///Tracker information:


  m_pointingTrkCode = generaltks.make<TH1D>("TrckCode","Tracker Code", 10, 0.0, 10);
  m_pointingTrkCodeIn = generaltks.make<TH1D>("TrckCodeIn","Tracker Code In tracker", 10, 0.0, 10);
  
  //
  TrackerPt_In_bit25        = generaltks.make<TH1D>("TrackPt.In.bit.25","Track Muon Pt: triggered by RPC-TT", 
                                                   100,0.0, m_maxPt);
  TrackerPt_In_bit25->Sumw2();
  
  TrackerPt_Out_bit25       = generaltks.make<TH1D>("TrackPt.Out.bit.25","Track Muon Pt: triggered by RPC-TT", 
                                                   100,0.0, m_maxPt);
  TrackerPt_Out_bit25->Sumw2();
  
  TrackerPt_In_CTF_bit25    = generaltks.make<TH1D>("TrackPt.In.CTF..bit.25","Track Muon Pt: triggered by RPC-TT", 
                                                   100,0.0, m_maxPt);
  TrackerPt_In_CTF_bit25->Sumw2();
  
  TrackerPt_Out_CTF_bit25   = generaltks.make<TH1D>("TrackPt.Out.CTF.bit.25","Track Muon Pt: triggered by RPC-TT", 
                                                   100,0.0, m_maxPt);
  TrackerPt_Out_CTF_bit25->Sumw2();
  
  TrackerPt_All_bit25       = generaltks.make<TH1D>("TrackPt.ALL.bit.25","Track Muon Pt: triggered by RPC-TT", 
                                                   100,0.0, m_maxPt);
  TrackerPt_All_bit25->Sumw2();

  //... Geometrical location of triggers

  m_hh_eta_phi_all_bit25    = generaltks.make<TH2D>("Cosmic.Eta.Phi.All","Cosmic Eta vs Phi of All tracks bit 25", 
                                                    60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  m_hh_eta_phi_trk_bit25    = generaltks.make<TH2D>("Cosmic.Eta.Phi.Trk","Cosmic Eta vs Phi of Trk in Tracker bit 25", 
                                                    60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  m_hh_eta_phi_ctf_bit25    = generaltks.make<TH2D>("Cosmic.Eta.Phi.CTF","Cosmic Eta vs Phi of CTF in Tracker bit 25", 
                                                    60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  m_hh_eta_phi_matchLeg_trk_bit25    = generaltks.make<TH2D>("Cosmic.Eta.Phi.Trk.Match","Cosmic Eta vs Phi of Trk  bit 25", 
                                                             60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  m_hh_eta_phi_matchLeg_ctf_bit25    = generaltks.make<TH2D>("Cosmic.Eta.Phi.CTF.Match","Cosmic Eta vs Phi of CTF  bit 25", 
                                                             60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  //.......
  
  m_hh_d0_dz_all_bit25    = generaltks.make<TH2D>("Cosmic.d0.dz.All","Cosmic d0 vs dz of All tracks bit 25", 
                                                  100, -max_x, max_x, 100, -max_y, max_y );
  
  m_hh_d0_dz_trk_bit25    = generaltks.make<TH2D>("Cosmic.d0.dz.Trk","Cosmic d0 vs dz of Trk in Tracker bit 25", 
                                                  100, -max_x, max_x, 100, -max_y, max_y );
  
  m_hh_d0_dz_ctf_bit25    = generaltks.make<TH2D>("Cosmic.d0.dz.CTF","Cosmic d0 vs dz of CTF in Tracker bit 25", 
                                                  100, -max_x, max_x, 100, -max_y, max_y );
  
  m_hh_d0_dz_matchLeg_trk_bit25  = generaltks.make<TH2D>("Cosmic.d0.dz.Trk.Match","Cosmic d0 vs dz of Trk  bit 25", 
                                                         100, -max_x, max_x, 100, -max_y, max_y );
  
  m_hh_d0_dz_matchLeg_ctf_bit25  = generaltks.make<TH2D>("Cosmic.d0.dz.CTF.Match","Cosmic d0 vs dz of CTF  bit 25", 
                                                         100, -max_x, max_x, 100, -max_y, max_y );
  
  m_hh_TwoLegsDifference_bit24 = generaltks.make<TH2D>("TwoLegsDiff.Pt.Dz.bit.24",
                                                       "Two legs difference ", 100, -100.0 , 100, 50, -50.0, 50.0);
  
  m_hh_TwoLegsDifference_bit25 = generaltks.make<TH2D>("TwoLegsDiff.Pt.Dz.bit.25",
                                                       "Two legs difference ", 100, -100.0 , 100, 50, -50.0, 50.0);
  
  m_total_bit25_triggers     = generaltks.make<TH1D>("Total.Bit.25.triggers","Number of tracks per event", 4, 0.0, 4.0);
  
  m_total_bit25_cosmics      = generaltks.make<TH1D>("Total.Bit.25.Any.Cosmics","Number of tracks per event", 4, 0.0, 4.0);
  
  m_hh_xy_inner_bit25        = generaltks.make<TH2D>("Cosmic.XY.inner.bit.25", "Cosmics XY inner: inner most XY of track", 
                                                     100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_xy_outer_bit25        = generaltks.make<TH2D>("Cosmic.XY.outer.bit.25", "Cosmics XY outer: outer most XY of track", 
                                                     100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_xy_inner_bit24        = generaltks.make<TH2D>("Cosmic.XY.inner.bit.24", "Cosmics XY inner: inner most XY of track", 
                                                     100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_xy_outer_bit24        = generaltks.make<TH2D>("Cosmic.XY.outer.bit.24", "Cosmics XY outer: outer most XY of track", 
                                                     100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_inner_bit25        = generaltks.make<TH2D>("Cosmic.YZ.inner.bit.25", "Cosmics YZ inner: inner most YZ of track", 
                                                     100, -max_x*2.4, max_x*2.4, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_outer_bit25        = generaltks.make<TH2D>("Cosmic.YZ.outer.bit.25", "Cosmics YZ outer: outer most YZ of track", 
                                                     100, -max_x*2.4, max_x*2.4, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_inner_bit24        = generaltks.make<TH2D>("Cosmic.YZ.inner.bit.24", "Cosmics YZ inner: inner most YZ of track", 
                                                     100, -max_x*2.4, max_x*2.4, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_outer_bit24        = generaltks.make<TH2D>("Cosmic.YZ.outer.bit.24", "Cosmics YZ outer: outer most YZ of track", 
                                                     100, -max_x*2.4, max_x*2.4, 100, -max_y*2, max_y*2 );
  
  m_hh_xy_rpc_rechit_All = rpcrechits.make<TH2D>( "Track.XY.Rpc.RecHit.All", "Tracks XY Rpc RecHit All", 
                                                  100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_rpc_rechit_All = rpcrechits.make<TH2D>( "Track.YZ.Rpc.RecHit.All", "Tracks YZ Rpc RecHit All", 
                                                  100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_h_RpcHits_Layer_All  = rpcrechits.make<TH1D>("Rpc.Hits.Layer.All","RPC RecHits Layer", 10, 0.0, 10);
  
  m_h_RpcHits_Sector_All = rpcrechits.make<TH1D>("Rpc.Hits.Sector.All","RPC RecHits Sector", 14, 0.0, 14);
  
  m_h_RpcHits_Wheel_All  = rpcrechits.make<TH1D>("Rpc.Hits.Wheel.All","RPC RecHits Wheel", 11, -5.5, 5.5);

  for( int k=0; k < 4; ++k) {
    std::ostringstream hname;
    hname.str("");
    hname << "Rpc.Hits.Fraction." << (k+1);
    m_h_RpcHits_FracStation[k]  = rpcrechits.make<TH1D>(hname.str().c_str(),"RPC RecHits Fraction in Station", 100, 0.0 , 1.1);
    
  }
  
  m_hh_bx_rpc_rechit_All = rpcrechits.make<TH2D>( "Rpc.RecHit.BX.Station.All", "RPC RecHits BX per station",
                                                  11, -5.5, 5.5, 6, 0, 6 );
  
  for( int k=-2; k <= 2; ++k) {
    
    std::ostringstream hname;
    
    hname.str("");
    hname << "Rpc.Hits.Wheel." << k << ".Top";
    
    m_h_RpcHits_WheelBxTop[k+2] = rpcrechits.make<TH2D>( hname.str().c_str() , "RPC RecHits BX per Layer in Wheel",
                                                         11, -5.5, 5.5, 8, 0, 8 );
    
    hname.str("");
    hname << "Rpc.Hits.Wheel." << k << ".Bot";
    
    m_h_RpcHits_WheelBxBot[k+2] = rpcrechits.make<TH2D>( hname.str().c_str(), "RPC RecHits BX per Layer in Wheel",
                                                         11, -5.5, 5.5, 8, 0, 8 );
    
    for( int bx=-3; bx <= 3; ++bx ) {
      
      hname.str("");
      hname << "Rpc.Hits.Wheel." << k << ".Bx." << bx;
      m_h_RpcHits_WheelBx[k+2][bx+3] = rpcrechits.make<TH2D>(hname.str().c_str(),
                                                             "RPC RecHits Wheel/BX distribution", 
                                                             100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
    }
    
  }
  
  
  m_h_bit31_Compare[0] = l1trigger.make<TH1D>("Bit.31.History.1","Bit 31 history: Comparison side by side", 
                                              12, 0.0, 12);
  
  m_h_bit31_Compare[1] = l1trigger.make<TH1D>("Bit.31.History.2","Bit 31 history: Comparison side by side", 
                                              12, 0.0, 12);
  
  
  for( int k = 0; k < m_maxAlgBits; ++k) {

    std::ostringstream hname;
    hname << "BX.Bit25.vs.Algo." << m_singleMuBits[k];
    
    m_bxDistMu55TT25[k] = l1trigger.make<TH2D>( hname.str().c_str(), "Bx of TT Bit 25 vs MuAlgos",
                                                5, -2.5, 2.5, 5, -2.5, 2.5 );
    hname.str("");
    
  }
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1GtTtuAnalyzer::endJob() {
  
  std::cout << "total time: " << m_totalTime << " "
            << "total elapsed time: " << m_elapsedTime << std::endl;

  std::cout << "total bits 25: " << m_totalBit25 << " "
            << "total of bits 25 + any Cosmic muon: " << m_totalBit25Muon << std::endl;
  
  std::cout << "GMT-problems: " << m_GMTproblem << std::endl;
  
}


//define this as a plug-in
DEFINE_FWK_MODULE(L1GtTtuAnalyzer);
