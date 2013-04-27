// $Id: $
// Include files 



// local
#include "Histograms.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Histograms
//
// 2012-01-30 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Histograms::Histograms( const char * outfname ) {

  outfile = new TFile( outfname, "RECREATE");
  outfile->cd();

  h_partMultip = new TH1F("multiplicity","Final states multiplicity",100,0,200);
  h_stats = new TH1F("stats","Some counting plots",100,0,10);
  h_istate_eta = new TH1F("initial.states.eta","Initial states eta", 50, -4.0, 4.0);
  h_istate_pt = new TH1F("initial.states.pt","Initial states pt", 100, 0.0, 1000);
  h_fstate_eta = new TH1F("final.states.eta","Final states eta", 50, -4.0, 4.0);
  h_fstate_pt = new TH1F("final.states.pt","Final states pt", 100, 0.0, 500);
  h_lsp_eta = new TH1F("lsp.eta","LSPs (chi_10) eta x2", 50, -4.0, 4.0);
  h_lsp_pt = new TH1F("lsp.pt","LSPs (chi_10) pt x2", 100, 0.0, 1000);

  SetHistogramOptions();
  
}
//=============================================================================
// Destructor
//=============================================================================
Histograms::~Histograms() {
  
  outfile->Write();
  outfile->Close();
  
} 

//=============================================================================
void Histograms::SetHistogramOptions()
{

  h_istate_eta->GetXaxis()->SetTitle("#eta");
  h_istate_eta->GetXaxis()->CenterTitle(true);

  h_istate_pt->GetXaxis()->SetTitle("Pt [GeV/c]");
  h_istate_pt->GetXaxis()->CenterTitle(true);

  h_fstate_eta->GetXaxis()->SetTitle("#eta");
  h_fstate_eta->GetXaxis()->CenterTitle(true);

  h_fstate_pt->GetXaxis()->SetTitle("Pt [GeV/c]");
  h_fstate_pt->GetXaxis()->CenterTitle(true);

  h_lsp_eta->GetXaxis()->SetTitle("#eta");
  h_lsp_eta->GetXaxis()->CenterTitle(true);
  
  h_lsp_pt->GetXaxis()->SetTitle("Pt [GeV/c]");
  h_lsp_pt->GetXaxis()->CenterTitle(true);

}
