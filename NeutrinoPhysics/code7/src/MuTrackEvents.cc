// Include files 

// local
#include "MuTrackEvents.h"

//-----------------------------------------------------------------------------
// Implementation file for class : MuTrackEvents
//
// 2010-09-13 : Andres Osorio
//-----------------------------------------------------------------------------

MuTrackEvents::MuTrackEvents(const char * nuxsec, const char * antinuxsec, Parameters * input) {

  debug = false;
    
  nu_xsec_data = std::string(nuxsec);
  antinu_xsec_data = std::string(antinuxsec);
  m_input = input;

  m_phi_nu[0] = m_input->GetPar11(); //phi_e
  m_phi_nu[1] = m_input->GetPar12(); //phi_mu
  m_phi_nu[2] = m_input->GetPar13(); //phi_tau
  
  if( debug) std::cout << m_phi_nu[0] << " " << m_phi_nu[1] << " " << m_phi_nu[2] << '\n';
  
  m_NuMuTracks = 0.0;
  m_NuTauTracks = 0.0;
  
}

float MuTrackEvents::Evaluate() {
  
  m_NuMuTracks = 0.0;
  m_NuTauTracks = 0.0;

  //... get Nu_mu / Anti-Nu_mu contribution

  float v1 = EvaluateNuMuContribution();
  
  m_NuMuTracks = v1;
  
  //... get Nu_tau / Anti-Nu_tau contribution
  
  float v2 = EvaluateNuTauContribution();
  
  m_NuTauTracks = v2;

  return (v1 + v2);

}

float MuTrackEvents::EvaluateNuMuContribution() {
  
  //... This is formula 5 from Ref[1]

  m_Numu_integral_dx * ff = new m_Numu_integral_dx();

  m_input->SetPar4( m_phi_nu[1] ); // N_beta = phi_mu
  
  ff->SetData(nu_xsec_data, antinu_xsec_data);
  ff->SetParameters( m_input );
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 0.0, 1.E-12, 1000 );
  
  nminteg->SetFunction( *(ROOT::Math::IGenFunction*)ff );
  
  float m_mu_Th = m_input->GetPar1();
  float m_nu_Cut = m_input->GetPar2();
      
  double result = nminteg->Integral(m_mu_Th, m_nu_Cut);

  ff->DestroyInterpolator();
  
  delete ff;
  delete nminteg;
  
  double rho  = m_input->GetPar5();
  double Area = m_input->GetPar6();
  double Na   = m_input->GetPar7();
  double kk   = rho * Area * Na;
  
  return kk * result;

}

float MuTrackEvents::EvaluateNuTauContribution() {

  //... This is formula 7 from Ref[1]
  
  m_Nutau_integral_dx * ff = new m_Nutau_integral_dx();

  m_input->SetPar4( m_phi_nu[2] ); // N_beta = phi_tau
  
  ff->SetData(nu_xsec_data, antinu_xsec_data);
  ff->SetParameters( m_input );
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-12, 1000 );
  
  nminteg->SetFunction( *(ROOT::Math::IGenFunction*)ff );
  
  float m_mu_Th = m_input->GetPar1();
  float m_nu_Cut = m_input->GetPar2();
      
  double result = nminteg->Integral(m_mu_Th, m_nu_Cut);

  ff->DestroyInterpolator();
  
  delete ff;
  delete nminteg;
  
  double rho  = m_input->GetPar5();
  double Area = m_input->GetPar6();
  double Na   = m_input->GetPar7();
  double Br   = m_input->GetPar8();
  double kk   = Br * rho * Area * Na;
  
  return kk * result;
  

}

