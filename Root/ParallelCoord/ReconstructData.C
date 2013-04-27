// $Id: $
// Include files 


// local
#include "ReconstructData.h"

//-----------------------------------------------------------------------------
// Implementation file for class : ReconstructData
//
// 2009-07-09 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
ReconstructData::ReconstructData( const char * fileList, int mode ) {
  
  m_mode = mode;
  m_ccounter = 0;
  m_debug = false;
    
  m_fileList = new std::ifstream( fileList , ifstream::in );
  
  if ( m_fileList->bad() ) m_noinputfile = true;
  else m_noinputfile = false;
  if ( m_noinputfile ) exit(1);
  
  int files(0);
  
  while (1) {
    
    std::string data1;
    
    if ( m_fileList->fail()) break;
    (*m_fileList) >> data1;
    if ( m_fileList->eof() ) break;

    m_fileNames.push_back(data1);
        
    //...open files 
    
    if ( mode == 2 ) {
      
      m_gzinData = new gz::igzstream( data1.c_str() );
      
      if ( m_gzinData->bad() ) m_noinputfile = true;
      else m_noinputfile = false;
      
      m_sdinData = NULL;
      
    } 
    
    if ( !m_noinputfile ) 
    {
      
      m_gzdataList.push_back( m_gzinData );
      
    } else continue;
    
    files+=1;
    
  }
  
  std::cout << "Total files to be analyzed: " << files << std::endl;
  
  int maxfiles =  m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) 
  {
    std::cout << "file1 " << k << " isready: " <<  m_gzdataList[k]->good() << '\n';
  }
  
  std::cout << "Total files: " << maxfiles << std::endl;

  std::string inFileName(fileList);
  
  string::size_type loc = inFileName.find( "/", 0 );
  
  if( loc != string::npos ) {
    cout << "Output file name" << loc << endl;
    string sub = inFileName.substr(0,loc);
    std::cout << sub << std::endl;
  } else {
    cout << "Using default file name" << endl;
  }
    
  m_gzoutData = new L1GtExtractedInfo("l1Gtinformation.txt.gz");
  
  m_useCompression = 1;
  m_writeMode = 1;
  m_precision = 10;
  
  if (m_useCompression <= 0) m_gzoutData->NoCompression();
  m_gzoutData->SetMode( m_writeMode );
  m_gzoutData->SetPrecision( m_precision );

  std::cout << "Outputfile ready " << std::endl;

  

  m_currentEvent = 0;
  m_previousEvent = 0;
    
}
//=============================================================================
// Destructor
//=============================================================================
ReconstructData::~ReconstructData() {
  
  int maxfiles = m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) 
  {
    m_gzinData     = m_gzdataList[k];
    
    if ( m_gzinData ) {
      m_gzinData->close();
      delete m_gzinData;
    }
    
  }
  
  m_gzdataList.clear();
  
  if ( m_fileList ) {
    m_fileList->close();
    delete m_fileList;
  }

  if (m_gzoutData)
    delete m_gzoutData;

  if (m_outmap)
    delete m_outmap;
  
  if (m_inmap)
    delete m_inmap;
  
    
} 

//=============================================================================
void ReconstructData::rewind( int idx )
{
  
  //... unfortunately gzstream does not implement seek()
  //... rewind = close file and reopen
  
  m_gzinData     = m_gzdataList[idx];
  
  if ( m_gzinData ) {
    m_gzinData->close();
    m_gzinData->clear();
  }
  
  m_gzinData     = m_gzdataList[idx];
  
  if ( m_gzinData ) {
    m_gzinData->open( m_fileNames[idx].c_str() );
  }
  
}

void ReconstructData::FirstLoop( )
{
  
  int evt(0);
  int firstevt(0);

  m_outmap = new std::ofstream("event.dataset.map.txt");

  //std::map<int,int>::iterator evtItr;
  
  if ( m_noinputfile ) return;
  
  int maxfiles = m_gzdataList.size();
  
  for( int k = 0; k < maxfiles; ++k) {
    
    m_gzinData     = m_gzdataList[k];
    
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
      
      //...get first event
      if ( evt == 0 ) 
        firstevt = dataInfo->m_ievent;
      
      //evtItr = find( m_eventsInFile.begin(), m_eventsInFile.end(), dataInfo->m_ievent);
      //if ( evtItr != m_eventsInFile.end() )
      //  std::cout << "event already present. possible duplicate" << std::endl;
            
      m_eventsInFile[ dataInfo->m_ievent ] = k;
      
      delete dataInfo;
      ++evt;
      
    }
    
    
  }
  
  int counter(0);
  
  for( m_evtItr = m_eventsInFile.begin(); m_evtItr != m_eventsInFile.end(); ++m_evtItr ) {
    
    //std::cout << "evt: " << (*m_evtItr).first << " in " << (*m_evtItr).second << std::endl;
    //if (counter > 5 ) break;

    counter++;
    
    (*m_outmap) <<  (*m_evtItr).first << '\t' << (*m_evtItr).second << std::endl;
    
  }
  
  std::cout << "total events: " << evt << '\n';
  
  m_outmap->close();
    
}

void ReconstructData::SecondLoop( )
{
  
  int k(0);
  unsigned int evt(0);
  int evtOut(0);
  bool evtFound(false);

  for( int k=0; k < 8; ++k)
    m_ntrigger.push_back( 0 );

  m_totalTime    = 0.0;
  m_elapsedTime  = 0.0;
  m_previousTime = 0.0;
  
  for( m_evtItr = m_eventsInFile.begin(); m_evtItr != m_eventsInFile.end(); ++m_evtItr ) {
    
    evt = (*m_evtItr).first;
    
    k = (*m_evtItr).second;
    
    //std::cout << "searching for event: " << evt << " " << k << std::endl;
    
    m_gzinData     = m_gzdataList[k];
    
    while(1) {
      
      evtFound = false;
      
      L1GtExtractedInfo * dataInfo = new L1GtExtractedInfo();
      
      if ( m_mode == 2 ) {
        
        (*m_gzinData) >> (*dataInfo);
        
        if( m_gzinData->eof() ) { 
          if ( !evtFound ) rewind(k);
          //break;
        }
        
      } else {}
      
      //......
      //std::cout << "event " << dataInfo->m_ievent << " " << evt <<  std::endl;
      
      if ( dataInfo->m_ievent == evt ) {
        
        m_currentEvent = dataInfo->m_ievent;
        
        (*m_gzoutData) = (*dataInfo);
        
        //...correct for ntriggered and time
        
        applyCorrection( );
        
        //...
        
        m_gzoutData->Write();
        m_gzoutData->reset();
        
        //std::cout << " data write" << std::endl;
        
        delete dataInfo;
        evtFound = true;
        ++evtOut;
        break;
        
      } else evtFound = false;
      
      delete dataInfo;
      
    }
    
    //if ( evtOut > 1000 ) break;
        
  }
  
  std::cout << "total events wrote to file: " << evtOut << '\n';
  
  m_gzoutData->Close();
    
}

void ReconstructData::applyCorrection( )
{
  
  int deltaEvent(0);
  double deltaTime(0.0);
    
  //...clear the current flag
  m_gzoutData->m_outputRate = 0;
  
  int maxbits = m_gzoutData->m_ntriggered.size();
  
  for(int k=0; k < maxbits; ++k)
    m_gzoutData->m_ntriggered[k] = 0;
  
  //...

  deltaEvent = m_currentEvent - m_previousEvent;

  m_currentTime = evaluateTime ( m_gzoutData->m_time_ns );
  
  deltaTime = fabs(m_currentTime - m_previousTime);
  
  if ( deltaTime > 1.0 ) deltaTime = 0;

  ///reset counters and times if difference between events is > 1 (we are loosing information and cannot read rate)

  //if ( deltaEvent > 1 ) {
  //  if ( m_debug ) std::cout << "deltaEvent: " << deltaEvent << std::endl;
  //  resetCounters();
  //} else evaluateCounters();

  evaluateCounters();
  
  if ( m_elapsedTime < 0 ) 
    deltaTime = m_currentTime - 0.0;
  
  m_totalTime   += deltaTime;
  m_elapsedTime += deltaTime;
  
  if ( m_elapsedTime > 1.0 ) { 
    
    m_gzoutData->m_outputRate = true;
    
    for( int k=0; k < m_gzoutData->m_maxttBits; ++k) {
      
      m_gzoutData->m_ntriggered[k] = m_ntrigger[k];
      m_ntrigger[k] = 0;
      
    }
    
    m_elapsedTime = 0;
    
  } else m_gzoutData->m_outputRate = false;
  
  m_previousTime = m_currentTime;

  m_previousEvent = m_currentEvent;
    
  m_gzoutData->m_time = m_totalTime;

}

long double ReconstructData::evaluateTime ( const unsigned long long & time_ns )
{
  
  int time_sec = ( time_ns ) / 1000000000;
  
  long double rmder = std::fmod( (long double) time_ns, (long double) 1000000000 );
  
  int rmder_ms = (int) std::floor (rmder / 1000000.0);
  
  long double fftime = (double) time_sec + (double) rmder_ms/1000.0;
  
  return fftime;
  
}

void ReconstructData::resetCounters()
{
  
  int maxbits = m_gzoutData->m_bitResult.size();
  
  for( int k=0; k < maxbits; ++k ) {
    
    if ( m_gzoutData->m_bitResult[k] > 0 )
      m_ntrigger[k] = 0;
    
  }
  
}

void ReconstructData::evaluateCounters()
{
  
  int maxbits = m_gzoutData->m_bitResult.size();
  
  for( int k=0; k < maxbits; ++k ) {
    
    if ( m_gzoutData->m_bitResult[k] > 0 )
      m_ntrigger[k]+=1;
    
  }
  
}

void ReconstructData::readMap( const char * inmap )
{
  
  m_inmap =  new std::ifstream( inmap , ifstream::in );

  m_eventsInFile.clear();
  
  int evt(0);
  
  while (1) {
    
    int event;
    int fileIndex;
    
    if ( m_inmap->fail()) break;
    (*m_inmap) >> event >> fileIndex;
    if ( m_inmap->eof() ) break;
    
    m_eventsInFile[ event ] = fileIndex;
    ++evt;
    
  }
  
  std::cout << "total events: " << evt << '\n';

  m_inmap->close();
  

}
