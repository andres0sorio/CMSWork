// $Id: $
// Include files 



// local
#include "TDataSets.h"

ClassImp(TDataSets)

//-----------------------------------------------------------------------------
// Implementation file for class : TDataSets
//
// 2011-11-04 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TDataSets::TDataSets(  ) {

}
//=============================================================================
// Destructor
//=============================================================================
TDataSets::~TDataSets() {

} 

//=============================================================================

TDataSets::TDataSets(int id, std::string &nm) {

  Id = id;
  name = nm;
  graph = new TGraphAsymmErrors();
  
}

TGraphAsymmErrors *  TDataSets::getGraph() { 
  
  return graph; 
  
}

void TDataSets::setMarker(int marker, int colour, float size ) {
  
  graph->SetMarkerStyle(marker); //to change the style of the marker
  graph->SetMarkerColor(colour); // to change the color of the marker
  graph->SetMarkerSize(size); //to change the size of the marker
  graph->SetLineColor(colour); //to change the color of the line (error bars)
  
}
