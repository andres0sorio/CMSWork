// $Id: $
#ifndef ZPLOTS_H 
#define ZPLOTS_H 1

// Include files
#include <string>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"

/** @class ZPlots ZPlots.h
 *  
 *
 *  @author Andres Felipe Osorio Oliveros
 *  @date   2009-01-30
 */
class ZPlots {
public: 
  /// Standard constructor
  ZPlots( ) { }; 

  ZPlots( edm::Service<TFileService> & , const char * ); 
  
  virtual ~ZPlots( ); ///< Destructor
  
  //...Declare here the histograms
  
  //... basic data sample
  TH1D * tracksPt;
  TH1D * emclustEt;
  TH1D * centraltrkPt;
  
  //... for Z selection
  TH1D * pairPt;
  TH1D * pairM;
  TH1D * leptoncand1Eta;
  TH1D * leptoncand2Eta;
  
  //... for kinematic selection

  TH1D * njets;
  TH1D * Etsumjets;
  
protected:

private:

  std::string option;
  
};
#endif // ZPLOTS_H
