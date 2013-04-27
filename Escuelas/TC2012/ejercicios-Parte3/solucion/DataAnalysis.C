#define DataAnalysis_cxx
#include "DataAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

DataAnalysis::DataAnalysis(const char * fname)
{

  // Cambiar el constructor - preferible que tome como argumento un nombre de archivo
  TTree * tree;
  TFile * f = TFile::Open(fname);
  f->cd(); 
  tree = (TTree*)gDirectory->Get("t1");
  Init(tree);
  
}


void DataAnalysis::Loop()
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   //Mi primer histograma de masa invariante con datos REALES del LHC!!!
   TH1F * h_DiMuonInv = new TH1F("mumuInv","Masa invariante de muones", 120, 0, 120);
   h_DiMuonInv->Sumw2();

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      ///Hacer un loop sobre los muones - necesitamos definir dos 4-vectores para el muon 1 y el muon 2

      TLorentzVector muonOne;
      TLorentzVector muonTwo;

/// el maximo numero de muones en este evento, lo tenemos gracias a la variable nMuons, contenida en el TTree
    int maxMuons = nMuons;

  /// Iniciamos un ciclo con indice i
    
    for( int i = 0; i < maxMuons; ++i) {

      // Necesitamos formar parejas de muones i-j
      //   luego puedo iniciar un ciclo secundario sobre el indice j y que empieze en i+1

      for( int j = (i+1); j < maxMuons; ++j) {

        // condicion: si el indice i es diferente del indice j  -Y-  la carga de los muones es opuesta entonces proceder 
        if ( ( i != j ) && (muons_fC[i] != muons_fC[j] )) {
                    
	// Esto va dentro de la condicion
        muonOne.SetPxPyPzE( muons_fPx[i], muons_fPy[i], muons_fPz[i], muons_fE[i] ); //va con el indice i
        muonTwo.SetPxPyPzE( muons_fPx[j], muons_fPy[j], muons_fPz[j], muons_fE[j] ); //va con el indico j

        TLorentzVector combVector = (muonOne + muonTwo);
        float invMass = combVector.M();  
        h_DiMuonInv ->Fill(invMass);


        } // cerrar la condicion
                
      } // cerrar ciclo sobre las j
      
    } // cerrar cicclo sobre las i
   
   }

   TCanvas *c1 = new TCanvas("c1", "c1",11,281,700,502);
   c1->SetFillColor(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
   
   c1->cd();

   h_DiMuonInv->GetXaxis()->SetTitle("M(#mu^{+}#mu^{-}) [GeV/c^{2}]");
   h_DiMuonInv->GetXaxis()->CenterTitle(true);
   h_DiMuonInv->GetXaxis()->SetTitleFont(42);

   h_DiMuonInv ->Draw();
   
   
}
