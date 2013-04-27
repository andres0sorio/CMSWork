// $Id: $
#ifndef TEST_ANALYZELTCDATA_H 
#define TEST_ANALYZELTCDATA_H 1

// Include files
#include "CommonIncludes.h"
#include <sstream>
#include "StudyL1Trigger/L1GtExtractInfo/interface/L1GtExtractedInfo.h"

#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"

/** @class AnalyzeLtcData AnalyzeLtcData.h test/AnalyzeLtcData.h
 *  
 *
 *  @author Andres Felipe Osorio Oliveros
 *  @date   2009-06-26
 */

class AnalyzeLtcData {
public: 
  /// Standard constructor
  AnalyzeLtcData( ){}; 
  
  AnalyzeLtcData(const char *, int ); 
  
  virtual ~AnalyzeLtcData( ); ///< Destructor
  
  void Loop();

  int addCanvas();
  
  TH1D * hh[10];
  TCanvas * canvas[10];
  
protected:
  
private:
  
  int m_mode;
  
  int m_ccounter;
  
  bool m_noinputfile;
  
  std::ifstream * m_sdin;
  
  gz::igzstream * m_gzin;
  
};
#endif // TEST_ANALYZELTCDATA_H
