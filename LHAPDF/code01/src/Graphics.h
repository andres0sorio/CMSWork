// $Id: $
#ifndef GRAPHICS_H 
#define GRAPHICS_H 1

// Include files

#include "RootCommon.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TColor.h"

/** @class Graphics Graphics.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-09-19
 */

class Graphics {
public: 
  /// Standard constructor
  Graphics( );
    
  virtual ~Graphics( ); ///< Destructor
  
  TGraph * g1[10];
    
  TLegend * tleg_1;
  TLegend * tleg_2;

  void SetOptions();
  
protected:
  
private:

};
#endif // GRAPHICS_H
