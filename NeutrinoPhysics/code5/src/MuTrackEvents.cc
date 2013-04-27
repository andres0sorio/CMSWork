// Include files 

// local
#include "MuTrackEvents.h"

//-----------------------------------------------------------------------------
// Implementation file for class : MuTrackEvents
//
// 2010-09-13 : Andres Osorio
//-----------------------------------------------------------------------------

MuTrackEvents::MuTrackEvents(const char * nuxsec, const char * antinuxsec, Parameters * input) {
  
  nu_xsec_data = std::string(nuxsec);
  antinu_xsec_data = std::string(antinuxsec);
  m_input = input;

  m_phi_nu[0] = m_input->GetPar11();
  m_phi_nu[1] = m_input->GetPar12();
  m_phi_nu[2] = m_input->GetPar13();
  
  std::cout << m_phi_nu[0] << " " << m_phi_nu[1] << " " << m_phi_nu[2] << '\n';
  
}

float MuTrackEvents::Evaluate() {

  //... get Nu_mu / Anti-Nu_mu contribution

  float v1 = EvaluateNuMuContribution();
  
  //... get Nu_tau / Anti-Nu_tau contribution

  float v2 = EvaluateNuTauContribution();
  
  return (v1+v2);

}

float MuTrackEvents::EvaluateNuMuContribution() {
  
  //... This is formula 5 from Ref[1]

  m_Numu_integral_dx * ff = new m_Numu_integral_dx();
  
  ff->SetData(nu_xsec_data, antinu_xsec_data);
  ff->SetParameters( m_input );
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-11, 1000 );
  
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
  
  double kk = rho * Area * Na;
  
  return m_phi_nu[1] * kk * result;

}

float MuTrackEvents::EvaluateNuTauContribution() {

  //... This is formula 7 from Ref[1]
  
  m_Nutau_integral_dx * ff = new m_Nutau_integral_dx();
  
  ff->SetData(nu_xsec_data, antinu_xsec_data);
  ff->SetParameters( m_input );
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-11, 1000 );
  
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
  
  return m_phi_nu[2] * kk * result;
  
}


