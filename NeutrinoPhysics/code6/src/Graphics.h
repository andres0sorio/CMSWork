// $Id: $
#ifndef GRAPHICS_H 
#define GRAPHICS_H 1

// Include files

#include "RootCommon.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH1F.h"

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
  
  TGraph * g1;
  TGraph * g2;
  TGraph * g3;
  
  void SetOptions();
  
protected:
  
private:

};
#endif // GRAPHICS_H
