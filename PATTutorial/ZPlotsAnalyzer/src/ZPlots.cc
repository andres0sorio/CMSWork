// $Id: $
// Include files 



// local
#include "ZPlots.h"

//-----------------------------------------------------------------------------
// Implementation file for class : ZPlots
//
// 2009-01-31 : Andres Felipe Osorio Oliveros
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
ZPlots::ZPlots( edm::Service<TFileService> & fs , const char * opt ) {
  
  option = std::string( opt );
  
  tracksPt        = fs->make<TH1D>("trks-Pt"          , "Traks Pt" , 100 , 0 , 300 );
  emclustEt       = fs->make<TH1D>("emclust-Et"       , "EM cluster Et" , 100 , 0 , 100 );
  centraltrkPt    = fs->make<TH1D>("centrk-Pt"        , "Central Track Et" , 100 , 0 , 300 );
  pairPt          = fs->make<TH1D>("pair-Pt"          , "pair Pt" , 100 , 0 , 300 );
  pairM           = fs->make<TH1D>("pair-M"           , "pair Inv.Mass" , 100 , 70 , 120 );
  leptoncand1Eta  = fs->make<TH1D>("lep-cand1-eta"    , "cand1 eta" , 100 , -3 , 3 );
  leptoncand2Eta  = fs->make<TH1D>("lepton-cand2-eta" , "cand2 eta" , 100 , -3 , 3 );
  njets           = fs->make<TH1D>("njets"            , "N jets" , 50 , 0 , 50 );
  Etsumjets       = fs->make<TH1D>("etsum-jets"       , "Et sum jets" , 100 , 0 , 300 );
  

}

//=============================================================================
// Destructor
//=============================================================================
ZPlots::~ZPlots() {} 

//=============================================================================
