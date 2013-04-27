// $Id: $
#ifndef CONFIGCODE_TTUBOARDSPECSIO_H 
#define CONFIGCODE_TTUBOARDSPECSIO_H 1

// Include files

#include "TTUBoardSpecs.h"
#include "rpctSettingsXml.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <map>

/** @class TTUBoardSpecsIO TTUBoardSpecsIO.h ConfigCode/TTUBoardSpecsIO.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-12-16
 */

void removeWhite (std::string &str);

void removeAllWhite (std::string &str);

class TTUBoardSpecsIO : public TTUBoardSpecs {
public: 
  /// Standard constructor
  TTUBoardSpecsIO( ); 

  virtual ~TTUBoardSpecsIO( ); ///< Destructor

  friend std::istream& operator>>(std::istream &, TTUBoardConfig   &);

  friend DOMDocument&  operator>>(DOMDocument  &, TTUBoardSpecsIO  &);

  friend std::ostream& operator<<(std::ostream &, TTUBoardSpecsIO &);

  std::vector<Board> v_board;
  
  void getWheelConfig( int , WheelConfig & );

protected:
  
private:

  std::map<int,std::string> m_wheelttu;
  
  std::map<int,int> m_wheelAssoc;
  
  std::map<int,std::string> m_wheelTriggAssoc;
  
};
#endif // CONFIGCODE_TTUBOARDSPECSIO_H
