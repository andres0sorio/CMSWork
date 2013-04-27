// -*- C++ -*-
//
// Package:    GoldenBit25
// Class:      GoldenBit25
// 
/**\class GoldenBit25 GoldenBit25.cc StudyL1Trigger/GoldenBit25/src/GoldenBit25.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andres Felipe Osorio Oliveros,512 1-009,+41227670491,
//         Created:  Tue Apr 13 00:57:43 CEST 2010
// $Id$
//
//


// system include files
#include <memory>
#include <map>
#include <bitset>
#include <iostream>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//L1 information
#include <DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h>
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

//
// class declaration
//

class GoldenBit25 : public edm::EDAnalyzer {
public:
  explicit GoldenBit25(const edm::ParameterSet&);
  ~GoldenBit25();
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  int m_techBitNb;
  std::string m_techBitName;
  edm::InputTag m_gtReadoutLabel;
  std::bitset<5> m_ttuDec;
  unsigned int m_pattern;

  bool m_debug;
  
  std::map<int,int> m_counterLS;
  
  std::ofstream * gzfileDump; 
  
};

GoldenBit25::GoldenBit25(const edm::ParameterSet& iConfig)

{
  
  //now do what ever initialization is needed
  m_gtReadoutLabel = iConfig.getParameter<edm::InputTag>("GTReadoutRcd");
  m_techBitNb      = iConfig.getUntrackedParameter<int>("TechBitNumber", 25);
  m_techBitName    = iConfig.getUntrackedParameter<std::string>("TechBitName");
  m_pattern        = iConfig.getUntrackedParameter<int>("Pattern", 0x04); 
  
  //0x04; // --X--
  //0x1C; // xxX--
  
  m_ttuDec.reset();

  gzfileDump = new std::ofstream( "l1Gtinformation.csv" );

  m_debug = false;

}


GoldenBit25::~GoldenBit25()
{
 
  if ( gzfileDump ) {
    gzfileDump->close();
    delete gzfileDump;
  }
  
}


void
GoldenBit25::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( m_gtReadoutLabel, gtRecord);
  
  if ( !gtRecord.isValid() ) {
    return;
  }

  unsigned int lumiSec = iEvent.luminosityBlock();
  
  for( int iebx=0; iebx<5; iebx++) {
    const TechnicalTriggerWord gtTTWord = gtRecord->technicalTriggerWord(iebx-2);
    m_ttuDec.set(4-iebx, gtTTWord[25] );
  }
  
  std::map<int,int>::iterator itrLS;
  itrLS = m_counterLS.find( lumiSec );
  
  if ( itrLS == m_counterLS.end() ) {
    //add new LS
    m_counterLS [ lumiSec ] = 0;
    
  }
  
  if ( m_ttuDec.to_ulong() == m_pattern ) {
    
    if (m_debug) std::cout << "matched" << m_ttuDec.to_string() << std::endl;
    
    itrLS = m_counterLS.find( lumiSec );
    (*itrLS).second += 1;
            
        
  }
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
GoldenBit25::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GoldenBit25::endJob() {

  //drop all the information

  std::map<int,int>::iterator itrLS;

  for( itrLS = m_counterLS.begin(); itrLS != m_counterLS.end(); ++itrLS ) {
    
    (* gzfileDump) << (*itrLS).first << '\t' << (*itrLS).second << '\n';
        
  }
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(GoldenBit25);
