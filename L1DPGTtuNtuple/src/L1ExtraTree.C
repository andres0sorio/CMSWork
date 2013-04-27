#define L1ExtraTree_cxx
#include "L1ExtraTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "CommonIncludes.h"

void L1ExtraTree::Loop(Long64_t maxevts)
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  if ( maxevts > 0 )
    nentries = maxevts;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }

  std::cout << nentries << std::endl;

}
