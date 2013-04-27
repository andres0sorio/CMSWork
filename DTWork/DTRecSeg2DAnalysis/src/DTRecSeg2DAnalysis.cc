#include "DTWork/DTRecSeg2DAnalysis/src/DTRecSeg2DAnalysis.h"

//

DTRecSeg2DAnalysis::DTRecSeg2DAnalysis(const edm::ParameterSet& iConfig)
{

  m_DTSegmentLabel = iConfig.getParameter<edm::InputTag>("DTsegmentsLabel");

  m_trackLabel = iConfig.getParameter<edm::InputTag>("TrackLabel");

  m_muonLabel = iConfig.getParameter<edm::InputTag>("MuonLabel");			

  edm::ParameterSet serviceParameters = iConfig.getParameter<edm::ParameterSet>("ServiceParameters");
  m_MuonServiceProxy = new MuonServiceProxy(serviceParameters);
  
  edm::ParameterSet matchParameters = iConfig.getParameter<edm::ParameterSet>("MatchParameters");
  m_MuonSegMatcher = new MuonSegmentMatcher(matchParameters, m_MuonServiceProxy);
  
  ///m_partLabel = iConfig.getParameter<edm::InputTag>("partLabel");
  
  ///m_hscpId = iConfig.getUntrackedParameter< std::vector<int> >("MCPartIds");
  
  m_debug = true;
  
}

DTRecSeg2DAnalysis::~DTRecSeg2DAnalysis()
{
  
  
}

//
// member functions
//

float deltaphi(float phi1, float phi2){
  float diffphi = phi1 - phi2;
  if(diffphi>3.14159265) return 2*3.1415926535-diffphi;
  else if(diffphi < -3.14159265) return 2*3.1415926535+diffphi;
  else return diffphi;
}

// ------------ method called to for each event  ------------

void DTRecSeg2DAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  unsigned int ieventX = iEvent.id().event();
  if(m_debug)   std::cout << " @Evento: " << ieventX << std::endl;

  h_statistics->Fill(1);	
  
  bool m_noTrackinfo = false;
  
  edm::Handle<reco::MuonCollection> muonCollectionHandle;
  iEvent.getByLabel(m_muonLabel, muonCollectionHandle);
  
  if ( !muonCollectionHandle.isValid() ) {
    std::cout << "DTRecSeg2DAnalysis> " << " can't find MuonCollection with label "
              << m_muonLabel << '\n';
    m_noTrackinfo = true;
  }
  
  if ( ! m_noTrackinfo  ) {
    
    reco::MuonCollection::const_iterator recoMuItr;
    
    int trackcounter = 0;
    
    for (recoMuItr = muonCollectionHandle->begin(); recoMuItr != muonCollectionHandle->end(); recoMuItr++) {
  
      //Only study the GlobalMuons from this collection
      
      h_statistics->Fill(3);
      
      if( ! (*recoMuItr).isGlobalMuon() ) continue; 
      
      h_statistics->Fill(4);

      std::cout << "DTRecSeg2DAnalysis> Get Global Track from muon" << '\n';
      
      reco::TrackRef trackItr = (*recoMuItr).globalTrack();

      std::cout << "DTRecSeg2DAnalysis> Get Inner Track from muon" << '\n';

      reco::TrackRef Tracker =(*recoMuItr).innerTrack();
      
      if ( ! Tracker.isAvailable()  )  { 
	std::cout << "DTRecSeg2DAnalysis> Get Inner Track from muon not available" << '\n';
	continue;
      }

      double p=Tracker->p();
      double p_gm =trackItr->p();
      double pt=Tracker->pt();
      double etatrack=Tracker->eta();
      double phitrack=Tracker->phi();
      double Chi2=trackItr->chi2();
      

      h_Chi2->Fill(Chi2);
      h_muonPt->Fill(pt);
      h_muonEta->Fill( etatrack );
      
      if( fabs(etatrack) < 2.1 ) h_muonInBarrel->Fill(  etatrack );

      //std::cout << " *Traza: " << trackcounter << std::endl; 
        
      // linear regression parameters PG = betta*(0.3*t0+PG0)
      int segmentcounter=0;
      double Sx, Sy, Sx2, Sy2, Sxy, ti;
      Sx = Sy = Sx2 = Sy2 = Sxy = ti = 0;
      
      m_MuonServiceProxy->update(iSetup);
      
      // get the DT segments that were used to construct the muon
      std::vector<const DTRecSegment4D*> recSegments4D = m_MuonSegMatcher->matchDT( *trackItr, iEvent);
      std::vector<const DTRecSegment4D*>::iterator rechit;
      
      for ( rechit = recSegments4D.begin(); rechit!=recSegments4D.end();++rechit) { 
        
        // use only segments with both phi and theta projections present (optional)
        bool bothProjections = ( ((*rechit)->hasPhi()) && ((*rechit)->hasZed()) );
        bool requireBothProjections = false;
        if ( requireBothProjections && !bothProjections) continue;
        
        //	double ti;
        //	ti=0;
        
        // loop over (theta, phi) segments
        for (int phi=0; phi<2; phi++) {
          
          const DTRecSegment2D* segm;
          
          if ( phi ) segm = dynamic_cast<const DTRecSegment2D*>((*rechit)->phiSegment()); 
          else segm = dynamic_cast<const DTRecSegment2D*>((*rechit)->zSegment());
          
          if(segm==0) continue;
          if (!segm->specificRecHits().size()) continue;
          
          if(phi==0) continue;
          

          //  std::cout << " *segmento: " << segmentcounter << std::endl; 
          
          // Create the Chamber Id
          DetId id = (*rechit)->geographicalId();
          DTChamberId chamberId(id.rawId());
          int station = chamberId.station();
          int sector  = chamberId.sector();
          int wheel = chamberId.wheel();
          double t0 = segm->t0();
          double chi2 = segm->chi2();
          
          bool ist0Valid = segm->ist0Valid();
          if(ist0Valid==(false)) continue;
          
          
          // Get the DT Geometry
          edm::ESHandle<DTGeometry> theDTGeom;
          iSetup.get<MuonGeometryRecord>().get(theDTGeom);
          const DTChamber* chamber = theDTGeom->chamber(id.rawId());
          
          // Get the Position and Direction (Local and Global)
          LocalPoint pos = segm->localPosition();
          LocalVector dir = segm->localDirection();
          
          GlobalVector Gdir = chamber->toGlobal(dir);
          //double PhiL = Gdir.phi();
          //double EtaL = Gdir.eta();
          
          GlobalPoint Gpos = chamber->toGlobal( pos );
          double Gx = Gpos.x();
          double Gy = Gpos.y();
          double Gz = Gpos.z();
          double PG = 0.01*(sqrt((Gx*Gx)+(Gy*Gy)+(Gz*Gz)));
          
          // Get the ToF
          double t = ((PG/0.3)+t0);
          
          // ToF incremental
          //	      if(t>=ti){
          
          //linear regression variables    
          Sy+=PG;
          Sx+=t;
          Sy2+=(PG*PG);
          Sx2+=(t*t);
          Sxy+=(PG*t);
          
          h_chi2->Fill(chi2);
          
          h_t0->Fill(t0);
          
          //ToF histograms
          if(station == 1){
            h_t0seg_st1->Fill(t0);
            h_tseg_station1->Fill(t);
            
          }
          if(station == 2){
            h_t0seg_st2->Fill(t0);
            h_tseg_station2->Fill(t);
          }
          if(station == 3){
            h_t0seg_st3->Fill(t0);
            h_tseg_station3->Fill(t);
          }
          if(station == 4){
            h_t0seg_st4->Fill(t0);
            h_tseg_station4->Fill(t);
          }
          
          if(station == 2 && sector == 1 && wheel == 0){
            h_t0seg_st2_sec1_w0->Fill(t0);
            h_tseg_st2_sec1_w0->Fill(t);
          }
	   
          //}
          
          //	      ti=t; 
          
        }
        
        ++segmentcounter;
        
      } /// Rechit 4d
      
      h_Chi2_2->Fill(Chi2);
      h_statistics->Fill(6);	
      
      double px = Tracker->momentum().x();
      double py = Tracker->momentum().y(); 	
      
      //	double pz = trackItr->momentum().z();
      
      double Pt = sqrt((px*px)+(py*py));
      double beta, gamma, m, e;
      //double diffbeta, diffp;
      
      if(segmentcounter!=0){
        
        h_statistics->Fill(7);
        
        beta=(Sxy/Sx2)/0.3;
        gamma = 1 / (sqrt(1-(beta*beta)));
        m = p / (gamma*beta);
        e = sqrt(m*m+p*p);
        
        h_beta->Fill(beta);
        h_betainv->Fill(1/beta);
        
        h_mass->Fill(m);
        h_momentum->Fill(p);
        h_momentum_global->Fill(p_gm);
        h_energy->Fill(e);
        h_momentumtrans->Fill(Pt);
        h_phi->Fill(phitrack);
        h_eta->Fill(etatrack);
        
      } // if(segment counter >= 2)
	    
      ++trackcounter;
      
    }//end Track 
   

    h_muonEvt->Fill( trackcounter );
 
  }
  
  
}//end analizer





// ------------ method called once each job just before starting event loop  ------------
void 
DTRecSeg2DAnalysis::beginJob()
{
  edm::Service<TFileService> fs;

  h_beta = fs->make<TH1D>("beta(track)","beta", 50 , -0.5 , 1.7); 
  h_betainv = fs->make<TH1D>("betainv(track)","beta-1", 50 , -0.5 , 4.5);
  h_momentum = fs->make<TH1D>("momentum","Momentum(GeV/c)", 50 , -50.0 , 2000.0);
  h_momentum_global = fs->make<TH1D>("momentum","Momentum(GeV/c)", 50 , -50.0 , 2000.0);
  h_energy = fs->make<TH1D>("energy","Energia(GeV)", 50 , -50.0 , 2000.0);
  h_momentumtrans = fs->make<TH1D>("momentum_transverso"," Pt(GeV/c)", 50 , -50.0 , 2000.0);
  h_phi = fs->make<TH1D>("phi" , "Phi" , 50 , -4.0 , 4.0 );
  h_eta = fs->make<TH1D>("eta" , "Eta" , 50 , -4.0 , 4.0 );
  h_mass = fs->make<TH1D>("mass_from_beta ","Masa (GeV/c2)", 50 , -50.0 , 1500.0);


  h_t0 = fs->make<TH1D>("t0_general","t0 in station 1", 50 , -35.0 , 70.0);
  h_t0seg_st1 = fs->make<TH1D>("t0_station_1","t0 in station 1", 50 , -35.0 , 70.0);
  h_t0seg_st2 = fs->make<TH1D>("t0_station_2","t0 in station 2", 50 , -35.0 , 70.0);
  h_t0seg_st3 = fs->make<TH1D>("t0_station_3","t0 in station 3", 50 , -35.0 , 70.0);
  h_t0seg_st4 = fs->make<TH1D>("t0_station_4","t0 in station 4", 50 , -35.0 , 70.0);
  h_t0seg_st2_sec1_w0 = fs->make<TH1D>("t0_chamber","t0 en la estacion 2, sector 1, rueda 0 ", 50 , -35.0 , 70.0);
  h_tseg_station1 = fs->make<TH1D>("ToF_station_1","t0 Segment 2D in station 1", 50 , -35.0 , 100.0);
  h_tseg_station2 = fs->make<TH1D>("ToF_station_2","t0 Segment 2D in station 2", 50 , -35.0 , 100.0);
  h_tseg_station3 = fs->make<TH1D>("ToF_station_3","t0 Segment 2D in station 3", 50 , -35.0 , 100.0);
  h_tseg_station4 = fs->make<TH1D>("ToF_station_4","t0 Segment 2D in station 4", 50 , -35.0 , 100.0);
  h_tseg_st2_sec1_w0 = fs->make<TH1D>("ToF_chamber210","t0 en la estacion 2, sector 1, rueda 0 ", 50 , -35.0 , 100.0);

  h_Chi2 = fs->make<TH1D>("chi2_track" , "chi2" , 50 , -0.5 , 200.0 );
  h_Chi2_2 = fs->make<TH1D>("chi2_track2" , "chi2" , 50 , -0.5 , 200.0 );
  h_chi2 = fs->make<TH1D>("chi2" , "chi2" , 50 , -0.5 , 100.0 );
  h_statistics = fs->make<TH1F>("statistics" , "informacion" , 50 , -0.5 , 8.0 );
    
  h_muonPt = fs->make<TH1F>("muonPt" , "Muon Pt" , 50 , 0.0 , 2000.0 );
  h_muonEta = fs->make<TH1F>("muonEta" , "Muon Eta" , 50 , -4.0 , 4.0 );
  h_muonInBarrel = fs->make<TH1F>("muonInBarrel" , "Muon in Barrel Region" , 50 , -4.0 , 4.0 );
  h_muonEvt = fs->make<TH1F>("muonEvt" , "Number of muons per event" , 50 , 0 , 10.0 );

}


void 
DTRecSeg2DAnalysis::beginRun(const edm::Run& iRun , const edm::EventSetup& iSetup ) 
{
  
  // get the DT geometry
  iSetup.get<MuonGeometryRecord>().get(m_DTGeom);  
  
}
// ------------ method called once each job just after ending the event loop  ------------
void 
DTRecSeg2DAnalysis::endJob() {
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(DTRecSeg2DAnalysis);
