#define SimpleJetTree_cxx

#include "SimpleJetTree.h"
#include <algorithm>

void SimpleJetTree::Loop()
{
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  std::cout << " n " << nentries << std::endl;

  Long64_t nbytes = 0, nb = 0;
  
  nentries = 1000;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    
    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    int max_jets = v_jets->size();

    std::sort( v_jets->begin(), v_jets->end() );
    std::reverse( v_jets->begin(), v_jets->end() );

    for( int k=0; k < max_jets; ++k ) {
      
      m_histograms2D["jetetaEt"]->Fill(v_jets->at(k).m_Seed.EtaPos, v_jets->at(k).m_Seed.Et );

    }
    

    int max_regions = v_regions->size();
    
    for( int k=0; k < max_regions; ++k ) {
      
      //std::cout << max_regions << " " << v_regions->at(k).EtaPos << " " << v_regions->at(k).Et << std::endl;

      //if ( v_regions->at(k).Et > 0 ) {
	
	m_histograms1D["regionEt"]->Fill( v_regions->at(k).PhysicalEt );
	m_histograms2D["etaphi"]->Fill(v_regions->at(k).EtaPos, v_regions->at(k).PhiPos);
	m_histograms2D["etaphiEt"]->Fill(v_regions->at(k).EtaPos, v_regions->at(k).PhiPos, v_regions->at(k).PhysicalEt );
	m_histograms2D["etaEt"]->Fill(v_regions->at(k).EtaPos,v_regions->at(k).PhysicalEt );
	m_histogramsPf["etaEt"]->Fill( v_regions->at(k).EtaPos,v_regions->at(k).PhysicalEt );
      
	//}

    }
    
  }
  
  m_canvas["c1"] = new TCanvas("c1","Plots",800,600 );
  m_canvas["c1"]->Divide(2,2);
  
  m_canvas["c1"]->cd(1);
  m_histograms2D["etaphiEt"]->Draw();
  
  m_canvas["c1"]->cd(2);
  TH2F * h1 = (TH2F*)m_histograms2D["etaphiEt"]->Clone();
  h1->Divide( m_histograms2D["etaphi"] );
  //h1->Draw();
  
  m_histograms2D["etaEt"]->Draw();


  m_canvas["c1"]->cd(3);
  m_histograms1D["regionEt"]->Draw();
  //... Average energy per region

  m_canvas["c1"]->cd(4);
  m_histogramsPf["etaEt"]->Draw();

  m_canvas["c2"] = new TCanvas("c2","Plots",800,600 );
  m_canvas["c2"]->Divide(2,2);

  m_canvas["c2"]->cd(1);

  m_histograms2D["jetetaEt"]->Draw();


}
