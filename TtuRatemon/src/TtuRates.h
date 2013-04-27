//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Feb 28 17:34:40 2010 by ROOT version 5.22/00
// from TTree TtuRates/Ttu rates
// found on file: tturates.root
//////////////////////////////////////////////////////////

#ifndef TtuRates_h
#define TtuRates_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "TrigRates.h"
#include "HistoRates.h"
#include "TCanvas.h"

class TtuRates {
public :

  enum iomode {in=0 , out=1};

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Int_t           Run;
  Int_t           Lumi;
  ULong64_t       Orbit;
  ULong64_t       Time;
  Int_t           nWheels;
  Float_t         RateByWheel[5];   //[nWheels]
  Int_t           nSectors;
  Float_t         RateBySectorWM2[12];   //[nSectors]
  Float_t         RateBySectorWM1[12];   //[nSectors]
  Float_t         RateBySectorW00[12];   //[nSectors]
  Float_t         RateBySectorWP1[12];   //[nSectors]
  Float_t         RateBySectorWP2[12];   //[nSectors]
  
  // List of branches
  TBranch        *b_Run;   //!
  TBranch        *b_Lumi;   //!
  TBranch        *b_Orbit;   //!
  TBranch        *b_Time;   //!
  TBranch        *b_nWheels;   //!
  TBranch        *b_RateByWheel;   //!
  TBranch        *b_nSectors;   //!
  TBranch        *b_RateBySectorWM2;   //!
  TBranch        *b_RateBySectorWM1;   //!
  TBranch        *b_RateBySectorW00;   //!
  TBranch        *b_RateBySectorWP1;   //!
  TBranch        *b_RateBySectorWP2;   //!
  
  TtuRates( TFile * );
  TtuRates( const char * option );

  virtual ~TtuRates();
  
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  
  virtual void     Loop();
  virtual void     Book();
  virtual void     Fill( TrigRates * );
  
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  TFile * m_output;
  
  std::string m_option;

  bool hasStop;
  
  HistoRates * m_plots;

  int m_iomode;
  
  float m_factor;
  
  TCanvas * m_canvasW;

  TCanvas * m_canvasS;

  TCanvas * m_canvasS1;

  TCanvas * m_canvasP1;

  
            
  bool m_debug;

};

#endif

