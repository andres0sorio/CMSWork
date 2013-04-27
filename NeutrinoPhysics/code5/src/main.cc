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

  bool debug = true;

  Graphics * graphs = new Graphics();
   
  float phi_neu = 0.0;
  float dphi = 1.0;
  
  for ( int k = 0; k < 50; ++k ) 
  {
  
    Parameters * pars = parlist.GetParameters(0);
    
    pars->SetPar11( phi_neu );
    
    MuTrackEvents * mu1 = new MuTrackEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
    double N_mutaus_tracks = mu1->Evaluate();

    double N_mu_tracks = mu1->EvaluateNuMuContribution();
    
    ShowerEvents * sh1 =  new ShowerEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
    double N_showers = sh1->Evaluate();
    
    double ratio = N_mutaus_tracks / N_showers;
    
    double ratio_notaus = N_mu_tracks / N_showers;

    float sum = phi_neu + 2.0;
    
    graphs->g1->SetPoint(k, (phi_neu / sum), ratio);
    graphs->g2->SetPoint(k, (phi_neu / sum), ratio_notaus);
     
    if ( debug ) 
    {
      
      std::cout << "-------------------------------------------------------" << '\n';
      std::cout << "NuMu: " << mu1->EvaluateNuMuContribution() << '\n';
      std::cout << "NuTau: " << mu1->EvaluateNuTauContribution() << '\n';
      std::cout << "NCC: " << sh1->EvaluateNCContribution() << '\n';
      std::cout << "CCNueC: " << sh1->EvaluateCCNueContribution() << '\n';
      std::cout << "CCNutau: " << sh1->EvaluateCCNutauContribution() << '\n';
      std::cout << "-------------------------------------------------------" << '\n';
      std::cout << "Ratio Ntracks/Nshower like events: " <<  ratio << std::endl;
      std::cout << "-------------------------------------------------------" << '\n';
    }
    
    phi_neu = phi_neu + dphi;
    
    delete sh1;
    delete mu1;
  
  }
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  c1->SetFillColor(10);
  c1->cd();
  graphs->SetOptions();
  graphs->g1->Draw("ACP");
  graphs->g2->Draw("CP");
  c1->Print("ratio.vs.phi_new.eps");

  
  return 1;
    
}
