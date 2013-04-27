#if defined(__CINT__)
{
  
  TFile *m_output = new TFile("tturates.root","RECREATE");
  
  TTree *tree = new TTree("TtuRates","Ttu rates");
  
  // Declaration of leaf types
  Int_t           Run;
  Int_t           Lumi;
  ULong64_t       Orbit;
  ULong64_t       Time;
  Int_t           nWheels;
  Int_t           nSectors;
  Int_t           RateByWheel[5];
  Int_t           RateBySectorWM2[12];
  Int_t           RateBySectorWM1[12];
  Int_t           RateBySectorW00[12];
  Int_t           RateBySectorWP1[12];
  Int_t           RateBySectorWP2[12];
    
  // List of branches
  TBranch        *b_Run;
  TBranch        *b_Lumi;
  TBranch        *b_Orbit;
  TBranch        *b_Time;
  
  TBranch        *b_nWheels;
  TBranch        *b_nSectors;
  TBranch        *b_RateByWheel;
  TBranch        *b_RateBySectorWM2;
  TBranch        *b_RateBySectorWM1;
  TBranch        *b_RateBySectorW00;
  TBranch        *b_RateBySectorWP1;
  TBranch        *b_RateBySectorWP2;

  //////

  // Set branch addresses and branch pointers
  
  tree->Branch("Run"             , &Run         , "Run/I");
  tree->Branch("Lumi"            , &Lumi        , "Lumi/I");
  tree->Branch("Orbit"           , &Orbit       , "Orbit/l");
  tree->Branch("Time"            , &Time        , "Time/l");
  tree->Branch("nWheels"         , &nWheels     , "nWheels/I");
  tree->Branch("RateByWheel"     , RateByWheel  , "RateByWheel[nWheels]/I");
  tree->Branch("nSectors"        , &nSectors        , "nSectors/I");
  tree->Branch("RateBySectorWM2" , RateBySectorWM2  , "RateBySectorWM2[nSectors]/I");
  tree->Branch("RateBySectorWM1" , RateBySectorWM1  , "RateBySectorWM1[nSectors]/I");
  tree->Branch("RateBySectorW00" , RateBySectorW00  , "RateBySectorW00[nSectors]/I");
  tree->Branch("RateBySectorWP1" , RateBySectorWP1  , "RateBySectorWP1[nSectors]/I");
  tree->Branch("RateBySectorWP2" , RateBySectorWP2  , "RateBySectorWP2[nSectors]/I");
  
  ///Fill the ntuple:

  for( int run = 0; run < 5; ++run ) 
  {
    Run      = run + 125200;
    Lumi     = 50;
    Orbit    = 1000;
    Time     = 1000;
    nWheels  = 5;
    nSectors = 12;
    
    for( int k=0; k < 5; ++k )
    {
      RateByWheel[k] = 40 + k*10;
    }
    
    for( int k=0; k < 12; ++k) 
    {
      RateBySectorWM2[k] = 10;
      RateBySectorWM1[k] = 15;
      RateBySectorW00[k] = 20;
      RateBySectorWP1[k] = 25;
      RateBySectorWP2[k] = 30;
            
    }


    tree->Fill();
    
  }

  m_output.Write();
  m_output.Close();

}
#endif
