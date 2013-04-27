// $Id: $
#ifndef D2SIGMACC_NC_H 
#define D2SIGMACC_NC_H 1


// Include files
#include "RootCommon.h"
#include "GSLHelpers.h"
#include <Math/IFunction.h>

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

  dsigmaCC_dQdy() : SUBSET(0), NAME("cteq6l")
  {

  }

  double DoEval(const double* x) const;
  
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
