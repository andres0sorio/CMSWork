// $Id: 
// Include files 

#include <MuTrackEvents.h>
#include <ShowerEvents.h>
#include <Graphics.h>
#include <NeutrinoOscInVacuum.h>
#include <NeutrinoOscInMatter.h>


#include <sstream>

///////////////////////////////////////////////////////////////
// The effective potential Ve

double evaluateVe( float enu)
{
  return -enu;
}

double evaluateVe( float rho, float ye)
{
  return 7.6 * ye * rho * 1E-14;
}

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {
  
  ParameterList parlist;
  
  if (parlist.ParseFile("config.xml") == 0)
    std::cout << parlist;
  std::cout << "ParameterList-------------------------------------------------------" << '\n';
  
  MixingParameterList mixparlist;
  
  if (mixparlist.ParseFile("matrix_config.xml") == 0)
    std::cout << mixparlist;
  std::cout << "MixingParameterList-------------------------------------------------" << '\n';
  
  MixingParameters *mixpars =  mixparlist.GetParameters(0);
  
  Graphics * graphs = new Graphics();
  
  double log_DeltaM2 = -2.9;
  double log_DetlaM2_max = -2.2;
  double DeltaM2 = pow(10.0, log_DeltaM2);
  double Ve  = 1.0;
  float  rho = 10.0;
  float  Ye  = 1.0;
  
  NeutrinoOscInMatter * nuOscMat = new NeutrinoOscInMatter( mixpars );
  
  Ve = evaluateVe ( rho, Ye );
  
  //Ve = evaluateVe ( nuOscMat->m_input->GetPar6() );
  
  nuOscMat->m_input->SetPar7( Ve );
  nuOscMat->m_input->SetPar4( DeltaM2 );
  nuOscMat->updateMixingMatrix();
  nuOscMat->Propagate(1.0, 2.0, 0.0);

  int k = 0;
  
  while(1) 
  {
    
    if( log_DeltaM2 >=  log_DetlaM2_max ) break;
    
    DeltaM2 = pow(10.0, log_DeltaM2);
    
    nuOscMat->m_input->SetPar4( DeltaM2 );
    nuOscMat->updateMixingMatrix();
    nuOscMat->Propagate(1.0, 2.0, 0.0);
    
    double Pemu = (*nuOscMat->m_Prob_AtoB) (0,1);
    double Pmumu = (*nuOscMat->m_Prob_AtoB) (1,1);
    double Pmutau = (*nuOscMat->m_Prob_AtoB) (1,2);
    
    graphs->g7->SetPoint(k, log_DeltaM2, Pemu);
    graphs->g8->SetPoint(k, log_DeltaM2, Pmumu);
    graphs->g9->SetPoint(k, log_DeltaM2, Pmutau);
    
    k = k + 1;
    
    log_DeltaM2 = log_DeltaM2 + 0.001;
    
            
  }
  
  
    
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  
  c1->SetFillColor(10);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->cd();
  
  graphs->SetOptions();
  graphs->g7->SetMaximum(1.1);
  graphs->g7->SetMinimum(0.0);
  graphs->g7->Draw("ACP");
  
  c1->Print("pemu_logDm2.pars_1.png");
  c1->Print("pemu_logDm2.pars_1.eps");
  
  graphs->SetOptions();
  graphs->g8->SetMaximum(1.1);
  graphs->g8->SetMinimum(0.0);
  graphs->g8->Draw("ACP");
  
  c1->Print("pmumu_logDm2.pars_1.png");
  c1->Print("pmumu_logDm2.pars_1.eps");
  
  graphs->SetOptions();
  graphs->g9->SetMaximum(1.1);
  graphs->g9->SetMinimum(0.0);
  graphs->g9->Draw("ACP");
  
  c1->Print("pmutau_logDm2.pars_1.png");
  c1->Print("pmutau_logDm2.pars_1.eps");

  
  delete c1;
  delete nuOscMat;

  return 1;
    
}
