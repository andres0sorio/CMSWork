// $Id: $
// Include files 

// local
#include "Integrals.h"
#include "Math/GSLIntegrator.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Integrals
//
// 2010-09-13 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, destructor and Setters of Base class Integrals
//=============================================================================
Integrals::Integrals() { 
  m_destroy_interp = false;
}

Integrals::~Integrals() {
  
  if ( m_destroy_interp ) {
    
    if (        nu_xsec_interp ) delete        nu_xsec_interp;
    if (    antinu_xsec_interp ) delete    antinu_xsec_interp;

    if (     nu_xsec_derivator ) delete     nu_xsec_derivator;
    if ( antinu_xsec_derivator ) delete antinu_xsec_derivator;
    
  }
  
} 

void Integrals::SetParameters( Parameters * input ) 
{
  m_input = input;
}

void Integrals::SetData( const std::string & xsec1, const std::string & xsec2)
{
  
  nu_xsec_interp        = new Interpolation( xsec1.c_str() );
  antinu_xsec_interp    = new Interpolation( xsec2.c_str() );
  nu_xsec_derivator     = new   Derivatives( nu_xsec_interp );
  antinu_xsec_derivator = new   Derivatives( antinu_xsec_interp );

}

//=============================================================================
// auxiliary functions:

double Rmu ( double * x )
{
  
  double E1 = x[0];
  double E2 = x[1];
  double kk = 2.6e5;
  
  double f_rmu = log ( 2.0 + ( 0.0042*E1 ) ) - log ( 2.0 + ( 0.0042*E2 ) );

  return kk * f_rmu;
  
}

double dFnub( double * x, double * par) 
{
  
  double alfa  = par[0];
  double Nbeta = par[1];

  double f_dfnu = Nbeta * pow ( x[0], -1.0 * alfa );
  
  return f_dfnu;
  
}

double fBLimOne( double * x ) 
{
  
  double E1 = x[0]; // E_tau
  double E2 = x[1]; // E_mu
  double ff = (5.0)/(3.0*E1) 
    - (3.0 * pow( E2, 2.0 ) ) / ( pow ( E1, 3.0 ) ) 
    + (4.0 * pow( E2, 3.0 ) ) / ( 3.0 * pow ( E1, 4.0 ) );
  
  return ff;

}




//=============================================================================
// Clone method implementation: just a formality

ROOT::Math::IBaseFunctionOneDim* m_Numu_integral_dx::Clone() const{
  
  m_Numu_integral_dx * f1 = new m_Numu_integral_dx();
  return f1;
  
}

ROOT::Math::IBaseFunctionOneDim* m_Numu_integral_dxdy::Clone() const{
  
  m_Numu_integral_dxdy * f1 = new m_Numu_integral_dxdy();
  return f1;
  
}

ROOT::Math::IBaseFunctionOneDim* m_Nutau_integral_dx::Clone() const{
  
  m_Nutau_integral_dx * f1 = new m_Nutau_integral_dx();
  return f1;
  
}

ROOT::Math::IBaseFunctionOneDim* m_Nutau_integral_dxdy::Clone() const{
  
  m_Nutau_integral_dxdy * f1 = new m_Nutau_integral_dxdy();
  return f1;
  
}

ROOT::Math::IBaseFunctionOneDim* m_Nutau_integral_dxdydz::Clone() const{
  
  m_Nutau_integral_dxdydz * f1 = new m_Nutau_integral_dxdydz();
  return f1;
  
}

ROOT::Math::IBaseFunctionOneDim* m_NC_showers_integral_dx::Clone() const{
  
  m_NC_showers_integral_dx* f1 = new m_NC_showers_integral_dx();
  return f1;
  
}

ROOT::Math::IBaseFunctionOneDim* m_CCnue_showers_integral_dx::Clone() const{
  
  m_CCnue_showers_integral_dx* f1 = new m_CCnue_showers_integral_dx();
  return f1;
  
}

ROOT::Math::IBaseFunctionOneDim* m_CCnutau_showers_integral_dx::Clone() const{
  
  m_CCnutau_showers_integral_dx* f1 = new m_CCnutau_showers_integral_dx();
  return f1;
  
}

//=============================================================================

double m_Numu_integral_dx::DoEval(double enu) const{
  
  m_Numu_integral_dxdy * ff = new m_Numu_integral_dxdy( *(Integrals*)this );
  
  ff->SetVar1 ( enu );
  
  float m_mu_Th = m_input->GetPar1();
  
  float m_y_low = m_mu_Th;
  float m_y_upp = enu;
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-12, 1000 );
  
  nminteg->SetFunction( *(ROOT::Math::IGenFunction*)ff );
  
  double result = nminteg->Integral(m_y_low , m_y_upp);
  
  delete ff;
  delete nminteg;
  
  return result;
  
}

//=============================================================================

double m_Numu_integral_dxdy::DoEval(double emu) const {
  
  double x1[2];
  double x2[1];
  double par[2];
  
  // x == Enu

  double y = 1.0 - ( emu / m_x );

  double dEnu_dEmu = (1.0 / (1.0 - y) );
  
  double dsigmaCC_dEnu = nu_xsec_derivator->evaluateCC( m_x );

  x1[0] = emu;
  x1[1] = m_input->GetPar1(); // Emu_Th
  
  x2[0] = m_x;
  
  par[0] = m_input->GetPar3(); // alfa
  par[1] = m_input->GetPar4(); // N_beta
  
  double ff = 0.5 * Rmu ( x1 ) * dFnub( x2, par) * dsigmaCC_dEnu * dEnu_dEmu;
  
  dsigmaCC_dEnu = antinu_xsec_derivator->evaluateCC( m_x );
  
  double gg = 0.5 * Rmu ( x1 ) * dFnub( x2, par) * dsigmaCC_dEnu * dEnu_dEmu;
  
  return ( ff + gg );
  
}

//=============================================================================

double m_Nutau_integral_dx::DoEval(double enut) const{

  //std::cout << "given: enut" << enut << std::endl;
  
  m_Nutau_integral_dxdy * ff = new m_Nutau_integral_dxdy( *(Integrals*)this );
  
  ff->SetVar1 ( enut ); // ... x == Enu_tau
  
  float m_mu_Th = m_input->GetPar1();
  
  float m_y_low = m_mu_Th;
  float m_y_upp = enut;
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-12, 1000 );
  
  nminteg->SetFunction( *(ROOT::Math::IGenFunction*)ff );
  
  double result = nminteg->Integral(m_y_low , m_y_upp);
  
  delete ff;
  delete nminteg;
  
  return result;
  
}

//=============================================================================

double m_Nutau_integral_dxdy::DoEval(double etau) const{
  
  m_Nutau_integral_dxdydz * ff = new m_Nutau_integral_dxdydz( *(Integrals*)this );
  
  ff->SetVar1 ( m_x );
  ff->SetVar2 ( etau );

  float mu_Th = m_input->GetPar1();
  
  float M_tau = 1.7840; // GeV/c^2
  float Gamma = M_tau / etau;
  float Beta  = sqrt ( 1.0 - (Gamma*Gamma) );
  
  float z_low = mu_Th;
  float z_upp = 0.5 * etau * ( 1.0 + Beta);
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-12, 1000 );
  
  nminteg->SetFunction( *(ROOT::Math::IGenFunction*)ff );
  
  double result = nminteg->Integral(z_low , z_upp);
  
  delete ff;
  delete nminteg;
  
  return result;
  
}

//=============================================================================

double m_Nutau_integral_dxdydz::DoEval(double z) const{
  
  double xx[2];
  double yy[2];
  double x2[1];

  double par[2];
  
  // x == E_nu_tau
  // y == E_tau
  // z == E_mu

  float E_tau = m_y;

  double y = 1.0 - ( m_y / m_x );

  double dEnu_dEmu = (1.0 / (1.0 - y) );
    
  double dsigmaCC_dEnu = nu_xsec_derivator->evaluateCC( m_x );
  
  xx[0] = z;
  xx[1] = m_input->GetPar1(); // Emu_Th

  yy[0] = E_tau;
  yy[1] = z;

  x2[0] = m_x;
      
  par[0] = m_input->GetPar3(); // alfa
  par[1] = m_input->GetPar4(); // N_beta
  
  double ff = 0.5 * Rmu ( xx ) * dFnub( x2, par) * fBLimOne( yy ) * dsigmaCC_dEnu * dEnu_dEmu;
  
  dsigmaCC_dEnu = antinu_xsec_derivator->evaluateCC( m_x );
  
  double gg = 0.5 * Rmu ( xx ) * dFnub( x2, par) * fBLimOne( yy ) * dsigmaCC_dEnu * dEnu_dEmu;
  
  return ( ff + gg );
  
}

//=============================================================================

double m_NC_showers_integral_dx::DoEval(double x) const{

  double xx[2];
  double par[2];
  
  double sigma_NC_log10 = nu_xsec_interp->evaluateNC( log10( x ) );
  double sigma_NC = pow( 10.0, sigma_NC_log10);
  
  xx[0]  = x;
  
  par[0] = m_input->GetPar3(); // alfa
  par[1] = m_input->GetPar4(); // N_beta
  
  double ff = 0.5 * dFnub( xx, par) * sigma_NC ;
  
  sigma_NC_log10 = antinu_xsec_interp->evaluateNC( log10(x) );
  sigma_NC = pow( 10.0, sigma_NC_log10);
  
  double gg = 0.5 * dFnub( xx, par) * sigma_NC;

  return ( ff + gg );
  
}

//=============================================================================

double m_CCnue_showers_integral_dx::DoEval(double x) const{

  double xx[2];
  double par[2];
  
  double sigma_CC_log10 = nu_xsec_interp->evaluateCC( log10( x ) );
  double sigma_CC = pow( 10.0, sigma_CC_log10);
  
  xx[0]  = x;
  
  par[0] = m_input->GetPar3(); // alfa
  par[1] = m_input->GetPar4(); // N_beta
  
  double ff = 0.5 * dFnub( xx, par) * sigma_CC ;
  
  sigma_CC_log10 = antinu_xsec_interp->evaluateCC( log10(x) );
  sigma_CC = pow( 10.0, sigma_CC_log10);
  
  double gg = 0.5 * dFnub( xx, par) * sigma_CC;

  return ( ff + gg );
  
}

//=============================================================================

double m_CCnutau_showers_integral_dx::DoEval(double x) const{

  double xx[2];
  double par[2];
  
  double sigma_CC_log10 = nu_xsec_interp->evaluateCC( log10( x ) );
  double sigma_CC = pow( 10.0, sigma_CC_log10);

  xx[0]  = x;
  
  par[0] = m_input->GetPar3(); // alfa
  par[1] = m_input->GetPar4(); // N_beta
  
  double ff = 0.5 * dFnub( xx, par) * sigma_CC ;

  sigma_CC_log10 = antinu_xsec_interp->evaluateCC( log10( x ) );
  sigma_CC = pow( 10.0, sigma_CC_log10);
  
  double gg = 0.5 * dFnub( xx, par) * sigma_CC;
  
  return ( ff + gg );
  
}

//=============================================================================
