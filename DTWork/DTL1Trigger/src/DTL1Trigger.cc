#include "DTWork/DTL1Trigger/src/DTL1Trigger.h"

#include "DTWork/DTL1Trigger/src/DTRecHitBxAssociator.h"

DTL1Trigger::DTL1Trigger(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_gmtReadoutLabel    = iConfig.getParameter<edm::InputTag>("GMTReadoutRcd");
  m_hltResultsLabel    = iConfig.getParameter<edm::InputTag>("TriggerResultsLabel");
  m_trackLabel         = iConfig.getParameter<edm::InputTag>("TrackLabel");
  m_dtChambPhLabel     = iConfig.getParameter<edm::InputTag>("DTChamPhLabel");
  m_dtlocaltrigLabel   = iConfig.getParameter<edm::InputTag>("DTLocalTrigLabel");
  m_debug = true;

  m_noL1info = false;
  m_noHLTinfo = false;
  m_noGMTinfo = false;
  m_noTrackinfo = false;
  
}


DTL1Trigger::~DTL1Trigger()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DTL1Trigger::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  /*

  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
  unsigned int runidX  = iEvent.run();
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  unsigned int lumiSec = iEvent.luminosityBlock();

  */
  
  m_evt = iEvent.id().event();
  EventInfo * event = new EventInfo();

  //..............................................................................................
  // L1GT
  edm::Handle< L1GlobalTriggerReadoutRecord > gtReadoutHandle;
  iEvent.getByLabel( m_gtReadoutLabel, gtReadoutHandle);
  
  if ( !gtReadoutHandle.isValid() ) {
    std::cout << "L1GtTtuAnalyzer" << "can't find L1GlobalTriggerRecord with label: " 
              << m_gtReadoutLabel << '\n';
    
    m_noL1info = true;
  }
  
  
  //..............................................................................................
  // HLT 
    
  edm::Handle< edm::TriggerResults > triggerResultsHandle;
  iEvent.getByLabel( m_hltResultsLabel, triggerResultsHandle);
  if ( !triggerResultsHandle.isValid()) {
    std::cout << "L1GtTtuAnalyzer" << "can't find TriggerResults with label: " 
              <<  m_hltResultsLabel << '\n';
    
    m_noHLTinfo = true;
    
  }
  
  //..............................................................................................
  // L1GMT
  
  edm::Handle<L1MuGMTReadoutCollection> gmtReadoutHandle;
  iEvent.getByLabel(m_gmtReadoutLabel, gmtReadoutHandle);
  
  if ( !gmtReadoutHandle.isValid() ) {
    std::cout << "DTL1Trigger> " << " can't find L1MuGMTReadoutCollection with label "
              << m_gmtReadoutLabel << '\n';
    
    m_noGMTinfo = true;
    
  }
  
  if ( ! m_noGMTinfo ) {
      
    // get GMT readout collection
    
    const L1MuGMTReadoutCollection * gmtRC = gmtReadoutHandle.product();
    
    // get record vector
    std::vector<L1MuGMTReadoutRecord>::const_iterator RRItr;
    
    std::vector<L1MuGMTReadoutRecord> gmt_records = gmtRC->getRecords();
    
    edm::LogInfo("DiscriminateGMT") << "nRecords: " << gmt_records.size() << '\n';
    
    for( RRItr = gmt_records.begin(); RRItr != gmt_records.end(); RRItr++ ) {
      
      int BxInEvent = RRItr->getBxInEvent();
      int BxInEventNew = RRItr->getBxNr();
      
      // DT barrel muon candidates
      int ndtB  = 0;
      
      //std::vector<L1MuRegionalCand> BrlRPCCands  = RRItr->getRPCBXCands ();
      std::vector<L1MuRegionalCand> BrlDTCands  = RRItr->getDTBXCands ();
      
      std::vector<L1MuRegionalCand>::const_iterator RCItr;
      
      for( RCItr = BrlDTCands.begin(); RCItr !=BrlDTCands.end(); ++RCItr) {
        if ( !(*RCItr).empty() ) {
	  
          if( m_debug) std::cout << "Found " << ndtB << " valid barrel DT candidates in bx wrt. L1A = "
                                 << (*RCItr).bx() << '\t'
                                 << BxInEvent << '\t'
                                 << BxInEventNew << std::endl;
          
          ndtB++;
        }
      }
    }
  }

  //..............................................................................................
  //TrackCollection
  
  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackLabel, trackCollectionHandle);
  
  if ( !trackCollectionHandle.isValid() ) {
    std::cout << "DTL1Trigger> " << " can't find L1MuGMTReadoutCollection with label "
              << m_gmtReadoutLabel << '\n';
    
    m_noTrackinfo = true;
    
  }
  
  std::vector<DTRecHit1D*> dtrechitsVec;
  std::vector<L1MuDTChambPhDigi*> dttfDigisVec;
  
  if ( ! m_noTrackinfo  ) {
      
    reco::TrackCollection::const_iterator trackItr;
    
    int rechitcounter = 0;
    int trackcounter = 0;
    
    for (trackItr = trackCollectionHandle->begin(); trackItr != trackCollectionHandle->end(); trackItr++) {
      
      trackingRecHit_iterator recHitItr;
      
      trackcounter++;
      rechitcounter = 0;
      
      m_trkchi2 = trackItr->chi2();
      m_trkchg  = trackItr->charge();
      
      if (m_debug) std::cout << trackcounter << "*" << std::endl;
      
      for( recHitItr = trackItr->recHitsBegin(); recHitItr != trackItr->recHitsEnd(); recHitItr++) {
	
	rechitcounter++;
	
	if ( (*recHitItr)->geographicalId().det() != DetId::Muon ) 
	  continue;
	
	if ( (*recHitItr)->geographicalId().subdetId() != MuonSubdetId::DT )  {
	  continue;
	}
	
	if ( !(*recHitItr)->isValid() ) continue;
	
	m_trk  = trackcounter;
	m_time = ((DTRecHit1D*)(&(**recHitItr)))->digiTime();
	m_lr   = ((DTRecHit1D*)(&(**recHitItr)))->lrSide();
	
	m_sc   = ((DTRecHit1D*)(&(**recHitItr)))->wireId().sector();
	m_st   = ((DTRecHit1D*)(&(**recHitItr)))->wireId().station();
	m_wh   = ((DTRecHit1D*)(&(**recHitItr)))->wireId().wheel();
	m_lyr  = ((DTRecHit1D*)(&(**recHitItr)))->wireId().layer();
	m_sly  = ((DTRecHit1D*)(&(**recHitItr)))->wireId().superLayer();

	// Transform hit position from local chamber geometry to global CMS geom
	LocalPoint rhitLocPos= ((DTRecHit1D*)(&(**recHitItr)))->localPosition();

	DTWireId wireId = ((DTRecHit1D*)(&(**recHitItr)))->wireId();
	const DTLayer* layer = muonGeom->layer(wireId);
	GlobalPoint rhitGlobPos= layer->toGlobal( rhitLocPos );
	
	m_xi   =  rhitGlobPos.x();
	m_yi   =  rhitGlobPos.y();
	
	if (m_debug) std::cout << m_evt << " " << rechitcounter << " " 
			       << (*recHitItr)->geographicalId().subdetId() << " "
			       << rhitLocPos.x() << " " << rhitLocPos.y() << " GB-X "
			       << m_xi << " GB-Y " << m_yi << " "
			       << m_wh << " " << m_sc << " " << m_st << " "
			       << m_sly << " " << m_lyr << " " 
			       << ((DTRecHit1D*)(&(**recHitItr)))->lrSide() << "=" << m_lr
			       << std::endl;
	
	if ( m_sly == 2 ) continue;
	
	dtrechitsVec.push_back( ((DTRecHit1D*)(&(**recHitItr))) );
	
	h_dtTime->Fill( m_time );
	m_tree->Fill( );
	
      }
    }
  }
  
  //..............................................................................................
  //DTTF info
  
  if ( 1 ) {
    
    //... DTBX - phi segment data)
    
    edm::Handle<L1MuDTChambPhContainer> l1DTTPGPh;
    iEvent.getByLabel(m_dtChambPhLabel, l1DTTPGPh);
    
    std::vector<L1MuDTChambPhDigi> *  phTrigs = l1DTTPGPh->getContainer();
    
    std::vector<L1MuDTChambPhDigi>::const_iterator iph;
    std::vector<L1MuDTChambPhDigi>::const_iterator iphe = phTrigs->end();
    
    int diffBxAssignment = 0;

    int wh_0  = -1000;
    int sec_0 = -1000;
    int ch_0  = -1000;
    int bx_0  = -1000;
    int xl_0  = -1000;

    for(iph  = phTrigs->begin(); iph !=iphe ; ++iph) {
            
      int qual = iph->code();
      int bx   = iph->bxNum();
      int ch   = iph->stNum();
      int sec  = iph->scNum() + 1; // DTTF range [0:11] -> DT SC range [1:12] 
      int wh   = iph->whNum();
      
      std::cout << "dttf-Ph: " << qual << '\t' << bx << '\t' << wh << '\t' << sec << '\t' << ch << '\n';
      
      //DT Trigger Position(?)
      LocalPoint trigPos = trigGeomUtils->trigLocalPos( &(*iph) );
      
      DTChamberId dtChIdSC = DTChamberId( wh, ch, sec);
      int indexCh = dtChIdSC.rawId(); 
      DTWireId wireId( indexCh );
      const DTLayer* layer = muonGeom->layer(wireId);
      
      GlobalPoint trigGlobPos= layer->toGlobal( trigPos );
      
      std::cout << "dttf-Ph: pos x " << trigPos.x() << " y " << trigPos.y() << '\n';
      std::cout << "dttf-Ph: pos GB-X " << trigGlobPos.x() << " GB-Y " << trigGlobPos.y() << '\n';
      
      dttfDigisVec.push_back( (L1MuDTChambPhDigi*)&(*iph) );
      
      double xl = trigPos.x();
      
      //////////
      if ( wh_0 == wh && sec_0 == sec && ch_0 == ch && (bx_0 != bx) ) {

	++diffBxAssignment;

	/*
	if ( xl_0 == xl )
	++diffBxAssignment;
	else { 
	std::cout << "Diff Bx assigment but different XL at evt: " 
	<< m_evt << '\t' 
	<< bx << '\t' 
	<< wh << '\t' 
	<< sec << '\t' 
	<< ch << std::endl; 
	}
	*/

      }
      
      wh_0  = wh;
      sec_0 = sec;
      ch_0  = ch;
      bx_0  = bx;
      xl_0  = xl;
      
      h_dtBx->Fill( bx );
      h_dtQual->Fill( qual );
      h_diffBxAssignmentVsQual->Fill( diffBxAssignment, qual );

    }

    h_diffBxAssignment->Fill( diffBxAssignment );
    
    //Run here the associator
    DTRecHitBxAssociator * associator = new DTRecHitBxAssociator();
    
    associator->Run( dtrechitsVec, dttfDigisVec );
    
    std::vector<DTRecHitwBx*>::const_iterator itrHitsBx;
    
    for( itrHitsBx = associator->m_hitsWBx.begin(); 
	 itrHitsBx != associator->m_hitsWBx.end(); 
	 ++itrHitsBx) {

      int sl = (*itrHitsBx)->m_hit->wireId().superLayer();
      int bx = (*itrHitsBx)->m_bx;
      int qu = (*itrHitsBx)->m_qual;

      if( m_debug) std::cout << "using: " << (*itrHitsBx)->m_hit << " " 
			     << sl << " " 
			     << bx << " " 
			     << qu << std::endl;

      
    }

    //associator->Run( dtrechitsVec, dttfPhiDigisVec, dttfThDigisVec);


    bool hasInc = associator->hasIncrementalBx();
    
    if ( hasInc ) {
      if( m_debug ) std::cout << "Found increasing BX" << std::endl;
    }
    
    dtrechitsVec.clear();
    dttfDigisVec.clear();
   
    delete associator;

    //... DTBX - th segment data)
    edm::Handle<L1MuDTChambThContainer> l1DTTPGTh;
    iEvent.getByLabel(m_dtChambPhLabel, l1DTTPGTh);
    
    std::vector<L1MuDTChambThDigi> *  thTrigs = l1DTTPGTh->getContainer();
    
    std::vector<L1MuDTChambThDigi>::const_iterator ith;
    std::vector<L1MuDTChambThDigi>::const_iterator ithe = thTrigs->end();
    
    for(ith  = thTrigs->begin(); ith !=ithe ; ++ith) {
      
      //int qual = ith->code();
      int bx   = ith->bxNum();
      int ch   = ith->stNum();
      int sec  = ith->scNum() + 1; // DTTF range [0:11] -> DT SC range [1:12] 
      int wh   = ith->whNum();
      
      std::cout << "dttf-Th: " << '\t' << bx << '\t' << ch << '\t' << sec << '\t' << wh << '\n';
      
    }
  }
  
  //..............................................................................................
  //DTLocalTriggerCollection
  
  if ( 0 ) {
    
    edm::Handle<DTLocalTriggerCollection> trigsDDU;
    iEvent.getByLabel(m_dtlocaltrigLabel,trigsDDU);
    
    std::cout << "DTLocalTrigger Info" << std::endl;
    
    DTLocalTriggerCollection::DigiRangeIterator detUnitIt;
    
    for (detUnitIt=trigsDDU->begin();detUnitIt!=trigsDDU->end();++detUnitIt){
      
      int ch  = (*detUnitIt).first.station();
      
      std::cout << "DTLocalTrigger Info chamber: " << ch << std::endl;
      
      const DTLocalTriggerCollection::Range& range = (*detUnitIt).second;
      
      for (DTLocalTriggerCollection::const_iterator trigIt = range.first; trigIt!=range.second;++trigIt){	
	
        int bx = trigIt->bx();
        int qual = trigIt->quality();
	std::cout << " DTLocalTrigg: " << bx << " " << qual << " " << std::endl;
      }
    }
  }
  
  if( m_debug) std::cout << "that's all for this event" << std::endl;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
DTL1Trigger::beginJob()
{
  
  edm::Service<TFileService> fs;
  
  h_rpcBx  = fs->make<TH1D>("rpcHitsBx","RPC Rec Hits BX", 7, -3.5 , 3.5);
  h_dtBx   = fs->make<TH1D>("dtHitsBx","DTBX Phi view segment data: BX", 7, -3.5 , 3.5);
  h_dtQual = fs->make<TH1D>("dtbxQual","DTBX Phi view segment data: Quality", 8, 0 , 8);
  h_dtTime = fs->make<TH1D>("dtTime","Time box", 100, 400 , 1000);
  h_diffBxAssignment = fs->make<TH1D>("diffBxAssignment","Different Bx assignment for same DTTrig phi Segment", 10, 0, 10);
  h_diffBxAssignmentVsQual = fs->make<TH2D>("diffBxAssignment.vs.Quality",
					    "Different Bx assignment for same DTTrig phi Segment vs Quality", 
					    10, 0, 10, 
					    8, 0, 8);
  
  m_outFile = new TFile("dtrecohits.root","RECREATE");
  m_tree = new TTree("t1","DT RecHits information");

  m_tree->Branch("Evt"    ,&m_evt     ,"Evt/i");
  m_tree->Branch("Xi"     ,&m_xi      ,"Xi/F");
  m_tree->Branch("Yi"     ,&m_yi      ,"Yi/F");
  m_tree->Branch("LR"     ,&m_lr      ,"LR/F");
  m_tree->Branch("Time"   ,&m_time    ,"Time/F");
  m_tree->Branch("Trk"    ,&m_trk     ,"Trk/I");
  m_tree->Branch("TrkChi2",&m_trkchi2 ,"TrkChi2/F");
  m_tree->Branch("TrkChg" ,&m_trkchg  ,"TrkChg/I");
  m_tree->Branch("Wh"     ,&m_wh      ,"Wh/I");
  m_tree->Branch("St"     ,&m_st      ,"St/I");
  m_tree->Branch("Sc"     ,&m_sc      ,"Sc/I");
  m_tree->Branch("Lyr"    ,&m_lyr     ,"Lyr/I");
  m_tree->Branch("SLy"    ,&m_sly     ,"Sly/I");
  
}

void
DTL1Trigger::beginRun(const edm::Run& run, const edm::EventSetup& context ){
  
  context.get<MuonGeometryRecord>().get(muonGeom);
  trigGeomUtils = new DTTrigGeomUtilsExt(muonGeom);
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DTL1Trigger::endJob() {

  m_tree->Write();
  m_outFile->Close();

}

//define this as a plug-in
DEFINE_FWK_MODULE(DTL1Trigger);
