// -*- C++ -*-
//
// Package:    StudyMCResolution
// Class:      StudyMCResolution
// 
/**\class StudyMCResolution StudyMCResolution.cc UserCode/StudyMCResolution/src/StudyMCResolution.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Oliveros
//         Created:  Fri Feb  8 10:46:06 CST 2013
// $Id: StudyMCResolution.cc,v 1.2 2013/02/26 20:08:48 aosorio Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


//...GenParticle
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include <map>

//...ROOT and File servies

#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//
// class declaration
//

class StudyMCResolution : public edm::EDAnalyzer {
public:
  explicit StudyMCResolution(const edm::ParameterSet&);
  ~StudyMCResolution();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  // ----------member data ---------------------------

  int m_genPdgId;
  edm::InputTag m_partLabel;
  edm::InputTag m_genpartLabel;
  
  std::map<std::string,TH1F*> h_histograms1D;

  bool m_debug;

};


StudyMCResolution::StudyMCResolution(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
 
  m_genPdgId = iConfig.getParameter<int>("genPdgId");
  m_partLabel = iConfig.getParameter<edm::InputTag>("partLabel");
  m_genpartLabel = iConfig.getParameter<edm::InputTag>("genpartLabel");
  
  m_debug = true;

 edm::Service<TFileService> fs; 
  
 h_histograms1D["genPt"] = fs->make<TH1F>("Pt","Pt of generated particle",50,0,200);
 h_histograms1D["genVisiblePt"] = fs->make<TH1F>("VisiblePt","Pt of generated particle",50,0,200);

}


StudyMCResolution::~StudyMCResolution()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.) 
  
}


//
// member functions
//

// ------------ method called for each event  ------------
void
StudyMCResolution::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  unsigned int ieventX = iEvent.id().event();
  std::cout << " @Event: " << ieventX << std::endl;
  
  edm::Handle<edm::HepMCProduct> genParticles;
  iEvent.getByLabel(m_partLabel, genParticles);

  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(genParticles->GetEvent()));

  
  for(HepMC::GenEvent::particle_iterator partIt = myGenEvent->particles_begin();
      partIt != myGenEvent->particles_end(); ++partIt ){
   
    int mcpartId = (*partIt)->pdg_id();
    
    bool foundMCpart = false;
   
    if( ( abs(mcpartId) == m_genPdgId ))  {
     
      double mmc_gen = (*partIt)->generated_mass();
      double ptrans = (*partIt)->momentum().perp();
      double etamc = (*partIt)->momentum().eta();
      double phimc = (*partIt)->momentum().phi();
      
      
      std::cout << " found: " << mmc_gen << " status " << (*partIt)->status() << " " << ptrans << " " << etamc << " " << phimc << std::endl;
      
    } 
    
  }
  
  
  edm::Handle<reco::GenParticleCollection> genParticlesColl;
  iEvent.getByLabel(m_genpartLabel, genParticlesColl);
  
  for(size_t i = 0; i < genParticlesColl->size(); ++ i) {
    
    const reco::GenParticle & p = (*genParticlesColl)[i];
    
    int id = p.pdgId();
    int st = p.status();  

    if( ( abs(id) == m_genPdgId ) && ( st == 2 ) )  {
      
    const reco::Candidate * mom = p.mother();
    double pt = p.pt(), eta = p.eta(), phi = p.phi(), mass = p.mass();
    double vx = p.vx(), vy = p.vy(), vz = p.vz();
    int charge = p.charge();
    int n = p.numberOfDaughters();

    h_histograms1D["genPt"]->Fill( pt );

    double ptSum = 0.0;
    
    for(int j = 0; j < n; ++ j) {
      
      const reco::Candidate * d = p.daughter( j );
      int dauId = d->pdgId();
      
      std::cout << j << " dauId for Tau: " << id << " is " << dauId << std::endl;
          


      if ( abs( dauId ) != 12 || abs( dauId ) != 14  || abs( dauId ) != 16 ) { 
	
	ptSum += d->pt();
	
      }
      
    }
    
    h_histograms1D["genVisiblePt"]->Fill( ptSum );
    
    }
    
  }
    
}


// ------------ method called once each job just before starting event loop  ------------
void 
StudyMCResolution::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
StudyMCResolution::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
StudyMCResolution::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
StudyMCResolution::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
StudyMCResolution::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
StudyMCResolution::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
StudyMCResolution::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(StudyMCResolution);
