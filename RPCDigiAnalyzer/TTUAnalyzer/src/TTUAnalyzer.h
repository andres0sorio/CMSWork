// -*- C++ -*-
//
// Package:    TTUAnalyzer
// Class:      TTUAnalyzer
// 
/**\class TTUAnalyzer TTUAnalyzer.cc RPCDigiAnalyzer/TTUAnalyzer/src/TTUAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andres Osorio
//         Created:  Thu Feb 26 22:15:47 CET 2009
// $Id$
//
//

//

// system include files

#include <memory>
#include <fstream>
#include <iostream>
#include <map>

// Include files From CMSSW
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"

#include "DataFormats/RPCDigi/interface/RPCDigi.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"


//...RPCDigiSimLink
#include <DataFormats/Common/interface/DetSetVector.h>
#include <SimDataFormats/RPCDigiSimLink/interface/RPCDigiSimLink.h>


#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH2D.h"

// Include from Local
#include "RPCDigiAnalyzer/TTUAnalyzer/src/HistoOutput.h"


//............

class TTUAnalyzer : public edm::EDAnalyzer {
  
public:
  explicit TTUAnalyzer(const edm::ParameterSet&);
  ~TTUAnalyzer();
  
  class WheelMap {
    
  public:
    
    WheelMap() {};
    WheelMap(int bx, int wheel) { 
      
      m_bx = bx;
      m_wheel = wheel;
      
      for(int i=0; i < 12; ++i)
        for(int j=0; j <  6; ++j) wheelmap[i][j] = 0;
      
      arrangesec[0]  = 9;
      arrangesec[1]  = 8;
      arrangesec[2]  = 7;
      arrangesec[3]  = 6;
      arrangesec[4]  = 5;
      arrangesec[5]  = 4;
      arrangesec[6]  = 3;
      arrangesec[7]  = 2;
      arrangesec[8]  = 1;
      arrangesec[9]  = 12;
      arrangesec[10] = 11;
      arrangesec[11] = 10;
      
    }
    
    ~WheelMap() {
      for(int i=0; i < 12; ++i)
        for(int j=0; j <  6; ++j) wheelmap[i][j] = 0;
    };
    
    int m_bx;
    int m_wheel;
    std::vector<int> sector;
    std::vector<int> layer;
    int wheelmap[12][6];
    int arrangesec[12];
    
    void printmaps( std::ofstream * _os ) 
    {
      
      (*_os) << "map for: bx " << m_bx << '\n';
      (*_os) << " map for: wheel " << m_wheel << '\n';
      (*_os) << "  total digis: " << sector.size() << " " << layer.size() << '\n';
      
      int maxdig = sector.size();
      
      for (int i=0; i < maxdig; ++i){
        wheelmap[ sector[i] ][ layer[i] ] = 1;
      }
      
      (*_os) << "  ";
      for(int j=0; j <  12; ++j) (*_os ) << arrangesec[j] << " : ";
      (*_os) << '\n';
      
      for(int i=5; i >= 0; --i) {
        (*_os) << "  ";
        for(int j=0; j < 12; ++j) { (*_os ) << wheelmap[ arrangesec[j] - 1 ][i] << "   "; }
        (*_os) << '\n';
        
      }
      
      
    };
    
    void fillhistograms( HistoOutput * hout ) {
      
      for(int i=0; i < 6; ++i) {
        for(int j=0; j < 12; ++j) {
          hout->hbylayer[arrangesec[j] - 1]->Fill ( i, wheelmap[ arrangesec[j] - 1 ][i]);
          
        }
      }
      
    };
    
    WheelMap& operator+=(const WheelMap &rhs) 
    {
      
      //make an or with another Wheel Map
      for(int i=0; i < 6; ++i)
        for(int j=0; j < 12; ++j)
          (*this).wheelmap[j][i] += rhs.wheelmap[j][i];
            
      return (*this);
            
    }
    


  };
  
private:
  
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  int getBarrelLayer(const int &, const int &);
    
  int m_nevts;
  int m_ndigi[6];
  int m_EvtSelection;
  int m_EvtSelType;
  int m_BxWindow;
  
  std::string m_evtselInfile;
  
  std::map<int, HistoOutput *>  m_houtput;
  
  TH1D * m_allbx;
  TH1D * m_avgbx[5];
  TH1D * m_NDigis;
  TH2D * m_sectorVsblayer[5];
  
  TH1D * topSecbx;
  TH1D * bottomSecbx;

  std::ofstream *out;
  std::ofstream *outbxw;

  std::ifstream *iss;
  
  std::map<int,WheelMap*>::iterator m_itr;
  
  std::map<int,HistoOutput*>::iterator m_itrHO;
  
  std::map<int,TTUAnalyzer::WheelMap*> m_wheelmapsPerBx;
  
  std::vector<int> m_bxevt[5];
  
  unsigned int m_minDigis;

  edm::InputTag m_rpcDigiLabel;
    
  std::vector<int> m_selectedEvts;
  
  bool m_noinputfile;
  




};

