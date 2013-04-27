// -*- C++ -*-
//
// Package:    PATCosmicStudy
// Class:      PATCosmicStudy
// 
/**\class PATCosmicStudy PATCosmicStudy.cc StudyL1Trigger/PATCosmicStudy/src/PATCosmicStudy.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Tue Sep  8 22:52:40 CEST 2009
// $Id$
//
//
#include "StudyL1Trigger/PATCosmicStudy/src/PATCosmicStudy.h"


PATCosmicStudy::PATCosmicStudy(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  
  m_muonLabel          = iConfig.getParameter<edm::InputTag>("MuonLabel");
  m_jetsLabel          = iConfig.getParameter<edm::InputTag>("JetsLabel");

  m_rpcDigiLabel       = iConfig.getParameter<edm::InputTag>("RPCDigiLabel");
  m_gtReadoutLabel     = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_gmtReadoutLabel    = iConfig.getParameter<edm::InputTag>("GMTReadoutRcd");
  m_ttBits             = iConfig.getParameter< std::vector<unsigned> >("BitNumbers");

  m_maxttBits = 7;
  
}


PATCosmicStudy::~PATCosmicStudy()
{


}

void PATCosmicStudy::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // get muon collection
  edm::Handle<edm::View<pat::Muon> > patHandle;
  iEvent.getByLabel( m_muonLabel , patHandle);

  edm::Handle<edm::View<pat::Jet> > jetsHandle;
  iEvent.getByLabel( m_jetsLabel , jetsHandle);
  
  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( m_gtReadoutLabel, gtRecord);
  
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
    
    //if( !(muon::isGoodMuon( (*muon), pat::Muon::GlobalMuonPromptTight)) )
    //  continue;
    //float MuonIso = ((*iter1).ecalIso() + (*iter1).hcalIso() + (*iter1).trackIso())/(*iter1).pt();
    //MuonIsoBC->Fill(MuonIso);
    
    if(muon->isStandAloneMuon())
      if(muon->isGlobalMuon())
        if(muon->isTrackerMuon()) MuonType->Fill(1);  // STA + GLB + TM
        else MuonType->Fill(2); // STA + GLB
      else 
        if(muon->isTrackerMuon()) MuonType->Fill(3);  // STA + TM
        else MuonType->Fill(5); // STA
    else
      if(muon->isTrackerMuon()) MuonType->Fill(4);    // TM
    
    if ( ! muon->standAloneMuon() )
      continue;
    
    float Muond0_STA =  muon->standAloneMuon()->d0() 
      - x0*sin( muon->standAloneMuon()->phi() ) 
      - y0*cos( muon->standAloneMuon()->phi() );
    
    float Muondsz_STA = muon->standAloneMuon()->dsz();
    
    float Muond0_GBL = 0.0;
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
    }
    
    const TechnicalTriggerWord tWord = gtRecord->technicalTriggerWord(); //size=64

    std::vector<unsigned>::iterator bitsItr;
    int k = 0;
    
    bool wasEventTriggered(false);
    
    for ( bitsItr = m_ttBits.begin(); bitsItr != m_ttBits.end(); ++bitsItr ) {
      
      wasEventTriggered = tWord.at( (*bitsItr) );
      
      if ( wasEventTriggered ) {
        
        m_HMuonPt[k]->Fill( muon->pt() );
        m_HMuonEta[k]->Fill( muon->eta() );
        m_HMuonPhi[k]->Fill( muon->phi() );
        m_HMuond0dist[k]->Fill( Muond0_STA );
        m_HMuondszdist[k]->Fill( Muondsz_STA );
        m_HMuond0dist_GBL[k]->Fill( Muond0_GBL );
        m_HMuondszdist_GBL[k]->Fill( Muondsz_GBL );

      }
      
      ++k;
      
    }
    
  }
  
  NumberMuonsEvt->Fill( num_Mu );

  //... Jets
  
  if ( ! jetsHandle.isValid() ) {
    std::cout << "PATCosmicStudy::analyze> there is a problem with the jets Handle"  << std::endl;
    return;
  }

  int num_jets = 0;
  
  for ( edm::View<pat::Jet>::const_iterator jet = jetsHandle->begin();  jet != jetsHandle->end(); ++jet) {
    ++num_jets;

    JetsEtaPhi->Fill ( jet->eta(), jet->phi() );
    JetsEtaPt->Fill ( jet->eta(), jet->pt() );
        
  }
  
  NumberJetsEvt->Fill( num_jets );
  
  
}


// ------------ method called once each job just before starting event loop  ------------
void PATCosmicStudy::beginJob()
{
  
  edm::Service<TFileService> fservice;
  
  //MuonIso = fservice->make<TH1F>("MuonIsoBC","Muon Isolation before muon cuts",30,0.0,30.0);
  
  NumberMuonsEvt = fservice->make<TH1D>("NumberMuonsEvt","Number of muons per event", 15, 0.0, 15.0);
  MuonPt         = fservice->make<TH1D>("MuonPt","Muon Pt", 120,0.0,100.0);
  MuonEta        = fservice->make<TH1D>("MuonEta","Muon Eta", 60, -5.0, 5.0);
  MuonEtaPhi     = fservice->make<TH2D>("Muon.Eta.Phi","Muon Eta vs Phi", 60, -5.0, 5.0, 60, -4.0, 4.0 );
  MuonEtaPhi_GBL = fservice->make<TH2D>("Muon.Eta.Phi.GBL","Muon Eta vs Phi of GL", 60, -5.0, 5.0, 60, -4.0, 4.0 );
  MuonPhi        = fservice->make<TH1D>("MuonPhi","Muon Phi", 60,  -4.0, 4.0);
  MuonChi2DoF    = fservice->make<TH1D>("MuonChi2DoF","Muon Track Chi2/DoF",120,0.0,12.0);
  
  MuonType       = fservice->make<TH1D>("MuonType","Muon Type", 7, 0.0, 7.0);
  
  NumberJetsEvt  = fservice->make<TH1D>("NumberJetsEvt","Number of jets per event", 20, 0.0, 20.0);
  JetsEtaPhi     = fservice->make<TH2D>("Jets.Eta.Phi","Jets Eta vs Phi", 60, -5.0, 5.0, 60, -4.0, 4.0 );
  JetsEtaPt      = fservice->make<TH2D>("Jets.Eta.Pt","Jets Eta vs Pt", 60, -5.0, 5.0, 100, 0.0, 100.0 );
  

  Muond0dist_STA     = fservice->make<TH1D>("Muond0.sta","Muon d0", 200, -1000.0 , 1000.0);
  Muondszdist_STA    = fservice->make<TH1D>("Muondsz.sta","Muon dsz", 200, -1000.0 , 1000.0);
  Muond0dist_GBL     = fservice->make<TH1D>("Muond0.gbl","Muon d0", 200, -1000.0 , 1000.0);
  Muondszdist_GBL    = fservice->make<TH1D>("Muondsz.gbl","Muon dsz", 200, -1000.0 , 1000.0);

  //.....
  
  for( int k=0; k < m_maxttBits; ++k) {
    
    std::ostringstream hname;
    
    hname << "Muon.Pt." << m_ttBits[k];
    std::cout << hname.str() << std::endl;
    
    
    m_HMuonPt[k]   = fservice->make<TH1D>( hname.str().c_str(),
                                           "Muon Pt",
                                           120,0.0,100.0);
    
    hname.str("");
    
    hname << "Muon.Eta." << m_ttBits[k];
    
    m_HMuonEta[k] = fservice->make<TH1D>( hname.str().c_str(),
                                          "Muon Eta",
                                          60, -5.0, 5.0);
    
    hname.str("");
    
    hname << "Muon.Phi." << m_ttBits[k];

    m_HMuonPhi[k] = fservice->make<TH1D>( hname.str().c_str(),
                                          "Muon Phi",
                                           60,  -4.0, 4.0);
    
    hname.str("");
    
    hname << "Muon.d0." << m_ttBits[k];
    
    m_HMuond0dist[k] = fservice->make<TH1D>( hname.str().c_str(),
                                          "Muon d0", 200, -1000.0 , 1000.0);
    
    hname.str("");
    
    hname << "Muon.dsz." << m_ttBits[k];
    
    m_HMuondszdist[k] = fservice->make<TH1D>( hname.str().c_str(),
                                              "Muon dsz", 200, -1000.0 , 1000.0);
    
    hname.str("");

    hname << "Muon.d0.GBL." << m_ttBits[k];
    
    m_HMuond0dist_GBL[k] = fservice->make<TH1D>( hname.str().c_str(),
                                             "Muon d0 GBL", 200, -1000.0 , 1000.0);
    
    hname.str("");
    
    hname << "Muon.dsz.GBL." << m_ttBits[k];
    
    m_HMuondszdist_GBL[k] = fservice->make<TH1D>( hname.str().c_str(),
                                                  "Muon dsz GBL", 200, -1000.0 , 1000.0);

    hname.str("");

    
  }
  
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PATCosmicStudy::endJob() {
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(PATCosmicStudy);
