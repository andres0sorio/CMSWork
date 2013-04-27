// $Id: 
// Include files

#include <fstream>
#include <MuTrackEvents.h>
#include <ShowerEvents.h>
#include <Graphics.h>

int main(int iargv, const char **argv) {
  
  ParameterList parlist;
  
  if (parlist.ParseFile("config.xml") == 0)
    std::cout << parlist;
  std::cout << "-------------------------------------------------------" << '\n';

  bool debug = false;

  std::ofstream * m_out = new std::ofstream("ratios-data.csv");

  Graphics * graphs = new Graphics();
   
  float phi_neu_frac = 0.0;
  float phi_neu = 0.0;
  float phi_mutau_frac = 0.0;
  float dphi = 1.0;
  
  for ( int k = 0; k < 10; ++k ) 
  {
  
    float sum = phi_neu + 2.0;

    Parameters * pars = parlist.GetParameters(0);
  
    phi_neu_frac = (phi_neu / sum);
    phi_mutau_frac = ( 1.0 - phi_neu_frac) / 2.0;
    
    pars->SetPar11( phi_neu );
    
    if ( phi_neu == 0.0 ) 
    {
      pars->SetPar12( 1.0 );
      pars->SetPar13( 1.0 );
    } else 
    {
      pars->SetPar12( 1.0 );
      pars->SetPar13( 1.0 );
    }

    std::cout << " phi_l: " 
              << pars->GetPar11() << " " 
              << pars->GetPar12() << " " 
              << pars->GetPar13() << '\n';
        
    MuTrackEvents * mu1 = new MuTrackEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );

    double N_mutaus_tracks = mu1->Evaluate();
    
    double N_mu_tracks = mu1->EvaluateNuMuContribution();

    double N_tau_tracks = mu1->EvaluateNuTauContribution();
    
    std::cout << "data: " 
              << N_mu_tracks << '\t'
              << N_tau_tracks << '\t'
              << (N_mu_tracks + N_tau_tracks) << '\t'
              << N_mutaus_tracks
              << '\n';
    
    ShowerEvents * sh1 =  new ShowerEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
    double N_showers = sh1->Evaluate();
    
    double ratio = N_mutaus_tracks / N_showers;
    
    double ratio_notaus = N_mu_tracks / N_showers;

    graphs->g1->SetPoint(k, phi_neu_frac, ratio);
    graphs->g2->SetPoint(k, phi_neu_frac, ratio_notaus);

    (*m_out) << k << "," << (phi_neu / sum) << "," << N_mu_tracks << "," << N_tau_tracks
             << "," << N_showers << std::endl;
         
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

  m_out->close();
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  c1->SetFillColor(10);
  c1->cd();
  graphs->SetOptions();
  graphs->g1->SetMaximum(8.0);
  graphs->g1->Draw("ACP");
  graphs->g2->Draw("CP");
  c1->Print("ratio.vs.phi_new.png");

  
  return 1;
    
}
