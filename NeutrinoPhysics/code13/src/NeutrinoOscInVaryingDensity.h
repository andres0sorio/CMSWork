// $Id: $
#ifndef NEUTRINOOSCINVARYINGDENSITY_H 
#define NEUTRINOOSCINVARYINGDENSITY_H 1

// Include files
#include "NeutrinoOscInMatter.h"

/** @class NeutrinoOscInVaryingDensity NeutrinoOscInVaryingDensity.h
 *  
 *  Class for Modelling of neutrino oscillation in varying matter density
 *  Method A: Using constant density layers
 *
 *
 *  @author Andres Osorio
 *  @date   2011-07-26
 */

class NeutrinoOscInVaryingDensity {
public: 
  
  /// Standard constructor
  NeutrinoOscInVaryingDensity( ) {}; 
  
  NeutrinoOscInVaryingDensity( MixingParameters * ); 
  
  virtual ~NeutrinoOscInVaryingDensity( ); ///< Destructor
  
  void Validate( );

  void SetProfile( TF1 * );
  
  void EvalInRange( float, float, float);
    

protected:
  
private:
  
  TF1              * m_densityProfile;
  MixingParameters * m_mixpars;
  matrix< double > m_prob_dx;

};
#endif // NEUTRINOOSCINVARYINGDENSITY_H
