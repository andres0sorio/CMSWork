#ifndef BASICOUTPUT_H
#define BASICOUTPUT_H

#include "CommonIncludes.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TNamed.h>
#include <TObjArray.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TPaveLabel.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TString.h>

#include <sys/stat.h>
#include <sys/unistd.h>

class BasicOutput {
  
private:
  
  const char * dir_name;
  
  TObjArray  * histograms;
  
public:
  
  ////////////////////////////////////////////////////  
  //...

  TH1D *njets;
  TH1D *jets_energy;
  TH1D *jets_high_energy;
  TH2D *jets_phieta;

  //...
  
  TH1D *nv;
  TH1D *nv2;
  TH1D *nv4;
  TH1D *etjetratio[3];
  
  //...
  
  TH2D *etmiss_nv;
  TH2D *dphi1_nv;
  TH2D *dphi2_nv;
  TH2D *dphi3_nv;
  TH2D *dphi4_nv;
  
  TH2D *etjet_dphi1;
  TH2D *etjet_dphi2;
  
  TH2D *etjet_nv;
  
  TH2D *etjet2_dphi2;
  TH2D *etjet1_dphi1;
  TH2D *etjet2_dphi12;
  
  
  // End of histogram declaration 
  ////////////////////////////////////////////////////
  
  BasicOutput() { };
  
  BasicOutput(const char *name);
  
  ~BasicOutput();
  
  void addObject(TObject *);
  
  //void scaleHistograms(double factor);
  
};

#endif
