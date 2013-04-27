// -*- C++ -*-
//
// Package:    ZMuMuAnalyzer
// Class:      ZMuMuAnalyzer
// 
/**\class ZMuMuAnalyzer ZMuMuAnalyzer.cc PATTutorial/ZMuMuAnalyzer/src/ZMuMuAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Sun Feb  8 19:50:51 CET 2009
// $Id$
//
//

#include "PATTutorial/ZMuMuAnalyzer/src/ZMuMuAnalyzer.h"
#include "DataFormats/Common/interface/OwnVector.h"
#include "DataFormats/PatCandidates/interface/TriggerPrimitive.h"


ZMuMuAnalyzer::ZMuMuAnalyzer(const edm::ParameterSet& iConfig)
  
{
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  m_hdeltaR  = fs->make<TH1D>("deltaR"  , "deltaR muons"  , 120 , 0 , 1.2 );
  m_hdeltaPt = fs->make<TH1D>("deltaPt" , "deltaPt muons" , 120 , 0 , 120 );
  m_hnmuons  = fs->make<TH1D>("nMuons" , "Number of Muons", 100 , 0 , 10  );
    
}


ZMuMuAnalyzer::~ZMuMuAnalyzer()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called to for each event  ------------
void ZMuMuAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  edm::Handle< edm::OwnVector<pat::TriggerPrimitive> > trigPrimHandle;
  iEvent.getByLabel("myTrigObjects",trigPrimHandle);
  
  std::cout << "ZMuMuAnalyzer::analyze> OwnVector: " << trigPrimHandle << std::endl;
  
  edm::Handle<std::vector<pat::Muon> > patHandle;
  iEvent.getByLabel("selectedLayer1Muons",patHandle);
  
  std::vector<pat::Muon>::const_iterator itr;
  
  int _nmuons(0);
  
  for(itr = patHandle->begin(); itr != patHandle->end(); itr++){
    
    reco::GenParticleRef ref= (*itr).genParticleRef();
    
    std::cout << (*itr).genParticlesSize() << '\n';
    
    if ( ! ref.isNull() ) {
      
      std::cout << "id: " << ref.id() << std::endl;
      
      double deltaR = std::sqrt( ( itr->eta() - ref->eta())*( itr->eta() - ref->eta()) 
                                 + ( itr->phi() - ref->phi())*(itr->phi() - ref->phi()) );
      
      std::cout << deltaR << std::endl;
      
      m_hdeltaR->Fill(deltaR);
      
    }
    
    ++_nmuons;
    
  }
  
  m_hnmuons->Fill(_nmuons);
  
  
}


// ------------ method called once each job just before starting event loop  ------------
void ZMuMuAnalyzer::beginJob(const edm::EventSetup&) {
  
}

// ------------ method called once each job just after ending the event loop  ------------
void ZMuMuAnalyzer::endJob() {
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZMuMuAnalyzer);
