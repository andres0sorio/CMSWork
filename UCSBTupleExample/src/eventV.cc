// $Id: $
// Include files 

#include "eventV.h"

// local

//-----------------------------------------------------------------------------
// Implementation file for class : eventV
//
// 2008-10-25 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================

eventV::eventV( TFile * infile )
{
  
  infile->cd();
  infile->cd("configurableAnalysis");
  
  TTree * tree = (TTree*)gDirectory->Get("eventV");
  
  Init(tree);
  
}

eventV::eventV( TChain * inchain )
{
  
  TTree * tree = (TTree*)inchain;
  Init(tree);
  
}

//=============================================================================
// Destructor
//=============================================================================

eventV::~eventV()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

//=============================================================================
Int_t eventV::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t eventV::LoadTree(Long64_t entry)
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

void eventV::Init(TTree *tree)
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
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("CandHLT1METPre1", &CandHLT1METPre1, &b_CandHLT1METPre1);
  fChain->SetBranchAddress("CandHLT1METPre2", &CandHLT1METPre2, &b_CandHLT1METPre2);
  fChain->SetBranchAddress("CandHLT1METPre3", &CandHLT1METPre3, &b_CandHLT1METPre3);
  fChain->SetBranchAddress("CandHLT1MuonLevel1", &CandHLT1MuonLevel1, &b_CandHLT1MuonLevel1);
  fChain->SetBranchAddress("CandHLT1MuonPrescalePt3", &CandHLT1MuonPrescalePt3, &b_CandHLT1MuonPrescalePt3);
  fChain->SetBranchAddress("CandHLT1MuonPrescalePt5", &CandHLT1MuonPrescalePt5, &b_CandHLT1MuonPrescalePt5);
  fChain->SetBranchAddress("CandHLT1MuonPrescalePt7x10", &CandHLT1MuonPrescalePt7x10, &b_CandHLT1MuonPrescalePt7x10);
  fChain->SetBranchAddress("CandHLT1MuonPrescalePt7x7", &CandHLT1MuonPrescalePt7x7, &b_CandHLT1MuonPrescalePt7x7);
  fChain->SetBranchAddress("CandHLT1PhotonL1Isolated", &CandHLT1PhotonL1Isolated, &b_CandHLT1PhotonL1Isolated);
  fChain->SetBranchAddress("CandHLT1SumET", &CandHLT1SumET, &b_CandHLT1SumET);
  fChain->SetBranchAddress("CandHLT1jetPE7", &CandHLT1jetPE7, &b_CandHLT1jetPE7);
  fChain->SetBranchAddress("CandHLT2ElectronExclusive", &CandHLT2ElectronExclusive, &b_CandHLT2ElectronExclusive);
  fChain->SetBranchAddress("CandHLT2ElectronZCounter", &CandHLT2ElectronZCounter, &b_CandHLT2ElectronZCounter);
  fChain->SetBranchAddress("CandHLT2MuonIso", &CandHLT2MuonIso, &b_CandHLT2MuonIso);
  fChain->SetBranchAddress("CandHLT2PhotonExclusive", &CandHLT2PhotonExclusive, &b_CandHLT2PhotonExclusive);
  fChain->SetBranchAddress("CandHLT2jetAve110", &CandHLT2jetAve110, &b_CandHLT2jetAve110);
  fChain->SetBranchAddress("CandHLT2jetAve150", &CandHLT2jetAve150, &b_CandHLT2jetAve150);
  fChain->SetBranchAddress("CandHLT2jetAve200", &CandHLT2jetAve200, &b_CandHLT2jetAve200);
  fChain->SetBranchAddress("CandHLT2jetAve30", &CandHLT2jetAve30, &b_CandHLT2jetAve30);
  fChain->SetBranchAddress("CandHLT2jetAve60", &CandHLT2jetAve60, &b_CandHLT2jetAve60);
  fChain->SetBranchAddress("CandHLTHcalIsolatedTrack", &CandHLTHcalIsolatedTrack, &b_CandHLTHcalIsolatedTrack);
  fChain->SetBranchAddress("CandHLTJetMETRapidityGap", &CandHLTJetMETRapidityGap, &b_CandHLTJetMETRapidityGap);
  fChain->SetBranchAddress("CandHLTS2jetAco", &CandHLTS2jetAco, &b_CandHLTS2jetAco);
  fChain->SetBranchAddress("CandHLTSjet1MET1Aco", &CandHLTSjet1MET1Aco, &b_CandHLTSjet1MET1Aco);
  fChain->SetBranchAddress("CandHLTSjet2MET1Aco", &CandHLTSjet2MET1Aco, &b_CandHLTSjet2MET1Aco);
  fChain->SetBranchAddress("HLT1EMHighEt", &HLT1EMHighEt, &b_HLT1EMHighEt);
  fChain->SetBranchAddress("HLT1EMVeryHighEt", &HLT1EMVeryHighEt, &b_HLT1EMVeryHighEt);
  fChain->SetBranchAddress("HLT1Electron", &HLT1Electron, &b_HLT1Electron);
  fChain->SetBranchAddress("HLT1ElectronRelaxed", &HLT1ElectronRelaxed, &b_HLT1ElectronRelaxed);
  fChain->SetBranchAddress("HLT1MET", &HLT1MET, &b_HLT1MET);
  fChain->SetBranchAddress("HLT1MET1HT", &HLT1MET1HT, &b_HLT1MET1HT);
  fChain->SetBranchAddress("HLT1MuonIso", &HLT1MuonIso, &b_HLT1MuonIso);
  fChain->SetBranchAddress("HLT1MuonNonIso", &HLT1MuonNonIso, &b_HLT1MuonNonIso);
  fChain->SetBranchAddress("HLT1Photon", &HLT1Photon, &b_HLT1Photon);
  fChain->SetBranchAddress("HLT1PhotonRelaxed", &HLT1PhotonRelaxed, &b_HLT1PhotonRelaxed);
  fChain->SetBranchAddress("HLT1Tau", &HLT1Tau, &b_HLT1Tau);
  fChain->SetBranchAddress("HLT1Tau1MET", &HLT1Tau1MET, &b_HLT1Tau1MET);
  fChain->SetBranchAddress("HLT1jet", &HLT1jet, &b_HLT1jet);
  fChain->SetBranchAddress("HLT1jet1MET", &HLT1jet1MET, &b_HLT1jet1MET);
  fChain->SetBranchAddress("HLT1jet1METAco", &HLT1jet1METAco, &b_HLT1jet1METAco);
  fChain->SetBranchAddress("HLT1jetPE1", &HLT1jetPE1, &b_HLT1jetPE1);
  fChain->SetBranchAddress("HLT1jetPE3", &HLT1jetPE3, &b_HLT1jetPE3);
  fChain->SetBranchAddress("HLT1jetPE5", &HLT1jetPE5, &b_HLT1jetPE5);
  fChain->SetBranchAddress("HLT2Electron", &HLT2Electron, &b_HLT2Electron);
  fChain->SetBranchAddress("HLT2ElectronRelaxed", &HLT2ElectronRelaxed, &b_HLT2ElectronRelaxed);
  fChain->SetBranchAddress("HLT2MuonJPsi", &HLT2MuonJPsi, &b_HLT2MuonJPsi);
  fChain->SetBranchAddress("HLT2MuonNonIso", &HLT2MuonNonIso, &b_HLT2MuonNonIso);
  fChain->SetBranchAddress("HLT2MuonSameSign", &HLT2MuonSameSign, &b_HLT2MuonSameSign);
  fChain->SetBranchAddress("HLT2MuonUpsilon", &HLT2MuonUpsilon, &b_HLT2MuonUpsilon);
  fChain->SetBranchAddress("HLT2MuonZ", &HLT2MuonZ, &b_HLT2MuonZ);
  fChain->SetBranchAddress("HLT2Photon", &HLT2Photon, &b_HLT2Photon);
  fChain->SetBranchAddress("HLT2PhotonRelaxed", &HLT2PhotonRelaxed, &b_HLT2PhotonRelaxed);
  fChain->SetBranchAddress("HLT2TauPixel", &HLT2TauPixel, &b_HLT2TauPixel);
  fChain->SetBranchAddress("HLT2jet", &HLT2jet, &b_HLT2jet);
  fChain->SetBranchAddress("HLT2jet1MET", &HLT2jet1MET, &b_HLT2jet1MET);
  fChain->SetBranchAddress("HLT2jetAco", &HLT2jetAco, &b_HLT2jetAco);
  fChain->SetBranchAddress("HLT2jetvbfMET", &HLT2jetvbfMET, &b_HLT2jetvbfMET);
  fChain->SetBranchAddress("HLT3jet", &HLT3jet, &b_HLT3jet);
  fChain->SetBranchAddress("HLT3jet1MET", &HLT3jet1MET, &b_HLT3jet1MET);
  fChain->SetBranchAddress("HLT4jet", &HLT4jet, &b_HLT4jet);
  fChain->SetBranchAddress("HLT4jet1MET", &HLT4jet1MET, &b_HLT4jet1MET);
  fChain->SetBranchAddress("HLTB1Jet", &HLTB1Jet, &b_HLTB1Jet);
  fChain->SetBranchAddress("HLTB1JetMu", &HLTB1JetMu, &b_HLTB1JetMu);
  fChain->SetBranchAddress("HLTB2Jet", &HLTB2Jet, &b_HLTB2Jet);
  fChain->SetBranchAddress("HLTB2JetMu", &HLTB2JetMu, &b_HLTB2JetMu);
  fChain->SetBranchAddress("HLTB3Jet", &HLTB3Jet, &b_HLTB3Jet);
  fChain->SetBranchAddress("HLTB3JetMu", &HLTB3JetMu, &b_HLTB3JetMu);
  fChain->SetBranchAddress("HLTB4Jet", &HLTB4Jet, &b_HLTB4Jet);
  fChain->SetBranchAddress("HLTB4JetMu", &HLTB4JetMu, &b_HLTB4JetMu);
  fChain->SetBranchAddress("HLTBHT", &HLTBHT, &b_HLTBHT);
  fChain->SetBranchAddress("HLTBHTMu", &HLTBHTMu, &b_HLTBHTMu);
  fChain->SetBranchAddress("HLTBJPsiMuMu", &HLTBJPsiMuMu, &b_HLTBJPsiMuMu);
  fChain->SetBranchAddress("HLTMinBias", &HLTMinBias, &b_HLTMinBias);
  fChain->SetBranchAddress("HLTMinBiasPixel", &HLTMinBiasPixel, &b_HLTMinBiasPixel);
  fChain->SetBranchAddress("HLTNMuonNonIso", &HLTNMuonNonIso, &b_HLTNMuonNonIso);
  fChain->SetBranchAddress("HLTS2jet1METAco", &HLTS2jet1METAco, &b_HLTS2jet1METAco);
  fChain->SetBranchAddress("HLTS2jet1METNV", &HLTS2jet1METNV, &b_HLTS2jet1METNV);
  fChain->SetBranchAddress("HLTXElectron1Jet", &HLTXElectron1Jet, &b_HLTXElectron1Jet);
  fChain->SetBranchAddress("HLTXElectron2Jet", &HLTXElectron2Jet, &b_HLTXElectron2Jet);
  fChain->SetBranchAddress("HLTXElectron3Jet", &HLTXElectron3Jet, &b_HLTXElectron3Jet);
  fChain->SetBranchAddress("HLTXElectron4Jet", &HLTXElectron4Jet, &b_HLTXElectron4Jet);
  fChain->SetBranchAddress("HLTXElectronBJet", &HLTXElectronBJet, &b_HLTXElectronBJet);
  fChain->SetBranchAddress("HLTXElectronMuon", &HLTXElectronMuon, &b_HLTXElectronMuon);
  fChain->SetBranchAddress("HLTXElectronMuonRelaxed", &HLTXElectronMuonRelaxed, &b_HLTXElectronMuonRelaxed);
  fChain->SetBranchAddress("HLTXElectronTau", &HLTXElectronTau, &b_HLTXElectronTau);
  fChain->SetBranchAddress("HLTXMuonBJet", &HLTXMuonBJet, &b_HLTXMuonBJet);
  fChain->SetBranchAddress("HLTXMuonBJetSoftMuon", &HLTXMuonBJetSoftMuon, &b_HLTXMuonBJetSoftMuon);
  fChain->SetBranchAddress("HLTXMuonJets", &HLTXMuonJets, &b_HLTXMuonJets);
  fChain->SetBranchAddress("HLTXMuonTau", &HLTXMuonTau, &b_HLTXMuonTau);
  fChain->SetBranchAddress("HLTZeroBias", &HLTZeroBias, &b_HLTZeroBias);
  fChain->SetBranchAddress("csaWeight", &csaWeight, &b_csaWeight);
  fChain->SetBranchAddress("procIDSplit", &procIDSplit, &b_procIDSplit);
  
  Notify();
  
}

Bool_t eventV::Notify()
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

