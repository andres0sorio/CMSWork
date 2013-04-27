// $Id: $
#ifndef DENSITYMODELS_H 
#define DENSITYMODELS_H 1

// Include files
#include <RootCommon.h>
#include <cmath>



/** @class DensityModels DensityModels.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-09-25
 */

class DensityModels {
public: 
  
  /// Standard constructor
  DensityModels( ){}; 
  
  virtual ~DensityModels( ){}; ///< Destructor

  virtual double operator() (double *x, double *p) = 0;

  void treat_as_AntiNu() { m_sign = -1.0; };
  
  double m_pars[10];
  static const double Mp;
  static const double GF;
  static const double InveV;
  static const double InveV2;
  static const double TeV;
  
  double m_sign; // m_sign: used for selecting nu vs anti-nu from construction

};

class rhoEarthB : public DensityModels {
public: 
  
  /// Standard constructor
  rhoEarthB( ) : DensityModels() { m_sign = 1.0; }; 
  
  virtual ~rhoEarthB( ){}; ///< Destructor
  
  virtual double operator() (double *x, double *p) {
    
    // rho [g/cm^3]: Ref Physics Reports 458 (2008) 173-246
    
    double value = 0.0;
    
    double LMAX   = p[0];
    double offset = p[2];
    double DX     = LMAX/2.0;
    double x0     = abs( ( x[0]-DX+offset) ) / DX;
    double toNU   = p[1];
    double xx     = pow( x0 , 2.0 );
    double xxx    = pow( x0 , 3.0 );

    if( x0 < 0.192 )
      value = 13.0885 - 8.8381*x0;
    else if( x0 > 0.192 && x0 < 0.546 )
      value = 12.5815 - 1.2638 * x0 - 3.6426 * xx - 5.5281 * xxx;
    else if( x0 > 0.546 && x0 < 0.895 ) 
      value = 7.9565 - 6.4761 * x0 + 5.5283 * xx - 3.0807 * xxx;
    else if( x0 > 0.895 && x0 < 0.906) 
      value = 5.3197 - 1.4836 * x0;
    else if( x0 > 0.906 && x0 < 0.937) 
      value = 11.2494 - 8.0298 * x0;
    else if( x0 > 0.937 && x0 < 0.965) 
      value = 7.1089 - 3.8045 * x0;
    else if( x0 > 0.965 && x0 < 0.996) 
      value = 2.691 + 0.6924 * x0;
    else if( x0 > 0.996 && x0 < 0.998) 
      value = 2.9;
    else if( x0 > 0.998 && x0 < 0.999) 
      value = 2.6;
    else if ( x0 > 0.999 && x0 <= 1.0) 
      value = 1.02;
    else value = -1.1111;
    
    return (m_sign * value * toNU);
    
  };
  
};

class rhoEarthA : public DensityModels {
public: 
  
  /// Standard constructor
  rhoEarthA( ) : DensityModels() { m_sign = 1.0; }; 
  
  virtual ~rhoEarthA( ){}; ///< Destructor
  
  virtual double operator() (double *x, double *p) {

    double offset = p[5];
    double xx = x[0]+offset;
    
    double L1 = p[2] * p[4];
    double L2 = L1 + ( p[3] * p[4] );
    double A1 = p[0];
    double A2 = p[1];
    
    double result = 0.0;
    
    if ( xx <= L1 ) 
      result = A1;
    else if ( xx > L1 && xx <= L2 )
      result = A2;
    else if ( xx >= L2 ) 
      result = A1;
    else result = -1.1111;
    
    return m_sign * result;
    
  };
  
};


class nvEnergy {
public: 
  
  /// Standard constructor
  nvEnergy( ) {
    m_k0 = ( 1.0 / (4.0 * M_PI * DensityModels::InveV) );
  };
  
  virtual ~nvEnergy( ){}; ///< Destructor
  
  virtual double operator() (double *x, double *p) {
    
    return  m_k0 * sin( 2.0 * p[1] * M_PI / 180.0) * p[0] * p[2] * x[0];
    
  };
  
  double m_k0;
    
};  

class lR2d {
public: 
  
  /// Standard constructor
  lR2d( ) {
    m_k0 = 4.0 * M_PI * DensityModels::InveV * 1E12;
  };
  
  virtual ~lR2d( ){}; ///< Destructor
  
  virtual double operator() (double *x, double *p) {
    return  m_k0 * (x[1]/x[0]) * ( 1.0 / sin( 2.0 * p[0] * M_PI / 180.0 ));
  };
  
  double m_k0;
  
};  




#endif // DENSITYMODELS_H
