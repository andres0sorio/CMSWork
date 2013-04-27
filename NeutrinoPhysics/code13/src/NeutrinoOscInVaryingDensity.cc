// $Id: $
// Include files 



// local
#include "NeutrinoOscInVaryingDensity.h"

//-----------------------------------------------------------------------------
// Implementation file for class : NeutrinoOscInVaryingDensity
//
// 2011-07-26 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
NeutrinoOscInVaryingDensity::NeutrinoOscInVaryingDensity( MixingParameters * mixpars ) {

  m_mixpars =  mixpars;

}

//=============================================================================
// Destructor
//=============================================================================

NeutrinoOscInVaryingDensity::~NeutrinoOscInVaryingDensity() {

  if ( m_densityProfile ) 
    delete m_densityProfile;
  
} 

//=============================================================================
void NeutrinoOscInVaryingDensity::SetProfile( TF1 * profile ) {

  m_densityProfile = profile;
  
}

void NeutrinoOscInVaryingDensity::EvalInRange( float xmin, float xmax, float dx )
{
  
  float x0 = xmin;
  float xx = x0 + dx;
  
  NeutrinoOscInMatter * nuOscMat = new NeutrinoOscInMatter( m_mixpars );
  
  while ( xx < xmax ) {
      
    //. Displacement
    nuOscMat->m_input->SetPar5( dx );
    
    //. Density
    //  NeutrinoOscInMatter uses an effective potencial Ve
    //  m_densityProfile is the pointer to such function and must be set 
    //  before this evaluation!
    
    double Ve = m_densityProfile->Eval( xx );
    nuOscMat->m_input->SetPar7( Ve ); 
    
    nuOscMat->updateMixingMatrix();
    
    double Pemu = (*nuOscMat->m_Prob_AtoB) (0,1);
    double Pmumu = (*nuOscMat->m_Prob_AtoB) (1,1);
    double Pmutau = (*nuOscMat->m_Prob_AtoB) (1,2);
    
    xx += dx;
    
  }
  
}

void NeutrinoOscInVaryingDensity::Validate() {

  float xmin = 100.0;
  float xmax = 10000.0;

  m_densityProfile = new TF1();

  this->Eval( xmin, xmax, 10.0 );

  


}
