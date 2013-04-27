// $Id: 
// Include files 

#include <MuTrackEvents.h>
#include <ShowerEvents.h>
#include <Graphics.h>
#include <NeutrinoOscillation.h>

#include <sstream>
//
int main(int iargv, const char **argv) {
  
  ParameterList parlist;
  
  if (parlist.ParseFile("config.xml") == 0)
    std::cout << parlist;
  std::cout << "-------------------------------------------------------" << '\n';
  
  double theta = 0.0;
  double theta_max = 15.0;
  int parset = 1;
  
  Parameters *pars =  parlist.GetParameters(0);

  Graphics * graphs = new Graphics();
    
  NeutrinoOscillation * nuOsc = new NeutrinoOscillation();

  //
  
  int k = 0;
  std::stringstream ss_png;
  std::stringstream ss_eps;
  
  ss_png << "results/ratio.vs.theta13.pars_" << parset << ".png";
  ss_eps << "results/ratio.vs.theta13.pars_" << parset << ".eps";

  while(1) 
  {
    
    if( theta >= theta_max ) break;

    double sin2theta = pow ( sin( theta * M_PI / 180.0), 2.0 );
        
    nuOsc->setAngle(1,3,theta);
    nuOsc->setPhase(0.0);
    nuOsc->Propagate( 1.0, 2.0, 0.0 );

    pars->SetPar11( nuOsc->m_phi_e_f );
    pars->SetPar12( nuOsc->m_phi_mu_f );
    pars->SetPar13( nuOsc->m_phi_tau_f );
    
    MuTrackEvents * mu1 = new MuTrackEvents("XSec_neut.dat", "XSec_anti.dat", pars );
    ShowerEvents  * sh1 = new ShowerEvents("XSec_neut.dat", "XSec_anti.dat", pars );

    double N_mu_racks = mu1->Evaluate();
    double N_shower_racks = sh1->Evaluate();
    double ratio = N_mu_racks / N_shower_racks;

    graphs->g5->SetPoint(k, sin2theta, ratio);

    delete mu1;
    delete sh1;

    nuOsc->setPhase(180.0);
    nuOsc->Propagate( 1.0, 2.0, 0.0 );

    pars->SetPar11( nuOsc->m_phi_e_f );
    pars->SetPar12( nuOsc->m_phi_mu_f );
    pars->SetPar13( nuOsc->m_phi_tau_f );
    
    mu1 = new MuTrackEvents("XSec_neut.dat", "XSec_anti.dat", pars );
    sh1 = new ShowerEvents("XSec_neut.dat", "XSec_anti.dat", pars );
    
    N_mu_racks = mu1->Evaluate();
    N_shower_racks = sh1->Evaluate();
    ratio = N_mu_racks / N_shower_racks;

    graphs->g6->SetPoint(k, sin2theta, ratio);

    k = k + 1;
    theta = theta + 0.1;
    
    delete mu1;
    delete sh1;
        
  }
  
  //.........................................................................................

  delete nuOsc;
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  
  c1->SetFillColor(10);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->cd();
  
  graphs->SetOptions();
  graphs->g5->SetMaximum(2.5);
  graphs->g5->SetMinimum(2.0);
  
  graphs->g5->Draw("ACP");
  graphs->g6->Draw("CP");
  
  graphs->tleg_1->Draw();
  
  c1->Print(ss_png.str().c_str());
  c1->Print(ss_eps.str().c_str());
  
  delete c1;

  return 1;
    
}
