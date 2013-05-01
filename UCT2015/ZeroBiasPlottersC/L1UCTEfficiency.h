//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 15 16:28:13 2012 by ROOT version 5.32/00
// from TTree Ntuple/Expression Ntuple
// found on file: ../uct_eff_trees_dielec.root
//////////////////////////////////////////////////////////

#ifndef L1UCTEfficiency_h
#define L1UCTEfficiency_h

#include <Histograms.h>
#include <L1RateTree.h>

class L1UCTEfficiency : public Histograms {
 public :
  
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  // L1 object

  Float_t         l1Pt;
  Float_t         l1Eta;
  Float_t         l1Phi;

  ULong64_t       evt;
  UInt_t          run;
  UInt_t          lumi;

  Float_t         l1Match;
  
  // Reco object

  Float_t         recoPt;
  Float_t         recoEta;
  Float_t         recoPhi;

  UInt_t          nRecoObjects;
  
  //...
  
  TBranch        *b_l1Pt;   //!
  TBranch        *b_l1Phi;   //!
  TBranch        *b_l1Eta;   //!

  TBranch        *b_evt;   //!
  TBranch        *b_run;   //!
  TBranch        *b_lumi;   //!

  TBranch        *b_l1Match;   //!

  TBranch        *b_recoPt;   //!
  TBranch        *b_recoEta;   //!
  TBranch        *b_recoPhi;   //!

  TBranch        *b_nRecoObjects;   //!

  L1UCTEfficiency(L1RateTree * t1, L1RateTree * t2, const char *infile);
  
  virtual ~L1UCTEfficiency();
  
  virtual void Loop(int, int );
  
 private:
  
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual Int_t    GetEntry(Long64_t entry);
  
  TFile * m_output;
  TTree * m_tree;
 
  L1RateTree * m_L1Tree;
  L1RateTree * m_RecoTree;
      
};

#endif

#ifdef L1UCTEfficiency_cxx

L1UCTEfficiency::L1UCTEfficiency( L1RateTree * t1, L1RateTree * t2, const char * outfile) : Histograms()
{

  m_L1Tree = t1;
  m_RecoTree = t2;
  
  m_output = new TFile(outfile,"RECREATE");
  m_output->cd();

  m_tree = new TTree("EfficiencyTree","Tree to work out the L1 efficiency");

  Init(m_tree);
  
}

L1UCTEfficiency::~L1UCTEfficiency()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
  
}

Int_t L1UCTEfficiency::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t L1UCTEfficiency::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void L1UCTEfficiency::Init(TTree *tree) 
{  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  //Create branches
    
  //L1

  fChain->Branch("l1Pt", &l1Pt, "l1Pt/f");
  fChain->Branch("l1Eta", &l1Eta, "l1Eta/f");
  fChain->Branch("l1Phi", &l1Phi, "l1Phi/f");

  fChain->Branch("evt",  &evt,  "evt/i");
  fChain->Branch("run",  &run,  "run/i");
  fChain->Branch("lumi", &lumi, "lumi/i");

  fChain->Branch("l1Match", &l1Match, "l1Match/f");
 
  //Reco

  fChain->Branch("recoPt", &recoPt, "recoPt/f");
  fChain->Branch("recoEta", &recoEta, "recoEta/f");
  fChain->Branch("recoPhi", &recoPhi, "recoPhi/f");

  fChain->Branch("nRecoObjects", &nRecoObjects, "nRecoObjects/i");

  Notify();
}

Bool_t L1UCTEfficiency::Notify() {
    
    return kTRUE;
  }

void L1UCTEfficiency::Show(Long64_t entry) {
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

#endif // #ifdef L1UCTEfficiency_cxx
