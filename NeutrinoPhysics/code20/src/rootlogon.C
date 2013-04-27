void rootlogon() 
{
  
  rootlogon(0);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {

    gROOT->LoadMacro("interpolator.C");
    gROOT->LoadMacro("makePlots.C");
    
  } else {
    
    //// compile the basic stuff first
    
    
  }
  
}
