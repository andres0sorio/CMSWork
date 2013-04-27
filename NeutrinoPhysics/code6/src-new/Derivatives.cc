// $Id: $
// Include files 



// local
#include "Derivatives.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Derivatives
//
// 2010-10-08 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Derivatives::Derivatives( const char * data ) {
  
  m_xsec_CC = new sigmaCC();
  m_xsec_CC->SetData( data );
  sigmaCC_derivator = new ROOT::Math::Derivator();
  sigmaCC_derivator->SetFunction( *(ROOT::Math::IGenFunction*)m_xsec_CC );
}

Derivatives::Derivatives( Interpolation * interpol ) {
  
  m_xsec_CC = new sigmaCC( interpol );
  sigmaCC_derivator = new ROOT::Math::Derivator();
  sigmaCC_derivator->SetFunction( *(ROOT::Math::IGenFunction*)m_xsec_CC );

}


//=============================================================================
// Destructor
//=============================================================================
Derivatives::~Derivatives() {

  if (m_xsec_CC) delete m_xsec_CC;
  if (sigmaCC_derivator) delete sigmaCC_derivator;
  
} 

//=============================================================================
double Derivatives::evaluateCC( double x ) 
{
  return sigmaCC_derivator->Eval(x);
}

double Derivatives::evaluateNC( double x ) 
{
  return 1.0;
}


//=============================================================================

ROOT::Math::IBaseFunctionOneDim* sigmaCC::Clone() const{

  sigmaCC * f1 = new sigmaCC();
  return f1;
  
}

void sigmaCC::SetData(const char * indata) {
  m_xsec_interp = new Interpolation( indata );
}

double sigmaCC::DoEval(double x) const{
  
  double sigma_CC_log10 = m_xsec_interp->evaluateCC( x );
  double sigma_CC = pow( 10.0, sigma_CC_log10);
  
  return sigma_CC;
  
}
