// $Id: $
// Include files 

// local

//-----------------------------------------------------------------------------
// Implementation file for class : GuiHistoRates
//
// 2010-03-03 : Andres Osorio
//-----------------------------------------------------------------------------

#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include "TAxis.h"

#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>
#include <TGFrame.h>
#include <TGLayout.h>
#include <TGWindow.h>
#include <TGLabel.h>
#include <TString.h>

#include "GuiHistoRates.h"

GuiHistoRates::GuiHistoRates(const TGWindow *p,UInt_t w,UInt_t h) : HistoRates() {
  
  // Create a main frame
  fMainA = new TGMainFrame(p,w,h);
  
  fMainB = new TGMainFrame(p,w,h);
  
  // Create canvas widget
  fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMainA,500,300);
  
  fMainA->AddFrame(fEcanvas, new TGLayoutHints( kLHintsExpandX | kLHintsExpandY,
                                                10,10,10,15));
  
  //Control buttons
  TGHorizontalFrame *hframe = new TGHorizontalFrame(fMainA, 70, 100);
  
  fCheckb[0] = new TGCheckButton( hframe , new TGHotString("Set Log"), IDs.GetUnID());
  fCheckb[0]->Connect("Toggled(Bool_t)", "GuiHistoRates", this, "SetLogScale(Bool_t)");
  
  hframe->AddFrame(fCheckb[0], new TGLayoutHints(kLHintsCenterX,5,5,3,4));
  
  fMainA->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
  
  //Wheel Selection Option

  fCheckb[1] = new TGCheckButton(hframe, new TGHotString("All Wheels"), IDs.GetUnID());
  
  hframe->AddFrame(fCheckb[1], new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
  
  fButtonGroup = new TGVButtonGroup(hframe, "Please Select");
  fCheckW[0] = new TGCheckButton(fButtonGroup, "WM2", IDs.GetUnID());
  fCheckW[1] = new TGCheckButton(fButtonGroup, "WM1", IDs.GetUnID());
  fCheckW[2] = new TGCheckButton(fButtonGroup, "W00", IDs.GetUnID());
  fCheckW[3] = new TGCheckButton(fButtonGroup, "WP1", IDs.GetUnID());
  fCheckW[4] = new TGCheckButton(fButtonGroup, "WP2", IDs.GetUnID());

  ULong_t bcolor, ycolor;
  gClient->GetColorByName("#009900", bcolor);
  fCheckW[0]->SetTextColor(bcolor);
  gClient->GetColorByName("#ff00ff", bcolor);
  fCheckW[1]->SetTextColor(bcolor);
  gClient->GetColorByName("#0000ff", bcolor);
  fCheckW[2]->SetTextColor(bcolor);
  gClient->GetColorByName("#ff0000", bcolor);
  fCheckW[3]->SetTextColor(bcolor);
  gClient->GetColorByName("#00ff00", bcolor);
  fCheckW[4]->SetTextColor(bcolor);
    
  fButtonGroup->Show();

  hframe->AddFrame(fButtonGroup, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 1, 1, 1, 1));

  fCheckb[1]->Connect("Toggled(Bool_t)", "GuiHistoRates", this, "SetGroupEnabled(Bool_t)");
  fCheckb[1]->SetOn();

  fButtonGroup->SetState(kFALSE);
  
  for(int i=0; i<5; ++i)
    fCheckW[i]->SetOn();

  fCheckW[0]->Connect("Toggled(Bool_t)", "GuiHistoRates", this, "SelectWM2(Bool_t)");
  fCheckW[1]->Connect("Toggled(Bool_t)", "GuiHistoRates", this, "SelectWM1(Bool_t)");
  fCheckW[2]->Connect("Toggled(Bool_t)", "GuiHistoRates", this, "SelectW00(Bool_t)");
  fCheckW[3]->Connect("Toggled(Bool_t)", "GuiHistoRates", this, "SelectWP1(Bool_t)");
  fCheckW[4]->Connect("Toggled(Bool_t)", "GuiHistoRates", this, "SelectWP2(Bool_t)");

    
  //..............................................................................

  // Exit button
  //TGTextButton *exit = new TGTextButton(hframe,"&Exit", "gApplication->Terminate(0)");
  TGTextButton *exit = new TGTextButton(hframe,"&Exit");
  exit->Connect("Clicked()","GuiHistoRates",this,"Terminate()");
  
  
  hframe ->AddFrame(exit,new TGLayoutHints(kLHintsCenterX, 8, 5, 3, 4));
  
  fDcanvas = new TRootEmbeddedCanvas("Dcanvas",fMainB,700,500);
  
  fMainB->AddFrame(fDcanvas, new TGLayoutHints( kLHintsExpandX | kLHintsExpandY,
                                                10,10,10,1));
  
  fScanvas = fDcanvas->GetCanvas();
  fScanvas->Divide(3,4);
  fScanvas->SetFillColor(10);
  fScanvas->Draw();
  

  // Set a name to the main frame
  fMainA->SetWindowName("Wheel Rates");
  // Map all subwindows of main frame
  fMainA->MapSubwindows();
  // Initialize the layout algorithm
  fMainA->Resize(fMainA->GetDefaultSize());
  // Map main frame
  fMainA->MapWindow();

  // Set a name to the main frame
  fMainB->SetWindowName("Wheel Rates");
  // Map all subwindows of main frame
  fMainB->MapSubwindows();
  // Initialize the layout algorithm
  fMainB->Resize(fMainB->GetDefaultSize());
  // Map main frame
  fMainB->MapWindow();

  m_terminate = false;
    
}

void GuiHistoRates::DoDraw( TtuRates * input ) {
  
  
  addTime( input->Time );
  
  for( int i=0; i < 5; ++i) 
  {
    addwheelRate( i, input->RateByWheel[i]);
  }
  
  TCanvas *fCanvas = fEcanvas->GetCanvas();
  fCanvas->SetFillColor(10);
  fCanvas->Update();
  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetGridy();

  if ( this->m_logscale == true)
    fCanvas->SetLogy();
  else
    fCanvas->SetLogy(0);

  fCanvas->Update();
  
  this->DrawWheelRates( fCanvas );
  
  ///////////////////////////////////////////////////////////////////////
    
  fCanvas = fDcanvas->GetCanvas();
  fCanvas->SetFillColor(10);
  
  addsectorRates( input->RateBySectorWM2,
                  input->RateBySectorWM1,
                  input->RateBySectorW00,
                  input->RateBySectorWP1,
                  input->RateBySectorWP2 );

  this->DrawSectorRates( fCanvas, this->m_logscale);
    
   fCanvas->cd();
   fCanvas->Update();

   ///////////////////////////////////////////////////////////////////////

}

void GuiHistoRates::SetLogScale(Bool_t on)
{
  if (on) this->m_logscale = true;
  else this->m_logscale = false;
  
}


void GuiHistoRates::SetGroupEnabled(Bool_t on)
{

  fButtonGroup->SetState(!on);
  for(int i=0; i<5; ++i)
    fCheckW[i]->SetOn();

  if( on ) 
  {
    this->m_selectedWheel.reset();
    this->m_selectedWheel.flip();
  }
  
}

///////////////////////////////////////////
//wheel masks!
void GuiHistoRates::SelectWM2(Bool_t on)
{

  if (on)
    this->m_selectedWheel.set(4,1);
  else
    this->m_selectedWheel.set(4,0);
    
}

void GuiHistoRates::SelectWM1(Bool_t on)
{

  if (on)
    this->m_selectedWheel.set(3,1);
  else
    this->m_selectedWheel.set(3,0);

}

void GuiHistoRates::SelectW00(Bool_t on)
{

  if (on)
    this->m_selectedWheel.set(2,1);
  else
    this->m_selectedWheel.set(2,0);

}

void GuiHistoRates::SelectWP1(Bool_t on)
{

  if (on)
    this->m_selectedWheel.set(0,1);
  else
    this->m_selectedWheel.set(0,0);

}

void GuiHistoRates::SelectWP2(Bool_t on)
{

  if (on)
    this->m_selectedWheel.set(1,1);
  else
    this->m_selectedWheel.set(1,0);

}

void GuiHistoRates::Terminate()
{

  m_terminate = true;
  m_exitCode = 0;
  
}

/////////////////////////////////////////////////////////

GuiHistoRates::~GuiHistoRates() {
  fMainA->Cleanup();
  delete fMainA;

  fMainB->Cleanup();
  delete fMainB;

}

