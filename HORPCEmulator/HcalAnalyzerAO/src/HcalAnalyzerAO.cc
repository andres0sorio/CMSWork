// -*- C++ -*-
//
// Package:    HcalAnalyzerAO
// Class:      HcalAnalyzerAO
// 
/**\class HcalAnalyzerAO HcalAnalyzerAO.cc UserCode/HcalAnalyzerAO/src/HcalAnalyzerAO.cc

Description: HO (RecHit/digis) & RPC Trigger digis Analyzer. Made for basic understanding of objects & Geometry
             Stage 0 of HO+RPC trigger emulator

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Andres Oliveros
//         Created:  Tue Apr  2 09:22:22 CDT 2013
// $Id: HcalAnalyzerAO.cc,v 1.1 2013/04/23 16:04:17 aosorio Exp $
//
//


// system include files
#include <map>
#include <memory>
#include <vector>
#include <utility>
#include <ostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/HcalRecHit/interface/HBHERecHit.h"
#include "DataFormats/HcalRecHit/interface/HFRecHit.h"
#include "DataFormats/HcalRecHit/interface/HORecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

//...Muon
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

//...RPC Trigger

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"

#include "DataFormats/Math/interface/deltaR.h"

#include <TLorentzVector.h>

//
// class declaration
//

class HcalAnalyzerAO : public edm::EDAnalyzer {
public:
  explicit HcalAnalyzerAO(const edm::ParameterSet&);
  ~HcalAnalyzerAO();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  void FillGeometry( edm::EventSetup const& );
  
  // ----------member data ---------------------------
  
  std::map<std::string,TH1D*> h_1dhistograms; 
  std::map<std::string,TH2D*> h_2dhistograms; 

  edm::InputTag m_hcalDigisLabel;

  edm::InputTag m_hoRecHitsLabel;

  edm::InputTag m_recoMuonLabel;

  edm::InputTag m_rpctLabel;

  TH2D* hHCAL_ieta_iphi_etaMap;
  TH2D* hHCAL_ieta_iphi_phiMap;
  
};

HcalAnalyzerAO::HcalAnalyzerAO(const edm::ParameterSet& iConfig)
{
  
  m_hcalDigisLabel = iConfig.getParameter<edm::InputTag>("hoRechits");
  m_hoRecHitsLabel = iConfig.getParameter<edm::InputTag>("hoDigis");
  m_recoMuonLabel  = iConfig.getParameter<edm::InputTag>("muon");
  m_rpctLabel      = iConfig.getParameter<edm::InputTag>("rpctDigis");

  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  
  h_1dhistograms["EHOB"]    = fs->make<TH1D>("ehob" , "Reconstructed energy for HO" , 100, -5.5 , 50.0 );
  h_1dhistograms["HOiEta"]  = fs->make<TH1D>("hoiEta" , "Reconstructed Eta" , 50, -30.0 , 30.00 );
  h_1dhistograms["HOiPhi"]  = fs->make<TH1D>("hoiPhi" , "Reconstructed Phi" , 50, 0.0 , 80.00 );
  h_1dhistograms["HOiEtaD"]  = fs->make<TH1D>("hoiEtaD" , "Reconstructed Eta" , 50, -3.0 , 3.00 );
  h_1dhistograms["HOiPhiD"]  = fs->make<TH1D>("hoiPhiD" , "Reconstructed Phi" , 50, -4.0 , 4.00 );
  
  h_1dhistograms["muonPt"]  = fs->make<TH1D>("muonPt"  , "Reco muon Pt"  , 50, 0.0 , 200.00 );
  h_1dhistograms["muonEta"] = fs->make<TH1D>("muonEta" , "Reco muon Eta" , 50, -3.0 , 3.0 );
  h_1dhistograms["muonPhi"] = fs->make<TH1D>("muonPhi" , "Reco muon Phi" , 50, -3.0 , 3.0 );
  h_1dhistograms["deltaR"]  = fs->make<TH1D>("deltaR"  , "DeltaR"        , 50, 0.0 , 10.0 );

  //RPCbTrigger
  //h_1dhistograms["RPCbx"]  = fs->make<TH1D>("RPCbx"  , "RPC bx"  , 8, -4.0 , 4.0 );
  //h_1dhistograms["RPCPt"]  = fs->make<TH1D>("RPCPt"  , "RPC Pt"  , 50, 0.0 , 100.0 );
  


  hHCAL_ieta_iphi_etaMap    = fs->make<TH2D>("HCAL_ieta_iphi_etaMap","",30, -15, 15, 72, 1,73);
  hHCAL_ieta_iphi_phiMap    = fs->make<TH2D>("HCAL_ieta_iphi_phiMap","",30, -15, 15, 72, 1,73);

  // Initialize bins for geometry to -999 because z = 0 is a valid entry 
  for (int i = 1; i <= 30; i++) {
    
    for (int j = 1; j <= 72; j++) {

      hHCAL_ieta_iphi_etaMap->SetBinContent(i,j,-99);
      hHCAL_ieta_iphi_phiMap->SetBinContent(i,j,-99);
      
    }
    
  }
  
}


HcalAnalyzerAO::~HcalAnalyzerAO()
{
  
  
}

//
// member functions
//

// ------------ method called for each event  ------------
void
HcalAnalyzerAO::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //Muon candidate
  edm::Handle<reco::MuonCollection> muonHandle;
  bool found = iEvent.getByLabel( m_recoMuonLabel, muonHandle);
  
  if(!found) {
    std::cout <<"could not find muon " << m_recoMuonLabel << std::endl;
  } else {
    
    reco::MuonCollection::const_iterator recoMuItr;
    
    for (recoMuItr = muonHandle->begin(); recoMuItr != muonHandle->end(); recoMuItr++) {
      
      //Only study the GlobalMuons from this collection
      
      if( ! (*recoMuItr).isGlobalMuon() ) continue;
      
      reco::TrackRef trackItr = (*recoMuItr).globalTrack();
      
      double trkPt  = trackItr->pt();
      double trkEta = trackItr->eta();
      double trkPhi = trackItr->phi();
      
      h_1dhistograms["muonPt" ]->Fill( trkPt  );
      h_1dhistograms["muonEta"]->Fill( trkEta );
      h_1dhistograms["muonPhi"]->Fill( trkPhi ); 
      
      //HO RecHits
      edm::Handle<HORecHitCollection> rhcHandle;
      found &= iEvent.getByLabel( m_hoRecHitsLabel, rhcHandle);
  
      if(!found) {
    
	std::cout <<"could not find rechits " << m_hoRecHitsLabel << std::endl;
    
      }
  
      else {
    
	assert( rhcHandle.isValid() );
    
	// process HO rechits
    
	int offset = 16;

	for(unsigned i=0; i<rhcHandle->size(); i++) {
       
	  const HORecHit& erh = (*rhcHandle)[i];

	  double energy = erh.energy();
      
	  const HcalDetId& detid = (HcalDetId)erh.detid();
	  
	  HcalSubdetector esd=(HcalSubdetector)detid.subdetId();
      
	  //Check if muon+hohit matches in eta/phi
	  
	  if ( esd == 3 ) {  //HcalOuter = 3 
	    
	    double iEta = detid.ieta();
	    double iPhi = detid.iphi();

	    //std::cout << " Calo_ieta " << iEta
	    //	      << " Calo_iphi " << iPhi << std::endl;

	    h_1dhistograms["HOiEta"]->Fill( iEta );
	    h_1dhistograms["HOiPhi"]->Fill( iPhi );
	    
	    
	    if ( iEta > 0 )  iEta = iEta - 1;
	    	    
	    double eta = hHCAL_ieta_iphi_etaMap->GetBinContent( iEta + offset,iPhi);
	    double phi = hHCAL_ieta_iphi_phiMap->GetBinContent( iEta + offset,iPhi);
	    
	    //double theta = 2*TMath::ATan(exp(-1*eta));
	    //double ET = energy * TMath::Sin(theta);

	    double deltaR = sqrt( std::pow((trkEta - eta ), 2.0) + std::pow( (trkPhi - phi ) , 2.0 ) );

	    h_1dhistograms["deltaR"]->Fill( deltaR );
	    
	    if ( iEta == 0 ) {
	      h_1dhistograms["EHOB"]->Fill( energy*1.0e3 );//MeV
	      h_1dhistograms["HOiPhiD"]->Fill( phi );
	      h_1dhistograms["HOiEtaD"]->Fill( eta );
	    }
	    
	  }
	  
	}
	
      }
      
    }
    
  }
 
  ///
  
  edm::Handle< std::vector<L1MuRegionalCand> > rpcbHandle; 
  iEvent.getByLabel(m_rpctLabel,rpcbHandle);
  
  
  //L1MuGMTReadoutCollection const* gmtrc = gmtrc_handle.product();
    
  if( ! rpcbHandle.isValid() ) {
    std::cout <<"could not find rechits " << m_rpctLabel << std::endl;
    return;
  }
  
  
  std::vector<L1MuRegionalCand>::const_iterator itRPC;
  
  int counter = 0;

  for(itRPC = rpcbHandle->begin(); itRPC != rpcbHandle->end(); itRPC++) {
    
    std::cout << "RPC Bx "        << counter << '\t' << (*itRPC).bx()          << std::endl;
    std::cout << "RPC Eta value " << counter << '\t' << (*itRPC).etaValue()    << std::endl;
    std::cout << "RPC Phi Value " << counter << '\t' << (*itRPC).phiValue()    << std::endl;
    std::cout << "RPC Pt Value "  << counter << '\t' << (*itRPC).ptValue()     << std::endl;
    std::cout << "RPC charge "    << counter << '\t' << (*itRPC).chargeValue() << std::endl;
    std::cout << "RPC Quality "   << counter << '\t' << (*itRPC).quality()     << std::endl;
    counter++;
  }
	
	

}



// ------------ method called once each job just before starting event loop  ------------
void 
HcalAnalyzerAO::beginJob() 
{
}

void
HcalAnalyzerAO::FillGeometry( const edm::EventSetup& iSetup ) {

  const CaloSubdetectorGeometry* HOgeom;
  
  edm::ESHandle<CaloGeometry> pG;
  iSetup.get<CaloGeometryRecord>().get(pG);
  
  if (!pG.isValid() )
    {
      edm::LogInfo("OutputInfo") << "Failed to retrieve an Event Setup Handle, Aborting Task "
                                 << "HCALRecHitAnalyzer::FillGeometry!\n"; 
      return;
    }
  
  const CaloGeometry cG = *pG;
  
  HOgeom = cG.getSubdetectorGeometry(DetId::Hcal,HcalOuter);

  int offset = 16;

  int nHOdetid = 0;
  std::vector<DetId> HOids = HOgeom->getValidDetIds(DetId::Hcal, HcalOuter);
  std::vector<DetId>::iterator itr;

  for ( itr = HOids.begin(); itr != HOids.end(); itr++) {
    
    nHOdetid++;
    
    const CaloCellGeometry* cell = HOgeom->getGeometry(*itr);
    HcalDetId HcalID(itr->rawId());
    //GlobalPoint p = cell->getPosition();

    int Calo_ieta = HcalID.ieta();
    int Calo_iphi = HcalID.iphi();
    double Calo_eta = cell->getPosition().eta();
    double Calo_phi = cell->getPosition().phi();

    //std::cout << " Calo_ieta " << Calo_ieta
    //	        << " Calo_iphi " << Calo_iphi
    //          << " Calo_eta  " << Calo_eta
    //          << " Calo_phi  " << Calo_phi << std::endl;

    if ( Calo_ieta > 0 )  Calo_ieta = Calo_ieta - 1;
   
    
    // HCAL to HO eta, phi map comparison
    if ( hHCAL_ieta_iphi_etaMap->GetBinContent( Calo_ieta + offset,Calo_iphi) == -99 ) {

      hHCAL_ieta_iphi_etaMap->SetBinContent( Calo_ieta + offset, Calo_iphi, Calo_eta);
      hHCAL_ieta_iphi_phiMap->SetBinContent( Calo_ieta + offset, Calo_iphi, Calo_phi);
    
    }
        
    // (Calo_ieta > HOmax_ieta) HOmax_ieta = Calo_ieta;
    // (Calo_ieta < HOmin_ieta) HOmin_ieta = Calo_ieta;
    // (Calo_iphi > HOmax_iphi) HOmax_iphi = Calo_iphi;
    // (Calo_iphi > HOmax_iphi) HOmin_iphi = Calo_iphi;
    
  }
  
}


// ------------ method called once each job just after ending the event loop  ------------
void 
HcalAnalyzerAO::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
HcalAnalyzerAO::beginRun(edm::Run const& run , edm::EventSetup const& iSetup)
{
  
  FillGeometry(iSetup);
  
}

// ------------ method called when ending the processing of a run  ------------
void 
HcalAnalyzerAO::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
HcalAnalyzerAO::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
HcalAnalyzerAO::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HcalAnalyzerAO::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HcalAnalyzerAO);
