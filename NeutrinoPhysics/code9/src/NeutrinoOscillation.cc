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
NeutrinoOscillation::NeutrinoOscillation(  ) {

  debug = false;
  
  //intialize parameters and set matrix elements
  setPhase( 0.0 );
  

  
  //Angles:
  m_Q   = new matrix< double >(3,3);
  initializeAngles();
  
  m_Prob_AtoB = new matrix< double >(3,3);
  m_U  = new matrix< std::complex<double> >(3,3);
  m_UC = new matrix< std::complex<double> >(3,3);

  initializeMatrix( m_U );
  initializeMatrix( m_UC );
  initializeMatrix( m_Prob_AtoB );

  updateMixingMatrix();
  
  calcProbabilities();

  if (debug) 
  {
    std::cout << (*m_Q) << std::endl;
    std::cout << (*m_U) << std::endl;
    std::cout << (*m_UC) << std::endl;
    std::cout << (*m_Prob_AtoB) << std::endl;
  }
  
  
}

//=============================================================================
// Destructor
//=============================================================================

NeutrinoOscillation::~NeutrinoOscillation() {
  
  if( m_U ) delete m_U;
  
  if( m_UC ) delete m_UC;

  if( m_Prob_AtoB ) delete m_Prob_AtoB;
  
  
} 

//=============================================================================
void NeutrinoOscillation::initializeAngles() 
{
  
  for(int i=0; i < 3; ++i) 
    for( int j=0; j < 3; ++j)
      (*m_Q)(i,j) = 0.0;
  
  setAngle(1, 2, 33.0);  //theta_12
  setAngle(1, 3,  0.0);  //theta_13
  setAngle(2, 3, 45.0);  //theta_23

}

void NeutrinoOscillation::setAngle(int i, int j, double angle) 
{

  (*m_Q)(i-1,j-1) = (angle * M_PI)/180.0;
  (*m_Q)(j-1,i-1) = (angle * M_PI)/180.0;
  
}

void NeutrinoOscillation::setPhase( double angle ) 
{

  m_dCP = (angle * M_PI)/180.0;
  
}

double NeutrinoOscillation::cosTh( int i, int j )
{
  
  return cos( (*m_Q)(i-1,j-1) );
  
}

double NeutrinoOscillation::sinTh( int i, int j )
{
  
  return sin( (*m_Q)(i-1,j-1) );

}

void NeutrinoOscillation::initializeMatrix( matrix< double > * Mat )
{
  
  for(int i=0; i < 3; ++i) 
    for( int j=0; j < 3; ++j)
      (*Mat)(i,j) = 0.0;
  
}


void NeutrinoOscillation::initializeMatrix( matrix< std::complex<double> > * Mat )
{
  
  for(int i=0; i < 3; ++i) 
    for( int j=0; j < 3; ++j)
      (*Mat)(i,j) = std::complex<double>(0.0, 0.0);
  
}

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

void NeutrinoOscillation::calcProbabilities() 
{
  
  double sum=0.0;
  
  for(int a=0; a<3; ++a)
    for(int b=0; b<3; ++b) 
    {
      sum = 0.0;
      for(int i=0; i<3; ++i) 
        sum += ((*m_U)(a,i) * (*m_UC)(a,i)).real() * ((*m_U)(b,i) * (*m_UC)(b,i)).real();
            
      (*m_Prob_AtoB) (a,b) = sum;
      
    }
  
  
}

void NeutrinoOscillation::Propagate(double phi_e0, double phi_mu0, double phi_tau0)
{

  updateMixingMatrix();
  
  calcProbabilities();
    
  double phi_b0[3];

  phi_b0[0] = phi_e0;
  phi_b0[1] = phi_mu0;
  phi_b0[2] = phi_tau0;
    
  m_phi_e_f = 0.0;

  matrix<double> T_Prob_AtoB( trans(*m_Prob_AtoB) );

  for(int b=0; b<3; ++b) 
    m_phi_e_f += T_Prob_AtoB (b,0) * phi_b0[b];
  
  m_phi_mu_f = 0.0;
  
  for(int b=0; b<3; ++b) 
    m_phi_mu_f += T_Prob_AtoB (b,1) * phi_b0[b];
  

  m_phi_tau_f = 0.0;
  
  for(int b=0; b<3; ++b) 
    m_phi_tau_f += T_Prob_AtoB (b,2) * phi_b0[b];
  
  std::cout << m_phi_e_f << " "
            << m_phi_mu_f << " " 
            << m_phi_tau_f << std::endl;
    

}
