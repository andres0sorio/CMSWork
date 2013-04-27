//
// This scripts works out the resolution of L1 Upgrades vs RECO (PFTaus)
// -- input data 2012 MuTau skim (@ 8 TeV) - no MTCut applied (not for this test)
// Switching on/off ECAL and HCAL 
//

void plotResolution( ) {
  
  float maxPt = 300.0;
  
  plotResolution("Pt", 0, maxPt, "(50,-2.0 , 2.0)", "MuTau_MTcut_EC");
  plotResolution("Eta",0, maxPt, "(50,-2.0 , 2.0)", "MuTau_MTcut_EC");
  plotResolution("Phi",0, maxPt, "(50,-2.0 , 2.0)", "MuTau_MTcut_EC");
  
}

void plotResolution( char* var, float xmin, float xmax, const char *xbinning, const char * skim) {
  
  //Output path
  TString path("./uct15-plots/resolution/Taus/noPUC/isoStudies");
    
  TString varName = TString("reco") + TString(var);  // RECO(PFTau)
  TString l1varName = TString("l1g") + TString(var); // L1 Calo Upgrade (can be Stage 1 or Stage 2)
  
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

  TFile * f1 = new TFile("../L1Tree_ECALThInf_MTCut.root" ); //ECAL off - Stage 2 ECAL Th -> inf

  //TFile * f1 = new TFile("../L1Tree_HCALThInf_MTCut.root" ); //HCAL off - Stage 2 HCAL Th -> inf

  f1->cd();

  TTree * Stage1Taus = (TTree*)gDirectory->Get("rlxTauSt1Efficiency/Ntuple");

  TTree * Stage2Taus = (TTree*)gDirectory->Get("rlxTauSt2Efficiency/Ntuple");
  
  std::cout << " Ntuple ready: " << Stage1Taus << " " << Stage2Taus << std::endl;
  
  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  
  TList * Stage1Histos = new TList();
  TList * Stage2Histos = new TList();
  
  //this is to separate into different decay mode as in reco::PFTau::hadronicDecayMode
  // Enumerator:
  // -1 kNull
  //  0 kOneProng0PiZero
  //  1 kOneProng1PiZero
  //  2 kOneProng2PiZero
  //  ...
  // 10 kThreeProng0PiZero

  int decayMode[10] = {0,1,10};
  
  for( int k = 0 ; k < 3; ++k ) {
    
    int xMin = xmin;
    int xMax = xmax;
    
    char cuts[200];
    
    //this is to use the decayMode:
    sprintf(cuts, " ( l1gMatch >= 1.0 )&& ( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 ) && recoPt > %d && recoPt < %d && decayMode == %d", xMin, xMax, decayMode[k]);
    
    TString histoDraw = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")/") + TString(varName) + TString(">> ");
    
    char st1HistoName[100];
    sprintf(st1HistoName, "htempSt1_%d", k);

    char st2HistoName[100];
    sprintf(st2HistoName, "htempSt2_%d", k);

    Stage1Taus->Draw( histoDraw + TString(st1HistoName) + TString(xbinning), cuts, "");
    TH1F* h1 = (TH1F*)gDirectory->Get( st1HistoName )->Clone();
    
    std::cout << h1 << std::endl;
    Stage1Histos->Add( h1 );
    
    Stage2Taus->Draw( histoDraw + TString(st2HistoName) + TString(xbinning), cuts, "");
    TH1F* h2 = (TH1F*)gDirectory->Get( st2HistoName )->Clone();
    
    std::cout << h2 << std::endl;
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
