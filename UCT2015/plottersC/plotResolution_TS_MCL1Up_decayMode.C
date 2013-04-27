//
// This scripts works out the resolution of the L1 Upgrades (Stage1 & Stage2) vs MCGen particle
// -- we worked this for Taus
// -- input data H->tau tau @ 14 TeV simulation
//

void plotResolution( ) {
  
  float maxPt = 300.0;

  plotResolution("Pt",  0, maxPt, "(50,-2.0 , 2.0)", "HtottMC_EC");
  plotResolution("Eta", 0, maxPt, "(50,-2.0 , 2.0)", "HtottMC_EC");
  plotResolution("Phi", 0, maxPt, "(50,-2.0 , 2.0)", "HtottMC_EC");

}

void plotResolution( char* var, float xmin, float xmax, const char *xbinning, const char * skim) {
  
  //Output path
  TString path("./uct15-plots/resolution/Taus/noPUC/isoStudies");

  TString varName = TString("reco") + TString(var);
  TString l1varName = TString("l1g") + TString(var);

  gROOT->SetStyle("Plain");
  gROOT->SetBatch(false);
  gStyle->SetOptStat(0);

  // --- Use the CMS TDR style
  gROOT->ProcessLine(".L tdrStyle.C");
  setTDRStyle();
  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetPadRightMargin(0.08);
  tdrStyle->SetLegendBorderSize(0);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetOptStat(0);
  tdrStyle->SetTitleFontSize(0.05);

  TFile * f1 = new TFile("../L1Tree_Htt_MC_RAWRECO_MC_VisTau.root" );

  f1->cd();

  TTree * Stage1Taus = (TTree*)gDirectory->Get("rlxVisTauSt1Efficiency/Ntuple");

  TTree * Stage2Taus = (TTree*)gDirectory->Get("rlxVisTauSt2Efficiency/Ntuple");

  std::cout << " Ntuple ready: " << Stage1Taus << std::endl;
  std::cout << " Ntuple ready: " << Stage1Taus << std::endl;
  
  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  
  TList * Stage1Histos = new TList();
  TList * Stage2Histos = new TList();
  
  //this is to separate in the differente decay Modes:
  //Enumerator:
  // 0  kElectron 	
  // 1  kMuon 	
  // 2  kOneProng0pi0 	
  // 3  kOneProng1pi0 	
  // 4  kOneProng2pi0 	
  // 5  kThreeProng0pi0 	
  // 6  kThreeProng1pi0 	
  // 7  kOther 	


  int decayMode[10] = {2,3,5}; // Same decays as we studied in Data
  
  for( int k = 0 ; k < 3; ++k ) {
    
    int xMin = xmin;
    int xMax = xmax;
    
    char cuts[200];
    
    //this is to use the decayMode:
    sprintf(cuts, " (l1gMatch >= 1.0) && (l1gDR < 0.4) && ( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 ) && recoPt > %d && recoPt < %d && decayMode == %d", xMin, xMax, decayMode[k]);
    
    TString histoDraw = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")/") + TString(varName) + TString(">> ");
   
    std::cout << " plotting: " << histoDraw << std::endl; 
    std::cout << " cuts: " << TString( cuts ) << std::endl;

    char st1HistoName[100];
    sprintf(st1HistoName, "htempSt1_%d", k);

    char st2HistoName[100];
    sprintf(st2HistoName, "htempSt2_%d", k);

    Stage1Taus->Draw( histoDraw + TString(st1HistoName) + TString(xbinning), cuts, "");
    TH1F* h1 = (TH1F*)gDirectory->Get( st1HistoName )->Clone();
    
    Stage1Histos->Add( h1 );
    
    Stage2Taus->Draw( histoDraw + TString(st2HistoName) + TString(xbinning), cuts, "");
    TH1F* h2 = (TH1F*)gDirectory->Get( st2HistoName )->Clone();
    
    Stage2Histos->Add( h2 );

    //////////////////////////////////////////////////
    TLegend * leg = new TLegend(0.21,0.72,0.44,0.86);
    leg->AddEntry( h1, "Stage 1" );
    leg->AddEntry( h2, "Stage 2" );
    leg->SetBorderSize(0);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(0);
    leg->SetFillStyle(1001);
    
    canvas->cd();
    
    //h1->GetXaxis()->SetTitle("(E_{T,L1} - E_{T,reco})/E_{T,reco}");
    h1->GetXaxis()->SetLabelFont(42);
    h1->GetXaxis()->SetTitleOffset(1.34);
    h1->GetXaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitle("A.U.");
    h1->GetYaxis()->SetLabelFont(42);
    h1->GetYaxis()->SetTitleOffset(1.3);
    h1->GetYaxis()->SetTitleFont(42);

    //h1->SetMaximum(200E3);
    h1->SetLineColor(2);
    h1->Draw("ph");
    h1->Draw();
    
    h2->SetLineColor(4);
    h2->Draw("same");
    
    leg->Draw();

    std::stringstream saveAs;
    
    saveAs.str("");
    saveAs << path << "/eps/rlx_tau_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_dcm_" << k << "_" << ".eps";
    canvas->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/png/rlx_tau_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_dcm_" << k << "_" << ".png";
    canvas->SaveAs( saveAs.str().c_str() );
    
  }
  
  



}
