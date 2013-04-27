// $Id: $
#ifndef AOSORIO_DTTRIGGEOMUTILSEXT_H 
#define AOSORIO_DTTRIGGEOMUTILSEXT_H 1

// Include files

#include "DQM/DTMonitorModule/interface/DTTrigGeomUtils.h"
#include <DataFormats/GeometryVector/interface/LocalPoint.h>
#include <DataFormats/GeometryVector/interface/GlobalPoint.h>

/** @class DTTrigGeomUtilsExt DTTrigGeomUtilsExt.h aosorio/DTTrigGeomUtilsExt.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-06-16
 */
class DTTrigGeomUtilsExt : public DTTrigGeomUtils {
public: 
  /// Standard constructor
  DTTrigGeomUtilsExt( edm::ESHandle<DTGeometry> muonGeom, bool dirInDeg=true ); 

  virtual ~DTTrigGeomUtilsExt( ); ///< Destructor

  virtual LocalPoint trigLocalPos(const L1MuDTChambPhDigi* trig);

 protected:
  
 private:
  
  
  
};
#endif // AOSORIO_DTTRIGGEOMUTILSEXT_H
