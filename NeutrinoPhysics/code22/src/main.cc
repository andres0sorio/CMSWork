// $Id: 
// Include files 

#include <RootCommon.h>
#include <DensityModels.h>
#include <sstream>
#include "sys/stat.h"
#include <map>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <TAxis.h>

int main(int iargv, char **argv) {
  
  //.........................................................................................
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  c1->SetFillColor(10);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->Draw();
  c1->cd();
   
  // 

  std::map<std::string,DensityModels*> m_Models;
  
  m_Models["ModelA"] = (DensityModels*) new rhoModelA();
  m_Models["ModelB"] = (DensityModels*) new rhoModelB();
  m_Models["ModelC"] = (DensityModels*) new rhoModelC();

  DensityModels * density_Mod = m_Models["ModelA"];

  double LMAX  = 1.61e+17;
  double LMIN  = 3.202e+15;
  
  double k0 = 3.02e-19;
  double lmax = 1.61e+17;
  
  int maxpars = 2;
  
  TF1 * profA = new TF1("profA", density_Mod, LMIN, LMAX, maxpars);
  
  profA->SetParameter( 0 ,   k0);
  profA->SetParameter( 1 ,   lmax);
  
  density_Mod = m_Models["ModelB"];

  maxpars = 5;
  
  TF1 * profB = new TF1("profB", density_Mod, LMIN, LMAX, maxpars);
  
  double kB = 2.57e-18;
  double RstarCM = 3.16e12;
  double RbCM = 1.0e12;
  double Rmin = 3.202e+15;
  double cfact = 5.076e+4;

  profB->SetParameter( 0 , kB );
  profB->SetParameter( 1 , RstarCM );
  profB->SetParameter( 2 , RbCM );
  profB->SetParameter( 3 , Rmin );
  profB->SetParameter( 4 , cfact );
  
  density_Mod = m_Models["ModelC"];

  maxpars = 9;

  TF1 * profC = new TF1("profC", density_Mod, LMIN, LMAX, maxpars);
  
  double KC = 4.76e-19;
  RstarCM = 3.16e12; //cm
  RbCM = 1.0e11; //cm
  Rmin = 3.202e+15; // 1oeV
  double A1 = 20.0;
  double neff1 = 2.1;
  double A2 = 1.0;
  double neff2 = 2.5;
  cfact = 5.076e+4;

  profC->SetParameter( 0 ,   KC);
  profC->SetParameter( 1 ,   RstarCM);
  profC->SetParameter( 2 ,   RbCM);
  profC->SetParameter( 3 ,   Rmin);
  profC->SetParameter( 4 ,   A1);
  profC->SetParameter( 5 ,   neff1);
  profC->SetParameter( 6 ,   A2);
  profC->SetParameter( 7 ,   neff2);
  profC->SetParameter( 8 ,   cfact);
  
  c1->cd();
  c1->SetLogx();
  c1->SetLogy();

  profA->SetLineColor(1);
  profA->Draw();
  profB->SetLineColor(1);
  profB->SetLineStyle(2);
  profB->Draw("same");
  profC->SetLineColor(4);
  profC->SetFillColor(10);
  profC->SetLineStyle(3);
  profC->Draw("same");

  c1->Print("c1.eps");
  c1->Print("c1.pdf");

  /*
    profB->SetLineColor(1);
    profB->SetFillColor(10);
    profB->GetXaxis()->SetTitle("L (1/eV)");
    profB->GetXaxis()->CenterTitle(true);
    profB->GetXaxis()->SetLabelFont(42);
    profB->GetXaxis()->SetLabelSize(0.035);
    profB->GetXaxis()->SetTitleSize(0.035);
    profB->GetXaxis()->SetTitleFont(42);
    profB->GetYaxis()->SetTitle("A");
    profB->GetYaxis()->CenterTitle(true);
    profB->GetYaxis()->SetLabelFont(42);
    profB->GetYaxis()->SetLabelSize(0.035);
    profB->GetYaxis()->SetTitleSize(0.035);
    profB->GetYaxis()->SetTitleFont(42);
  */
  
  
  /*
    TLegend * leg = new TLegend(0.69,0.77,0.98,0.96);
    leg->AddEntry( profA,"Model A-Ohlsson");
    leg->AddEntry( profB,"Model B-Garcia");
    leg->AddEntry( profC,"Earch C-Ohlsson corrected");
    leg->Draw();
  */
  
  
  //.........................................................................................

  return 0;
  
}
