void rootlogon() 
{
  //don't compile: 0 compile: 1 don't do anything: -1
  rootlogon(1);
    
}

void rootlogon(int option) {
  
  gSystem->Load("libMathMore.so");

  if (option < 0) return;
  
  //don't compile - load shared objects
  if (!option) {
    
  gSystem->Load("loader_cc.so");
  gSystem->Load("BasicOutput_cc.so");
  gSystem->Load("eventB_cc.so");
  gSystem->Load("eventV_cc.so");
  gSystem->Load("UCSBTuplesAnalyzer_cc.so");
  

  } else {
    
    //// compile the basic stuff first
    gROOT->LoadMacro("loader.cc++");
    gROOT->LoadMacro("BasicOutput.cc++");
    gROOT->LoadMacro("eventB.cc++");
    gROOT->LoadMacro("eventV.cc++");
    gROOT->LoadMacro("UCSBTuplesAnalyzer.cc++"); 
  
  }
  
}
