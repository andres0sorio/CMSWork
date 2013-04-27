// -*- C++ -*-
//
// Package:    PATTechTrigg
// Class:      PATTechTrigg
// 
/**\class PATTechTrigg PATTechTrigg.cc MyPATExamples/PATTechTrigg/src/PATTechTrigg.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Felipe Osorio Oliveros,512 1-009,+41227670491,
//         Created:  Fri Jun 11 02:00:00 CEST 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include <DataFormats/Common/interface/RefVector.h>

//
// class declaration
//

class PATTechTrigg : public edm::EDAnalyzer {

public:
  explicit PATTechTrigg(const edm::ParameterSet&);
  ~PATTechTrigg();
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  TH1D * histo; 


  unsigned int m_l1techBit;
  std::string m_l1techBitname;
  edm::InputTag triggerEvent_;
  
};

//
//.............................................................................
//

PATTechTrigg::PATTechTrigg(const edm::ParameterSet& iConfig)

{

  triggerEvent_ = iConfig.getParameter< edm::InputTag >( "triggerEvent" );
  
  m_l1techBit = iConfig.getParameter< unsigned int > ( "l1techBit" );
  
  m_l1techBitname = iConfig.getParameter< std::string > ( "l1techBitName" );
 
}


PATTechTrigg::~PATTechTrigg()
{
 

}

// ------------ method called to for each event  ------------
void
PATTechTrigg::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // PAT trigger information
  edm::Handle< pat::TriggerEvent > triggerEvent;
  
  iEvent.getByLabel( triggerEvent_, triggerEvent );
  
  pat::TriggerAlgorithmRefVector techBits = (*triggerEvent).techAlgorithms();

  pat::TriggerAlgorithmRefVector::const_iterator itrBit = techBits.begin();
  
  int nbit = 0;
  
  while ( itrBit != techBits.end()) {
    
    //std::cout << "looping over techBits: " << nbit << '\t' 
    //          << (*itrBit)->bit() << '\t' 
    //          << (*itrBit)->name() << '\t'
    //          << (*itrBit)->decision() << '\t'
    //          << (*itrBit)->decisionBeforeMask() << '\t'
    //          << (*itrBit)->decisionAfterMask() << '\t'
    //          << '\n';
    
    if ( (*itrBit)->decision() ) 
      histo->Fill( (*itrBit)->bit() );
    
    if ( m_l1techBitname.compare( (*itrBit)->name() ) == 0 )
      std::cout << "looping over techBits: " << nbit << '\t' 
                << (*itrBit)->bit() << '\t' 
                << (*itrBit)->name() << '\t'
                << (*itrBit)->decision() << '\t'
                << (*itrBit)->decisionBeforeMask() << '\t'
                << (*itrBit)->decisionAfterMask() << '\t'
                << '\n';
    
    itrBit++;
    nbit++;

    
    
  }
  




}


// ------------ method called once each job just before starting event loop  ------------
void 
PATTechTrigg::beginJob()
{
  
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  histo = fs->make<TH1D>("TechTriggers" , "Technical triggers" ,65 , 0 , 64 );
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PATTechTrigg::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(PATTechTrigg);
