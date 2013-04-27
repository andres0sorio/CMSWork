void rootlogon() 
{
  gStyle->SetPalette(0);  
  rootlogon(1);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {
    
    gSystem->Load("L1GtExtractedInfo_cc.so");
    gSystem->Load("DisplayParallelCoord_C.so");
    gSystem->Load("CompareDataEmulator_C.so");
    gSystem->Load("ReconstructData_C.so");
    
    
  } else {
	
   gSystem->AddIncludePath(" -DGZSTREAM_NAMESPACE=gz -I/usr/local/include ");
   gSystem->AddLinkedLibs(" -L/usr/local/lib -lgzstream -lz ");

   //gSystem->Load("L1GtExtractedInfo_cc.so");
   //gSystem->Load("DisplayParallelCoord_C.so");
   //gSystem->Load("CompareDataEmulator_C.so");
   
   gROOT->LoadMacro("L1GtExtractedInfo.cc++");
   gROOT->LoadMacro("DisplayParallelCoord.C++");
   gROOT->LoadMacro("CompareDataEmulator.C++");
   gROOT->LoadMacro("ReconstructData.C++");
   
  }
  
}
