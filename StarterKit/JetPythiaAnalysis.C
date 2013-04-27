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
JetPythiaAnalysis::JetPythiaAnalysis( const char * fname, const char * opt, int type ) : PythiaAnalysis(fname,opt,type) {
  
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
  
  //Aqui se crea el contenedor para almacenar los Z0
  TList *v_Z0 = new TList();
  TList *v_Muons = new TList();
  
  std::cout << "nevts: " << nentries << std::endl;
  
  // choose a jet definition
  double R = 0.7;
  fastjet::JetDefinition jet_def(fastjet::kt_algorithm, R);
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    int np = 0;
    int max_part = particles_;
    std::vector<fastjet::PseudoJet> particles;

    std::cout << "evt: " << jentry << std::endl;
    
    //Implementar aqui el analisis
    while ( np < max_part )  {
      
      //fill with all stable particles

      if ( (particles_fDaughter[np][0] == -1) && (particles_fDaughter[np][1] == -1) ) 
      {
        
        particles.push_back( fastjet::PseudoJet( particles_fPx[np], 
                                                 particles_fPy[np],
                                                 particles_fPz[np],
                                                 particles_fE[np] ) );
      
      }
      
      ++np;
      
    }
     
    std::cout << particles.size() << std::endl;
    if ( particles.size() <= 0 )
      continue;
    
    // run the clustering, extract the jets
    fastjet::ClusterSequence cs(particles, jet_def);
    std::vector<fastjet::PseudoJet> jets = cs.inclusive_jets();
    
    // print the jets
    std::cout <<   "        pt y phi" << std::endl;
    for (unsigned i = 0; i < jets.size(); i++) {
      std::cout << "jet " << i << ": "<< jets[i].perp() << " " 
           << jets[i].rap() << " " << jets[i].phi() << endl;
      m_root_out->h_JetPt->Fill( jets[i].perp() );
      
    }

    std::cout << "-------";
    jets.clear();
    particles.clear();
    std::cout << " // -------" << std::endl;

    
  }//cierra loop sobre eventos  
   
  
  //termina Loop() limpiar memoria:
  delete v_Z0;
  delete v_Muons;
  

}

