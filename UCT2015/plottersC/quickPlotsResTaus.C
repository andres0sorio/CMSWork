{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);

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

  TFile * f1 = new TFile("../L1Tree_DiTaus_Resolution_Stg12.root" );

  f1->cd();

  TTree * Stage1Taus = (TTree*)gDirectory->Get("rlxTauSt1Efficiency/Ntuple");

  TTree * Stage2Taus = (TTree*)gDirectory->Get("rlxTauSt2Efficiency/Ntuple");
  
  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  
  Stage1Taus->Draw("(l1gPt - recoPt)/recoPt>> htemp1(50,-1.0 , 1.0)", "l1gMatch > 0", "");
  TH1F* h1 = (TH1F*)gDirectory->Get("htemp1").Clone();

  Stage2Taus->Draw("(l1gPt - recoPt)/recoPt>> htemp2(50,-1.0 , 1.0)", "l1gMatch > 0", "");
  TH1F* h2 = (TH1F*)gDirectory->Get("htemp2").Clone();

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

  h1->GetXaxis()->SetTitle("(E_{T,L1} - E_{T,reco})/E_{T,reco}");
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetTitleOffset(1.34);
  h1->GetXaxis()->SetTitleFont(42);
  h1->GetYaxis()->SetTitle("A.U.");
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetTitleOffset(1.3);
  h1->GetYaxis()->SetTitleFont(42);
    
  h1->SetLineColor(2);
  h1->Draw("ph");
  h1->Draw();

  h2->SetLineColor(4);
  h2->Draw("same");

  leg->Draw();
  
}
