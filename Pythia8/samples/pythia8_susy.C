void pythia8_susy(Int_t nev  = 100000, const char * input) {
  
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
  TFile * outfile = new TFile("eventos_pythia8_SUSY_100kev.root","RECREATE");
  
  TH1F * cont1 = new TH1F("cont1","Control var 1",100, 0, 6000);
  
  // Array of particles
  TClonesArray* particles = new TClonesArray("TParticle", 5000);
  
  //Definir el TTree
  TTree*tree= new TTree("tree","Arbol con particulas segun Pythia8");
  tree->Branch("particles",&particles);
  
  // Create pythia8 object
  TPythia8* pythia8 = new TPythia8();
  
  // Configure    
  //pythia8->ReadString("SUSY:All = on");
  
  pythia8->ReadString("SUSY:gg2gluinogluino = on");
  
  TString SLHA("SLHA:file = ");
  
  SLHA += TString(input);
  
  pythia8->ReadString( SLHA.Data() );

  pythia8->ReadString("PDF:useLHAPDF = on ");
  pythia8->ReadString("PDF:LHAPDFset = cteq6l.LHpdf ");

  // Initialize 
  
  pythia8->Initialize(2212 /* p */, 2212 /* p */, 7000. /* TeV */);
  
  int iev = 0;
  
  // Event loop
  while( iev < nev ) {
    
    cout <<"Generando Evento:" << iev <<'\n';
    pythia8->GenerateEvent();
    if (iev < 1) pythia8->EventListing();
    pythia8->ImportParticles(particles,"All");

    Int_t np = particles->GetEntriesFast();
    
    cont1->Fill( np );
    
    //for (Int_t ip = 0; ip < np; ip++) {
    //Leemos informacion de cada particula
    //  TParticle* part = (TParticle*) particles->At(ip); //Esta es la particula i
    //  Int_t ist = part->GetStatusCode(); //obtenemos su estatus
    //  Int_t pdg = part->GetPdgCode(); // y su codigo PDG
    //Queremos graficar el momento Transverso de los muones = Sqrt(px*px + py*py)
    //1. Obtener aqui el momento de las particulas
    //float px = part->Px();
    //float py = part->Px();
    //h1->Fill( sqrt(px*px + py*py) );
    //}
    
    tree->Fill();
    ++iev;
    
  }
  cout <<"END:::Events Generated:" << iev <<'\n';
  
  pythia8->PrintStatistics();
  
  outfile->Write();
  outfile->Close();
  
}

