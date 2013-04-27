#define L12015Analysis_cxx

#include "L12015Analysis.h"


void L12015Analysis::Loop()
{
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();

  nentries = 10000;

  Long64_t nbytes = 0, nb = 0;
  
  m_l1treeEG = new L1RateTree();
  m_upgradetreeEG = new UCTRateTree();

  m_l1treeEGIso = new L1RateTree();
  m_upgradetreeEGIso = new UCTRateTree();

  m_l1treeTau = new L1RateTree();
  m_upgradetreeTau = new UCTRateTree();

  m_l1treeIsoTau = new L1RateTree();
  m_upgradetreeIsoTau = new UCTRateTree();

  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //Ok! So back in business - however we need to get back to Ntuples - This can be changed in future
    
    //EG objects
    m_l1treeEG->Clear();
    m_upgradetreeEG->Clear();

    //Iso EG objects
    m_l1treeEGIso->Clear();
    m_upgradetreeEGIso->Clear();

    //Taus objects
    m_l1treeTau->Clear();
    m_upgradetreeTau->Clear();

    //Iso Taus objects
    m_l1treeIsoTau->Clear();
    m_upgradetreeIsoTau->Clear();
    
    //l1extra_
    
    for( unsigned int k=0; k < l1extra_->nNonIsoEm; ++k ) { 
      m_l1treeEG->pt->push_back(l1extra_->nonIsoEmEt[k]);
      m_l1treeEG->eta->push_back(l1extra_->nonIsoEmEta[k]);
      m_l1treeEG->phi->push_back(l1extra_->nonIsoEmPhi[k]);
    }
    
    for( unsigned int k=0; k < l1extra_->nIsoEm; ++k ) { 
      m_l1treeEGIso->pt->push_back(l1extra_->isoEmEt[k]);
      m_l1treeEGIso->eta->push_back(l1extra_->isoEmEta[k]);
      m_l1treeEGIso->phi->push_back(l1extra_->isoEmPhi[k]);
    }
    
    for( unsigned int k=0; k < l1extra_->nTauJets; ++k ) { 
      m_l1treeTau->pt->push_back(l1extra_->tauJetEt[k]);
      m_l1treeTau->eta->push_back(l1extra_->tauJetEta[k]);
      m_l1treeTau->phi->push_back(l1extra_->tauJetPhi[k]);
    }
    
    //Non Tau isolation in Current L1
    for( unsigned int k=0; k < l1extra_->nTauJets; ++k ) { 
      m_l1treeIsoTau->pt->push_back(l1extra_->tauJetEt[k]);
      m_l1treeIsoTau->eta->push_back(l1extra_->tauJetEta[k]);
      m_l1treeIsoTau->phi->push_back(l1extra_->tauJetPhi[k]);
    }
    
    m_l1treeEG->run = 1.0;
    m_l1treeEG->lumi = 1.0;
    m_l1treeEG->evt = 1.0;

    m_l1treeEGIso->run = 1.0;
    m_l1treeEGIso->lumi = 1.0;
    m_l1treeEGIso->evt = 1.0;
    
    m_l1treeTau->run = 1.0;
    m_l1treeTau->lumi = 1.0;
    m_l1treeTau->evt = 1.0;

    m_l1treeIsoTau->run = 1.0;
    m_l1treeIsoTau->lumi = 1.0;
    m_l1treeIsoTau->evt = 1.0;
    
    //l1upgrade_
    
    for( unsigned int k=0; k < l1upgrade_->nEG; ++k ) { 
      m_upgradetreeEG->pt->push_back(l1upgrade_->egEt[k]);
      m_upgradetreeEG->eta->push_back(l1upgrade_->egEta[k]);
      m_upgradetreeEG->phi->push_back(l1upgrade_->egPhi[k]);

    }

    for( unsigned int k=0; k < l1upgrade_->nIsoEG; ++k ) { 
      m_upgradetreeEGIso->pt->push_back(l1upgrade_->isoEGEt[k]);
      m_upgradetreeEGIso->eta->push_back(l1upgrade_->isoEGEta[k]);
      m_upgradetreeEGIso->phi->push_back(l1upgrade_->isoEGPhi[k]);

    }

    for( unsigned int k=0; k < l1upgrade_->nTau; ++k ) { 
      m_upgradetreeTau->pt->push_back(l1upgrade_->tauEt[k]);
      m_upgradetreeTau->eta->push_back(l1upgrade_->tauEta[k]);
      m_upgradetreeTau->phi->push_back(l1upgrade_->tauPhi[k]);

    }

    for( unsigned int k=0; k < l1upgrade_->nIsoTau; ++k ) { 
      m_upgradetreeIsoTau->pt->push_back(l1upgrade_->isoTauEt[k]);
      m_upgradetreeIsoTau->eta->push_back(l1upgrade_->isoTauEta[k]);
      m_upgradetreeIsoTau->phi->push_back(l1upgrade_->isoTauPhi[k]);

    }
    
    m_upgradetreeEG->run = 1.0;
    m_upgradetreeEG->lumi = 1.0;
    m_upgradetreeEG->evt = 1.0;
    
    m_upgradetreeEGIso->run = 1.0;
    m_upgradetreeEGIso->lumi = 1.0;
    m_upgradetreeEGIso->evt = 1.0;
    
    m_upgradetreeTau->run = 1.0;
    m_upgradetreeTau->lumi = 1.0;
    m_upgradetreeTau->evt = 1.0;
    
    m_upgradetreeIsoTau->run = 1.0;
    m_upgradetreeIsoTau->lumi = 1.0;
    m_upgradetreeIsoTau->evt = 1.0;
    
    //Fill the l1tree & l1uct
    m_l1treeEG->fChain->Fill();
    m_upgradetreeEG->fChain->Fill();
    
    m_l1treeEGIso->fChain->Fill();
    m_upgradetreeEGIso->fChain->Fill();
    
    m_l1treeTau->fChain->Fill();
    m_upgradetreeTau->fChain->Fill();
    
    m_l1treeIsoTau->fChain->Fill();
    m_upgradetreeIsoTau->fChain->Fill();
    
  }
  
  std::cout << " L12015Analysis::Loop> done! " << std::endl;
  
  
}

//EG
void L12015Analysis::RunL1RateEG( const char * var, const char * selec, const char * Xbinning, const char *name) {
  
  m_l1treeEG->Loop( var, selec, Xbinning, name );
  
}

void L12015Analysis::RunUCTRateEG( const char * var, const char * selec, const char * Xbinning, const char *name) {

  m_upgradetreeEG->Loop( var, selec, Xbinning, name );

}

//Iso EG
void L12015Analysis::RunL1RateEGIso( const char * var, const char * selec, const char * Xbinning, const char *name) {
  
  m_l1treeEGIso->Loop( var, selec, Xbinning, name );
  
}

void L12015Analysis::RunUCTRateEGIso( const char * var, const char * selec, const char * Xbinning, const char *name) {

  m_upgradetreeEGIso->Loop( var, selec, Xbinning, name );

}

// Tau
void L12015Analysis::RunL1RateTau( const char * var, const char * selec, const char * Xbinning, const char *name) {
  
  m_l1treeTau->Loop( var, selec, Xbinning, name );
  
}

void L12015Analysis::RunUCTRateTau( const char * var, const char * selec, const char * Xbinning, const char *name) {

  m_upgradetreeTau->Loop( var, selec, Xbinning, name );

}

//Iso Tau

void L12015Analysis::RunL1RateIsoTau( const char * var, const char * selec, const char * Xbinning, const char *name) {
  
  m_l1treeIsoTau->Loop( var, selec, Xbinning, name );
  
}

void L12015Analysis::RunUCTRateIsoTau( const char * var, const char * selec, const char * Xbinning, const char *name) {

  m_upgradetreeIsoTau->Loop( var, selec, Xbinning, name );

}

