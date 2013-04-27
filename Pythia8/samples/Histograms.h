// $Id: $
#ifndef ALL_HISTOGRAMS_H 
#define ALL_HISTOGRAMS_H 1

// Include files
#include <TH1F.h>
#include <TFile.h>

/** @class Histograms Histograms.h all/Histograms.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-01-31
 */
class Histograms {
public: 
  /// Standard constructor
  Histograms( ){ }; 
  
  Histograms(const char * );
  
  virtual ~Histograms( ); ///< Destructor

  void SetHistogramOptions();
  
  //Declarar todos los histogramas
  TFile * outfile;

  TH1F * h_partMultip;
  TH1F * h_stats;
  TH1F * h_istate_eta;
  TH1F * h_istate_pt;
  TH1F * h_fstate_eta;
  TH1F * h_fstate_pt;
  TH1F * h_lsp_eta;
  TH1F * h_lsp_pt;
  
protected:

private:

};
#endif // ALL_HISTOGRAMS_H
