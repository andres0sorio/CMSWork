#define PythiaAnalysis_cxx

#include "PythiaAnalysis.h"

void PythiaAnalysis::Loop()
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  //Adicionar un histograma para contar el numero de muones
  
  // Empieza loop sobre eventos  
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //Implementar aqui el analisis
       
  }//cierra loop sobre eventos  
   
  //Graficar el histograma del numero de muones por evento
      
  //termina Loop() 
  
}





