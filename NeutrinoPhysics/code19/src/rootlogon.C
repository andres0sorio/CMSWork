void rootlogon() 
{
  
  rootlogon(0);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {

    gSystem->Load("logpar_interp_cc.so");
    gROOT->LoadMacro("graph-LogParabolas-Interp1.C");
    gROOT->LoadMacro("graph-1959-650-1ES.C");
    gROOT->LoadMacro("fitted-parabolas-data.C");
    
  } else {
    
    //// compile the basic stuff first
    gROOT->LoadMacro("logpar_interp.cc++");
    gROOT->LoadMacro("graph-LogParabolas-Interp1.C");
    gROOT->LoadMacro("graph-1959-650-1ES.C");
    gROOT->LoadMacro("fitted-parabolas-data.C");
    
    
  }
  
}
