// Include from Local
#include "RPCDigiAnalyzer/TTUAnalyzer/src/TTUAnalyzer.h"

#include <Geometry/RPCGeometry/interface/RPCRollSpecs.h>

// -------------------------------------------------------------------

TTUAnalyzer::TTUAnalyzer(const edm::ParameterSet& iConfig) {
  
  m_nevts = 0;

  m_rpcDigiLabel = iConfig.getParameter<edm::InputTag>("RPCDigiLabel");
  m_minDigis     = iConfig.getUntrackedParameter<int>("CutAtDigis", 0);
  m_EvtSelection = iConfig.getUntrackedParameter<int>("EvtSelection", 0);
  m_EvtSelType   = iConfig.getUntrackedParameter<int>("EvtSelType", 0); // ... 1: keep or 0: reject from list
  m_BxWindow     = iConfig.getUntrackedParameter<int>("BxWindow", 1); // ... +/- bx window
  m_evtselInfile = iConfig.getUntrackedParameter<std::string>("EvtSelInput", std::string("test.txt") );
  
  out = new std::ofstream("checkdata.out",ofstream::out);
  
  outbxw = new std::ofstream("checkdata_bxwindow.out",ofstream::out);
  
  m_noinputfile = true;
  
  if ( m_EvtSelection > 0 ) {
    iss = new std::ifstream( m_evtselInfile.c_str(), ifstream::in );
    if ( iss->bad() ) m_noinputfile = true;
    else m_noinputfile = false;
  }
  
  
  if ( ! m_noinputfile ) {
    while(1) {
      int evt(0);
      if( iss->eof() ) break;
      (*iss) >> evt;
      m_selectedEvts.push_back( evt );
    }
    iss->close();
    delete iss;
  }
  
  edm::Service<TFileService> fservice;
  
  for(int i = 0; i < 7; ++i) {
    
    int _bxid = i-3;
    
    for(int j = 0; j < 5; ++j) {
      
      int _wheel = j;
      int code   = 0;
      int bxsign = 1;
      
      if ( _bxid != 0 ) bxsign = ( _bxid / std::abs(_bxid) );
      else bxsign = 1;
      code = bxsign * ( 1000000*std::abs(_bxid) + 10000*_wheel );
      
      std::cout << "TTUAnalyzer> total HistoOutput: " << code << std::endl;
      
      m_houtput[ code ] = new HistoOutput( fservice , _bxid , _wheel);
      
    }
    
  }
  
  std::cout << "TTUAnalyzer> total HistoOutput: " <<  m_houtput.size() << std::endl;
  
  m_allbx  = fservice->make<TH1D>("All.BX",
                                  "All bx distribution in data",
                                  7, -4 , 4 );
  std::ostringstream hname;

  for(int i = 0; i < 5; ++i) {
    hname << "Sector.Layer.BX+1.W." << (i-2);
    m_sectorVsblayer[i] = fservice->make<TH2D>(hname.str().c_str(),
                                               "Sector vs Layer for BX=+1",
                                               12, 0 , 12, 7, 0, 7 );
    hname.str("");
  }
  
  for(int i=-2; i < 3; ++i) {
    
    hname << "Avg.BX.Event.Wheel." << i ;
    m_avgbx[i+2]  = fservice->make<TH1D>(hname.str().c_str(),
                                         "Average bx distribution per event and wheel",
                                         7, -4 , 4 );
    hname.str("");
    
  }
    
  m_NDigis = fservice->make<TH1D>("N.digis.in.event",
                                  "N digis in all the event",
                                  20, 0 , 20 );

  hname << "top.Sector.Bx";
  topSecbx = fservice->make<TH1D>(hname.str().c_str(),
                                  "Layer hits profile per sector",
                                  7, -3.5 ,3.5 );
  hname.str("");
  hname << "bottom.Sector.Bx";

  bottomSecbx = fservice->make<TH1D>(hname.str().c_str(),
                                     "Layer hits profile per sector",
                                     7, -3.5 ,3.5 );
  hname.str("");            
    
  
}

TTUAnalyzer::~TTUAnalyzer()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}

// ------------ method called to for each event  ------------

void TTUAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  bool foundEvt(false);
  bool keepEvt(false);
  
  int evt = iEvent.id().event();
  
  std::vector<int>::iterator itrEvt;
  itrEvt = find( m_selectedEvts.begin(), m_selectedEvts.end(), evt );
  
  if ( m_EvtSelection > 0 ) {
    
    if ( itrEvt != m_selectedEvts.end() ) {
      foundEvt  = true;
      m_selectedEvts.erase( itrEvt );
      
    } else foundEvt  = false;
    
    if ( foundEvt )
      keepEvt = (bool) m_EvtSelType;
    else keepEvt = ! (bool) m_EvtSelType;
    
    if ( ! keepEvt) return;
        
  }
  
  edm::ESHandle<RPCGeometry> m_ptr_rpcGeom;
  iSetup.get<MuonGeometryRecord>().get( m_ptr_rpcGeom );
  
  edm::LogInfo("TTUAnalyzer::analyze") << '\n';
  std::cout << "TTUAnalyzer::analyze" << std::endl;
  
  (*out) << "---: " <<  iEvent.id() << '\n';
  (*outbxw) << "---: " <<  iEvent.id() << '\n';
  

  
  for(int i=0; i < 6; ++i) m_ndigi[i] = 0;
  
#ifndef _USESIM
  
  edm::Handle<RPCDigiCollection> m_ptr_digiColl;
  try {
    iEvent.getByLabel(m_rpcDigiLabel, m_ptr_digiColl);
  }
  catch (...) {
    edm::LogInfo("TTUAnalyzer:analyze") << "can't find  with label RPCDigiCollection" << '\n';
    return;
  }
  
  if ( m_EvtSelection > 0 && m_noinputfile ) {
    edm::LogInfo("TTUAnalyzer:analyze") << "no event selection possible: please give an input file" << '\n';
    return;
  }
  
  RPCDigiCollection::const_iterator m_digiItr;
  RPCDigiCollection::DigiRangeIterator m_detUnitItr;
  
  for (m_detUnitItr = (m_ptr_digiColl)->begin();
       m_detUnitItr != (m_ptr_digiColl)->end(); ++m_detUnitItr ) {
    
    m_digiItr = (*m_detUnitItr ).second.first;
    
    const RPCDetId & id  = (*m_detUnitItr).first;
    
    int bx      = (*m_digiItr).bx();
    int strip   = (*m_digiItr).strip();
    
#else

    edm::Handle<edm::DetSetVector<RPCDigiSimLink> > simLink;

    iEvent.getByLabel("simMuonRPCDigis", "RPCDigiSimLink", simLink);
    
    if ( ! simLink.isValid() ) {
      edm::LogError("RPCTechnicalTrigger") << "can't find RPCDigiCollection with label: " 
                                           << m_rpcDigiLabel << '\n';
      return;
      
    }
    
    std::cout << simLink->size() << std::endl;
    
    edm::DetSetVector<RPCDigiSimLink>::const_iterator m_linkItr;
    edm::DetSet<RPCDigiSimLink>::const_iterator m_digiItr;
    
    for( m_linkItr = simLink->begin();
         m_linkItr != simLink->end();
         ++m_linkItr ) {
      
      for ( m_digiItr = m_linkItr->data.begin();
            m_digiItr != m_linkItr->data.end();
            ++m_digiItr ) {
        
        uint32_t detid = m_digiItr->getDetUnitId();
        const RPCDetId id( detid );

        int bx      = (*m_digiItr).getBx();
        int strip   = (*m_digiItr).getStrip();

        
#endif
    
        const RPCRoll * roll = dynamic_cast<const RPCRoll* >( (m_ptr_rpcGeom)->roll(id));
        
        if((roll->isForward())) {
          std::cout << "TTUAnalyzer: roll is forward" << std::endl;
          continue;
        }
        
        
        int wheel   = roll->id().ring();
        int sector  = roll->id().sector() - 1;
        int layer   = roll->id().layer();
        int station = roll->id().station();
        int blayer  = getBarrelLayer( layer, station ) - 1;
        
        m_allbx->Fill(bx);

        if ( sector > 1 && sector < 5 ) 
          topSecbx->Fill( bx );
        else if ( sector > 7 && sector < 12 )
          bottomSecbx->Fill( bx );
        else {
        }
        
        switch(wheel){
        case -2:
          // code to execute if integer_val is val_1
          std::cout << "adding bx to wheel -2: " <<  bx << std::endl;
          m_bxevt[0].push_back(bx);
          ++m_ndigi[1];
          if (bx == 1)
            m_sectorVsblayer[0]->Fill(sector,blayer);
          break;
        case -1:
          // code to execute if integer_val is val_n
          std::cout << "adding bx to wheel -1: " <<  bx << std::endl;
          m_bxevt[1].push_back(bx);
          ++m_ndigi[2];
          if (bx == -1)
            m_sectorVsblayer[1]->Fill(sector,blayer);
          break;
        case 0:
          // code to execute if integer_val is val_n
          std::cout << "adding bx to wheel 0 " <<  bx << std::endl;
          m_bxevt[2].push_back(bx);
          ++m_ndigi[3];
          if (bx == -1)
            m_sectorVsblayer[2]->Fill(sector,blayer);
          break;
        case 1:
          // code to execute if integer_val is val_n
          std::cout << "adding bx to wheel +1: " <<  bx << std::endl;
          m_bxevt[3].push_back(bx);
          ++m_ndigi[4];
          if (bx == -1)
            m_sectorVsblayer[3]->Fill(sector,blayer);
          break;
        case 2:
          // code to execute if integer_val is val_n
          std::cout << "adding bx to wheel +2: " <<  bx << std::endl;
          m_bxevt[4].push_back(bx);
          ++m_ndigi[5];
          if (bx == -1)
            m_sectorVsblayer[4]->Fill(sector,blayer);
          break;
        default:
          // code to execute if integer_val is none of the above
          std::cout << "wheel not determined" << std::endl;
        }
        
        std::cout << "Bx: "      << bx      << '\t'
                  << "Wheel: "   << wheel   << '\t'
                  << "Sector: "  << sector  << '\t'
                  << "Layer: "   << layer   << '\t'
                  << "Station: " << station << '\t'
                  << "B-Later: " << blayer  << '\t'
                  << "Strip: "   << strip   << '\n';
        
        const RPCRollSpecs * rpcspecs;
        rpcspecs = roll->specs();
        
        std::cout << "Specs: " << rpcspecs->detName() << '\n';
        
        int code(0);
        int bxsign(1);
        
        //...
        
        if ( std::abs( bx ) > 5 ) {
          std::cout << "TTUAnalyzer: bx larger than 3" << std::endl;
          continue;
        }
          
        if ( bx != 0 ) bxsign = ( bx / std::abs(bx) );
        else bxsign = 1;
        code = bxsign * ( 1000000*std::abs(bx) + 10000*(wheel+2) );
        
        WheelMap * wmap = new WheelMap( bx , wheel );
        std::pair<std::map<int,WheelMap*>::iterator, bool > ret;
        
        // first insert function version (single parameter):
        ret = m_wheelmapsPerBx.insert ( std::pair<int,WheelMap*>( code , wmap) );
        
        if (ret.second==false) {
          std::cout << "element with bx " << bx << " already existed" << '\n';
          m_itr = m_wheelmapsPerBx.find( code );
          (*m_itr).second->sector.push_back( sector );
          (*m_itr).second->layer.push_back( blayer );
          
        } else {
          
          wmap->sector.push_back(sector);
          wmap->layer.push_back(blayer);
          
        }
        
        ++m_ndigi[0];
#ifndef _USESIM
        //there is only one loop with normal digis
      }
#else   
      //there are two loops with sim digis
    }
  }
#endif
  
  m_NDigis->Fill(m_ndigi[0]);
  
  //.. calculate average BX per event in all wheels
  std::vector<int>::iterator itr;
  for( int i = -2; i < 3; ++i ) {
    
    if ( m_ndigi[i+3] != 0 ) {
      for(itr = m_bxevt[i+2].begin(); itr != m_bxevt[i+2].end(); ++itr)
        m_avgbx[i+2]->Fill( (double)(*itr) );
    }
    m_bxevt[i+2].clear();
    
  }
  
  //.. process each wheel map
  std::cout << "TTUAnalyzer: " << m_wheelmapsPerBx.size() << std::endl;

  for( m_itr=m_wheelmapsPerBx.begin(); m_itr != m_wheelmapsPerBx.end(); ++m_itr ) {
    
    std::cout << "TTUAnalyzer: printing wheel maps" << std::endl;
    
    if ( (*m_itr).second->sector.size() <  m_minDigis ) {
      continue;
    }
    
    (*m_itr).second->printmaps( out );
    
    int key = (int) (*m_itr).first;
    
    m_itrHO = m_houtput.find( key );
    
    (*m_itr).second->fillhistograms( (*m_itrHO).second );
    
  }
  

  //... make an OR of maps in Bx window +/- bx
  std::vector< WheelMap* > vecWheelMaps;
  std::vector< WheelMap* >::iterator itrWM;
  
  for(int wheel=-2; wheel < 3; ++wheel) {
    
    int minBx=-1*m_BxWindow;
    int maxBx=m_BxWindow;
    int code(0);
    int bxsign(1);
    
    WheelMap * WideMap = new WheelMap(0, wheel);
    bool hasMap = false;
    
    for( int bx = minBx; bx <= maxBx; ++bx ) {
      
      if ( bx != 0 ) bxsign = ( bx / std::abs(bx) );
      else bxsign = 1;
      code = bxsign * ( 1000000*std::abs(bx) + 10000*(wheel+2) );
      
      m_itr = m_wheelmapsPerBx.find( code );
      
      if ( m_itr != m_wheelmapsPerBx.end() ) {
        std::cout << "adding data" << std::endl;
        (*WideMap)+=*(*m_itr).second;
        hasMap = true;
      } else continue;
      
    }
    
    if ( hasMap ) vecWheelMaps.push_back( WideMap );
    
  }

  //... print the resulting map of time window
  
  for( itrWM = vecWheelMaps.begin(); itrWM != vecWheelMaps.end(); ++itrWM ){
    
    (*itrWM)->printmaps( outbxw );
    
  }
  
  (*outbxw) << "-----------------------------" << '\n';

  //.. clear the wheel maps for the next event
  for( m_itr=m_wheelmapsPerBx.begin(); m_itr != m_wheelmapsPerBx.end(); ++m_itr )
    delete (*m_itr).second;
  m_wheelmapsPerBx.clear();
  
  for( itrWM = vecWheelMaps.begin(); itrWM != vecWheelMaps.end(); ++itrWM )
    delete (*itrWM);
  vecWheelMaps.clear();
    
  //...
  
  (*out) << "-----------------------------" << '\n';
  
  ++m_nevts;
  
  std::cout << "TTUAnalyzer::analyze> end of event" << std::endl;
  
}

int TTUAnalyzer::getBarrelLayer( const int & _layer, const int & _station )
{
  
  //... Calculates the generic Barrel Layer (1 to 6)
  int blayer(0);
  
  if ( _station < 3 ) {
    blayer = ( (_station-1) * 2 ) + _layer;
  } else {
    blayer = _station + 2;
  }

  return blayer;
      
}


// ------------ method called once each job just before starting event loop  ------------

void TTUAnalyzer::beginJob( )
{
  
}

// ------------ method called once each job just after ending the event loop  ------------

void TTUAnalyzer::endJob() {

  out->close();
  delete out;
  
  outbxw->close();
  delete outbxw;
    
  std::cout << "TTUAnalyzer> done. total events: " << m_nevts << '\n';
  

}

//define this as a plug-in
DEFINE_FWK_MODULE(TTUAnalyzer);
