//

#include "DTWork/MCHSCPAnalysis/src/MCHSCPAnalysis.h"

MCHSCPAnalysis::MCHSCPAnalysis(const edm::ParameterSet& iConfig)
{
  
  m_mcpartLabel = iConfig.getParameter<edm::InputTag>("MCPartLabel");
  m_hscpId = iConfig.getUntrackedParameter<int>("HSCPId");
  
}

MCHSCPAnalysis::~MCHSCPAnalysis()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


void
MCHSCPAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  edm::Handle<edm::HepMCProduct> genParticles;
  iEvent.getByLabel(m_mcpartLabel, genParticles);

  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(genParticles->GetEvent()));
  
  //loop over MC particles::::::::
  
  for(HepMC::GenEvent::particle_iterator partIt = myGenEvent->particles_begin();
      partIt != myGenEvent->particles_end(); ++partIt ) {
    
    float etamc=0.0;
    float phimc=0.0;
    float betamc=0.0;
    float pmc=0.0;
    float mmc=0.0;
    float ptrans=0.0;
    float emc=0.0;

    if( abs( (*partIt)->pdg_id() ) == m_hscpId && (*partIt)->status() == 1)  {
      
      mmc = (*partIt)->generated_mass();
      ptrans = (*partIt)->momentum().perp();
      pmc = (*partIt)->momentum().rho();
      
      emc = sqrt ( (*partIt)->momentum().rho()*(*partIt)->momentum().rho() 
		   + (*partIt)->generated_mass()* (*partIt)->generated_mass() );
      
      betamc = pmc / emc;
      
      etamc = (*partIt)->momentum().eta();
      
      phimc = (*partIt)->momentum().phi();
      
      std::cout << mmc << '\t' << ptrans << '\t' << pmc << '\t' << emc << '\t'
		<< betamc << '\t' << etamc << '\t' << phimc << '\n';

      h_mcbeta->Fill(betamc);
      h_mceta->Fill(etamc);
      h_mcphi->Fill(phimc);
      h_mcpt->Fill(ptrans);
      h_mcmm->Fill(mmc);
      h_mce->Fill(emc);
      h_mcmagp->Fill(pmc);
    }
    
  }
    
}


// ------------ method called once each job just before starting event loop  ------------
void 
MCHSCPAnalysis::beginJob()
{

  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  
  ///Definicion de los histogramas
  
  h_mcbeta = fs->make<TH1F>("MCbeta" , "Beta from MC" , 50 , 0.0 , 1.0 );
  h_mceta = fs->make<TH1F>("MCeta" , "Eta from MC" , 50 , -6.0 , 6.0 );
  h_mcphi = fs->make<TH1F>("MCphi" , "Phi from MC" , 50 , -4.0 , 4.0 );
  h_mcpt = fs->make<TH1F>("MCmomentotransverso" , "Pt from MC" , 50 , 0.0 , 600.0 );
  h_mcmm = fs->make<TH1F>("MCmasa" , "M from MC" , 50 , 0.0 , 500.0 );
  h_mce = fs->make<TH1F>("MCenergia" , "Energy from MC" , 50 , 0.0 , 1000.0 );
  h_mcmagp = fs->make<TH1F>("MCmomento" , "Momentum from MC" , 50 , 0.0 , 1000.0 );

}

// ------------ method called once each job just after ending the event loop  ------------
void 
MCHSCPAnalysis::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCHSCPAnalysis);
