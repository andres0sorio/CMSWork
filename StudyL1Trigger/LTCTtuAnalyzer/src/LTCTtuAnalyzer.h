// -*- C++ -*-
//
// Package:    LTCTtuAnalyzer
// Class:      LTCTtuAnalyzer
// 
/**\class LTCTtuAnalyzer LTCTtuAnalyzer.cc StudyL1Trigger/LTCTtuAnalyzer/src/LTCTtuAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Felipe Osorio Oliveros
//         Created:  Tue Jun 23 20:27:15 CEST 2009
// $Id$
//
//


// system include files
#include <memory>
#include <bitset>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

//#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1.h"

#include "StudyL1Trigger/L1GtExtractInfo/interface/L1GtExtractedInfo.h"

//
// class declaration
//

class LTCTtuAnalyzer : public edm::EDAnalyzer {

public:
  
  explicit LTCTtuAnalyzer(const edm::ParameterSet&);
  ~LTCTtuAnalyzer();
  
private:
  
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------
  
  long double m_currentTime;
  long double m_previousTime;
  long double m_totalTime;
  long double m_elapsedTime;
  
  long double evaluateTime( unsigned int , unsigned int );
  
  void getRpcInfo( const edm::Event&, const edm::EventSetup& );

  int getBarrelLayer( const int & , const int &  );

  void getRpcTechTriggerBits( const edm::Event & , const edm::EventSetup& );
      
  TH1D * m_bxDist;
  TH1D * m_bxNumber;
  TH1D * m_bxNumberClose;
  TH1D * m_bxDistDiff;
  TH1D * m_hasTrigger;
  TH1D * m_trigRateHz;
  TH1D * m_trigRateDist;
  
  int m_bxFinal;
  int m_maxNBx;
  int m_bxNumMin;
  int m_bxNumMax;
  int m_useCompression;
  int m_writeMode;
  int m_precision;
  int m_maxRate;
  int m_flag;
  int m_readRpcTT;
  int m_maxttBits;

  std::vector<unsigned> m_ttBits;

  unsigned int m_nevtTrg;
  unsigned int m_firstEvt;
  unsigned int m_lastEvt;
  unsigned int m_nevt;
  
  edm::InputTag m_rpcDigiLabel;
  edm::InputTag m_ltcDigiLabel;
  edm::InputTag m_rpcTechTrig;
  
  int m_selFilter;
  bool m_applyFilter;
  int m_EvtWindow;
  std::vector<int> m_ntrigger;
  
  bool m_debug;
  
  L1GtExtractedInfo * m_infoObj;
  
};

