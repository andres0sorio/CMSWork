// $Id: $
// Include files 


// local
#include "UCSBTuplesAnalyzer.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include <TROOT.h>
#include <TFile.h>

//-----------------------------------------------------------------------------
// main : analise
//
// 2008-12-20 : Andres Osorio
//-----------------------------------------------------------------------------

int main(int iargv, const char **argv) {
  
  if ( iargv < 3 ) {
    std::cout << "usage: ./analyse <file.txt> <option>" << std::endl;
    exit(0);
  }
  
  gROOT->ProcessLine("#include <vector>");
  
  TChain *chainV = new TChain("events");
  TChain *chainB = new TChain("events");
  
  const char *in     = argv[1];
  const char *option = argv[2];
  ifstream infile;
  infile.open( in );
  
  while (1) {
    char file[100];
    infile >> file;
    if (!infile.good()) break;
    TString cmdV = TString(file) + TString("/configurableAnalysis/eventV");
    TString cmdB = TString(file) + TString("/configurableAnalysis/eventB");
    chainV->Add(cmdV.Data());
    chainB->Add(cmdB.Data());
  }    
  
  infile.close();
  
  //. create a pointer to a UCSBTupleAnalyzer object
  UCSBTuplesAnalyzer * data = new UCSBTuplesAnalyzer(chainB,chainV,option);
  
  //. loop over events in that file
  data->Loop();
  
  //.all done. clean up and close any output file
  delete data;
  
  return 1;
  
}
