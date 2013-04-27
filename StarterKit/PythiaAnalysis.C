#define PythiaAnalysis_cxx

#include "PythiaAnalysis.h"

void PythiaAnalysis::Loop()
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  //Aqui se crea el contenedor para almacenar los Z0
  TList *v_Z0 = new TList();
  TList *v_Muons = new TList();
  
  std::cout << "nevts: " << nentries << std::endl;

  // Empieza loop sobre eventos  

  //nentries = 10;

  for (Long64_t jentry=0; jentry<nentries;jentry++) { 

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //Implementar aqui el analisis
    

    
  }//cierra loop sobre eventos  
   
  
  
  //termina Loop() limpiar memoria:
  delete v_Z0;
  delete v_Muons;

}

int PythiaAnalysis::GetMotherId( int index ) {

  int current_Pdg = particles_fPdgCode[index]; //por ejemplo muon= 13,-13

  int mother_Id = -1;

  while( 1 ) {
    
    int mother_pos_1 = particles_fMother[index][0];
    
    mother_Id = particles_fPdgCode[mother_pos_1];

    if ( mother_Id != current_Pdg) { 
      break;
    } else { index = mother_pos_1; };

    int mom_daug1 =  particles_fDaughter[mother_pos_1][0];
    int mom_daug2 =  particles_fDaughter[mother_pos_1][1];
    
    if ( mom_daug1 != mom_daug2 ) {
      mother_Id = GetMotherId( mother_pos_1 );
      break;
    }
    
  }
  
  return mother_Id;
  
}



