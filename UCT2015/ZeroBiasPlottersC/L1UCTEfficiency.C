#define L1UCTEfficiency_cxx

#include "L1UCTEfficiency.h"

void L1UCTEfficiency::Loop( int first_evt, int last_evt ) {
  
  // ... - > Loop over Reco objects

  Long64_t max_reco = m_RecoTree->fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  
  std::cout << max_reco << std::endl;
  
  for ( Long64_t iEvt = (38371-2) ; iEvt < (38371 + 2); iEvt++ ){ // Primary LOOP
    
    Long64_t iLT = m_RecoTree->LoadTree(iEvt);
    
    if (iLT < 0) break;
    
    nb = m_RecoTree->fChain->GetEntry(iEvt);
    nbytes += nb;
    
    evt = m_RecoTree->evt;
    run = m_RecoTree->run;
    lumi= m_RecoTree->lumi;
    
    // ... - > Loop over L1 objects to do the matching in Delta R
    // ... - > Loop is done between first_evt and last_evt
    // ... - > l1Match = true/false;
    // ... - > Save into tree the L1, Reco and match info

    // Variable no usada
    //   Long64_t max_l1 = m_L1Tree->fChain->GetEntriesFast();
    
    Long64_t mbytes = 0, mb = 0;

    nRecoObjects = int( m_RecoTree->pt->size() );
    
    if( nRecoObjects == 1) {
      if ( m_RecoTree->pt->at(0) < 0 ) 
	continue;
    }
    else {
      std::cout << " first event with nreco > 1 " << iEvt << std::endl;
    }
    
    for ( Long64_t jEvt = first_evt; jEvt <= last_evt; jEvt++ ){ // Secondary LOOP
      
      Long64_t jLT = m_L1Tree->LoadTree(jEvt);
      
      if ( jLT < 0 ) break;
      
      mb = m_L1Tree->fChain->GetEntry(jEvt);
      mbytes += mb;
      
      // Match event first
      Long64_t l1_evt = m_L1Tree->evt;
      Long64_t l1_run = m_L1Tree->run;
      
      std::cout << "l1_run " << l1_run << " evt: " << evt << " " << l1_evt << std::endl;
      
      if ( (evt == l1_evt) && (run == l1_run) ) {
	
	std::cout << " event matched! " << std::endl;
	
	// Match DeltaR < 0.5 where DeltaR = sqrt ( (DeltaEta)^2 + (DeltaPhi)^2 )
	// m_RecoTree->eta->at(position)
	
	int best_i_pos = 0;
	int best_j_pos = 0;
	float minDeltaR = -1.0;
	
	for (size_t i = 0; i < nRecoObjects; ++i) {
	  
	  recoEta = m_RecoTree->eta->at(i);
	  recoPhi = m_RecoTree->phi->at(i);
	  recoPt  = m_RecoTree->pt->at(i);
	  
	  std::cout << " reco: " << recoEta << " " << recoPhi << " " << recoPt << std::endl;

	  for (size_t j = 0; j < m_L1Tree->pt->size(); ++j) {
	  
	    /*	    
	      l1Eta = m_L1Tree->eta->at(j);
	      l1Phi = m_L1Tree->phi->at(j);
	      l1Pt  = m_L1Tree->pt->at(j);
	    */

	    if ( abs( m_L1Tree->eta->at(j) ) > 5.0 ) 
	      continue;

	    std::cout << " l1: " << m_L1Tree->eta->at(j) << " " << m_L1Tree->phi->at(j) << " " << std::endl;
	    
	    float deltaR1 = std::sqrt( pow( (m_RecoTree->eta->at(i)) - (m_L1Tree->eta->at(j)), 2.0 ) 
				       + pow( (m_RecoTree->phi->at(i) - (m_L1Tree->phi->at(j)) ), 2.0 ) );
	    
	    //float deltaR2 = std::sqrt( pow( (m_RecoTree->eta->at(i)) - (m_L1Tree->eta->at(j+1)) ,2.0) 
	    //		       + pow( (m_RecoTree->phi->at(i) - (m_L1Tree->phi->at(j+1)) ), 2.0) );
	    
	    std::cout <<  " deltaR " << deltaR1 << std::endl;
	    	    
	    // lo anterior es lo mismo que lo siguiente	    
	    // float deltaR = std::sqrt( ( recoEta - l1Eta )^2) + (( recoPhi - l1Phi )^2) );
	    
	    if ( deltaR1 < 0.5 ) {
	      
	      if ( deltaR1 < minDeltaR ) {
		
		best_i_pos = i;
		best_j_pos = j;
		minDeltaR = deltaR1;

		std::cout <<  " We found a match " << std::endl;
		l1Match = 1.0;
		
	      }
	      
	    } else l1Match = 0.0;
	    
	  }
	  
	}
	
	//only fill the closest DR (matched or not matched)
	
	// use the best_i_pos, best_j_pos 
	std::cout << " " << best_i_pos << "  " << best_j_pos << std::endl;
	
	m_tree->Fill();
	
      } else 
	std::cout << " No event matching" << std::endl;
      
    }
    
  }
  
  m_tree->Write();
  
  m_output->Close();
  
  std::cout << " Job done! " << std::endl;
  
}
