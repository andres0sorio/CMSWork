// $Id: $
#ifndef COMPARADATAEMULATOR_H 
#define COMPARADATAEMULATOR_H 1

// Include files
#include "CommonIncludes.h"
#include <sstream>
#include "L1GtExtractedInfo.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TGraph.h"
#include "TLegend.h"

/** @class CompareDataEmulator CompareDataEmulator.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-06-30
 */

class CompareDataEmulator {
public: 
  /// Standard constructor
  CompareDataEmulator( ) {}; 

  CompareDataEmulator(const char * , int );
  
  CompareDataEmulator(const char * , const char * , int );
  
  virtual ~CompareDataEmulator( ); ///< Destructor

  void Loop( int );
  
  void LoopOverData( int );
  
  void discriminateDecision(int,int);

  void prepareHistograms();
    
  int addCanvas();

  void setFactor( float ff)
  {
    m_timeFactor = ff;
  }

  void setRunId( const char * run)
  {
    m_runId = std::string(run);
  }
    
  TH1D    * hh[20];
  TH1D    * hc[20];
  TH2D    * h2d[20];
  TGraph  * gg[20];
  TCanvas * canvas[20];
  TNtuple * m_data;
  
protected:
  
private:

  int m_mode;
  int m_ccounter;
  bool m_noinputfile;
  bool m_debug;
  float m_timeFactor;
  float m_timeSampling;
  int m_colors[10];
  
  std::string m_runId;
  
  std::ifstream * m_fileList;
  std::ifstream * m_sdinData;
  std::ifstream * m_sdinEmulator;
  
  gz::igzstream * m_gzinData;
  gz::igzstream * m_gzinEmulator;

  std::vector<gz::igzstream *> m_gzdataList;
  std::vector<gz::igzstream *> m_gzemulList;

  std::ofstream * m_out;

  void rewind();
    
};
#endif // COMPARADATAEMULATOR_H
