// $Id: $
// Include files 



// local
#include "TtuConfigLeftFrame.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TtuConfigLeftFrame
//
// 2009-03-02 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TtuConfigLeftFrame::TtuConfigLeftFrame( const char * name ) {
  
  m_name = std::string(name);

  m_sectors[1] = std::string("12-1");
  m_sectors[2] = std::string("2-3");
  m_sectors[3] = std::string("10-11");

  m_sectors[4] = std::string("4-5");
  m_sectors[5] = std::string("6-7");
  m_sectors[6] = std::string("8-9");

  
}
//=============================================================================
// Destructor
//=============================================================================
TtuConfigLeftFrame::~TtuConfigLeftFrame() {} 

//=============================================================================
void TtuConfigLeftFrame::initialize() 
{
  
  
  
  
}

void TtuConfigLeftFrame::process( xgi::Input * in, xgi::Output * out ) 
{
  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eFrames) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::title("LeftFrame") << std::endl;
  *out << cgicc::link().set("rel","stylesheet").
    set("href","/rpct/xdaqTtuConfig/images/ttu_style.css").
    set("type","text/css") << std::endl;
  
  //... Status panel
  std::string src("/xdaqTtuConfig/data/defaultstatus.txt");
  
  *out <<  "<div id=\"Status\">" << std::endl;
  
  *out << cgicc::h3("TTU/RBC status") << std::endl;
  *out <<  "<div id=\"StatusCode\">" << std::endl;
  
  *out <<  "<span class=\"codeON\"> Masked</span> <span class=\"codeNR\"> Sync <span class=\"codeOFF\"> 000"
       << std::endl;
  *out <<  "</div>" << std::endl;

  bool status = drawBoxes(src, out );
    
  *out <<  "</div>" << std::endl;
  
  *out << cgicc::html() << std::endl;
  
}

bool TtuConfigLeftFrame::drawBoxes( const std::string & src, xgi::Output * out)
{
  
  std::cout << src << std::endl;
  
  std::map<int,std::string>::const_iterator itr;
  
  for(int i=0; i < 5; ++i ) {
 
    *out << "<p>" << std::endl;
    *out << "Status for wheel:" << (i-2) << "</br>" << std::endl;
    *out << "<table border=0>" << std::endl;
    
    for( itr = m_sectors.begin(); itr != m_sectors.end(); ++itr) {
      
      *out << "<tr>" << std::endl;
      *out << "<td class=\"topics\">" << (*itr).second << "</td>" << std::endl;
      *out << "<td>" << 1 << "</td></tr>" << std::endl;
      
    }
    
    *out << "</table>" << std::endl;
    *out << "</p>" << std::endl;
  }
  
  return true;
  
}

