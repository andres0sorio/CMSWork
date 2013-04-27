// $Id: $
#ifndef PARALLELCOORD_RECONSTRUCTDATA_H 
#define PARALLELCOORD_RECONSTRUCTDATA_H 1

// Include files
#include "CommonIncludes.h"
#include <sstream>
#include "L1GtExtractedInfo.h"
#include <map>
#include <algorithm>

/** @class ReconstructData ReconstructData.h ParallelCoord/ReconstructData.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-07-09
 */
class ReconstructData {
public: 
  /// Standard constructor
  ReconstructData( ) {}; 

  ReconstructData( const char * , int ); 

  virtual ~ReconstructData( ); ///< Destructor
  
  void FirstLoop( );

  void SecondLoop();
  
  void readMap( const char *);
  
  void applyCorrection();
  
  void rewind( int );
  
  long double evaluateTime(  const unsigned long long & );

  void resetCounters();
  
  void evaluateCounters();

protected:
  
private:
  
  int m_mode;
  int m_ccounter;
  int m_useCompression;
  int m_writeMode;
  int m_precision;
  
  bool m_noinputfile;
  bool m_debug;

  std::ifstream * m_fileList;
  
  std::ifstream * m_sdinData;

  std::ifstream * m_inmap;
  
  std::ofstream * m_outmap;
  
  gz::igzstream * m_gzinData;
  
  L1GtExtractedInfo * m_gzoutData;
  
  std::vector<std::string> m_fileNames;
  
  std::vector<gz::igzstream *> m_gzdataList;
  
  std::ofstream * m_out;
  
  std::map<int,int> m_eventsInFile;
  
  std::map<int,int>::iterator m_evtItr;

  long double m_currentTime;
  long double m_previousTime;

  int m_currentEvent;
  int m_previousEvent;
  
  long double m_totalTime;
  long double m_elapsedTime;

  std::vector<int> m_ntrigger;
  
};
#endif // PARALLELCOORD_RECONSTRUCTDATA_H
