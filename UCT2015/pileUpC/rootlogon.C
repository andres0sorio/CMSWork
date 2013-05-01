void rootlogon() 
{
  
  TString cmsswbase = getenv("CMSSW_BASE");
  
  if (cmsswbase.Length() > 0) {
    cout << "Loading FW Lite setup." << endl;
    gSystem->Load("libFWCoreFWLite.so");
    AutoLibraryLoader::enable();
    gSystem->Load("libDataFormatsFWLite.so");
    gSystem->Load("libUserCodeJetEventDataformat.so");
    
    gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/JetEventDataformat/src");
      
  }

  rootlogon(1);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {

    gSystem->Load("Histograms_C.so");
    

  } else {
    
    //compile the basic stuff first
    gROOT->LoadMacro("Histograms.C++");
    gROOT->LoadMacro("SimpleJetTree.C++");
    
  }
  
}
