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
  
  m_partLabel = iConfig.getParameter<edm::InputTag>("partLabel");
  
  m_hscpId = iConfig.getUntrackedParameter< std::vector<int> >("MCPartIds");
  
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
  //   std::cout << " @Evento: " << ieventX << std::endl;
  
  bool m_noTrackinfo = false;
  
  edm::Handle<edm::HepMCProduct> genParticles;
  iEvent.getByLabel(m_partLabel, genParticles);
  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(genParticles->GetEvent()));
  
  // loop over MC particle::::::::
  
  for(HepMC::GenEvent::particle_iterator partIt = myGenEvent->particles_begin();
      partIt != myGenEvent->particles_end(); ++partIt ){
    
    float etamc=0.0;
    float phimc=0.0;
    float betamc=0.0;
    float pmc=0.0;
    float mmc=0.0;
    float mmc_gen=0.0;
    float ptrans=0.0;
    float emc=0.0;
    float gammamc=0.0;

    int mcpartId = (*partIt)->pdg_id();

    if( abs( mcpartId ) > 100000 ) {
      if(m_debug) std::cout << "DTRecSeg2DAnalysis> mcpartID: " << mcpartId 
                            << " status= " << (*partIt)->status() << std::endl;
    }
    
    std::vector<int>::iterator idItr = m_hscpId.begin();
    
    bool foundMCpart = false;
    
    for( idItr = m_hscpId.begin(); idItr != m_hscpId.end(); ++idItr) {
      if( abs( mcpartId ) == (*idItr) ) { 
        foundMCpart = true;
        break;
      }
    }

    if( foundMCpart && (*partIt)->status() == 1)  {
      
      mmc_gen = (*partIt)->generated_mass();
      ptrans = (*partIt)->momentum().perp();
      pmc = (*partIt)->momentum().rho();
      emc = sqrt(pmc*pmc + mmc_gen*mmc_gen); 
      
      betamc = pmc / emc;
      gammamc = 1/(sqrt(1-(betamc*betamc)));
      mmc   = pmc/(betamc*gammamc);
      
      etamc = (*partIt)->momentum().eta();
      phimc = (*partIt)->momentum().phi();
      
      h_mcbeta->Fill(betamc);
      h_mceta->Fill(etamc);
      h_mcphi->Fill(phimc);
      h_mcmm->Fill(mmc_gen);
      h_mce->Fill(emc);
      h_mcmagp->Fill(pmc);
      h_mcpt->Fill(ptrans);
      
    } else {
      //if( m_debug) std::cout << "DTRecSeg2DAnalysis> " << mcpartId << " != " << m_hscpId << std::endl;
      continue;
    }
    
    ///edm::Handle<reco::TrackCollection> trackCollectionHandle;
    ///iEvent.getByLabel(m_trackLabel, trackCollectionHandle);

    edm::Handle<reco::MuonCollection> muonCollectionHandle;
    iEvent.getByLabel(m_muonLabel, muonCollectionHandle);
    
    ///if ( !trackCollectionHandle.isValid() ) {
    ///  std::cout << "DTRecSeg2DAnalysis> " << " can't find TrackCollection with label "
    //            << m_trackLabel << '\n';
    ///  m_noTrackinfo = true;
    ///}

    if ( !muonCollectionHandle.isValid() ) {
      std::cout << "DTRecSeg2DAnalysis> " << " can't find MuonCollection with label "
                << m_muonLabel << '\n';
      m_noTrackinfo = true;
    }
    
    
    if ( ! m_noTrackinfo  ) {
      
      //reco::TrackCollection::const_iterator trackItr;
      
      reco::MuonCollection::const_iterator recoMuItr;
      
      int trackcounter = 1;
      float dR;
      dR=9999999999;
      
      //for (trackItr = trackCollectionHandle->begin(); trackItr != trackCollectionHandle->end(); trackItr++) {
      
      for (recoMuItr = muonCollectionHandle->begin(); recoMuItr != muonCollectionHandle->end(); recoMuItr++) {
        
        //Only study the GlobalMuons from this collection

        if( ! (*recoMuItr).isGlobalMuon() ) continue; 
        
        
        reco::TrackRef trackItr = (*recoMuItr).globalTrack();
        
        double etatrack=trackItr->eta();
        double phitrack=trackItr->phi();
        double p =trackItr->p();
        
        float Diffeta = etamc-etatrack;
        float Diffphi = deltaphi(phimc, phitrack);
        //	float Diffp = pmc - p;
        
        dR = sqrt(Diffeta*Diffeta + Diffphi*Diffphi);
        
        //match entre MC part y part reco
        if(dR>=0.1) continue;
        
        //	std::cout << " *Traza: " << trackcounter << std::endl; 
        
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
            double PhiL = Gdir.phi();
            double EtaL = Gdir.eta();

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

	   
            //}
	    
            //	      ti=t; 
	    
          }
 	  
          ++segmentcounter;
	  
        } /// Rechit 4d

	
        double px = trackItr->momentum().x();
        double py = trackItr->momentum().y();  
        //	double pz = trackItr->momentum().z();
	
        double Pt = sqrt((px*px)+(py*py));
        //	double P = sqrt((px*px)+(py*py)+(pz*pz));
  
        double beta, gamma, m, e;
        double diffbeta, diffp;
	  
        if(segmentcounter!=0){
	  
          beta=(Sxy/Sx2)/0.3;
          gamma = 1 / (sqrt(1-(beta*beta)));
          m = p / (gamma*beta);
          e = sqrt(m*m+p*p);

          diffbeta = betamc-beta;
          diffp = pmc-p;
	  
          h_beta->Fill(beta);
          h_mass->Fill(m);
          h_momentum->Fill(p);
          h_energy->Fill(e);
          h_momentumtrans->Fill(Pt);
          h_phi->Fill(phitrack);
          h_eta->Fill(etatrack);
	    
          //ressiduals histograms
          h_diffbeta->Fill(diffbeta);
          h_diffp->Fill(diffp);
          h_diffeta->Fill(Diffeta);
          h_diffphi->Fill(Diffphi);
	  
          if(beta>=1.0){
	      
            h_beta_beta->Fill(beta);
            h_momentum_beta->Fill(p);
            h_momentumtrans_beta->Fill(Pt);
            h_phi_beta->Fill(phitrack);
            h_eta_beta->Fill(etatrack);
            h_diffbeta_beta->Fill(diffbeta);
            h_diffp_beta->Fill(diffp);
            h_diffeta_beta->Fill(Diffeta);
            h_diffphi_beta->Fill(Diffphi);

            std::cout << " @Evento: " << ieventX << std::endl;
            std::cout << " Tr " << trackcounter << " MC, part @ beta : " << betamc << " - " << beta << " = " << diffbeta
                      << " p : " << pmc << " - " << p << " = " << diffp << std::endl;

            std::cout << " MC, part @ phi : " << phimc << " - "  << phitrack << " = " << Diffphi
                      << " @ eta : " << etamc << " - " << etatrack << " = " << Diffeta << std::endl;
	  
          }
	    
	    
        } // if(segment counter >= 2)
	    
        ++trackcounter;
	
      }//end Track 
	
    }
    
  }//end MCPart

}//end analizer





// ------------ method called once each job just before starting event loop  ------------
void 
DTRecSeg2DAnalysis::beginJob()
{
  edm::Service<TFileService> fs;

  h_beta = fs->make<TH1D>("beta(track)","beta", 50 , -0.5 , 1.7); 
  h_momentum = fs->make<TH1D>("momentum","p(GeV/c)", 50 , -50.0 , 1000.0);
  h_energy = fs->make<TH1D>("energy","E(GeV)", 50 , -50.0 , 1000.0);
  h_momentumtrans = fs->make<TH1D>("momentum_transverso"," Pt(GeV/c)", 50 , -50.0 , 1000.0);
  h_phi = fs->make<TH1D>("phi" , "phi" , 50 , -4.0 , 4.0 );
  h_eta = fs->make<TH1D>("eta" , "eta" , 50 , -4.0 , 4.0 );

  h_beta_beta = fs->make<TH1D>("beta_beta(track)","beta>=1.2", 50 , -0.5 , 1.7); 
  h_momentum_beta = fs->make<TH1D>("momentum_beta","p(GeV/c),beta>=1.2", 50 , -50.0 , 1000.0);
  h_momentumtrans_beta = fs->make<TH1D>("momentumtrans_beta"," Pt(GeV/c),beta>=1.2", 50 , -50.0 , 1000.0);
  h_phi_beta = fs->make<TH1D>("phi_beta" , "phi,beta>=1.2" , 50 , -4.0 , 4.0 );
  h_eta_beta = fs->make<TH1D>("eta_beta" , "eta,beta>=1.2" , 50 , -4.0 , 4.0 );

  h_mass = fs->make<TH1D>("mass_from_beta ","mass (GeV/c2)", 50 , -50.0 , 1000.0);
 
  h_t0seg_st1 = fs->make<TH1D>("t0_station 1","t0 in station 1", 50 , -35.0 , 35.0);
  h_t0seg_st2 = fs->make<TH1D>("t0_station 2","t0 in station 2", 50 , -35.0 , 35.0);
  h_t0seg_st3 = fs->make<TH1D>("t0_station 3","t0 in station 3", 50 , -35.0 , 35.0);
  h_t0seg_st4 = fs->make<TH1D>("t0_station 4","t0 in station 4", 50 , -35.0 , 35.0);
  h_tseg_station1 = fs->make<TH1D>("ToF_station 1","t0 Segment 2D in station 1", 50 , -35.0 , 35.0);
  h_tseg_station2 = fs->make<TH1D>("ToF_station 2","t0 Segment 2D in station 2", 50 , -35.0 , 35.0);
  h_tseg_station3 = fs->make<TH1D>("ToF_station 3","t0 Segment 2D in station 3", 50 , -35.0 , 35.0);
  h_tseg_station4 = fs->make<TH1D>("ToF_station 4","t0 Segment 2D in station 4", 50 , -35.0 , 35.0);

  h_chi2 = fs->make<TH1D>("chi2" , "chi2" , 50 , -0.5 , 70.0 );

  h_mcbeta = fs->make<TH1F>("MCbeta" , "Beta from MC" , 50 , -0.5 , 1.5 );
  h_mceta = fs->make<TH1F>("MCeta" , "Eta from MC" , 50 , -6.0 , 6.0 );
  h_mcphi = fs->make<TH1F>("MCphi" , "Phi from MC" , 50 , -4.0 , 4.0 );
  h_mcpt = fs->make<TH1F>("MCmomentotransverso" , "Pt from MC" , 50 , 0.0 , 600.0 );
  h_mcmm = fs->make<TH1F>("MCmasa" , "M from MC" , 50 , -50.0 , 1000.0 );
  h_mcmagp = fs->make<TH1F>("MCmomento" , "Momentum from MC" , 50 , -50.0 , 1000.0 );
  h_mce = fs->make<TH1F>("MCenergy" , "Energy from MC" , 50 , -50.0 , 1000.0 );

  h_diffbeta = fs->make<TH1F>("beta_ressidual" , "Beta Ress" , 50 , -0.5 , 0.5 );
  h_diffphi = fs->make<TH1F>("phi_ressidual" , "Phi Ress" , 50 , -1.0 , 1.0 );
  h_diffp = fs->make<TH1F>("p_ressidual" , "p Ress" , 50 ,-100.0 , 100.0 );
  h_diffeta = fs->make<TH1F>("Eta_Ressidual" , "Eta residual" , 50 , -1.0 , 1.0 );
  h_diffbeta_beta = fs->make<TH1F>("beta_ressidual" , "Beta Ress" , 50 , -0.5 , 0.5 );
  h_diffphi_beta = fs->make<TH1F>("phi_ressidual" , "Phi Ress" , 50 , -1.0 , 1.0 );
  h_diffp_beta = fs->make<TH1F>("p_ressidual" , "p Ress" , 50 ,-100.0 , 100.0 );
  h_diffeta_beta = fs->make<TH1F>("Eta_Ressidual" , "Eta residual" , 50 , -1.0 , 1.0 );


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
