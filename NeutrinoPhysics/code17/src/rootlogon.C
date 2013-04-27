void rootlogon() 
{
  
  rootlogon(1);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {

    //gSystem->Load("RootOutput_C.so");
    //gSystem->Load("PythiaAnalysis_C.so");
	
    
  } else {
    
    //// compile the basic stuff first
    gROOT->LoadMacro("TDataSets.cc++");
    gROOT->LoadMacro("TGraphFromXML.cc++");
        
  }
  
}
