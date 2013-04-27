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
  double R = 0.2;
  fastjet::JetDefinition jet_def(fastjet::kt_algorithm, R);

  //Definir aqui los histogramas del analisis
  TH1F * h_JetPt = new TH1F("JetsPt","Momento transversal de Jets ",50, 0, 100);
  TH1F * h_NJets = new TH1F("NJets","Numero de Jets por evento",50, 0, 15);
  //Ejercicio 4
  TH1F * h_JetInv = new TH1F("JetsInv","Masa invariante de Jets 1 y 2 ",50, 100, 150);

  //Inicia el Ciclo sobre eventos simulados
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    int np = 0;
    int max_part = particles_; //Maximo numero de particulas
    
    // Definir un contenedor de Particulas para pasarle a FastJet
    std::vector<fastjet::PseudoJet> particles;
    
    //Implementar aqui el analisis
    while ( np < max_part )  {
      
      //llenar aqui con las particulas estables: estas particulas serian aquellas que no tienen hijas

      if ( (particles_fDaughter[np][0] == -1) && (particles_fDaughter[np][1] == -1) ) 
      {

        bool isDetectable = true;

        //Crear un 4-vector para cada una de las particulas - necesitamos calcular el eta 
        TLorentzVector partVec( particles_fPx[np], particles_fPy[np], particles_fPz[np], particles_fE[np] );
        float eta = partVec.Eta();

        if ( abs (particles_fPdgCode[np]) == 12 || 
	     abs (particles_fPdgCode[np]) == 14 || 
	     abs (particles_fPdgCode[np]) == 16 || 
             abs (particles_fPdgCode[np]) == 13 || 
             abs ( eta ) > 2.4    )
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

    int njets = jets.size();

    h_NJets->Fill( njets );

    for (int i = 0; i < njets; i++) {

      h_JetPt->Fill( jets[i].perp() );
      
    }

    //Ejercicio 4 - Masa invariante de jets

    //Ordenar de mayor a menor segun momento transversal
    std::vector<fastjet::PseudoJet> ord_jets  =  sorted_by_pt( jets );

    // Definir dos 4-vectores

    TLorentzVector jetOne;
    TLorentzVector jetTwo;   

    // Por seguridad, solo consideramos eventos en los que se reconstruyen 2 o mas jets
    if( njets >= 2 ) {

    jetOne.SetPxPyPzE( ord_jets[0].px(), ord_jets[0].py(), ord_jets[0].pz(), ord_jets[0].e() );
    jetTwo.SetPxPyPzE( ord_jets[1].px(), ord_jets[1].py(), ord_jets[1].pz(), ord_jets[1].e() );

    TLorentzVector combVector = (jetOne + jetTwo);
    
    float invMass = combVector.M();  

    h_JetInv->Fill(invMass);

    }

    jets.clear(); //Limpiar el contenedor de jets y particulas en preparacion para el proximo evento
    particles.clear();
    ord_jets.clear();

    
  }//cierra loop sobre eventos 
 
  ///Un Canvas nos define un area en donde colocar objetos graficos
  TCanvas * c1 = new TCanvas();
  c1->Divide(2,2);
  c1->SetFillColor(10);
  c1->Draw();

  // Dibujar la distribucion de numero de Jets por evento
  
  c1->cd(1);
  h_NJets->Draw();

  // Dibujar la distribucion de momento transversal
  
  c1->cd(2);
  h_JetPt->Draw();

  //Ejercicio 4 - Masa invariante de Jets
  c1->cd(3);
  h_JetInv->Draw();
    
  c1->cd();
  //termina Loop() limpiar memoria

  

}

