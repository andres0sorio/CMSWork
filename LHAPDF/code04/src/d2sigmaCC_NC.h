// $Id: $
#ifndef D2SIGMACC_NC_H 
#define D2SIGMACC_NC_H 1


// Include files
#include "RootCommon.h"
#include "GSLHelpers.h"
#include <Math/IFunction.h>
#include "LHAPDF/LHAPDF.h"

/** @class Integrals Integrals.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-09-13
 */

//=============================================================================

//=============================================================================

class dsigmaCC_dQdy : public ROOT::Math::IBaseFunctionMultiDim {
  
public:

  dsigmaCC_dQdy() : SUBSET(0), NAME("cteq6")
  {

    LHAPDF::initPDFSet(NAME, LHAPDF::LHPDF, SUBSET);
    LHAPDF::initPDF(0);

  }

  double DoEval(const double * x) const;

  double qDist( double, double ) const;
  
  double qbarDist( double , double ) const;
    
  void SetEnu( double enu ) 
  {
    Enu = enu;
  }
  
  void SetM( double mass ) 
  {
    M = mass;
  }
  
  unsigned int NDim() const
  {
    return 3;
  }
  
  ROOT::Math::IBaseFunctionMultiDim* Clone() const
  {
    return new dsigmaCC_dQdy();
  }
  
private:
  
  const int SUBSET;
  const string NAME;
  
  static const double GF;
  static const double pi_over_2;
  static const double Mw;
  static const double Mz;
  
  double M; //nucleon mass
  double Enu; //incoming neutrino energy
    
};

#endif // D2SIGMACC_NC_H
