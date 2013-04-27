// $Id: $
// Include files 

// local
#include "CompareDataEmulator.h"
#include "TLatex.h"

//-----------------------------------------------------------------------------
// Implementation file for class : CompareDataEmulator
//
// 2009-06-30 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

CompareDataEmulator::CompareDataEmulator( const char * fileList, int mode  ) {
  
  m_mode = mode;
  m_ccounter = 0;
  m_debug = false;
  m_timeFactor = 1;
  m_timeSampling = 10; //seconds
  
  m_fileList = new std::ifstream( fileList , ifstream::in );
  
  if ( m_fileList->bad() ) m_noinputfile = true;
  else m_noinputfile = false;
  if ( m_noinputfile ) exit(1);

  int files(0);
    
  while (1) {
    
    std::string data1;
    std::string emul1;

    if ( m_fileList->fail()) break;
    (*m_fileList) >> data1 >> emul1;
    if ( m_fileList->eof() ) break;
    
    //...open files 
        
    if ( mode == 2 ) {
      
      m_gzinData = new gz::igzstream( data1.c_str() );
      
      if ( m_gzinData->bad() ) m_noinputfile = true;
      else m_noinputfile = false;
      
      m_sdinData = NULL;
      
      m_gzinEmulator = new gz::igzstream( emul1.c_str() );
      
      if ( m_gzinEmulator->bad() ) m_noinputfile = true;
      else m_noinputfile = false;
      
      m_sdinEmulator = NULL;
      
    } 
    
    if ( !m_noinputfile ) 
    {
    
      m_gzdataList.push_back( m_gzinData );
      m_gzemulList.push_back( m_gzinEmulator );
      
    } else continue;
    
    files+=2;
    
  }

  std::cout << "Total files to be analyzed: " << files << std::endl;

  int maxfiles =  m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) 
  {
    std::cout << "file1 " << k << " isready: " <<  m_gzdataList[k]->good() << '\t'
              << "file2 " << k << " isready: " <<  m_gzemulList[k]->good() << '\n';
    
  }
  
  std::cout << "Total files: " << maxfiles << std::endl;
  
  prepareHistograms();

}

CompareDataEmulator::CompareDataEmulator( const char * fileData, const char * fileEmulator, int mode  ) {
  
  m_mode = mode;
  m_ccounter = 0;
  m_debug = false;
  m_timeFactor = 1;
  
  if (mode == 1 ) {
    
    m_sdinData = new std::ifstream( fileData , ifstream::in );
    
    if ( m_sdinData->bad() ) m_noinputfile = true;
    else m_noinputfile = false;
    
    m_gzinData = NULL;
    
    m_sdinEmulator = new std::ifstream( fileEmulator , ifstream::in );
    
    if ( m_sdinEmulator->bad() ) m_noinputfile = true;
    else m_noinputfile = false;
    
    m_gzinEmulator = NULL;
    
  } else if ( mode == 2 ) {
    
    m_gzinData = new gz::igzstream( fileData );
    
    if ( m_gzinData->bad() ) m_noinputfile = true;
    else m_noinputfile = false;
    
    m_sdinData = NULL;

    m_gzinEmulator = new gz::igzstream( fileEmulator );
    
    if ( m_gzinEmulator->bad() ) m_noinputfile = true;
    else m_noinputfile = false;
    
    m_sdinEmulator = NULL;

    if ( !m_noinputfile ) 
    {
      
      m_gzdataList.push_back( m_gzinData );
      m_gzemulList.push_back( m_gzinEmulator );
      
    }
    
        
  } else {}

  //...............................................................................

  std::cout << m_noinputfile << std::endl;

  prepareHistograms();
  
}


void CompareDataEmulator::prepareHistograms() 
{

  for(int k = 0; k < 15; ++k)
    addCanvas();
    
  m_data = new TNtuple("nt","containers","flag:bunchNb:time:res24:res25:ndigis:wheel:secA:layA");
  
  m_out = new std::ofstream("CompareDataEmulator.Output.txt");
  
  float maxRate=250.0;
  
  hh[0] = new TH1D("Emu.TT.Compare","Comparison between emulator and TT decisions", 7, 0, 7 );
  hh[1] = new TH1D("Trigger.Rate.Dist.B1","Trigger rate distribution [Hz]", 100, 0, maxRate );
  hh[2] = new TH1D("Time.Diff","Time difference between consecutive events",1000, 0, 1000.0);
  hh[3] = new TH1D("Event.Diff","Event difference between consecutive events",50, 0, 20);
  hh[4] = new TH1D("Trigger.Rate.Dist.B2","Trigger rate distribution [Hz]", 100, 0, maxRate );
  hh[5] = new TH1D("Special.Bx.Time","Time of appearance of Bn", 5000, 0, 5000 );
  hh[6] = new TH1D("Special.Bx.Time.Diff","Time difference between two consecutive peaks", 1000, 0, 10 );
  
  hc[0] = new TH1D("Emu.TT.Compare.0","Comparison between emulator and TT decisions", 7, 0, 7 );
  hc[1] = new TH1D("Emu.TT.Compare.1","Comparison between emulator and TT decisions", 7, 0, 7 );
  hc[2] = new TH1D("Emu.TT.Compare.2","Comparison between emulator and TT decisions", 7, 0, 7 );
  
  h2d[0] = new TH2D("Evt.Dif.vs.Time","Event difference vs time", 5000, 0, 5000, 50, 0, 50 );
 
  m_colors[0] = 9;
  m_colors[1] = 2;
  m_colors[2] = 8;
  
 
}

//=============================================================================
// Destructor
//=============================================================================
CompareDataEmulator::~CompareDataEmulator() {

  
  int maxfiles = m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) 
  {
    m_gzinData     = m_gzdataList[k];
    m_gzinEmulator = m_gzemulList[k];
  
    if ( m_gzinData ) {
      m_gzinData->close();
      delete m_gzinData;
    }
    
    if ( m_gzinEmulator ) {
      m_gzinEmulator->close();
      delete m_gzinEmulator;
    } 
    
  }
  
  m_gzdataList.clear();
  m_gzemulList.clear();

  if ( m_fileList ) {
    m_fileList->close();
    delete m_fileList;
  }
  
  for(int k = 0; k < 5; ++k)
    delete hh[k];
  
  for(int k = 0; k < 15; ++k)
    delete canvas[k];
    
  if ( m_data ) delete m_data;
  
} 

//=============================================================================
int CompareDataEmulator::addCanvas() 
{
  
  std::ostringstream hname;
  
  hname << "CompareDataEmulator.Canvas." << m_ccounter;
  
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
void CompareDataEmulator::Loop( int bit )
{
  
  int evt(0);

  int nevtExc(0);
  int matchBit(0);
  int mismatchBit(0);
  float wall_time(0.0);
  float timeOffset(0.0);
  float lastRecordedTime(0.0);
  int timeRequest(0);
  int bothTriggerData(0);
  int bothTriggerEmul(0);
  bool matched = false;
  
  std::vector<float> m_dataRate;
  std::vector<float> m_dataTime;
  std::vector<float> m_emuRate;
  std::vector<float> m_emuTime;
  
  if ( m_noinputfile ) return;
  
  //Loop over the list of files:
  
  int maxfiles = m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) 
  {
    m_gzinData     = m_gzdataList[k];
    m_gzinEmulator = m_gzemulList[k];
    
    while(1) {
      
      L1GtExtractedInfo * dataInfo = new L1GtExtractedInfo();
      L1GtExtractedInfo * emuInfo  = new L1GtExtractedInfo();
      
      matched = false;
      
      if ( m_mode == 1 ) {
        
        (*m_sdinData) >> (*dataInfo);
        (*m_sdinEmulator) >> (*emuInfo);
        
        if( m_sdinData->eof() ) break;
        if( m_sdinEmulator->eof() ) break;
        
      } else if ( m_mode == 2 ) {
        
        (*m_gzinData) >> (*dataInfo);
        (*m_gzinEmulator) >> (*emuInfo);
        
        if( m_gzinData->eof() ) break;
        if( m_gzinEmulator->eof() ) break;
        
      } else {}
      
      if (m_debug) std::cout << (*dataInfo) ;
      
      int bnData = dataInfo->m_bunchNumber;
      int bnEmu  = emuInfo->m_bunchNumber;
      
      if ( bnData != bnEmu ) { 
        std::cout << "Compare: " << k << std::endl;
        std::cout << "Event mismatch! check data" << std::endl;
        continue;
      }
      
      //...compare rates

      wall_time = dataInfo->m_time + timeOffset;

      if ( dataInfo->m_outputRate == 1 ) {
        
        if ( timeRequest > m_timeSampling ) {
          
          m_dataRate.push_back( dataInfo->m_ntriggered[bit] * m_timeFactor);
          m_dataTime.push_back( wall_time );
          
          m_emuRate.push_back( emuInfo->m_ntriggered[bit] * m_timeFactor);
          m_emuTime.push_back( wall_time );
          
          timeRequest = 0;
          
        } else timeRequest++;
        
      }
            
      if ( dataInfo->m_maxttBits > 0 ) {
        
        //... do some work here
        if ( dataInfo->m_hasRpcInfo > 0 ) 
        {
          
          //if ( bnData != 111 ) 
          //{
            
            int dataBit = dataInfo->m_bitResult[ bit ];
            int emuBit = emuInfo->m_bitResult[ bit ];
            
            discriminateDecision( dataBit, emuBit );
            
            if ( (dataBit == 1) && (dataBit == emuBit) ) {
              ++matchBit;
              matched = true;
            }
            else 
              ++mismatchBit;
            
            //this outputs to a ascii file

            if ( ( dataBit == 1 ) && (  emuBit == 0 ) ) 
              (*m_out) << "no match data=1 " << dataInfo->m_ievent 
                       << " e: " << emuInfo->m_ievent
                       << " " << 0 << std::endl;
            
            if ( ( dataBit == 0 ) && ( emuBit == 1) ) {
              (*m_out) << "no match data=0 " << dataInfo->m_ievent 
                       << " e: " << emuInfo->m_ievent
                       << " " << 1 
                       << " triggered by ";
              for( int i=0 ; i < dataInfo->m_maxttBits; ++i)
                (*m_out) << dataInfo->m_bitResult[ i ] << " ";
              (*m_out) << std::endl;
            }

            bool allagreeData = true;
            bool allagreeEmul = true;
            
            for( int i=2 ; i < 8; ++i) {
              if ( i == 1 ) continue;
              if( m_debug ) std::cout << dataInfo->m_bitResult[ i ] << " ";
              allagreeData |= (bool)  dataInfo->m_bitResult[ i ];
            }
            if( m_debug ) std::cout << '\n';
            
            for( int i=2 ; i < 8; ++i) {
              if ( i == 1 ) continue;
              if( m_debug ) std::cout << emuInfo->m_bitResult[ i ] << " ";
              allagreeEmul |= (bool)  emuInfo->m_bitResult[ i ];
            }
            
            if( m_debug ) std::cout << '\n';
            
            if ( allagreeData ) bothTriggerData+=1;
            if ( allagreeEmul ) bothTriggerEmul+=1;
            
            ++nevtExc;
            
            //}
          
        }
        
        
        delete dataInfo;
        delete emuInfo;
        
        ++evt;
      }
    
      lastRecordedTime = (float)  dataInfo->m_time;
      
    }
    
    timeOffset += lastRecordedTime;
    
  }
  
  std::cout << "total events: " << evt << '\t'
            << "nevt (have Rpcinfo): " << nevtExc << '\t'
            << "match: " << matchBit << '\t'
            << "mismatch: " << mismatchBit << '\n';
  
  std::cout << "both triggered: Data " << bothTriggerData <<  " Emu: " << bothTriggerEmul << std::endl;
  
  m_out->close();
  
  delete m_out;
  
  canvas[0]->cd();

  hh[0]->SetFillColor(kBlue-6);
  hh[0]->GetXaxis()->SetLabelColor(1);
  hh[0]->GetXaxis()->SetNdivisions(10);
  
  double norm = hh[0]->Integral();
  hh[0]->Scale( 1.0 / norm);
  hh[0]->SetStats(0);
  hh[0]->Draw();
  
  TLatex * tex = new TLatex(0.89,-941.0,"Ttu 1 = emu 1");
  tex->SetTextSize(0.02978723);
  tex->SetLineWidth(2);
  //tex->Draw();
  tex = new TLatex(2.55,-941.0,"Ttu = 1 emu = 0");
  tex->SetTextSize(0.02978723);
  tex->SetLineWidth(2);
  //tex->Draw();
  tex = new TLatex(4.69,-941.0,"Ttu = 0 emu = 1");
  tex->SetTextSize(0.02978723);
  tex->SetLineWidth(2);
  //tex->Draw();
  //tex = new TLatex(6.69,-941.0,"Ttu = 0 emu = 0");
  //tex->SetTextSize(0.02978723);
  //tex->SetLineWidth(2);
  //tex->Draw();

  canvas[0]->Modified();
  canvas[0]->cd();

  //

  TLegend * leg =  new TLegend(0.50, 0.55, 0.80, 0.70);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  
  canvas[10]->cd();
  
  hc[0]->SetBinContent( 1 , hh[0]->GetBinContent(1));
  hc[1]->SetBinContent( 2 , hh[0]->GetBinContent(3));
  hc[2]->SetBinContent( 3 , hh[0]->GetBinContent(5));
  
  std::vector<std::string> labels;
  labels.push_back( std::string("1. Data:Emulator Agrees") );
  labels.push_back( std::string("2. Emulator disagrees") );
  labels.push_back( std::string("3. Data disagrees") );
  

  for(int i= 0; i < 3; ++i) 
  {
    
    hc[i]->Scale(1.0 / norm);
    hc[i]->SetStats(0);
    hc[i]->SetFillColor( m_colors[i] );
    hc[i]->SetTitle("");
    hc[i]->SetNdivisions(8);
        
    leg->AddEntry(hc[i], labels[i].c_str(),"f");
    
    if ( i < 1 ) 
      hc[i]->Draw();
    else 
      hc[i]->Draw("same");
  }

  leg->Draw();

  tex = new TLatex(3.0,0.90,"CMS Preliminary 2009");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  std::string runId = std::string("CRAFT09: RunID: ") + m_runId;
    
  tex = new TLatex(3.0,0.84, runId.c_str());
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(3.0,0.78,"TTU (Pointing-to-Tracker Bit)");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

    
  std::cout << m_dataTime.size() << std::endl;

  int max = m_dataTime.size();
  int m_maxrate = 250;
  
  canvas[1]->cd();
  gg[0] = new TGraph( max, &m_dataTime[0], &m_dataRate[0] );
  gg[0]->SetMaximum(m_maxrate);
  gg[0]->SetMarkerStyle(25);
  gg[0]->SetFillColor(1);
  gg[0]->SetLineColor(kGray);
  gg[0]->GetXaxis()->SetTitle("Time [s]");
  gg[0]->GetYaxis()->SetTitle("Rate [Hz]");
  gg[0]->Draw("APL");
  
  canvas[1]->cd();
  gg[1] = new TGraph( max, &m_emuTime[0], &m_emuRate[0] );
  gg[1]->SetMaximum(m_maxrate);
  gg[1]->SetMarkerStyle(7);
  gg[1]->SetMarkerColor(2);
  gg[1]->SetFillColor(2);
  gg[1]->SetLineColor(kGray+2);
  gg[1]->GetXaxis()->SetTitle("Time [s]");
  gg[1]->GetYaxis()->SetTitle("Rate [Hz]");
  gg[1]->Draw("PL");
  canvas[1]->Update();
  
  //...
    
}

void CompareDataEmulator::discriminateDecision( int data, int emu ) 
{
  
  if ( data == 1 && emu == 1 )
  {
    hh[0]->Fill( 1 );
    hc[0]->Fill( 1 );
  }
  
  if ( data == 1 && emu == 0 ) 
  {
    hh[0]->Fill( 3 );
    hc[1]->Fill( 3 );
  }
  
  if ( data == 0 && emu == 1 ) 
  {
    hh[0]->Fill( 5 );
    hc[2]->Fill( 5 );
  }
  
  //if ( data == 0 && emu == 0 )
  //  hh[0]->Fill( 7 );
  
  
}

void CompareDataEmulator::LoopOverData( int bit )
{
  
  int evt(0);
  int nBn(0);
  
  float timeOffset(0.0);
  float lastRecordedTime(0.0);
  
  std::vector<float> m_dataRate;
  std::vector<float> m_dataTime;
  std::vector<float> m_time;
  std::vector<float> m_ievent;
  std::vector<float> m_ievt;
  std::vector<float> m_ndigis;
  
  std::vector<float> m_peak_time_occ;
  std::vector<float> m_peak_Dtime_occ;

  float prev_time(0.0);
  float curr_time(0.0);
  float prev_event(0.0);
  float curr_event(0.0);
  float wall_time(0.0);
  float ndigis(0.0);
  
  int timeRequest(0);
      
  if ( m_noinputfile ) return;
  
  int maxfiles = m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) {
    
    m_gzinData     = m_gzdataList[k];

    std::cout << m_gzinData << std::endl;

    float m_peak_prev_time(0.);
            
    while(1) {
      
      L1GtExtractedInfo * dataInfo = new L1GtExtractedInfo();
      
      if ( m_mode == 1 ) {
        
        (*m_sdinData) >> (*dataInfo);
        
        if( m_sdinData->eof() ) break;
        
      } else if ( m_mode == 2 ) {
        
        (*m_gzinData) >> (*dataInfo);
        
        if( m_gzinData->eof() ) break;
        
      } else {}
      
      if (m_debug) std::cout << (*dataInfo) ;
      
      ndigis = dataInfo->m_rpcNdigis;
      
      wall_time = dataInfo->m_time + timeOffset;
      
      m_time.push_back( wall_time );
      m_ndigis.push_back( ndigis );
      m_ievent.push_back( (float) dataInfo->m_ievent );
      m_ievt.push_back( (float) evt );
      
      curr_time = dataInfo->m_time ;
      hh[2]->Fill(abs( curr_time - prev_time) );
      prev_time = curr_time;
      
      curr_event = (float) dataInfo->m_ievent;
      hh[3]->Fill(abs( curr_event - prev_event) );
      prev_event = curr_event;
      
      h2d[0]->Fill( wall_time , abs( curr_event - prev_event)*1.0 );
      
      if ( m_debug ) std::cout << dataInfo->m_time << " " <<  dataInfo->m_ievent << std::endl;

      float m_peak_time(0.);
      float deltaPeakTime(0.);
      
      if( dataInfo->m_bunchNumber == -1 ) 
      {
        
        m_peak_time = dataInfo->m_time;
        
        deltaPeakTime = m_peak_time - m_peak_prev_time;
        
        m_peak_time_occ.push_back(m_peak_time);
        m_peak_Dtime_occ.push_back(deltaPeakTime);
        
        m_peak_prev_time = m_peak_time;
        
        if ( m_debug ) std::cout << "134: "
                                 << dataInfo->m_bitResult[0] << " "
                                 << dataInfo->m_time << " " 
                                 << dataInfo->m_time_bx << " "
                                 << dataInfo->m_ievent << std::endl;
        
        hh[5]->Fill( dataInfo->m_time , 1);
        hh[6]->Fill( deltaPeakTime );

        ++nBn;
        
      }
      
      //... get rates
      
      if ( dataInfo->m_outputRate == 1 ) {
        
        if ( timeRequest > m_timeSampling ) {
          m_dataRate.push_back( dataInfo->m_ntriggered[bit] * m_timeFactor);
          m_dataTime.push_back( wall_time );
          timeRequest = 0;
        } else timeRequest++;
        
        hh[1]->Fill( dataInfo->m_ntriggered[bit] * m_timeFactor );
        
      }
      
      lastRecordedTime = (float)  dataInfo->m_time;
      
      delete dataInfo;
      ++evt;

      //if ( nBn > 50 ) break;
      
    }
            
    timeOffset += lastRecordedTime;
    
    //if ( evt >= 1000 ) break;

  }
  
  
  
  std::cout << "total events: " << evt << '\n';
    
  std::cout << m_dataTime.size() << std::endl;
  
  int max = m_dataTime.size();
  
  int m_maxrate = 250;
  
  canvas[0]->cd();
  gg[0] = new TGraph( max, &m_dataTime[0], &m_dataRate[0] );
  gg[0]->SetMarkerStyle(25);
  gg[0]->SetFillColor(1);
  gg[0]->SetLineColor(kGray);
  gg[0]->GetXaxis()->SetTitle("Time [s]");
  gg[0]->GetYaxis()->SetTitle("Rate [Hz]");
  gg[0]->SetMinimum(0.0);
  gg[0]->SetMaximum(m_maxrate);
  gg[0]->Draw("APL");
      
  //...

  canvas[1]->cd();
  hh[1]->Draw();
  
  canvas[2]->cd();
  gg[1] = new TGraph( evt, &m_ievent[0], &m_time[0] );
  gg[1]->SetMarkerStyle(1);
  gg[1]->SetFillColor(1);
  gg[1]->GetXaxis()->SetTitle("event");
  gg[1]->GetYaxis()->SetTitle("Time");
  gg[1]->Draw("APL");
  
  canvas[3]->cd();
  hh[2]->Draw();
  
  canvas[4]->cd();
  hh[3]->Draw();
  
  canvas[5]->cd();
  gg[2] = new TGraph( evt, &m_ievt[0], &m_time[0] );
  gg[2]->SetMarkerStyle(1);
  gg[2]->SetFillColor(1);
  gg[2]->GetXaxis()->SetTitle("event");
  gg[2]->GetYaxis()->SetTitle("Time");
  gg[2]->Draw("APL");
  
  canvas[5]->cd();
  hh[5]->Draw();

  canvas[6]->cd();
  h2d[0]->Draw();
  
  canvas[7]->cd();
  hh[6]->Draw();
  
  int evt2 = m_peak_time_occ.size();
  
  canvas[8]->cd();
  gg[3] = new TGraph( evt2, &m_peak_time_occ[0], &m_peak_Dtime_occ[0] );
  gg[3]->SetMarkerStyle(1);
  gg[3]->SetFillColor(1);
  gg[3]->GetXaxis()->SetTitle("Time");
  gg[3]->GetYaxis()->SetTitle("Dt");
  gg[3]->Draw("APL");
  
  canvas[9]->cd();
  gg[4] = new TGraph( evt, &m_time[0] , &m_ndigis[0] );
  gg[4]->SetMarkerStyle(1);
  gg[4]->SetFillColor(1);
  gg[4]->GetXaxis()->SetTitle("Time");
  gg[4]->GetYaxis()->SetTitle("NDigis");
  gg[4]->Draw("APL");


}

