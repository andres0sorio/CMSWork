// -*- C++ -*-
//
// Package:    JetsAnalyzer
// Class:      JetsAnalyzer
// 
/**\class JetsAnalyzer JetsAnalyzer.cc PATTutorial/JetsAnalyzer/src/JetsAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Sat Jan 31 15:39:08 CET 2009
// $Id$
//
//
#include "PATTutorial/JetsAnalyzer/src/JetsAnalyzer.h"

#include "PhysicsTools/Utilities/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Flags.h"


JetsAnalyzer::JetsAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  edm::Service<TFileService> fs;

  //* Number of jets above 10 Gev
  //* Energy of the closest electron
  //* Energy of the closest electron over energy of the jet
  //* Electromagnetic fraction of the jets
  //* Track isolation of the closest electron 
  
  njets          = fs->make<TH1D>("NJets"   , "Number of jets" , 100 , 0 , 50 ); //x
  njetscut       = fs->make<TH1D>("NJetsAfterCut"   , "Number of jets above 10 Gev" , 100 , 0 , 50 ); //x
  nelectrons     = fs->make<TH1D>("NElectrons" , "Number of electrons in jet" , 100 , 0 , 50 ); //x

  eclosestEl     = fs->make<TH1D>("EclosEl" , "Energy of the closest electron" , 100 , 0 , 300 ); //x

  eclosertEloJet = fs->make<TH1D>("EclosEJ" , 
                                  "Energy of the closest electron over energy of the jet" , 100 , 0 , 300 );
  
  emfraction     = fs->make<TH1D>("EMfrac"  , "Electromagnetic fraction of the jets" , 100 , -50 , 50 );
  trkisolation   = fs->make<TH1D>("TrkIso"  , "Track isolation of the closest electron" , 100 , -2 , 20 );
  
  deltaR         = fs->make<TH1D>("deltaR"  , "DeltaR e-jet" , 100 , 0 , 20 );
  
  totaljetenergy = fs->make<TH1D>("TotEnergy" , "Energy of jets" , 100 , 0 , 300 );
  
  totaljetenergysum = fs->make<TH1D>("TotEnergybySum" , "Energy of jets by addind Calo info" , 100 , 0 , 300 );

  overlapjet = fs->make<TH1D>("OverlapJetFlag" , "Checking the test on overlapping works" , 10 , -3 , 3 );
  
  eleLabel_ = (iConfig.getUntrackedParameter<edm::InputTag>("electronTag"));
  muoLabel_ = (iConfig.getUntrackedParameter<edm::InputTag>("muonTag"));
  jetLabel_ = (iConfig.getUntrackedParameter<edm::InputTag>("jetTag"));
  tauLabel_ = (iConfig.getUntrackedParameter<edm::InputTag>("tauTag"));
  metLabel_ = (iConfig.getUntrackedParameter<edm::InputTag>("metTag"));

  m_useflaggedJets =  (iConfig.getUntrackedParameter<bool>("useFlaggedJets",false));
  

  
}


JetsAnalyzer::~JetsAnalyzer()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called to for each event  ------------
void JetsAnalyzer::analyze(const edm::Event& iEvent, 
                           const edm::EventSetup& iSetup)
{
  
  doExercise1( iEvent, iSetup );
  
  doExercise2( iEvent, iSetup );

}

void JetsAnalyzer::doExercise1( const edm::Event& iEvent, 
                                const edm::EventSetup& iSetup)
{
  
  int _nelectrons(0);
  int _njets(0);
  int _njetscut(0);
  
  edm::Handle<edm::View<pat::Jet> > jetHandle;
  iEvent.getByLabel(jetLabel_,jetHandle);
  
  
  edm::Handle<edm::View<pat::Electron> > electronHandle;
  iEvent.getByLabel(eleLabel_,electronHandle);

  std::vector<float> vecdeltaR;
  
  for(edm::View<pat::Jet>::const_iterator jet_iter = jetHandle->begin(); 
      jet_iter!=jetHandle->end(); ++jet_iter){
    
    _nelectrons = 0;
  
    vecdeltaR.clear();
    
    for(edm::View<pat::Electron>::const_iterator electron_iter = electronHandle->begin(); 
        electron_iter!=electronHandle->end(); ++electron_iter) {
      
      float _deltaR = DeltaR<pat::Electron, pat::Jet>()( (*electron_iter), (*jet_iter) );
    
      vecdeltaR.push_back(_deltaR);
        
      deltaR->Fill( _deltaR );
      
      ++_nelectrons;
      
    }

    float jetenergysum = (*jet_iter).hadEnergyInHB()+
      (*jet_iter).hadEnergyInHE()+
      (*jet_iter).hadEnergyInHF()+
      (*jet_iter).hadEnergyInHO();
    
    float jetenergy = (*jet_iter).energy();
    
    totaljetenergysum->Fill( jetenergysum );
    
    totaljetenergy->Fill( jetenergy );
        
    if ( jetenergy > 10 ) ++_njetscut;
    ++_njets;
    
    int pos = findClosest( vecdeltaR );
    
    if ( electronHandle->size() != 0) {
      
      float closestelectronE = (*electronHandle)[pos].energy();
      eclosestEl->Fill(closestelectronE);
      float ratio = closestelectronE / jetenergy ;
      eclosertEloJet->Fill( ratio );
      
      trkisolation->Fill( (*electronHandle)[pos].trackIso() );
      
    }
    
    emfraction->Fill( (*jet_iter).emEnergyFraction() );
    
  }
  
  njets->Fill( _njets );
  njetscut->Fill( _njetscut );
  nelectrons->Fill ( _nelectrons );
  
}

void JetsAnalyzer::doExercise2( const edm::Event& iEvent, 
                                const edm::EventSetup& iSetup)
{
  
  edm::Handle<edm::View<pat::Jet> > jetHandle;
  iEvent.getByLabel(jetLabel_,jetHandle);
  
  for(edm::View<pat::Jet>::const_iterator jet_iter = jetHandle->begin(); 
      jet_iter!=jetHandle->end(); ++jet_iter){

    if ( m_useflaggedJets ) {
      
      


      if (pat::Flags::test( (*jet_iter), pat::Flags::Overlap::Electrons)) {
        // the jet does not overlap with electrons
        overlapjet->Fill(-1);
        
      } else {
        // the jet is overlapping with electrons
        overlapjet->Fill(1);
      }
      
    }
    
    else continue;
    
  }

}

int JetsAnalyzer::findClosest( const std::vector<float> & data )
{
  
  std::vector<float>::const_iterator itr;
  
  int k(0);
  int pos(0);
  float smallest(1000.);
  
  for(itr=data.begin(); itr != data.end(); ++itr) {
    
    float tmp = (*itr);
    if ( tmp < smallest ) { 
      smallest = tmp;
      pos = k;
    }
    ++k;
  }
  
  return pos;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
JetsAnalyzer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetsAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetsAnalyzer);
