// $Id: $
// Include files 



// local
#include "Graphics.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Graphics
//
// 2010-09-19 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Graphics::Graphics( const char * outfile ) {

  m_outfile = new TFile( outfile, "RECREATE" );
  m_outfile->cd();
  
  g1[0] = new TGraph();
  g1[0]->SetName("graphFig1");
  
  tleg_1 = new TLegend(0.51, 0.80, 0.85, 0.89, NULL, "brNDC");
  tleg_2 = new TLegend(0.51, 0.80, 0.85, 0.89, NULL, "brNDC");
  
  
}

//=============================================================================
// Destructor
//=============================================================================

Graphics::~Graphics() {
  g1[0]->Write();
  m_outfile->Write();
  m_outfile->Close();
  
} 

//=============================================================================
void Graphics::SetOptions() {

  TH1F * h1 = g1[0]->GetHistogram();
  h1->SetXTitle("x");
  g1[0]->GetXaxis()->SetLabelSize(0.03);
  g1[0]->GetXaxis()->SetTitleFont(22);
  g1[0]->GetXaxis()->SetRange(1.0E-8, 1.0);
  
  
}
