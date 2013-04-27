// $Id: $
// Include files 



// local
#include "NeutrinoOscillation.h"

//-----------------------------------------------------------------------------
// Implementation file for class : NeutrinoOscillation
//
//
//
// 2010-10-28 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
NeutrinoOscillation::NeutrinoOscillation(  ) : IProbabilityMatrix( ) {
  
}

//=============================================================================
// Destructor
//=============================================================================

NeutrinoOscillation::~NeutrinoOscillation() {
} 

//=============================================================================

void NeutrinoOscillation::updateMixingMatrix( )
{
  
  (*m_U) (0,0) = std::complex<double>( cosTh(1,2)*cosTh(1,3), 0.0);

  (*m_U) (0,1) = std::complex<double>( cosTh(1,3)*sinTh(1,2), 0.0);
  
  (*m_U) (0,2) = std::complex<double>( sinTh(1,3)*cos(m_dCP),
                                       - sinTh(1,3)*sin(m_dCP) );
  
  (*m_U) (1,0) = std::complex<double>( -cosTh(2,3)*sinTh(1,2) - cosTh(1,2)*sinTh(1,3)*sinTh(2,3)*cos(m_dCP), 
                                       -cosTh(1,2)*sinTh(1,3)*sinTh(2,3)*sin(m_dCP) );

  (*m_U) (1,1) = std::complex<double>( cosTh(1,2)*cosTh(2,3) - sinTh(1,2)*sinTh(1,3)*sinTh(2,3)*cos(m_dCP), 
                                       -sinTh(1,2)*sinTh(1,3)*sinTh(2,3)*sin(m_dCP) );
  
  (*m_U) (1,2) = std::complex<double>( cosTh(1,3)*sinTh(2,3), 0.0);
  
  (*m_U) (2,0) = std::complex<double>( sinTh(1,2)*sinTh(2,3) - cosTh(1,2)*cosTh(2,3)*sinTh(1,3)*cos(m_dCP), 
                                       -cosTh(1,2)*cosTh(2,3)*sinTh(1,3)*sin(m_dCP) );
  
  (*m_U) (2,1) = std::complex<double>( -cosTh(1,2)*sinTh(2,3) - cosTh(2,3)*sinTh(1,2)*sinTh(1,3)*cos(m_dCP), 
                                       -cosTh(2,3)*sinTh(1,2)*sinTh(1,3)*sin(m_dCP) );
  
  (*m_U) (2,2) = std::complex<double>( cosTh(1,3)*cosTh(2,3), 0.0);

  //conj == conjugate of Matrix U
  (*m_UC) = conj( (*m_U) );
    
}
