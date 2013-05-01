/*
 * =====================================================================================
 *
 *       Filename:  PileUpTree.cc
 *
 *    Description:  Produce a tree for studying the pileup subtraction on L1 calo trigger
 *
 *         Author:  Marco Verzocchi, mverzocc@fnal.gov
 *        Company:  Fermilab
 *
 * =====================================================================================
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"

#include "TTree.h"

typedef std::vector<edm::InputTag> VInputTag;

class PileUpTree : public edm::EDAnalyzer {
  public:
    PileUpTree(const edm::ParameterSet& pset);
    virtual ~PileUpTree();
    void analyze(const edm::Event& evt, const edm::EventSetup& es);
  private:
    VInputTag src_;
    TTree* tree;
    UInt_t run_;
    UInt_t lumi_;
    ULong64_t event_;
    std::vector<Int_t>* l1et_;

};

PileUpTree::PileUpTree(const edm::ParameterSet& pset) {
  // Initialize the ntuple builder
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("Ntuple", "Ntuple");
  tree->Branch("run", &run_, "run/i");
  tree->Branch("lumi", &lumi_, "lumi/i");
  tree->Branch("evt", &event_, "evt/l");
  l1et_ = new std::vector<Int_t>();
  tree->Branch("l1et", "std::vector<int>", &l1et_);
}

PileUpTree::~PileUpTree() {
  delete l1et_;
}

void PileUpTree::analyze(const edm::Event& evt, const edm::EventSetup& es) {

  // Setup meta info
  run_ = evt.id().run();
  lumi_ = evt.id().luminosityBlock();
  event_ = evt.id().event();

  // Get the trigger tower energies and store them in the tree (the double
  // copy is used to sort them in rapidity)
  edm::Handle<L1CaloRegionCollection> newRegions;
  evt.getByLabel("uctDigis", newRegions);
  std::vector<unsigned int> gctEnergy;
  gctEnergy.clear();
  gctEnergy.reserve(396);
  for(L1CaloRegionCollection::const_iterator newRegion = newRegions->begin(); newRegion != newRegions->end(); newRegion++){
    gctEnergy[18*newRegion->gctEta()+newRegion->gctPhi()] = newRegion->et();
  }
  l1et_->clear();
  l1et_->reserve(396);
  for ( int i=0; i!=396; ++i ) {
    l1et_->push_back(gctEnergy[i]);
  }

  tree->Fill();
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(PileUpTree);
