// $Id: $
// Include files 

#include <iterator>
#include <iostream>
#include <cstdlib>

// local
#include "d2sigmaCC_NC.h"

//-----------------------------------------------------------------------------
// Implementation file for class : d2sigmaCC_NC
//
// 2012-06-13 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables, constants
//=============================================================================

const double dsigmaCC_dQdy::GF = 1.1663E-5; // Fermi constant [GeV-2]
const double dsigmaCC_dQdy::pi_over_2 = 1.57079632; // PI/2.0
const double dsigmaCC_dQdy::Mw = 80.398; // W boson mass
const double dsigmaCC_dQdy::Mz = 91.187; // Z boson mass

//=============================================================================
double dsigmaCC_dQdy::DoEval(const double * xx) const{

  double x  = xx[0];
  double y  = xx[1];
  double nu = Enu * y;
  
  double Q2 = xx[3];

  double k = GF * GF * M * Enu / pi_over_2;
  
  double kk = ( Mw*Mw / ( Q2 + Mw*Mw) ) * ( Mw*Mw / ( Q2 + Mw*Mw) );
  
  double q = qDist( x, Q2 );
  double qbar = qbarDist( x, Q2 );
  
  double qpart = ( (x * q) + (x * qbar * (1.0 - y) * (1.0 - y) ));
  
  double val = k * kk * qpart;
  
  return val;
  
}

double dsigmaCC_dQdy::qDist(double x1, double x2 ) const
{
  

  double x = x1;
  double Q = sqrt(x2);
  
  if( x < 1.0E-6) LHAPDF::extrapolate(true);
  
  double uv =  LHAPDF::xfx(x, Q, 2);
  double dv =  LHAPDF::xfx(x, Q, 1);
  double us =  LHAPDF::xfx(x, Q, -2);
  double ds =  LHAPDF::xfx(x, Q, -1);
  double ss =  LHAPDF::xfx(x, Q,  3);
  double bs =  LHAPDF::xfx(x, Q,  5);
  
  double val = ( (uv + dv ) / 2.0 ) + ( (us + ds ) / 2.0 ) + ss + bs;
    
  return val;
    
}

double dsigmaCC_dQdy::qbarDist(double x1, double x2 ) const
{
  
  double x = x1;
  double Q = sqrt(x2);
  
  if( x < 1.0E-6) LHAPDF::extrapolate(true);
  
  double us =  LHAPDF::xfx(x, Q, -2);
  double ds =  LHAPDF::xfx(x, Q, -1);
  double cs =  LHAPDF::xfx(x, Q,  3);
  double ts =  LHAPDF::xfx(x, Q,  5);
  
  double val = ( (us + ds ) / 2.0 ) + cs + ts;
  
  return val;
  
}

