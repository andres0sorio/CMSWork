//
//
//
#include <algorithm>

int index = 0;
bool m_debug = false;

std::map<double, double> points;
std::map<double, double>::iterator itrP;

bool compare( double v1, double v2) 
{
  return (v1 <= v2 );
    
}


double interpolateFunction ( double * x, double * p ) 
{
  

  std::map<double, double>::iterator itr;

  //iterar sobre los valores de E, hasta obtener un valor > que el de energia actual - detenerse
  // Asi obtengo el E_(i+1)
  for( itr = points.begin(); itr != points.end(); ++itr) {
    if ( (*itr).first > x[0] ) { if(m_debug) std::::cout << " ->" << '\n'; break; }
  }
  
  if ( itr == points.begin() ) ++itr;
  
  itrP = itr;

  // E_(i+1), phi_(i+1)
  double xi1 = (*itrP).first;
  double yi1 = (*itrP).second;

  if(m_debug) std::cout << " * i+1 " << xi1 << " " << yi1 << " " << std::endl;

  // Conociendo E_(i+1), hago un paso atras para obtener E_(i) y phi_(i)
  double xi = (*(--itrP)).first;
  double yi = (*itrP).second;

  if(m_debug) std::cout << " * i " << xi << " " << yi << " " << std::endl;

  double slope = (yi1 - yi)/(xi1-xi);
      
  return slope*( x[0] - xi) + yi;
  
}


void interpolator( TGraph * gInput )
{
    
  int maxpoints = gInput->GetN();
  
  TGraph * gOut = new TGraph();
  
  int i = 0;
  
  for( int k = 0; k < maxpoints; ++k ) {
    
    double xx(0.);
    double yy(0.);
    
    int stat =  gInput->GetPoint( k , xx, yy);

    if ( k  % 1000 == 0 ) {

      //std::cout << k << " point: " << xx << " " << yy << '\n';
      
      points[xx] = yy;
      gOut->SetPoint( i, xx , yy );
      ++i;
      
    }
    
    
  }
  
  std::cout << points.size() << std::endl;
    
  gOut->SetMarkerColor(2);
  gOut->SetMarkerStyle(4);
  gOut->SetMarkerSize(1.1);
  gOut->Draw("P");

  double xmin  = 0.8E11;
  double xmax  = 1.0E14;
  
  TF1 * f1 = new TF1("interp", interpolateFunction, xmin, xmax, 1);
  f1->SetNumberFitPoints( 40 );
  f1->Draw("SAME");

  double deltax = 0.02E11;

  double par = 1.0;
  
  for( int k = 0; k < 5; ++k) {
    
    double ymin = interpolateFunction( &xmin, &par );
    std::cout << k << " " << xmin << " " << ymin << std::endl;
    xmin+=deltax;
    
  }

  std::map<double, double>::iterator itr;
  
  int np = 0;
  
  for( itr = points.begin(); itr != points.end(); ++itr) {
    std::cout << " * " << (*itr).first << " " << (*itr).second << " " << std::endl;  
    if ( np > 5) break;
    ++np;
  }
  
  
 
}
