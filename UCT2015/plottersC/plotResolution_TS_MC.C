void plotResolution( ) {
  
  plotResolution("Pt", 0,201);
  plotResolution("Eta",0,201);
  plotResolution("Phi",0,201);
  
  
}

void plotResolution( char* var, float xmin, float xmax ) {

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

  //TFile * f1 = new TFile("../L1Tree_DiTaus_Resolution_Stg12.root" );

  //TFile * f1 = new TFile("../L1Tree_Htt_MC_RAWRECO_MC.root" );

  TFile * f1 = new TFile("../L1Tree_Htt_MC_RAWRECO_MC_VisTau.root" );

  f1->cd();

  TTree * Stage1Taus = (TTree*)gDirectory->Get("rlxVisTauSt1Efficiency/Ntuple");

  TTree * Stage2Taus = (TTree*)gDirectory->Get("rlxVisTauSt2Efficiency/Ntuple");
  
  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  
  int DeltaX = 2000;

  TList * Stage1Histos = new TList();
  TList * Stage2Histos = new TList();

  for( int k = 0 ; k < 1; ++k ) {

    int xMin = xmin + (DeltaX*k);
    int xMax = xMin + DeltaX;

    char cuts[100];
    sprintf(cuts, " l1gMatch > 0 && abs( recoEta ) < 1.4 && recoPt > %d && recoPt < %d", xMin, xMax);
    
    TString histoDraw = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")/") + TString(varName) + TString(">> ");
    
    char st1HistoName[100];
    sprintf(st1HistoName, "htempSt1_%d", k);

    char st2HistoName[100];
    sprintf(st2HistoName, "htempSt2_%d", k);

    Stage1Taus->Draw( histoDraw + TString(st1HistoName) + TString("(50,-2.0 , 2.0)"), cuts, "");
    TH1F* h1 = (TH1F*)gDirectory->Get( st1HistoName )->Clone();

    std::cout << h1 << std::endl;
    Stage1Histos->Add( h1 );

    Stage2Taus->Draw( histoDraw + TString(st2HistoName) + TString("(50,-2.0 , 2.0)"), cuts, "");
    TH1F* h2 = (TH1F*)gDirectory->Get( st2HistoName )->Clone();
    
    std::cout << h2 << std::endl;
    Stage2Histos->Add( h2 );

    TLegend * leg = new TLegend(0.2148241,0.722028,0.4484925,0.8601399);
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
    saveAs << path << "/eps/rlx_tau_reso_" << var << "_" << xMin << "_" << xMax << "_" << k << "_MC_V2" << ".eps";
    canvas->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/png/rlx_tau_reso_" << var << "_" << xMin << "_" << xMax << "_" << k << "_MC_V2" << ".png";
    canvas->SaveAs( saveAs.str().c_str() );
    
  }
  
  



}
