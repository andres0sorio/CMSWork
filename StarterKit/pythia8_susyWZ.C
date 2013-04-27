// Note that before executing this script, 
//   -the env variable PYTHIA8 must point to the pythia8100 (or newer) directoryDATA
//   -the env variable PYTHIA8DATA must be defined and it must point to $PYTHIA8/xmldoc

void pythia8_susyWZ(Int_t nev  = 100, Int_t ndeb = 1) {
  
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
  TFile * outfile = new TFile("eventos_pythia8_SUSYWZa.root","RECREATE");
  
  // Array of particles
  TClonesArray* particles = new TClonesArray("TParticle", 4000);
  
  //Definir el TTree
  TTree*tree= new TTree("tree","Arbol con particulas segun Pythia8");
  tree->Branch("particles",&particles);
  
  // Create pythia8 object
  TPythia8* pythia8 = new TPythia8();
  
  // Configure    
  pythia8->ReadString("SUSY:qqbar2chi+-chi0 = on");
  pythia8->ReadString("SLHA:file = SUSY_LM2_sftsht.slha");

  pythia8->ReadString("PDF:useLHAPDF = on ");
  pythia8->ReadString("PDF:LHAPDFset = cteq6l.LHpdf ");

  // Initialize 
  
   pythia8->Initialize(2212 /* p */, 2212 /* p */, 7000. /* TeV */);
   
   pythia8->ReadString("SUSY:idA        = 1000023");
   pythia8->ReadString("SUSY:idB        = 1000024");

   pythia8->ReadString("1000023:onMode = off");
   pythia8->ReadString("1000024:onMode = off");

   pythia8->ReadString("1000023:onIfMatch = 1000022 23");
   pythia8->ReadString("1000024:onIfMatch = 1000022 24");
   
   //W -> mu  nu_mu
   //pythia8->ReadString("24:onMode = off");
   //pythia8->ReadString("24:onIfMatch = -13 14");

   bool has_1000023 = false;
   bool has_1000024 = false;
   
   int iev = 0;
   
   // Event loop
   //for (Int_t iev = 0; iev < nev; iev++) {
   while( iev < nev ) {
     
     pythia8->GenerateEvent();
     if (iev < ndeb) pythia8->EventListing();
     pythia8->ImportParticles(particles,"All");
     
     Int_t np = particles->GetEntriesFast();
     
     // Particle loop
     
     for (Int_t ip = 0; ip < np; ip++) {
       
       TParticle* part = (TParticle*) particles->At(ip);
       Int_t ist = part->GetStatusCode();
       Int_t pdg = part->GetPdgCode();
       
       //if( abs(pdg) == 1000023 ) 
       //  has_1000023 = true;
         
       if( pdg == 1000023 ) 
         has_1000023 = true;

       //if( pdg == -1000023 ) 
       //  has_1000023 = true;

       if( abs(pdg) == 1000024 )
         has_1000024 = true;
              
       //Float_t charge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge();
       
     }
     
     // keep only events where we have chi1+ and chi20
     if ( has_1000023 && has_1000024 ) 
     {
       tree->Fill();
       ++iev;
     }
     
     has_1000023 = false;
     has_1000024 = false;
        
   }
   
   pythia8->PrintStatistics();
   
   outfile->Write();
   outfile->Close();
   
   
}

