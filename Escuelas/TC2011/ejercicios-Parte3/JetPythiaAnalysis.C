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
  


  //Definir un histograma para el momento transversal de los Jets

  
  //Inicia el Ciclo sobre eventos simulados
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    int np = 0;
    int max_part = particles_; //Maximo numero de particulas

    // Definit un contenedor de Particulas para pasarle a FastJet

    
    //Implementar aqui el analisis
    while ( np < max_part )  {
      
      


      
      ++np;
      
    }
     
    
    
  }//cierra loop sobre eventos  

  // Dibujar la distribucion de momento transversal
    
  //termina Loop() limpiar memoria

 
}

