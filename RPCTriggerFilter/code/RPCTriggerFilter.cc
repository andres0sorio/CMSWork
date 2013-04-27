/**\class RPCTriggerFilter.cc
 Description: Provides a trigger filter for L1 muon Candidates
*/
// Original Author:  Anna Cimmino
//         Created:  Mon May  5 17:01:23 CEST 2008

// user include files
#include "DQMOffline/Muon/src/RPCTriggerFilter.h"
//Data Formats
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuRegionalCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
 
using namespace edm;
using namespace std;
RPCTriggerFilter::RPCTriggerFilter(const ParameterSet& ps)
{

  m_checker = new std::ofstream("checkdata.out",std::ofstream::out);
  
  LogVerbatim ("rpctriggerfilter") << "[RPCTriggerFilter]: Constructor";
  
  inputTag_ = ps.getUntrackedParameter<edm::InputTag>("GMTInputTag", edm::InputTag("gmt"));
  
  (*m_checker) << "input tag: instance: " << inputTag_.instance() << " : label: " << inputTag_.label() << '\n';
  
  rpcBarOnly_     = ps.getUntrackedParameter<bool>("RPCBarrelTrigger", false);
  rpcFwdOnly_     = ps.getUntrackedParameter<bool>("RPCEndcapTrigger", false);
  rpcOnly_        = ps.getUntrackedParameter<bool>("RPCTrigger",       true);
  dtOnly_         = ps.getUntrackedParameter<bool>("DTTrigger",        false);
  cscOnly_        = ps.getUntrackedParameter<bool>("CSCTrigger",       false);
  rpcAndDt_       = ps.getUntrackedParameter<bool>("RPCAndDT",         false);
  rpcAndCsc_      = ps.getUntrackedParameter<bool>("RPCAndCSC",        false);
  dtAndCsc_       = ps.getUntrackedParameter<bool>("DTAndCSC",         false);
  rpcAndDtAndCsc_ = ps.getUntrackedParameter<bool>("RPCAndDTAndCSC",   true);

  enableFilter_   = ps.getUntrackedParameter<bool>("EnableTriggerFilter", true);
  
}

RPCTriggerFilter::~RPCTriggerFilter(){}

bool RPCTriggerFilter::filter(Event& iEvent, const EventSetup& iSetup)
{
  event_++;
  LogVerbatim ("rpctriggerfilter") << "[RPCTriggerFilter]: Filtering event n°"<<event_;
  if(!enableFilter_){goodEvent_++; return true;}
  
  Handle<L1MuGMTReadoutCollection> pCollection;

  try {
    iEvent.getByLabel(inputTag_.label(),pCollection);
  }
  catch (...) {
    LogInfo("DataNotFound") << "can't find L1MuGMTReadoutCollection with label "
                            << inputTag_.label() ;
    return false;
  }
  
  LogVerbatim ("rpctriggerfilter") << "[RPCTriggerFilter]: L1MuGMTReadoutCollection found";
  
  bool rpcBarFlag  = false;
  bool rpcFwdFlag  = false;
  bool dtFlag      = false;
  bool cscFlag     = false;
  
  // get GMT readout collection
  const L1MuGMTReadoutCollection * gmtrc = pCollection.product();
  
  (*m_checker) << "Event: " << event_ << '\t' <<  gmtrc << '\n';

  // get record vector
  vector<L1MuGMTReadoutRecord> gmt_records = gmtrc->getRecords();
  // loop over records of individual bx's
  vector<L1MuGMTReadoutRecord>::const_iterator RRItr;
  int muons_ =0;
  
  (*m_checker) << "nRecords: " << gmt_records.size() << '\n';
  
  for( RRItr = gmt_records.begin(); RRItr != gmt_records.end(); RRItr++ ) 
  {   
    vector<L1MuGMTExtendedCand> GMTCands   = RRItr->getGMTCands();
    
    int BxInEvent = RRItr->getBxInEvent();
    if(BxInEvent!=0) continue;    
    
    //loop over GMT candidates in each record 
    vector<L1MuGMTExtendedCand>::const_iterator GMTItr;
    for( GMTItr = GMTCands.begin(); GMTItr != GMTCands.end(); ++GMTItr ) {
      
      muons_++;
      
      //this->printInfo( (*GMTItr) );
      
      if(GMTItr->empty()) continue;
      
      if (GMTItr->isRPC()&& !GMTItr->isFwd()) rpcBarFlag= true;
      else if (GMTItr->isRPC()) rpcFwdFlag=true;
      else if (!GMTItr->isFwd())dtFlag=true;
      else cscFlag=true;
      
    }//loop over GMT candidates in each record END
  }//loop over records of individual bxs END
  
  LogVerbatim ("rpctriggerfilter") << "[RPCTriggerFilter]: Muon #"<<muons_;
  
  if( (rpcOnly_        && (rpcBarFlag || rpcFwdFlag) && !dtFlag && !cscFlag) || // rpc Event
      (rpcBarOnly_     && !rpcFwdFlag && rpcBarFlag  && !dtFlag && !cscFlag) || // rpc Event in barrel
      (rpcFwdOnly_     && !rpcBarFlag && rpcFwdFlag  && !dtFlag && !cscFlag) || // rpc event in endcaps
      (dtOnly_         && !rpcFwdFlag && !rpcBarFlag && dtFlag  && !cscFlag) || // dt  event
      (cscOnly_        && !rpcFwdFlag && !rpcBarFlag && !dtFlag && cscFlag)  || // csc event
      (rpcAndDt_       && !rpcFwdFlag && rpcBarFlag  && dtFlag  && !cscFlag) || // rpc & dt  event
      (rpcAndCsc_      && rpcFwdFlag  && !rpcBarFlag && !dtFlag && cscFlag)  || // rpc & csc event
      (dtAndCsc_       && !rpcFwdFlag && !rpcBarFlag && dtFlag  && cscFlag)  || // dt  & csc event
      (rpcAndDtAndCsc_ && (rpcFwdFlag || rpcBarFlag) && dtFlag  && cscFlag) ) { // rpc & dt & csc event
    goodEvent_++; 
    (*m_checker) << "Accepted: " << 1 << '\n';
    return true;
    
  } else {
    (*m_checker) << "Accepted: " << 0 << '\n';
    return false;
  }
  
}

void RPCTriggerFilter::beginJob(const edm::EventSetup&)
{  //reset counters
  event_=0;
  goodEvent_=0;
}

void RPCTriggerFilter::endJob() {
  LogVerbatim ("rpctriggerfilter") << "[RPCTriggerFilter]: "<<event_<<" events checked. "<<goodEvent_<<" accepted!";
  m_checker->close();
}

void RPCTriggerFilter::printInfo( const L1MuGMTExtendedCand & _candidate)
{
  
  bool rpcBarFlag = false;
  bool rpcFwdFlag = false;
  bool dtFlag     = false;
  bool cscFlag    = false;
  
  (*m_checker) << "CandidateHasInfo: " << !(_candidate.empty()) << '\t';
  (*m_checker) << "Type: " << _candidate.isRPC() << '\t' << _candidate.isFwd() << '\n';
  
  if (_candidate.isRPC()&& !_candidate.isFwd()) rpcBarFlag= true;
  else if (_candidate.isRPC()) rpcFwdFlag=true;
  else if (!_candidate.isFwd())dtFlag=true;
  else cscFlag=true;
  
  (*m_checker) << "Flags: " << rpcBarFlag << " " << rpcFwdFlag << " " << dtFlag << " " << cscFlag << '\n';
  
  if( !_candidate.empty() ) {
    LogVerbatim ("rpctriggerfilter") << "[RPCTriggerFilter]: CandidateHasInfo";
    _candidate.print();
  } else {
    LogVerbatim ("rpctriggerfilter") << "[RPCTriggerFilter]: CandidateHasNoInfo";
    _candidate.print();
  }
  
}
