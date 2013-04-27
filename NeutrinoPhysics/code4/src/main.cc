// $Id: 
// Include files 

#include <MuTrackEvents.h>
#include <ShowerEvents.h>
#include <Graphics.h>

int main(int iargv, const char **argv) {
  
  ParameterList parlist;
  
  if (parlist.ParseFile("config.xml") == 0)
    std::cout << parlist;
  std::cout << "-------------------------------------------------------" << '\n';

  bool debug = false;

  Graphics * graphs = new Graphics();

  float phi_neu = 0.0;
  float dphi = 1.0;
  
  for ( int k = 0; k < 10; ++k ) 
  {
  
    Parameters * pars = parlist.GetParameters(0);
    
    pars->SetPar11( phi_neu );
    
    MuTrackEvents * mu1 = new MuTrackEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
    double N_mu_racks = mu1->Evaluate();
    
    ShowerEvents * sh1 =  new ShowerEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
    double N_shower_racks = sh1->Evaluate();
    
    double ratio = N_mu_racks / N_shower_racks;
    
    float sum = phi_neu + 2.0;
    
    graphs->g1->SetPoint(k, (phi_neu / sum), ratio);
    
    if ( ! debug ) 
    {
      
      std::cout << "-------------------------------------------------------" << '\n';
      std::cout << mu1->EvaluateNuMuContribution() << '\n';
      std::cout << mu1->EvaluateNuTauContribution() << '\n';
      std::cout << sh1->EvaluateNCContribution() << '\n';
      std::cout << sh1->EvaluateCCNueContribution() << '\n';
      std::cout << sh1->EvaluateCCNutauContribution() << '\n';
    }
    
    std::cout << "-------------------------------------------------------" << '\n';
    std::cout << "Ratio Ntracks/Nshower like events: " <<  ratio << std::endl;
    std::cout << "-------------------------------------------------------" << '\n';
    
    phi_neu = phi_neu + dphi;
    
    delete sh1;
    delete mu1;
  
  }
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  c1->SetFillColor(10);
  c1->cd();
  graphs->g1->Draw("ACP");
  c1->Print("ratio.vs.phi_new.png");

  
  return 1;
    
}
