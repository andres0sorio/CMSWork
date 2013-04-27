void pythia8_susy() {
  
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
  
  // Configure    
  pythia8->ReadString("SUSY:All = on");
  //pythia8->ReadString("SUSY:qqbar2chi+-chi0 = on");

  pythia8->ReadString("SLHA:file = SUSY_LM2_sftsht.slha");

  // Initialize 
  
  pythia8->Initialize(2212 /* p */, 2212 /* p */, 7000. /* TeV */);
  
  int iev = 0;

  //Declaramos y definimos un apuntador a un Histograma
  //Este histograma nos mostrara la distribucion de momento transversal Pt de los muones en el eventos
  //Quitar el comentario y escribir el numero de bins, xmin, xmax para el histograma  

  TH1F * h1 = new TH1F("hpt", "Muons Pt", 50, 0, 100);

  // Event loop
  while( iev < maxEvts ) {
    
    pythia8->GenerateEvent();
    if (iev < 1) pythia8->EventListing();
    pythia8->ImportParticles(particles,"All");
    
    Int_t np = particles->GetEntriesFast();
    
    // Particle loop
    
    for (Int_t ip = 0; ip < np; ip++) {
      
      //Leemos informacion de cada particula

      TParticle* part = (TParticle*) particles->At(ip); //Esta es la particula i
      Int_t ist = part->GetStatusCode(); //obtenemos su estatus
      Int_t pdg = part->GetPdgCode(); // y su codigo PDG
      
      //1 Introducir una codicion para separar los muones
      
      if ( pdg == 13 || pdg == -13 ) {
      
	//Queremos graficar el momento Transverso de los muones Pt == Sqrt(px*px + py*py)
        //2. Obtener aqui las componentes Px y Py del momento de las particulas

        float px = part->Px();
        float py = part->Px();
        float Pt = sqrt(px*px + py*py);

        //3. Llenar el histograma h1 con el momento transversar
        h1->Fill( Pt );
      
    } ///no olvidar! cerrar el condicional

   }
   
    tree->Fill();

    ++iev;
         
  }
    
  // Ahora podemos dibujar el histograma y que lo muestre en pantalla
  h1->Draw();
  
  pythia8->PrintStatistics();
  
  outfile->Write();
     
}

