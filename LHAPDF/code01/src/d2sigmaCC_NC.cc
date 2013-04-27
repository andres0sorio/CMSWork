// $Id: $
// Include files 
#include "LHAPDF/LHAPDF.h"
#include <iterator>
#include <iostream>
#include <cstdlib>

//#include "LHAPDF/FortranWrappers.h"
//#ifdef FC_DUMMY_MAIN
//int FC_DUMMY_MAIN() { return 1; }
//#endif


// local
#include "d2sigmaCC_NC.h"

//-----------------------------------------------------------------------------
// Implementation file for class : d2sigmaCC_NC
//
// 2012-06-13 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

//=============================================================================
double dsigmaCC_dQdy::DoEval(const double * x) const{
  
  double Q2 = x[0];
  double y = x[1];
  
  LHAPDF::initPDFSet(NAME, LHAPDF::LHPDF, SUBSET);

  const double Q = 10.0, mz = 91.2;
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

    // LHAPDF::extrapolate();

  const int NUMBER = LHAPDF::numberPDF();

    
  for (int n = 0; n < NUMBER + 1; ++n) {
    std::cout << "Set number: " << n << std::endl; 
    LHAPDF::initPDF(n);
    for (int ix = 1; ix < 11; ++ix) {
      const double x = (ix - 0.5) / 10.0;
      std::cout << "x=" << x << ", Q=" << Q << ", f=0: " << LHAPDF::xfx(x, Q, 0) << std::endl;
    }
    std::cout << std::endl;
  }


  for (int n = 0; n < NUMBER + 1; ++n) {
    std::cout << "Set number: " << n << std::endl; 
    LHAPDF::initPDF(n);
    for (int ix = 1; ix < 11; ++ix) {
      const double x = (ix - 0.5) / 10.0;
      std::cout << "x=" << x << ", Q=" << Q << ": ";
      std::vector<double> result = LHAPDF::xfx(x, Q);
      std::copy(result.begin(), result.end(), ostream_iterator<double>(std::cout,"\t"));
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }


  std::cout << string().insert(0, 40, '-') << endl << std::endl;
  std::cout << "Checking LHAPDF with package " << std::endl;
  std::cout << NAME << " set number " << SUBSET << "/" << LHAPDF::numberPDF() << endl << std::endl;
  std::cout << "LHAPDF::getDescription() gives:" << std::endl;
  LHAPDF::getDescription();

  

  return Q2 + sin(y);
  
  
}

