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
  
  SetOptions();
  

}
//=============================================================================
// Destructor
//=============================================================================
Graphics::~Graphics() {} 

//=============================================================================
void Graphics::SetOptions() {

  TH1F * h1 = g1->GetHistogram();
  h1->SetXTitle("#nu_e fraction");
  h1->SetYTitle("");
  h1->SetTitle("");
  
  h1 = g2->GetHistogram();
  h1->SetXTitle("#nu_e fraction");
  h1->SetYTitle("");
  h1->SetTitle("");
  
  g1->SetLineColor(2);
  g2->SetLineColor(3);
  
}
