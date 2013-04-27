// $Id: $
#ifndef PARALLELCOORD_DISPLAYPARALLELCOORD_H 
#define PARALLELCOORD_DISPLAYPARALLELCOORD_H 1

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

/** @class DisplayParallelCoord DisplayParallelCoord.h ParallelCoord/DisplayParallelCoord.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-06-27
 */
class DisplayParallelCoord {
public: 
  /// Standard constructor
  DisplayParallelCoord( ) {;}; 

  DisplayParallelCoord(const char * , int ); 

  virtual ~DisplayParallelCoord( ); ///< Destructor

  void Loop();

  int addCanvas();
  
  void prepareHistograms();
  
  TH1D    * hh[10];
  TH2D    * h2h[10];
  TGraph  * gg[10];
  TCanvas * canvas[10];
  TNtuple * m_data;
  
protected:
  
private:
  
  int m_mode;
  int m_ccounter;
  bool m_noinputfile;
  bool m_debug;
    
  std::ifstream * m_sdin;
  gz::igzstream * m_gzin;
  
  std::ifstream * m_fileList;

  std::vector<gz::igzstream *> m_gzdataList;
  std::vector<gz::igzstream *> m_gzemulList;
  

};
#endif // PARALLELCOORD_DISPLAYPARALLELCOORD_H
