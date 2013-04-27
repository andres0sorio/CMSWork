// $Id: $
// Include files 



// local
#include "HistoRates.h"
#include "TFrame.h"
//-----------------------------------------------------------------------------
// Implementation file for class : HistoRates
//
// 2010-03-02 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
HistoRates::HistoRates(  ) {

  max_buff_size = 200;
  isfirst = false;
  m_hotSector = false;
  m_YLimit = 50000;
  
  std::ostringstream hname;
  m_colour["WP1"] = 2; //red
  m_colour["WP2"] = 3; //green
  m_colour["W00"] = 4; //blue
  m_colour["WM1"] = 6; //purple
  m_colour["WM2"] = 8; //dark-green
  
  m_wcolour.push_back(m_colour["WP1"]);
  m_wcolour.push_back(m_colour["WP2"]);
  m_wcolour.push_back(m_colour["W00"]);
  m_wcolour.push_back(m_colour["WM1"]);
  m_wcolour.push_back(m_colour["WM2"]);
  
  for(int k=0; k < 5; ++k) 
  {
    wheelRates[k] = new TGraph(1000);
    wheelRates[k]->SetMinimum(0);
    wheelRates[k]->SetMaximum( m_YLimit );
    wheelRates[k]->SetMarkerStyle(20);
    wheelRates[k]->SetMarkerSize(1.0);
    wheelRates[k]->SetMarkerColor( m_wcolour[k] );
    wheelRates[k]->SetLineColor( m_wcolour[k] );
  
    hname << "sectorRatesW" << k ;
    secRatesSummary[k] = new TH1D(hname.str().c_str(), "Sector counts summary", 14, 0, 14);
    secRatesSummary[k]->SetLineColor( m_wcolour[k] );
    secRatesSummary[k]->SetFillColor( m_wcolour[k] );
    secRatesSummary[k]->SetFillStyle( 3001 );
    hname.str("");

    





  }

  for(int k=0; k < 12; ++k)
  {
    sectorRatesWM2[k] = new TGraph(1000);
    sectorRatesWM2[k]->SetMinimum(0);
    sectorRatesWM2[k]->SetMaximum( m_YLimit );
    sectorRatesWM2[k]->SetMarkerStyle(20);
    sectorRatesWM2[k]->SetMarkerSize(0.4);
    sectorRatesWM2[k]->SetMarkerColor(m_colour["WM2"]);
    sectorRatesWM2[k]->SetLineColor(m_colour["WM2"]);
    
    sectorRatesWM1[k] = new TGraph(1000);
    sectorRatesWM1[k]->SetMinimum(0);
    sectorRatesWM1[k]->SetMaximum( m_YLimit );
    sectorRatesWM1[k]->SetMarkerStyle(20);
    sectorRatesWM1[k]->SetMarkerSize(0.4);
    sectorRatesWM1[k]->SetMarkerColor(m_colour["WM1"]);
    sectorRatesWM1[k]->SetLineColor(m_colour["WM1"]);
    
    sectorRatesW00[k] = new TGraph(1000);
    sectorRatesW00[k]->SetMinimum(0);
    sectorRatesW00[k]->SetMaximum( m_YLimit );
    sectorRatesW00[k]->SetMarkerStyle(20);
    sectorRatesW00[k]->SetMarkerSize(0.4);
    sectorRatesW00[k]->SetMarkerColor(m_colour["W00"]);
    sectorRatesW00[k]->SetLineColor(m_colour["W00"]);
        
    sectorRatesWP1[k] = new TGraph(1000);
    sectorRatesWP1[k]->SetMinimum(0);
    sectorRatesWP1[k]->SetMaximum( m_YLimit );
    sectorRatesWP1[k]->SetMarkerStyle(20);
    sectorRatesWP1[k]->SetMarkerSize(0.4);
    sectorRatesWP1[k]->SetMarkerColor(m_colour["WP1"]);
    sectorRatesWP1[k]->SetLineColor(m_colour["WP1"]);
    
    sectorRatesWP2[k] = new TGraph(1000);
    sectorRatesWP2[k]->SetMinimum(0);
    sectorRatesWP2[k]->SetMaximum( m_YLimit );
    sectorRatesWP2[k]->SetMarkerStyle(20);
    sectorRatesWP2[k]->SetMarkerSize(0.4);
    sectorRatesWP2[k]->SetMarkerColor(m_colour["WP2"]);
    sectorRatesWP2[k]->SetLineColor(m_colour["WP2"]);

  }
  
  m_selectedWheel.reset();
  m_selectedWheel.flip();
  
}
//=============================================================================
// Destructor
//=============================================================================
HistoRates::~HistoRates() {} 

//=============================================================================
void HistoRates::addTime( int time)
{

  buff_time.push_back(time);
  
  if ( (int) buff_time.size() > max_buff_size )
  {
    //remove first element
    buff_time.erase( buff_time.begin()+0 );
  }
  
}

void HistoRates::addwheelRate( int wheel, float rate)
{
  
  buff_wheelrates[wheel].push_back( rate );
  
  if ( (int)buff_wheelrates[wheel].size() > max_buff_size )
  {
    //remove first element
    buff_wheelrates[wheel].erase( buff_wheelrates[wheel].begin()+0);
  }
  
  ///////////////////////////////////////////////////////////////////////

}

void HistoRates::addsectorRates( float *r1, float *r2, float *r3, float *r4, float *r5)
{
  
  ///////////////////////////////////////////////////////////////////////
  
  for(int i=0; i < 12; ++i) 
  {
    
    buff_sectorRatesWM2[i].push_back( r1[i] );
    buff_sectorRatesWM1[i].push_back( r2[i] );
    buff_sectorRatesW00[i].push_back( r3[i] );
    buff_sectorRatesWP1[i].push_back( r4[i] );
    buff_sectorRatesWP2[i].push_back( r5[i] );

    secRatesSummary[4]->Fill( i, r1[i] );
    secRatesSummary[3]->Fill( i, r2[i] );
    secRatesSummary[2]->Fill( i, r3[i] );
    secRatesSummary[0]->Fill( i, r4[i] );
    secRatesSummary[1]->Fill( i, r5[i] );
    
  }
  
  if ( (int) buff_sectorRatesWM2[0].size() > max_buff_size )
  {
    
    for(int i=0; i < 12; ++i) 
    {
     
      buff_sectorRatesWM2[i].erase( buff_sectorRatesWM2[i].begin()+0);
      buff_sectorRatesWM1[i].erase( buff_sectorRatesWM1[i].begin()+0);
      buff_sectorRatesW00[i].erase( buff_sectorRatesW00[i].begin()+0);
      buff_sectorRatesWP1[i].erase( buff_sectorRatesWP1[i].begin()+0);
      buff_sectorRatesWP2[i].erase( buff_sectorRatesWP2[i].begin()+0);
      
    }
    
  }


}

void HistoRates::DrawWheelRates(TCanvas * fCanvas) 
{

  float yy[1000];
  int first = 0;
  bool is_first_done = false;

  fCanvas->SetLogy(1);
  
  for(int i=0; i < 5; ++i) 
  {
    
    ///////////////////////////////////////////////////////////////////////

    if ( ! m_selectedWheel[i] ) 
    {
      first+=1;
      continue;
    }
    
    
    int max = copyToArray( buff_wheelrates[i] , yy );
    
    if ( i == first & (!is_first_done) )
    {
      delete wheelRates[first];
      wheelRates[first] = new TGraph( max, &buff_time[0] , yy );
      wheelRates[first]->SetTitle("Wheel Rates");
      wheelRates[first]->SetMinimum(0);
      wheelRates[first]->SetMaximum( m_YLimit );
      wheelRates[first]->SetMarkerStyle(20);
      wheelRates[first]->SetMarkerSize(1.0);
      wheelRates[first]->SetMarkerColor(m_wcolour[first]);
      wheelRates[first]->SetLineColor(m_wcolour[first]);
      wheelRates[first]->GetXaxis()->SetLimits( buff_time[0], buff_time[0]+max_buff_size);
      wheelRates[first]->Draw("alp");
      is_first_done = true;
    }
    else
      wheelRates[i]->DrawGraph( max, &buff_time[0] , yy , "pl");
    
    fCanvas->Update();
    
  }
  
}

void HistoRates::DrawSectorRates(TCanvas * fCanvas, Bool_t logscale) 
{

  int max = 0;
  bool is_first = true;
  std::ostringstream gname;
  float yy[1000];

  //std::cout << m_selectedWheel.to_string() << std::endl;
  
  for(int i=0; i < 12; ++i) 
  {
    
    fCanvas->Update();
    fCanvas->cd(i+1);
    gPad->Clear();
    gPad->SetGridy();
    gPad->SetFillColor(10);

    logscale = true;

    if ( logscale == true)
      gPad->SetLogy();
    else
      gPad->SetLogy(0);
    
    gPad->Update();
    
    gname << "Sector [" << (i+1) << "] Rates";
    
    //////////////////////////////////////////////////////////////////////
    //
    
    is_first = true;
    m_hotSector = false;
    
    if ( m_selectedWheel[4] ) 
    {
      
      if( is_first ) 
      {
        delete sectorRatesWM2[i];
        max = copyToArray( buff_sectorRatesWM2[i], yy );

        if ( m_hotSector ) {
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }
                
        sectorRatesWM2[i] = new TGraph( max, &buff_time[0] , yy );
        sectorRatesWM2[i]->SetTitle( gname.str().c_str() );
        setGraphOptions( sectorRatesWM2[i], m_colour["WM2"] );
        sectorRatesWM2[i]->GetXaxis()->SetLimits( buff_time[0], buff_time[0]+max_buff_size);
        sectorRatesWM2[i]->Draw("alp");
        is_first = false;
        m_hotSector = false;
        
      }
      
    }
    
    if ( m_selectedWheel[3] ) 
    {
      
      if ( is_first ) 
      {
        delete sectorRatesWM1[i];
        max = copyToArray( buff_sectorRatesWM1[i], yy );
        
        if ( m_hotSector ) {
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }

        sectorRatesWM1[i] = new TGraph( max, &buff_time[0] , yy );
        sectorRatesWM1[i]->SetTitle( gname.str().c_str() );
        setGraphOptions( sectorRatesWM1[i], m_colour["WM1"] );
        sectorRatesWM1[i]->GetXaxis()->SetLimits( buff_time[0], buff_time[0]+max_buff_size);
        sectorRatesWM1[i]->Draw("alp");
        is_first = false;
        m_hotSector = false;
      } else 
      {
        max = copyToArray( buff_sectorRatesWM1[i], yy );
        if ( m_hotSector ) { 
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }
        
        sectorRatesWM1[i]->DrawGraph( max, &buff_time[0] , yy , "pl");
        m_hotSector = false;
      }
      
    }
    
    
    if ( m_selectedWheel[2] ) 
    {
      if ( is_first ) 
      {
        delete sectorRatesW00[i];
        max = copyToArray( buff_sectorRatesW00[i], yy );
        
        if ( m_hotSector ) {
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }

        sectorRatesW00[i] = new TGraph( max, &buff_time[0] , yy );
        sectorRatesW00[i]->SetTitle( gname.str().c_str() );
        setGraphOptions( sectorRatesW00[i], m_colour["W00"] );
        sectorRatesW00[i]->GetXaxis()->SetLimits( buff_time[0], buff_time[0]+max_buff_size);
        sectorRatesW00[i]->Draw("alp");
        is_first = false;
        m_hotSector = false;
      } else 
      {
        max = copyToArray( buff_sectorRatesW00[i], yy );
        if ( m_hotSector ) { 
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }
                
        sectorRatesW00[i]->DrawGraph( max, &buff_time[0] , yy , "pl");
        m_hotSector = false;
      }
      
    }
    
    
    if ( m_selectedWheel[0] ) 
    {
      
      if ( is_first ) 
      {
        delete sectorRatesWP1[i];
        max = copyToArray( buff_sectorRatesWP1[i], yy );

        if ( m_hotSector ) {
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }

        sectorRatesWP1[i] = new TGraph( max, &buff_time[0] , yy );
        sectorRatesWP1[i]->SetTitle( gname.str().c_str() );
        setGraphOptions( sectorRatesWP1[i], m_colour["WP1"] );
        sectorRatesWP1[i]->GetXaxis()->SetLimits( buff_time[0], buff_time[0]+max_buff_size);
        sectorRatesWP1[i]->Draw("alp");
        is_first = false;
        m_hotSector = false;
      } else 
      { 
        max = copyToArray( buff_sectorRatesWP1[i], yy );
        if ( m_hotSector ) { 
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }
        
        sectorRatesWP1[i]->DrawGraph( max, &buff_time[0] , yy , "pl");
        m_hotSector = false;
      }
      
    }
    
    if ( m_selectedWheel[1] ) 
    {
      
      if ( is_first ) 
      {
        delete sectorRatesWP2[i];
        max = copyToArray( buff_sectorRatesWP2[i], yy );

        if ( m_hotSector ) {
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }


        sectorRatesWP2[i] = new TGraph( max, &buff_time[0] , yy );
        sectorRatesWP2[i]->SetTitle( gname.str().c_str() );
        setGraphOptions( sectorRatesWP2[i], m_colour["WP2"] );
        sectorRatesWP2[i]->GetXaxis()->SetLimits( buff_time[0], buff_time[0]+max_buff_size);
        sectorRatesWP2[i]->Draw("alp");
        is_first = false;
        m_hotSector = false;
      } else 
      {
        max = copyToArray( buff_sectorRatesWP2[i], yy );
        if ( m_hotSector ) { 
          gPad->SetFillColor(kOrange-4);
          gPad->GetFrame()->SetFillColor(10);
          gPad->GetFrame()->SetBorderMode(0);
        }
        
        sectorRatesWP2[i]->DrawGraph( max, &buff_time[0] , yy , "pl");
        m_hotSector = false;
      }
      
    }
    
    //////////////////////////////////////////////////////////////////////

    gPad->Update();
    
    gname.str("");
    
  }


}

void HistoRates::DrawSectorSummary(TCanvas * fCanvas) 
{
  
  fCanvas->cd();

  int pos = 0;
  float max0 = 0.0;
  
  for(int i=0; i < 5; ++i) 
  {
    
    float max = secRatesSummary[i]->GetMaximum();
    if ( max > max0 ) 
    {
      max0 = max;
      pos  = i;
    }
    
  }
  
  for(int i=0; i < 5; ++i) 
  {
    
    if( i == pos) 
      secRatesSummary[i]->Draw("B");
    else 
      secRatesSummary[i]->Draw("BSAME");
    
  }

}

void HistoRates::DrawSectorPie(TCanvas * fCanvas) 
{
  
  fCanvas->cd();

  int pos = 0;
  float max0 = 0.0;
  
  for(int i=0; i < 5; ++i) 
  {
    
    float max = secRatesSummary[i]->GetMaximum();
    if ( max > max0 ) 
    {
      max0 = max;
      pos  = i;
    }
    
  }
  
  for(int i=0; i < 5; ++i) 
  {
    
    if( i == pos) 
      secRatesSummary[i]->Draw("POL");
    else 
      secRatesSummary[i]->Draw("POLSAME");
    
  }

}

int HistoRates::copyToArray( const std::vector<float> & vecIn, float * arrOut)
{
  
  int max =  vecIn.size();
  std::vector<float>::const_iterator itrYY;

  for(int j=0; j < 1000; ++j)
    arrOut[j] = 0;
  
  int k = 0;
  for( itrYY= vecIn.begin(); itrYY != vecIn.end(); ++itrYY) 
  {
    arrOut[k] = (*itrYY);
    if( (*itrYY) > m_YLimit )
      this->m_hotSector = true;
    ++k;
  }
  
  return max;
  
}

void HistoRates::setGraphOptions( TGraph * g1, int colour ) 
{
  
  
  g1->SetMinimum(0);
  g1->SetMaximum(50000);
  g1->SetMarkerStyle(20);
  g1->SetMarkerColor( colour );
  g1->SetMarkerSize(0.4);
  g1->SetLineColor( colour );
  
  
}
