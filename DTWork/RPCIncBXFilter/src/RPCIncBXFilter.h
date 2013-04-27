// -*- C++ -*-
//
// Package:    RPCIncBXFilter
// Class:      RPCIncBXFilter
// 
/**\class RPCIncBXFilter RPCIncBXFilter.cc DTWork/RPCIncBXFilter/src/RPCIncBXFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Osorio
//         Created:  Tue Jun 28 15:50:20 COT 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


//...Tracker
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"

//... Det/MuonDet
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>

#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/RPCGeometry/interface/RPCGeometry.h>
#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>



//
// class declaration
//

class RPCIncBXFilter : public edm::EDFilter {
   public:
      explicit RPCIncBXFilter(const edm::ParameterSet&);
      ~RPCIncBXFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
  
  edm::InputTag m_trackLabel;
  bool m_debug;
  bool m_noTrackinfo;

};

