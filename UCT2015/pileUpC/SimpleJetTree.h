//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Dec 22 16:37:57 2012 by ROOT version 5.32/00
// from TTree Ntuple/Ntuple
// found on file: ../uct_rate_tree.root
//////////////////////////////////////////////////////////

#ifndef SimpleJetTree_h
#define SimpleJetTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <JetEvent.h>
#include <Histograms.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class SimpleJetTree : public Histograms {

 public :

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   
   std::vector<Region> * v_regions;
   
   std::vector<SimpleJet> * v_jets;

   std::vector<Region> * v_jet_regions;
   
   UInt_t          run;
   UInt_t          lumi;
   ULong64_t       evt;
   UInt_t          puM1;
   UInt_t          puM2;
   UInt_t          nPVs;
   Float_t         instLumi;

   int nReg;

   float jet_Et;
   int   jet_EtaPos;
   int   jet_PhiPos;

   float region_Et;
   int   region_EtaPos;
   int   region_PhiPos;

   TBranch        *b_v_regions;   //!
   TBranch        *b_v_jets;      //!
   TBranch        *b_v_jet_regions;   //!
   TBranch        *b_run;         //!
   TBranch        *b_lumi;  //!
   TBranch        *b_evt;   //!
   TBranch        *b_jet_nreg;
   TBranch        *b_puM1;
   TBranch        *b_puM2;
   TBranch        *b_nPVs;
   TBranch        *b_instLumi;
   
   SimpleJetTree(const char * infile, const char * path);
   
   virtual ~SimpleJetTree();
   
   virtual void     Loop();

 private:
   
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Show(Long64_t entry = -1);

};

#endif

#ifdef SimpleJetTree_cxx

SimpleJetTree::SimpleJetTree(const char * infile, const char * path ) : Histograms()
{
  
  TTree *tree;
  
  TFile * f1 = TFile::Open(infile);
  
  if( !f1 ) {
    std::cout << "Cannot open file: " << std::string() << std::endl;
    exit(1);
  }
  
  tree = (TTree*)gDirectory->Get(path);
  
  std::cout << " t " << tree << std::endl;

  v_jets = new std::vector<SimpleJet>;

  v_jet_regions = new std::vector<Region>;

  v_regions = new std::vector<Region>;
  
  Init(tree);
 
}

SimpleJetTree::~SimpleJetTree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t SimpleJetTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t SimpleJetTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
  }
  return centry;
}

void SimpleJetTree::Init(TTree *tree)
{
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("evt", &evt, &b_evt);
  fChain->SetBranchAddress("puM1", &puM1, &b_puM1);
  fChain->SetBranchAddress("puM2", &puM2, &b_puM2);
  fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
  fChain->SetBranchAddress("instlumi", &instLumi, &b_instLumi);

  fChain->SetBranchAddress("regions", &v_regions, &b_v_regions);

  fChain->SetBranchAddress("jets", &v_jets, &b_v_jets);
  fChain->SetBranchAddress("jets.v_Regions", &v_jet_regions, &b_v_jet_regions);
  fChain->SetBranchAddress("jets.n_Reg", &nReg, &b_jet_nreg);

}

void SimpleJetTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}


#endif // #ifdef SimpleJetTree_cxx
