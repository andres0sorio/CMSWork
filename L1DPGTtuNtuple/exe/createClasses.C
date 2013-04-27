{

  /*
  
  _file0->cd();

  _file0->cd("l1NtupleProducer");
  TTree * t1 = (TTree*)gDirectory->FindObjectAny("L1Tree");
  t1->MakeClass("L1Tree");
  
  _file0->cd("l1ExtraTreeProducer");
  t1 = (TTree*)gDirectory->FindObjectAny("L1ExtraTree");
  t1->MakeClass("L1ExtraTree");

  _file0->cd("l1MuonRecoTreeProducer");
  t1 = (TTree*)gDirectory->FindObjectAny("MuonRecoTree");
  t1->MakeClass("MuonRecoTree");
  

  _file0->cd("l1JetRecoTreeProducer");
  t1 = (TTree*)gDirectory->FindObjectAny("L1Tree");
  t1->MakeClass("L1Tree");
  
  _file0->cd("l1EgammaRecoTreeProducer");
  t1 = (TTree*)gDirectory->FindObjectAny("L1Tree");
  t1->MakeClass("L1Tree");
  
  */
  
  _file1->cd();
  _file1->cd("l1gtAnalyzer");
  t1 = (TTree*)gDirectory->FindObjectAny("L1TTUTree");
  t1->MakeClass("L1TTUTree"); 
  
  

}
