#ifndef eventV_h
#define eventV_h

#include "CommonIncludes.h"
#include <TChain.h>
#include <TFile.h>


//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Dec 19 15:49:11 2008 by ROOT version 5.20/00
// from TTree eventV/VariableNTuple tree
// found on file: MuonChowderNtupleCombined1.root
//////////////////////////////////////////////////////////
//
// Class modified by Andres Osorio: aosorio@uniandes.edu.co
//
//////////////////////////////////////////////////////////

class eventV {
public :

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Double_t        CandHLT1METPre1;
  Double_t        CandHLT1METPre2;
  Double_t        CandHLT1METPre3;
  Double_t        CandHLT1MuonLevel1;
  Double_t        CandHLT1MuonPrescalePt3;
  Double_t        CandHLT1MuonPrescalePt5;
  Double_t        CandHLT1MuonPrescalePt7x10;
  Double_t        CandHLT1MuonPrescalePt7x7;
  Double_t        CandHLT1PhotonL1Isolated;
  Double_t        CandHLT1SumET;
  Double_t        CandHLT1jetPE7;
  Double_t        CandHLT2ElectronExclusive;
  Double_t        CandHLT2ElectronZCounter;
  Double_t        CandHLT2MuonIso;
  Double_t        CandHLT2PhotonExclusive;
  Double_t        CandHLT2jetAve110;
  Double_t        CandHLT2jetAve150;
  Double_t        CandHLT2jetAve200;
  Double_t        CandHLT2jetAve30;
  Double_t        CandHLT2jetAve60;
  Double_t        CandHLTHcalIsolatedTrack;
  Double_t        CandHLTJetMETRapidityGap;
  Double_t        CandHLTS2jetAco;
  Double_t        CandHLTSjet1MET1Aco;
  Double_t        CandHLTSjet2MET1Aco;
  Double_t        HLT1EMHighEt;
  Double_t        HLT1EMVeryHighEt;
  Double_t        HLT1Electron;
  Double_t        HLT1ElectronRelaxed;
  Double_t        HLT1MET;
  Double_t        HLT1MET1HT;
  Double_t        HLT1MuonIso;
  Double_t        HLT1MuonNonIso;
  Double_t        HLT1Photon;
  Double_t        HLT1PhotonRelaxed;
  Double_t        HLT1Tau;
  Double_t        HLT1Tau1MET;
  Double_t        HLT1jet;
  Double_t        HLT1jet1MET;
  Double_t        HLT1jet1METAco;
  Double_t        HLT1jetPE1;
  Double_t        HLT1jetPE3;
  Double_t        HLT1jetPE5;
  Double_t        HLT2Electron;
  Double_t        HLT2ElectronRelaxed;
  Double_t        HLT2MuonJPsi;
  Double_t        HLT2MuonNonIso;
  Double_t        HLT2MuonSameSign;
  Double_t        HLT2MuonUpsilon;
  Double_t        HLT2MuonZ;
  Double_t        HLT2Photon;
  Double_t        HLT2PhotonRelaxed;
  Double_t        HLT2TauPixel;
  Double_t        HLT2jet;
  Double_t        HLT2jet1MET;
  Double_t        HLT2jetAco;
  Double_t        HLT2jetvbfMET;
  Double_t        HLT3jet;
  Double_t        HLT3jet1MET;
  Double_t        HLT4jet;
  Double_t        HLT4jet1MET;
  Double_t        HLTB1Jet;
  Double_t        HLTB1JetMu;
  Double_t        HLTB2Jet;
  Double_t        HLTB2JetMu;
  Double_t        HLTB3Jet;
  Double_t        HLTB3JetMu;
  Double_t        HLTB4Jet;
  Double_t        HLTB4JetMu;
  Double_t        HLTBHT;
  Double_t        HLTBHTMu;
  Double_t        HLTBJPsiMuMu;
  Double_t        HLTMinBias;
  Double_t        HLTMinBiasPixel;
  Double_t        HLTNMuonNonIso;
  Double_t        HLTS2jet1METAco;
  Double_t        HLTS2jet1METNV;
  Double_t        HLTXElectron1Jet;
  Double_t        HLTXElectron2Jet;
  Double_t        HLTXElectron3Jet;
  Double_t        HLTXElectron4Jet;
  Double_t        HLTXElectronBJet;
  Double_t        HLTXElectronMuon;
  Double_t        HLTXElectronMuonRelaxed;
  Double_t        HLTXElectronTau;
  Double_t        HLTXMuonBJet;
  Double_t        HLTXMuonBJetSoftMuon;
  Double_t        HLTXMuonJets;
  Double_t        HLTXMuonTau;
  Double_t        HLTZeroBias;
  Double_t        csaWeight;
  Double_t        procIDSplit;
  
  // List of branches
  TBranch        *b_CandHLT1METPre1;   
  TBranch        *b_CandHLT1METPre2;   
  TBranch        *b_CandHLT1METPre3;   
  TBranch        *b_CandHLT1MuonLevel1;   
  TBranch        *b_CandHLT1MuonPrescalePt3;   
  TBranch        *b_CandHLT1MuonPrescalePt5;   
  TBranch        *b_CandHLT1MuonPrescalePt7x10;   
  TBranch        *b_CandHLT1MuonPrescalePt7x7;   
  TBranch        *b_CandHLT1PhotonL1Isolated;   
  TBranch        *b_CandHLT1SumET;   
  TBranch        *b_CandHLT1jetPE7;   
  TBranch        *b_CandHLT2ElectronExclusive;   
  TBranch        *b_CandHLT2ElectronZCounter;   
  TBranch        *b_CandHLT2MuonIso;   
  TBranch        *b_CandHLT2PhotonExclusive;   
  TBranch        *b_CandHLT2jetAve110;   
  TBranch        *b_CandHLT2jetAve150;   
  TBranch        *b_CandHLT2jetAve200;   
  TBranch        *b_CandHLT2jetAve30;   
  TBranch        *b_CandHLT2jetAve60;   
  TBranch        *b_CandHLTHcalIsolatedTrack;   
  TBranch        *b_CandHLTJetMETRapidityGap;   
  TBranch        *b_CandHLTS2jetAco;   
  TBranch        *b_CandHLTSjet1MET1Aco;   
  TBranch        *b_CandHLTSjet2MET1Aco;   
  TBranch        *b_HLT1EMHighEt;   
  TBranch        *b_HLT1EMVeryHighEt;   
  TBranch        *b_HLT1Electron;   
  TBranch        *b_HLT1ElectronRelaxed;   
  TBranch        *b_HLT1MET;   
  TBranch        *b_HLT1MET1HT;   
  TBranch        *b_HLT1MuonIso;   
  TBranch        *b_HLT1MuonNonIso;   
  TBranch        *b_HLT1Photon;   
  TBranch        *b_HLT1PhotonRelaxed;   
  TBranch        *b_HLT1Tau;   
  TBranch        *b_HLT1Tau1MET;   
  TBranch        *b_HLT1jet;   
  TBranch        *b_HLT1jet1MET;   
  TBranch        *b_HLT1jet1METAco;   
  TBranch        *b_HLT1jetPE1;   
  TBranch        *b_HLT1jetPE3;   
  TBranch        *b_HLT1jetPE5;   
  TBranch        *b_HLT2Electron;   
  TBranch        *b_HLT2ElectronRelaxed;   
  TBranch        *b_HLT2MuonJPsi;   
  TBranch        *b_HLT2MuonNonIso;   
  TBranch        *b_HLT2MuonSameSign;   
  TBranch        *b_HLT2MuonUpsilon;   
  TBranch        *b_HLT2MuonZ;   
  TBranch        *b_HLT2Photon;   
  TBranch        *b_HLT2PhotonRelaxed;   
  TBranch        *b_HLT2TauPixel;   
  TBranch        *b_HLT2jet;   
  TBranch        *b_HLT2jet1MET;   
  TBranch        *b_HLT2jetAco;   
  TBranch        *b_HLT2jetvbfMET;   
  TBranch        *b_HLT3jet;   
  TBranch        *b_HLT3jet1MET;   
  TBranch        *b_HLT4jet;   
  TBranch        *b_HLT4jet1MET;   
  TBranch        *b_HLTB1Jet;   
  TBranch        *b_HLTB1JetMu;   
  TBranch        *b_HLTB2Jet;   
  TBranch        *b_HLTB2JetMu;   
  TBranch        *b_HLTB3Jet;   
  TBranch        *b_HLTB3JetMu;   
  TBranch        *b_HLTB4Jet;   
  TBranch        *b_HLTB4JetMu;   
  TBranch        *b_HLTBHT;   
  TBranch        *b_HLTBHTMu;   
  TBranch        *b_HLTBJPsiMuMu;   
  TBranch        *b_HLTMinBias;   
  TBranch        *b_HLTMinBiasPixel;   
  TBranch        *b_HLTNMuonNonIso;   
  TBranch        *b_HLTS2jet1METAco;   
  TBranch        *b_HLTS2jet1METNV;   
  TBranch        *b_HLTXElectron1Jet;   
  TBranch        *b_HLTXElectron2Jet;   
  TBranch        *b_HLTXElectron3Jet;   
  TBranch        *b_HLTXElectron4Jet;   
  TBranch        *b_HLTXElectronBJet;   
  TBranch        *b_HLTXElectronMuon;   
  TBranch        *b_HLTXElectronMuonRelaxed;   
  TBranch        *b_HLTXElectronTau;   
  TBranch        *b_HLTXMuonBJet;   
  TBranch        *b_HLTXMuonBJetSoftMuon;   
  TBranch        *b_HLTXMuonJets;   
  TBranch        *b_HLTXMuonTau;   
  TBranch        *b_HLTZeroBias;   
  TBranch        *b_csaWeight;   
  TBranch        *b_procIDSplit;

  eventV() {};
  
  eventV( TFile  * );
  
  eventV( TChain * );

  ~eventV();
  
  Int_t    GetEntry(Long64_t entry);
  Long64_t LoadTree(Long64_t entry);
  
private:
  
  void     Init(TTree *tree);
  Bool_t   Notify();
  
};
#endif

