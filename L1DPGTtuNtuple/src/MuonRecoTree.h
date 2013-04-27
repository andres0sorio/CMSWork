//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb  1 22:44:17 2010 by ROOT version 5.22/00
// from TTree MuonRecoTree/MuonRecoTree
// found on file: L1DPG-All.root
//////////////////////////////////////////////////////////

#ifndef MuonRecoTree_h
#define MuonRecoTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class MuonRecoTree {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Int_t           Nmuons;

  Double_t        BeamSpotX;
  Double_t        BeamSpotY;

  Int_t           Muon_type[20];   //[Nmuons]
  Double_t        Muons_ch[20];   //[Nmuons]
  Double_t        Muons_pt[20];   //[Nmuons]
  Double_t        Muons_p[20];   //[Nmuons]
  Double_t        Muons_eta[20];   //[Nmuons]
  Double_t        Muons_phi[20];   //[Nmuons]
  Double_t        Muons_validhist[20];   //[Nmuons]
  Double_t        Muons_normchi2[20];   //[Nmuons]
  Double_t        Muons_imp_point_x[20];   //[Nmuons]
  Double_t        Muons_imp_point_y[20];   //[Nmuons]
  Double_t        Muons_imp_point_z[20];   //[Nmuons]
  Double_t        Muons_imp_point_p[20];   //[Nmuons]
  Double_t        Muons_imp_point_pt[20];   //[Nmuons]
  Double_t        Muons_phi_hb[20];   //[Nmuons]
  Double_t        Muons_z_hb[20];   //[Nmuons]
  Double_t        Muons_phi_he_n[20];   //[Nmuons]
  Double_t        Muons_phi_he_p[20];   //[Nmuons]
  Double_t        Muons_r_he_n[20];   //[Nmuons]
  Double_t        Muons_r_he_p[20];   //[Nmuons]
  Double_t        Muons_calocomp[20];   //[Nmuons]
  Double_t        Muons_d0[20];   //[Nmuons]
  Double_t        Muons_d0s[20];   //[Nmuons]
  Double_t        Muons_tr_ch[20];   //[Nmuons]
  Double_t        Muons_tr_pt[20];   //[Nmuons]
  Double_t        Muons_tr_p[20];   //[Nmuons]
  Double_t        Muons_tr_eta[20];   //[Nmuons]
  Double_t        Muons_tr_phi[20];   //[Nmuons]
  Double_t        Muons_tr_validhist[20];   //[Nmuons]
  Double_t        Muons_tr_normchi2[20];   //[Nmuons]
  Double_t        Muons_tr_imp_point_x[20];   //[Nmuons]
  Double_t        Muons_tr_imp_point_y[20];   //[Nmuons]
  Double_t        Muons_tr_imp_point_z[20];   //[Nmuons]
  Double_t        Muons_tr_imp_point_p[20];   //[Nmuons]
  Double_t        Muons_tr_imp_point_pt[20];   //[Nmuons]
  Double_t        Muons_tr_calocomp[20];   //[Nmuons]
  Double_t        Muons_tr_d0[20];   //[Nmuons]
  Double_t        Muons_tr_d0s[20];   //[Nmuons]
  Double_t        Muons_sa_phi_mb2[20];   //[Nmuons]
  Double_t        Muons_sa_z_mb2[20];   //[Nmuons]
  Double_t        Muons_sa_pseta[20];   //[Nmuons]
  Double_t        Muons_sa_normchi2[20];   //[Nmuons]
  Double_t        Muons_sa_validhits[20];   //[Nmuons]
  Double_t        Muons_sa_ch[20];   //[Nmuons]
  Double_t        Muons_sa_pt[20];   //[Nmuons]
  Double_t        Muons_sa_p[20];   //[Nmuons]
  Double_t        Muons_sa_eta[20];   //[Nmuons]
  Double_t        Muons_sa_phi[20];   //[Nmuons]
  Double_t        Muons_sa_outer_pt[20];   //[Nmuons]
  Double_t        Muons_sa_inner_pt[20];   //[Nmuons]
  Double_t        Muons_sa_outer_eta[20];   //[Nmuons]
  Double_t        Muons_sa_inner_eta[20];   //[Nmuons]
  Double_t        Muons_sa_outer_phi[20];   //[Nmuons]
  Double_t        Muons_sa_inner_phi[20];   //[Nmuons]
  Double_t        Muons_sa_outer_x[20];   //[Nmuons]
  Double_t        Muons_sa_outer_y[20];   //[Nmuons]
  Double_t        Muons_sa_outer_z[20];   //[Nmuons]
  Double_t        Muons_sa_inner_x[20];   //[Nmuons]
  Double_t        Muons_sa_inner_y[20];   //[Nmuons]
  Double_t        Muons_sa_inner_z[20];   //[Nmuons]
  Double_t        Muons_sa_imp_point_x[20];   //[Nmuons]
  Double_t        Muons_sa_imp_point_y[20];   //[Nmuons]
  Double_t        Muons_sa_imp_point_z[20];   //[Nmuons]
  Double_t        Muons_sa_imp_point_p[20];   //[Nmuons]
  Double_t        Muons_sa_imp_point_pt[20];   //[Nmuons]
  Double_t        Muons_sa_phi_hb[20];   //[Nmuons]
  Double_t        Muons_sa_z_hb[20];   //[Nmuons]
  Double_t        Muons_sa_phi_he_n[20];   //[Nmuons]
  Double_t        Muons_sa_phi_he_p[20];   //[Nmuons]
  Double_t        Muons_sa_r_he_n[20];   //[Nmuons]
  Double_t        Muons_sa_r_he_p[20];   //[Nmuons]
  
  // List of branches
  TBranch        *b_Nmuons;   //!
  TBranch        *b_BeamSpotX;   //!
  TBranch        *b_BeamSpotY;   //!
  TBranch        *b_Muon_type;   //!
  TBranch        *b_Muons_ch;   //!
  TBranch        *b_Muons_pt;   //!
  TBranch        *b_Muons_p;   //!
  TBranch        *b_Muons_eta;   //!
  TBranch        *b_Muons_phi;   //!
  TBranch        *b_Muons_validhist;   //!
  TBranch        *b_Muons_normchi2;   //!
  TBranch        *b_Muons_imp_point_x;   //!
  TBranch        *b_Muons_imp_point_y;   //!
  TBranch        *b_Muons_imp_point_z;   //!
  TBranch        *b_Muons_imp_point_p;   //!
  TBranch        *b_Muons_imp_point_pt;   //!
  TBranch        *b_Muons_phi_hb;   //!
  TBranch        *b_Muons_z_hb;   //!
  TBranch        *b_Muons_phi_he_n;   //!
  TBranch        *b_Muons_phi_he_p;   //!
  TBranch        *b_Muons_r_he_n;   //!
  TBranch        *b_Muons_r_he_p;   //!
  TBranch        *b_Muons_calocomp;   //!
  TBranch        *b_Muons_d0;   //!
  TBranch        *b_Muons_d0s;   //!
  TBranch        *b_Muons_tr_ch;   //!
  TBranch        *b_Muons_tr_pt;   //!
  TBranch        *b_Muons_tr_p;   //!
  TBranch        *b_Muons_tr_eta;   //!
  TBranch        *b_Muons_tr_phi;   //!
  TBranch        *b_Muons_tr_validhist;   //!
  TBranch        *b_Muons_tr_normchi2;   //!
  TBranch        *b_Muons_tr_imp_point_x;   //!
  TBranch        *b_Muons_tr_imp_point_y;   //!
  TBranch        *b_Muons_tr_imp_point_z;   //!
  TBranch        *b_Muons_tr_imp_point_p;   //!
  TBranch        *b_Muons_tr_imp_point_pt;   //!
  TBranch        *b_Muons_tr_calocomp;   //!
  TBranch        *b_Muons_tr_d0;   //!
  TBranch        *b_Muons_tr_d0s;   //!
  TBranch        *b_Muons_sa_phi_mb2;   //!
  TBranch        *b_Muons_sa_z_mb2;   //!
  TBranch        *b_Muons_sa_pseta;   //!
  TBranch        *b_Muons_sa_normchi2;   //!
  TBranch        *b_Muons_sa_validhits;   //!
  TBranch        *b_Muons_sa_ch;   //!
  TBranch        *b_Muons_sa_pt;   //!
  TBranch        *b_Muons_sa_p;   //!
  TBranch        *b_Muons_sa_eta;   //!
  TBranch        *b_Muons_sa_phi;   //!
  TBranch        *b_Muons_sa_outer_pt;   //!
  TBranch        *b_Muons_sa_inner_pt;   //!
  TBranch        *b_Muons_sa_outer_eta;   //!
  TBranch        *b_Muons_sa_inner_eta;   //!
  TBranch        *b_Muons_sa_outer_phi;   //!
  TBranch        *b_Muons_sa_inner_phi;   //!
  TBranch        *b_Muons_sa_outer_x;   //!
  TBranch        *b_Muons_sa_outer_y;   //!
  TBranch        *b_Muons_sa_outer_z;   //!
  TBranch        *b_Muons_sa_inner_x;   //!
  TBranch        *b_Muons_sa_inner_y;   //!
  TBranch        *b_Muons_sa_inner_z;   //!
  TBranch        *b_Muons_sa_imp_point_x;   //!
  TBranch        *b_Muons_sa_imp_point_y;   //!
  TBranch        *b_Muons_sa_imp_point_z;   //!
  TBranch        *b_Muons_sa_imp_point_p;   //!
  TBranch        *b_Muons_sa_imp_point_pt;   //!
  TBranch        *b_Muons_sa_phi_hb;   //!
  TBranch        *b_Muons_sa_z_hb;   //!
  TBranch        *b_Muons_sa_phi_he_n;   //!
  TBranch        *b_Muons_sa_phi_he_p;   //!
  TBranch        *b_Muons_sa_r_he_n;   //!
  TBranch        *b_Muons_sa_r_he_p;   //!
  
  MuonRecoTree(TTree *tree, const char * option);
  virtual ~MuonRecoTree();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(Long64_t maxevts);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  std::string m_option;
  
};

#endif

