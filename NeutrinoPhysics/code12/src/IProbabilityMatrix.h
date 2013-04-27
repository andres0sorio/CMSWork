// $Id: $
#ifndef IPROBABILITYMATRIX_H 
#define IPROBABILITYMATRIX_H 1

// Include files

#include <string>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <complex>
#include <cmath>

#include <MixingParameters.h>

/** @class IProbabilityMatrix IProbabilityMatrix.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-01-06
 */

using namespace boost::numeric::ublas;

class IProbabilityMatrix {
  
public: 
  
  IProbabilityMatrix();
  virtual ~IProbabilityMatrix();
  
  // utilities:
  double cosTh( int, int);
  double sinTh( int, int );
  
  void   setAngle( int, int, double);
  void   setPhase( double);
  
  void   initializeMatrix( matrix< double > * );
  void   initializeMatrix( matrix< std::complex<double> > * );

  void   Propagate( double, double, double );

  void   SetParameters( MixingParameters * input ) 
  {
    m_input = input;
  }

  //...............

  // these need to be implemented for each case

  virtual void initializeAngles() = 0;
  
  virtual void updateMixingMatrix() = 0;

  virtual void calcProbabilities() = 0;
  
  //...............
  
  double m_phi_e_f;
  double m_phi_mu_f;
  double m_phi_tau_f;
  
  //...............
  
  double m_dCP;
  
  matrix< double > * m_Q; // mixing angles matrix
  matrix< double > * m_Prob_AtoB; // survival probabilities matrix
  
  matrix< std::complex<double> > * m_U; // mixing matrix
  matrix< std::complex<double> > * m_UC; // conjugate of mixing matrix
  
  //...............

  bool debug;
  bool has_mixing_matrix;
  bool use_default_pars;
  
  MixingParameters * m_input;
    
protected:

private:

    
};
#endif // IPROBABILITYMATX_H
