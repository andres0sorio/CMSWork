// $Id: $
#ifndef COMMON_TTUCONFIGLEFTFRAME_H 
#define COMMON_TTUCONFIGLEFTFRAME_H 1

// Include files
#include <string>
#include <map>
#include <vector>

//.. From xgi
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include <cgicc/HTMLClasses.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLElement.h>


/** @class TtuConfigLeftFrame TtuConfigLeftFrame.h common/TtuConfigLeftFrame.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-03-02
 */
class TtuConfigLeftFrame {
public: 
  /// Standard constructor
  TtuConfigLeftFrame( ) { }; 

  TtuConfigLeftFrame( const char * ); 
  
  virtual ~TtuConfigLeftFrame( ); ///< Destructor
  
  void initialize( );

  void process( xgi::Input * in, xgi::Output * out );
  
  bool drawBoxes( const std::string &, xgi::Output * out);
  

protected:
  
private:

  std::string m_name;
  std::map<int,std::string> m_sectors;
  
  
};
#endif // COMMON_TTUCONFIGLEFTFRAME_H
