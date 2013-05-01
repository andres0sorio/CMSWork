#define L1RateTree_cxx

#include "L1RateTree.h"

void L1RateTree::Loop() {
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  
  std::cout << nentries << std::endl;

  int good_evts = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    
    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if ( ((pt->size() > 0 ) && (pt->at(0) > 0)) ) {
      //std::cout << "run " << run << " evt " << evt << " pt " << pt->at(0) << std::endl;
      ++good_evts;
    }

    //break;

  }
  
  std::cout << " good evts: " << good_evts << std::endl;


}

