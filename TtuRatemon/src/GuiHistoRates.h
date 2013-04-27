// $Id: $
#ifndef GUIHISTORATES_H 
#define GUIHISTORATES_H 1

// Include files
#include <TQObject.h>
#include <RQ_OBJECT.h>

#include "HistoRates.h"
#include "TtuRates.h"
#include "TCanvas.h"
#include <TGButton.h>
#include <TGButtonGroup.h>
#include <sstream>
#include <bitset>

/** @class GuiHistoRates GuiHistoRates.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-03-03
 */

class TGWindow;
class TGMainFrame;
class TRootEmbeddedCanvas;

class IDList {

private:
   Int_t nID;   // creates unique widget's IDs

public:
   IDList() : nID(0) {}
   ~IDList() {}
   Int_t GetUnID(void) { return ++nID; }
};

class GuiHistoRates : public HistoRates{

  RQ_OBJECT("GuiHistoRates")

private:
  
  
  TGMainFrame         *fMainA;
  TGMainFrame         *fMainB;
  IDList               IDs;
  TRootEmbeddedCanvas *fEcanvas;
  TRootEmbeddedCanvas *fDcanvas;
  TCanvas             *fScanvas;
  TGCheckButton       *fCheckb[4];
  TGVButtonGroup      *fButtonGroup;  // Button group
  TGCheckButton       *fCheckW[5];    // Check buttons
  
  Bool_t m_logscale;
  Int_t m_exitCode;
  
  
 public:
  
  GuiHistoRates(const TGWindow *p, UInt_t w, UInt_t h);
  virtual ~GuiHistoRates();
  void DoDraw( TtuRates *);

  void SetLogScale(Bool_t on);
  void SetGroupEnabled(Bool_t);
  
  void SelectWM2(Bool_t on);
  void SelectWM1(Bool_t on);
  void SelectW00(Bool_t on);
  void SelectWP1(Bool_t on);
  void SelectWP2(Bool_t on);

  void Terminate();

  Bool_t m_terminate;
    
};

#endif // GUIHISTORATES_H
