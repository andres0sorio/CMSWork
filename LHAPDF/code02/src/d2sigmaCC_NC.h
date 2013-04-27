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

    const double mz = 91.2;
    std::cout << "alphas(mz) = " << LHAPDF::alphasPDF(mz) << std::endl;
    std::cout << "qcdlam4    = " << LHAPDF::getLam4(SUBSET) << std::endl;
    std::cout << "qcdlam5    = " << LHAPDF::getLam5(SUBSET) << std::endl;
    std::cout << "orderPDF   = " << LHAPDF::getOrderPDF() << std::endl;
    std::cout << "xmin       = " << LHAPDF::getXmin(SUBSET) << std::endl;
    std::cout << "xmax       = " << LHAPDF::getXmax(SUBSET) << std::endl;
    std::cout << "q2min      = " << LHAPDF::getQ2min(SUBSET) << std::endl;
    std::cout << "q2max      = " << LHAPDF::getQ2max(SUBSET) << std::endl;
    std::cout << "orderalfas = " << LHAPDF::getOrderAlphaS() << std::endl;
    std::cout << "num flav   = " << LHAPDF::getNf() << std::endl;
    std::cout << "name       = " << NAME << std::endl;
    std::cout << "number     = " << LHAPDF::numberPDF() << std::endl;
    std::cout << std::endl;

    LHAPDF::initPDF(0);

  }

  double DoEval(const double * x) const;

  double Validate(const double * x) const;
  
  unsigned int NDim() const
  {
    return 2;
  }
  
  ROOT::Math::IBaseFunctionMultiDim* Clone() const
  {
    return new dsigmaCC_dQdy();
  }
  
private:
  
  const int SUBSET;
  const string NAME;
  

  
};

#endif // D2SIGMACC_NC_H
