void rootlogon() 
{
  
  rootlogon(0);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {

    gSystem->Load("../lib/libExRootAnalysis.so");
	
  } else {
    
    
  }
  
}
