// $Id: HistoOutput.cc,v 1.1 2009/02/16 09:11:30 aosorio Exp $
// Include files 



// local
#include "HistoOutput.h"

//-----------------------------------------------------------------------------
// Implementation file for class : HistoOutput
//
// 2009-02-05 : Andres Felipe Osorio Oliveros
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
HistoOutput::HistoOutput( edm::Service<TFileService> & fservice, int bx, int wheel ) {
  
  std::ostringstream hname;
  
  for(int j=0; j < 12; ++j) {
    
    hname << "LayerHits.wheel." << (wheel-2) << ".sec." << j << ".BX." << bx ;

    hbylayer[j] = fservice->make<TH1D>(hname.str().c_str(),
                                       "Layer hits profile per sector",
                                       7, 0 ,7 );
    hname.str("");
    
  }

  
}
//=============================================================================
// Destructor
//=============================================================================
HistoOutput::~HistoOutput() {} 

//=============================================================================
