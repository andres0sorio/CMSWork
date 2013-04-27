// system include files
#include "StudyL1Trigger/L1GtTechTrig/src/L1GtTechTrig.h"

//.......................................................................

L1GtTechTrig::L1GtTechTrig(const edm::ParameterSet& iConfig) : m_conf( iConfig )
{
  //now do what ever initialization is needed
  
  m_debug = false;
  
  m_ltcDigiLabel       = iConfig.getParameter<edm::InputTag>("L1TTBitsLabel");
  m_muonLabel          = iConfig.getParameter<edm::InputTag>("MuonLabel");
  m_recoMuonLabel      = iConfig.getParameter<edm::InputTag>("RecoMuonLabel");
  m_recoTracksLabel    = iConfig.getParameter<edm::InputTag>("RecoTrackLabel");    
  
  m_selFilter          = iConfig.getUntrackedParameter<int>("SelectFilter", 1);
  m_maxNBx             = iConfig.getUntrackedParameter<int>("MaxNBx", 2);
  m_bxNumMin           = iConfig.getUntrackedParameter<int>("MinBxNum", 70);
  m_bxNumMax           = iConfig.getUntrackedParameter<int>("MaxBxNum", 270);
  m_EvtWindow          = iConfig.getUntrackedParameter<int>("EventWindow", 10);
  m_precision          = iConfig.getUntrackedParameter<int>("Precision", 10);
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers");
  m_muonPtcut          = iConfig.getUntrackedParameter<double>("MuonPtCut", 4.0);
  
  m_patData            = iConfig.getUntrackedParameter<bool>("PATdata", false);
  m_trackParticles     = iConfig.getUntrackedParameter<bool>("TrackParticles", false);
  m_generalTracks      = iConfig.getUntrackedParameter<bool>("GeneralTracks", false);
  
  m_maxttBits = 7;
  m_bxFinal   = 0;
  m_nevt      = 0;
  m_maxPt     = 100;

  gzfileDump = new gz::ogzstream( "l1Gtinformation.csv.gz" );
    
}

L1GtTechTrig::~L1GtTechTrig()
{

  if ( gzfileDump ) delete gzfileDump;
  
}

//.......................................................................

void
L1GtTechTrig::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  edm::Handle< L1GtTechnicalTriggerRecord > gtRecord;
  iEvent.getByLabel( m_ltcDigiLabel , gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "L1GtTechTrig" << "can't find L1GtTechnicalTriggerRecord with label: " 
              << "rpcTechnicalTrigger" << '\n';
    return;
  }
  
  //.................................................................
    
  ttVec = gtRecord->gtTechnicalTrigger();
  
  if ( m_debug ) std::cout << "Size of technical trigger vector" << ttVec.size() << std::endl;
  
  std::vector<L1GtTechnicalTrigger>::const_iterator ttItr;
  
  bool wasEventTriggered(false);

  isTriggeredBy25 = false;

  unsigned int ieventX = iEvent.id().event();
  //unsigned int iorbitX = iEvent.orbitNumber();
  //int bxX = iEvent.bunchCrossing(); // ... 1 to 3564

  for( int k=0; k < m_maxttBits; ++k )
    wasTriggeredBy[k] = false;
  
  int k(0);
  
  if ( ttVec.size() > 0 )
    (*gzfileDump) << "L1GtTechnicalTrigger> " << ieventX << " " ;
  
  for( ttItr = ttVec.begin(); ttItr != ttVec.end(); ++ttItr) {
    
    (*gzfileDump) << (*ttItr).gtTechnicalTriggerBitNumber() << " "
                  << (*ttItr).gtTechnicalTriggerResult() << " ";
    
    m_ttBitsResults->Fill( (*ttItr).gtTechnicalTriggerBitNumber(), (int) (*ttItr).gtTechnicalTriggerResult() );
    
    m_NOttBits->Fill( (*ttItr).gtTechnicalTriggerBitNumber(), (int) ! (*ttItr).gtTechnicalTriggerResult() );
    
    wasEventTriggered |= true;
    
    wasTriggeredBy[k] = (*ttItr).gtTechnicalTriggerResult();
    
    ++k;
    
  }
  
  (*gzfileDump) << '\n';
  
  if ( ttVec.size() > 1 )
    isTriggeredBy25 = ttVec.at(1).gtTechnicalTriggerResult();
  else isTriggeredBy25 = false;
  
  m_pointingTrack->Fill( (int) isTriggeredBy25 );
  
  //...............................................................................................................
  //... Loop now over the muon candidates, sim tracks
  //    
  
  if ( m_patData ) 
    lookatPATCandidates( iEvent, iSetup );
  else
    lookatMuonCandidates( iEvent , iSetup );
  
  //...

  if ( m_trackParticles )
    lookatPSimHitsWithTracker( iEvent , iSetup );
  else
    lookatPSimHits( iEvent , iSetup );

  if ( m_generalTracks ) 
    lookatGeneralTracks( iEvent , iSetup );

  //if ( m_rpcRecHits )
  lookatRpcRecHits( iEvent , iSetup );
  
  //...............................................................................................................
  
  if ( m_debug ) std::cout << "wasEvtTriggered: " << wasEventTriggered << std::endl;
  
  ++m_nevt;
  
}

void
L1GtTechTrig::lookatGeneralTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  
  
  // Tracker: Only for Cosmics samples
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
  

  //.................................................................................................................
  
  edm::Handle< edm::View<reco::Track> > tracksHandle;
  iEvent.getByLabel(m_recoTracksLabel, tracksHandle);
  
  if ( ! tracksHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the tracks Handle"  << std::endl;
    return;
  }
  
  edm::View<reco::Track>::const_iterator track;
  //.................................................................................................................
  
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  //double x0 = beamSpot.x0();
  //double y0 = beamSpot.y0();
  
  //std::vector<bool> TrackLocation;
  //std::vector<double> TrackMomentum;
  //std::vector<double> TrackPhi;
  //std::vector<double> TrackEta;
  //std::vector<double> TrackD0;
  //std::vector<double> TrackDz;
  
  //bool isInTracker(false);
  
  int num_Tks(0);
  //int num_Tks_in_Tracker(0);
  //int num_Tks_in_Tracker_By25(0);
  //int num_Hits_in_Tracker_By25(0);
  //bool  has_Hits_in_Tracker(false);
  
  for( track=tracksHandle->begin(); track != tracksHandle->end(); ++track) {
    
    ++num_Tks;
    
    // select only those in the region of the tracker
    //.
    const DetId detid( (*track).outerDetId() );
    //std::cout << "detID: " << (*track).outerDetId() << " " << detid.det() << std::endl;
    
    //float Trackd0 =  track->d0() 
    //  - x0*sin( track->phi() ) 
    //  - y0*cos( track->phi() );
    
    //float Tracksz = track->dsz();

    //SimTracksPDG->Fill( track->pdgId() );

    //double trkPt    = track->pt();
    //double trkPhi   = track->phi();
    //double trkEta   = track->eta();
    //double trkD0    = Trackd0;
    //double trkDz    = Tracksz;
    
    const math::XYZPoint trackInpos = track->innerPosition();
    const math::XYZPoint trackOutpos = track->outerPosition();
    
    float sf = 1.0;
    
    m_hh_xy_outer_All->Fill( trackOutpos.x(), trackOutpos.y() ); 
    m_hh_yz_outer_All->Fill( trackOutpos.z()*sf, trackOutpos.y());
    m_hh_xy_inner_All->Fill( trackInpos.x(), trackInpos.y() );
    m_hh_yz_inner_All->Fill( trackInpos.z()*sf , trackInpos.y() );
    
    //(*gzfileDump) << "InnerOuterPos:All "
    //             << trackInpos.x()  << " "
    //            << trackInpos.y()  << " "
    //            << trackInpos.z()*sf << " " 
    //            << trackOutpos.x() << " "
    //            << trackOutpos.y() << " " 
    //            << trackOutpos.z()*sf << " " 
    //            << '\n';
    
    for( int k=0; k < m_maxttBits; ++k) {
      if ( ttVec.size() > 0 ) 
        if ( ttVec[k].gtTechnicalTriggerResult() ) {
          m_hh_xy_outer[k]->Fill( trackOutpos.x(), trackOutpos.y() ); 
          m_hh_yz_outer[k]->Fill( trackOutpos.z()*sf, trackOutpos.y());
          m_hh_xy_inner[k]->Fill( trackInpos.x(), trackInpos.y() );
          m_hh_yz_inner[k]->Fill( trackInpos.z()*sf , trackInpos.y() );
          (*gzfileDump) << "InnerOuterPos: "
                        << ieventX << " "
                        << iorbitX << " "
                        << bxX << " "
                        << 24+k << " "
                        << trackInpos.x()  << " "
                        << trackInpos.y()  << " "
                        << trackInpos.z()*sf << " " 
                        << trackOutpos.x() << " "
                        << trackOutpos.y() << " " 
                        << trackOutpos.z()*sf << " " 
                        << '\n';
        }
    }
    
  }
  
}

void
L1GtTechTrig::lookatRpcRecHits(const edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  
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
  
  for (rpcIt = rpcRecHits->begin(); rpcIt != rpcRecHits->end(); rpcIt++) {
    
    if ( (*rpcIt).BunchX() != 0 )
      continue;
        
    LocalPoint rhitlocal = (*rpcIt).localPosition();
    RPCDetId id  = (RPCDetId)(*rpcIt).rpcId();
    int kRegion  = id.region();
    
    const GeomDetUnit *det = geom->idToDetUnit ( id );
    
    if ( kRegion == 0 ) {
      
      GlobalPoint gp = det->toGlobal( rhitlocal );
      
      int kStation = id.station();
      int kRing    = id.ring();
      int kSector  = id.sector();
      int kLayer   = id.layer();
      int blayer   = getBarrelLayer( kLayer, kStation );     // 1 to 6
      
      m_h_RpcHits_Layer_All->Fill( blayer );
      m_h_RpcHits_Sector_All->Fill ( kSector );
      m_h_RpcHits_Wheel_All->Fill( kRing );
      
      float xg = gp.x ();
	    float yg = gp.y ();
	    float zg = gp.z ();
      
      m_hh_xy_rpc_rechit_All->Fill( xg, yg );
      m_hh_yz_rpc_rechit_All->Fill( zg, yg );
      
      if ( ttVec.size() > 0 ) 
        for( int k=0; k < m_maxttBits; ++k) {
          if ( ttVec[k].gtTechnicalTriggerResult() ) {
            
            m_h_RpcHits_Layer[k]->Fill( blayer );
            m_h_RpcHits_Sector[k]->Fill( kSector );
            m_h_RpcHits_Wheel[k]->Fill( kRing );
            
            m_hh_xy_rpc_rechit[k]->Fill( xg, yg );
            m_hh_yz_rpc_rechit[k]->Fill( zg, yg );
            
          }
        }
      
      for ( int k=1; k< 5; ++k)
        if ( kStation == k )
          ++nRPC_in_Station[k-1];
      
      nRPC++;
      
    }
    
  }
  
  //... Fraction of RPC RecHit in Stations
  
  if ( nRPC != 0 ) {
    for ( int k=0; k< 4; ++k) {
      float fraction = (float)nRPC_in_Station[k]/(float)nRPC;
      m_h_RpcHits_FracStation[k]->Fill( fraction );
            
    }
  }
      
}

int 
L1GtTechTrig::getBarrelLayer( const int & _layer, const int & _station )
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

void 
L1GtTechTrig::lookatPATCandidates(const edm::Event& iEvent, const edm::EventSetup& iSetup) 
{

  std::cout << "Using PAT" << std::endl;
  
  edm::Handle<edm::View<pat::Muon> > patHandle;
  iEvent.getByLabel( m_muonLabel , patHandle);
  
  if ( ! patHandle.isValid() ) {
    std::cout << "PATCosmicStudy::analyze> there is a problem with the muon Handle"  << std::endl;
    return;
  }
  
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  double x0 = beamSpot.x0();
  double y0 = beamSpot.y0();
  
  int num_Mu(0);
  
  for( edm::View<pat::Muon>::const_iterator muon=patHandle->begin(); muon != patHandle->end(); ++muon) {
    
    ++num_Mu;
    
    if(muon->isStandAloneMuon())
      if(muon->isGlobalMuon())
        if(muon->isTrackerMuon()) MuonType->Fill(1);  // STA + GLB + TM
        else MuonType->Fill(2); // STA + GLB
      else 
        if(muon->isTrackerMuon()) MuonType->Fill(3);  // STA + TM
        else MuonType->Fill(5); // STA
    else
      if(muon->isTrackerMuon()) MuonType->Fill(4);    // TM
    
    //....................................................................
    
    if ( ! muon->standAloneMuon() )
      continue;
    
    //....................................................................
    
    float Muond0_STA  = muon->standAloneMuon()->d0() 
      - x0*sin( muon->standAloneMuon()->phi() ) 
      - y0*cos( muon->standAloneMuon()->phi() );
    float Muondsz_STA = muon->standAloneMuon()->dsz();
    float Muond0_GBL  = 0.0;
    float Muondsz_GBL = 0.0;
    
    if ( muon->isGlobalMuon() ) {
      
      Muond0_GBL =  muon->globalTrack()->d0() 
        - x0*sin( muon->globalTrack()->phi() ) 
        - y0*cos( muon->globalTrack()->phi() );
      Muondsz_GBL = muon->globalTrack()->dsz();
      
    }
    
    MuonPt->Fill( muon->pt() );
    MuonEta->Fill( muon->eta() );
    MuonPhi->Fill( muon->phi() );
    MuonEtaPhi->Fill( muon->eta(), muon->phi() );
    
    Muond0dist_STA->Fill( Muond0_STA );
    Muondszdist_STA->Fill( Muondsz_STA );
    
    if ( muon->isGlobalMuon() ) {
      Muond0dist_GBL->Fill( Muond0_GBL );
      Muondszdist_GBL->Fill( Muondsz_GBL );
      MuonEtaPhi_GBL->Fill( muon->eta(), muon->phi() );
      MuonCaloCompatibility->Fill ( muon->caloCompatibility() );
      MuonPt_GBL->Fill( muon->pt() );
      
      if ( isTriggeredBy25 )  {
        MuonPt_GBL_bit25->Fill( muon->pt() );
      }
      
    }
    
  }
   
}

void 
L1GtTechTrig::lookatPSimHitsWithTracker(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //...............................................................................
  //... Using TrackingParticles and PSimHit collections
  //.
  
  std::vector<PSimHit> theTOBHits;
  std::vector<PSimHit> theTECHits;
  
  //
  edm::Handle<edm::PSimHitContainer> TOBHitsLowTof;
  iEvent.getByLabel("g4SimHits","TrackerHitsTOBLowTof",TOBHitsLowTof);
  theTOBHits.insert(theTOBHits.end(),TOBHitsLowTof->begin(),TOBHitsLowTof->end());
  
  edm::Handle<edm::PSimHitContainer> TOBHitsHighTof;
  iEvent.getByLabel("g4SimHits","TrackerHitsTOBHighTof",TOBHitsHighTof);
  theTOBHits.insert(theTOBHits.end(),TOBHitsHighTof->begin(),TOBHitsHighTof->end());
  //
  
  edm::Handle<edm::PSimHitContainer> TECHitsLowTof;
  iEvent.getByLabel("g4SimHits","TrackerHitsTECLowTof",TECHitsLowTof);
  theTECHits.insert(theTECHits.end(),TECHitsLowTof->begin(),TECHitsLowTof->end());
  
  edm::Handle<edm::PSimHitContainer> TECHitsHighTof;
  iEvent.getByLabel("g4SimHits","TrackerHitsTECHighTof",TECHitsHighTof);
  theTECHits.insert(theTECHits.end(),TECHitsHighTof->begin(),TECHitsHighTof->end());
  
  //int nSimHits = 0;
  
  if ( m_debug ) std::cout << "# Sim hits found in TOB = " <<  theTOBHits.size() << std::endl;
  if ( m_debug ) std::cout << "# Sim hits found in TEC = " <<  theTECHits.size() << std::endl;
  
  int nSimTracks(0);
  
  edm::ESHandle<TrackerGeometry> trackerGeom;
  iSetup.get<TrackerDigiGeometryRecord>().get(trackerGeom);
  theTracker = trackerGeom.product();
  
  // Tracker
  edm::Handle<TrackingParticleCollection> simTrackHandle;
  iEvent.getByLabel("mergedtruth", "MergedTrackTruth", simTrackHandle);
  
  if ( ! simTrackHandle.isValid() ) {
    edm::LogError("L1GtTechTrigger") << "can't find TrackingParticle(s) with label: " 
                                     << " mergedtruth" << '\n';
    return;
  }
  
  const TrackingParticleCollection* simTracks = simTrackHandle.product();
  
  TrackingParticleCollection::const_iterator simTrack;
  
  for( simTrack = simTracks->begin(); simTrack!= simTracks->end(); ++simTrack) {
    
    m_trackInTOB    = false;
    m_trackInTEC    = false;
    m_trackInTOBTEC = false;
    
    std::vector<PSimHit>::const_iterator itrSimHitsinTrack;
    std::vector<PSimHit>::iterator itrSimHit;
    
    int nsimHitsinTrack = 0;
    int nmatchSimHits_TOB = 0;
    int nmatchSimHits_TEC = 0;
    
    SimTracksPDG->Fill( simTrack->pdgId() );
    
    for ( itrSimHitsinTrack  = simTrack->pSimHit_begin(); 
          itrSimHitsinTrack != simTrack->pSimHit_end(); ++itrSimHitsinTrack) {
      
      TrackParticle_Pt->Fill( simTrack->pt() );
      TrackParticle_EtaPhi->Fill( simTrack->eta(), simTrack->phi() );
      
      if ( simTrack->pt() < m_muonPtcut ) continue;
      
      for ( itrSimHit = theTOBHits.begin(); itrSimHit != theTOBHits.end(); ++itrSimHit ) {
        
        int unsigned simtrackid = 0;
        simtrackid = itrSimHit->particleType();
        
        if (abs(simtrackid) != 13) continue; // Select simulated muons
        
        int unsigned simtrackInid = 0;
        simtrackInid = itrSimHitsinTrack->particleType();
        
        if( itrSimHit->localPosition().x() == itrSimHitsinTrack->localPosition().x() &&
            itrSimHit->localPosition().y() == itrSimHitsinTrack->localPosition().y() &&
            itrSimHit->localPosition().z() == itrSimHitsinTrack->localPosition().z() ) {
          ++nmatchSimHits_TOB;
        }
        
      }
      
      for ( itrSimHit = theTECHits.begin(); itrSimHit != theTECHits.end(); ++itrSimHit ) {
        
        int unsigned simtrackid = 0;
        simtrackid = itrSimHit->particleType();
        
        if (abs(simtrackid) != 13) continue; // Select simulated muons
        
        int unsigned simtrackInid = 0;
        simtrackInid = itrSimHitsinTrack->particleType();

        if( itrSimHit->localPosition().x() == itrSimHitsinTrack->localPosition().x() &&
            itrSimHit->localPosition().y() == itrSimHitsinTrack->localPosition().y() &&
            itrSimHit->localPosition().z() == itrSimHitsinTrack->localPosition().z() ) {
          ++nmatchSimHits_TEC;
          
        }
        
      }
      
      ++nsimHitsinTrack;
      
    }
    
    NumberSimHitsTrack->Fill (nsimHitsinTrack);
    
    if( nmatchSimHits_TOB > 0 ) NumberSimHitsTOB->Fill( nmatchSimHits_TOB );
    if( nmatchSimHits_TEC > 0 ) NumberSimHitsTEC->Fill( nmatchSimHits_TEC );
    
    if ( nmatchSimHits_TOB > 0 && nmatchSimHits_TEC == 0 )
      m_trackInTOB = true;
    
    if ( nmatchSimHits_TOB == 0 && nmatchSimHits_TEC > 0 )
      m_trackInTEC = true;
    
    if ( nmatchSimHits_TOB > 0 && nmatchSimHits_TEC > 0 )
      m_trackInTOBTEC = true;
    
    if ( m_debug ) std::cout << "in track: " << nsimHitsinTrack 
                             << " match: " << nmatchSimHits_TOB 
                             << " match: " << nmatchSimHits_TEC 
                             << " PDG: " << simTrack->pdgId() << std::endl ;
    
    if ( m_trackInTOB ) {
      TrackParticle_Pt_TOB->Fill( simTrack->pt() );
      TrackParticle_EtaPhi_TOB->Fill( simTrack->eta(), simTrack->phi() );
      
      for( int k=0; k < m_maxttBits; ++k ) {
        if ( wasTriggeredBy[k] )
          TrackParticle_Pt_TOB_Bit[k]->Fill( simTrack->pt() );
      }
      
    }
    
    if ( m_trackInTEC ) {
      
      TrackParticle_Pt_TEC->Fill( simTrack->pt() );
      TrackParticle_EtaPhi_TEC->Fill( simTrack->eta(), simTrack->phi() );
      
      for( int k=0; k < m_maxttBits; ++k ) {
        if ( wasTriggeredBy[k] )
          TrackParticle_Pt_TEC_Bit[k]->Fill( simTrack->pt() );
      }
      
    }
    
    if ( m_trackInTOBTEC ) {
      
      TrackParticle_Pt_TOBTEC->Fill( simTrack->pt() );
      TrackParticle_EtaPhi_TOBTEC->Fill( simTrack->eta(), simTrack->phi() );
      
      for( int k=0; k < m_maxttBits; ++k ) {
        if ( wasTriggeredBy[k] )
          TrackParticle_Pt_TOE_Bit[k]->Fill( simTrack->pt() );
      }
      
    }
    
    if ( m_trackInTOB || m_trackInTEC || m_trackInTOBTEC ) SimTracksPDG_Muon->Fill( simTrack->pdgId() );
    
    ++nSimTracks;
    
  }
  
  
}


void
L1GtTechTrig::lookatMuonCandidates( const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  
  edm::Handle< edm::View<reco::Muon> > muonHandle;
  iEvent.getByLabel(m_recoMuonLabel, muonHandle);
  
  if ( ! muonHandle.isValid() ) {
    std::cout << "L1GtTechTrig::analyze> there is a problem with the muon Handle"  << std::endl;
    return;
  }
  
  edm::View<reco::Muon>::const_iterator muon;
  
  //edm::Handle<std::vector<SimTrack> > simTracks;
  //iEvent.getByLabel("g4SimHits", "", simTracks);
  //if ( ! simTracks.isValid() ) {
  //  std::cout <<  "can't find vector<SimTrack>(s) with label: " << "g4SimHits" << '\n';
  //  return;
  //}
  
  //.................................................................................................................
  
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  double x0 = beamSpot.x0();
  double y0 = beamSpot.y0();
  
  int num_Mu(0);
  
  for( muon=muonHandle->begin(); muon != muonHandle->end(); ++muon) {
    
    ++num_Mu;
    
    if(muon->isStandAloneMuon())
      if(muon->isGlobalMuon())
        if(muon->isTrackerMuon()) MuonType->Fill(1);  // STA + GLB + TM
        else MuonType->Fill(2); // STA + GLB
      else 
        if(muon->isTrackerMuon()) MuonType->Fill(3);  // STA + TM
        else MuonType->Fill(5); // STA
    else
      if(muon->isTrackerMuon()) MuonType->Fill(4);    // TM
    
    //....................................................................
    
    
    
    
    
    
    
    

    //....................................................................

    if ( muon->isStandAloneMuon() ) {
      
      float Muond0_STA = 0.0;
      Muond0_STA = muon->standAloneMuon()->d0() 
        - x0*sin( muon->standAloneMuon()->phi() ) 
        - y0*cos( muon->standAloneMuon()->phi() );
      float Muondsz_STA = 0.0;
      Muondsz_STA = muon->standAloneMuon()->dsz();
      
      //...
      MuonPt->Fill( muon->standAloneMuon()->pt() );
      MuonEtaPhi->Fill(  muon->standAloneMuon()->eta(), muon->standAloneMuon()->phi() );
      
      //for( int k=0; k < m_maxttBits; ++k ) {
      //  if ( wasTriggeredBy[k] ) {
      //    m_HMuonPt_Bit[k]->Fill( muon->standAloneMuon()->pt() );
      //    m_HMuonEtaPhi_Bit[k]->Fill( muon->standAloneMuon()->eta(), muon->standAloneMuon()->phi() );
      //}
      //}
      
    }
    
     //....................................................................
    
    if ( muon->isGlobalMuon() ) {
      
       float Muond0_GBL =  muon->globalTrack()->d0() 
         - x0*sin( muon->globalTrack()->phi() ) 
         - y0*cos( muon->globalTrack()->phi() );
       float Muondsz_GBL = muon->globalTrack()->dsz();
       
       //...
       MuonPt_GBL->Fill( muon->globalTrack()->pt() );
       MuonEtaPhi_GBL->Fill( muon->globalTrack()->eta(), muon->globalTrack()->phi() );
       Muond0dist_GBL->Fill( Muond0_GBL );
       Muondszdist_GBL->Fill( Muondsz_GBL );
              
       Muond0dist_GBL->Fill(Muond0_GBL);
       Muondszdist_GBL->Fill(Muondsz_GBL);
       
       for( int k=0; k < m_maxttBits; ++k ) {
         if ( wasTriggeredBy[k] ) {
           m_HMuonPt_Bit[k]->Fill( muon->globalTrack()->pt() );
           m_HMuonEtaPhi_Bit[k]->Fill( muon->globalTrack()->eta(), muon->globalTrack()->phi() );
           m_HMuond0dist_Bit[k]->Fill( Muond0_GBL );
           m_HMuondszdist_Bit[k]->Fill( Muondsz_GBL );
           
         }
         
       }
       
     } else {

       m_pointingNoRecoTrack->Fill( (int) isTriggeredBy25 );
       
     }
     
     
   }
   
}

void 
L1GtTechTrig::lookatPSimHits( const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  std::vector<PSimHit> theTOBHits;
  std::vector<PSimHit> theTECHits;
  
  edm::Handle<std::vector<SimTrack> > simTracks;
  iEvent.getByLabel("g4SimHits", "", simTracks);
  
  if ( ! simTracks.isValid() ) {
    edm::LogError("L1GtTechTrigger") << "can't find vector<SimTrack>(s) with label: " 
                                     << "g4SimHits" << '\n';
    return;
  }
  
  edm::SimTrackContainer::const_iterator simTrack;
  std::vector<PSimHit>::iterator itrSimHit;
  
  int nSimTracks(0);
  int nsimHitsinTrack = 0;
  int nmatchSimHits_TOB = 0;
  int nmatchSimHits_TEC = 0;
  
  m_trackInTOB    = false;
  m_trackInTEC    = false;
  m_trackInTOBTEC = false;
  
  int simTrackPos(0);
  
  if ( (*simTracks).size() <= 0 ) return;
  
  int pos=0;
  
  for ( simTrack = (*simTracks).begin(); simTrack != (*simTracks).end(); ++simTrack ) {
    
    SimTracksPDG->Fill( simTrack->type() );
    
    if ( abs( simTrack->type() ) == 13 ) {
      
      simTrackPos = pos;
      
      SimTracksPDG_Muon->Fill( simTrack->type() );
      TrackParticle_Pt->Fill( simTrack->momentum().pt() );
      TrackParticle_EtaPhi->Fill( simTrack->momentum().eta(), simTrack->momentum().phi() );
      
      ++nmatchSimHits_TOB;
      ++nmatchSimHits_TEC;
      
      //... TOB
      for ( itrSimHit = theTOBHits.begin(); itrSimHit != theTOBHits.end(); ++itrSimHit ) {
        ++nsimHitsinTrack;
        
        int unsigned simtrackid = 0;
        simtrackid = itrSimHit->particleType();
        
        if (abs(simtrackid) != 13) continue; // Select simulated muons
        ++nmatchSimHits_TOB;
        
      }
      
      //... TEC
      for ( itrSimHit = theTECHits.begin(); itrSimHit != theTECHits.end(); ++itrSimHit ) {
        ++nsimHitsinTrack;
        
         int unsigned simtrackid = 0;
         simtrackid = itrSimHit->particleType();
         
         if (abs(simtrackid) != 13) continue; // Select simulated muons
         ++nmatchSimHits_TEC;
         
      }

      //for( int k=0; k < m_maxttBits; ++k) {
      //  
      //  m_hh_xy_outer[k]->Fill(simTrack-> , simTrack-> );
      //  m_hh_yz_outer[k]->Fill(simTrack-> , simTrack-> );
      //  m_hh_xy_inner[k]->Fill(simTrack-> , simTrack-> );
      //  m_hh_yz_inner[k]->Fill(simTrack-> , simTrack-> );
      //  
      //}
      
     
    } //if track_id = muon
    
    ++pos;
    
  }
  
  NumberSimHitsTrack->Fill (nsimHitsinTrack/2);
  
  if( nmatchSimHits_TOB  > 0 ) NumberSimHitsTOB->Fill( nmatchSimHits_TOB );
  if( nmatchSimHits_TEC  > 0 ) NumberSimHitsTEC->Fill( nmatchSimHits_TEC );
  
  if ( nmatchSimHits_TOB > 0 && nmatchSimHits_TEC == 0 )
    m_trackInTOB = true;
  
  if ( nmatchSimHits_TOB == 0 && nmatchSimHits_TEC > 0 )
     m_trackInTEC = true;
  
  if ( nmatchSimHits_TOB > 0 && nmatchSimHits_TEC > 0 )
    m_trackInTOBTEC = true;
  
  if ( m_debug ) std::cout << "in track: " << nsimHitsinTrack 
                           << " match: "   << nmatchSimHits_TOB 
                           << " match: "   << nmatchSimHits_TEC << std::endl ;
  
  if ( m_trackInTOB ) {
    TrackParticle_Pt_TOB->Fill( (*simTracks)[simTrackPos].momentum().pt() );
    TrackParticle_EtaPhi_TOB->Fill( (*simTracks)[simTrackPos].momentum().eta(), (*simTracks)[simTrackPos].momentum().phi() );
    
    for( int k=0; k < m_maxttBits; ++k ) {
      if ( wasTriggeredBy[k] )
        TrackParticle_Pt_TOB_Bit[k]->Fill( (*simTracks)[simTrackPos].momentum().pt() );
    }
     
  }
  
  
  if ( m_trackInTEC ) {
    
    TrackParticle_Pt_TEC->Fill( (*simTracks)[simTrackPos].momentum().pt() );
    TrackParticle_EtaPhi_TEC->Fill( (*simTracks)[simTrackPos].momentum().eta(), (*simTracks)[simTrackPos].momentum().phi() );
    
    for( int k=0; k < m_maxttBits; ++k ) {
      if ( wasTriggeredBy[k] )
        TrackParticle_Pt_TEC_Bit[k]->Fill( (*simTracks)[simTrackPos].momentum().pt() );
    }
    
  }
  
  
  if ( m_trackInTOBTEC ) {
    
    TrackParticle_Pt_TOBTEC->Fill( (*simTracks)[simTrackPos].momentum().pt() );
    TrackParticle_EtaPhi_TOBTEC->Fill( (*simTracks)[simTrackPos].momentum().eta(), (*simTracks)[simTrackPos].momentum().phi() );
    
    for( int k=0; k < m_maxttBits; ++k ) {
      if ( wasTriggeredBy[k] )
        TrackParticle_Pt_TOE_Bit[k]->Fill( (*simTracks)[simTrackPos].momentum().pt() );
    }
    
  }
  
  //if ( m_trackInTOB || m_trackInTEC || m_trackInTOBTEC ) SimTracksPDG_Muon->Fill( (*simTracks)[simTrackPos].type() );
  
  ++nSimTracks;
  
  NumberSimTracks->Fill(nSimTracks);
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
L1GtTechTrig::beginJob()
{
  
  edm::Service<TFileService> fservice;
  
  TFileDirectory patcan     = fservice->mkdir( "PATCandidates" );
  TFileDirectory muoncan    = fservice->mkdir( "MuonCandidates" );
  TFileDirectory psimhits   = fservice->mkdir( "PSimHits" );
  TFileDirectory psimhittk  = fservice->mkdir( "PSimHitsWithTracker" );
  TFileDirectory generaltks = fservice->mkdir( "GeneralTracks" );
  TFileDirectory rpcrechits = fservice->mkdir( "lookatRpcRecHits" );
  TFileDirectory l1trigger  = fservice->mkdir( "L1TechnicalTrigger" );
  
  m_ttBitsResults = l1trigger.make<TH1D>("TechTrigger.Bits",
                                         "Technical Trigger bits : Summary", 9, 23, 32 );
  
  m_NOttBits = l1trigger.make<TH1D>("No.TechTrigger.Bits",
                                    "Technical Trigger bits : Summary", 9, 23, 32 );
  
  m_pointingTrack = generaltks.make<TH1D>("Bit.25.Tracks","Bit 25 performance - association with recoTracks",2,0,1);
  
  m_pointingNoRecoTrack = generaltks.make<TH1D>("Bit.25.NoRecoTracks","Bit 25 performance - association with recoTracks",2,0,1);
  
  MuonType       = muoncan.make<TH1D>("MuonType","Muon Type", 7, 0.0, 7.0);
  
  NumberMuonsEvt = muoncan.make<TH1D>("NumberMuonsEvt","Number of muons per event", 15, 0.0, 15.0);
  
  MuonCaloCompatibility = muoncan.make<TH1D>("Muon.CaloComp","Muon calo Compatibility", 100, 0.0 , 1.0);
  
  //....................................................................................................................
  
  MuonPt         = muoncan.make<TH1D>("MuonPt","Muon Pt", 100,  0.0, m_maxPt);
  MuonEta        = muoncan.make<TH1D>("MuonEta","Muon Eta", 60, -5.0, 5.0);
  MuonEtaPhi     = muoncan.make<TH2D>("Muon.Eta.Phi","Muon Eta vs Phi", 60, -5.0, 5.0, 60, -4.0, 4.0 );
  MuonPhi        = muoncan.make<TH1D>("MuonPhi","Muon Phi", 60,  -4.0, 4.0);
  MuonChi2DoF    = muoncan.make<TH1D>("MuonChi2DoF","Muon Track Chi2/DoF",   100,0.0,12.0);
  
  NumberJetsEvt  = muoncan.make<TH1D>("NumberJetsEvt","Number of jets per event", 20, 0.0, 20.0);
  JetsEtaPhi     = muoncan.make<TH2D>("Jets.Eta.Phi","Jets Eta vs Phi", 60, -5.0, 5.0, 60, -4.0, 4.0 );
  JetsEtaPt      = muoncan.make<TH2D>("Jets.Eta.Pt","Jets Eta vs Pt", 60, -5.0, 5.0, 100, 0.0, 100.0 );
  
  //....................................................................................................................
  //STA plots

  Muond0dist_STA     = muoncan.make<TH1D>("Muond0.sta","Muon d0", 200, -1000.0 , 1000.0);
  Muondszdist_STA    = muoncan.make<TH1D>("Muondsz.sta","Muon dsz", 200, -1000.0 , 1000.0);
  
  //....................................................................................................................
  //GBL plots
  
  Muond0dist_GBL     = muoncan.make<TH1D>("Muond0.gbl","Muon d0", 200, -1000.0 , 1000.0);
  Muondszdist_GBL    = muoncan.make<TH1D>("Muondsz.gbl","Muon dsz", 200, -1000.0 , 1000.0);
  MuonEtaPhi_GBL     = muoncan.make<TH2D>("Muon.Eta.Phi.GBL","Muon Eta vs Phi of GL", 60, -5.0, 5.0, 60, -4.0, 4.0 );

  MuonPt_GBL         = muoncan.make<TH1D>("MuonPt.GBL","Global Muon Pt", 100,0.0, m_maxPt);
  MuonPt_GBL->Sumw2();
  MuonPt_GBL_bit25   = muoncan.make<TH1D>("MuonPt.GBL.bit.25","Global Muon Pt: triggered by RPC-TT", 100,0.0, m_maxPt);
  MuonPt_GBL_bit25->Sumw2();
  
  TrackParticle_Pt = generaltks.make<TH1D>("TrackParticle.Pt","Tracking particle Pt", 100,0.0, m_maxPt);
  TrackParticle_Pt->Sumw2();

  TrackParticle_EtaPhi = generaltks.make<TH2D>("TrackParticle.Eta.Phi",
                                              "Tracking particle Eta vs Phi", 
                                              60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    std::ostringstream hname;
    
    hname << "Selected.Muon.Pt.Bit." << m_ttBits[k];
    
    m_HMuonPt_Bit[k] = muoncan.make<TH1D>( hname.str().c_str(),"Selected muon Pt bit", 100, 0.0, m_maxPt);
    m_HMuonPt_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "Selected.Muon.EtaPhi.Bit." << m_ttBits[k];
    
    m_HMuonEtaPhi_Bit[k] = muoncan.make<TH2D>(hname.str().c_str(),"Selected muon eta/phi bit", 60, -5.0, 5.0, 60, -4.0, 4.0 );
    m_HMuonEtaPhi_Bit[k]->Sumw2();
  
    hname.str("");
    hname << "Selected.Muon.do.Bit." << m_ttBits[k];

    m_HMuond0dist_Bit[k] = muoncan.make<TH1D>(hname.str().c_str(),"Selected muon d0", 200, -1000.0 , 1000.0 );
    m_HMuond0dist_Bit[k]->Sumw2();

    hname.str("");
    hname << "Selected.Muon.dz.Bit." << m_ttBits[k];
    
    m_HMuondszdist_Bit[k] = muoncan.make<TH1D>(hname.str().c_str(),"Selected muon dz", 200, -1000.0 , 1000.0 );
    m_HMuondszdist_Bit[k]->Sumw2();
  
  }

  //....................................................................................................................
  //... SimTracks plots
    
  NumberSimTracks    = generaltks.make<TH1D>("NumberSimTracks","Number of simTracks per event", 150, 0.0, 1500.0);
  SimTracksPDG       = generaltks.make<TH1D>("SimTracksPDG","simTracks PDG", 600, -300.0 , 300.0);
  SimTracksPDG_Muon  = generaltks.make<TH1D>("SimTracksPDG.Muons","simTracks PDG after selection", 600, -300.0 , 300.0);
  NumberSimHitsTrack = generaltks.make<TH1D>("NumberSimHits","Number of simHits in track event", 100, 0.0, 100.0);
  NumberSimHitsTOB   = generaltks.make<TH1D>("NumberSimHitsTOB","Number of simHits matched in TOB", 100, 0.0, 100.0);
  NumberSimHitsTEC   = generaltks.make<TH1D>("NumberSimHitsTEC","Number of simHits matched in TEC", 100, 0.0, 100.0);
  
  TrackParticle_Pt_TOB = generaltks.make<TH1D>("TrackParticle.Pt.TOB","Tracking particle Pt", 100,0.0, m_maxPt);
  TrackParticle_Pt_TOB->Sumw2();
  
  TrackParticle_EtaPhi_TOB = generaltks.make<TH2D>("TrackParticle.Eta.Phi.TOB",
                                                  "Tracking particle Eta vs Phi", 
                                                  60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  TrackParticle_Pt_TEC = generaltks.make<TH1D>("TrackParticle.Pt.TEC","Tracking particle Pt", 100,0.0, m_maxPt);
  TrackParticle_Pt_TEC->Sumw2();

  TrackParticle_EtaPhi_TEC = generaltks.make<TH2D>("TrackParticle.Eta.Phi.TEC",
                                                  "Tracking particle Eta vs Phi", 
                                                  60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  TrackParticle_Pt_TOBTEC = generaltks.make<TH1D>("TrackParticle.Pt.TOBTEC","Tracking particle Pt", 100,0.0,m_maxPt);
  TrackParticle_Pt_TOBTEC->Sumw2();

  TrackParticle_EtaPhi_TOBTEC = generaltks.make<TH2D>("TrackParticle.Eta.Phi.TOBTEC",
                                                     "Tracking particle Eta vs Phi", 
                                                     60, -5.0, 5.0, 60, -4.0, 4.0 );
  
  //....................................................................................................................
  double max_x = 600.0;
  double max_y = 400.0;
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    std::ostringstream hname;
    
    hname << "TrackParticle.Pt.TOB." << m_ttBits[k];
    
    TrackParticle_Pt_TOB_Bit[k] = generaltks.make<TH1D>( hname.str().c_str(),"Tracking particle Pt", 100,0.0, m_maxPt);
    TrackParticle_Pt_TOB_Bit[k]->Sumw2();

    hname.str("");
    hname << "TrackParticle.Pt.TEC." << m_ttBits[k];
    
    TrackParticle_Pt_TEC_Bit[k] = generaltks.make<TH1D>(hname.str().c_str(),"Tracking particle Pt", 100,0.0, m_maxPt);
    TrackParticle_Pt_TEC_Bit[k]->Sumw2();
    
    hname.str("");
    hname << "TrackParticle.Pt.TOE." << m_ttBits[k];
    
    TrackParticle_Pt_TOE_Bit[k] = generaltks.make<TH1D>(hname.str().c_str(),"Tracking particle Pt", 100,0.0, m_maxPt);
    TrackParticle_Pt_TOE_Bit[k]->Sumw2();

    hname.str("");
    hname << "Track.XY.outer.bit." << m_ttBits[k];
    
    m_hh_xy_outer[k] = generaltks.make<TH2D>( hname.str().c_str(), "Tracks XY outer: outer most XY of track", 
                                             100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
    
    hname.str("");
    hname << "Track.YZ.outer.bit." << m_ttBits[k];
    
    m_hh_yz_outer[k] = generaltks.make<TH2D>( hname.str().c_str(), "Tracks YZ outer: outer most YZ of track", 
                                             100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
    
    hname.str("");
    hname << "Track.XY.inner.bit." << m_ttBits[k];
    
    m_hh_xy_inner[k] = generaltks.make<TH2D>( hname.str().c_str(), "Tracks XY inner: inner most XY of track", 
                                             100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
    
    hname.str("");
    hname << "Track.YZ.inner.bit." << m_ttBits[k];
    
    m_hh_yz_inner[k] = generaltks.make<TH2D>( hname.str().c_str(), "Tracks YZ inner: inner most YZ of track", 
                                             100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );

    
    //

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
    m_h_RpcHits_Wheel[k]  = rpcrechits.make<TH1D>(hname.str().c_str(),"RPC RecHits Wheel", 7, -3, 3);
    
  }
  
  m_hh_xy_outer_All = generaltks.make<TH2D>( "Tracks.XY.outer.All", "Tracks XY outer: outer most XY of track", 
                                           100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_outer_All = generaltks.make<TH2D>( "Tracks.YZ.outer.All", "Tracks YZ outer: outer most YZ of track", 
                                           100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_xy_inner_All = generaltks.make<TH2D>( "Tracks.XY.inner.All", "Tracks XY inner: inner most XY of track", 
                                           100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_inner_All = generaltks.make<TH2D>( "Tracks.YZ.inner.All", "Tracks YZ inner: inner most YZ of track", 
                                           100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_xy_rpc_rechit_All = rpcrechits.make<TH2D>( "Track.XY.Rpc.RecHit.All", "Tracks XY Rpc RecHit All", 
                                                 100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_rpc_rechit_All = rpcrechits.make<TH2D>( "Track.YZ.Rpc.RecHit.All", "Tracks YZ Rpc RecHit All", 
                                                 100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_h_RpcHits_Layer_All  = rpcrechits.make<TH1D>("Rpc.Hits.Layer.All","RPC RecHits Layer", 10, 0.0, 10);
  
  m_h_RpcHits_Sector_All = rpcrechits.make<TH1D>("Rpc.Hits.Sector.All","RPC RecHits Sector", 14, 0.0, 14);
  
  m_h_RpcHits_Wheel_All  = rpcrechits.make<TH1D>("Rpc.Hits.Wheel.All","RPC RecHits Wheel", 7, -3, 3);


  //

  for( int k=0; k < 4; ++k) {
    std::ostringstream hname;
    hname.str("");
    hname << "Rpc.Hits.Fraction." << (k+1);
    m_h_RpcHits_FracStation[k]  = rpcrechits.make<TH1D>(hname.str().c_str(),"RPC RecHits Fraction in Station", 100, 0.0 , 1.1);
    
  }
    
  //....................................................................................................................
  
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1GtTechTrig::endJob() {
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1GtTechTrig);
