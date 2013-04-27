#include "SUSYAnalyzers/UTAnalyzer/src/UTAnalyzer.h"

//Includes for PAT candidates


#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

UTAnalyzer::UTAnalyzer(const edm::ParameterSet& iConfig)
{
  
  m_muonSrc = iConfig.getUntrackedParameter<edm::InputTag>("muonSrc");
  m_jetSrc  = iConfig.getUntrackedParameter<edm::InputTag>("jetSrc" );
  m_metSrc  = iConfig.getUntrackedParameter<edm::InputTag>("metSrc" );
  
  
}

UTAnalyzer::~UTAnalyzer()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
}

//
// member functions
//

// ------------ method called to for each event  ------------
void
UTAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  /////////////////////////////////////////////////////////////////////////////////
  // 1. Jet collection
  edm::Handle<edm::View<pat::Jet> > jets;
  iEvent.getByLabel(m_jetSrc,jets);
  
  // 2. Muon collection
  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByLabel(m_muonSrc,muons);

  // 3. MET collection  
  edm::Handle<edm::View<pat::MET> > mets;
  iEvent.getByLabel(m_metSrc,mets);
  /////////////////////////////////////////////////////////////////////////////////

  //...Loop sobre Jets
  int nJets = 0;
  
  for(edm::View<pat::Jet>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
    if( jet->pt()>50.0 ) //seleccionamos solo jets con Pt > 50
      ++nJets;
  }
  
  h_1DHistContainer["Njets"]->Fill(nJets);
  
  //...Loop sobre Muones
  
  int nMuons = 0;
  
  for(edm::View<pat::Muon>::const_iterator muon=muons->begin(); muon!=muons->end(); ++muon){
    ++nMuons;
  }
  
  h_1DHistContainer["Nmuons"]->Fill(nMuons);
  
  //...MET
  
  if( ! mets->empty() ) {
    h_1DHistContainer["met"]->Fill( (*mets)[0].et() );
  }
  
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
UTAnalyzer::beginJob()
{
  
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;

  // book histograms:
  h_1DHistContainer["Nmuons"] = fs->make<TH1F>("Nmuons",   "muon multiplicity",     10, 0,  10);
  h_1DHistContainer["Njets" ] = fs->make<TH1F>("Njets",    "jet multiplicity",      10, 0,  10);
  h_1DHistContainer["met"   ] = fs->make<TH1F>("met",      "missing E_{T}",         20, 0, 100);
    
}

// ------------ method called once each job just after ending the event loop  ------------
void 
UTAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(UTAnalyzer);
