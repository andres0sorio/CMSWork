// $Id: $
// Include files 

void processFile(const char *data, const char *emudata ) {
  
  gSystem->Load("L1GtExtractedInfo_cc.so");
  gSystem->Load("CompareDataEmulator_C.so");
  
  CompareDataEmulator *r1 = new CompareDataEmulator( data, emudata, 2);
  
  r1->setRunId( "111664" );
  
  r1->Loop(1); // 0=24, 1=25, ....
             
  //delete r1;
  
    
}
