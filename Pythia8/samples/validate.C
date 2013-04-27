void validate( const char * input, const char * output, int istatePDG, int ievent, int jevent ) 
{

  gSystem->Load("Histograms_C.so");
  gSystem->Load("PythiaAnalysis_C.so");

  PythiaAnalysis * dataA;
  dataA = new PythiaAnalysis(input, output);
  dataA->SetInitialState(istatePDG);
  dataA->Loop(ievent, jevent);
  delete dataA;
  
}
