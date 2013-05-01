/*
 * =====================================================================================
 *
 *       Filename:  PileUpTreeExtra.cc
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
#include "DataFormats/Scalers/interface/LumiScalers.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "TTree.h"

#include "UserCode/JetEventDataformat/src/JetEvent.h"

typedef std::vector<edm::InputTag> VInputTag;

class PileUpTreeExtra : public edm::EDAnalyzer {
  
public:
  
  PileUpTreeExtra(const edm::ParameterSet& pset);
  virtual ~PileUpTreeExtra();
  void analyze(const edm::Event& evt, const edm::EventSetup& es);
  
private:
  
  VInputTag src_;
  TTree* tree;
  
  UInt_t run_;
  UInt_t lumi_;
  ULong64_t event_;
  Int_t puM1;
  Int_t puM2;
  Float_t instLumi_;
  Int_t nPVs;

  bool m_puCorrect;
  bool m_srcIsReco;
  double m_regionLSB;
  unsigned int m_jetSeed;
  unsigned int m_puETMax;
  edm::InputTag scalerSrc_;
  edm::InputTag pvSrc_;

  std::vector<Region> * v_regions;
  std::vector<SimpleJet> * v_jets;
  
  void puSubtraction( const edm::Event& );

  double regionPhysicalEt(const L1CaloRegion& cand) {
    return m_regionLSB*cand.et();
  };
  
  int deltaPhi18(int phi1, int phi2) {
    // Compute the difference in phi between two towers, wrapping at phi = 18
    int difference = phi1 - phi2;
    if (std::abs(phi1 - phi2) == 17) {
      difference = -difference/std::abs(difference);
    }
    return difference;
  };
  
  int deltaGctPhi(const L1CaloRegion& r1, const L1CaloRegion& r2) {
    return deltaPhi18(r1.gctPhi(), r2.gctPhi());
  };
    

};

PileUpTreeExtra::PileUpTreeExtra(const edm::ParameterSet& iConfig) {

  
  m_puCorrect = iConfig.getParameter<bool>("puCorrect");
  m_puETMax = iConfig.getParameter<unsigned int>("puETMax");
  m_jetSeed = iConfig.getParameter<unsigned int>("jetSeed");
  m_regionLSB = iConfig.getParameter<double>("regionLSB");
  m_srcIsReco = iConfig.getParameter<bool>("srcIsReco");

  scalerSrc_ = iConfig.exists("scalerSrc") ?
    iConfig.getParameter<edm::InputTag>("scalerSrc") : edm::InputTag("scalersRawToDigi");

  pvSrc_ = iConfig.exists("pvSrc") ? 
    iConfig.getParameter<edm::InputTag>("pvSrc") : edm::InputTag("offlinePrimaryVertices");
  
  // Initialize the ntuple builder
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("Ntuple", "Ntuple");
  
  v_jets = new std::vector<SimpleJet>; //JetEventCollection;

  v_regions = new std::vector<Region>;

  tree->Branch("jets","std::vector<SimpleJet>", &v_jets);
  tree->Branch("regions","std::vector<Region>", &v_regions);
  
  tree->Branch("run", &run_, "run/i");
  tree->Branch("lumi", &lumi_, "lumi/i");
  tree->Branch("evt", &event_, "evt/l");
  tree->Branch("instlumi", &instLumi_, "instlumi/F");
  tree->Branch("puM1", &puM1, "puM1/i");
  tree->Branch("puM2", &run_, "puM2/i");
  tree->Branch("nPVs", &nPVs, "nPVs/i");

}

PileUpTreeExtra::~PileUpTreeExtra() {
  //delete l1et_;
}

void PileUpTreeExtra::analyze(const edm::Event& evt, const edm::EventSetup& es) {

  // Setup meta info
  run_ = evt.id().run();
  lumi_ = evt.id().luminosityBlock();
  event_ = evt.id().event();

  // Get instantaneous lumi from the scalers
  // thx to Carlo Battilana

  edm::Handle<LumiScalersCollection> lumiScalers;
  evt.getByLabel(scalerSrc_, lumiScalers);
  assert(lumiScalers->size());
  instLumi_ = lumiScalers->begin()->instantLumi();

  if( m_srcIsReco ) {
    
    edm::Handle<reco::VertexCollection> vertices;
    evt.getByLabel(pvSrc_, vertices);
    nPVs = vertices->size();
  } else
    nPVs = 0;
  
  puSubtraction( evt );

  // Get the trigger tower energies and store them in the tree (the double
  // copy is used to sort them in rapidity)
  edm::Handle<L1CaloRegionCollection> newRegions;
  
  evt.getByLabel("uctDigis", newRegions);
  
  std::vector<unsigned int> gctEnergy;
  
  gctEnergy.clear();
  
  gctEnergy.reserve(396);
  
  for(L1CaloRegionCollection::const_iterator newRegion = newRegions->begin(); newRegion != newRegions->end(); newRegion++) {

    gctEnergy[18*newRegion->gctEta()+newRegion->gctPhi()] = newRegion->et();

    double regionET = regionPhysicalEt(*newRegion);

    if(regionET > m_jetSeed) {

      SimpleJet * jetCandidate = new SimpleJet();

      double neighborN_et = 0;
      double neighborS_et = 0;
      double neighborE_et = 0;
      double neighborW_et = 0;
      double neighborNE_et = 0;
      double neighborSW_et = 0;
      double neighborNW_et = 0;
      double neighborSE_et = 0;
      unsigned int nNeighbors = 0;
      
      //std::cout << "Looking for seed @ " << newRegion->gctPhi() << " " << newRegion->gctEta() << std::endl;
      
      for(L1CaloRegionCollection::const_iterator neighbor = newRegions->begin(); neighbor != newRegions->end(); neighbor++) {
	
	double neighborET = regionPhysicalEt(*neighbor);
	
	if(deltaGctPhi(*newRegion, *neighbor) == 1 &&  (newRegion->gctEta() ) == neighbor->gctEta()) {
	  neighborN_et = neighborET;
          nNeighbors++;
	  jetCandidate->AddRegion( neighborET, neighbor->gctEta(), neighbor->gctPhi() );
          //debug("N", *newRegion, *neighbor);
	  continue;
	}
	else if(deltaGctPhi(*newRegion, *neighbor) == -1 &&
		(newRegion->gctEta()    ) == neighbor->gctEta()) {
	  neighborS_et = neighborET;
          nNeighbors++;
	  jetCandidate->AddRegion( neighborET, neighbor->gctEta(), neighbor->gctPhi() );
          //debug("S", *newRegion, *neighbor);
	  continue;
	}
	else if(deltaGctPhi(*newRegion, *neighbor) == 0 &&
		(newRegion->gctEta() + 1) == neighbor->gctEta()) {
	  neighborE_et = neighborET;
          nNeighbors++;
	  jetCandidate->AddRegion( neighborET, neighbor->gctEta(), neighbor->gctPhi() );
          //debug("E", *newRegion, *neighbor);
	  continue;
	}
	else if(deltaGctPhi(*newRegion, *neighbor) == 0 &&
		(newRegion->gctEta() - 1) == neighbor->gctEta()) {
	  neighborW_et = neighborET;
          nNeighbors++;
	  jetCandidate->AddRegion( neighborET, neighbor->gctEta(), neighbor->gctPhi() );
          //debug("W", *newRegion, *neighbor);
	  continue;
	}
	else if(deltaGctPhi(*newRegion, *neighbor) == 1 &&
		(newRegion->gctEta() + 1) == neighbor->gctEta()) {
	  neighborNE_et = neighborET;
          nNeighbors++;
	  jetCandidate->AddRegion( neighborET, neighbor->gctEta(), neighbor->gctPhi() );
          //debug("NE", *newRegion, *neighbor);
	  continue;
	}
	else if(deltaGctPhi(*newRegion, *neighbor) == -1 &&
		(newRegion->gctEta() - 1) == neighbor->gctEta()) {
	  neighborSW_et = neighborET;
          nNeighbors++;
	  jetCandidate->AddRegion( neighborET, neighbor->gctEta(), neighbor->gctPhi() );
          //bug("SW", *newRegion, *neighbor);
	  continue;
	}
	else if(deltaGctPhi(*newRegion, *neighbor) == 1 &&
		(newRegion->gctEta() - 1) == neighbor->gctEta()) {
	  neighborNW_et = neighborET;
          nNeighbors++;
	  jetCandidate->AddRegion( neighborET, neighbor->gctEta(), neighbor->gctPhi() );
          //debug("NW", *newRegion, *neighbor);
	  continue;
	}
	else if(deltaGctPhi(*newRegion, *neighbor) == -1 &&
		(newRegion->gctEta() + 1) == neighbor->gctEta()) {
	  neighborSE_et = neighborET;
          nNeighbors++;
	  jetCandidate->AddRegion( neighborET, neighbor->gctEta(), neighbor->gctPhi() );
          //debug("SE", *newRegion, *neighbor);
	  continue;
	}
      }
      if(regionET > neighborN_et &&
	 regionET > neighborNW_et &&
	 regionET > neighborW_et &&
	 regionET > neighborSW_et &&
	 regionET >= neighborNE_et &&
	 regionET >= neighborE_et &&
	 regionET >= neighborSE_et &&
	 regionET >= neighborS_et) {
	
	unsigned int jetET = regionET +
	  neighborN_et + neighborS_et + neighborE_et + neighborW_et +
	  neighborNE_et + neighborSW_et + neighborSE_et + neighborNW_et;
	
	// Temporarily use the region granularity -- we will try to improve as above when code is debugged
	int jetPhi = newRegion->gctPhi();
	int jetEta = newRegion->gctEta();
	
        bool neighborCheck = (nNeighbors == 8);
        // On the eta edge we only expect 5 neighbors
        
	if (!neighborCheck && (jetEta == 0 || jetEta == 21) && nNeighbors == 5)
          neighborCheck = true;
	
        if (!neighborCheck) {
          std::cout << " Et: " << jetET << " phi: " << jetPhi << " eta: " << jetEta << " n: " << nNeighbors << std::endl;
          assert(false);
        }
	
	///Here I want to replace with a JetEvent class so I can have a better look at Jets
	
	jetCandidate->m_Seed.Initialize( jetET, jetEta, jetPhi );
	
	jetCandidate->n_Reg = nNeighbors;

	v_jets->push_back( (*jetCandidate) );
	
      }
    }
  }
  
  tree->Fill();

  v_jets->clear();
  
  v_regions->clear();


}

void PileUpTreeExtra::puSubtraction( const edm::Event& iEvent )
{
  
  edm::Handle<L1CaloRegionCollection> newRegions;
  iEvent.getByLabel("uctDigis", newRegions);
  
  puM1 = 0;
  puM2 = 0;
  
  int puCount = 0;

  for(L1CaloRegionCollection::const_iterator newRegion = newRegions->begin(); newRegion != newRegions->end(); newRegion++) {

    Region * region = new Region();

    double regionEt = newRegion->et();
    double regionPhysEt = regionPhysicalEt(*newRegion);

    region->Initialize( regionEt, regionPhysEt, newRegion->gctEta(), newRegion->gctPhi() );

    v_regions->push_back( (*region) );
    
    if(regionPhysicalEt(*newRegion) <= m_puETMax) {
      puM1 += newRegion->et(); puCount++;
    }

  }
  
  // Add a factor of 9, so it corresponds to a jet.  Reduces roundoff error.
  puM1 *= 9;
  // std::cout << puM1 << " : " << puCount << " : " << puM1/puCount << std::endl;
  puM1 = puM1 / puCount;
  
}


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(PileUpTreeExtra);
