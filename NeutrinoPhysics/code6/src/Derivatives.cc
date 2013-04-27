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

Derivatives::Derivatives( ) {

  m_testF = new testFunction();
  test_derivator =  new ROOT::Math::Derivator();
  test_derivator->SetFunction( *(ROOT::Math::IGenFunction*)m_testF );
  
  sigmaCC_derivator = 0x0;
  sigmaNC_derivator = 0x0;
  m_xsec_CC = 0x0;
  
}

Derivatives::Derivatives( const char * data ) {
  
  m_xsec_CC = new sigmaCC();
  m_xsec_CC->SetData( data );
  sigmaCC_derivator = new ROOT::Math::Derivator();
  sigmaCC_derivator->SetFunction( *(ROOT::Math::IGenFunction*)m_xsec_CC );

  sigmaNC_derivator = 0x0;
  
  test_derivator = 0x0;

}

Derivatives::Derivatives( Interpolation * interpol ) {
  
  m_xsec_CC = new sigmaCC( interpol );
  sigmaCC_derivator = new ROOT::Math::Derivator();
  sigmaCC_derivator->SetFunction( *(ROOT::Math::IGenFunction*)m_xsec_CC );

  sigmaNC_derivator = 0x0;

  test_derivator = 0x0;
  
}


//=============================================================================
// Destructor
//=============================================================================
Derivatives::~Derivatives() {

  if (m_xsec_CC) delete m_xsec_CC;
  if (sigmaCC_derivator) delete sigmaCC_derivator;
  if (sigmaNC_derivator) delete sigmaNC_derivator;
  if (test_derivator   ) delete test_derivator;
  
} 

//=============================================================================
double Derivatives::evaluateCC( double x ) 
{
  return sigmaCC_derivator->EvalCentral(x,1E-6);
}

double Derivatives::evaluateNC( double x ) 
{
  return sigmaNC_derivator->EvalCentral(x,1E-6);
}

double Derivatives::evaluateTest( double x ) 
{
  return test_derivator->EvalCentral(x,1E-6);
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
  
  double sigma_CC_log10 = m_xsec_interp->evaluateCC( log10( x ) );
  double sigma_CC = pow( 10.0, sigma_CC_log10);
  
  return sigma_CC;
  
}


//=============================================================================
// ... this is a test function: f(x) = x^2

ROOT::Math::IBaseFunctionOneDim* testFunction::Clone() const{

  testFunction * f1 = new testFunction();
  return f1;
}

double testFunction::DoEval(double x) const{

  return x*x;
}

//=============================================================================
