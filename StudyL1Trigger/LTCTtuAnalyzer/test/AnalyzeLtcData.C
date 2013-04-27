// $Id: $
// Include files 



// local
#include "AnalyzeLtcData.h"

//-----------------------------------------------------------------------------
// Implementation file for class : AnalyzeLtcData
//
// 2009-06-26 : Andres Felipe Osorio Oliveros
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
AnalyzeLtcData::AnalyzeLtcData( const char * filename , int mode) {

  m_mode = mode;
    
  if (mode == 1 ) {
    
    m_sdin = new std::ifstream( filename , ifstream::in );
    
    if ( m_sdin->bad() ) m_noinputfile = true;
    else m_noinputfile = false;
    
    m_gzin = NULL;
    
  } else if ( mode == 2 ) {
    
    m_gzin = new gz::igzstream( filename );
    
    if ( m_gzin->bad() ) m_noinputfile = true;
    else m_noinputfile = false;
    
    m_sdin = NULL;
    
  } else {}
  
  std::cout << m_noinputfile << std::endl;

  m_ccounter=0;
  
  int status(0);
  
  hh[0]  = new TH1D("Time.diff","Time diference between two successive peaks", 200, -0.1, 5.0);
  status = addCanvas();
  
  hh[1]  = new TH1D("Trigger.Rate","Trigger rate Hz", 100000, 0.0, 10000);
  status = addCanvas();
  
  hh[2]  = new TH1D("Peaks.in.bN","Peaks in bunch number", 100000, 0.0, 10000);
  status = addCanvas();
  
}
//=============================================================================
// Destructor
//=============================================================================
AnalyzeLtcData::~AnalyzeLtcData() {
  
  if ( m_sdin ) { 
    m_sdin->close();
    delete m_sdin;
  }
  
  if ( m_gzin ) {
    m_gzin->close();
    delete m_gzin;
  }
  
} 

int AnalyzeLtcData::addCanvas() 
{
  
  std::ostringstream hname;
  
  hname << "AnalyzeLtcData.Canvas." << m_ccounter;
  
  TCanvas *c1 = new TCanvas( hname.str().c_str(), "Analysis area", 406, 253, 698, 498);
  c1->SetFillColor(10);
  c1->Range(0,0,1,1);
  c1->SetBorderSize(1);
  c1->SetFrameFillColor(0);
  c1->Modified();
  c1->cd();
  c1->SetSelected(c1);
  c1->Draw();
  
  canvas[m_ccounter] = c1;
  
  ++m_ccounter;
    
}

//=============================================================================
void AnalyzeLtcData::Loop()
{
  
  int evt(0);
  
  double current_time = 0.0;
  double prev_time = 100.0;
  double deltaT = 0.0;
  bool m_debug = false;
  
  if ( ! m_noinputfile ) {
    
    while(1) {
      
      L1GtExtractedInfo * info = new L1GtExtractedInfo();
      
      if ( m_mode == 1 ) {
        
        (*m_sdin) >> (*info);
        if( m_sdin->eof() ) break;
        
      } else if ( m_mode == 2 ) {
        
        (*m_gzin) >> (*info);
        if( m_gzin->eof() ) break;
        
      } else {}
      
      if (m_debug) std::cout << (*info) ;
      
      //... do some work
      
      if ( info->m_bunchNumber == 134 ) {
        
        current_time = info->m_time;
        deltaT = current_time - prev_time;
        hh[0]->Fill( deltaT );
        prev_time = current_time;
        
        hh[2]->Fill( info->m_time , 10 );
        
      }
      
      if ( info->m_outputRate == 1 ) {
        hh[1]->Fill( info->m_time , info->m_ntriggered );
      }
      
      delete info;
      
      ++evt;
      
    }
    
  } else {
    
    std::cout << "No file opened" << std::endl;
    
  }
  
  canvas[0]->cd();
  hh[0]->Draw();

  canvas[1]->cd();
  hh[1]->Draw();

  canvas[2]->cd();
  hh[1]->Draw();
  hh[2]->Draw("same");
  
  
}

