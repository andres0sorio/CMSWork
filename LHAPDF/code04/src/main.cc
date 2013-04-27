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

  //Graphics * graphs = new Graphics("test.root");

  TGraph * g1[5];

  g1[0] = new TGraph();

  //.........................................................................................

  double Emin = 10;
  double Emax = 1.0E12;
  double step = 10;
  double Enu  = Emin;
  
  double xmin[3];
  double xmax[3];

  // x [ ]
  xmin[0] = 1.0E-7;
  xmax[0] = 0.1;

  // y [0,1]
  xmin[1] = 0.0;
  xmax[1] = 1.0;
  
  // y [0,1]
  xmin[2] = 1.7;
  xmax[2] = 1.0E8;
  
  int i = 0;
  
  f1->SetM( 0.939 ) ; //neutron mass
    
  double unit_factor = 1.0E-18 * (1.97E-5) * (1.97E-5) ;
    
  while ( Enu <= Emax ) {
    
    f1->SetEnu( Enu );
    
    ROOT::Math::GSLMCIntegrator * nminteg = 
      new ROOT::Math::GSLMCIntegrator( ROOT::Math::IntegrationMultiDim::kVEGAS, 1.E-6, 1.E-4, 50000 );
    
    nminteg->SetFunction( *(ROOT::Math::IMultiGenFunction*)f1 );
    
    double sigma = nminteg->Integral( xmin , xmax );
    
    std::cout << "integral result: " << sigma << " " << nminteg->ChiSqr() << std::endl;
    
    g1[0]->SetPoint( i , Enu, sigma*(1.0/Enu)*unit_factor );
    
    i += 1;
    Enu *= step;
  
    delete nminteg;
  
  }
  
  
  delete f1;
  
  //.........................................................................................
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  
  c1->SetFillColor(10);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLogx();
  c1->SetLogy();
  c1->cd();
  
  g1[0]->SetMaximum(1.0E-38);
  g1[0]->SetMinimum(1.0E-44);
  g1[0]->SetLineStyle(1);
  g1[0]->Draw("ACP");
  
  c1->Print("validate.eps");
  
  return 1;
  
}

#include "LHAPDF/FortranWrappers.h"
#ifdef FC_DUMMY_MAIN
int FC_DUMMY_MAIN() { return 1; }
#endif
