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
Graphics::Graphics(  ) {

  g1 = new TGraph();
  g2 = new TGraph();
  g3 = new TGraph();
  g4 = new TGraph();

  tleg_1 = new TLegend(0.51, 0.80, 0.85, 0.89, NULL, "brNDC");

  tleg_2 = new TLegend(0.51, 0.80, 0.85, 0.89, NULL, "brNDC");
  
  txtci = TColor::GetColor("#333333");
    
}

//=============================================================================
// Destructor
//=============================================================================

Graphics::~Graphics() {} 

//=============================================================================
void Graphics::SetOptions() {

  TH1F * h1 = g1->GetHistogram();
  h1->SetXTitle("#nu_e fraction");
  g1->GetXaxis()->SetLabelSize(0.03);
  g1->GetXaxis()->SetTitleFont(22);
    
  h1->SetYTitle("R=Tracks/Showers");
  g1->GetYaxis()->SetLabelSize(0.03);
  g1->GetYaxis()->SetTitleOffset(1.09);
  g1->GetYaxis()->SetTitleFont(22);
  
  h1->SetFillColor(10);
  g1->SetFillColor(10);
  
  h1->SetTitle("");
  
  h1 = g2->GetHistogram();
  h1->SetXTitle("#nu_e fraction");
  g2->GetXaxis()->SetLabelSize(0.03);
  g2->GetXaxis()->SetTitleFont(22);
   
  h1->SetYTitle("R=Tracks/Showers");
  g2->GetYaxis()->SetLabelSize(0.03);
  g2->GetYaxis()->SetTitleOffset(1.09);
  g2->GetYaxis()->SetTitleFont(22);
  
  h1->SetFillColor(10);
  g2->SetFillColor(10);
  h1->SetTitle("");
  
  g1->SetLineColor(1);
  g1->SetLineStyle(1);
  g1->SetLineWidth(1.4);

  g2->SetLineColor(2);
  g2->SetLineStyle(2);
  g2->SetLineWidth(1.4);

  tleg_1->SetBorderSize(0);
  tleg_1->SetTextFont(22);
  tleg_1->SetTextSize(0.04);
  tleg_1->SetLineColor(1);
  tleg_1->SetLineStyle(1);
  tleg_1->SetLineWidth(1);
  tleg_1->SetFillColor(0);
  tleg_1->SetFillStyle(1001);
  tleg_1->SetTextColor(txtci);

  tleg_1->AddEntry(g1,"all tracks contribution");
  tleg_1->AddEntry(g2,"no #tau-tracks contribution");
  
  /////////////////////////////////////////////////////////

  h1 = g3->GetHistogram();
  h1->SetXTitle("Spectral index (#alpha)");
  g3->GetXaxis()->SetLabelSize(0.03);
  g3->GetXaxis()->SetTitleFont(22);
  
  h1->SetYTitle("R=Tracks/Showers");
  g3->GetYaxis()->SetLabelSize(0.03);
  g3->GetYaxis()->SetTitleOffset(1.09);
  g3->GetYaxis()->SetTitleFont(22);

  
  h1->SetFillColor(10);
  g3->SetFillColor(10);
  h1->SetTitle("");

  h1 = g4->GetHistogram();
  h1->SetXTitle("Spectral index (#alpha)");
  g4->GetXaxis()->SetLabelSize(0.03);
  g4->GetXaxis()->SetTitleFont(22);
  
  h1->SetYTitle("R=Tracks/Showers");
  g4->GetYaxis()->SetLabelSize(0.03);
  g4->GetYaxis()->SetTitleOffset(1.09);
  g4->GetYaxis()->SetTitleFont(22);

  h1->SetFillColor(10);
  g4->SetFillColor(10);
  h1->SetTitle("");

  g3->SetLineColor(1);
  g3->SetLineStyle(1);
  g3->SetLineWidth(1.4);
  
  g4->SetLineColor(2);
  g4->SetLineStyle(2);
  g4->SetLineWidth(1.4);
 
  tleg_2->SetBorderSize(0);
  tleg_2->SetTextFont(22);
  tleg_2->SetTextSize(0.04);
  tleg_2->SetLineColor(1);
  tleg_2->SetLineStyle(1);
  tleg_2->SetLineWidth(1);
  tleg_2->SetFillColor(0);
  tleg_2->SetFillStyle(1001);
  tleg_2->SetTextColor(txtci);
  
  tleg_2->AddEntry(g3,"all tracks contribution");
  //tleg_2->AddEntry(g4,"no #tau-tracks contribution");

}
