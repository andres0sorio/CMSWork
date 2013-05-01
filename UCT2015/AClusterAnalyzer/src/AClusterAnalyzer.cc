// -*- C++ -*-
//
// Package:    AClusterAnalyzer
// Class:      AClusterAnalyzer
// 
/**\class AClusterAnalyzer AClusterAnalyzer.cc UserCode/AClusterAnalyzer/src/AClusterAnalyzer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Andres Oliveros
//         Created:  Wed Mar 20 13:14:30 CDT 2013
// $Id: AClusterAnalyzer.cc,v 1.1 2013/04/23 16:00:29 aosorio Exp $
//
//

// system include files
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <TTree.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"


// L1 Trigger Stuff/ UCT2015

#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"

#include "CondFormats/L1TObjects/interface/L1CaloEcalScale.h"
#include "CondFormats/DataRecord/interface/L1CaloEcalScaleRcd.h"

#include "L1Trigger/UCT2015/interface/UCTCandidate.h"
#include "L1Trigger/UCT2015/interface/helpers.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


//
// class declaration
//

class AClusterAnalyzer : public edm::EDAnalyzer {
public:
  explicit AClusterAnalyzer(const edm::ParameterSet&);
  ~AClusterAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  static const unsigned int N_TOWER_PHI;
  static const unsigned int N_TOWER_ETA;

  // Concrete collection of output objects (with extra tuning information)
  typedef std::vector<UCTCandidate> UCTCandidateCollection;
  typedef std::auto_ptr<UCTCandidateCollection> UCTCandidateCollectionPtr;
  

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  void makeEClusters();

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  // ----------member data ---------------------------
  
  bool debug;
  
  unsigned int eClusterSeed;
  double eLSB_;

  std::vector<edm::InputTag> ecalDigis;

  std::vector<std::vector <unsigned int> > eTowerETCode;
  std::vector<std::vector <bool> > eTowerFGVeto;
  
  L1CaloRegionCollection eRegionList;
  
  ///AO - march 20 2013
  std::map<std::string,TH1F*> m_1dhistos;
  std::map<std::string,TH2F*> m_2dhistos;
  
};


//
// constants, enums and typedefs
//

//
// static data member definitions
//
unsigned int const AClusterAnalyzer::N_TOWER_PHI = 72;
unsigned int const AClusterAnalyzer::N_TOWER_ETA = 56;

//
// constructors and destructor
//
AClusterAnalyzer::AClusterAnalyzer(const edm::ParameterSet& iConfig) :
  debug(iConfig.getParameter<bool>("debug")),
  eClusterSeed(iConfig.getParameter<unsigned int>("eClusterSeed")),
  eLSB_(iConfig.getParameter<double>("ecalLSB")),
  ecalDigis(iConfig.getParameter<std::vector<edm::InputTag> >("ecalDigis")),
  eTowerETCode(N_TOWER_PHI, std::vector<unsigned int>(N_TOWER_ETA)),
  eTowerFGVeto(N_TOWER_PHI, std::vector<bool>(N_TOWER_ETA))
{

  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  m_1dhistos["nclusters"] = fs->make<TH1F>("nclusters", "N clusters",50,0,100);
  m_1dhistos["nclustersCd2"] = fs->make<TH1F>("nclustersCd2", "N clusters",50,0,100);
  m_2dhistos["clustetaphi"] = fs->make<TH2F>("clustetaphi", "Cluster eta/phi",50,-3.0, 3.0, 50, -10, 10);
  m_2dhistos["clustetaphiCd2"] = fs->make<TH2F>("clustetaphiCd2", "Cluster eta/phi",50,-3.0, 3.0, 50, -10, 10);
}


AClusterAnalyzer::~AClusterAnalyzer()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called for each event  ------------
void
AClusterAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  UCTCandidateCollectionPtr unpackedEClusters(new UCTCandidateCollection);
  
  std::auto_ptr<L1CaloRegionCollection> ERegions (new L1CaloRegionCollection);

  edm::Handle<EcalTrigPrimDigiCollection> ecal;
  
  iEvent.getByLabel(ecalDigis[0], ecal);
  
  EcalTrigPrimDigiCollection ecalCollection;
  
  if (ecal.isValid()) { ecalCollection = *ecal;}
  else {return;}
  
  unsigned int nEcalDigi = ecalCollection.size();
  
  if (nEcalDigi>4032) {nEcalDigi=4032;}
  
  for (unsigned int i = 0; i < nEcalDigi; i++){
    int ieta = ecalCollection[i].id().ieta();
    // Note TPG absIeta counts from 1-28 (not 0-27)
    int cal_iphi = ecalCollection[i].id().iphi();
    unsigned int iEta;
    // So here, -28 becomes 0.  -1 be comes 27.  +1 becomes 28. +28 becomes 55.
    // And we have mapped [-28, -1], [1, 28] onto [0, 55]
    if(ieta < 0)
      iEta = ieta + 28;
    else if(ieta > 0)
      iEta = ieta + 27;
    else {
      std::cout << "AClusterAnalyzer: Illegal value for ecalCollection->id().ieta() -- should never be zero!" << std::endl;
      return;
    }
    
    // TPG iPhi starts at 1 and goes to 72.  Let's index starting at zero.
    unsigned int iPhi = (cal_iphi-1);
    eTowerETCode[iPhi][iEta] = ecalCollection[i].compressedEt()*eLSB_;
    eTowerFGVeto[iPhi][iEta] = (bool) ecalCollection[i].fineGrain();     // 0 or 1
  }
  
  
  makeEClusters();
  
  
}

void AClusterAnalyzer::makeEClusters() {
  
  float ncluster = 0.0;
  float nclusterCd2 = 0.0;
  
  for(unsigned int iPhi = 0; iPhi < N_TOWER_PHI; iPhi++) {
    for(unsigned int iEta = 0; iEta < N_TOWER_ETA; iEta++) {
      if(eTowerETCode[iPhi][iEta] > eClusterSeed) {

	unsigned int center_et = eTowerETCode[iPhi][iEta];
	unsigned int neighborN_et = 0;
	unsigned int neighborS_et = 0;
	unsigned int neighborE_et = 0;
	unsigned int neighborW_et = 0;
	unsigned int neighborNE_et = 0;
	unsigned int neighborNW_et = 0;
	unsigned int neighborSE_et = 0;
	unsigned int neighborSW_et = 0;
	unsigned int N;
	unsigned int S;
	
	if(iPhi > 0 && iPhi < (N_TOWER_PHI - 1)) {
	  N = iPhi + 1;
	  S = iPhi - 1;
	}
	else if(iPhi == (N_TOWER_PHI - 1)) {
	  N = 0;
	  S = iPhi - 1;
	}
	else if(iPhi == 0) {
	  N = iPhi + 1;
	  S = N_TOWER_PHI - 1;
	}
	if(iEta == 0) {
	  unsigned int E = iEta + 1;
	  neighborN_et = eTowerETCode[N][iEta];
	  neighborS_et = eTowerETCode[S][iEta];
	  neighborE_et = eTowerETCode[iPhi][E];
	  neighborNE_et = eTowerETCode[N][E];
	  neighborSE_et = eTowerETCode[S][E];
	}
	else if(iEta == N_TOWER_ETA - 1) {
	  unsigned int W = iEta - 1;
	  neighborN_et = eTowerETCode[N][iEta];
	  neighborS_et = eTowerETCode[S][iEta];
	  neighborW_et = eTowerETCode[iPhi][W];
	  neighborNW_et = eTowerETCode[N][W];
	  neighborSW_et = eTowerETCode[S][W];
	}
	else {
	  unsigned int E = iEta + 1;
	  unsigned int W = iEta - 1;
	  neighborN_et = eTowerETCode[N][iEta];
	  neighborS_et = eTowerETCode[S][iEta];
	  neighborE_et = eTowerETCode[iPhi][E];
	  neighborW_et = eTowerETCode[iPhi][W];
	  neighborNE_et = eTowerETCode[N][E];
	  neighborNW_et = eTowerETCode[N][W];
	  neighborSE_et = eTowerETCode[S][E];
	  neighborSW_et = eTowerETCode[S][W];
	}
	
	bool defaultCondition = center_et > neighborN_et &&
	  center_et > neighborNW_et &&
	  center_et > neighborW_et &&
	  center_et > neighborSW_et &&
	  center_et >= neighborNE_et &&
	  center_et >= neighborE_et &&
	  center_et >= neighborSE_et &&
	  center_et >= neighborS_et;

	double realPhi = convertTPGPhi(iPhi);
	double realEta = convertTPGEta(iEta);

	if(defaultCondition) {
	  
	  unsigned int eClusterET = center_et +
	    neighborN_et + neighborS_et + neighborE_et + neighborW_et +
	    neighborNE_et + neighborSW_et + neighborSE_et + neighborNW_et;
	  // Temporarily use the tower (iPhi, iEta) -- todo: convert to half-tower resolution
          double realEt = eClusterET;
          double stripEt = center_et + neighborS_et + neighborN_et;
          
          UCTCandidate theCluster(realEt, realEta, realPhi);
          theCluster.setInt("twrPhi", iPhi);
          theCluster.setInt("twrEta", iEta);
          theCluster.setFloat("emClusterCenterEt", center_et);
          theCluster.setFloat("emClusterStripEt", stripEt);
          theCluster.setInt("rgnPhi", twrPhi2RegionPhi(iPhi));
          theCluster.setInt("rgnEta", twrEta2RegionEta(iEta));
	  ncluster += 1.0;
	  m_2dhistos["clustetaphi"]->Fill( realEta, realPhi);
	}
	
	bool modifiedCondition = (center_et >= neighborN_et) ||
	  ( center_et >= neighborW_et ) ||
	  ( center_et >= neighborE_et ) ||
	  ( center_et >= neighborS_et );
	
	if(modifiedCondition) {
	  nclusterCd2 += 1.0;
	  m_2dhistos["clustetaphiCd2"]->Fill( realEta, realPhi);
	}
	
      }
    }
  }
  
  m_1dhistos["nclusters"]->Fill( ncluster );
  m_1dhistos["nclustersCd2"]->Fill( nclusterCd2 );
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
AClusterAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AClusterAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
AClusterAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
AClusterAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
AClusterAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
AClusterAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
AClusterAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(AClusterAnalyzer);
