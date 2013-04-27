#include <stdio.h>
#include <stdlib.h>

#include "TTUStatisticDiagManager.h"


int main(int iargv, char **argv) {

  rpct::SorterCrate SC;
  
  rpct::TTUStatisticDiagManager * ttsd = new rpct::TTUStatisticDiagManager(std::string("TTUStats"),
									   std::string("/home/aosorio/scratch0/TtuRatemon/rpct/"),
									   &SC,
									  false);

  //
  
  TFile * outfile = new TFile("outfile-rates.root","RECREATE");
  outfile->cd();
  TTree * tree = new TTree("TtuRates","Ttu rates");

  ttsd->createBranches( (*tree) );

  ttsd->resetAndConfigHistos();

  ttsd->start();

  time_t startTime;

  ttsd->initialize(startTime);

  for(int k=0; k < 10; ++k) {

    ttsd->readout(true);
    
    ttsd->analyse();
    
    ttsd->finalize();
    
    sleep(2);

  }

  tree->Write();

  delete ttsd;
  

  return 1;

}
