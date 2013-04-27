#include "DoubleMuons.h"

//

DoubleMuons::DoubleMuons(const edm::ParameterSet& iConfig)

{

  m_trackLabel = iConfig.getParameter<edm::InputTag>("TrackLabel");
  m_muonLabel = iConfig.getParameter<edm::InputTag>("MuonLabel");	
  m_debug = true;
  
}


DoubleMuons::~DoubleMuons()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
  m_outfile->Write();
  m_outfile->Close();


}


//
// member functions
//

// ------------ method called for each event  ------------
void
DoubleMuons::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  unsigned int ieventX = iEvent.id().event();
  if(m_debug)   std::cout << " @Evento: " << ieventX << std::endl;
  
  edm::Handle<reco::MuonCollection> muonCollectionHandle;
  iEvent.getByLabel(m_muonLabel, muonCollectionHandle);
  
  if ( muonCollectionHandle.isValid() ) {
    
    reco::MuonCollection::const_iterator recoMuItr;
    
    int iMu = 0;
    
    for (recoMuItr = muonCollectionHandle->begin(); recoMuItr != muonCollectionHandle->end(); recoMuItr++) {
      
      //Only study the GlobalMuons from this collection
      
      if( ! (*recoMuItr).isGlobalMuon() ) continue; 
      
      muons_fPx[iMu]  = (*recoMuItr).px();
      muons_fPy[iMu]  = (*recoMuItr).py();
      muons_fPz[iMu]  = (*recoMuItr).pz();
      muons_fE[iMu]   = (*recoMuItr).energy();
      muons_fC[iMu]   = (*recoMuItr).charge();
      muons_fEta[iMu] = (*recoMuItr).eta();

      ++iMu;
      
    }
    
    h_nMuons->Fill(iMu);
    
    nmuons = iMu;
    
    if ( nmuons >= 2 && nmuons < 5)
      m_tree->Fill();
    
  } else {
    
    std::cout << "Cannot find collection with name " << m_muonLabel << std::endl;
        
  }
  
  
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
DoubleMuons::beginJob()
{

  edm::Service<TFileService> fs;
  
  h_nMuons = fs->make<TH1F>("nMuons" , "GL Muons per event" , 5 , 0.0 , 5.0 );
  h_MuonsInv = fs->make<TH1F>("muonsInv" , "Dimuons invariant mass" , 40 , 60 , 100 ); 


  m_outfile = new TFile("ntupler_output.root","RECREATE");
  
  m_outfile->cd();
  
  m_tree = new TTree("t1","Real data root-tuple");

  //adicionar una rama por variable  
  m_tree->Branch("nMuons", &nmuons ,"nMuons/I");
  m_tree->Branch("muons_fPx"  , muons_fPx  ,"muons_fPx[5]/F");
  m_tree->Branch("muons_fPy"  , muons_fPy  ,"muons_fPy[5]/F");
  m_tree->Branch("muons_fPz"  , muons_fPz  ,"muons_fPz[5]/F");
  m_tree->Branch("muons_fE"   , muons_fE   ,"muons_fE[5]/F");
  m_tree->Branch("muons_fC"   , muons_fC   ,"muons_fC[5]/F");
  m_tree->Branch("muons_fEta" , muons_fEta ,"muons_fEta[5]/F");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
DoubleMuons::endJob() 
{

  //m_outfile->Write();
  //m_outfile->Close();
  
}

// ------------ method called when starting to processes a run  ------------
void 
DoubleMuons::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
DoubleMuons::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
DoubleMuons::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
DoubleMuons::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DoubleMuons::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DoubleMuons);
