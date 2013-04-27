// -*- C++ -*-
//
// Package:    RPCTTConfMaker
// Class:      RPCTTConfMaker
// 
/**\class RPCTTConfMaker RPCTTConfMaker.cc RPCTTConfigurator/RPCTTConfMaker/src/RPCTTConfMaker.cc
   
 Description: <one line class summary>

 Implementation:
 <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Sat Dec 13 14:16:45 CET 2008
// $Id$

#include "RPCTTConfigurator/RPCTTConfMaker/src/RPCTTConfMaker.h"

RPCTTConfMaker::RPCTTConfMaker(const edm::ParameterSet& iConfig)
{
  
  std::string infile = iConfig.getUntrackedParameter<std::string>("DataFile",
                                                                  std::string("testdata.txt"));
  
  m_in = new std::ifstream();
  m_in->open(infile.c_str());
  
  if(!m_in->is_open()) {
    std::cout << "RPCTTConfMaker> cannot open file" << std::endl;
  } else {
    std::cout << "RPCTTConfMaker> file is now open" << std::endl;
  }
  
  
}

RPCTTConfMaker::~RPCTTConfMaker()
{
  
}

// ------------ method called to for each event  ------------
void RPCTTConfMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  RBCBoardSpecs * prbcspecs = new RBCBoardSpecs();
  TTUBoardSpecs * pttuspecs = new TTUBoardSpecs();

  //... add some initial values, just for testing

  addData( prbcspecs );
  addData( pttuspecs );
  
  //...
  
  edm::Service<cond::service::PoolDBOutputService> poolDbService;
  
  if( poolDbService.isAvailable() ) {
    
    if ( poolDbService->isNewTagRequest( "RBCBoardSpecsRcd" ) )
      poolDbService->createNewIOV<RBCBoardSpecs>( prbcspecs, poolDbService->beginOfTime(), poolDbService->endOfTime(),
                                                  "RBCBoardSpecsRcd");
    else
      poolDbService->appendSinceTime<RBCBoardSpecs>( prbcspecs, poolDbService->currentTime(),
                                                     "RBCBoardSpecsRcd");
    
    if ( poolDbService->isNewTagRequest( "TTUBoardSpecsRcd" ) )
      poolDbService->createNewIOV<TTUBoardSpecs>( pttuspecs, poolDbService->beginOfTime(), poolDbService->endOfTime(),
                                                  "TTUBoardSpecsRcd");
    
    else
      poolDbService->appendSinceTime<TTUBoardSpecs>( pttuspecs, poolDbService->currentTime(),
                                                     "TTUBoardSpecsRcd");
    
  }
  
}

// ------------ ------------------------------------------------------------ ------------

void 
RPCTTConfMaker::addData( RBCBoardSpecs * specs )
{

  RBCBoardSpecs::RBCBoardConfig * board;
  
  for( int i=0; i < 30; i++) {
    
    board = new RBCBoardSpecs::RBCBoardConfig();

    (*m_in) >> (*board);
     
    specs->v_boardspecs.push_back( *board );
    
  }
  
}

void 
RPCTTConfMaker::addData( TTUBoardSpecs * specs )
{
  
  TTUBoardSpecs::TTUBoardConfig * board;
  
  for(int i=0; i < 3; i++){
    
    board= new TTUBoardSpecs::TTUBoardConfig();
    
    (*m_in) >> (*board);
    
    specs->m_boardspecs.push_back( *board );
    
  }
    
}


// ------------ method called once each job just before starting event loop  ------------
void 
RPCTTConfMaker::beginJob(const edm::EventSetup&)
{
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCTTConfMaker::endJob() {

}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCTTConfMaker);
