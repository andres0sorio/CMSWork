// $Id: 
// Include files 

#include <fstream>
#include <Graphics.h>
#include <nuN_interpxsec.h>
#include <Derivatives.h>

double dsigmady( double y ) 
{
  return 5.47 * exp ( - y );
}

int main(int iargv, const char **argv) {
  
  Graphics      * graphs = new Graphics();
  Interpolation * nu_xsec_interp   = new Interpolation( "XSec_neut.dat" );
  Derivatives   * nu_xsec_derivator = new   Derivatives( nu_xsec_interp );
  
  float m_x = 100;
  float xmax = 10000;
  float dx = 99;
  double sigma = 0.0;
  double dsigma = 0.0;
  
  float m_y = 0.0;
  float dy = 0.01;
   
  int k = 0;

  std::ofstream * m_out = new std::ofstream("derivatives-data.csv");
  
  //1.0
  while ( m_x < xmax ) 
  {
   
    sigma =  pow( 10.0, nu_xsec_interp->evaluateCC( log10( m_x ) ) );
    
    dsigma = nu_xsec_derivator->evaluateCC( m_x );
    
    graphs->g1->SetPoint(k, m_x, (1.0/sigma) * dsigma );
  
    (*m_out) << m_x << "," << dsigma*100000 << std::endl;
      
    k = k + 1;
    m_x = m_x + dx;
    
  }
   
  m_out->close();
   
  std::cout << "Ok" << std::endl;
  

  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  c1->SetFillColor(10);
  c1->cd();
  graphs->g1->Draw("ACP");
  c1->Print("dsigma_denu.png");

  k = 0;
  m_x = 100;


  //1.1
  while ( m_x < xmax ) 
  {
   
    sigma =  pow( 10.0, nu_xsec_interp->evaluateCC( log10( m_x ) ) );

    dsigma = nu_xsec_derivator->evaluateCC( m_x );
    
    graphs->g2->SetPoint(k, m_x, sigma );
    
    k = k + 1;
    m_x = m_x + dx;
    
  }

  c1->cd();
  graphs->g2->Draw("ACP");
  c1->Print("sigma_enu.png");

  //0. Test function (x^2)

  m_x = 0.0;
  
  Derivatives   * test_derivator = new   Derivatives( );

  while (m_x < 100) 
  {
    sigma = test_derivator->evaluateTest( m_x );
    //std::cout << m_x << "," << sigma << std::endl;
    m_x = m_x + 0.5;
  }
  
  delete graphs;
  delete nu_xsec_interp;
  delete nu_xsec_derivator;
  delete test_derivator;
  
  return 1;
    
}
