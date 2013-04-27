#define PythiaAnalysis_cxx

#include "PythiaAnalysis.h"

void PythiaAnalysis::Loop()
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  //Adicionar un histograma hacer una distribucion de masa invariante de muones
  TH1F * h1 = new TH1F("mumuInv","Masa invariante de muones", 120, 0, 120);

  // Empieza loop sobre eventos  
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //Implementar aqui el analisis
    
    int maxpart = particles_; //maxpart contiene el numero maximo de particulas

    //Definimos dos 4-vectores (px,py,pz,E) para guardar la informacion de los DOS muones por evento
    TLorentzVector muonOne;
    TLorentzVector muonTwo;    

    for (int i = 0; i < maxpart; ++i ) 
    {
      
	//La condicion debe seleccionar solo muones y que estos sean estables
 	if ( particles_fPdgCode[i] == 13 && (particles_fDaughter[i][0] == -1) && (particles_fDaughter[i][1] == -1) )
		muonOne.SetPxPyPzE(particles_fPx[i],particles_fPy[i],particles_fPz[i],particles_fE[i]);
	
        //La condicion debe seleccionar solo muones y que estos sean estables
	if ( particles_fPdgCode[i] == -13 && (particles_fDaughter[i][0] == -1) && (particles_fDaughter[i][1] == -1) )
		muonTwo.SetPxPyPzE(particles_fPx[i],particles_fPy[i],particles_fPz[i],particles_fE[i]);

    } //Este cierra el Loop sobre particulas en 1 evento
    
    //Ahora podemos combinar los dos 4-vectores y calcular la masa invariante E*E - (Px*Px+Py*Py+Pz*Pz)

    TLorentzVector combVector = (muonOne + muonTwo);
    
    float invMass = combVector.M();  

    h1->Fill(invMass);
    
  }//cierra loop sobre eventos  
   
  //Graficar el histograma
  h1->Draw();
    
  //termina Loop() 
  
}





