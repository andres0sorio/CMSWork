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
    
    gSystem->AddIncludePath(" -I$FASTJET/include ");
    gSystem->AddLinkedLibs("-Wl,-rpath,$FASTJET/lib -lm -L$FASTJET/lib -lfastjet");

    //// compile the basic stuff first
    gROOT->LoadMacro("RootOutput.C++");
    gROOT->LoadMacro("PythiaAnalysis.C++");
    gROOT->LoadMacro("JetPythiaAnalysis.C++");
    
  }
  
}
