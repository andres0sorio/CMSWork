//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May 28 16:40:32 2012 by ROOT version 5.28/00
// from TTree t1/Real data root-tuple
// found on file: real_data_sample1.root
//////////////////////////////////////////////////////////

#ifndef DataAnalysis_h
#define DataAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>

#include <stdlib.h>
#include <iostream>


class DataAnalysis {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Int_t           nMuons;
  Float_t         muons_fPx[5];
  Float_t         muons_fPy[5];
  Float_t         muons_fPz[5];
  Float_t         muons_fE[5];
  Float_t         muons_fC[5];
  Float_t         muons_fEta[5];

  // List of branches
  TBranch        *b_nMuons;   //!
  TBranch        *b_muons_fPx;   //!
  TBranch        *b_muons_fPy;   //!
  TBranch        *b_muons_fPz;   //!
  TBranch        *b_muons_fE;   //!
  TBranch        *b_muons_fC;   //!
  TBranch        *b_muons_fEta;   //!

  DataAnalysis(const char *);
  virtual ~DataAnalysis();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

};

#endif

#ifdef DataAnalysis_cxx
DataAnalysis::DataAnalysis(const char * fname)
{

  // Cambiar el constructor - preferible que tome como argumento un nombre de archivo
  TTree * tree;
  TFile * f = TFile::Open(fname);
  
  if (!f) {
    std::cout << "Cannot open file: " << std::string(fname) << std::endl;
    exit(1);
  }
  
  tree = (TTree*)gDirectory->Get("t1");
  
  Init(tree);
  
}

DataAnalysis::~DataAnalysis()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t DataAnalysis::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t DataAnalysis::LoadTree(Long64_t entry)
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

void DataAnalysis::Init(TTree *tree)
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
  
  fChain->SetBranchAddress("nMuons", &nMuons, &b_nMuons);
  fChain->SetBranchAddress("muons_fPx", muons_fPx, &b_muons_fPx);
  fChain->SetBranchAddress("muons_fPy", muons_fPy, &b_muons_fPy);
  fChain->SetBranchAddress("muons_fPz", muons_fPz, &b_muons_fPz);
  fChain->SetBranchAddress("muons_fE", muons_fE, &b_muons_fE);
  fChain->SetBranchAddress("muons_fC", muons_fC, &b_muons_fC);
  fChain->SetBranchAddress("muons_fEta", muons_fEta, &b_muons_fEta);
  Notify();
  
}

Bool_t DataAnalysis::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void DataAnalysis::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t DataAnalysis::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef DataAnalysis_cxx
