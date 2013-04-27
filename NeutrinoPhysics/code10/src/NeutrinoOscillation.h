// $Id: $
#ifndef NEUTRINOOSCILLATION_H 
#define NEUTRINOOSCILLATION_H 1

// Include files
#include "IProbabilityMatrix.h"

/** @class NeutrinoOscillation NeutrinoOscillation.h
 *
 *  Class for Modelling of neutrino oscillation between source and earth
 *  Ref:
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-10-28
 */

using namespace boost::numeric::ublas;

class NeutrinoOscillation : public IProbabilityMatrix {
public: 
  
  /// Standard constructor
  NeutrinoOscillation( ); 
  
  virtual ~NeutrinoOscillation( ); ///< Destructor
  
  void   updateMixingMatrix();
  
  void   calcProbabilities();
  
protected:

private:

    
};
#endif // NEUTRINOOSCILLATION_H
