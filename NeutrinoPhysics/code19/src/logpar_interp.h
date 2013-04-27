// $Id: $
#ifndef LOGPAR_INTERP_H 
#define LOGPAR_INTERP_H 1

// Include files

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <math.h>
#include "Riostream.h"
#include <TROOT.h>
#include <TMath.h>

#include <Math/Integrator.h>
#include <Math/IntegrationTypes.h>
#include "Math/WrappedFunction.h"
#include "Math/RootFinder.h"
#include "Math/RootFinderAlgorithms.h"
#include <Math/Interpolator.h>


/** @class logpar_interp logpar_interp.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-12-20
 */
class logpar_interp {
public: 
  /// Standard constructor
  
  logpar_interp( ); 
  
  logpar_interp( const char * ); 
  
  virtual ~logpar_interp( ); ///< Destructor
  
  double operator() (double *x, double *p);
  
private:
  
  std::ifstream * m_in;
  ROOT::Math::Interpolator * m_interpolator;

  std::vector<double> m_xx;
  std::vector<double> m_yy;
  
  
};
#endif // LOGPAR_INTERP_H
