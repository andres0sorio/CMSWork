// $Id: $
// Include files 

void processFile(const char *dataset, const char *inmap ) {
  
  gSystem->Load("L1GtExtractedInfo_cc.so");
  gSystem->Load("ReconstructData_C.so");

  ReconstructData *r1 = new ReconstructData(dataset,2);
  
  r1->readMap( inmap );
  
  r1->SecondLoop();
  
  delete r1;
  
  gSystem->Exec("rm *.so");
  
}
