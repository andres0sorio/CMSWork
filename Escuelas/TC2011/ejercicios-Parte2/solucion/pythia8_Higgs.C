void pythia8_Higgs() {

  Int_t maxEvts = 1000; // Maximo numero de eventos
   
  char* path = gSystem->ExpandPathName("$PYTHIA8DATA");

  if (gSystem->AccessPathName(path)) {
    Warning("pythia8.C", 
            "Environment variable PYTHIA8DATA must contain path to pythi8100/xmldoc directory !");
    return;
  }
  
  // Load libraries
  gSystem->Load("$PYTHIA8/lib/libpythia8");
  gSystem->Load("$PYTHIA8/lib/liblhapdfdummy");
  
  /// PDFs: - lamentablemente en el LiveCD esta opcion no es posible
  //gSystem->Load("$LHAPDFLOCATION/lib/libLHAPDF");
  
  gSystem->Load("libEG");
  gSystem->Load("libEGPythia8");
  
  //Definir archivo de salida
  TFile * outfile = new TFile("eventos_pythia8_Higgs.root","RECREATE");
  
  // Array of particles
  TClonesArray* particles = new TClonesArray("TParticle", 4000);
  
  //Definir el TTree
  TTree*tree= new TTree("tree","Arbol con particulas segun Pythia8");
  tree->Branch("particles",&particles);
  
  // Create pythia8 object
  TPythia8* pythia8 = new TPythia8();
  
  // Configure: aqui se selecciona el proceso a simular    
  pythia8->ReadString("HiggsSM:gg2H = on");
  
  /// PDFs: - lamentablemente en el LiveCD esta opcion no es posible
  //pythia8->ReadString("PDF:useLHAPDF = on ");
  //pythia8->ReadString("PDF:LHAPDFset = cteq6l.LHpdf ");
  
  pythia8->ReadString("25:m0 = 200.0"); //masa del Higgs <- Cambiar a la masa sugerida

  pythia8->ReadString("25:onMode = off"); // esta opcion apaga todos los modos de decaimiento posibles para el Higgs
  pythia8->ReadString("25:onIfMatch = 24 -24"); // esta opcion enciende el decaimiento a 25 (H0) ->24 (W+) -24(W-) 

  //Ejercicio 2: queremos W -> mu nu
  
  //pythia8->ReadString("24:onMode = off");
  //pythia8->ReadString("24:onIfMatch = -13 14");
  
  // Initializar: aqui seleccionar el tipo de haz y la energia de C.M. 
  // proton 2212 anti proton -2212
  // electron 11 anti electron -11

  
  //LHC:
  pythia8->Initialize(2212 /* p */, 2212 /* p */, 7000. /* GeV */);
  
  // Event loop
  for (Int_t iev = 0; iev < maxEvts; iev++) {
    
    pythia8->GenerateEvent();
    if (iev < 1) pythia8->EventListing();
    pythia8->ImportParticles(particles,"All");
    
    tree->Fill();
    
  }
  
  pythia8->PrintStatistics();
  
  outfile->Write();
  outfile->Close();
  
  
}
