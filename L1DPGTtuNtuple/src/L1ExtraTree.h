//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb  1 22:44:17 2010 by ROOT version 5.22/00
// from TTree L1ExtraTree/L1ExtraTree
// found on file: L1DPG-All.root
//////////////////////////////////////////////////////////

#ifndef L1ExtraTree_h
#define L1ExtraTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class L1ExtraTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           nIsoEm;
   Double_t        isoEmEt[4];   //[nIsoEm]
   Double_t        isoEmEta[4];   //[nIsoEm]
   Double_t        isoEmPhi[4];   //[nIsoEm]
   Int_t           nNonIsoEm;
   Double_t        nonIsoEmEt[2];   //[nNonIsoEm]
   Double_t        nonIsoEmEta[2];   //[nNonIsoEm]
   Double_t        nonIsoEmPhi[2];   //[nNonIsoEm]
   Int_t           nCenJets;
   Double_t        cenJetEt[2];   //[nCenJets]
   Double_t        cenJetEta[2];   //[nCenJets]
   Double_t        cenJetPhi[2];   //[nCenJets]
   Int_t           nTauJets;
   Double_t        tauJetEt[4];   //[nTauJets]
   Double_t        tauJetEta[4];   //[nTauJets]
   Double_t        tauJetPhi[4];   //[nTauJets]
   Int_t           nFwdJets;
   Double_t        fwdJetEt[4];   //[nFwdJets]
   Double_t        fwdJetEta[4];   //[nFwdJets]
   Double_t        fwdJetPhi[4];   //[nFwdJets]
   Int_t           nMuons;
   Double_t        muonEt[4];   //[nMuons]
   Double_t        muonEta[4];   //[nMuons]
   Double_t        muonPhi[4];   //[nMuons]
   Int_t           muonChg[4];   //[nMuons]
   Int_t           muonIso[4];   //[nMuons]
   Int_t           muonMip[4];   //[nMuons]
   Int_t           muonFwd[4];   //[nMuons]
   Int_t           muonRPC[4];   //[nMuons]
   Double_t        hfEtSum[4];
   Int_t           hfBitCnt[4];
   Double_t        met;
   Double_t        metPhi;
   Double_t        et;
   Double_t        mht;
   Double_t        mhtPhi;
   Double_t        ht;

   // List of branches
   TBranch        *b_nIsoEm;   //!
   TBranch        *b_isoEmEt;   //!
   TBranch        *b_isoEmEta;   //!
   TBranch        *b_isoEmPhi;   //!
   TBranch        *b_nNonIsoEm;   //!
   TBranch        *b_nonIsoEmEt;   //!
   TBranch        *b_nonIsoEmEta;   //!
   TBranch        *b_nonIsoEmPhi;   //!
   TBranch        *b_nCenJets;   //!
   TBranch        *b_cenJetEt;   //!
   TBranch        *b_cenJetEta;   //!
   TBranch        *b_cenJetPhi;   //!
   TBranch        *b_nTauJets;   //!
   TBranch        *b_tauJetEt;   //!
   TBranch        *b_tauJetEta;   //!
   TBranch        *b_tauJetPhi;   //!
   TBranch        *b_nFwdJets;   //!
   TBranch        *b_fwdJetEt;   //!
   TBranch        *b_fwdJetEta;   //!
   TBranch        *b_fwdJetPhi;   //!
   TBranch        *b_nMuons;   //!
   TBranch        *b_muonEt;   //!
   TBranch        *b_muonEta;   //!
   TBranch        *b_muonPhi;   //!
   TBranch        *b_muonChg;   //!
   TBranch        *b_muonIso;   //!
   TBranch        *b_muonMip;   //!
   TBranch        *b_muonFwd;   //!
   TBranch        *b_muonRPC;   //!
   TBranch        *b_hfEtSum;   //!
   TBranch        *b_hfBitCnt;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metPhi;   //!
   TBranch        *b_et;   //!
   TBranch        *b_mht;   //!
   TBranch        *b_mhtPhi;   //!
   TBranch        *b_ht;   //!

  L1ExtraTree(TTree *tree, const char * option );
  virtual ~L1ExtraTree();
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

#ifdef L1ExtraTree_cxx
L1ExtraTree::L1ExtraTree(TTree *tree, const char * option)
{
  
  Init(tree);
  m_option = std::string(option);
  
}

L1ExtraTree::~L1ExtraTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t L1ExtraTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t L1ExtraTree::LoadTree(Long64_t entry)
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

void L1ExtraTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("nIsoEm", &nIsoEm, &b_nIsoEm);
   fChain->SetBranchAddress("isoEmEt", isoEmEt, &b_isoEmEt);
   fChain->SetBranchAddress("isoEmEta", isoEmEta, &b_isoEmEta);
   fChain->SetBranchAddress("isoEmPhi", isoEmPhi, &b_isoEmPhi);
   fChain->SetBranchAddress("nNonIsoEm", &nNonIsoEm, &b_nNonIsoEm);
   fChain->SetBranchAddress("nonIsoEmEt", nonIsoEmEt, &b_nonIsoEmEt);
   fChain->SetBranchAddress("nonIsoEmEta", nonIsoEmEta, &b_nonIsoEmEta);
   fChain->SetBranchAddress("nonIsoEmPhi", nonIsoEmPhi, &b_nonIsoEmPhi);
   fChain->SetBranchAddress("nCenJets", &nCenJets, &b_nCenJets);
   fChain->SetBranchAddress("cenJetEt", cenJetEt, &b_cenJetEt);
   fChain->SetBranchAddress("cenJetEta", cenJetEta, &b_cenJetEta);
   fChain->SetBranchAddress("cenJetPhi", cenJetPhi, &b_cenJetPhi);
   fChain->SetBranchAddress("nTauJets", &nTauJets, &b_nTauJets);
   fChain->SetBranchAddress("tauJetEt", tauJetEt, &b_tauJetEt);
   fChain->SetBranchAddress("tauJetEta", tauJetEta, &b_tauJetEta);
   fChain->SetBranchAddress("tauJetPhi", tauJetPhi, &b_tauJetPhi);
   fChain->SetBranchAddress("nFwdJets", &nFwdJets, &b_nFwdJets);
   fChain->SetBranchAddress("fwdJetEt", fwdJetEt, &b_fwdJetEt);
   fChain->SetBranchAddress("fwdJetEta", fwdJetEta, &b_fwdJetEta);
   fChain->SetBranchAddress("fwdJetPhi", fwdJetPhi, &b_fwdJetPhi);
   fChain->SetBranchAddress("nMuons", &nMuons, &b_nMuons);
   fChain->SetBranchAddress("muonEt", muonEt, &b_muonEt);
   fChain->SetBranchAddress("muonEta", muonEta, &b_muonEta);
   fChain->SetBranchAddress("muonPhi", muonPhi, &b_muonPhi);
   fChain->SetBranchAddress("muonChg", muonChg, &b_muonChg);
   fChain->SetBranchAddress("muonIso", muonIso, &b_muonIso);
   fChain->SetBranchAddress("muonMip", muonMip, &b_muonMip);
   fChain->SetBranchAddress("muonFwd", muonFwd, &b_muonFwd);
   fChain->SetBranchAddress("muonRPC", muonRPC, &b_muonRPC);
   fChain->SetBranchAddress("hfEtSum", hfEtSum, &b_hfEtSum);
   fChain->SetBranchAddress("hfBitCnt", hfBitCnt, &b_hfBitCnt);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
   fChain->SetBranchAddress("et", &et, &b_et);
   fChain->SetBranchAddress("mht", &mht, &b_mht);
   fChain->SetBranchAddress("mhtPhi", &mhtPhi, &b_mhtPhi);
   fChain->SetBranchAddress("ht", &ht, &b_ht);
   Notify();
}

Bool_t L1ExtraTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void L1ExtraTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t L1ExtraTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef L1ExtraTree_cxx
