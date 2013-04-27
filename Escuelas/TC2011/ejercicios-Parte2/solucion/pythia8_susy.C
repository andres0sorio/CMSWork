void pythia8_susy() {

  Int_t maxEvts = 100; // Maximo numero de eventos

  char* path = gSystem->ExpandPathName("$PYTHIA8DATA");
  if (gSystem->AccessPathName(path)) {
    Warning("pythia8.C", 
            "Environment variable PYTHIA8DATA must contain path to pythi8100/xmldoc directory !");
    return;
  }
  
  // Load libraries
  gSystem->Load("$PYTHIA8/lib/libpythia8");
  gSystem->Load("$PYTHIA8/lib/liblhapdfdummy");
  
  gSystem->Load("libEG");
  gSystem->Load("libEGPythia8");
  
  //Definir archivo de salida
  TFile * outfile = new TFile("eventos_pythia8_SUSY.root","RECREATE");
  
  // Array of particles
  TClonesArray* particles = new TClonesArray("TParticle", 5000);
  
  //Definir el TTree
  TTree*tree= new TTree("tree","Arbol con particulas segun Pythia8");
  tree->Branch("particles",&particles);
  
  // Create pythia8 object
  TPythia8* pythia8 = new TPythia8();
  
  //*Configurar: Aqui seleccione el proceso que quiere simular    
  pythia8->ReadString("SUSY:all = on"); //Todos los procesos susy posibles
  //pythia8->ReadString("SUSY:qqbar2chi+-chi0 = on"); //Un proceso en especial
  
  //Importante: pasar a Pythia8 el nombre del archivo SLHA
  pythia8->ReadString("SLHA:file = SUSY_LM2_sftsht.slha"); //insertar aqui el nombre del archivo SLHA

  // Initialize 
  
  pythia8->Initialize(2212 /* p */, 2212 /* p */, 7000. /* TeV */);
  
  int iev = 0;
  
  // Event loop
  
  while( iev < maxEvts ) {
    
    pythia8->GenerateEvent();
    if (iev < 1) pythia8->EventListing();
    pythia8->ImportParticles(particles,"All");
    
    Int_t np = particles->GetEntriesFast();
    
    // Particle loop
    
    for (Int_t ip = 0; ip < np; ip++) {
      
      TParticle* part = (TParticle*) particles->At(ip);
      Int_t ist = part->GetStatusCode();
      Int_t pdg = part->GetPdgCode();
      
    }

   tree->Fill();
   ++iev;
     	 
  }
  
  pythia8->PrintStatistics();
  
  outfile->Write();
  outfile->Close();
  
   
}

