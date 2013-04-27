// $Id: $
// Include files 



// local
#include "DTTrigGeomUtilsExt.h"

#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"

// Geometry & Segment
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/DTGeometry/interface/DTChamber.h"
#include "Geometry/DTGeometry/interface/DTSuperLayer.h"
#include "Geometry/DTGeometry/interface/DTLayer.h"
#include "Geometry/DTGeometry/interface/DTTopology.h"


//-----------------------------------------------------------------------------
// Implementation file for class : DTTrigGeomUtilsExt
//
// 2011-06-16 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
DTTrigGeomUtilsExt::DTTrigGeomUtilsExt( edm::ESHandle<DTGeometry> muonGeom , bool dirInDeg) 
  : DTTrigGeomUtils( muonGeom , false ) {
  
}

//=============================================================================
// Destructor
//=============================================================================

DTTrigGeomUtilsExt::~DTTrigGeomUtilsExt() {} 

//=============================================================================

LocalPoint DTTrigGeomUtilsExt::trigLocalPos(const L1MuDTChambPhDigi* trig) {

  float x_local = trigPos( trig );
  LocalPoint localPos( x_local, 0.0, 0.0 );
  
  return localPos;
  
}
