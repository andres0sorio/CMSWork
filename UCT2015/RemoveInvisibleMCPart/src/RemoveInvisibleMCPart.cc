// -*- C++ -*-
//
// Package:    RemoveInvisibleMCPart
// Class:      RemoveInvisibleMCPart
// 
/**\class RemoveInvisibleMCPart RemoveInvisibleMCPart.cc UserCode/RemoveInvisibleMCPart/src/RemoveInvisibleMCPart.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Oliveros
//         Created:  Sat Feb  9 13:06:41 CST 2013
// $Id: RemoveInvisibleMCPart.cc,v 1.2 2013/02/26 20:07:56 aosorio Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

//...GenParticle
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Point3D.h"

#include "RecoTauTag/TauTagTools/interface/GeneratorTau.h"

#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>

//
// class declaration
//
typedef math::XYZTLorentzVector LorentzVector;

class RemoveInvisibleMCPart : public edm::EDProducer {

public:
  explicit RemoveInvisibleMCPart(const edm::ParameterSet&);
  ~RemoveInvisibleMCPart();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run&, edm::EventSetup const&);
  virtual void endRun(edm::Run&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
  
  // ----------member data ---------------------------
  
  edm::InputTag m_simLabel;
  
  int m_genPdgId;


};

RemoveInvisibleMCPart::RemoveInvisibleMCPart(const edm::ParameterSet& iConfig)
{

  m_simLabel = iConfig.getParameter<edm::InputTag>("simLabel");
  m_genPdgId = iConfig.getParameter<int>("genPdgId");
  produces<reco::GenParticleCollection>();
  
}


RemoveInvisibleMCPart::~RemoveInvisibleMCPart()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


// ------------ method called to produce the data  ------------

void
RemoveInvisibleMCPart::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  
  edm::Handle<reco::GenParticleCollection> genParticlesColl;
  iEvent.getByLabel(m_simLabel, genParticlesColl);

  std::vector<const reco::GenParticle*> modTaus;
  
  std::auto_ptr<reco::GenParticleCollection> target( new reco::GenParticleCollection );

  for(size_t i = 0; i < genParticlesColl->size(); ++ i) {
    
    const reco::GenParticle & p = (*genParticlesColl)[i];
    
    int id = p.pdgId();
    int st = p.status();  

    if( ( abs(id) == m_genPdgId ) && ( st == 2 ) )  {
       
      int n = p.numberOfDaughters();
      
      double ptSum = 0.0;
      
      //math::XYZTLorentzVector invisibleP4;
      LorentzVector invisibleP4;
      
      for(int j = 0; j < n; ++ j) {
	
	const reco::Candidate * d = p.daughter( j );
	int dauId = d->pdgId();
	
	if ( abs( dauId ) == 12 || abs( dauId ) == 14  || abs( dauId ) == 16 ) { 
	  
	  ptSum += d->pt();
	  invisibleP4 += d->p4();
		  
	}
      
      }
    
      //Save new Candidate having the invisible momentum removed
            
      GeneratorTau * genTau = new GeneratorTau( );
      int decayMode = genTau->computeDecayMode( &p ); //... Using the official tool
      delete genTau;
      
      reco::GenParticle* tau = p.clone();
      tau->setP4( p.p4() - invisibleP4 );
      tau->setStatus ( decayMode ); //... this is a hack - otherwise I would need to run the GeneratorTau Producer 
      
      std::cout << " original " << p.pt() << " new " << tau->pt() << " " << decayMode << " : " << tau->status() << std::endl;
      
      target->push_back( *tau );
      
    }
    
  }
  
  //get ref product from the event
  //const reco::GenParticleRefProd ref = iEvent.getRefBeforePut<reco::GenParticleCollection>(); 
  std::cout << " saving candidates" << std::endl;

  iEvent.put(target);

}

// ------------ method called once each job just before starting event loop  ------------
void 
RemoveInvisibleMCPart::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RemoveInvisibleMCPart::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
RemoveInvisibleMCPart::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
RemoveInvisibleMCPart::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
RemoveInvisibleMCPart::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
RemoveInvisibleMCPart::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RemoveInvisibleMCPart::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RemoveInvisibleMCPart);
