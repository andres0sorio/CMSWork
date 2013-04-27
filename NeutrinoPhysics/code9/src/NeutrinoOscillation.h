// $Id: $
#ifndef NEUTRINOOSCILLATION_H 
#define NEUTRINOOSCILLATION_H 1

// Include files

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <complex>
#include <cmath>

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

class NeutrinoOscillation {
public: 
  /// Standard constructor
  NeutrinoOscillation( ); 

  virtual ~NeutrinoOscillation( ); ///< Destructor

  double cosTh( int, int );
  double sinTh( int, int );

  void   setAngle( int, int, double);
  void   setPhase( double);
  
  void   initializeAngles();
  void   initializeMatrix( matrix< double > * );
  void   initializeMatrix( matrix< std::complex<double> > * );
  
  void   updateMixingMatrix();
  
  void   calcProbabilities();
  
  void   Propagate( double, double, double );
  
  double m_phi_e_f;
  double m_phi_mu_f;
  double m_phi_tau_f;
      
protected:

private:

  double m_dCP;

  matrix< double > * m_Q;
  matrix< double > * m_Prob_AtoB;
  
  matrix< std::complex<double> > * m_U;
  matrix< std::complex<double> > * m_UC;
  
  bool debug;
    
};
#endif // NEUTRINOOSCILLATION_H
