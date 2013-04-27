// $Id: $
// Include files 



// local
#include "Analyze.h"
#include <TCanvas.h>
#include <TStyle.h>


//-----------------------------------------------------------------------------
// Implementation file for class : Analyze
//
// 2012-08-08 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Analyze::Analyze( const char * infile  ) {

  m_debug = false;
  
  m_d1 = new Data( infile );
  m_d1->Read();
  
  if(m_debug) m_d1->Show();
  
}

Analyze::Analyze( const char * infile1  ,  const char * infile2) {

  m_debug = false;
  
  m_d1 = new Data( infile1 );
  m_d1->Read();
  
  m_d2 = new Data( infile2 );
  m_d2->Read();

  std::cout << m_d1->m_Results.size() << " " << m_d2->m_Results.size() << std::endl;
  std::cout << m_d1->m_Results[0]->m_weights.size() << " " << m_d2->m_Results[0]->m_weights.size() << std::endl;

  m_maxEvts = m_d1->m_Results[0]->m_weights.size();
  
  if(m_debug) { 
    m_d1->Show();
    m_d2->Show();
  }
  
  
}

//=============================================================================
// Destructor
//=============================================================================
Analyze::~Analyze() {
  
  delete m_d1;
  delete m_d2;
  
} 

//=============================================================================

void Analyze::Run()
{
  
  std::stringstream dscSB(std::stringstream::in | std::stringstream::out);
    
  std::vector<MadWeightResults*>::iterator itrD1;
  std::vector<MadWeightResults*>::iterator itrD2;

  itrD1 = m_d1->m_Results.begin();
  itrD2 = m_d2->m_Results.begin();

  for( itrD1 = m_d1->m_Results.begin(); itrD1 != m_d1->m_Results.end(); ++itrD1) {
    
    int ID1 = (*itrD1)->m_ID;
    int ID2 = (*itrD2)->m_ID;
    
    dscSB << "dscSB_" << ID1 << ID2;

    std::cout << "Run> calculating Ps/(Ps+Pb) " << dscSB.str() << std::endl;
    
    
    h_1DHistContainer[dscSB.str().c_str()] = new TH1F(dscSB.str().c_str(),
                                                      "MadWeight - Discriminator", 50, 0.0, 1.0 );
    
    for( int k=0; k< m_maxEvts; ++k ) {
      
      double Ps = (*itrD1)->m_weights[k];
      double Pb = (*itrD2)->m_weights[k];
      double discriminator = Ps / (Ps + Pb);
      
      h_1DHistContainer[dscSB.str().c_str()]->Fill( discriminator );
      
    }
    
    dscSB.str("");
    
    ++itrD2;
    
  }
  
  TCanvas * c1 = new TCanvas();
  c1->SetFillColor(10);
  c1->Divide(2,2);
  c1->cd(1);
  
  h_1DHistContainer["dscSB_11"]->Draw();
  

  c1->Print("c1.eps");
    

}
