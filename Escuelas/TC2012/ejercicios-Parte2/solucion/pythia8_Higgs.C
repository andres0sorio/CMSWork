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
  TClonesArray* particles = new TClonesArray("TParticle", 5000);
  
  //Definir el TTree
  TTree*tree= new TTree("tree","Arbol con particulas segun Pythia8");
  tree->Branch("particles",&particles);
  
  // Create pythia8 object
  TPythia8* pythia8 = new TPythia8();
  
  // Configure: aqui se selecciona el proceso a simular    
  pythia8->ReadString("HiggsSM:ffbar2HZ = on");

  /// PDFs: - lamentablemente en el LiveCD esta opcion no es posible
  //pythia8->ReadString("PDF:useLHAPDF = on ");
  //pythia8->ReadString("PDF:LHAPDFset = cteq6l.LHpdf ");
  
  // Por el momento apagamos la hadronizacion - todo para en los partones iniciales
  pythia8->ReadString("HadronLevel:all = off"); 
  pythia8->ReadString("PartonLevel:ISR = off");
  pythia8->ReadString("PartonLevel:FSR = off");

  pythia8->ReadString("25:m0 = 125.0"); //masa del Higgs <- Cambiar a la masa sugerida

  //Queremos que Z-> q qbar y H0-> b bbar
  pythia8->ReadString("25:onMode = off"); // esta opcion apaga todos los modos de decaimiento posibles para el Higgs
  pythia8->ReadString("25:onIfMatch = -5 5"); // esta opcion enciende el decaimiento a 25 (H0) ->24 (W+) -24(W-) 

  pythia8->ReadString("23:onMode = off");
  pythia8->ReadString("23:onIfMatch = -13 13");

  // Initializar: aqui seleccionar el tipo de haz y la energia de C.M. 
  // proton 2212 anti proton -2212
  
  //LHC:
  pythia8->Initialize(2212 /* p */, 2212 /* p */, 8000. /* GeV */);
  
  TH1F * h1 = new TH1F("hpt", "Muons Pt", 50, 0, 200);

  // Event loop
  for (Int_t iev = 0; iev < maxEvts; iev++) {
    
    pythia8->GenerateEvent();
    if (iev < 1) pythia8->EventListing();
    pythia8->ImportParticles(particles,"All");

    Int_t np = particles->GetEntriesFast();

    // Particle Loop

    for (Int_t ip = 0; ip < np; ip++) {
      
      //Leemos informacion de cada particula

      TParticle* part = (TParticle*) particles->At(ip); //Esta es la particula i
      Int_t ist = part->GetStatusCode(); //obtenemos su estatus
      Int_t pdg = part->GetPdgCode(); // y su codigo PDG

      //1. Introducir una codicion para separar los muones
      if ( (pdg == 13 || pdg == -13) && ( ist > 0 ) ) {

      //Queremos graficar el momento Transverso de los muones Pt == Sqrt(px*px + py*py)
      //2. Obtener aqui las componentes Px y Py del momento de las particulas

	float px = part->Px();
        float py = part->Px();
        float Pt = sqrt(px*px + py*py);

      //3. Llenar el histograma h1 con el momento transversar
      h1->Fill( Pt );
      
      } // cerrar el condicional que se introdujo


    } // No olvidar! cerrar el loop que hemos introducido 


    tree->Fill();
    
  }
  
  pythia8->PrintStatistics();

  // Ahora podemos dibujar el histograma y que lo muestre en pantalla
  h1->Draw();

  outfile->Write();
  
}
