// $Id: $
// Include files 



// local
#include "StudyL1Trigger/L1GtExtractInfo/interface/L1GtExtractedInfo.h"

//-----------------------------------------------------------------------------
// Implementation file for class : L1GtExtractedInfo
//
// 2009-06-09 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
L1GtExtractedInfo::L1GtExtractedInfo(  ) {

  m_outgz= false;
  m_precision = 10;
  m_mode = 1;
  m_outputRate = false;
  gzoutfile = NULL;

  m_maxttBits = 8;
  
  for( int k=0; k < m_maxttBits; ++k)
    m_ntriggered.push_back( 0 );
  
  
}

L1GtExtractedInfo::L1GtExtractedInfo( const char * filename ) {
  
  m_outgz= true;
  m_precision = 10;
  m_mode = 1;
  m_outputRate = false;
  
  gzoutfile = new gz::ogzstream( filename );  
  
  m_maxttBits = 8;
  
  for( int k=0; k < m_maxttBits; ++k)
    m_ntriggered.push_back( 0 );
  
}

//=============================================================================
// Destructor
//=============================================================================
L1GtExtractedInfo::~L1GtExtractedInfo() {
  
  if ( gzoutfile ) delete gzoutfile;
  
} 

//=============================================================================
void L1GtExtractedInfo::NoCompression( )
{
  
  m_outgz = false;

}

void L1GtExtractedInfo::SetMode( int mode )
{
 
  m_mode = mode;
  
}

void L1GtExtractedInfo::SetPrecision( int precision )
{
  
  m_precision = precision;
  
}

void L1GtExtractedInfo::reset()
{

  m_sector.clear();
  m_layer.clear();
  m_bxInEvent.clear();
  m_bitNumber.clear();
  m_bitResult.clear();
  
}


void L1GtExtractedInfo::Write()
{
  
  if ( m_outgz )
    ( *gzoutfile ) << (*this);
  else
    ( std::cout  ) << (*this);
  
}

void L1GtExtractedInfo::Close()
{
  
  if ( m_outgz )
    gzoutfile->close();
  
}

void L1GtExtractedInfo::setTechnicalTriggerBits( int bx, int bit, bool result )
{
  
  m_bxInEvent.push_back(bx);
  m_bitNumber.push_back(bit);
  m_bitResult.push_back(result);
  
}

void L1GtExtractedInfo::setRpcSectorLayer( int sec, int layer )
{
  
  m_sector.push_back(sec);
  m_layer.push_back(layer);
  
}

gz::igzstream& operator>>(gz::igzstream &istr, L1GtExtractedInfo &rhs) {
  
  istr.precision(rhs.m_precision);
  
  rhs.reset();
  
  istr >> rhs.m_ievent      ;
  istr >> rhs.m_iorbit      ;
  istr >> rhs.m_bunchNumber ;
  istr >> rhs.m_time_bx     ;
  istr >> rhs.m_time_ns     ;
  istr >> rhs.m_time        ;
  istr >> rhs.m_flag        ;
  istr >> rhs.m_outputRate  ;
  
  if ( rhs.m_outputRate ) {
    int maxttBits(0);
    int counter(0);
    
    istr >> rhs.m_ievent      ;
    istr >> maxttBits;
    
    for( int k=0; k < maxttBits; ++k) {
      istr >> counter;
      rhs.m_ntriggered[k] = counter;
    }
    
  }
  
  int maxbits = 0;
  int bx(0);
  int bit(0);
  bool result(false);
  
  istr >> maxbits;
  
  for( int k=0; k < maxbits; ++k ) {
    
    istr >> bx;
    istr >> bit;
    istr >> result;
    
    rhs.m_bxInEvent.push_back(bx) ;
    rhs.m_bitNumber.push_back(bit) ;
    rhs.m_bitResult.push_back(result);
    
  }
  
  int hasRpcInfo(0);
  int ndigis(0);
  int wheel(0);
  int sec(0);
  int lay(0);
  
  istr >> hasRpcInfo;
  
  rhs.m_hasRpcInfo = hasRpcInfo;
  
  if ( hasRpcInfo > 0 ) {
    
    istr >> bx >> ndigis >> wheel;
    
    rhs.m_bxInRpcEvent = bx;
    rhs.m_rpcNdigis = ndigis;
    rhs.m_wheel = wheel;
    
    for( int k=0; k < 5; ++k ) {
      
      istr >> sec >> lay;
      
      rhs.m_sector.push_back(sec);
      rhs.m_layer.push_back(lay);
      
    }
    
  }
  
  return istr;
  
}

gz::ogzstream& operator<<(gz::ogzstream &ostr, L1GtExtractedInfo &rhs) {
  
  ostr.precision(rhs.m_precision);
  
  ostr << rhs.m_ievent      << '\t';
  ostr << rhs.m_iorbit      << '\t';
  ostr << rhs.m_bunchNumber << '\t';
  ostr << rhs.m_time_bx     << '\t';
  ostr << rhs.m_time_ns     << '\t';
  ostr << rhs.m_time        << '\t';
  ostr << rhs.m_flag        << '\t';
  ostr << rhs.m_outputRate  << '\n';
  
  if ( rhs.m_outputRate ) {
    int maxttBits(0);
    maxttBits = rhs.m_maxttBits;

    ostr << rhs.m_ievent      << '\t';
    ostr << maxttBits         << '\t';
    
    for ( int k=0; k < maxttBits; ++k )
      ostr << rhs.m_ntriggered[k]  << '\t';
    
    ostr << '\n';
    
  }
  
  int maxbits = rhs.m_bitNumber.size();
  
  ostr << maxbits << '\n';
  
  for( int k=0; k < maxbits; ++k ) {
    ostr << rhs.m_bxInEvent[k] << '\t';
    ostr << rhs.m_bitNumber[k] << '\t';
    ostr << rhs.m_bitResult[k] << '\t';
  }
  
  ostr << '\n';

  ostr << rhs.m_hasRpcInfo << '\n';
  
  if ( rhs.m_hasRpcInfo ) {
    
    ostr << rhs.m_bxInRpcEvent << '\t'
         << rhs.m_rpcNdigis << '\t'
         << rhs.m_wheel << '\n';
    
    for( int k=0; k < 5; ++k) {
      ostr << rhs.m_sector[k] << '\t'
           << rhs.m_layer[k] << '\n';
    }
    
  }
  
  return ostr;
  
}

std::istream& operator>>(std::istream &istr, L1GtExtractedInfo &rhs) {
  
  istr.precision(rhs.m_precision);
  
  rhs.reset();

  istr >> rhs.m_ievent      ;
  istr >> rhs.m_iorbit      ;
  istr >> rhs.m_bunchNumber ;
  istr >> rhs.m_time_bx     ;
  istr >> rhs.m_time_ns     ;
  istr >> rhs.m_time        ;
  istr >> rhs.m_flag        ;
  istr >> rhs.m_outputRate  ;
  
  if ( rhs.m_outputRate ) {
    int maxttBits(0);
    int counter(0);
    
    istr >> rhs.m_ievent      ;
    istr >> maxttBits;
    
    for( int k=0; k < maxttBits; ++k) {
      istr >> counter;
      rhs.m_ntriggered[k] = counter;
    }

  }
  
  int maxbits = 0;
  int bx(0);
  int bit(0);
  bool result(false);
  
  istr >> maxbits;
  
  for( int k=0; k < maxbits; ++k ) {
    
    istr >> bx;
    istr >> bit;
    istr >> result;
    
    rhs.m_bxInEvent.push_back(bx) ;
    rhs.m_bitNumber.push_back(bit) ;
    rhs.m_bitResult.push_back(result);
    
  }
  
  int hasRpcInfo(0);
  int ndigis(0);
  int wheel(0);
  int sec(0);
  int lay(0);
  
  istr >> hasRpcInfo;
  
  rhs.m_hasRpcInfo = hasRpcInfo;
  
  if ( hasRpcInfo > 0 ) {
    
    istr >> bx >> ndigis >> wheel;
    
    rhs.m_bxInRpcEvent = bx;
    rhs.m_rpcNdigis = ndigis;
    rhs.m_wheel = wheel;
    
    for( int k=0; k < 5; ++k ) {
      
      istr >> sec >> lay;
    
      rhs.m_sector.push_back(sec);
      rhs.m_layer.push_back(lay);
      
    }
    
  }
  
  return istr;
  
}

std::ostream& operator<<(std::ostream &ostr, L1GtExtractedInfo &rhs) {
  
  ostr << " writting to std::cout" << std::endl;
  
  ostr.precision(rhs.m_precision);
  
  ostr << rhs.m_ievent      << '\t';
  ostr << rhs.m_iorbit      << '\t';
  ostr << rhs.m_bunchNumber << '\t';
  ostr << rhs.m_time_bx     << '\t';
  ostr << rhs.m_time_ns     << '\t';
  ostr << rhs.m_time        << '\t';
  ostr << rhs.m_flag        << '\t';
  ostr << rhs.m_outputRate  << '\n';
  
  if ( rhs.m_outputRate ) {
    int maxttBits(0);
    maxttBits = rhs.m_maxttBits;
    
    ostr << rhs.m_ievent      << '\t';
    ostr << maxttBits         << '\t';
    
    for ( int k=0; k < maxttBits; ++k )
      ostr << rhs.m_ntriggered[k]  << '\t';
    
    ostr << '\n';
    
  }
  
  int maxbits = rhs.m_bitNumber.size();
  
  ostr << maxbits << '\n';
  
  for( int k=0; k < maxbits; ++k ) {
    ostr << rhs.m_bxInEvent[k] << '\t';
    ostr << rhs.m_bitNumber[k] << '\t';
    ostr << rhs.m_bitResult[k] << '\t';
  }
  
  ostr << '\n';

  ostr << rhs.m_hasRpcInfo << '\n';
  
  if ( rhs.m_hasRpcInfo ) {
    
    ostr << rhs.m_bxInRpcEvent << '\t'
         << rhs.m_rpcNdigis << '\t'
         << rhs.m_wheel << '\n';
    
    for( int k=0; k < 5; ++k) {
      ostr << rhs.m_sector[k] << '\t'
           << rhs.m_layer[k] << '\n';
    }
    
  }
  
  return ostr;
  
}

//....


std::ifstream& operator>>(std::ifstream &istr, L1GtExtractedInfo &rhs) {
  
  istr.precision(rhs.m_precision);

  rhs.reset();
  
  istr >> rhs.m_ievent      ;
  istr >> rhs.m_iorbit      ;
  istr >> rhs.m_bunchNumber ;
  istr >> rhs.m_time_bx     ;
  istr >> rhs.m_time_ns     ;
  istr >> rhs.m_time        ;
  istr >> rhs.m_flag        ;
  istr >> rhs.m_outputRate  ;
  
  if ( rhs.m_outputRate ) {
    int maxttBits(0);
    int counter(0);
    
    istr >> rhs.m_ievent      ;
    istr >> maxttBits;
    
    for( int k=0; k < maxttBits; ++k) {
      istr >> counter;
      rhs.m_ntriggered[k] = counter;
    }
    
  }
  
  int maxbits = 0;
  int bx(0);
  int bit(0);
  bool result(false);
  
  istr >> maxbits;
  
  for( int k=0; k < maxbits; ++k ) {
    
    istr >> bx;
    istr >> bit;
    istr >> result;
    
    rhs.m_bxInEvent.push_back(bx) ;
    rhs.m_bitNumber.push_back(bit) ;
    rhs.m_bitResult.push_back(result);
    
  }
  
  int hasRpcInfo(0);
  int ndigis(0);
  int wheel(0);
  int sec(0);
  int lay(0);
  
  istr >> hasRpcInfo;
  
  rhs.m_hasRpcInfo = hasRpcInfo;
  
  if ( hasRpcInfo > 0 ) {
    
    istr >> bx >> ndigis >> wheel;
    
    rhs.m_bxInRpcEvent = bx;
    rhs.m_rpcNdigis = ndigis;
    rhs.m_wheel = wheel;
    
    for( int k=0; k < 5; ++k ) {
      
      istr >> sec >> lay;
      
      rhs.m_sector.push_back(sec);
      rhs.m_layer.push_back(lay);
      
    }
    
  }
  
  return istr;
  
}

std::ofstream& operator<<(std::ofstream &ostr, L1GtExtractedInfo &rhs) {

  ostr.precision(rhs.m_precision);
  
  ostr << rhs.m_ievent      << '\t';
  ostr << rhs.m_iorbit      << '\t';
  ostr << rhs.m_bunchNumber << '\t';
  ostr << rhs.m_time_bx     << '\t';
  ostr << rhs.m_time_ns     << '\t';
  ostr << rhs.m_time        << '\t';
  ostr << rhs.m_flag        << '\t';
  ostr << rhs.m_outputRate  << '\n';
  
  if ( rhs.m_outputRate ) {
    int maxttBits(0);
    maxttBits = rhs.m_maxttBits;
    
    ostr << rhs.m_ievent      << '\t';
    ostr << maxttBits         << '\t';
        
    for ( int k=0; k < maxttBits; ++k )
      ostr << rhs.m_ntriggered[k]  << '\t';
    
    ostr << '\n';
    
  }
  
  int maxbits = rhs.m_bitNumber.size();
  
  ostr << maxbits << '\n';
  
  for( int k=0; k < maxbits; ++k ) {
    ostr << rhs.m_bxInEvent[k] << '\t';
    ostr << rhs.m_bitNumber[k] << '\t';
    ostr << rhs.m_bitResult[k] << '\t';
  }
  
  ostr << '\n';

  ostr << rhs.m_hasRpcInfo << '\n';
  
  if ( rhs.m_hasRpcInfo ) {
    
    ostr << rhs.m_bxInRpcEvent << '\t'
         << rhs.m_rpcNdigis << '\t'
         << rhs.m_wheel << '\n';
    
    for( int k=0; k < 5; ++k) {
      ostr << rhs.m_sector[k] << '\t'
           << rhs.m_layer[k] << '\n';
    }
    
  }
  
  return ostr;
  
}
