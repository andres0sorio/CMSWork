// $Id: $
#ifndef HISTOGRAMS_H 
#define HISTOGRAMS_H 1

// Include files
#include "RootCommon.h"

#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TFile.h>

/** @class Histograms Histograms.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-09-21
 */
class Histograms {
public: 
  /// Standard constructor
  Histograms( ) {}; 
  Histograms( const char * );

  virtual ~Histograms( ); ///< Destructor

  void SetOptions();
  
  std::map<std::string,TH1F*> h_1DHistograms;
  std::map<std::string,TH2F*> h_2DHistograms;
  std::map<std::string,TProfile*> h_ProfileHistograms;
  
protected:

private:
  
  TFile * m_output;
  
  
};
#endif // HISTOGRAMS_H
