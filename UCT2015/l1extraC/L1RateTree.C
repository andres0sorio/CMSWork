#define L1RateTree_cxx
#include "L1RateTree.h"

void L1RateTree::Loop(const char * var, const char * selec, const char * binning, const char *name)
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "L1RateTree> data nentries: " << nentries << std::endl;
  
  L1_CALIB_FACTOR = 1.0;
  
  m_histograms1D[var] = MakePlot( var, selec, binning, "pt", "L1 trigger studies",name);
  
  m_histograms1D[var]->Scale( L1_CALIB_FACTOR );

  m_histograms1D["l1rate"] = Make_Th_Integral( m_histograms1D[var] );

}


void L1RateTree::Loop() {
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1F * h1 = new TH1F("l1njets","L1 N jets",50,0,50);
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if ( !((pt->size() == 1) && (pt->at(0) < 0)) ) 
      h1->Fill( pt->size() );
    
  }
  
  m_canvas["njets"] = new TCanvas("UCTNjets", "L1 and UCT rates", 600, 600);
  m_canvas["njets"]->cd();
  h1->Draw();
  
}
