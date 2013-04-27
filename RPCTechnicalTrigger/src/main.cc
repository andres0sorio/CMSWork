// $Id: 
// Include files 

#include "L1Trigger/RPCTechnicalTrigger/src/RPCTechnicalTrigger.h"
#include "L1Trigger/RPCTechnicalTrigger/src/TTUTrackingAlg.h"
#include "L1Trigger/RPCTechnicalTrigger/src/AccessConfigMySQL.h"
#include "L1Trigger/RPCTechnicalTrigger/src/EDM.h"

 
int main(int iargv, const char **argv) {
  
  if(iargv < 3 ) {
    std::cout << "usage : emulate> [datain] [logic]" << std::endl;
    return 0;
  }
  
  const char *in  = argv[1];
  const char *logic = argv[2];

  //... Test a RBCEmulator

  bool status(true);
  
  //for (int i=0; i < 80000; ++i ) {
    
  RBCEmulator * rbcsec12 = new RBCEmulator( in , logic );
  status = rbcsec12->initialise();
  if (!status) return 0;
  rbcsec12->emulate();
  rbcsec12->printinfo();
  std::cout << "deleting..." << std::endl;
  delete rbcsec12;
  
  //}
  
  std::cout << "Up to here, all goes well" << std::endl;
  
  //... Now test a Wheel object:
  
  TTUInput *_ttuin = new TTUInput();
  
  //for (int i=0; i < 10000; ++i ) {
  RPCWheel * wp1 = new RPCWheel( 1 , in, logic );
  status = wp1->initialise();
  if (!status) return 0;
  wp1->emulate();
  wp1->createWheelMap();
  wp1->printinfo();
  wp1->retrieveWheelMap( (*_ttuin) );
  delete wp1;
  //}
  
  std::cout << "Up to here, all goes well" << std::endl;

  ///... Test the TTU Units
  RPCTTU * ttu1 = new RPCTTU( 3 , in, logic, "TrackingAlgo", 1);
  status = ttu1->initialise();
  if (!status) return 0;
  ttu1->printinfo();
  //ttu1->emulate();
  //ttu1->getresults();
  delete ttu1;
  
  std::cout << "Up to here, all goes well" << std::endl;
  
  ///... Test the TTUTrackingAlg
  
  TTUTrackingAlg * trkalgo = new TTUTrackingAlg();
  trkalgo->process( (*_ttuin) );
  delete trkalgo;
  
  delete _ttuin;

  //... Test access to ToyDB
  //for (int i=0; i < 1000000; ++i ) {
  AccessConfigMySQL * config = new AccessConfigMySQL("configfile.txt");
  //config->read();
  config->setwritemode( AccessConfigMySQL::recreate );
  config->write();
  config->read();
  delete config;
  //}


  //... Test RPCTechnical Trigger
  edm::ParameterSet *par = new edm::ParameterSet();
  edm::Event *ievt = new edm::Event();
  edm::EventSetup *iset = new edm::EventSetup();
  
  RPCTechnicalTrigger * rpctt = new RPCTechnicalTrigger( *par );
  rpctt->analyze( *ievt, *iset );
  
  return 1;
  
}
