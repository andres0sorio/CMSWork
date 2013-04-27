#define PythiaAnalysis_cxx

#include "PythiaAnalysis.h"

void PythiaAnalysis::Loop( Long64_t ievent )
{
  
  if (fChain == 0) return;
  
  //std::cout << "ievent " << ievent << std::endl;
  
  Long64_t nentries = fChain->GetEntriesFast();//Numero de eventos (pueden haber unos eventos fallidos dentro del total)
  Long64_t nbytes = 0, nb = 0;

  // Empieza loop sobre eventos  

  Long64_t firstEvt(0);
  Long64_t lastEvt(0);

  Double_t PtCut = 0.0; //15.0
  Double_t EtaCut = 3.0;
  
  m_debug = false;
  
  if ( ievent < 0 ) {
    firstEvt  = 0;
    lastEvt = nentries;
  } else {
    firstEvt = ievent;
    lastEvt = ievent+1;
  }
  
  for (Long64_t jentry = firstEvt; jentry < lastEvt; jentry++) {  ////////////////////Loop eventos
    
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;//Loop

    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //Implementar aqui el analisis
    int maxpart = particles_; 

    if( m_debug ) std::cout << "ievent: " << jentry << " " << ientry << " " << nb << " " << maxpart << std::endl;
    
    
    for (int i = 0; i < maxpart; ++i ) //Loop sobre particulas 
    { 
      
      //creamos un objeto TParticle con la informacion del TTree
      
      TParticle *p1 = new TParticle ( particles_fPdgCode[i], 
                                      particles_fStatusCode[i],
                                      particles_fMother[i][0],
                                      particles_fMother[i][1],
                                      particles_fDaughter[i][0],
                                      particles_fDaughter[i][1],
                                      particles_fPx[i],
                                      particles_fPy[i],
                                      particles_fPz[i],
                                      particles_fE [i],
                                      particles_fVx[i],
                                      particles_fVy[i],
                                      particles_fVz[i],
                                      particles_fVt[i] );
      
      double pfpt = p1->Pt();
      double pfeta = p1->Eta();
            
      //Any stable particle different from Neutrino
      if ( ((particles_fDaughter[i][0] == -1) && (particles_fDaughter[i][1] == -1)) 
           && ( (abs(particles_fPdgCode[i])!=12) && (abs(particles_fPdgCode[i])!=14) && (abs(particles_fPdgCode[i])!=16) 
                && (abs(particles_fPdgCode[i])!=1000022) ) 
           && (  pfpt >= PtCut ) && ( abs(pfeta) < EtaCut) ) {
        
        v_FinalState->Add(p1);
        
      }
      
      //Neutrinos
      else if ((particles_fDaughter[i][0] == -1) && (particles_fDaughter[i][1] == -1)
               && ( ( abs(particles_fPdgCode[i]) == 12) 
                    || (abs(particles_fPdgCode[i]) == 14) 
                    || (abs(particles_fPdgCode[i]) == 16) ) ) {
        v_Neutrinos->Add(p1);
        
      }
      
      //Neutralinos
      else if ((particles_fDaughter[i][0] == -1) && (particles_fDaughter[i][1] == -1) 
               && (abs(particles_fPdgCode[i]) == 1000022) ) {
        v_Neutralinos->Add(p1);
      }
	
      //Initial State Particles
      else if( abs(particles_fPdgCode[i]) == m_InitialStatePDG
               && (particles_fMother[i][0] != particles_fMother[i][1] ) ) {
        
        if ( m_debug ) std::cout << "Found susy particle = " << particles_fPdgCode[i] << " " 
                                 << particles_fMother[i][0] << " " << particles_fMother[i][1]
                                 << std::endl;
        
        if( particles_fMother[i][1] != -1 ) {
          
          if ( m_debug ) std::cout << "Found susy particle = " << particles_fPdgCode[i] << " " 
                                   << particles_fMother[i][0] << " " << particles_fMother[i][1]
                                   << std::endl;
          v_InitialState->Add(p1);
        }
        
        
      } else delete p1;
      
    } //Loop de particulas
    
    /////Graficas de control sobre particulas
    
    
    int max_fstates = v_FinalState->GetSize();
    int max_istates = v_InitialState->GetSize();
    int max_lsps    = v_Neutralinos->GetSize();
    
    histos->h_stats->Fill( 1, max_istates );
    histos->h_stats->Fill( 2, max_lsps );
    
    histos->h_partMultip->Fill(max_fstates);
    
    for( int k = 0; k < max_fstates; ++k) {
      
      TParticle * pf = ((TParticle*)v_FinalState->At(k));
      histos->h_fstate_eta->Fill( pf->Eta() );
      histos->h_fstate_pt->Fill( pf->Pt() );
      
    }
    
    
    for( int k = 0; k < max_istates; ++k) {
      
      TParticle * pf = ((TParticle*)v_InitialState->At(k));
      histos->h_istate_eta->Fill( pf->Eta() );
      histos->h_istate_pt->Fill( pf->Pt() );
      
    }
    
    for( int k = 0; k < max_lsps; ++k) {
      
      TParticle * pf = ((TParticle*)v_Neutralinos->At(k));
      histos->h_lsp_eta->Fill( pf->Eta() );
      histos->h_lsp_pt->Fill( pf->Pt() );
      
    }
    
    
    if ( ievent < 0 ){
      v_FinalState->Delete();
      v_InitialState->Delete();
      v_Neutralinos->Delete();
      v_Neutrinos->Delete();
      
    }
    
    if ( m_debug ) std::cout << "ievent: " << jentry << std::endl;
    
  } //cierra loop sobre eventos  
  
}


void PythiaAnalysis::Loop( Long64_t firstevent, Long64_t lastevent )
{
  
  
  for( Long64_t k = firstevent; k <= lastevent; ++k ) {
    
    this->Loop( k );
  
    v_FinalState->Delete();
    v_InitialState->Delete();
    v_Neutralinos->Delete();
    v_Neutrinos->Delete();
    
  }
  
  
}



