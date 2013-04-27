// $Id: 
// Include files 

#include <Graphics.h>
#include <d2sigmaCC_NC.h>

#include <sstream>
#include "sys/stat.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int iargv, char **argv) {
    
  //.........................................................................................

    
  dsigmaCC_dQdy * f1 = new dsigmaCC_dQdy();
  
  Graphics * graphs = new Graphics("test.root");
  
  double xmin = 1.0E-8;
  double xmax = 1.0;
  double dx   = 2;
  double xx   = xmin;
  double mw   = 80.4;
  double Q    = 100.0;
  
  double vars[3];
  
  int i = 0;
  
  TGraph *g1[7];
  g1[0] = new TGraph();
  g1[1] = new TGraph();
  g1[2] = new TGraph();
  g1[3] = new TGraph();
  g1[4] = new TGraph();
  g1[5] = new TGraph();
  g1[6] = new TGraph();
  
  while ( xx < xmax ) {
    
    vars[0] = xx;
    vars[1] = Q;
    
    double value = f1->DoEval( vars );
        
    graphs->g1[0]->SetPoint(i, xx, value );
  
    vars[2] = 0.0;
    value =  f1->Validate( vars );
    g1[0]->SetPoint(i, xx, value );

    vars[2] = 2.0;
    value =  f1->Validate( vars );
    g1[1]->SetPoint(i, xx, value );

    vars[2] = 1.0;
    value =  f1->Validate( vars );
    g1[2]->SetPoint(i, xx, value );

    vars[2] = -2.0;
    value =  f1->Validate( vars );
    g1[3]->SetPoint(i, xx, value );

    vars[2] = -1.0;
    value =  f1->Validate( vars );
    g1[4]->SetPoint(i, xx, value );
      
    vars[2] = 3.0;
    value =  f1->Validate( vars );
    g1[5]->SetPoint(i, xx, value );

    vars[2] = 4.0;
    value =  f1->Validate( vars );
    g1[6]->SetPoint(i, xx, value );

    i = i + 1;
    xx *= dx;
    
  };

  delete f1;

  graphs->SetOptions();
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  
  c1->SetFillColor(10);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLogx();
  c1->SetLogy();
  c1->cd();
  
  graphs->g1[0]->SetMaximum(1000);
  graphs->g1[0]->SetMinimum(0.001);
  graphs->g1[0]->Draw("ACP");

  c1->Print("fig1.eps");
  
  delete graphs;
  
  //.........................................................................................

   
  TCanvas *c2 = new TCanvas("c2","Graphics canvas",526,216,650,500);
  
  c2->SetFillColor(10);
  c2->SetTickx(1);
  c2->SetTicky(1);
  c2->SetLogx();
  c2->SetLogy();
  c2->cd();
  
  g1[0]->SetMaximum(100);
  g1[0]->SetMinimum(0.01);
  g1[0]->SetLineStyle(1);
  g1[0]->Draw("ACP");

  for(int k=1; k < 7; ++k) 
  {
    
    g1[k]->SetMaximum(100);
    g1[k]->SetMinimum(0.01);
    g1[k]->SetLineStyle(k+1);
    g1[k]->Draw("CP");
    
  }
  

  c2->Print("validate.eps");

  return 1;
  
}

#include "LHAPDF/FortranWrappers.h"
#ifdef FC_DUMMY_MAIN
int FC_DUMMY_MAIN() { return 1; }
#endif
