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

  TGraph * g1[5];

  g1[0] = new TGraph();
  g1[1] = new TGraph();
  
  //.........................................................................................
  
  double Emin = 10;
  double Emax = 1.0E12;
  double step = 10;
  double Enu  = Emin;
  
  double xmin[2];
  double xmax[2];
  
  // x [ ]
  xmin[0] = 1.0E-8;
  xmax[0] = 0.1;
  
  // y [0,1]
  xmin[1] = 0.0;
  xmax[1] = 1.0;
  
  int i = 0;
  
  f1->SetM( 0.939 ) ; //neutron mass
    
  double x = xmin[0];
  double Q2 = 1.69;
      
  while ( x <= xmax[0] ) {
    
    double val = f1->qDist( x, Q2 );
    g1[0]->SetPoint( i , x , val );
    std::cout << "q: " << val << std::endl;
    
    val = f1->qbarDist( x, Q2 );
    g1[1]->SetPoint( i , x , val );
    std::cout << "qbar: " << val << std::endl;
    
    i += 1;
    x *= step;
  
  }
  
  
  delete f1;
  
  //.........................................................................................
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,850,800);
  c1->SetFillColor(10);

  c1->Divide(3,3);
  
  
  TPad * p1 = (TPad*)c1->cd(1);
  p1->SetTickx(1);
  p1->SetTicky(1);
  p1->SetLogx();
  p1->SetLogy();

  g1[0]->SetLineStyle(1);
  g1[0]->Draw("ACP"); 


  p1 = (TPad*)c1->cd(2);
  p1->SetTickx(1);
  p1->SetTicky(1);
  p1->SetLogx();
  p1->SetLogy();
  
  g1[1]->SetLineStyle(1);
  g1[1]->Draw("ACP");


  c1->Print("validate.eps");
  
  return 1;
  
}

#include "LHAPDF/FortranWrappers.h"
#ifdef FC_DUMMY_MAIN
int FC_DUMMY_MAIN() { return 1; }
#endif
