// $Id: $
#ifndef CONFIGCODE_RBCBOARDSPECSIO_H 
#define CONFIGCODE_RBCBOARDSPECSIO_H 1

// Include files

#include "RBCBoardSpecs.h"
#include "rpctSettingsXml.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ios>

/** @class RBCBoardSpecsIO RBCBoardSpecsIO.h ConfigCode/RBCBoardSpecsIO.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-12-16
 */
class RBCBoardSpecsIO : public RBCBoardSpecs {
public: 
  /// Standard constructor
  RBCBoardSpecsIO( );

  virtual ~RBCBoardSpecsIO( ); ///< Destructor
  
  friend std::istream& operator>>(std::istream &, RBCBoardConfig &);

  friend  DOMDocument& operator>>( DOMDocument &, RBCBoardSpecsIO  &);

  std::vector<Board> v_board;

protected:
  
private:
  
};
#endif // CONFIGCODE_RBCBOARDSPECSIO_H
