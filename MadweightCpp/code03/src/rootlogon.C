void rootlogon() 
{
  
  rootlogon(1);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {
    
    gSystem->Load("Data_cc.so");
    
  } else {

    gROOT->LoadMacro("Data.cc++");

  }
  
}
