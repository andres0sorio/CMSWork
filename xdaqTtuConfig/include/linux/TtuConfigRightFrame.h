// $Id: $
#ifndef COMMON_TTUCONFIGRIGHTFRAME_H 
#define COMMON_TTUCONFIGRIGHTFRAME_H 1

// Include files
#include <string>
#include <map>
#include <map>


//.. From xgi
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include <cgicc/HTMLClasses.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLElement.h>

//... From XDAQ
#include "xdaq/WebApplication.h"
#include "xdata/UnsignedLong.h"

//.. Local from Project
#include "RBCBoardSpecs.h"

/** @class TtuConfigRightFrame TtuConfigRightFrame.h common/TtuConfigRightFrame.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-03-02
 */
class TtuConfigRightFrame {
public: 
  /// Standard constructor
  TtuConfigRightFrame( ){ }; 
  
  TtuConfigRightFrame( const char * ); 

  virtual ~TtuConfigRightFrame( ); ///< Destructor

  void initialize( );

  void process( xgi::Input * in, xgi::Output * out );

  void process( xgi::Input * in, xgi::Output * out , int , const std::string & , RBCBoardSpecs *);
  
  bool findRbcBoardConfig( RBCBoardSpecs * , int , int, RBCBoardSpecs::RBCBoardConfig * & );
  
protected:
  
private:
  
  std::string m_name;

  std::map<int,std::string> m_sectors;
    
};
#endif // COMMON_TTUCONFIGRIGHTFRAME_H
