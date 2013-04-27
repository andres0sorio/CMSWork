// $Id: $
// Include files 



// local
#include "TTUHistograms.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TTUHistograms
//
// 2010-01-31 : Andres Felipe Osorio Oliveros
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TTUHistograms::TTUHistograms( edm::Service<TFileService> & FileService, const char * Name) {

  m_option = std::string(Name);
  
  //... FileService (for the moment, same as in L1GtTtuAnalyzer
  
  TFileDirectory muoncand    = FileService->mkdir( "MuonCandidates" );
  
  h_MuonType           = muoncand.make<TH1D>("MuonType","Muon Type", 7, 0.0, 7.0);
  h_trkMuon_calocomp   = muoncand.make<TH1D>("TRKCaloComp","Calo compatability", 50, 0.0, 1.0);

  m_etaBins = new float[17];
  m_etaBins[0]  = -2.5;
  m_etaBins[1]  = -2.3;
  m_etaBins[2]  = -2.1;
  m_etaBins[3]  = -1.9;
  m_etaBins[4]  = -1.6;
  m_etaBins[5]  = -1.3;
  m_etaBins[6]  = -1.0;
  m_etaBins[7]  = -0.5;
  m_etaBins[8]  =  0.0;
  m_etaBins[9]  =  0.5;
  m_etaBins[10] =  1.0;
  m_etaBins[11] =  1.3;
  m_etaBins[12] =  1.6;
  m_etaBins[13] =  1.9;
  m_etaBins[14] =  2.1;
  m_etaBins[15] =  2.3;
  m_etaBins[16] =  2.5;
  
  //...........................................................................

  std::ostringstream hname;
  hname << "Trk.Muons.Eta.Phi.Bit.All";
  
  h_trkMuon_eta_phi = muoncand.make<TH2D>(hname.str().c_str(),"Tracker muons eta/phi", 50, -5.0, 5.0, 50, -4.0, 4.0 );
  h_trkMuon_eta_phi->Sumw2();
  
  hname.str("");
  hname << "Trk.Muons.Eta.Phi.Bit." << 31;
  h_trkMuon_eta_phi_bit31 = muoncand.make<TH2D>(hname.str().c_str(),"Selected muon eta/phi: selected", 
                                                50, -5.0, 5.0, 50, -4.0, 4.0 );
  h_trkMuon_eta_phi_bit31->Sumw2();
  
  hname.str("");
  hname << "Trk.Muons.Eta.Phi.Only.Bit." << 31;
  h_trkMuon_eta_phi_only_bit31 = muoncand.make<TH2D>(hname.str().c_str(),"Selected muon eta/phi bit: only bit31", 
                                                     50, -5.0, 5.0, 50, -4.0, 4.0 );
  h_trkMuon_eta_phi_only_bit31->Sumw2();
  
  //...........................................................................
  
  hname.str("");
  hname << "Trk.Muons.Eta.Bit.All";
  
  h_trkMuon_eta = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta", 60, -5.0, 5.0);
  h_trkMuon_eta->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Eta.Bit.31";
  h_trkMuon_eta_bit31 = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta", 16, m_etaBins );
  h_trkMuon_eta_bit31->Sumw2();
  
  hname.str("");
  hname << "Trk.Muons.Pt.Bit.All";
  
  h_trkMuon_pt = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 60, 0.0, 10.0);
  h_trkMuon_pt->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Pt.Bit.31";
  
  h_trkMuon_pt_bit31 = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 60, 0.0, 10.0);
  h_trkMuon_pt_bit31->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Dz.Bit.All";
  
  h_trkMuon_dz = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 60, -5.0, 5.0);
  h_trkMuon_dz->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Dz.Bit.31";
  
  h_trkMuon_dz_bit31 = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 60, -5.0, 5.0);
  h_trkMuon_dz_bit31->Sumw2();
  
  //...........................................................................

  hname.str("");
  hname << "Trk.Muons.Eta.Only.Bit.31";
  
  h_trkMuon_eta_only_bit31 = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 16, m_etaBins );
  h_trkMuon_eta_only_bit31->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Pt.Only.Bit.31";
  
  h_trkMuon_pt_only_bit31 = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 60, 0.0, 10.0);
  h_trkMuon_pt_only_bit31->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Dz.Only.Bit.31";
  
  h_trkMuon_dz_only_bit31 = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 60, -5.0, 5.0);
  h_trkMuon_dz_only_bit31->Sumw2();

  //...........................................................................
  
  hname.str("");
  hname << "Trk.Muons.Eta.Barrel";
  
  h_trkMuon_eta_brl = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 16, m_etaBins );
  h_trkMuon_eta_brl->Sumw2();
  
  hname.str("");
  hname << "Trk.Muons.Eta.Matched.Barrel";
  
  h_matched_eta_brl = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 16, m_etaBins );
  h_matched_eta_brl->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Eta..Matched.BrlFwd";
  
  h_matched_eta_brlfwd = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 16, m_etaBins );
  h_matched_eta_brlfwd->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Eta..Matched.Fwd";
  
  h_matched_eta_fwd = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 16, m_etaBins );
  h_matched_eta_fwd->Sumw2();
  
  hname.str("");
  hname << "Trk.Muons.Pt.Barrel";
  
  h_trkMuon_pt_brl = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 60, 0.0, 10.0);
  h_trkMuon_pt_brl->Sumw2();

  hname.str("");
  hname << "Trk.Muons.Dz.Barrel";
  
  h_trkMuon_dz_brl = muoncand.make<TH1D>(hname.str().c_str(),"Tracker muons eta/phi bit", 60, -5.0, 5.0);
  h_trkMuon_dz_brl->Sumw2();

  hname.str("");
  hname << "RB1st.N.RPChits.No.Match";
  
  h_Rb1st_Nhits_no_match = muoncand.make<TH1D>(hname.str().c_str(),"RB1st NRPChits No Match", 5, 0.0, 5.0);
  h_Rb1st_Nhits_no_match->Sumw2();

   //...........................................................................
  
  hname.str("");
  hname << "Matches.Detector";
  h_matches_detector = muoncand.make<TH1D>(hname.str().c_str(),"Matched detector", 5, 0.0, 5.0);

  hname.str("");
  hname << "Matches.Region";
  h_matches_region = muoncand.make<TH1D>(hname.str().c_str(),"Matched detector regions 1:B 2:B+E 3:E", 6, 0.0, 6.0);

  hname.str("");
  hname << "NMatches.In.Muon.Trk";
  h_trkMuon_NMatches = muoncand.make<TH1D>(hname.str().c_str(),"N. Matched detector", 10, 0.0, 10.0);
  
  hname.str("");
  hname << "Matches.Detector.NoBit31";
  h_matches_detector_not31 = muoncand.make<TH1D>(hname.str().c_str(),"Matched detector", 5, 0.0, 5.0);

  //...........................................................................
  hname.str("");
  hname << "RpcHits.Rbc1.Timing";
  h_rpcHits_Bx_Rb1st = muoncand.make<TH2D>(hname.str().c_str(),"Bx distributions of hits in Rb1st", 5, -2.5, 2.5, 5, -2.5, 2.5);

  hname.str("");
  hname << "RpcHits.Rb1st_Nhits_GoodMu";
  h_Rb1st_Nhits_good_mu = muoncand.make<TH1D>(hname.str().c_str(),"RB1st NRPChits No Match", 5, 0.0 , 5.0);
  h_Rb1st_Nhits_good_mu->Sumw2();

}
//=============================================================================
// Destructor
//=============================================================================
TTUHistograms::~TTUHistograms() {} 

//=============================================================================
