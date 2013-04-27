// $Id: $
#ifndef RPCTTCONFMAKER_H 
#define RPCTTCONFMAKER_H 1

// Include files

/** @class RPCTTConfMaker RPCTTConfMaker.h
 *  
 *
 *  @author Andres Felipe Osorio Oliveros
 *  @date   2008-12-13
 */
// system include files
#include <memory>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ios>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// DB includes
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"


#include "CondFormats/RPCObjects/interface/RBCBoardSpecs.h"
#include "CondFormats/DataRecord/interface/RBCBoardSpecsRcd.h"

#include "CondFormats/RPCObjects/interface/TTUBoardSpecs.h"
#include "CondFormats/DataRecord/interface/TTUBoardSpecsRcd.h"

#include "RPCTTConfigurator/RPCTTConfMaker/src/RBCBoardSpecsIO.h"
#include "RPCTTConfigurator/RPCTTConfMaker/src/TTUBoardSpecsIO.h"
//
// class declaration
//

class RPCTTConfMaker : public edm::EDAnalyzer {

public:
  explicit RPCTTConfMaker(const edm::ParameterSet&);
  ~RPCTTConfMaker();
  
  
private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  void addData( TTUBoardSpecs * );
  void addData( RBCBoardSpecs * );

  std::ifstream * m_in;
  
  
};

#endif // RPCTTCONFMAKER_H

