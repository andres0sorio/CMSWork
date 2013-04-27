void pythia8_TopAll_100kev(Int_t nev  = 100000, const char * rndseed ) {
  
  char* path = gSystem->ExpandPathName("$PYTHIA8DATA");
  if (gSystem->AccessPathName(path)) {
    Warning("pythia8.C", 
            "Environment variable PYTHIA8DATA must contain path to pythi8100/xmldoc directory !");
    return;
  }
  
  // Load libraries
  gSystem->Load("$PYTHIA8/lib/libpythia8");
  gSystem->Load("$LHAPDFLOCATION/lib/libLHAPDF");

  gSystem->Load("libEG");
  gSystem->Load("libEGPythia8");
  
  //Definir archivo de salida
  TFile * outfile = new TFile("eventos_pythia8_100kev.root","RECREATE");
  
  TH1F * cont1 = new TH1F("cont1","Control var 1",100, 0, 6000);
 
  // Array of particles
  TClonesArray* particles = new TClonesArray("TParticle", 5000);
  
  //Definir el TTree
  TTree*tree= new TTree("tree","Arbol con particulas segun Pythia8");
  tree->Branch("particles",&particles);
  
  // Create pythia8 object
  TPythia8* pythia8 = new TPythia8();
  
  // Configure    
  pythia8->ReadString("Top:gg2ttbar = on");

  pythia8->ReadString("PDF:useLHAPDF = on ");
  pythia8->ReadString("PDF:LHAPDFset = cteq6l.LHpdf ");
  
  TString RandomStr("Random:seed = " );
  TString rndseedStr(rndseed);
  TString rndseedCmd = RandomStr + rndseedStr;
  
  pythia8->ReadString("Random:setSeed = on");
  pythia8->ReadString( rndseedCmd.Data() );
  
  // Initialize 
  
  pythia8->Initialize(2212 /* p */, 2212 /* p */, 7000. /* TeV */);
  
  // Event loop
  for (Int_t iev = 0; iev < nev; iev++) {
    
    pythia8->GenerateEvent();
    if (iev < 5) pythia8->EventListing();
    pythia8->ImportParticles(particles,"All");
    
    Int_t np = particles->GetEntriesFast();
    
    cont1->Fill( np );
    
    tree->Fill();
    
  }
  
  pythia8->PrintStatistics();
  
  outfile->Write();
  outfile->Close();
  
  
}
