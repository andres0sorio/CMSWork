// -*- C++ -*-
//
// Package:    RPCTechnicalTrigger
// Class:      RPCTechnicalTrigger
// 
/**\class RPCTechnicalTrigger RPCTechnicalTrigger.cc L1Trigger/RPCTechnicalTrigger/src/RPCTechnicalTrigger.cc

 Description: 

 Implementation:

*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Thu Nov 13 08:21:16 CET 2008
// $Id$

// local
#include "L1Trigger/RPCTechnicalTrigger/src/RPCTechnicalTrigger.h"

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RPCTechnicalTrigger::RPCTechnicalTrigger(const edm::ParameterSet& iConfig) : 
  edm::EDAnalyzer()
{
  
  m_debugmode = 2;
  m_rbclogictype = std::string("TestLogic");
  m_ttulogictype = std::string("TrackingAlgo");
  
  std::string _tmpfile("testdata.txt");
  m_signal  = new RPCProcessTestSignal( _tmpfile.c_str() );
  
  //... There are three Technical Trigger Units: 1 per 2 Wheels
  
  m_ttu[0] = new RPCTTU( 1 , m_rbclogictype.c_str(), m_ttulogictype.c_str(), 2 );
  m_ttu[1] = new RPCTTU( 2 , m_rbclogictype.c_str(), m_ttulogictype.c_str(), 2 );
  m_ttu[2] = new RPCTTU( 3 , m_rbclogictype.c_str(), m_ttulogictype.c_str(), 1 );
  
  //...
  
  bool status(false);
  status = initialise();
  
}

//=============================================================================
// Destructor
//=============================================================================
RPCTechnicalTrigger::~RPCTechnicalTrigger() {
  
  delete m_ttu[0];
  delete m_ttu[1];
  delete m_ttu[2];
  
} 

//=============================================================================
// ------------ method called to for each event  ------------------------------

void RPCTechnicalTrigger::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  bool status = m_signal->next();
  if ( !status) return;
  
  m_signal->retrievedata( m_data );
  
  //. distribute data to different TTU and process it
  
  for(int k=0; k<3; ++k) {
    m_ttu[k]->process( m_data );
  }
  
  //.. analyse results from emulation
  
  
  
  //... reset data map for next event
  
  m_data.clear();

  //...
  
}

// ------------ method called once each job just before starting event loop  ------------
void RPCTechnicalTrigger::beginJob(const edm::EventSetup& _evtSetup)
{

#ifdef AOSORIO_T61
  _evtSetup.get<MuonGeometryRecord>().get( m_rpcGeometry );
#endif

  bool status(false);
  status = initialise();
  
}

bool RPCTechnicalTrigger::initialise() 
{

  bool status(false);
  for (int k=0; k < 3; ++k )
    status = m_ttu[k]->initialise();
  return status;
  
}

void RPCTechnicalTrigger::printinfo()
{
  
  for (int k=0; k < 3; ++k )
    m_ttu[k]->printinfo();
  
}


// ------------ method called once each job just after ending the event loop  ------------
void RPCTechnicalTrigger::endJob() 
{
  
}

// //define this as a plug-in
// DEFINE_FWK_MODULE(RPCTechnicalTrigger);
