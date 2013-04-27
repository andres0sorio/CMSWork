#define PythiaAnalysis_cxx

#include "PythiaAnalysis.h"

void PythiaAnalysis::Loop()
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  //Adicionar un histograma hacer una distribucion de masa invariante de muones


  // Empieza loop sobre eventos  
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    int maxpart = particles_; //maxpart contiene el numero maximo de particulas

    //Implementar aqui el analisis
    


    //Definimos dos 4-vectores (px,py,pz,E) para guardar la informacion de los DOS muones por evento



    for (int i = 0; i < maxpart; ++i ) 
    {
      


    } //Este cierra el Loop sobre particulas en 1 evento
    
    //Ahora podemos combinar los dos 4-vectores y calcular la masa invariante E*E - (Px*Px+Py*Py+Pz*Pz)


    



    
  }//cierra loop sobre eventos  
   
  //Graficar el histograma

    
  //termina Loop() 
  
}





