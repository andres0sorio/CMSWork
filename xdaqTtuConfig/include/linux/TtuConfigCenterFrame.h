// $Id: $
#ifndef COMMON_TTUCONFIGCENTERFRAME_H 
#define COMMON_TTUCONFIGCENTERFRAME_H 1

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

//... From XDAQ
#include "xdaq/WebApplication.h"
#include "xdata/UnsignedLong.h"

//.. Local from Project
#include "TTUBoardSpecsIO.h"
#include "RbcControlQuickSync.h"

/** @class TtuConfigCenterFrame TtuConfigCenterFrame.h common/TtuConfigCenterFrame.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2009-03-02
 */
class TtuConfigCenterFrame {
public: 
  /// Standard constructor
  TtuConfigCenterFrame( ) { }; 
  
  TtuConfigCenterFrame( const char * ); 
  
  virtual ~TtuConfigCenterFrame( ); ///< Destructor
  
  void initialize( );
  
  void process( xgi::Input * in, xgi::Output * out, const std::string & );

  void process( xgi::Input * in, xgi::Output * out, 
                const std::string &, 
                const std::string &, 
		const std::string &,
                const std::vector<std::string> &, 
                TTUBoardSpecsIO *,
		RbcControlQuickSync * );
  
  void buildWheelForm( xgi::Output * out , const int & , const WheelConfig & );
  
  void buildRbcSelector( xgi::Output * out , const std::string & );
  
protected:
  
private:
  
  int m_maxwheels;
  std::string m_name;
  std::vector<int> m_wheelid;
  std::map<int,int> m_wheelttu;
  std::map<int,std::string> m_logictypes;
  std::string m_default_cfg_path;
};
#endif // COMMON_TTUCONFIGCENTERFRAME_H
