#include "StudyL1Trigger/PromptMuons/src/PromptMuons.h"

// system include files


PromptMuons::PromptMuons(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers");
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");

  
  m_maxttBits = m_ttBits.size();
  
}

PromptMuons::~PromptMuons()
{
  
}


// ------------ method called to for each event  ------------
void
PromptMuons::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //..............................................................................................
 
  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( m_gtReadoutLabel, gtRecord);
  
  if ( !gtRecord.isValid() ) {
    std::cout << "PromptMuons" << "can't find L1GlobalTriggerRecord with label: " 
              << m_gtReadoutLabel << '\n';
    return;
  }
  
  //..............................................................................................
  
  unsigned int ieventX = iEvent.id().event();
  unsigned int iorbitX = iEvent.orbitNumber();
  int bxX = iEvent.bunchCrossing(); // ... 1 to 3564
  
  m_bxDistEvent->Fill( bxX );
  
  std::map<int,bool> ttuDec;
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(0);
    
    ttVec.push_back( gtTTWord[ 24+k ] );
    
    if ( gtTTWord[ 24+k ] ) {
      m_bxDist[k]->Fill(  bxX  );
    }
    
    if ( (24+k) == 31 ) {
      if ( gtTTWord[31] )
        std::cout << ieventX << std::endl;
    }
    
    for( int iebx=0; iebx<=2; iebx++) {
      
      const TechnicalTriggerWord ggtTTWord = gtRecord->technicalTriggerWord(iebx-1);
      
      if ( ggtTTWord[ 24+k ] )
        m_bxWindowDist[k]->Fill( bxX, iebx-1);
      
    }
    
  }

  lookatRpcRecHits( iEvent, iSetup);
    
  //
  ttVec.clear();
  
  //
  
}

void
PromptMuons::lookatRpcRecHits(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
      int blayer   = getBarrelLayer( kLayer, kStation );
      // 1 to 6                                                                                     

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
          
          if ( ttVec[k] ) {
            
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

// ------------ method called once each job just before starting event loop  ------------
void 
PromptMuons::beginJob()
{

  edm::Service<TFileService> fservice;
  
  m_bxDistEvent = fservice->make<TH1D>("Bx.Nummber.in.Event",
                                       "Bx number",
                                       4000, 0, 4000);
  

  for( int k=0; k < m_maxttBits; ++k) {
    
    std::ostringstream hname;
    
    hname.str("");
    hname << "Trigger.Bx.Distribution." << m_ttBits[k];
    
    m_bxDist[k] = fservice->make<TH1D>(hname.str().c_str(),
                                       "Bx number",
                                       4000, 0, 4000);
    
    //hname.str("");
    //hname << "Trigger.Bx.Distribution.Diff." << m_ttBits[k];
    //m_bxDiffDist[k] = fservice->make<TH1D>(hname.str().c_str(),
    //                                       "Bx number number",
    //                                       100, -10, 10);

    hname.str("");
    hname << "Trigger.Bx.Window.Distribution." << m_ttBits[k];
    
    m_bxWindowDist[k] = fservice->make<TH2D>(hname.str().c_str(),
                                             "Bx number", 4000, 0, 4000, 7, -3, 3);
    
  }

  //RPC RecHits

   //....................................................................................................................
  double max_x = 600.0;
  double max_y = 400.0;
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    //
    std::ostringstream hname;
    hname.str("");
    hname << "Track.XY.Rpc.RecHit.bit." << m_ttBits[k];
    
    m_hh_xy_rpc_rechit[k] = fservice->make<TH2D>( hname.str().c_str(), "Tracks XY Rpc RecHit", 
                                                  100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
    
    hname.str("");
    hname << "Track.YZ.Rpc.RecHit.bit." << m_ttBits[k];
    
    m_hh_yz_rpc_rechit[k] = fservice->make<TH2D>( hname.str().c_str(), "Tracks YZ Rpc RecHit", 
                                                  100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
    hname.str("");
    hname << "Rpc.Hits.Layer.bit." << m_ttBits[k];
    
    m_h_RpcHits_Layer[k]  = fservice->make<TH1D>(hname.str().c_str(),"RPC RecHits Layer", 10, 0.0, 10);
    
    hname.str("");
    hname << "Rpc.Hits.Sector.bit." << m_ttBits[k];
    
    m_h_RpcHits_Sector[k] = fservice->make<TH1D>(hname.str().c_str(),"RPC RecHits Sector", 14, 0.0, 14);
    
    hname.str("");
    hname << "Rpc.Hits.Wheel.bit." << m_ttBits[k];
    m_h_RpcHits_Wheel[k]  = fservice->make<TH1D>(hname.str().c_str(),"RPC RecHits Wheel", 7, -3, 3);
    
  }
  
  m_hh_xy_rpc_rechit_All = fservice->make<TH2D>( "Track.XY.Rpc.RecHit.All", "Tracks XY Rpc RecHit All", 
                                                 100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_hh_yz_rpc_rechit_All = fservice->make<TH2D>( "Track.YZ.Rpc.RecHit.All", "Tracks YZ Rpc RecHit All", 
                                                 100, -max_x*2, max_x*2, 100, -max_y*2, max_y*2 );
  
  m_h_RpcHits_Layer_All  = fservice->make<TH1D>("Rpc.Hits.Layer.All","RPC RecHits Layer", 10, 0.0, 10);
  
  m_h_RpcHits_Sector_All = fservice->make<TH1D>("Rpc.Hits.Sector.All","RPC RecHits Sector", 14, 0.0, 14);
  
  m_h_RpcHits_Wheel_All  = fservice->make<TH1D>("Rpc.Hits.Wheel.All","RPC RecHits Wheel", 7, -3, 3);
  
  //

  for( int k=0; k < 4; ++k) {
    std::ostringstream hname;
    hname.str("");
    hname << "Rpc.Hits.Fraction." << (k+1);
    m_h_RpcHits_FracStation[k]  = fservice->make<TH1D>(hname.str().c_str(),"RPC RecHits Fraction in Station", 100, 0.0 , 1.1);
    
  }
    
    
}

int 
PromptMuons::getBarrelLayer( const int & _layer, const int & _station )
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



// ------------ method called once each job just after ending the event loop  ------------
void 
PromptMuons::endJob() {

}

//define this as a plug-in
DEFINE_FWK_MODULE(PromptMuons);
