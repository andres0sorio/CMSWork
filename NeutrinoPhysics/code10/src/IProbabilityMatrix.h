// $Id: $
#ifndef IPROBABILITYMATRIX_H 
#define IPROBABILITYMATRIX_H 1

// Include files

#include <string>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <complex>
#include <cmath>

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
  void   initializeAngles();
  void   initializeMatrix( matrix< double > * );
  void   initializeMatrix( matrix< std::complex<double> > * );

  void   Propagate( double, double, double );

  void   calcProbabilities();
  
  //...............

  // these need to be implemented for each case

  virtual void updateMixingMatrix() = 0;
  
  //...............
  
  double m_phi_e_f;
  double m_phi_mu_f;
  double m_phi_tau_f;
  
  //...............
  
  double m_dCP;
  
  matrix< double > * m_Q;
  matrix< double > * m_Prob_AtoB;
  
  matrix< std::complex<double> > * m_U;
  matrix< std::complex<double> > * m_UC;
  
  bool debug;
  
  //...............
  
protected:

private:



};
#endif // IPROBABILITYMATX_H
