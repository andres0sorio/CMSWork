#include "DTWork/RPCIncBXFilter/src/RPCIncBXFilter.h"

//

RPCIncBXFilter::RPCIncBXFilter(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  m_trackLabel         = iConfig.getParameter<edm::InputTag>("TrackLabel");
  m_debug = true;
  m_noTrackinfo = false;

}


RPCIncBXFilter::~RPCIncBXFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
RPCIncBXFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  edm::Handle<reco::TrackCollection> trackCollectionHandle;
  iEvent.getByLabel(m_trackLabel, trackCollectionHandle);
  
  if ( !trackCollectionHandle.isValid() ) {
    std::cout << "RPCIncBCFilter> " << " can't find tracks label "
              << m_trackLabel << '\n';
    
    m_noTrackinfo = true;
    return false;

  }

  int trackWincBx   = 0;
  
  if ( ! m_noTrackinfo  ) {
    
    reco::TrackCollection::const_iterator trackItr;
    
    int rechitcounter = 0;
    int trackcounter  = 0;

    for (trackItr = trackCollectionHandle->begin(); trackItr != trackCollectionHandle->end(); trackItr++) {
      
      trackingRecHit_iterator recHitItr;
      
      trackcounter++;
      rechitcounter = 0;
      
      if (m_debug) std::cout << trackcounter << "*" << std::endl;
      
      int bx0 = 0;
      int bx1 = 0;
      int prev_bx = 0;
      bool neg_pattern = false;

      for( recHitItr = trackItr->recHitsBegin(); recHitItr != trackItr->recHitsEnd(); recHitItr++) {
	
	if ( (*recHitItr)->geographicalId().det() != DetId::Muon )
	  continue;
	
	if ( (*recHitItr)->geographicalId().subdetId() != MuonSubdetId::RPC ) {
	  continue;
	}
	
	if ( !(*recHitItr)->isValid() ) continue;
	
	//RPCDetId rollId = (RPCDetId)(*recHit)->geographicalId();
	//RPCGeomServ rpcsrv(rollId);
	//LocalPoint recHitPos=(*recHit)->localPosition();
	
	int bx = ((RPCRecHit*)(&(**recHitItr)))->BunchX();

	std::cout << bx << std::endl;
	
	if( bx == 0 )
	  ++bx0;
	else if( bx >= 1 )
	  ++bx1;
	else {};
	
	int bx_diff = (bx - prev_bx);

	if ( bx_diff < 0 )
	  neg_pattern = true;

	prev_bx = bx;
	
	rechitcounter++;
	
      }
      
      if ( bx0 > 1 && bx1 > 1 && !neg_pattern)
	trackWincBx++;
    
    }
        
  }
  
  if ( trackWincBx > 0 ) {
    std::cout << "increasing RPC bx found" << std::endl;
    return true;
  }

  return false;
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
RPCIncBXFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCIncBXFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCIncBXFilter);
