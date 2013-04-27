// $Id: $
#ifndef TTUHISTOGRAMS_H 
#define TTUHISTOGRAMS_H 1

// Include files
#include <string>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH2D.h"

/** @class TTUHistograms TTUHistograms.h
 *  
 *
 *  @author Andres Felipe Osorio Oliveros
 *  @date   2010-01-31
 */
class TTUHistograms {
public: 
  /// Standard constructor
  TTUHistograms( edm::Service<TFileService> & , const char * );

  virtual ~TTUHistograms( ); ///< Destructor

  ///Declare here all needed histograms
  TH1D * h_MuonType;
  TH2D * h_trkMuon_eta_phi;
  TH1D * h_trkMuon_calocomp;
  TH1D * h_trkMuon_eta;
  TH1D * h_trkMuon_pt;
  TH1D * h_trkMuon_dz;

  TH1D * h_trkMuon_eta_brl;
  TH1D * h_trkMuon_pt_brl;
  TH1D * h_trkMuon_dz_brl;
  
  TH2D * h_trkMuon_eta_phi_bit31;
  TH1D * h_trkMuon_eta_bit31;
  TH1D * h_trkMuon_pt_bit31;
  TH1D * h_trkMuon_dz_bit31;

  TH2D * h_trkMuon_eta_phi_only_bit31;
  TH1D * h_trkMuon_eta_only_bit31;
  TH1D * h_trkMuon_pt_only_bit31;
  TH1D * h_trkMuon_dz_only_bit31;

  TH1D * h_matches_region;
  TH1D * h_matches_detector;
  TH1D * h_matches_detector_not31;
  TH1D * h_trkMuon_NMatches;
  TH1D * h_matched_eta_brl;
  TH1D * h_matched_eta_brlfwd;
  TH1D * h_matched_eta_fwd;
  TH1D * h_Rb1st_Nhits_no_match;
  TH1D * h_Rb1st_Nhits_good_mu;
  TH2D * h_rpcHits_Bx_Rb1st;
  

  float * m_etaBins;
      
protected:

private:

  std::string m_option;


};
#endif // TTUHISTOGRAMS_H
