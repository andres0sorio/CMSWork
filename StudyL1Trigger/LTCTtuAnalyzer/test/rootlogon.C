void rootlogon() 
{
  
  rootlogon(0);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {
    
    //gSystem->Load("Data_C.so");
    //gSystem->Load("AnalyzeLtcData_C.so");
    
  } else {
	
   gSystem->AddIncludePath(" -DGZSTREAM_NAMESPACE=gz -I$CMSSW_BASE/src ");
   gSystem->AddLinkedLibs(" -L$CMSSW_BASE/src/StudyL1Trigger/L1GtExtractInfo/lib -lgzstream ");
   gROOT->LoadMacro("$CMSSW_BASE/src/StudyL1Trigger/L1GtExtractInfo/plugins/L1GtExtractedInfo.cc++");

   gROOT->LoadMacro("AnalyzeLtcData.C++");

  }
  
}
