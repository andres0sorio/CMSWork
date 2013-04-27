#define PythiaAnalysis_cxx

#include "PythiaAnalysis.h"

void PythiaAnalysis::Loop()
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  //Adicionar un histograma para contar el numero de muones
  TH1F * h1 = new TH1F("nmu","Muones por evento", 30, 0, 15);

  // Empieza loop sobre eventos  
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //Implementar aqui el analisis
    
    int maxpart = particles_; //maxpart contiene el numero maximo de particulas
    int n_muons = 0;
    
    for (int i = 0; i < maxpart; ++i ) 
    {
      
      if( abs( particles_fPdgCode[i] ) == 13 )
        ++n_muons;
      
    }
    
    h1->Fill(n_muons);
    
  }//cierra loop sobre eventos  
   
  //Graficar el histograma del numero de muones por evento
  h1->Draw();
    
  //termina Loop() 
  
}





