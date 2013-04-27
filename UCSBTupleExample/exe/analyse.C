void analyse(const char *in , const char *opt) 
{
  
  //ROOT script to run the analysis in batch mode
  //It has the same functionality as the analyse.cc 
  
  gSystem->Load("loader_cc.so");
  gSystem->Load("BasicOutput_cc.so");
  gSystem->Load("eventB_cc.so");
  gSystem->Load("eventV_cc.so");
  gSystem->Load("UCSBTuplesAnalyzer_cc.so");
  
  TChain *chainV = new TChain("events");
  TChain *chainB = new TChain("events");
  
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
  UCSBTuplesAnalyzer * data = new UCSBTuplesAnalyzer(chainB,chainV,opt);
  
  //. loop over events in that file
  data->Loop();
  
  //.all done. clean up and close any output file
  delete data;
    
  
}
