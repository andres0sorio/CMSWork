// $Id: $
#ifndef INCLUDE_XDAQTTUCONFIG_H 
#define INCLUDE_XDAQTTUCONFIG_H 1

// Include files
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

//.. From xdaq
#include "xdaq/Application.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationStub.h"
#include "xdaq/WebApplication.h" 
#include "xdaq/exception/Exception.h" 
#include "xdaq/NamespaceURI.h"
#include "xdaq/ApplicationGroup.h"

#include "xdata/UnsignedLong.h"

//.. From xgi
#include "xgi/Method.h"

//.. From extern/cgicc
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include <cgicc/HTMLClasses.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLElement.h>

//.. From xerces
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

//...For RbcControl
#include "RbcControlQuickSync.h"
#include "rpct/xdaqutils/XdaqDbServiceClient.h"
#include "rpct/xdaqlboxaccess/XdaqLBoxAccessClient.h"

typedef rpct::xdaqutils::XdaqDbServiceClient::RbcInfoVector rbcs;
typedef std::vector<rpct::RbcInfo>::iterator rbcs_iter;


#include <string.h>
#include <stdlib.h>

static char*                    gXmlFile               = 0;
static bool                     gDoNamespaces          = false;
static bool                     gDoSchema              = false;
static bool                     gSchemaFullChecking    = false;
static bool                     gDoCreate              = false;
static char*                    goutputfile            = 0;

// options for DOMWriter's features

static XMLCh*                   gOutputEncoding        = 0;
static bool                     gSplitCdataSections    = true;
static bool                     gDiscardDefaultContent = true;
static bool                     gUseFilter             = false;
static bool                     gFormatPrettyPrint     = false;
static bool                     gWriteBOM              = false;

static XercesDOMParser::ValSchemes    gValScheme       = XercesDOMParser::Val_Auto;

XERCES_CPP_NAMESPACE_USE

#include "StrX.hpp"
#include "DOMTreeErrorReporter.hpp"

//.. From project
#include "RBCBoardSpecsIO.h"
#include "TTUBoardSpecsIO.h"
#include "TtuConfigActionFrame.h"
#include "TtuConfigLeftFrame.h"
#include "TtuConfigCenterFrame.h"
#include "TtuConfigRightFrame.h"

/** @class xdaqTtuConfig xdaqTtuConfig.h include/xdaqTtuConfig.h
 *    
 *  RPC Tecnical Trigger Configuration Interface   
 *  Making life easier for everyone
 *
 *  @authors Andres Osorio, Flavio Loddo
 *  
 *  @date   2009-02-25
 */

class xdaqTtuConfig : public xdaq::Application {
public: 
  
  XDAQ_INSTANTIATOR();
	
  xdaqTtuConfig( xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
  
  void Default    (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void ActionBar  (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void LeftFrame  (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void CenterFrame(xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void RightFrame (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  
  void SetPreset              (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void SetTtuConfiguration    (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void SetRbcConfiguration    (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void UpdateTtuConfiguration (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void UpdateRbcConfiguration (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  void ExecuteConfiguration   (xgi::Input * in, xgi::Output * out)   throw (xgi::exception::Exception);
  
  void setApplicationURLS();
  
  bool ReadPresetConfig();
  
  bool ReadXMLPresetConfig();
  
  bool ParseTtuConfigurationFile( const char *);
  
  //bool ParseRbcConfigurationFile();
  
  void WriteRbcData(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
  
  void WriteRbcRegister( std::string , std::string , std::string , bool * );
  
  TtuConfigActionFrame   * m_ActionFrame;
  TtuConfigLeftFrame     * m_LeftFrame;
  TtuConfigCenterFrame   * m_CenterFrame;
  TtuConfigRightFrame    * m_RightFrame;
  
  TTUBoardSpecsIO * m_ttuconfig;
  RBCBoardSpecsIO * m_rbcconfig;
  
protected:
  
private:
  
  int m_numUrl;
  std::vector<std::string> m_app_urls;
  std::vector<std::string> m_moduleNames;
  
  bool m_debug;
  
  bool m_hasPreset;
  bool m_isTtuConfigured;
  bool m_ttufileready;
  bool m_rbcfileready;
  bool m_ttuconfigdone;
  
  int m_wheel;
    
  xdata::UnsignedLong m_PresetConfig;
  
  std::string m_ttufile;
  std::string m_rbcfile;
  std::string m_ttuscript;
  std::string m_default_cfg_path;

  std::ifstream * m_in;
  
  std::vector<std::string> m_ttuConfigFiles;
  std::vector<bool> m_useTtuConfigFiles;

  std::vector<DOMDocument *> m_xmlDocuments;

  std::vector<XercesDOMParser * > m_xmlParsers;
  
  RbcControlQuickSync * m_RbcControl;
  
  rbcs * m_ptr_Rbcs;
  rpct::xdaqutils::XdaqDbServiceClient dbServiceClient;	
  rpct::XdaqLBoxAccessClient lboxAccessClient;
  
    

};
#endif // INCLUDE_XDAQTTUCONFIG_H
