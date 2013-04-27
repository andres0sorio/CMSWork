
#include "MuonRecoTree.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "CommonIncludes.h"

MuonRecoTree::MuonRecoTree(TTree *tree, const char * option)
{
  Init(tree);
  m_option = std::string(option);
  
}

MuonRecoTree::~MuonRecoTree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t MuonRecoTree::GetEntry(Long64_t entry)
{
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t MuonRecoTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void MuonRecoTree::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("Nmuons", &Nmuons, &b_Nmuons);
  fChain->SetBranchAddress("BeamSpotX", &BeamSpotX, &b_BeamSpotX);
  fChain->SetBranchAddress("BeamSpotY", &BeamSpotY, &b_BeamSpotY);
  fChain->SetBranchAddress("Muon_type", Muon_type, &b_Muon_type);
  fChain->SetBranchAddress("Muons_ch", Muons_ch, &b_Muons_ch);
  fChain->SetBranchAddress("Muons_pt", Muons_pt, &b_Muons_pt);
  fChain->SetBranchAddress("Muons_p", Muons_p, &b_Muons_p);
  fChain->SetBranchAddress("Muons_eta", Muons_eta, &b_Muons_eta);
  fChain->SetBranchAddress("Muons_phi", Muons_phi, &b_Muons_phi);
  fChain->SetBranchAddress("Muons_validhist", Muons_validhist, &b_Muons_validhist);
  fChain->SetBranchAddress("Muons_normchi2", Muons_normchi2, &b_Muons_normchi2);
  fChain->SetBranchAddress("Muons_imp_point_x", Muons_imp_point_x, &b_Muons_imp_point_x);
  fChain->SetBranchAddress("Muons_imp_point_y", Muons_imp_point_y, &b_Muons_imp_point_y);
  fChain->SetBranchAddress("Muons_imp_point_z", Muons_imp_point_z, &b_Muons_imp_point_z);
  fChain->SetBranchAddress("Muons_imp_point_p", Muons_imp_point_p, &b_Muons_imp_point_p);
  fChain->SetBranchAddress("Muons_imp_point_pt", Muons_imp_point_pt, &b_Muons_imp_point_pt);
  fChain->SetBranchAddress("Muons_phi_hb", Muons_phi_hb, &b_Muons_phi_hb);
  fChain->SetBranchAddress("Muons_z_hb", Muons_z_hb, &b_Muons_z_hb);
  fChain->SetBranchAddress("Muons_phi_he_n", Muons_phi_he_n, &b_Muons_phi_he_n);
  fChain->SetBranchAddress("Muons_phi_he_p", Muons_phi_he_p, &b_Muons_phi_he_p);
  fChain->SetBranchAddress("Muons_r_he_n", Muons_r_he_n, &b_Muons_r_he_n);
  fChain->SetBranchAddress("Muons_r_he_p", Muons_r_he_p, &b_Muons_r_he_p);
  fChain->SetBranchAddress("Muons_calocomp", Muons_calocomp, &b_Muons_calocomp);
  fChain->SetBranchAddress("Muons_d0", Muons_d0, &b_Muons_d0);
  fChain->SetBranchAddress("Muons_d0s", Muons_d0s, &b_Muons_d0s);
  fChain->SetBranchAddress("Muons_tr_ch", Muons_tr_ch, &b_Muons_tr_ch);
  fChain->SetBranchAddress("Muons_tr_pt", Muons_tr_pt, &b_Muons_tr_pt);
  fChain->SetBranchAddress("Muons_tr_p", Muons_tr_p, &b_Muons_tr_p);
  fChain->SetBranchAddress("Muons_tr_eta", Muons_tr_eta, &b_Muons_tr_eta);
  fChain->SetBranchAddress("Muons_tr_phi", Muons_tr_phi, &b_Muons_tr_phi);
  fChain->SetBranchAddress("Muons_tr_validhist", Muons_tr_validhist, &b_Muons_tr_validhist);
  fChain->SetBranchAddress("Muons_tr_normchi2", Muons_tr_normchi2, &b_Muons_tr_normchi2);
  fChain->SetBranchAddress("Muons_tr_imp_point_x", Muons_tr_imp_point_x, &b_Muons_tr_imp_point_x);
  fChain->SetBranchAddress("Muons_tr_imp_point_y", Muons_tr_imp_point_y, &b_Muons_tr_imp_point_y);
  fChain->SetBranchAddress("Muons_tr_imp_point_z", Muons_tr_imp_point_z, &b_Muons_tr_imp_point_z);
  fChain->SetBranchAddress("Muons_tr_imp_point_p", Muons_tr_imp_point_p, &b_Muons_tr_imp_point_p);
  fChain->SetBranchAddress("Muons_tr_imp_point_pt", Muons_tr_imp_point_pt, &b_Muons_tr_imp_point_pt);
  fChain->SetBranchAddress("Muons_tr_calocomp", Muons_tr_calocomp, &b_Muons_tr_calocomp);
  fChain->SetBranchAddress("Muons_tr_d0", Muons_tr_d0, &b_Muons_tr_d0);
  fChain->SetBranchAddress("Muons_tr_d0s", Muons_tr_d0s, &b_Muons_tr_d0s);
  fChain->SetBranchAddress("Muons_sa_phi_mb2", Muons_sa_phi_mb2, &b_Muons_sa_phi_mb2);
  fChain->SetBranchAddress("Muons_sa_z_mb2", Muons_sa_z_mb2, &b_Muons_sa_z_mb2);
  fChain->SetBranchAddress("Muons_sa_pseta", Muons_sa_pseta, &b_Muons_sa_pseta);
  fChain->SetBranchAddress("Muons_sa_normchi2", Muons_sa_normchi2, &b_Muons_sa_normchi2);
  fChain->SetBranchAddress("Muons_sa_validhits", Muons_sa_validhits, &b_Muons_sa_validhits);
  fChain->SetBranchAddress("Muons_sa_ch", Muons_sa_ch, &b_Muons_sa_ch);
  fChain->SetBranchAddress("Muons_sa_pt", Muons_sa_pt, &b_Muons_sa_pt);
  fChain->SetBranchAddress("Muons_sa_p", Muons_sa_p, &b_Muons_sa_p);
  fChain->SetBranchAddress("Muons_sa_eta", Muons_sa_eta, &b_Muons_sa_eta);
  fChain->SetBranchAddress("Muons_sa_phi", Muons_sa_phi, &b_Muons_sa_phi);
  fChain->SetBranchAddress("Muons_sa_outer_pt", Muons_sa_outer_pt, &b_Muons_sa_outer_pt);
  fChain->SetBranchAddress("Muons_sa_inner_pt", Muons_sa_inner_pt, &b_Muons_sa_inner_pt);
  fChain->SetBranchAddress("Muons_sa_outer_eta", Muons_sa_outer_eta, &b_Muons_sa_outer_eta);
  fChain->SetBranchAddress("Muons_sa_inner_eta", Muons_sa_inner_eta, &b_Muons_sa_inner_eta);
  fChain->SetBranchAddress("Muons_sa_outer_phi", Muons_sa_outer_phi, &b_Muons_sa_outer_phi);
  fChain->SetBranchAddress("Muons_sa_inner_phi", Muons_sa_inner_phi, &b_Muons_sa_inner_phi);
  fChain->SetBranchAddress("Muons_sa_outer_x", Muons_sa_outer_x, &b_Muons_sa_outer_x);
  fChain->SetBranchAddress("Muons_sa_outer_y", Muons_sa_outer_y, &b_Muons_sa_outer_y);
  fChain->SetBranchAddress("Muons_sa_outer_z", Muons_sa_outer_z, &b_Muons_sa_outer_z);
  fChain->SetBranchAddress("Muons_sa_inner_x", Muons_sa_inner_x, &b_Muons_sa_inner_x);
  fChain->SetBranchAddress("Muons_sa_inner_y", Muons_sa_inner_y, &b_Muons_sa_inner_y);
  fChain->SetBranchAddress("Muons_sa_inner_z", Muons_sa_inner_z, &b_Muons_sa_inner_z);
  fChain->SetBranchAddress("Muons_sa_imp_point_x", Muons_sa_imp_point_x, &b_Muons_sa_imp_point_x);
  fChain->SetBranchAddress("Muons_sa_imp_point_y", Muons_sa_imp_point_y, &b_Muons_sa_imp_point_y);
  fChain->SetBranchAddress("Muons_sa_imp_point_z", Muons_sa_imp_point_z, &b_Muons_sa_imp_point_z);
  fChain->SetBranchAddress("Muons_sa_imp_point_p", Muons_sa_imp_point_p, &b_Muons_sa_imp_point_p);
  fChain->SetBranchAddress("Muons_sa_imp_point_pt", Muons_sa_imp_point_pt, &b_Muons_sa_imp_point_pt);
  fChain->SetBranchAddress("Muons_sa_phi_hb", Muons_sa_phi_hb, &b_Muons_sa_phi_hb);
  fChain->SetBranchAddress("Muons_sa_z_hb", Muons_sa_z_hb, &b_Muons_sa_z_hb);
  fChain->SetBranchAddress("Muons_sa_phi_he_n", Muons_sa_phi_he_n, &b_Muons_sa_phi_he_n);
  fChain->SetBranchAddress("Muons_sa_phi_he_p", Muons_sa_phi_he_p, &b_Muons_sa_phi_he_p);
  fChain->SetBranchAddress("Muons_sa_r_he_n", Muons_sa_r_he_n, &b_Muons_sa_r_he_n);
  fChain->SetBranchAddress("Muons_sa_r_he_p", Muons_sa_r_he_p, &b_Muons_sa_r_he_p);
  Notify();
}

Bool_t MuonRecoTree::Notify()
{
  return kTRUE;
}

void MuonRecoTree::Show(Long64_t entry)
{
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t MuonRecoTree::Cut(Long64_t entry)
{
  return 1;
}

void MuonRecoTree::Loop(Long64_t maxevts)
{
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();

  if ( maxevts > 0 )
    nentries = maxevts;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }

  std::cout << nentries << std::endl;


}
