// $Id: $
// Include files 



// local
#include "TtuConfigCenterFrame.h"


//-----------------------------------------------------------------------------
// Implementation file for class : TtuConfigCenterFrame
//
// 2009-03-02 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TtuConfigCenterFrame::TtuConfigCenterFrame( const char * name ) {

  m_maxwheels = 5;
  m_name = std::string(name);
  
  m_wheelttu[-2] = 1;
  m_wheelttu[-1] = 3;
  m_wheelttu[ 0] = 2;
  m_wheelttu[ 1] = 1;
  m_wheelttu[ 2] = 3;
  
  m_wheelid.push_back(-2);
  m_wheelid.push_back(-1);
  m_wheelid.push_back( 0);
  m_wheelid.push_back( 1);
  m_wheelid.push_back( 2);

  m_logictypes[1] = std::string("LocalOR");
  m_logictypes[2] = std::string("GlobalOR");
  m_logictypes[3] = std::string("CombinedOR");

  m_default_cfg_path= std::string("/nfshome0/rpcdev/bin/config/ttuOri/");
  
  
}
//=============================================================================
// Destructor
//=============================================================================
TtuConfigCenterFrame::~TtuConfigCenterFrame() {} 

//=============================================================================
void TtuConfigCenterFrame::initialize() 
{

  
}

void TtuConfigCenterFrame::process(  xgi::Input * in, xgi::Output * out , const std::string &method )
{
  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eFrames) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::link().set("rel","stylesheet").
    set("href","/rpct/xdaqTtuConfig/images/ttu_style.css").
    set("type","text/css") << std::endl;
  *out << cgicc::title("Center Frame") << std::endl;

  
  //... TTU Configuration Panel
  
  *out <<  "<div id=\"Content\">" << std::endl;

  *out << cgicc::h3("TTU XML configuration files ") << std::endl;
  
  *out << "<p> <span class=\"shadow\"> path: " << m_default_cfg_path << "</span> </p>" << std::endl;
  
  *out << cgicc::h4("Ttu Optolinks:") << std::endl;
  *out << cgicc::form().set("method","GET").set("action", method).set("target","center") << std::endl;
  *out << "<p>";
  *out << cgicc::input().set("type","text").set("name","ttufile").set("value", "ttuEnable.xml") << std::endl;
  *out << "</p>";
  
  *out << cgicc::h4("Wheels:") << std::endl;
  *out << "<p>";
  *out << cgicc::input().set("type","text").set("name","wm2file").set("value", "ttuConfigsWM2.xml") << std::endl;
  *out << "</p><p>";
  
  *out << cgicc::input().set("type","text").set("name","wm1file").set("value", "ttuConfigsWM1.xml") << std::endl;
  *out << "</p><p>";
  
  *out << cgicc::input().set("type","text").set("name","w0file").set("value",  "ttuConfigsW0.xml") << std::endl;
  *out << "</p><p>";
  
  *out << cgicc::input().set("type","text").set("name","wp1file").set("value", "ttuConfigsWP1.xml") << std::endl;
  *out << "</p><p>";
  
  *out << cgicc::input().set("type","text").set("name","wp2file").set("value", "ttuConfigsWP2.xml") << std::endl;
  *out << "</p>";
  
  *out << cgicc::h4("Ttu Backplane:") << std::endl;

  *out << "<p>";
  *out << cgicc::input().set("type","text").set("name","bpfile").set("value", "ttuConfigsBackplane.xml") << std::endl;
  *out << "</p>";

  *out << cgicc::h4("Ttu Fast Configuration (FastConfig/Bottom/Pointing):") << std::endl;

  *out << "<p>";
  *out << cgicc::input().set("type","text").set("name","fastfile").set("value", "ttuConfigsFast.xml") << std::endl;
  *out << "</p>";
  
  *out << cgicc::h4("RBC XML configuration file(s) - not functional") << std::endl;
  *out << cgicc::input().set("type","text").set("name","rbcfile").set("value", "/data/") << std::endl;
  *out << cgicc::input().set("type","submit").set("value","Upload")  << std::endl;
  *out << cgicc::form() << std::endl;
  
  *out <<  "</div>" << std::endl;

  *out << cgicc::html() << std::endl;

}

void TtuConfigCenterFrame::process(  xgi::Input * in, xgi::Output * out, 
                                     const std::string & methodOne, 
                                     const std::string & methodTwo, 
				     const std::string & methodThr, 
				     const std::vector<std::string> & filenames , 
                                     TTUBoardSpecsIO   * ttubasicconf,
				     RbcControlQuickSync * quicksync
				     )
{
  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::link().set("rel","stylesheet").
    set("href","/rpct/xdaqTtuConfig/images/ttu_style.css").
    set("type","text/css") << std::endl;
  *out << cgicc::title("Center Frame") << std::endl;
  
  //... TTU Configuration Panel
  
  *out <<  "<div id=\"Content\">" << std::endl;
  
  *out << cgicc::form().set("name","ttumain").set("method","GET").set("action", methodOne) << std::endl;
  
  *out << cgicc::h3("TTU Configuration") << std::endl;
  
  *out << cgicc::h4("Ttu Optolinks:") << std::endl;

  std::vector<std::string>::const_iterator namesItr;
  for( namesItr = filenames.begin(); namesItr != filenames.end(); ++namesItr ) {
    *out << "<p>";
    *out << "<span class=\"shadow\">Preset configuration file: " << (*namesItr) << " found </span> </p>" << std::endl;
    *out << "<p>";
  }

  *out << "<input type=\"checkbox\" name=\"usefile1\"" << "\" value=" << "\"ON\" checked " << " /> Apply this configuration" << std::endl;
  *out << "</p>" << std::endl;
  

  std::map<int,int>::const_iterator itr;
  
  *out <<  cgicc::comment() << " Information for each wheel" <<  cgicc::comment() <<  std::endl;
  
  for ( int i=0 ; i < m_maxwheels; ++i ) {
    
    int wheelIdx = m_wheelid[i];
    char label[30];
    sprintf(label,"TTU: Wheel %d:", wheelIdx );
    
    *out << cgicc::h4(label) << std::endl;
    
    std::ostringstream usefile;
    usefile << "usefile" << (i+2);

    *out << "<p>";
    *out << "<input type=\"checkbox\" name=\"" << usefile.str().c_str() << "\"" << "\" value=" << "\"ON\" checked " << " /> Apply this configuration" << std::endl;
    *out << "</p>" << std::endl;
 
    itr = m_wheelttu.find( wheelIdx );
    
    WheelConfig wheelConfig;
    
    ttubasicconf->getWheelConfig( wheelIdx , wheelConfig );
    
    buildWheelForm( out , wheelIdx , wheelConfig );
    
    usefile.str("");
    
  }

  int maxfiles = filenames.size();

  *out << cgicc::h4("Ttu Backplane:") << std::endl;
  
  *out << "<p>";
  *out << "<span class=\"shadow\">Preset configuration file: " << filenames[maxfiles-2] << " found </span> </p>" << std::endl;
  *out << "<p>";
  *out << "<input type=\"checkbox\" name=\"usefile7\"" << "\" value=" << "\"ON\" checked " << " /> Apply this configuration" << std::endl;
  *out << "</p>" << std::endl;

  *out << cgicc::h4("Ttu Fast Configuration:") << std::endl;
  
  *out << "<p>";
  *out << "<span class=\"shadow\">Preset configuration file: " << filenames[maxfiles-1] << " found </span> </p>" << std::endl;
  *out << "<p>";
  *out << "<input type=\"checkbox\" name=\"usefile8\"" << "\" value=" << "\"ON\" checked " << " /> Apply this configuration" << std::endl;
  *out << "</p>" << std::endl;
  
  *out << "<input type=submit value=\"Update\" />" << std::endl;
  
  *out << cgicc::form() << std::endl;
  
  //...........
  
  buildRbcSelector( out , methodTwo );

  //.......... Quick Sync

  quicksync->Default( in, out, methodThr );
  
  *out <<  "</div>" << std::endl;

  *out << cgicc::html() << std::endl;
  
}


void TtuConfigCenterFrame::buildWheelForm( xgi::Output * out, 
                                           const int & wheelid,
                                           const WheelConfig & wheelconf )
{
  
  *out <<  "<p>" << std::endl;
  *out <<  "</p>" << std::endl;
        
}

void TtuConfigCenterFrame::buildRbcSelector( xgi::Output * out , const std::string & method )
{
  
  *out << cgicc::h4("Please select Wheel to configure RBC boards") << std::endl;

  *out << cgicc::form().set("name","rbcsel").set("method","GET").set("action", method).set("target","right") << std::endl;
  
  *out << "<p>" << std::endl;
  
  *out << "<select name=\"Wheel\">" << std::endl;
  for (int i=0; i < 5; ++i) {
    *out << "<option value=" << m_wheelid[i] << "> " << "W." << m_wheelid[i] << "</option>"
         << std::endl;
  }
  
  *out << "</select>" << std::endl;
  *out << "<input type=submit value=\"Configure\" />" << std::endl;
  *out << cgicc::form() << std::endl;

  *out << "</p>" << std::endl;
  
}

