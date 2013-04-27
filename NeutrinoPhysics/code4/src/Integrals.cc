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
    if ( nu_xsec_interp ) delete nu_xsec_interp;
    if ( antinu_xsec_interp ) delete antinu_xsec_interp;
  }
  
} 

void Integrals::SetParameters( Parameters * input ) 
{
  m_input = input;
}

void Integrals::SetData( const std::string & xsec1, const std::string & xsec2)
{
  
  nu_xsec_interp = new Interpolation( xsec1.c_str() );
  antinu_xsec_interp = new Interpolation ( xsec2.c_str() );
  
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

double dsigmady( double * x ) 
{
  
  double y  = x[0];
  
  //double ff = (5.47 * exp(-y));
  //return ff;

  double a  = 3.0;
  double b  = (exp(-a) + a - 1.0) / a;
  double ff = (exp(-a*y)) + b;

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
  
  float m_y_low = 0.0;
  float m_y_upp = ( enu - m_mu_Th) / enu;  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-12, 1000 );
  
  nminteg->SetFunction( *(ROOT::Math::IGenFunction*)ff );
  
  double result = nminteg->Integral(m_y_low , m_y_upp);
  
  delete ff;
  delete nminteg;
  
  return result;
  
}

//=============================================================================

double m_Numu_integral_dxdy::DoEval(double y) const {
  
  double x1[2];
  double x2[1];
  double x3[1];
  double par[2];
  
  // x == Enu
  
  double Emu = m_x * ( 1.0 - y );
  double sigma_CC_log10 = nu_xsec_interp->evaluateCC( log10(m_x) );
  double sigma_CC = pow( 10.0, sigma_CC_log10);
  
  x1[0] = Emu;
  x1[1] = m_input->GetPar1(); // Emu_Th
  
  x2[0] = m_x;
  
  par[0] = m_input->GetPar3(); // alfa
  par[1] = m_input->GetPar4(); // N_beta
  
  x3[0]  = y;
  
  double ff = Rmu ( x1 ) * dFnub( x2, par) * sigma_CC * dsigmady( x3 );

  sigma_CC_log10 = antinu_xsec_interp->evaluateCC( log10( m_x) );
  sigma_CC = pow( 10.0, sigma_CC_log10);
  
  double gg = Rmu ( x1 ) * dFnub( x2, par) * sigma_CC * dsigmady( x3 );
  
  return ( ff + gg );
  
}

//=============================================================================

double m_Nutau_integral_dx::DoEval(double enut) const{

  m_Nutau_integral_dxdy * ff = new m_Nutau_integral_dxdy( *(Integrals*)this );
  
  ff->SetVar1 ( enut ); // ... x == Enu_tau
  
  float m_mu_Th = m_input->GetPar1();
  
  float m_y_low = 0.0;
  float m_y_upp = ( enut - m_mu_Th ) / enut;
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-12, 1000 );
  
  nminteg->SetFunction( *(ROOT::Math::IGenFunction*)ff );
  
  double result = nminteg->Integral(m_y_low , m_y_upp);
  
  delete ff;
  delete nminteg;
  
  return result;
  
}

//=============================================================================

double m_Nutau_integral_dxdy::DoEval(double y) const{
  
  m_Nutau_integral_dxdydz * ff = new m_Nutau_integral_dxdydz( *(Integrals*)this );
  
  ff->SetVar1 ( m_x );
  ff->SetVar2 ( y );

  float mu_Th = m_input->GetPar1();
  
  float M_tau = 1.7840; // GeV/c^2
  float E_tau = m_x * ( 1.0 - y );
  float Gamma = M_tau / E_tau;
  float Beta  = sqrt ( 1.0 - (Gamma*Gamma) );

  float z_low = mu_Th;
  float z_upp = 0.5 * E_tau * ( 1.0 + Beta);
    
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
  
  double x1[2];
  double x2[1];
  double x3[1];

  double yy[2];
  double par[2];
  
  // x == E_nu_tau
  // y == y
  // z == E_mu

  float E_tau = m_x * ( 1.0 - m_y );
  
  double sigma_CC_log10 = nu_xsec_interp->evaluateCC( log10( m_x ) );
  double sigma_CC = pow( 10.0, sigma_CC_log10);
  
  x1[0] = z;
  x1[1] = m_input->GetPar1(); // Emu_Th

  yy[0] = E_tau;
  yy[1] = z;

  x2[0] = m_x;
      
  par[0] = m_input->GetPar3(); // alfa
  par[1] = m_input->GetPar4(); // N_beta
  
  x3[0]  = m_y;
       
  double ff = Rmu ( x1 ) * dFnub( x2, par) * fBLimOne( yy ) * sigma_CC * dsigmady ( x3 );
  
  sigma_CC_log10 = antinu_xsec_interp->evaluateCC( log10( m_x ) );
  sigma_CC = pow( 10.0, sigma_CC_log10);
  
  double gg = Rmu ( x1 ) * dFnub( x2, par) * fBLimOne( yy ) * sigma_CC * dsigmady ( x3 );
  
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
  
  double ff = dFnub( xx, par) * sigma_NC ;
  
  sigma_NC_log10 = antinu_xsec_interp->evaluateNC( log10(x) );
  sigma_NC = pow( 10.0, sigma_NC_log10);
  
  double gg = dFnub( xx, par) * sigma_NC;

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
  
  double ff = dFnub( xx, par) * sigma_CC ;
  
  sigma_CC_log10 = antinu_xsec_interp->evaluateCC( log10(x) );
  sigma_CC = pow( 10.0, sigma_CC_log10);
  
  double gg = dFnub( xx, par) * sigma_CC;

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
  
  double ff = dFnub( xx, par) * sigma_CC ;

  sigma_CC_log10 = antinu_xsec_interp->evaluateCC( log10( x ) );
  sigma_CC = pow( 10.0, sigma_CC_log10);
  
  double gg = dFnub( xx, par) * sigma_CC;
  
  return ( ff + gg );
  
}

//=============================================================================
