// $Id: $
// Include files 



// local
#include "logpar_interp.h"

//-----------------------------------------------------------------------------
// Implementation file for class : logpar_interp
//
// 2011-12-20 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
logpar_interp::logpar_interp(  ) {}

logpar_interp::logpar_interp( const char * fname ) {
  
  m_in = new std::ifstream(fname, ifstream::in);
  
  if(!m_in->is_open()) {
    std::cout << "Data> cannot open file" << std::endl;
  } else { 
    std::cout << "Data> file is now open" << std::endl;
  }
  
  m_xx.clear();
  m_yy.clear();
  
  double xx = 0.0;
  double yy = 0.0;
  double oldxx = 0.0;
  
  while( m_in->good() ) {
    
    if ( m_in->eof() ) break;
    
    (*m_in) >> xx >> yy;

    m_xx.push_back( xx );
    m_yy.push_back( yy );

    oldxx = xx;
    
    if ( m_in->fail()) break;
    
  }
  
  m_xx.pop_back();
  m_yy.pop_back();
  
  m_interpolator = new  ROOT::Math::Interpolator( m_xx, m_yy, ROOT::Math::Interpolation::kLINEAR);

  
}

//=============================================================================
// Destructor
//=============================================================================
logpar_interp::~logpar_interp() {
  
  delete m_interpolator;

  m_in->close();
  
  if (m_in )
    delete m_in;
  
} 

//=============================================================================
double logpar_interp::operator() (double *x, double *p) 
{

  double p1 = p[0];
  double ff = m_interpolator->Eval( x[0] );
  return ff;
  
}
