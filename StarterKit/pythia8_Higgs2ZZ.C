// Note that before executing this script, 
//   -the env variable PYTHIA8 must point to the pythia8100 (or newer) directoryDATA
//   -the env variable PYTHIA8DATA must be defined and it must point to $PYTHIA8/xmldoc

void pythia8_Higgs2ZZ(Int_t nev  = 100, Int_t ndeb = 1) {
  
  char* path = gSystem->ExpandPathName("$PYTHIA8DATA");

  if (gSystem->AccessPathName(path)) {
    Warning("pythia8.C", 
            "Environment variable PYTHIA8DATA must contain path to pythi8100/xmldoc directory !");
    return;
  }
  
  // Load libraries
  gSystem->Load("$PYTHIA8/lib/libpythia8");
  //gSystem->Load("$PYTHIA8/lib/liblhapdfdummy");
  gSystem->Load("$LHAPDFLOCATION/lib/libLHAPDF");
  
  gSystem->Load("libEG");
  gSystem->Load("libEGPythia8");
  
  //Definir archivo de salida
  TFile * outfile = new TFile("eventos_pythia8_HZZ.root","RECREATE");
  
  // Array of particles
  TClonesArray* particles = new TClonesArray("TParticle", 4000);
  
  //Definir el TTree
  TTree*tree= new TTree("tree","Arbol con particulas segun Pythia8");
  tree->Branch("particles",&particles);
  
  // Create pythia8 object
  TPythia8* pythia8 = new TPythia8();
  
  // Configure    
  pythia8->ReadString("HiggsSM:gg2H = on");
  pythia8->ReadString("PDF:useLHAPDF = on ");
  pythia8->ReadString("PDF:LHAPDFset = cteq6l.LHpdf ");

  pythia8->ReadString("25:m0 = 200.0");
  pythia8->ReadString("25:onMode = off"); // esta opcion apaga todos los modos de decaimiento posibles para el Higgs
  pythia8->ReadString("25:onIfMatch = 23 23"); // esta opcion enciende el decaimiento a 25 (H0) ->23 (Z) 23(Z) 
  
  //Caso 2: queremos Z0 -> mu- mu+
  pythia8->ReadString("23:onMode = off");
  pythia8->ReadString("23:onIfMatch = 13 -13"); 
  
  // Initialize 
  
  pythia8->Initialize(2212 /* p */, 2212 /* p */, 7000. /* TeV */);
  
  // Event loop
  for (Int_t iev = 0; iev < nev; iev++) {
    
    pythia8->GenerateEvent();
    if (iev < ndeb) pythia8->EventListing();
    pythia8->ImportParticles(particles,"All");
    
    Int_t np = particles->GetEntriesFast();
    
    // Particle loop
    
    for (Int_t ip = 0; ip < np; ip++) {
      
      TParticle* part = (TParticle*) particles->At(ip);
      Int_t ist = part->GetStatusCode();
      Int_t pdg = part->GetPdgCode();
      
    }
    
    tree->Fill();
    
  }
  
  pythia8->PrintStatistics();
  
  outfile->Write();
  outfile->Close();
  
  
}
