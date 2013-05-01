#include "SimpleJetTree.h"

void makePlots();

void makePlots( const char*, float );

void makePlots() {
  
  if( 1 ) {
    makePlots("80,0,400", 1.0 );
  }
  
}

void makePlots( const char* binning, float PUCut ) {
  
  std::ofstream * logfile = new std::ofstream("logs/runAnalysis_Jets_WP.log");
  std::ofstream * selfile = new std::ofstream("logs/runAnalysis_Jets_WP_Selection.log");

  TDatime *d1 = new TDatime();
  (*logfile) << d1->AsString() << std::endl;
  
  gROOT->SetBatch(false);

  //####################################
  //####### GET PLOTS #########
  //####################################

  // --- Use the CMS TDR style
  /*
    gROOT->ProcessLine(".L tdrStyle.C");
    setTDRStyle();
    tdrStyle->SetErrorX(0.5);
    tdrStyle->SetPadLeftMargin(0.18);
    tdrStyle->SetPadRightMargin(0.08);
    tdrStyle->SetLegendBorderSize(0);
    tdrStyle->SetTitleYOffset(1.3);
    tdrStyle->SetOptStat(0);
    tdrStyle->SetTitleFontSize(0.04);
    tdrStyle->SetLabelSize(0.04, "X");
    tdrStyle->cd();
  */

  //bool debug = false;
  
  TString PUopt("pre");
  TString input_data;
  //input_data = TString("../uct_eff_trees_jetskim_putree_v3.root");
  input_data = TString("../uct_rates_zerobAll_198609_PileUpExtra_V2.root");
  
  SimpleJetTree * uct = new SimpleJetTree(input_data.Data(),"pileUpTreeExtra/Ntuple");
  
  uct->BookHistograms(100,0,200);
  uct->Loop();
  
  char filenamePNG[100];
  char filenameEPS[100];
  
  TList * v_rates = new TList();
  
  std::stringstream Selection;
  std::stringstream BaseSelection;
  std::stringstream Command;
  
  ////
  


  ////

  sprintf(filenamePNG, "./uct15-plots/rate/Jets/%s/isoStudies/png/pu_jets_%0.2f.png" , PUopt.Data(), PUCut);
  sprintf(filenameEPS, "./uct15-plots/rate/Jets/%s/isoStudies/eps/pu_jets_%0.2f.eps" , PUopt.Data(), PUCut);
  
  logfile->close();
  delete logfile;
  selfile->close();
  delete selfile;
  
  delete d1;
  
}

