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
  
  bool convert = false;
  bool centerAt0 = true;
  
  std::map<std::string,DensityModels*> m_Models;
  
  m_Models["EarthA"] = (DensityModels*) new rhoEarthA();
  m_Models["EarthB"] = (DensityModels*) new rhoEarthB();
  
  double LMAX; 
  double LMIN;
  
  double h1 = 1.7E-13;
  double h2 = 4.4E-13;
  double s1 = 2.885e6;
  double s2 = 6.972e6;
  
  double m2ev = 0.0;
  double gcm3 = 4.2951E+18 * 8.79e-33;
  
  char xLabel[20];
  char yLabel[20];
  
  double offset = 0.0;
  
  if( convert )
  {
    
    m2ev = 5.076e+6;
    
    LMIN = 0.0;
    LMAX = 6.4750e+13;
    
    sprintf(xLabel,"L [1/eV]");
    sprintf(yLabel,"A [eV]");
    
    if ( centerAt0 ) 
      offset = (6.4750e+13 / 2.0 );
    else 
      offset = 0.0;
    
  } else {
    
    m2ev = 1.0;
    h1 = 4.50;
    h2 = 11.50;
    gcm3 = 1.0;
    
    LMIN = 0.0;
    LMAX = 12756.2e3;
    
    sprintf(xLabel,"L [m]");
    sprintf(yLabel,"#rho [g/cm^{3}]");
    
    if ( centerAt0 ) 
      offset = 6.37810e+06;
    else 
      offset = 0.0;
    
  }
  
  std::cout << " LMIN " << (LMIN-offset) << std::endl;
  
  DensityModels * density_Mod = m_Models["EarthB"];
  
  int maxpars = 3;
  
  TF1 * profB = new TF1("profB", density_Mod, (LMIN-offset), (LMAX-offset), maxpars);
  
  profB->SetParameter( 0 , LMAX);
  profB->SetParameter( 1 , gcm3 );
  profB->SetParameter( 2 , offset );
  
  density_Mod = m_Models["EarthA"];
  
  maxpars = 6;
  
  TF1 * profA = new TF1("profA", density_Mod, (LMIN-offset), (LMAX-offset), maxpars);
  
  //s2 = 8.17e6;
  
  profA->SetParameter( 0 ,   h1);
  profA->SetParameter( 1 ,   h2);
  profA->SetParameter( 2 ,   s1);
  profA->SetParameter( 3 ,   s2);
  profA->SetParameter( 4 , m2ev);
  profA->SetParameter( 5 , offset);
  
  ///Drawing now:

  profB->GetXaxis()->SetTitle(xLabel);
  profB->GetXaxis()->CenterTitle(true);
  profB->GetXaxis()->SetLabelFont(42);
  profB->GetXaxis()->SetLabelSize(0.05);
  profB->GetXaxis()->SetTitleSize(0.05);
  profB->GetXaxis()->SetTitleOffset(0.94);
  profB->GetXaxis()->SetTitleFont(42);
  profB->GetYaxis()->SetTitle(yLabel);
  profB->GetYaxis()->CenterTitle(true);
  profB->GetYaxis()->SetLabelFont(42);
  profB->GetYaxis()->SetLabelSize(0.05);
  profB->GetYaxis()->SetTitleSize(0.05);
  profB->GetYaxis()->SetTitleOffset(0.89);
  profB->GetYaxis()->SetTitleFont(42);

  profB->SetLineColor(1);
  profB->Draw();

  profA->SetLineColor(4);
  profA->SetLineStyle(3);
  profA->Draw("same");

  TLegend * leg = new TLegend(0.68,0.79,0.98,0.98);
    
  leg->AddEntry( profB,"Earth B-Becker");
  leg->AddEntry( profA,"Earth A-Ohlsson");
  leg->SetBorderSize(1);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->Draw();

  c1->Print("c1.pdf");

  //.........................................................................................

  return 0;
  
}
