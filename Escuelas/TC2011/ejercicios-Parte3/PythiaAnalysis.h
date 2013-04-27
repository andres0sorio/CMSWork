//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 13 17:20:51 2011 by ROOT version 5.27/04
// from TTree tree/Arbol con particulas segun Pythia8
// found on file: eventos_pythia8.root
//////////////////////////////////////////////////////////

#ifndef PythiaAnalysis_h
#define PythiaAnalysis_h

#include "RootCommon.h"

#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TParticle.h>
#include <TObjArray.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TDatabasePDG.h>

const Int_t kMaxparticles = 5000;

class PythiaAnalysis {

public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Int_t           particles_;
  UInt_t          particles_fUniqueID[kMaxparticles];   //[particles_]
  UInt_t          particles_fBits[kMaxparticles];   //[particles_]
  Short_t         particles_fLineColor[kMaxparticles];   //[particles_]
  Short_t         particles_fLineStyle[kMaxparticles];   //[particles_]
  Short_t         particles_fLineWidth[kMaxparticles];   //[particles_]
  Int_t           particles_fPdgCode[kMaxparticles];   //[particles_]
  Int_t           particles_fStatusCode[kMaxparticles];   //[particles_]
  Int_t           particles_fMother[kMaxparticles][2];   //[particles_]
  Int_t           particles_fDaughter[kMaxparticles][2];   //[particles_]
  Float_t         particles_fWeight[kMaxparticles];   //[particles_]
  Double_t        particles_fCalcMass[kMaxparticles];   //[particles_]
  Double_t        particles_fPx[kMaxparticles];   //[particles_]
  Double_t        particles_fPy[kMaxparticles];   //[particles_]
  Double_t        particles_fPz[kMaxparticles];   //[particles_]
  Double_t        particles_fE[kMaxparticles];   //[particles_]
  Double_t        particles_fVx[kMaxparticles];   //[particles_]
  Double_t        particles_fVy[kMaxparticles];   //[particles_]
  Double_t        particles_fVz[kMaxparticles];   //[particles_]
  Double_t        particles_fVt[kMaxparticles];   //[particles_]
  Double_t        particles_fPolarTheta[kMaxparticles];   //[particles_]
  Double_t        particles_fPolarPhi[kMaxparticles];   //[particles_]
  
  // List of branches
  TBranch        *b_particles_;   //!
  TBranch        *b_particles_fUniqueID;   //!
  TBranch        *b_particles_fBits;   //!
  TBranch        *b_particles_fLineColor;   //!
  TBranch        *b_particles_fLineStyle;   //!
  TBranch        *b_particles_fLineWidth;   //!
  TBranch        *b_particles_fPdgCode;   //!
  TBranch        *b_particles_fStatusCode;   //!
  TBranch        *b_particles_fMother;   //!
  TBranch        *b_particles_fDaughter;   //!
  TBranch        *b_particles_fWeight;   //!
  TBranch        *b_particles_fCalcMass;   //!
  TBranch        *b_particles_fPx;   //!
  TBranch        *b_particles_fPy;   //!
  TBranch        *b_particles_fPz;   //!
  TBranch        *b_particles_fE;   //!
  TBranch        *b_particles_fVx;   //!
  TBranch        *b_particles_fVy;   //!
  TBranch        *b_particles_fVz;   //!
  TBranch        *b_particles_fVt;   //!
  TBranch        *b_particles_fPolarTheta;   //!
  TBranch        *b_particles_fPolarPhi;   //!
  
  PythiaAnalysis(const char * fname );
  
  virtual ~PythiaAnalysis();

  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  
};

#endif

#ifdef PythiaAnalysis_cxx

PythiaAnalysis::PythiaAnalysis(const char * fname)
{
  
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  
  TTree * tree;
  TFile * f = TFile::Open(fname);
  
  if (!f) {
    std::cout << "Cannot open file: " << std::string(fname) << std::endl;
    exit(1);
  }
  
  tree = (TTree*)gDirectory->Get("tree");
  
  Init(tree);
  
}

PythiaAnalysis::~PythiaAnalysis()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

//Int_t PythiaAnalysis::GetMotherId( int index ) 
Int_t PythiaAnalysis::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t PythiaAnalysis::LoadTree(Long64_t entry)
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

void PythiaAnalysis::Init(TTree *tree)
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
  
  fChain->SetBranchAddress("particles", &particles_, &b_particles_);
  fChain->SetBranchAddress("particles.fUniqueID", particles_fUniqueID, &b_particles_fUniqueID);
  fChain->SetBranchAddress("particles.fBits", particles_fBits, &b_particles_fBits);
  fChain->SetBranchAddress("particles.fLineColor", particles_fLineColor, &b_particles_fLineColor);
  fChain->SetBranchAddress("particles.fLineStyle", particles_fLineStyle, &b_particles_fLineStyle);
  fChain->SetBranchAddress("particles.fLineWidth", particles_fLineWidth, &b_particles_fLineWidth);
  fChain->SetBranchAddress("particles.fPdgCode", particles_fPdgCode, &b_particles_fPdgCode);
  fChain->SetBranchAddress("particles.fStatusCode", particles_fStatusCode, &b_particles_fStatusCode);
  fChain->SetBranchAddress("particles.fMother[2]", particles_fMother, &b_particles_fMother);
  fChain->SetBranchAddress("particles.fDaughter[2]", particles_fDaughter, &b_particles_fDaughter);
  fChain->SetBranchAddress("particles.fWeight", particles_fWeight, &b_particles_fWeight);
  fChain->SetBranchAddress("particles.fCalcMass", particles_fCalcMass, &b_particles_fCalcMass);
  fChain->SetBranchAddress("particles.fPx", particles_fPx, &b_particles_fPx);
  fChain->SetBranchAddress("particles.fPy", particles_fPy, &b_particles_fPy);
  fChain->SetBranchAddress("particles.fPz", particles_fPz, &b_particles_fPz);
  fChain->SetBranchAddress("particles.fE", particles_fE, &b_particles_fE);
  fChain->SetBranchAddress("particles.fVx", particles_fVx, &b_particles_fVx);
  fChain->SetBranchAddress("particles.fVy", particles_fVy, &b_particles_fVy);
  fChain->SetBranchAddress("particles.fVz", particles_fVz, &b_particles_fVz);
  fChain->SetBranchAddress("particles.fVt", particles_fVt, &b_particles_fVt);
  fChain->SetBranchAddress("particles.fPolarTheta", particles_fPolarTheta, &b_particles_fPolarTheta);
  fChain->SetBranchAddress("particles.fPolarPhi", particles_fPolarPhi, &b_particles_fPolarPhi);
  Notify();

}

Bool_t PythiaAnalysis::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

void PythiaAnalysis::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t PythiaAnalysis::Cut(Long64_t entry)
{
  
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  std::cout << entry << std::endl;
  return 1;

}
#endif // #ifdef PythiaAnalysis_cxx
