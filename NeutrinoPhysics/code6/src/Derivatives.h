// $Id: $
#ifndef DERIVATIVES_H 
#define DERIVATIVES_H 1

// Include files
#include "RootCommon.h"
#include "GSLHelpers.h"
#include <Math/IFunction.h>
#include <Math/Derivator.h>
#include <nuN_interpxsec.h>

/** @class Derivatives Derivatives.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-10-08
 */

//=============================================================================
// ... this is a test function: f(x) = x^2

class testFunction : public ROOT::Math::IBaseFunctionOneDim {
  
public:
  
  testFunction(){};
 
  virtual ~testFunction() { };
  
  ROOT::Math::IBaseFunctionOneDim* Clone() const;

private:
  
  double DoEval(double x) const;
  
};

//=============================================================================

class sigmaCC : public ROOT::Math::IBaseFunctionOneDim {
  
public:
  
  sigmaCC(){};
  
  sigmaCC( Interpolation * interpolator ){ 
    m_xsec_interp = interpolator;
  };
  
  virtual ~sigmaCC() { };
  
  ROOT::Math::IBaseFunctionOneDim* Clone() const;

  void SetData( const char * );
  
private:
  
  Interpolation * m_xsec_interp;
  
  double DoEval(double x) const;
  
};


class Derivatives {
public: 
  /// Standard constructor
  
  Derivatives( ); 
  
  Derivatives( const char *); 

  Derivatives( Interpolation * );
    
  virtual ~Derivatives( ); ///< Destructor
  
  double evaluateCC( double );
  double evaluateNC( double );
  
  double evaluateTest( double );
  
protected:
  
private:

  sigmaCC * m_xsec_CC;
  sigmaCC * m_xsec_NC;

  testFunction * m_testF;
    
  ROOT::Math::Derivator * sigmaCC_derivator;
  ROOT::Math::Derivator * sigmaNC_derivator;
  
  ROOT::Math::Derivator * test_derivator;
    
};



#endif // DERIVATIVES_H
