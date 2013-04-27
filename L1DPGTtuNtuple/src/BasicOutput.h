#ifndef BASICOUTPUT_H
#define BASICOUTPUT_H

#include "CommonIncludes.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TNamed.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TPaveLabel.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TString.h"

#include <sys/stat.h>
#include <sys/unistd.h>
#include <sstream>
#include <map>

class BasicOutput {
  
private:

  
  const char *dir_name;
  std::string type_of_output;
  TObjArray::TObjArray *output;
  
 public:

  enum {
    MAX_BITS = 8,
    SEL_BITS = 3,
    MAX_MUTRIGS = 10
  };
  
  std::vector<int> m_ttbits;
  std::vector<int> m_selectedBits;
  std::vector<int> m_singleMuBits;
  
  // 1D - Histograms
  std::map< int, TH1D* > pacTTUDiff[MAX_BITS]; // runId, hitograms [ TTBit ]
  std::map< int, TH1D* >  dtTTUDiff[MAX_BITS]; // runId, hitograms [ TTBit ]
  std::map< int, TH1D* >      ttuBx[MAX_BITS]; // runId, hitograms [ TTBit ]
  std::map< int, TH1D* > TechTrigBx; // TTbit, histogram

  
  TH1D * h_GB_muon_Pt;
  TH1D * h_GB_muon_Phi;
  TH1D * h_GB_muon_Eta;
  TH1D * h_GB_caloComp;
    
  TH1D * h_TR_muon_Pt;
  TH1D * h_TR_muon_Phi;
  TH1D * h_TR_muon_Eta;
  TH1D * h_TR_caloComp;

  TH1D * h_SA_muon_Pt;
  TH1D * h_SA_muon_Phi;
  TH1D * h_SA_muon_Eta;

  TH1D * h_TR_muon_d0;
  TH1D * h_GB_muon_d0;

  TH1D * h_TR_muon_d0s;
  TH1D * h_GB_muon_d0s;

  TH1D * h_TR_chi2dof;
  TH1D * h_GB_chi2dof;

  TH1D * h_TR_validHits;
  TH1D * h_GB_validHits;
  
  TH1D * hc_SA_muon_Pt[SEL_BITS];
  TH1D * hc_TR_muon_Pt[SEL_BITS];
  TH1D * hc_GB_muon_Pt[SEL_BITS];
  
  TH1D * hc_SA_muon_Eta[SEL_BITS];
  TH1D * hc_TR_muon_Eta[SEL_BITS];
  TH1D * hc_GB_muon_Eta[SEL_BITS];
  
  TH1D * hc_SA_muon_Phi[SEL_BITS];
  TH1D * hc_TR_muon_Phi[SEL_BITS];
  TH1D * hc_GB_muon_Phi[SEL_BITS];

  TH1D * hc_TR_muon_Calo[SEL_BITS];
  TH1D * hc_GB_muon_Calo[SEL_BITS];
  
  TH1D * hc_TR_muon_d0[SEL_BITS];
  TH1D * hc_GB_muon_d0[SEL_BITS];

  TH1D * hc_TR_muon_d0s[SEL_BITS];
  TH1D * hc_GB_muon_d0s[SEL_BITS];

  TH1D * hc_TR_muon_chi2dof[SEL_BITS];
  TH1D * hc_GB_muon_chi2dof[SEL_BITS];

  TH1D * hc_TR_muon_validHits[SEL_BITS];
  TH1D * hc_GB_muon_validHits[SEL_BITS];
  
  TH1D * h_NRecHit_Evt;

  TH1D * h_NTrTracks_Evt;

  TH1D * hc_NRecHit_Evt[SEL_BITS];
  
  TH1D * h_muTriggBx[MAX_MUTRIGS];
  
  // 2D - Histograms
  TH2D *    pacTTU[MAX_BITS];
  TH2D *     dtTTU[MAX_BITS];
  TH2D * rpcbTTUBx[MAX_BITS];
  TH2D *     bxTTU[MAX_BITS];
  TH2D * h_beamSpot;
  
  TH2D *    hh_etaphi_TR;
  TH2D *    hh_etaphi_TR_Bit[MAX_BITS];
  
  TH2D *    hh_etaphi_GB;
  TH2D *    hh_etaphi_GB_Bit[MAX_BITS];
  
  TH2D *    hh_etaphi_SA;
  TH2D *    hh_etaphi_SA_Bit[MAX_BITS];

  TH2D * ttbitsVsMuTriggers;
  TH2D * ttbitsVsMuTriggers25;

  TH2D * ttbitsVsAlgbits;


  BasicOutput() { };
  BasicOutput(const char *name);
  
  ~BasicOutput();
  
  void book();
  
  void addObject(TObject *);

  void addRunToBXDist( int  );

  void addRunToBXDiff( int  );

  void makeHistory();
  
  
};

#endif
