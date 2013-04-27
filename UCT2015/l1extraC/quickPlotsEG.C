{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);
  
  TString input_data("./L1Tree.root");
  L12015Analysis * l1 = new L12015Analysis( input_data.Data() );
  l1->Loop();
  
  l1->m_l1tree->fChain->Draw("pt>>htemp1(80,0,80)", "pt > 0.0", "");
  TH1F* h1 = (TH1F*)gDirectory->Get("htemp1").Clone();
  
  l1->m_ucttree->fChain->Draw("pt>>htemp2(80,0,80)", "pt > 0.0", "");
  TH1F* h2 = (TH1F*)gDirectory->Get("htemp2").Clone();
  std::cout << h2 << " " << h2->GetName() << std::endl;
  
  h1->Draw("ph");
  h2->SetLineColor(2);
  h2->Draw("phsame");



}
