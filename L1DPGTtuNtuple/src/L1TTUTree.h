//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb  3 05:02:07 2010 by ROOT version 5.22/00
// from TTree L1TTUTree/L1TTUTree
// found on file: histo-skim-data.root
//////////////////////////////////////////////////////////

#ifndef L1TTUTree_h
#define L1TTUTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <bitset>

#include <BasicOutput.h>

class L1TTUTree {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Int_t           Run;
  Int_t           Event;
  Int_t           Lumi;
  Int_t           HasRPCB;
  Int_t           HasDT;
  Int_t           MaxBits;
  Float_t         PacTTU[8];   //[MaxBits]
  Float_t         DtTTU[8];   //[MaxBits]
  Int_t           nRpcHits;
  Int_t           rpcHitBX[231];   //[nRpcHits]
  Int_t           rpcHitSt[231];   //[nRpcHits]
  Int_t           rpcHitWh[231];   //[nRpcHits]
  Int_t           rpcHitSe[231];   //[nRpcHits]
  Int_t           rpcHitLa[231];   //[nRpcHits]
  Float_t         rpcHitX[231];   //[nRpcHits]
  Float_t         rpcHitY[231];   //[nRpcHits]
  Float_t         rpcHitZ[231];   //[nRpcHits]
  
  // List of branches
  TBranch        *b_Run;   //!
  TBranch        *b_Event;   //!
  TBranch        *b_Lumi;   //!
  TBranch        *b_HasRPCB;   //!
  TBranch        *b_HasDT;    //!
  TBranch        *b_MaxBits;   //!
  TBranch        *b_PacTTU;   //!
  TBranch        *b_DtTTU;   //!
  TBranch        *b_nRpcHits;   //!
  TBranch        *b_rpcHitBX;   //!
  TBranch        *b_rpcHitSt;   //!
  TBranch        *b_rpcHitWh;   //!
  TBranch        *b_rpcHitSe;   //!
  TBranch        *b_rpcHitLa;   //!
  TBranch        *b_rpcHitX;   //!
  TBranch        *b_rpcHitY;   //!
  TBranch        *b_rpcHitZ;   //!
  

  L1TTUTree(TTree *tree, const char * option);
  virtual ~L1TTUTree();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(Long64_t maxevts);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  
  ////////////////////////////////

  void Initialize();

  std::string m_option;

  std::vector<int> m_ttbits;
  std::vector<int> m_singleMuBits;
  
  std::bitset<64>  TechBits[5];
  std::bitset<64> AlgBitsw1[5];
  std::bitset<64> AlgBitsw2[5];
  
  TFile * m_output;
  
  BasicOutput * m_histos;

  int m_totalevts;

  void makeStudyOne();

  void CheckConsistency(int);

  void Create(TTree *);

  
};

#endif

#ifdef L1TTUTree_cxx
L1TTUTree::L1TTUTree(TTree *tree, const char * option)
{
  
   Init(tree);
   m_option = std::string(option);
}

L1TTUTree::~L1TTUTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t L1TTUTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t L1TTUTree::LoadTree(Long64_t entry)
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

void L1TTUTree::Init(TTree *tree)
{

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("Run", &Run, &b_Run);
  fChain->SetBranchAddress("Event", &Event, &b_Event);
  fChain->SetBranchAddress("Lumi", &Lumi, &b_Lumi);
  fChain->SetBranchAddress("HasRPCB", &HasRPCB, &b_HasRPCB);
  fChain->SetBranchAddress("HasDT", &HasDT, &b_HasRPCB);
  fChain->SetBranchAddress("MaxBits", &MaxBits, &b_MaxBits);
  fChain->SetBranchAddress("PacTTU", PacTTU, &b_PacTTU);
  fChain->SetBranchAddress("DtTTU", DtTTU, &b_DtTTU);
  fChain->SetBranchAddress("nRpcHits", &nRpcHits, &b_nRpcHits);
  fChain->SetBranchAddress("rpcHitBX", rpcHitBX, &b_rpcHitBX);
  fChain->SetBranchAddress("rpcHitSt", rpcHitSt, &b_rpcHitSt);
  fChain->SetBranchAddress("rpcHitWh", rpcHitWh, &b_rpcHitWh);
  fChain->SetBranchAddress("rpcHitSe", rpcHitSe, &b_rpcHitSe);
  fChain->SetBranchAddress("rpcHitLa", rpcHitLa, &b_rpcHitLa);
  fChain->SetBranchAddress("rpcHitX", rpcHitX, &b_rpcHitX);
  fChain->SetBranchAddress("rpcHitY", rpcHitY, &b_rpcHitY);
  fChain->SetBranchAddress("rpcHitZ", rpcHitZ, &b_rpcHitZ);

  Notify();
}

Bool_t L1TTUTree::Notify()
{
  return kTRUE;
}

void L1TTUTree::Show(Long64_t entry)
{
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t L1TTUTree::Cut(Long64_t entry)
{
  return 1;
}
#endif // #ifdef L1TTUTree_cxx
