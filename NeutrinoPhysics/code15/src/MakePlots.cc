// $Id: $
// Include files 

// local

#include "MakePlots.h"

#include <TCanvas.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TF1.h>
#include <TF2.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TH1F.h>

//-----------------------------------------------------------------------------
// Implementation file for class : MakePlots
//
// 2011-09-25 : Andres Osorio
//-----------------------------------------------------------------------------
const double DensityModels::Mp = 1.672621777E-24; // proton mass [g]
const double DensityModels::GF = 1.1663E-5; // Fermi constant [GeV-2]
const double DensityModels::InveV = (1.0 / 5.076) * 1E-4; // (1/eV) length conversion factor
const double DensityModels::TeV = 1.0E12; // 1TeV = 10^12 eV
 
void MakePlots( ) 
{
  
  rhoAtResonance *rho;
  rhoModelA * rhoA;
  rhoModelB * rhoB;
  rhoModelC * rhoC;

  rho  = new rhoAtResonance();
  rhoA = new rhoModelA ();
  rhoB = new rhoModelB ();
  rhoC = new rhoModelC ();
  
  //-----------------------------------------------------------------------------

  double xmin = 6.5E10;
  double xmax = 3.2E12;
  
  TF1 * f1 = new TF1("rho" , rho  , xmin  , xmax , 1, "Rho at resonance");
  TF1 * f2 = new TF1("rhoA", rhoA , xmin  , xmax , 2, "Rho model A");
  TF1 * f3 = new TF1("rhoB", rhoB , xmin  , xmax , 3, "Rho model B");
  TF1 * f4 = new TF1("rhoC", rhoC , xmin  , xmax , 2, "Rho model C");

  f1->SetLineWidth(1);
  f2->SetLineWidth(2);
  f2->SetLineStyle(1);
  f3->SetLineWidth(2);
  f3->SetLineStyle(2);
  f4->SetLineWidth(2);
  f4->SetLineStyle(5);

  //
  f2->SetMaximum(1.0);
  f2->SetMinimum(1.0E-10);
  
  double angle = 6.0; //theta13
  double k2    = 4.0E-6;
  double r0    = 3.16E12;
  double rB    =  1.0E12;
  double kB    = 3.4E-5;
  double kC    = 6.3E-6;
  double dm2   = 1.4E-3;
  
  f1->SetParameter(0, angle);
  f2->SetParameter(0, k2);
  f2->SetParameter(1, r0);
  
  f3->SetParameter(0, kB);
  f3->SetParameter(1, r0);
  f3->SetParameter(2, rB);

  f4->SetParameter(0, kC);
  f4->SetParameter(1, r0);



  //-----------------------------------------------------------------------------

  TCanvas * c1 = new TCanvas("c1","plot 1",176,42,651,596);
  TCanvas * c2 = new TCanvas("c2","plot 2",101,127,802,620);
  TCanvas * c3 = new TCanvas("c3","plot 3",101,127,802,620);

  c1->cd();
  c1->SetLogx();
  c1->SetLogy();
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLeftMargin(0.12);
  

  f2->SetLineColor(1);
  f3->SetLineColor(1);
  f4->SetLineColor(1);

  //TLegend
  TLegend * leg = new TLegend( 0.195, 0.37, 0.55, 0.54, NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextFont(62);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->AddEntry(f2, "A", "L");
  leg->AddEntry(f3, "B", "L");
  leg->AddEntry(f4, "C", "L");
  
  TH1F * fake = c1->DrawFrame(xmin, 1.E-10, 4.0E12, 1.0);

  fake->GetXaxis()->SetTitle("r ( cm )");
  fake->GetXaxis()->CenterTitle(true);
  fake->GetXaxis()->SetLabelFont(42);
  fake->GetXaxis()->SetLabelSize(0.035);
  fake->GetXaxis()->SetTitleSize(0.035);
  fake->GetXaxis()->SetTitleFont(42);
  fake->GetYaxis()->SetTitle("#rho (g / cm^{3} )");
  fake->GetYaxis()->CenterTitle(true);
  fake->GetYaxis()->SetLabelFont(42);
  fake->GetYaxis()->SetLabelSize(0.035);
  fake->GetYaxis()->SetTitleOffset(1.60);

  f2->Draw("same");
  f3->Draw("same");
  f4->Draw("same");
  
  leg->Draw();

  c1->Print("supernova_models_ABC.eps");
  

  //f1->Draw("same");
  
  //-----------------------------------------------------------------------------

  nvEnergy * Ev = new nvEnergy();
    
  TF1 * fEv= new TF1("Ev", Ev , 1.4E-3  , 6.0E-3 , 3 , "Ev energy [eV]");

  fEv->SetParameter(0, (1/DensityModels::TeV));
  fEv->SetParameter(1,  angle );
  fEv->SetParameter(2, dm2 );
  
  std::cout << fEv->Eval( 1.2E11 ) << std::endl;
  std::cout << fEv->Eval( 1.6E11 ) << std::endl;
  std::cout << fEv->Eval( 1.0E11 ) << std::endl;
  
  fEv->SetParameter(2, 1.2E11 );

  c2->cd();

  fEv->Draw();
  
  //-----------------------------------------------------------------------------

  c3->cd();
  gStyle->SetPalette(1);
  
  lR2d *LR = new lR2d();
  
  TF2 * flr= new TF2("LR", LR , 1.4E-3, 6.0E-3 , 0.05, 1.0, 1, "LR(dm2,Ev)");
  
  flr->SetParameter(0, 6.0 );
  
  int maxpts = 5;

  double lmin = 0.5E10;
  double lmax = 1.2E11;
  double dx = ( lmax - lmin ) / float(maxpts);
  
  double contours[20];
  for( int i = 0; i<maxpts ; ++i) {
    contours[i] = lmin + ( dx * (i+1) ); 
  }
  
  flr->SetContour( maxpts, contours );
  
  flr->Draw(""); //CONT4 surface
  

  //-----------------------------------------------------------------------------

}
