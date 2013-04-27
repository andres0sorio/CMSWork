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



  //Definir aqui los histogramas del analisis


  //Ejercicio 4


  //Inicia el Ciclo sobre eventos simulados
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    int np = 0;
    int max_part = particles_; //Maximo numero de particulas
    
    // Definir un contenedor de Particulas para pasarle a FastJet

    
    //Implementar aqui el analisis
    while ( np < max_part )  {
      
      //llenar aqui con las particulas estables: estas particulas serian aquellas que no tienen hijas

      
      
      ++np;
      
    }
     
    
    
    
    // Corremos ahora FastJet: hacer sobre las particulas la identificacion de Jets


    // Objeto Cluster contiene los jets: podemos guardarlos en un contenedor de Jets


   
    // Ahora podemos hacer un ciclo sobre los jets reconstruidos y extraer el momento transversal
    // - llenar histograma

    

    //Ejercicio 4 - Masa invariante de jets

    //Ordenar de mayor a menor segun momento transversal


    // Definir dos 4-vectores


    // Por seguridad, solo consideramos eventos en los que se reconstruyen 2 o mas jets
    
    
  }//cierra loop sobre eventos 
 
  ///Un Canvas nos define un area en donde colocar objetos graficos
  TCanvas * c1 = new TCanvas();
  c1->Divide(2,2);
  c1->SetFillColor(10);
  c1->Draw();

  // Dibujar la distribucion de numero de Jets por evento
  


  // Dibujar la distribucion de momento transversal
  


  //Ejercicio 4 - Masa invariante de Jets


    
  c1->cd();
  //termina Loop() limpiar memoria

  

}

