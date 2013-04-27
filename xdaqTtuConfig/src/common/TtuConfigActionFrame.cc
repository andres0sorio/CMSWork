// $Id: $
// Include files 



// local
#include "TtuConfigActionFrame.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TtuConfigActionFrame
//
// 2009-03-02 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TtuConfigActionFrame::TtuConfigActionFrame( const char *name ) {
  
  m_name = std::string(name);
  
}
//=============================================================================
// Destructor
//=============================================================================
TtuConfigActionFrame::~TtuConfigActionFrame() {} 

//=============================================================================
void TtuConfigActionFrame::initialize() 
{
  

  
}

void TtuConfigActionFrame::process(  xgi::Input * in, xgi::Output * out, 
                                     const std::string & methodOne )
{
  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eFrames) << std::endl;
  *out << cgicc::html() << cgicc::html() <<  cgicc::head() << std::endl;
  *out << cgicc::link().set("rel","stylesheet").
    set("href","/rpct/xdaqTtuConfig/images/ttu_style.css").
    set("type","text/css") << std::endl;
  *out << cgicc::title("Action Bar") << std::endl;
  *out << cgicc::head() << std::endl;
  
  //....
  
  *out << "<div id=\"TopTitle\">" << std::endl;
  *out << cgicc::h1("RPC Technical Trigger") << std::endl;
  *out << "<p class=\"top\"" << std::endl;
  *out << cgicc::a("RbcControl").set("href","http://vmepcs2g18-13:1975").set("target","_blank").
    set("class","top") << std::endl;
    *out << cgicc::a("IIAccess").set("href","http://pcrpct01:8080/iiaccess/faces/iiaccess.jspx").set("target","_blank").
    set("class","top") << std::endl;
  *out << cgicc::a("WikiDOC(pdf)").set("href","file:///nfshome0/rpcdev/rpct/xdaqRbcControlQuickSync/doc/CMS_TtuInUsc.pdf").set("target","_blank").
    set("class","top") << std::endl;
  *out << cgicc::a("Contact").set("href","http://www.cern.ch").set("target","_blank").
    set("class","top") << std::endl;
  *out << "v.1.0" << std::endl;
  *out << "</p></div>" << std::endl;

  //...Actions: Check status; Execute Configuration; Export Configuration; Report
  
  *out << "<div id=\"ActionBar\">" << std::endl;
  
  *out << "<table border=\"0\">" << std::endl;
  *out << "<tr>" << std::endl;
  
  *out << "<td>";
  *out << cgicc::form().set("method","GET").set("target","actions") << std::endl;
  *out << "<input type=submit value=\"Check status\" />" << std::endl;
  *out << cgicc::form() << std::endl;
  *out << "</td>" << std::endl;
  
  *out << "<td>";
  *out << cgicc::form().set("method","GET").set("action", methodOne).set("target","actions") << std::endl;
  *out << "<input type=submit value=\"Execute Configuration\" />" << std::endl;
  *out << cgicc::form() << std::endl;
  *out << "</td>" << std::endl;
  
  *out << "<td>";
  *out << cgicc::form().set("method","GET").set("target","actions") << std::endl;
  *out << "<input type=submit value=\"Export Configuration\" />" << std::endl;
  *out << cgicc::form() << std::endl;
  *out << "</td>"<< std::endl;
  
  *out << "</tr></table>" << std::endl;
  
  *out <<  "</div>" << std::endl;
  
  *out << cgicc::html() << std::endl;
  
}
