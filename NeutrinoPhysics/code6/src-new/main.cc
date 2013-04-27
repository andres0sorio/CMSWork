// $Id: 
// Include files 

#include <Graphics.h>
#include <nuN_interpxsec.h>
#include <Derivatives.h>

int main(int iargv, const char **argv) {
  
  Graphics      * graphs = new Graphics();
  Interpolation * nu_xsec_interp   = new Interpolation( "XSec_neut.dat" );
  Derivatives   * nu_xsec_derivator = new   Derivatives( nu_xsec_interp );
  
  float m_x = 100;
  float xmax = 10000;
  float dx = 100;
  double sigma = 0.0;
  double dsigma = 0.0;
  
  float m_y = 0.0;
  float dy = 0.1;
      
  while ( m_y < 1.0 ) 
  {

    m_x = 10000.0;
   
    sigma =  pow( 10.0, nu_xsec_interp->evaluateCC( log10( m_x ) ) );
    
    dsigma = nu_xsec_derivator->evaluateCC( log10(m_x ) );
    
    float inv_ydif2 = (1.0 / (1.0 - m_y )) * (1.0 / (1.0 - m_y ));
    
    std::cout << m_y << '\t'
              << sigma << '\t'
              << dsigma << '\t' 
              << (1.0/sigma) * dsigma * inv_ydif2 << std::endl;
  
  m_y = m_y + dy;
    
  }
    
  /*
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",526,216,650,500);
  c1->SetFillColor(10);
  c1->cd();
  graphs->g1->Draw("ACP");
  graphs->g2->Draw("CP");
  c1->Print("ratio.vs.phi_new.png");
  */

  delete graphs;
  delete nu_xsec_interp;
  delete nu_xsec_derivator;
    
  return 1;
    
}
