#include "nuN_xsec.h"

const double Gf = 1.16632e-15; //G_fermi
const double Mn = 0.939573; //M nucleon
const double Mw = 81.800;
const double Mz = 91.600;

//........................................................................

double xqx(double *xx, double *par ) {

  double x = xx[0];
  double Q = xx[1];
  
  double fq = 0.5*LHAPDF::xfx( x , Q , 2) 
    + 0.5*LHAPDF::xfx( x , Q , 1)
    + LHAPDF::xfx( x, Q, 3)
    + LHAPDF::xfx( x, Q, 5);

  //std::cout << "xqx= " << fq << std::endl;
  
  return fq;
  
}

double xqbarx( double *xx, double *par  ) {
  
  double x = xx[0];
  double Q = xx[1];
  
  double fqbar = 0.5*LHAPDF::xfx( x , Q , 2) 
    + 0.5*LHAPDF::xfx( x , Q , 1)
    + LHAPDF::xfx( x, Q, 3)
    + LHAPDF::xfx( x, Q, 5);
  
  //std::cout << "xqbarx= " << fqbar << std::endl;

  return fqbar;
  
}

//........................................................................

double XsecCC( double x ) {

  IntParams * p1 = new IntParams();
  
  p1->Q2 = 100000.0;
  
  double xlow = 0.00000000001;
  double xupp = x;

  ROOT::Math::GSLFuncPointer ff = &dXsecCCdx;
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-12, 1000 );
  
  nminteg->SetFunction( ff );

  //--range [xmin,xmax]
  double result = nminteg->Integral(ff, p1 , xlow , xupp);
  
  delete nminteg;
  delete p1;

  return result;
    
}

//integrate w.r.t. -y-

double dXsecCCdx( double x, void * pars) {
  
  double ylow = 0.001;
  double yupp = 0.1;
  
  IntParams * p1 = (IntParams*)(pars);
  p1->varx = x;
  
  ROOT::Math::GSLFuncPointer ff = &dXsecCCdxdy;
  
  ROOT::Math::GSLIntegrator * nminteg = 
    new ROOT::Math::GSLIntegrator( 1.E-12, 1.E-12, 1000 );
  
  nminteg->SetFunction( ff );

  //--range [xmin,xmax]
  double result = nminteg->Integral(ff, p1 , ylow , yupp);
  
  delete nminteg;

  return result;
  
}

double dXsecCCdxdy( double y, void * pars) {

  IntParams * p1 = (IntParams*)(pars);

  double xx[2];
  double par[1];
  
  xx[0]  = p1->varx;
  xx[1]  = p1->Q2;
  par[0] = 1.0;
  
  double Q2    = p1->Q2;

  double Enu =  Q2 / ( xx[0]*y*2*Mn );
    
  double f1 = ( xqx(xx,par) + xqbarx(xx,par)*(1 - y) );

  double f2 = (2.0 * Gf * Gf * Mn * Enu) * ( ( Mw*Mw )/( Q2 + Mw*Mw) ) * ( ( Mw*Mw )/( Q2 + Mw*Mw) ) * f1; 

  return f2;

}

double evalxsec () {
  
  const int SUBSET = 0;
  const string NAME = "cteq5d";
  
  LHAPDF::initPDFSet(NAME, LHAPDF::LHGRID, SUBSET);
  
  LHAPDF::initPDF(0);
  
  const double Q = 10000.0;

  double xx[2];
  xx[0] = 0.001;
  xx[1] = 0.001;
  
  double pars[1];
  pars[0] = Q;
  
  //std::cout << "diffXsec: " << dXsecCCdxdy( xx, pars ) <<  std::endl;

  std::cout << "Xsec: " << XsecCC(1.0) <<  std::endl;

  return 1.0;

}

#include "LHAPDF/FortranWrappers.h"
#ifdef FC_DUMMY_MAIN
int FC_DUMMY_MAIN() { return 1; }
#endif

