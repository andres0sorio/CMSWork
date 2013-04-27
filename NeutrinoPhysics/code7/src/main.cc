// $Id: 
// Include files 

#include <MuTrackEvents.h>
#include <ShowerEvents.h>
#include <Graphics.h>
#include <sstream>

int main(int iargv, const char **argv) {
  
  ParameterList parlist;
  
  if (parlist.ParseFile("config.xml") == 0)
    std::cout << parlist;
  std::cout << "-------------------------------------------------------" << '\n';
  
  bool debug = false;
  int parset = 1;
  
  //

  Parameters *pars;
  
  while ( (pars = parlist.Next()) ) {
    
    Graphics * graphs = new Graphics();
    
    float phi_neu = 0.0;
    float dphi = 1.0;
    float phi_ne_fr = 0.0;
    float phi_nmu_fr = 0.0;
    float phi_ntau_fr = 0.0;
    
    int k = 0;
    std::stringstream ss_png;
    std::stringstream ss_eps;
    
    ss_png << "results/ratio.vs.phi_new.pars_" << parset << ".png";
    ss_eps << "results/ratio.vs.phi_new.pars_" << parset << ".eps";
    
    while (1) 
    {
      
      if ( phi_neu > 1000 ) break;
      if ( phi_neu > 20 ) dphi = 100.0;
      
      float sum = phi_neu + 2.0;
      
      //Parameters * pars = parlist.GetParameters(0);
      
      phi_ne_fr = (phi_neu / sum);
      phi_nmu_fr = (1.0 - phi_ne_fr) / 2.0;
      phi_ntau_fr = phi_nmu_fr;
      
      pars->SetPar11( phi_ne_fr );
      pars->SetPar12( phi_nmu_fr );
      pars->SetPar13( phi_ntau_fr );
      
      //MuTrackEvents * mu1 = new MuTrackEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
      MuTrackEvents * mu1 = new MuTrackEvents("XSec_neut.dat", "XSec_anti.dat", pars );
      double N_mu_racks = mu1->Evaluate();
      
      double numu_trks  = mu1->m_NuMuTracks;
      
      //ShowerEvents * sh1 =  new ShowerEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
      ShowerEvents * sh1 =  new ShowerEvents("XSec_neut.dat", "XSec_anti.dat", pars );
      double N_shower_racks = sh1->Evaluate();
      
      double ratio = N_mu_racks / N_shower_racks;
      
      double ratio_notau = numu_trks / N_shower_racks;
      
      graphs->g1->SetPoint(k, (phi_neu / sum), ratio);
      graphs->g2->SetPoint(k, (phi_neu / sum), ratio_notau);
      
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
      
      k = k + 1;
      phi_neu = phi_neu + dphi;
      
      delete sh1;
      delete mu1;
      
    }
    
    TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
    c1->SetFillColor(10);
    c1->SetTickx(1);
    c1->SetTicky(1);
    c1->cd();

    graphs->SetOptions();
    graphs->g1->Draw("ACP");
    graphs->g2->Draw("CP");
    graphs->tleg_1->Draw();
    
    c1->Print(ss_png.str().c_str());
    c1->Print(ss_eps.str().c_str());

    parset = parset + 1;
        
    delete c1;

  }
  
  //

  Graphics * graphs = new Graphics();
    
  double alpha = 1.8;
    
  int k = 0;
  std::stringstream ss_png;
  std::stringstream ss_eps;
  
  ss_png << "results/ratio.vs.alpha.pars_" << parset << ".png";
  ss_eps << "results/ratio.vs.alpha.pars_" << parset << ".eps";

  pars = parlist.GetParameters(0);

  pars->SetPar11( 1.0 );
  pars->SetPar12( 1.0 );
  pars->SetPar13( 1.0 );

  while (1) 
  {

    if ( alpha >= 3.1 ) break;
    
    pars->SetPar3( alpha );
        
    MuTrackEvents * mu1 = new MuTrackEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
    double N_mu_racks = mu1->Evaluate();
      
    double numu_trks  = mu1->m_NuMuTracks;
      
    ShowerEvents * sh1 =  new ShowerEvents("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
    double N_shower_racks = sh1->Evaluate();
      
    double ratio = N_mu_racks / N_shower_racks;
    
    double ratio_notau = numu_trks / N_shower_racks;
    
    graphs->g3->SetPoint(k, alpha, ratio);
    graphs->g4->SetPoint(k, alpha, ratio_notau);
    
    k = k + 1;
    alpha = alpha + 0.05;
    
    delete sh1;
    delete mu1;
    
  }
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  c1->SetFillColor(10);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->cd();
  
  graphs->SetOptions();
  graphs->g3->SetMinimum(1.4);
  graphs->g3->Draw("ACP");
  //graphs->g4->Draw("CP");
  graphs->tleg_2->Draw();

  c1->Print(ss_png.str().c_str());
  c1->Print(ss_eps.str().c_str());
  
  delete c1;
  
  //.........................................................................................

  return 1;
    
}
