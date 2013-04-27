#ifndef NUN_XSEC_H 
#define NUN_XSEC_H 1

// Include files

#include "RootCommon.h"
#include "GSLHelpers.h"
#include "Math/GSLIntegrator.h"
#include "LHAPDF/LHAPDF.h"
#include <iterator>

double xqx(double *, double * );

double xqbarx( double *, double * );

double XsecCC( double );

double dXsecCCdx( double , void * );

double dXsecCCdxdy( double , void * );

double evalxsec ();

#endif // NUN_XSEC_H
