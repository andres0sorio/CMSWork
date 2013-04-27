// system include files

#include <StudyL1Trigger/L1TTUStudies/src/L1TTUStudies.h>

#include <DataFormats/MuonReco/interface/MuonSelectors.h>

L1TTUStudies::L1TTUStudies(const edm::ParameterSet& iConfig)
{
  
  m_debug = false;
  
  m_rpcDigiLabel       = iConfig.getParameter<edm::InputTag>("RPCDigiLabel");
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_gmtReadoutLabel    = iConfig.getParameter<edm::InputTag>("GMTReadoutRcd");
  m_recoMuonLabel      = iConfig.getParameter<edm::InputTag>("RecoMuonLabel");
  m_recoTracksLabel    = iConfig.getParameter<edm::InputTag>("RecoTracksLabel");
  m_recoSiStripLabel   = iConfig.getParameter<edm::InputTag>("RecoSiStripLabel");
  m_recoPixelLabel     = iConfig.getParameter<edm::InputTag>("RecoPixelLabel");
  m_hltResultsLabel    = iConfig.getParameter<edm::InputTag>("TriggerResultsLabel");

  ///
  m_lumiSection        = iConfig.getUntrackedParameter<int>("LumiSection", 0);
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers");
  m_ttBitsCollisions   = iConfig.getParameter< std::vector<unsigned> >("BitCollisions");
  m_makeCoincidenceTT  = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceTT");
  m_makeCoincidenceAlg = iConfig.getParameter< std::vector<unsigned> >("MakeCoincidenceAlgo");
  m_selectedBx         = iConfig.getParameter< std::vector<int> >("SelectedBxWindow");
  m_checkhltPaths      = iConfig.getParameter< std::vector<std::string> >("CheckHLTPaths");
  m_processName        = iConfig.getUntrackedParameter<std::string>("ProcessName", "HLT");
  m_maxMuonPt          = iConfig.getUntrackedParameter<double>("MaxPt", 100);
  m_trackerLength      = iConfig.getUntrackedParameter<double>("TrackerLength", 200);
  m_trackerHeight      = iConfig.getUntrackedParameter<double>("TrackerHeight", 200);
  m_muonPtcut          = iConfig.getUntrackedParameter<double>("MuonPtCut", 1.0);
  m_muonTypeSection    = iConfig.getUntrackedParameter<int>("MuonTypeSelection", 4);
  m_trkSelectionCuts   = iConfig.getUntrackedParameter<int>("TrackSelecionCuts", 0x0);
  m_GoodMuonSelection  = iConfig.getUntrackedParameter<int>("TrackerMuonSelection", 0);
  
  initialize();

  m_trkCuts = std::bitset<10>( m_trkSelectionCuts );
    
  m_debug = true;

  m_kSectorMin[1]  = 12;
  m_kSectorMin[2]  = 1;
  m_kSectorMin[3]  = 2;
  m_kSectorMin[4]  = 3;
  m_kSectorMin[5]  = 4;
  m_kSectorMin[6]  = 5;
  m_kSectorMin[7]  = 6;
  m_kSectorMin[8]  = 7;
  m_kSectorMin[9]  = 8;
  m_kSectorMin[10] = 9;
  m_kSectorMin[11] = 10;
  m_kSectorMin[12] = 11;

  m_kSectorMax[1]  = 2;
  m_kSectorMax[2]  = 3;
  m_kSectorMax[3]  = 4;
  m_kSectorMax[4]  = 5;
  m_kSectorMax[5]  = 6;
  m_kSectorMax[6]  = 7;
  m_kSectorMax[7]  = 8;
  m_kSectorMax[8]  = 9;
  m_kSectorMax[9]  = 10;
  m_kSectorMax[10] = 11;
  m_kSectorMax[11] = 12;
  m_kSectorMax[12] = 1;
  
  m_kRingLeft[-2] = -99;
  m_kRingRight[-2] = -1;
  
  m_kRingLeft[-1] = -2;
  m_kRingRight[-1] =  0;

  m_kRingLeft[ 0] = -1;
  m_kRingRight[ 0] =  1;

  m_kRingLeft[ 1] =  0;
  m_kRingRight[ 1] =  2;

  m_kRingLeft[ 2] = 1;
  m_kRingRight[ 2] = -99;

}

L1TTUStudies::~L1TTUStudies()
{
  
}

//void
//L1TTUStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)

bool
L1TTUStudies::filter( edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //... L1 analysis
  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( m_gtReadoutLabel, gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "L1TTUStudies> " << "can't find L1GlobalTriggerRecord with label: " 
              << m_gtReadoutLabel << '\n';
    return false;
  }
  
  
  //... L1GMT analysis
  
  //... HLT analysis
  
  //... Muon/Tracker/RPC analysis
  
  bool result = lookatRecoMuons( iEvent, iSetup, gtRecord );
  
  return result;
  
}

bool L1TTUStudies::lookatRecoMuons(const edm::Event & iEvent , 
                                   const edm::EventSetup& iSetup, 
                                   const edm::Handle< L1GlobalTriggerReadoutRecord > & gtRecord ) 
{
  
  //
  unsigned int  runidX = iEvent.run();
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int              bxX = iEvent.bunchCrossing();
  unsigned int lumiSec = iEvent.luminosityBlock();

  bool bit31_decision = false;
  std::vector<int>::iterator iebx;
  
  for( iebx = m_selectedBx.begin(); iebx != m_selectedBx.end(); ++iebx) {
    const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord( (*iebx) );
    bit31_decision |= gtTTWord [31];
  }
  
  //.................................................................................................................
  
  edm::Handle< edm::View<reco::Muon> > muonHandle;
  iEvent.getByLabel(m_recoMuonLabel, muonHandle);
  
  if ( ! muonHandle.isValid() ) {
    std::cout << "L1TTUStudies::analyze> there is a problem with the muon Handle"  << std::endl;
    return false;
  }
  
  edm::View<reco::Muon>::const_iterator muon;

  //.................................................................................................................
  edm::Handle<RPCRecHitCollection> rpcRecHits; 
  iEvent.getByLabel("rpcRecHits","",rpcRecHits);
  
  if ( ! rpcRecHits.isValid() ) {
    std::cout << "L1TTUStudies::analyze> there is a problem with the RPC RecHits Handle"  << std::endl;
    return false;
  }

  RPCRecHitCollection::const_iterator rpcIt;

  //.................................................................................................................  
  
  edm::ESHandle<RPCGeometry> geom;
  iSetup.get<MuonGeometryRecord> ().get (geom);
  
  if ( ! geom.isValid () ) {
    std::cout << "L1TTUStudies::analyze> there is a problem with the RPC Geometry Handler"  << std::endl;
    return false;
  }
  
  //.................................................................................................................  
  
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  double x0 = beamSpot.x0();
  double y0 = beamSpot.y0();
  
  //.................................................................................................................  

  int num_Mu(0);
  bool keepEvent = false;
  
  std::vector< reco::MuonChamberMatch > trkMuonMatches;
  std::vector< reco::MuonChamberMatch >::iterator itrMatch;

  std::map<int,int> n_matched_hits_RBSt1;
  std::map<int,int>::iterator itrNRBSt1;
  std::map<int,int> n_rpchits_bx_RBSt1;
  
  int counter = 0;
  int muon_type = 0;
  
  for( muon=muonHandle->begin(); muon != muonHandle->end(); ++muon) {
    
    ++num_Mu;
    
    m_isBit31_matched = false;
    
    if(muon->isStandAloneMuon())
      if(muon->isGlobalMuon())
        if(muon->isTrackerMuon()) muon_type = 1;  // 1= STA + GLB + TM
        else muon_type = 2;                       // 2= STA + GLB
      else 
        if(muon->isTrackerMuon()) muon_type = 3;  // 3= STA + TM
        else muon_type = 5;                       // 5= STA
    else
      if(muon->isTrackerMuon()) muon_type = 4;    // 4= TM
    
    m_Histograms->h_MuonType->Fill( muon_type );
    
    if (m_debug) std::cout << " muon : " << num_Mu << "---//--- type: " << muon_type << std::endl; 
    
    //Apply selection cuts for muons: good collision muons
    bool goodMuCand = false;
    
    bool isGoodMuon = applyMuonCuts( (*muon) );

    if ( !isGoodMuon )
      continue;
    
    //....................................................................

    float    Muond0_TRK = -99.0;
    float   Muondsz_TRK = -99.0;
    float  MuonChi2_TRK = -99.0;
    float   MuonEta_TRK = -99.0;
    float   MuonPhi_TRK = -99.0;
    float    MuonPt_TRK = -99.0;
    int   Nchambers_TRK = -99.0;
    float MuonCaloC_TRK = -99.0;
    int matchedDetector = -99.0;
    bool      hasFwdDet = false;
    int     NmatchedDet[3];
    
    for(int i=0; i<3; ++i) NmatchedDet[i] = 0;
            
    //....................................................................
    
    if ( muon_type == m_muonTypeSection ) {

      counter += 1;
            
      Muond0_TRK    = muon->track()->d0() 
        - x0*sin( muon->track()->phi() ) 
        - y0*cos( muon->track()->phi() );
      Muondsz_TRK   = muon->track()->dsz();
      MuonChi2_TRK  = muon->track()->normalizedChi2 ();
      MuonEta_TRK   = muon->track()->eta();
      MuonPhi_TRK   = muon->track()->phi();
      MuonPt_TRK    = muon->track()->pt();
      Nchambers_TRK = muon->numberOfChambers();
      MuonCaloC_TRK = muon->caloCompatibility();

      //... TRK/GBL muon information 
      m_Histograms->h_trkMuon_eta_phi->Fill( MuonEta_TRK, MuonPhi_TRK );
      m_Histograms->h_trkMuon_calocomp->Fill( MuonCaloC_TRK );
      m_Histograms->h_trkMuon_eta->Fill( MuonEta_TRK );
      m_Histograms->h_trkMuon_pt->Fill( MuonPt_TRK );
      m_Histograms->h_trkMuon_dz->Fill( Muondsz_TRK );

      trkMuonMatches = muon->matches();
      
      m_Histograms->h_trkMuon_NMatches->Fill( trkMuonMatches.size() );
                  
      int matchSectorRb1      = -999;

      for( itrMatch = trkMuonMatches.begin(); itrMatch != trkMuonMatches.end(); ++itrMatch ) {
        
        float     matchX = (*itrMatch).x;
        float     matchY = (*itrMatch).y;
        int     detector = (*itrMatch).detector();
        int      station = (*itrMatch).station();
        int   matchWheel = -99;
        int matchStation = -99;
        int  matchSector = -99;
        int  matchRegion = -99;
        
        matchSectorRb1      = -999;

        //... Match to which detector the track is associated
        
        if ( detector == MuonSubdetId::RPC ) {
          
          RPCDetId detid( (*itrMatch).id() );
          matchWheel      = detid.ring();
          matchStation    = detid.station();
          matchSector     = detid.sector();
          matchRegion     = detid.region(); //RPC Barrel = 0
          matchedDetector = detector;
          
          if ( matchRegion == 0 )
            NmatchedDet[0] += 1;
          else 
            NmatchedDet[2] += 1;
          
        }
        
        else if ( detector == MuonSubdetId::DT ) {
          
          DTChamberId detid( (*itrMatch).id() );
          matchWheel      = detid.wheel();
          matchStation    = detid.station();
          matchSector     = detid.sector();
          matchRegion     = 0;
          matchedDetector = detector;
          NmatchedDet[1] += 1;
  
        }
        else {
          
          matchedDetector = detector;
          matchRegion     = -1;
          NmatchedDet[2] += 1;
          
        }

        if( m_debug) std::cout << "Muon matches info: x:" 
                               << matchX   << " y:"
                               << matchY   << " det:"
                               << detector << " W:"
                               << matchWheel   << " mSt:" 
                               << matchStation << " sSt:" 
                               << station      << " Sec:"
                               << matchSector  << " "
                               << std::endl;
        
        if ( bit31_decision ) 
          m_Histograms->h_matches_detector->Fill( matchedDetector );
        else 
          m_Histograms->h_matches_detector_not31->Fill( matchedDetector );
        
        for (rpcIt = rpcRecHits->begin(); rpcIt != rpcRecHits->end(); ++rpcIt) {
          
          LocalPoint rhitlocal = (*rpcIt).localPosition();
          RPCDetId id  = (RPCDetId)(*rpcIt).rpcId();
          int kRegion  = id.region();
          
          const GeomDetUnit *det = geom->idToDetUnit ( id );
          GlobalPoint gp = det->toGlobal( rhitlocal );
          float xg = gp.x ();
          float yg = gp.y ();
          //float zg = gp.z ();
          
          int kStation = id.station();
          int kRing    = id.ring();
          int kLevel   = id.layer();  
          int kSector  = id.sector();
          int kBx      = (*rpcIt).BunchX();
          
          if (m_debug) {
            std::cout << "RPC RecHit info:" 
                      << "W: " << kRing << " "
                      << "St: " << kStation << " " 
                      << "Sc: " << kSector << " "
                      << "Bx: " << kBx << '\n';
            
          }
          
          if( kRegion     == 0 
              && kStation == matchStation 
              && ( m_kRingLeft[kRing]    == matchWheel  || m_kRingRight[kRing]   == matchWheel  || kRing   == matchWheel )
              && ( m_kSectorMin[kSector] == matchSector || m_kSectorMax[kSector] == matchSector || kSector == matchSector )
              && kStation == 1 ) {
            
            itrNRBSt1 = n_matched_hits_RBSt1.find( kRing );
            
            if( itrNRBSt1 == n_matched_hits_RBSt1.end() )
              n_matched_hits_RBSt1[ kRing ] = 1;
            else {
              matchSectorRb1 = kSector;
              (*itrNRBSt1).second = (*itrNRBSt1).second + 1;
            }

            if (m_debug)  std::cout << "we have a match! RPC-> DT,RPC" << std::endl;
            
            int kLayer = getBarrelLayer( kLevel, kStation );
            int key = (kSector * 1000) + kLayer;
            n_rpchits_bx_RBSt1[ key ] = kBx;
                                    
          } else {
            
            if (m_debug)  std::cout << "no match! RPC -/-> DT,RPC" << std::endl;
            
          }
          
          float distanceXY = std::sqrt( (xg - matchX)*(xg - matchX) + 
                                        (yg - matchY)*(yg - matchY) );
          
          if( m_debug) std::cout << "distance: " 
                                 << xg << " " 
                                 << yg << " " 
                                 << distanceXY << " " 
                                 << bit31_decision << std::endl;
          
        }
        
      } // muon matches 

      //... Plot Muon matches types:
      hasFwdDet = false;
      
      if ( ( NmatchedDet[0] > 0 || NmatchedDet[1] > 0 ) && ( NmatchedDet[2] == 0 )  ) {
        //only in Barrel
        hasFwdDet = false;
        m_Histograms->h_matches_region ->Fill( 1 );
        m_Histograms->h_matched_eta_brl->Fill( MuonEta_TRK);
      }
      
      else if ( ( NmatchedDet[0] > 0 || NmatchedDet[1] > 0 ) && ( NmatchedDet[2] > 0 ) )  {
        //in both Barrel and Endcap
        hasFwdDet = false;
        m_Histograms->h_matches_region ->Fill( 2 );
        m_Histograms->h_matched_eta_brlfwd->Fill(MuonEta_TRK );
      }
      
      else if ( ( NmatchedDet[0] == 0 && NmatchedDet[1] == 0 ) && ( NmatchedDet[2] > 0 ) ) {
        //only in edcap
        hasFwdDet = true;
        m_Histograms->h_matches_region ->Fill( 3 );
        m_Histograms->h_matched_eta_fwd->Fill( MuonEta_TRK);
      }
      else {
        std::cout << " No muon chambers matched ?!" << std::endl;
      }
      
      if ( bit31_decision ) {
        
        m_Histograms->h_trkMuon_eta_phi_only_bit31->Fill(MuonEta_TRK, MuonPhi_TRK );
        m_Histograms->h_trkMuon_eta_only_bit31->Fill( MuonEta_TRK );
        m_Histograms->h_trkMuon_pt_only_bit31->Fill( MuonPt_TRK );
        m_Histograms->h_trkMuon_dz_only_bit31->Fill( Muondsz_TRK );
        
      } else if ( counter == 1 ) {
        
        std::cout << "Not trigger by Bit31 evt= " << ieventX << std::endl;
        
      } else {}

      //....................................................................
      goodMuCand = false;
      
      if( std::fabs( MuonEta_TRK ) < 1.6 && (! hasFwdDet) ) {
        
        m_Histograms->h_trkMuon_eta_brl->Fill( MuonEta_TRK ); //Barrel muons
        m_Histograms->h_trkMuon_pt_brl->Fill( MuonPt_TRK );
        m_Histograms->h_Rb1st_Nhits_good_mu->Fill ( n_matched_hits_RBSt1.size() );
        
        goodMuCand = true;
              
      } else {
        
        std::cout << "this muon does not count!!!!" << std::endl;
      
      }
      
      //....................................................................

      if (m_debug) std::cout << runidX << " "
                             << ieventX << " "
                             << bxX << " "
                             << iorbitX << " " 
                             << lumiSec << " "
                             << Muond0_TRK << " "
                             << Muondsz_TRK << " "
                             << MuonChi2_TRK << " "
                             << MuonEta_TRK << " "
                             << MuonPhi_TRK << " "
                             << MuonPt_TRK << " "
                             << Nchambers_TRK << " "
                             << std::endl;
      
      trkMuonMatches.clear();
      
      //....................................................................
    
      m_isBit31_matched = false;
      
      for( itrNRBSt1 = n_matched_hits_RBSt1.begin() ; itrNRBSt1 != n_matched_hits_RBSt1.end(); ++itrNRBSt1 ) {
        
        std::cout << "hits at RBSt1: W:" << (*itrNRBSt1).first << " " << (*itrNRBSt1).second << std::endl;
        
        if ( (*itrNRBSt1).second >= 2 && bit31_decision )
          m_isBit31_matched |= true;
        
      }
      
      if ( m_isBit31_matched && goodMuCand ) {
        
        m_Histograms->h_trkMuon_eta_phi_bit31->Fill(MuonEta_TRK, MuonPhi_TRK );
        m_Histograms->h_trkMuon_eta_bit31->Fill( MuonEta_TRK );
        m_Histograms->h_trkMuon_pt_bit31->Fill( MuonPt_TRK );
        m_Histograms->h_trkMuon_dz_bit31->Fill( Muondsz_TRK );
        
      }
      else if ( goodMuCand )
      {
        
        m_Histograms->h_Rb1st_Nhits_no_match->Fill( n_matched_hits_RBSt1.size() );
        
        if (m_debug) std::cout << "no match " 
                               << runidX << " "
                               << ieventX << " "
                               << bxX << " "
                               << iorbitX << " " 
                               << lumiSec << " "
                               << Muond0_TRK << " "
                               << Muondsz_TRK << " "
                               << MuonChi2_TRK << " "
                               << MuonEta_TRK << " "
                               << MuonPhi_TRK << " "
                               << MuonPt_TRK << " "
                               << Nchambers_TRK << " RpcHits: "
                               << n_matched_hits_RBSt1.size()
                               << std::endl;

        std::cout << "Muon selection K: ";
        
        for(int k=1; k < 24; ++k ) {
          std::cout << k << "= " << muon::isGoodMuon( (*muon) , (muon::SelectionType) k ) << " ";
        }

        std::cout << std::endl;

         keepEvent |= true;
         
      } else {
        
      }
      
      
    } //... Muon type
    
    n_matched_hits_RBSt1.clear();
    n_rpchits_bx_RBSt1.clear();
    
  } //... muons
  
    //....................................................................
  
  
  return keepEvent;
  
}

bool
L1TTUStudies::applyMuonCuts( const reco::Muon & muon) 
{

  bool selectCriteria = muon::isGoodMuon( muon , (muon::SelectionType) m_GoodMuonSelection );

  return selectCriteria;
  
}

int 
L1TTUStudies::getBarrelLayer( int level , int station)
{
  
  //... Calculates the generic Barrel Layer (1 to 6)
  int blayer(0);
  
  if ( station < 3 ) {
    blayer = ( (station-1) * 2 ) + level;
  }
  else {
    blayer = station + 2;
  }
  
  return blayer;

}

void 
L1TTUStudies::beginJob( )
{

  edm::Service<TFileService> fs;
  m_Histograms = new TTUHistograms( fs , "TTUStudies");
  
}

void 
L1TTUStudies::beginRun( const edm::EventSetup& iSetup )
{
  std::cout << "this is done at the start of each run" << std::endl;
}

void
L1TTUStudies::initialize()
{
  
  m_maxttBits = m_ttBits.size();
  m_maxttBitsTrigger  = m_makeCoincidenceTT.size();
  m_maxAlgBitsTrigger = m_makeCoincidenceAlg.size();
  m_tracker_activity = false;
  
}

void 
L1TTUStudies::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TTUStudies);
