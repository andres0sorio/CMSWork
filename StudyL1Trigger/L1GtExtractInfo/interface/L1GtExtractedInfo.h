// $Id: $
#ifndef L1GTEXTRACTEDINFO_H 
#define L1GTEXTRACTEDINFO_H 1

// Include files
#include <iostream>
#include <vector>
#include <StudyL1Trigger/L1GtExtractInfo/interface/gzstream.h>

/** @class L1GtExtractedInfo L1GtExtractedInfo.h
 *
 * This is the information I like to save for analysis
 *  of the L1 Gt Technical Trigger
 *
 *
 *  @author Andres Osorio
 *  @date   2009-06-09
 */
class L1GtExtractedInfo {
public: 
  /// Standard constructor
  L1GtExtractedInfo( ); 
  
  L1GtExtractedInfo( const char *); 
  
  virtual ~L1GtExtractedInfo( ); ///< Destructor
  
  void NoCompression();

  void SetMode( int );
  
  void Write( );
  
  void Close();
  
  void SetPrecision( int );

  void reset();
    
  void setTechnicalTriggerBits( int, int, bool );
  
  void setRpcSectorLayer( int, int );
  
  //...Trigger information
  unsigned int  m_ievent;
  unsigned int  m_iorbit;
  unsigned long long m_time_bx;
  unsigned long long m_time_ns;
  int m_bunchNumber;
  double m_time;
  
  int m_maxttBits;
  std::vector<unsigned int> m_ntriggered;
  
  int m_flag;
  bool m_outputRate;
  
  //...RPC digis information
  bool m_hasRpcInfo;
  int m_bxInRpcEvent;
  int m_rpcNdigis;
  
  int m_wheel;
  std::vector<int> m_sector;
  std::vector<int> m_layer;
  
  std::vector<int> m_bxInEvent;
  std::vector<int> m_bitNumber;
  std::vector<int> m_bitResult;


  L1GtExtractedInfo & operator=( const  L1GtExtractedInfo & rhs )
  {
    
    if (this == &rhs) return (*this);
    
    m_ievent       = rhs.m_ievent;
    m_iorbit       = rhs.m_iorbit;
    m_time_bx      = rhs.m_time_bx;
    m_time_ns      = rhs.m_time_ns;
    m_bunchNumber  = rhs.m_bunchNumber;
    m_time         = rhs.m_time;
    
    m_maxttBits    = rhs.m_maxttBits;
    m_hasRpcInfo   = rhs.m_hasRpcInfo;
    m_bxInRpcEvent = rhs.m_bxInRpcEvent;
    m_rpcNdigis    = rhs.m_rpcNdigis;
    
    m_flag         = rhs.m_flag;
    m_outputRate   = rhs.m_outputRate;
    
    m_wheel        = rhs.m_wheel;
    
    int maxbits = rhs.m_ntriggered.size();
        
    for( int k=0; k < maxbits; ++k )
      m_ntriggered[k] = rhs.m_ntriggered[k]; //this one is initialized at construction 
    
    maxbits = rhs.m_bxInEvent.size();
    
    for( int k=0; k < maxbits; ++k ) {
      m_bxInEvent.push_back( rhs.m_bxInEvent[k] );
      m_bitNumber.push_back( rhs.m_bitNumber[k] );
      m_bitResult.push_back( rhs.m_bitResult[k] );
    }
    
    maxbits =  rhs.m_sector.size();
    
    for( int k=0; k < maxbits; ++k ) {
      m_sector.push_back( rhs.m_sector[k] );
      m_layer.push_back( rhs.m_layer[k] );
    }
    
    return (*this);
        
  };

  friend std::istream& operator>>(std::istream &istr,   L1GtExtractedInfo &rhs);
  friend std::ostream& operator<<(std::ostream &ostr,   L1GtExtractedInfo &rhs);
  
  friend std::ifstream& operator>>(std::ifstream &istr, L1GtExtractedInfo &rhs);
  friend std::ofstream& operator<<(std::ofstream &ostr, L1GtExtractedInfo &rhs);
  
  friend gz::igzstream& operator>>(gz::igzstream &istr, L1GtExtractedInfo &rhs);
  friend gz::ogzstream& operator<<(gz::ogzstream &ostr, L1GtExtractedInfo &rhs);
  
protected:
  
private:
  
  bool m_outgz;
  int m_mode;
  int m_precision;

  std::ofstream * sdoutfile;
  
  gz::ogzstream * gzoutfile;
  
  
};
#endif // L1GTEXTRACTEDINFO_H
