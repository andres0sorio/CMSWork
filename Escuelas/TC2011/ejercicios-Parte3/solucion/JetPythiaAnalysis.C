// $Id: $
// Include files 



// local
#include "JetPythiaAnalysis.h"

//-----------------------------------------------------------------------------
// Implementation file for class : JetPythiaAnalysis
//
// 2011-03-31 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
JetPythiaAnalysis::JetPythiaAnalysis( const char * fname ) : PythiaAnalysis(fname) {
  
}
//=============================================================================
// Destructor
//=============================================================================
JetPythiaAnalysis::~JetPythiaAnalysis() {} 

//=============================================================================

void JetPythiaAnalysis::Loop()
{
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  //Definir el tipo de Algoritmo para reconstruir Jets y pasarle el parametro requerido
  double R = 0.7;
  fastjet::JetDefinition jet_def(fastjet::kt_algorithm, R);

  //Definir un histograma para el momento transversal de los Jets
  TH1F * h_JetPt = new TH1F("JetsPt","Momento transversal de Jets ",50, 0, 100);
  
  //Inicia el Ciclo sobre eventos simulados
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    int np = 0;
    int max_part = particles_; //Maximo numero de particulas

    // Definit un contenedor de Particulas para pasarle a FastJet
    std::vector<fastjet::PseudoJet> particles;
    
    //Implementar aqui el analisis
    while ( np < max_part )  {
      
      //llenar aqui con las particulas estables: estas particulas serian aquellas que no tienen hijas

      if ( (particles_fDaughter[np][0] == -1) && (particles_fDaughter[np][1] == -1) ) 
      {

        bool isDetectable = true;

        // tenemos que saltarnos aquellas particulas que aun siendo estables, no serian detectables directables
	// 12 = nu_e ; 14 = nu_mu ; 16 = nu_tau ; 10000022 = SUSY LSP / neutrinalino

        if ( abs (particles_fPdgCode[np]) == 12 || 
	     abs (particles_fPdgCode[np]) == 14 || 
	     abs (particles_fPdgCode[np]) == 16 || 
	     abs (particles_fPdgCode[np]) == 10000022 )
			isDetectable = false;

        // lenamos el contenedor con particulas estables
        if( isDetectable ) particles.push_back( fastjet::PseudoJet( particles_fPx[np], 
                          	                                    particles_fPy[np],
                          	                                    particles_fPz[np],
                          	                                    particles_fE[np] ) );
      
      }
      
      ++np;
      
    }
     
    
    if ( particles.size() <= 0 )
      continue;
    
    // Corremos ahora FastJet: hacer sobre las particulas la identificacion de Jets
    fastjet::ClusterSequence Cluster(particles, jet_def);

    // Objeto Cluster contiene los jets: podemos guardarlos en un contenedor de Jets
    std::vector<fastjet::PseudoJet> jets = Cluster.inclusive_jets();
    
    // Ahora podemos hacer un ciclo sobre los jets reconstruidos y extraer el momento transversal
    // - llenar histograma

    for (unsigned i = 0; i < jets.size(); i++) {

      h_JetPt->Fill( jets[i].perp() );
      
    }

    jets.clear(); //Limpiar el contenedor de jets y particulas en preparacion para el proximo evento
    particles.clear();

    
  }//cierra loop sobre eventos  

  // Dibujar la distribucion de momento transversal
  h_JetPt->Draw();
    
  //termina Loop() limpiar memoria

  

}

