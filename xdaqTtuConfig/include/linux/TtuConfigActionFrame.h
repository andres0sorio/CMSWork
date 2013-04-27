// $Id: $
#ifndef COMMON_TTUCONFIGACTIONFRAME_H 
#define COMMON_TTUCONFIGACTIONFRAME_H 1

// Include files
#include <string>

//.. From xgi
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include <cgicc/HTMLClasses.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLElement.h>


/** @class TtuConfigActionFrame TtuConfigActionFrame.h common/TtuConfigActionFrame.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-03-02
 */
class TtuConfigActionFrame {
public: 
  /// Standard constructor
  TtuConfigActionFrame( ){ }; 

  TtuConfigActionFrame( const char * ); 

  virtual ~TtuConfigActionFrame( ); ///< Destructor
  
  void initialize( );
  
  void process( xgi::Input * in, xgi::Output * out , const std::string & );
  
protected:

private:

  std::string m_name;
  
};
#endif // COMMON_TTUCONFIGACTIONFRAME_H
