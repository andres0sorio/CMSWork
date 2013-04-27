// $Id: $
// Include files 



// local
#include "DisplayParallelCoord.h"
#include "TParallelCoord.h"
#include "TParallelCoordVar.h"
#include "TParallelCoordRange.h"


//-----------------------------------------------------------------------------
// Implementation file for class : DisplayParallelCoord
//
// 2009-06-27 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
DisplayParallelCoord::DisplayParallelCoord( const char * fileList , int mode ) {

  m_mode = mode;
  m_ccounter=0;
  m_debug = false;

  m_fileList = new std::ifstream( fileList , ifstream::in );
  
  if ( m_fileList->bad() ) m_noinputfile = true;
  else m_noinputfile = false;
  if ( m_noinputfile ) exit(1);

  int files(0);
    
  while (1) {
    
    std::string data;

    if ( m_fileList->fail()) break;
    (*m_fileList) >> data;
    if ( m_fileList->eof() ) break;
    
    //...open files 
        
    if ( mode == 2 ) {
      
      m_gzin = new gz::igzstream( data.c_str() );
      
      if ( m_gzin->bad() ) m_noinputfile = true;
      else m_noinputfile = false;
      
      m_sdin = NULL;
      
    } 
    
    if ( !m_noinputfile ) 
    {
    
      m_gzdataList.push_back( m_gzin );
          
    } else continue;
    
    files+=2;
    
  }

  std::cout << "Total files to be analyzed: " << files << std::endl;

  int maxfiles =  m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) 
  {
    std::cout << "file1 " << k << " isready: " <<  m_gzdataList[k]->good() << '\n';
  }
  
  std::cout << "Total files: " << maxfiles << std::endl;
  
  prepareHistograms();

  
}

void DisplayParallelCoord::prepareHistograms()
{
  
  for(int k = 0; k < 8; ++k)
    addCanvas();
  
  m_data = new TNtuple("nt","containers","flag:bunchNb:time:res24:res25:ndigis:wheel:secA:layA");
  
  hh[0] = new TH1D ( "wheels", "Wheel distribution in binary", 50, 0, 50);
  hh[1] = new TH1D ( "ndigis", "N digis distribution", 50, 0, 50);
  
  h2h[0] = new TH2D ( "ndigis.vs.rate", "N digis vs Rates", 50, 0, 50, 150, 0, 150);
    
  
}
//=============================================================================
// Destructor
//=============================================================================
DisplayParallelCoord::~DisplayParallelCoord() {


  
  if ( m_sdin ) { 
    m_sdin->close();
    delete m_sdin;
  }
  
  if ( m_gzin ) {
    m_gzin->close();
    delete m_gzin;
  }

} 

//=============================================================================
int DisplayParallelCoord::addCanvas() 
{
  
  std::ostringstream hname;
  
  hname << "DisplayParallelCoord.Canvas." << m_ccounter;
  
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

  return m_ccounter;
      
}

//=============================================================================
void DisplayParallelCoord::Loop()
{
  
  int evt(0);
  
  float wall_time(0.0);
  float timeOffset(0.0);
  float lastRecordedTime(0.0);
  
  if ( m_noinputfile ) return;
  
  int maxfiles = m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) 
  {
    m_gzin     = m_gzdataList[k];
    
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
      
      wall_time = info->m_time + timeOffset;

      if ( info->m_maxttBits > 0 ) {
        
        //... do some work
        if ( info->m_hasRpcInfo > 0 ) 
        {
          
          m_data->Fill( info->m_flag, 
                        info->m_bunchNumber, 
                        wall_time,
                        info->m_bitResult[0],
                        info->m_bitResult[1],
                        info->m_rpcNdigis, 
                        info->m_wheel,
                        info->m_sector[0], 
                        info->m_layer[0] );
          
          hh[0]->Fill(info->m_wheel);
          hh[1]->Fill(info->m_rpcNdigis);
          
          if ( info->m_outputRate == 1 ) {
            h2h[0]->Fill( info->m_rpcNdigis, info->m_ntriggered[0] );
          }
          
        }
        
        delete info;
        
        ++evt;
      }
      
      lastRecordedTime = (float)  info->m_time;
      
    }
    
    timeOffset += lastRecordedTime;
    
  }
  
  //
  
  canvas[0]->cd();
  m_data->Draw("res24:bunchNb:time:ndigis:wheel","","para", 500000);
  
  TParallelCoord* plot1 = (TParallelCoord*)gPad->GetListOfPrimitives()->FindObject("ParaCoord");
  plot1->SetDotsSpacing(5);
  
  TParallelCoordVar* firstaxis = (TParallelCoordVar*)plot1->GetVarList()->FindObject("bunchNb");
  firstaxis->AddRange(new TParallelCoordRange(firstaxis, 111.0, 111.9) );
  plot1->AddSelection("blue");
  plot1->GetCurrentSelection()->SetLineColor(kBlue);
  
  canvas[1]->cd();
  hh[0]->Draw();
  
  canvas[2]->cd();
  hh[1]->Draw();
  
  canvas[3]->cd();
  h2h[0]->Draw("box");
  
  
}

