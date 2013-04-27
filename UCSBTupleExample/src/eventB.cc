// $Id: $
// Include files 

#include "eventB.h"

// local

//-----------------------------------------------------------------------------
// Implementation file for class : eventB
//
// 2008-10-25 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

eventB::eventB( TFile * infile )
{

  infile->cd();
  infile->cd("configurableAnalysis");
  
  TTree * tree = (TTree*)gDirectory->Get("eventB");
  
  Init(tree);
  
}

eventB::eventB( TChain * inchain )
{
  
  TTree * tree = (TTree*)inchain;
  Init(tree);
  
}

eventB::eventB( std::string infile )
{
  
  std::cout << "eventB> initialising: " << infile << std::endl;
  
  input = new TFile( infile.c_str(), "READ");
  
  input->cd();
  input->cd("configurableAnalysis");
  
  TTree * tree = (TTree*)gDirectory->Get("eventB");
  
  Init(tree);
  
  std::cout << "eventB> done" << std::endl;
  
}

//=============================================================================
// Destructor
//=============================================================================

eventB::~eventB()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

//=============================================================================
Int_t eventB::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t eventB::LoadTree(Long64_t entry)
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

void eventB::Init(TTree *tree)
{
  /* 
     The Init() function is called when the selector needs to initialize
     a new tree or chain. Typically here the branch addresses and branch
     pointers of the tree will be set.
     It is normally not necessary to make changes to the generated
     code, but the routine can be extended by the user if needed.
     Init() will be called many times when running on PROOF
     (once per file to be processed).
  */
  
  // Set object pointer
  L1Triggerbits_pass = 0;
  L1Triggerbits_entities = 0;
  ccelectrons_et = 0;
  ccelectrons_eta = 0;
  ccelectrons_phi = 0;
  ccelectrons_pt = 0;
  ccelectrons_px = 0;
  ccelectrons_py = 0;
  ccelectrons_pz = 0;
  ccelectrons_status = 0;
  ccelectrons_theta = 0;
  ccjets_et = 0;
  ccjets_eta = 0;
  ccjets_phi = 0;
  ccjets_pt = 0;
  ccjets_px = 0;
  ccjets_py = 0;
  ccjets_pz = 0;
  ccjets_status = 0;
  ccjets_theta = 0;
  ccjets_energy = 0;
  ccjets_mass = 0;
  ccmets_et = 0;
  ccmets_phi = 0;
  ccmets_px = 0;
  ccmets_py = 0;
  ccmets_status = 0;
  ccmuons_et = 0;
  ccmuons_eta = 0;
  ccmuons_phi = 0;
  ccmuons_pt = 0;
  ccmuons_px = 0;
  ccmuons_py = 0;
  ccmuons_pz = 0;
  ccmuons_status = 0;
  ccmuons_theta = 0;
  els_et = 0;
  els_eta = 0;
  els_phi = 0;
  els_pt = 0;
  els_px = 0;
  els_py = 0;
  els_pz = 0;
  els_status = 0;
  els_theta = 0;
  els_id = 0;
  els_cIso = 0;
  els_tIso = 0;
  els_chi2 = 0;
  els_class = 0;
  els_charge = 0;
  els_e = 0;
  els_e_hadOverEm = 0;
  els_eOverPIn = 0;
  els_eSeedOverPOut = 0;
  els_eSCraw = 0;
  els_eSeed = 0;
  els_dEtaIn = 0;
  els_dPhiIn = 0;
  els_dEtaOut = 0;
  els_dPhiOut = 0;
  els_numvalhits = 0;
  els_numlosthits = 0;
  els_numCluster = 0;
  els_tk_pt = 0;
  els_tk_phi = 0;
  els_tk_eta = 0;
  els_d0 = 0;
  els_dz = 0;
  els_vx = 0;
  els_vy = 0;
  els_vz = 0;
  els_ndof = 0;
  els_ptError = 0;
  els_d0Error = 0;
  els_dzError = 0;
  els_etaError = 0;
  els_phiError = 0;
  els_cpx = 0;
  els_cpy = 0;
  els_cpz = 0;
  els_vpx = 0;
  els_vpy = 0;
  els_vpz = 0;
  els_cx = 0;
  els_cy = 0;
  els_cz = 0;
  els_IDRobust = 0;
  hemi_et = 0;
  hemi_eta = 0;
  hemi_phi = 0;
  hemi_pt = 0;
  hemi_px = 0;
  hemi_py = 0;
  hemi_pz = 0;
  hemi_status = 0;
  hemi_theta = 0;
  jets_et = 0;
  jets_eta = 0;
  jets_phi = 0;
  jets_pt = 0;
  jets_px = 0;
  jets_py = 0;
  jets_pz = 0;
  jets_status = 0;
  jets_theta = 0;
  jets_parton_Id = 0;
  jets_parton_pt = 0;
  jets_parton_phi = 0;
  jets_parton_eta = 0;
  jets_parton_Energy = 0;
  jets_parton_mass = 0;
  jets_gen_et = 0;
  jets_gen_pt = 0;
  jets_gen_eta = 0;
  jets_gen_phi = 0;
  jets_gen_mass = 0;
  jets_gen_Energy = 0;
  jets_gen_motherID = 0;
  jets_chgEmE = 0;
  jets_chgHadE = 0;
  jets_chgMuE = 0;
  jets_chg_Mult = 0;
  jets_neutralEmE = 0;
  jets_neutralHadE = 0;
  jets_neutral_Mult = 0;
  jets_mu_Mult = 0;
  jets_corr_fctr_def = 0;
  jets_emf = 0;
  jets_ehf = 0;
  jets_n60 = 0;
  jets_n90 = 0;
  jets_area = 0;
  jets_max_em = 0;
  jets_max_had = 0;
  jets_Energy = 0;
  jets_mass = 0;
  mc_doc_id = 0;
  mc_doc_pt = 0;
  mc_doc_px = 0;
  mc_doc_py = 0;
  mc_doc_pz = 0;
  mc_doc_status = 0;
  mc_doc_mother_id = 0;
  mc_doc_vertex_x = 0;
  mc_doc_vertex_y = 0;
  mc_doc_vertex_z = 0;
  mc_doc_mass = 0;
  mc_doc_numOfDaughters = 0;
  mc_electrons_id = 0;
  mc_electrons_pt = 0;
  mc_electrons_px = 0;
  mc_electrons_py = 0;
  mc_electrons_pz = 0;
  mc_electrons_status = 0;
  mc_electrons_mother_id = 0;
  mc_electrons_vertex_x = 0;
  mc_electrons_vertex_y = 0;
  mc_electrons_vertex_z = 0;
  mc_electrons_mass = 0;
  mc_electrons_numOfDaughters = 0;
  mc_mus_id = 0;
  mc_mus_pt = 0;
  mc_mus_px = 0;
  mc_mus_py = 0;
  mc_mus_pz = 0;
  mc_mus_status = 0;
  mc_mus_mother_id = 0;
  mc_mus_vertex_x = 0;
  mc_mus_vertex_y = 0;
  mc_mus_vertex_z = 0;
  mc_mus_mass = 0;
  mc_mus_numOfDaughters = 0;
  mets_et = 0;
  mets_phi = 0;
  mets_ex = 0;
  mets_ey = 0;
  mets_gen_et = 0;
  mets_gen_phi = 0;
  mets_sumEt = 0;
  mets_unCPhi = 0;
  mets_unCPt = 0;
  mus_et = 0;
  mus_eta = 0;
  mus_phi = 0;
  mus_pt = 0;
  mus_px = 0;
  mus_py = 0;
  mus_pz = 0;
  mus_status = 0;
  mus_theta = 0;
  mus_tkHits = 0;
  mus_cIso = 0;
  mus_tIso = 0;
  mus_id = 0;
  mus_charge = 0;
  mus_cm_chi2 = 0;
  mus_cm_ndof = 0;
  mus_cm_chg = 0;
  mus_cm_pt = 0;
  mus_cm_px = 0;
  mus_cm_py = 0;
  mus_cm_pz = 0;
  mus_cm_eta = 0;
  mus_cm_phi = 0;
  mus_cm_theta = 0;
  mus_cm_d0 = 0;
  mus_cm_dz = 0;
  mus_cm_vx = 0;
  mus_cm_vy = 0;
  mus_cm_vz = 0;
  mus_cm_numvalhits = 0;
  mus_cm_numlosthits = 0;
  mus_cm_d0Err = 0;
  mus_cm_dzErr = 0;
  mus_cm_ptErr = 0;
  mus_cm_etaErr = 0;
  mus_cm_phiErr = 0;
  mus_tk_chi2 = 0;
  mus_tk_ndof = 0;
  mus_tk_chg = 0;
  mus_tk_pt = 0;
  mus_tk_px = 0;
  mus_tk_py = 0;
  mus_tk_pz = 0;
  mus_tk_eta = 0;
  mus_tk_phi = 0;
  mus_tk_theta = 0;
  mus_tk_d0 = 0;
  mus_tk_dz = 0;
  mus_tk_vx = 0;
  mus_tk_vy = 0;
  mus_tk_vz = 0;
  mus_tk_numvalhits = 0;
  mus_tk_numlosthits = 0;
  mus_tk_d0Err = 0;
  mus_tk_dzErr = 0;
  mus_tk_ptErr = 0;
  mus_tk_etaErr = 0;
  mus_tk_phiErr = 0;
  mus_stamu_chi2 = 0;
  mus_stamu_ndof = 0;
  mus_stamu_chg = 0;
  mus_stamu_pt = 0;
  mus_stamu_px = 0;
  mus_stamu_py = 0;
  mus_stamu_pz = 0;
  mus_stamu_eta = 0;
  mus_stamu_phi = 0;
  mus_stamu_theta = 0;
  mus_stamu_d0 = 0;
  mus_stamu_dz = 0;
  mus_stamu_vx = 0;
  mus_stamu_vy = 0;
  mus_stamu_vz = 0;
  mus_stamu_numvalhits = 0;
  mus_stamu_numlosthits = 0;
  mus_stamu_d0Err = 0;
  mus_stamu_dzErr = 0;
  mus_stamu_ptErr = 0;
  mus_stamu_etaErr = 0;
  mus_stamu_phiErr = 0;
  mus_num_matches = 0;
  photons_et = 0;
  photons_eta = 0;
  photons_phi = 0;
  photons_pt = 0;
  photons_px = 0;
  photons_py = 0;
  photons_pz = 0;
  photons_status = 0;
  photons_theta = 0;
  tracks_chi2 = 0;
  tracks_ndof = 0;
  tracks_chg = 0;
  tracks_pt = 0;
  tracks_px = 0;
  tracks_py = 0;
  tracks_pz = 0;
  tracks_eta = 0;
  tracks_phi = 0;
  tracks_theta = 0;
  tracks_d0 = 0;
  tracks_dz = 0;
  tracks_vx = 0;
  tracks_vy = 0;
  tracks_vz = 0;
  tracks_numvalhits = 0;
  tracks_numlosthits = 0;
  tracks_d0Err = 0;
  tracks_dzErr = 0;
  tracks_ptErr = 0;
  tracks_etaErr = 0;
  tracks_phiErr = 0;
  tracks_Nrechits = 0;
  tracks_innerHitX = 0;
  tracks_innerHitY = 0;
  tracks_innerHitZ = 0;
  tracks_outerHitX = 0;
  tracks_outerHitY = 0;
  tracks_outerHitZ = 0;

  // Set branch addresses and branch pointers
  if (!tree) return;
  
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("NL1Triggerbits", &NL1Triggerbits, &b_NL1Triggerbits);
  fChain->SetBranchAddress("L1Triggerbits_pass", &L1Triggerbits_pass, &b_L1Triggerbits_pass);
  fChain->SetBranchAddress("L1Triggerbits_entities", &L1Triggerbits_entities, &b_L1Triggerbits_entities);
  fChain->SetBranchAddress("Nccelectrons", &Nccelectrons, &b_Nccelectrons);
  fChain->SetBranchAddress("ccelectrons_et", &ccelectrons_et, &b_ccelectrons_et);
  fChain->SetBranchAddress("ccelectrons_eta", &ccelectrons_eta, &b_ccelectrons_eta);
  fChain->SetBranchAddress("ccelectrons_phi", &ccelectrons_phi, &b_ccelectrons_phi);
  fChain->SetBranchAddress("ccelectrons_pt", &ccelectrons_pt, &b_ccelectrons_pt);
  fChain->SetBranchAddress("ccelectrons_px", &ccelectrons_px, &b_ccelectrons_px);
  fChain->SetBranchAddress("ccelectrons_py", &ccelectrons_py, &b_ccelectrons_py);
  fChain->SetBranchAddress("ccelectrons_pz", &ccelectrons_pz, &b_ccelectrons_pz);
  fChain->SetBranchAddress("ccelectrons_status", &ccelectrons_status, &b_ccelectrons_status);
  fChain->SetBranchAddress("ccelectrons_theta", &ccelectrons_theta, &b_ccelectrons_theta);
  fChain->SetBranchAddress("Nccjets", &Nccjets, &b_Nccjets);
  fChain->SetBranchAddress("ccjets_et", &ccjets_et, &b_ccjets_et);
  fChain->SetBranchAddress("ccjets_eta", &ccjets_eta, &b_ccjets_eta);
  fChain->SetBranchAddress("ccjets_phi", &ccjets_phi, &b_ccjets_phi);
  fChain->SetBranchAddress("ccjets_pt", &ccjets_pt, &b_ccjets_pt);
  fChain->SetBranchAddress("ccjets_px", &ccjets_px, &b_ccjets_px);
  fChain->SetBranchAddress("ccjets_py", &ccjets_py, &b_ccjets_py);
  fChain->SetBranchAddress("ccjets_pz", &ccjets_pz, &b_ccjets_pz);
  fChain->SetBranchAddress("ccjets_status", &ccjets_status, &b_ccjets_status);
  fChain->SetBranchAddress("ccjets_theta", &ccjets_theta, &b_ccjets_theta);
  fChain->SetBranchAddress("ccjets_energy", &ccjets_energy, &b_ccjets_energy);
  fChain->SetBranchAddress("ccjets_mass", &ccjets_mass, &b_ccjets_mass);
  fChain->SetBranchAddress("Nccmets", &Nccmets, &b_Nccmets);
  fChain->SetBranchAddress("ccmets_et", &ccmets_et, &b_ccmets_et);
  fChain->SetBranchAddress("ccmets_phi", &ccmets_phi, &b_ccmets_phi);
  fChain->SetBranchAddress("ccmets_px", &ccmets_px, &b_ccmets_px);
  fChain->SetBranchAddress("ccmets_py", &ccmets_py, &b_ccmets_py);
  fChain->SetBranchAddress("ccmets_status", &ccmets_status, &b_ccmets_status);
  fChain->SetBranchAddress("Nccmuons", &Nccmuons, &b_Nccmuons);
  fChain->SetBranchAddress("ccmuons_et", &ccmuons_et, &b_ccmuons_et);
  fChain->SetBranchAddress("ccmuons_eta", &ccmuons_eta, &b_ccmuons_eta);
  fChain->SetBranchAddress("ccmuons_phi", &ccmuons_phi, &b_ccmuons_phi);
  fChain->SetBranchAddress("ccmuons_pt", &ccmuons_pt, &b_ccmuons_pt);
  fChain->SetBranchAddress("ccmuons_px", &ccmuons_px, &b_ccmuons_px);
  fChain->SetBranchAddress("ccmuons_py", &ccmuons_py, &b_ccmuons_py);
  fChain->SetBranchAddress("ccmuons_pz", &ccmuons_pz, &b_ccmuons_pz);
  fChain->SetBranchAddress("ccmuons_status", &ccmuons_status, &b_ccmuons_status);
  fChain->SetBranchAddress("ccmuons_theta", &ccmuons_theta, &b_ccmuons_theta);
  fChain->SetBranchAddress("Nels", &Nels, &b_Nels);
  fChain->SetBranchAddress("els_et", &els_et, &b_els_et);
  fChain->SetBranchAddress("els_eta", &els_eta, &b_els_eta);
  fChain->SetBranchAddress("els_phi", &els_phi, &b_els_phi);
  fChain->SetBranchAddress("els_pt", &els_pt, &b_els_pt);
  fChain->SetBranchAddress("els_px", &els_px, &b_els_px);
  fChain->SetBranchAddress("els_py", &els_py, &b_els_py);
  fChain->SetBranchAddress("els_pz", &els_pz, &b_els_pz);
  fChain->SetBranchAddress("els_status", &els_status, &b_els_status);
  fChain->SetBranchAddress("els_theta", &els_theta, &b_els_theta);
  fChain->SetBranchAddress("els_id", &els_id, &b_els_id);
  fChain->SetBranchAddress("els_cIso", &els_cIso, &b_els_cIso);
  fChain->SetBranchAddress("els_tIso", &els_tIso, &b_els_tIso);
  fChain->SetBranchAddress("els_chi2", &els_chi2, &b_els_chi2);
  fChain->SetBranchAddress("els_class", &els_class, &b_els_class);
  fChain->SetBranchAddress("els_charge", &els_charge, &b_els_charge);
  fChain->SetBranchAddress("els_e", &els_e, &b_els_e);
  fChain->SetBranchAddress("els_e_hadOverEm", &els_e_hadOverEm, &b_els_e_hadOverEm);
  fChain->SetBranchAddress("els_eOverPIn", &els_eOverPIn, &b_els_eOverPIn);
  fChain->SetBranchAddress("els_eSeedOverPOut", &els_eSeedOverPOut, &b_els_eSeedOverPOut);
  fChain->SetBranchAddress("els_eSCraw", &els_eSCraw, &b_els_eSCraw);
  fChain->SetBranchAddress("els_eSeed", &els_eSeed, &b_els_eSeed);
  fChain->SetBranchAddress("els_dEtaIn", &els_dEtaIn, &b_els_dEtaIn);
  fChain->SetBranchAddress("els_dPhiIn", &els_dPhiIn, &b_els_dPhiIn);
  fChain->SetBranchAddress("els_dEtaOut", &els_dEtaOut, &b_els_dEtaOut);
  fChain->SetBranchAddress("els_dPhiOut", &els_dPhiOut, &b_els_dPhiOut);
  fChain->SetBranchAddress("els_numvalhits", &els_numvalhits, &b_els_numvalhits);
  fChain->SetBranchAddress("els_numlosthits", &els_numlosthits, &b_els_numlosthits);
  fChain->SetBranchAddress("els_numCluster", &els_numCluster, &b_els_numCluster);
  fChain->SetBranchAddress("els_tk_pt", &els_tk_pt, &b_els_tk_pt);
  fChain->SetBranchAddress("els_tk_phi", &els_tk_phi, &b_els_tk_phi);
  fChain->SetBranchAddress("els_tk_eta", &els_tk_eta, &b_els_tk_eta);
  fChain->SetBranchAddress("els_d0", &els_d0, &b_els_d0);
  fChain->SetBranchAddress("els_dz", &els_dz, &b_els_dz);
  fChain->SetBranchAddress("els_vx", &els_vx, &b_els_vx);
  fChain->SetBranchAddress("els_vy", &els_vy, &b_els_vy);
  fChain->SetBranchAddress("els_vz", &els_vz, &b_els_vz);
  fChain->SetBranchAddress("els_ndof", &els_ndof, &b_els_ndof);
  fChain->SetBranchAddress("els_ptError", &els_ptError, &b_els_ptError);
  fChain->SetBranchAddress("els_d0Error", &els_d0Error, &b_els_d0Error);
  fChain->SetBranchAddress("els_dzError", &els_dzError, &b_els_dzError);
  fChain->SetBranchAddress("els_etaError", &els_etaError, &b_els_etaError);
  fChain->SetBranchAddress("els_phiError", &els_phiError, &b_els_phiError);
  fChain->SetBranchAddress("els_cpx", &els_cpx, &b_els_cpx);
  fChain->SetBranchAddress("els_cpy", &els_cpy, &b_els_cpy);
  fChain->SetBranchAddress("els_cpz", &els_cpz, &b_els_cpz);
  fChain->SetBranchAddress("els_vpx", &els_vpx, &b_els_vpx);
  fChain->SetBranchAddress("els_vpy", &els_vpy, &b_els_vpy);
  fChain->SetBranchAddress("els_vpz", &els_vpz, &b_els_vpz);
  fChain->SetBranchAddress("els_cx", &els_cx, &b_els_cx);
  fChain->SetBranchAddress("els_cy", &els_cy, &b_els_cy);
  fChain->SetBranchAddress("els_cz", &els_cz, &b_els_cz);
  fChain->SetBranchAddress("els_IDRobust", &els_IDRobust, &b_els_IDRobust);
  fChain->SetBranchAddress("Nhemi", &Nhemi, &b_Nhemi);
  fChain->SetBranchAddress("hemi_et", &hemi_et, &b_hemi_et);
  fChain->SetBranchAddress("hemi_eta", &hemi_eta, &b_hemi_eta);
  fChain->SetBranchAddress("hemi_phi", &hemi_phi, &b_hemi_phi);
  fChain->SetBranchAddress("hemi_pt", &hemi_pt, &b_hemi_pt);
  fChain->SetBranchAddress("hemi_px", &hemi_px, &b_hemi_px);
  fChain->SetBranchAddress("hemi_py", &hemi_py, &b_hemi_py);
  fChain->SetBranchAddress("hemi_pz", &hemi_pz, &b_hemi_pz);
  fChain->SetBranchAddress("hemi_status", &hemi_status, &b_hemi_status);
  fChain->SetBranchAddress("hemi_theta", &hemi_theta, &b_hemi_theta);
  fChain->SetBranchAddress("Njets", &Njets, &b_Njets);
  fChain->SetBranchAddress("jets_et", &jets_et, &b_jets_et);
  fChain->SetBranchAddress("jets_eta", &jets_eta, &b_jets_eta);
  fChain->SetBranchAddress("jets_phi", &jets_phi, &b_jets_phi);
  fChain->SetBranchAddress("jets_pt", &jets_pt, &b_jets_pt);
  fChain->SetBranchAddress("jets_px", &jets_px, &b_jets_px);
  fChain->SetBranchAddress("jets_py", &jets_py, &b_jets_py);
  fChain->SetBranchAddress("jets_pz", &jets_pz, &b_jets_pz);
  fChain->SetBranchAddress("jets_status", &jets_status, &b_jets_status);
  fChain->SetBranchAddress("jets_theta", &jets_theta, &b_jets_theta);
  fChain->SetBranchAddress("jets_parton_Id", &jets_parton_Id, &b_jets_parton_Id);
  fChain->SetBranchAddress("jets_parton_pt", &jets_parton_pt, &b_jets_parton_pt);
  fChain->SetBranchAddress("jets_parton_phi", &jets_parton_phi, &b_jets_parton_phi);
  fChain->SetBranchAddress("jets_parton_eta", &jets_parton_eta, &b_jets_parton_eta);
  fChain->SetBranchAddress("jets_parton_Energy", &jets_parton_Energy, &b_jets_parton_Energy);
  fChain->SetBranchAddress("jets_parton_mass", &jets_parton_mass, &b_jets_parton_mass);
  fChain->SetBranchAddress("jets_gen_et", &jets_gen_et, &b_jets_gen_et);
  fChain->SetBranchAddress("jets_gen_pt", &jets_gen_pt, &b_jets_gen_pt);
  fChain->SetBranchAddress("jets_gen_eta", &jets_gen_eta, &b_jets_gen_eta);
  fChain->SetBranchAddress("jets_gen_phi", &jets_gen_phi, &b_jets_gen_phi);
  fChain->SetBranchAddress("jets_gen_mass", &jets_gen_mass, &b_jets_gen_mass);
  fChain->SetBranchAddress("jets_gen_Energy", &jets_gen_Energy, &b_jets_gen_Energy);
  fChain->SetBranchAddress("jets_gen_motherID", &jets_gen_motherID, &b_jets_gen_motherID);
  fChain->SetBranchAddress("jets_chgEmE", &jets_chgEmE, &b_jets_chgEmE);
  fChain->SetBranchAddress("jets_chgHadE", &jets_chgHadE, &b_jets_chgHadE);
  fChain->SetBranchAddress("jets_chgMuE", &jets_chgMuE, &b_jets_chgMuE);
  fChain->SetBranchAddress("jets_chg_Mult", &jets_chg_Mult, &b_jets_chg_Mult);
  fChain->SetBranchAddress("jets_neutralEmE", &jets_neutralEmE, &b_jets_neutralEmE);
  fChain->SetBranchAddress("jets_neutralHadE", &jets_neutralHadE, &b_jets_neutralHadE);
  fChain->SetBranchAddress("jets_neutral_Mult", &jets_neutral_Mult, &b_jets_neutral_Mult);
  fChain->SetBranchAddress("jets_mu_Mult", &jets_mu_Mult, &b_jets_mu_Mult);
  fChain->SetBranchAddress("jets_corr_fctr_def", &jets_corr_fctr_def, &b_jets_corr_fctr_def);
  fChain->SetBranchAddress("jets_emf", &jets_emf, &b_jets_emf);
  fChain->SetBranchAddress("jets_ehf", &jets_ehf, &b_jets_ehf);
  fChain->SetBranchAddress("jets_n60", &jets_n60, &b_jets_n60);
  fChain->SetBranchAddress("jets_n90", &jets_n90, &b_jets_n90);
  fChain->SetBranchAddress("jets_area", &jets_area, &b_jets_area);
  fChain->SetBranchAddress("jets_max_em", &jets_max_em, &b_jets_max_em);
  fChain->SetBranchAddress("jets_max_had", &jets_max_had, &b_jets_max_had);
  fChain->SetBranchAddress("jets_Energy", &jets_Energy, &b_jets_Energy);
  fChain->SetBranchAddress("jets_mass", &jets_mass, &b_jets_mass);
  fChain->SetBranchAddress("Nmc_doc", &Nmc_doc, &b_Nmc_doc);
  fChain->SetBranchAddress("mc_doc_id", &mc_doc_id, &b_mc_doc_id);
  fChain->SetBranchAddress("mc_doc_pt", &mc_doc_pt, &b_mc_doc_pt);
  fChain->SetBranchAddress("mc_doc_px", &mc_doc_px, &b_mc_doc_px);
  fChain->SetBranchAddress("mc_doc_py", &mc_doc_py, &b_mc_doc_py);
  fChain->SetBranchAddress("mc_doc_pz", &mc_doc_pz, &b_mc_doc_pz);
  fChain->SetBranchAddress("mc_doc_status", &mc_doc_status, &b_mc_doc_status);
  fChain->SetBranchAddress("mc_doc_mother_id", &mc_doc_mother_id, &b_mc_doc_mother_id);
  fChain->SetBranchAddress("mc_doc_vertex_x", &mc_doc_vertex_x, &b_mc_doc_vertex_x);
  fChain->SetBranchAddress("mc_doc_vertex_y", &mc_doc_vertex_y, &b_mc_doc_vertex_y);
  fChain->SetBranchAddress("mc_doc_vertex_z", &mc_doc_vertex_z, &b_mc_doc_vertex_z);
  fChain->SetBranchAddress("mc_doc_mass", &mc_doc_mass, &b_mc_doc_mass);
  fChain->SetBranchAddress("mc_doc_numOfDaughters", &mc_doc_numOfDaughters, &b_mc_doc_numOfDaughters);
  fChain->SetBranchAddress("Nmc_electrons", &Nmc_electrons, &b_Nmc_electrons);
  fChain->SetBranchAddress("mc_electrons_id", &mc_electrons_id, &b_mc_electrons_id);
  fChain->SetBranchAddress("mc_electrons_pt", &mc_electrons_pt, &b_mc_electrons_pt);
  fChain->SetBranchAddress("mc_electrons_px", &mc_electrons_px, &b_mc_electrons_px);
  fChain->SetBranchAddress("mc_electrons_py", &mc_electrons_py, &b_mc_electrons_py);
  fChain->SetBranchAddress("mc_electrons_pz", &mc_electrons_pz, &b_mc_electrons_pz);
  fChain->SetBranchAddress("mc_electrons_status", &mc_electrons_status, &b_mc_electrons_status);
  fChain->SetBranchAddress("mc_electrons_mother_id", &mc_electrons_mother_id, &b_mc_electrons_mother_id);
  fChain->SetBranchAddress("mc_electrons_vertex_x", &mc_electrons_vertex_x, &b_mc_electrons_vertex_x);
  fChain->SetBranchAddress("mc_electrons_vertex_y", &mc_electrons_vertex_y, &b_mc_electrons_vertex_y);
  fChain->SetBranchAddress("mc_electrons_vertex_z", &mc_electrons_vertex_z, &b_mc_electrons_vertex_z);
  fChain->SetBranchAddress("mc_electrons_mass", &mc_electrons_mass, &b_mc_electrons_mass);
  fChain->SetBranchAddress("mc_electrons_numOfDaughters", &mc_electrons_numOfDaughters, 
                           &b_mc_electrons_numOfDaughters);
  fChain->SetBranchAddress("Nmc_mus", &Nmc_mus, &b_Nmc_mus);
  fChain->SetBranchAddress("mc_mus_id", &mc_mus_id, &b_mc_mus_id);
  fChain->SetBranchAddress("mc_mus_pt", &mc_mus_pt, &b_mc_mus_pt);
  fChain->SetBranchAddress("mc_mus_px", &mc_mus_px, &b_mc_mus_px);
  fChain->SetBranchAddress("mc_mus_py", &mc_mus_py, &b_mc_mus_py);
  fChain->SetBranchAddress("mc_mus_pz", &mc_mus_pz, &b_mc_mus_pz);
  fChain->SetBranchAddress("mc_mus_status", &mc_mus_status, &b_mc_mus_status);
  fChain->SetBranchAddress("mc_mus_mother_id", &mc_mus_mother_id, &b_mc_mus_mother_id);
  fChain->SetBranchAddress("mc_mus_vertex_x", &mc_mus_vertex_x, &b_mc_mus_vertex_x);
  fChain->SetBranchAddress("mc_mus_vertex_y", &mc_mus_vertex_y, &b_mc_mus_vertex_y);
  fChain->SetBranchAddress("mc_mus_vertex_z", &mc_mus_vertex_z, &b_mc_mus_vertex_z);
  fChain->SetBranchAddress("mc_mus_mass", &mc_mus_mass, &b_mc_mus_mass);
  fChain->SetBranchAddress("mc_mus_numOfDaughters", &mc_mus_numOfDaughters, &b_mc_mus_numOfDaughters);
  fChain->SetBranchAddress("Nmets", &Nmets, &b_Nmets);
  fChain->SetBranchAddress("mets_et", &mets_et, &b_mets_et);
  fChain->SetBranchAddress("mets_phi", &mets_phi, &b_mets_phi);
  fChain->SetBranchAddress("mets_ex", &mets_ex, &b_mets_ex);
  fChain->SetBranchAddress("mets_ey", &mets_ey, &b_mets_ey);
  fChain->SetBranchAddress("mets_gen_et", &mets_gen_et, &b_mets_gen_et);
  fChain->SetBranchAddress("mets_gen_phi", &mets_gen_phi, &b_mets_gen_phi);
  fChain->SetBranchAddress("mets_sumEt", &mets_sumEt, &b_mets_sumEt);
  fChain->SetBranchAddress("mets_unCPhi", &mets_unCPhi, &b_mets_unCPhi);
  fChain->SetBranchAddress("mets_unCPt", &mets_unCPt, &b_mets_unCPt);
  fChain->SetBranchAddress("Nmus", &Nmus, &b_Nmus);
  fChain->SetBranchAddress("mus_et", &mus_et, &b_mus_et);
  fChain->SetBranchAddress("mus_eta", &mus_eta, &b_mus_eta);
  fChain->SetBranchAddress("mus_phi", &mus_phi, &b_mus_phi);
  fChain->SetBranchAddress("mus_pt", &mus_pt, &b_mus_pt);
  fChain->SetBranchAddress("mus_px", &mus_px, &b_mus_px);
  fChain->SetBranchAddress("mus_py", &mus_py, &b_mus_py);
  fChain->SetBranchAddress("mus_pz", &mus_pz, &b_mus_pz);
  fChain->SetBranchAddress("mus_status", &mus_status, &b_mus_status);
  fChain->SetBranchAddress("mus_theta", &mus_theta, &b_mus_theta);
  fChain->SetBranchAddress("mus_tkHits", &mus_tkHits, &b_mus_tkHits);
  fChain->SetBranchAddress("mus_cIso", &mus_cIso, &b_mus_cIso);
  fChain->SetBranchAddress("mus_tIso", &mus_tIso, &b_mus_tIso);
  fChain->SetBranchAddress("mus_id", &mus_id, &b_mus_id);
  fChain->SetBranchAddress("mus_charge", &mus_charge, &b_mus_charge);
  fChain->SetBranchAddress("mus_cm_chi2", &mus_cm_chi2, &b_mus_cm_chi2);
  fChain->SetBranchAddress("mus_cm_ndof", &mus_cm_ndof, &b_mus_cm_ndof);
  fChain->SetBranchAddress("mus_cm_chg", &mus_cm_chg, &b_mus_cm_chg);
  fChain->SetBranchAddress("mus_cm_pt", &mus_cm_pt, &b_mus_cm_pt);
  fChain->SetBranchAddress("mus_cm_px", &mus_cm_px, &b_mus_cm_px);
  fChain->SetBranchAddress("mus_cm_py", &mus_cm_py, &b_mus_cm_py);
  fChain->SetBranchAddress("mus_cm_pz", &mus_cm_pz, &b_mus_cm_pz);
  fChain->SetBranchAddress("mus_cm_eta", &mus_cm_eta, &b_mus_cm_eta);
  fChain->SetBranchAddress("mus_cm_phi", &mus_cm_phi, &b_mus_cm_phi);
  fChain->SetBranchAddress("mus_cm_theta", &mus_cm_theta, &b_mus_cm_theta);
  fChain->SetBranchAddress("mus_cm_d0", &mus_cm_d0, &b_mus_cm_d0);
  fChain->SetBranchAddress("mus_cm_dz", &mus_cm_dz, &b_mus_cm_dz);
  fChain->SetBranchAddress("mus_cm_vx", &mus_cm_vx, &b_mus_cm_vx);
  fChain->SetBranchAddress("mus_cm_vy", &mus_cm_vy, &b_mus_cm_vy);
  fChain->SetBranchAddress("mus_cm_vz", &mus_cm_vz, &b_mus_cm_vz);
  fChain->SetBranchAddress("mus_cm_numvalhits", &mus_cm_numvalhits, &b_mus_cm_numvalhits);
  fChain->SetBranchAddress("mus_cm_numlosthits", &mus_cm_numlosthits, &b_mus_cm_numlosthits);
  fChain->SetBranchAddress("mus_cm_d0Err", &mus_cm_d0Err, &b_mus_cm_d0Err);
  fChain->SetBranchAddress("mus_cm_dzErr", &mus_cm_dzErr, &b_mus_cm_dzErr);
  fChain->SetBranchAddress("mus_cm_ptErr", &mus_cm_ptErr, &b_mus_cm_ptErr);
  fChain->SetBranchAddress("mus_cm_etaErr", &mus_cm_etaErr, &b_mus_cm_etaErr);
  fChain->SetBranchAddress("mus_cm_phiErr", &mus_cm_phiErr, &b_mus_cm_phiErr);
  fChain->SetBranchAddress("mus_tk_chi2", &mus_tk_chi2, &b_mus_tk_chi2);
  fChain->SetBranchAddress("mus_tk_ndof", &mus_tk_ndof, &b_mus_tk_ndof);
  fChain->SetBranchAddress("mus_tk_chg", &mus_tk_chg, &b_mus_tk_chg);
  fChain->SetBranchAddress("mus_tk_pt", &mus_tk_pt, &b_mus_tk_pt);
  fChain->SetBranchAddress("mus_tk_px", &mus_tk_px, &b_mus_tk_px);
  fChain->SetBranchAddress("mus_tk_py", &mus_tk_py, &b_mus_tk_py);
  fChain->SetBranchAddress("mus_tk_pz", &mus_tk_pz, &b_mus_tk_pz);
  fChain->SetBranchAddress("mus_tk_eta", &mus_tk_eta, &b_mus_tk_eta);
  fChain->SetBranchAddress("mus_tk_phi", &mus_tk_phi, &b_mus_tk_phi);
  fChain->SetBranchAddress("mus_tk_theta", &mus_tk_theta, &b_mus_tk_theta);
  fChain->SetBranchAddress("mus_tk_d0", &mus_tk_d0, &b_mus_tk_d0);
  fChain->SetBranchAddress("mus_tk_dz", &mus_tk_dz, &b_mus_tk_dz);
  fChain->SetBranchAddress("mus_tk_vx", &mus_tk_vx, &b_mus_tk_vx);
  fChain->SetBranchAddress("mus_tk_vy", &mus_tk_vy, &b_mus_tk_vy);
  fChain->SetBranchAddress("mus_tk_vz", &mus_tk_vz, &b_mus_tk_vz);
  fChain->SetBranchAddress("mus_tk_numvalhits", &mus_tk_numvalhits, &b_mus_tk_numvalhits);
  fChain->SetBranchAddress("mus_tk_numlosthits", &mus_tk_numlosthits, &b_mus_tk_numlosthits);
  fChain->SetBranchAddress("mus_tk_d0Err", &mus_tk_d0Err, &b_mus_tk_d0Err);
  fChain->SetBranchAddress("mus_tk_dzErr", &mus_tk_dzErr, &b_mus_tk_dzErr);
  fChain->SetBranchAddress("mus_tk_ptErr", &mus_tk_ptErr, &b_mus_tk_ptErr);
  fChain->SetBranchAddress("mus_tk_etaErr", &mus_tk_etaErr, &b_mus_tk_etaErr);
  fChain->SetBranchAddress("mus_tk_phiErr", &mus_tk_phiErr, &b_mus_tk_phiErr);
  fChain->SetBranchAddress("mus_stamu_chi2", &mus_stamu_chi2, &b_mus_stamu_chi2);
  fChain->SetBranchAddress("mus_stamu_ndof", &mus_stamu_ndof, &b_mus_stamu_ndof);
  fChain->SetBranchAddress("mus_stamu_chg", &mus_stamu_chg, &b_mus_stamu_chg);
  fChain->SetBranchAddress("mus_stamu_pt", &mus_stamu_pt, &b_mus_stamu_pt);
  fChain->SetBranchAddress("mus_stamu_px", &mus_stamu_px, &b_mus_stamu_px);
  fChain->SetBranchAddress("mus_stamu_py", &mus_stamu_py, &b_mus_stamu_py);
  fChain->SetBranchAddress("mus_stamu_pz", &mus_stamu_pz, &b_mus_stamu_pz);
  fChain->SetBranchAddress("mus_stamu_eta", &mus_stamu_eta, &b_mus_stamu_eta);
  fChain->SetBranchAddress("mus_stamu_phi", &mus_stamu_phi, &b_mus_stamu_phi);
  fChain->SetBranchAddress("mus_stamu_theta", &mus_stamu_theta, &b_mus_stamu_theta);
  fChain->SetBranchAddress("mus_stamu_d0", &mus_stamu_d0, &b_mus_stamu_d0);
  fChain->SetBranchAddress("mus_stamu_dz", &mus_stamu_dz, &b_mus_stamu_dz);
  fChain->SetBranchAddress("mus_stamu_vx", &mus_stamu_vx, &b_mus_stamu_vx);
  fChain->SetBranchAddress("mus_stamu_vy", &mus_stamu_vy, &b_mus_stamu_vy);
  fChain->SetBranchAddress("mus_stamu_vz", &mus_stamu_vz, &b_mus_stamu_vz);
  fChain->SetBranchAddress("mus_stamu_numvalhits", &mus_stamu_numvalhits, &b_mus_stamu_numvalhits);
  fChain->SetBranchAddress("mus_stamu_numlosthits", &mus_stamu_numlosthits, &b_mus_stamu_numlosthits);
  fChain->SetBranchAddress("mus_stamu_d0Err", &mus_stamu_d0Err, &b_mus_stamu_d0Err);
  fChain->SetBranchAddress("mus_stamu_dzErr", &mus_stamu_dzErr, &b_mus_stamu_dzErr);
  fChain->SetBranchAddress("mus_stamu_ptErr", &mus_stamu_ptErr, &b_mus_stamu_ptErr);
  fChain->SetBranchAddress("mus_stamu_etaErr", &mus_stamu_etaErr, &b_mus_stamu_etaErr);
  fChain->SetBranchAddress("mus_stamu_phiErr", &mus_stamu_phiErr, &b_mus_stamu_phiErr);
  fChain->SetBranchAddress("mus_num_matches", &mus_num_matches, &b_mus_num_matches);
  fChain->SetBranchAddress("Nphotons", &Nphotons, &b_Nphotons);
  fChain->SetBranchAddress("photons_et", &photons_et, &b_photons_et);
  fChain->SetBranchAddress("photons_eta", &photons_eta, &b_photons_eta);
  fChain->SetBranchAddress("photons_phi", &photons_phi, &b_photons_phi);
  fChain->SetBranchAddress("photons_pt", &photons_pt, &b_photons_pt);
  fChain->SetBranchAddress("photons_px", &photons_px, &b_photons_px);
  fChain->SetBranchAddress("photons_py", &photons_py, &b_photons_py);
  fChain->SetBranchAddress("photons_pz", &photons_pz, &b_photons_pz);
  fChain->SetBranchAddress("photons_status", &photons_status, &b_photons_status);
  fChain->SetBranchAddress("photons_theta", &photons_theta, &b_photons_theta);
  fChain->SetBranchAddress("Ntracks", &Ntracks, &b_Ntracks);
  fChain->SetBranchAddress("tracks_chi2", &tracks_chi2, &b_tracks_chi2);
  fChain->SetBranchAddress("tracks_ndof", &tracks_ndof, &b_tracks_ndof);
  fChain->SetBranchAddress("tracks_chg", &tracks_chg, &b_tracks_chg);
  fChain->SetBranchAddress("tracks_pt", &tracks_pt, &b_tracks_pt);
  fChain->SetBranchAddress("tracks_px", &tracks_px, &b_tracks_px);
  fChain->SetBranchAddress("tracks_py", &tracks_py, &b_tracks_py);
  fChain->SetBranchAddress("tracks_pz", &tracks_pz, &b_tracks_pz);
  fChain->SetBranchAddress("tracks_eta", &tracks_eta, &b_tracks_eta);
  fChain->SetBranchAddress("tracks_phi", &tracks_phi, &b_tracks_phi);
  fChain->SetBranchAddress("tracks_theta", &tracks_theta, &b_tracks_theta);
  fChain->SetBranchAddress("tracks_d0", &tracks_d0, &b_tracks_d0);
  fChain->SetBranchAddress("tracks_dz", &tracks_dz, &b_tracks_dz);
  fChain->SetBranchAddress("tracks_vx", &tracks_vx, &b_tracks_vx);
  fChain->SetBranchAddress("tracks_vy", &tracks_vy, &b_tracks_vy);
  fChain->SetBranchAddress("tracks_vz", &tracks_vz, &b_tracks_vz);
  fChain->SetBranchAddress("tracks_numvalhits", &tracks_numvalhits, &b_tracks_numvalhits);
  fChain->SetBranchAddress("tracks_numlosthits", &tracks_numlosthits, &b_tracks_numlosthits);
  fChain->SetBranchAddress("tracks_d0Err", &tracks_d0Err, &b_tracks_d0Err);
  fChain->SetBranchAddress("tracks_dzErr", &tracks_dzErr, &b_tracks_dzErr);
  fChain->SetBranchAddress("tracks_ptErr", &tracks_ptErr, &b_tracks_ptErr);
  fChain->SetBranchAddress("tracks_etaErr", &tracks_etaErr, &b_tracks_etaErr);
  fChain->SetBranchAddress("tracks_phiErr", &tracks_phiErr, &b_tracks_phiErr);
  fChain->SetBranchAddress("tracks_Nrechits", &tracks_Nrechits, &b_tracks_Nrechits);
  fChain->SetBranchAddress("tracks_innerHitX", &tracks_innerHitX, &b_tracks_innerHitX);
  fChain->SetBranchAddress("tracks_innerHitY", &tracks_innerHitY, &b_tracks_innerHitY);
  fChain->SetBranchAddress("tracks_innerHitZ", &tracks_innerHitZ, &b_tracks_innerHitZ);
  fChain->SetBranchAddress("tracks_outerHitX", &tracks_outerHitX, &b_tracks_outerHitX);
  fChain->SetBranchAddress("tracks_outerHitY", &tracks_outerHitY, &b_tracks_outerHitY);
  fChain->SetBranchAddress("tracks_outerHitZ", &tracks_outerHitZ, &b_tracks_outerHitZ);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);

  Notify();

}

Bool_t eventB::Notify()
{

  /* 
     The Notify() function is called when a new file is opened. This
     can be either for a new TTree in a TChain or when when a new TTree
     is started when using PROOF. It is normally not necessary to make changes
     to the generated code, but the routine can be extended by the
     user if needed. The return value is currently not used.
  */
  
  return kTRUE;

}

