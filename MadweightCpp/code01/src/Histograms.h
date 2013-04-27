// $Id: $
#ifndef HISTOGRAMS_H 
#define HISTOGRAMS_H 1

// Include files

#include "RootCommon.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"

/** @class Histograms Histograms.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-09-21
 */
class Histograms {
public: 
  /// Standard constructor
  Histograms( ); 

  virtual ~Histograms( ); ///< Destructor

  std::map<std::string, TH1F*> h_1DHistContainer;

  std::map<std::string, TH2F*> h_2DHistContainer;

  std::map<std::string, TLegend*> h_legends;

  void BookBasicHistograms();
  
  void BookPermutationHistograms();
  
  //void Print();
  
protected:

private:

};
#endif // HISTOGRAMS_H
