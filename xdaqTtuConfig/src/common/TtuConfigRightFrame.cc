// $Id: $
// Include files 



// local
#include "TtuConfigRightFrame.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TtuConfigRightFrame
//
// 2009-03-02 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TtuConfigRightFrame::TtuConfigRightFrame( const char *name ) {

  m_name = std::string(name);

  m_sectors[1] = std::string("12-1");
  m_sectors[2] = std::string("2-3");
  m_sectors[3] = std::string("4-5");
  m_sectors[4] = std::string("6-7");
  m_sectors[5] = std::string("8-9");
  m_sectors[6] = std::string("10-11");

}
//=============================================================================
// Destructor
//=============================================================================
TtuConfigRightFrame::~TtuConfigRightFrame() {} 

//=============================================================================
void TtuConfigRightFrame::initialize() 
{
  
  

  
}

void TtuConfigRightFrame::process(  xgi::Input * in, xgi::Output * out )
{
  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eFrames) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::title("Right Frame") << std::endl;
  *out << cgicc::link().set("rel","stylesheet").
    set("href","/rpct/xdaqTtuConfig/images/ttu_style.css").
    set("type","text/css") << std::endl;

  //... RBC Configuration Panel
  
  *out <<  "<div id=\"Content\">" << std::endl;
  
  *out << cgicc::h3("RBC Configuration") << std::endl;
  
  *out <<  "</div>" << std::endl;
  
  *out << cgicc::html() << std::endl;
  
}

void TtuConfigRightFrame::process(  xgi::Input * in, xgi::Output * out , int wheel , 
                                    const std::string & methodOne , RBCBoardSpecs * rbcspecs )
{
  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eFrames) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::link().set("rel","stylesheet").
    set("href","/rpct/xdaqTtuConfig/images/ttu_style.css").
    set("type","text/css") << std::endl;
  *out << cgicc::title("Right Frame") << std::endl;
  
  //... RBC Configuration Panel
  
  char label[60];
  sprintf(label,"RBC configuration for Wheel: %d", wheel);
  
  *out <<  "<div id=\"Content\">" << std::endl;

  *out << cgicc::h3(label) << std::endl;

  *out << cgicc::form().set("name","rbcmain").set("method","GET").
    set("action", methodOne)  << std::endl;
  
  //... loop over the 6 sector RBCs
  
  std::map<int,std::string>::const_iterator sector_itr;
  
  RBCBoardSpecs::RBCBoardConfig * rbcboard;
    
  for( sector_itr = m_sectors.begin();
       sector_itr != m_sectors.end();
       ++sector_itr ) {
    
    bool status = findRbcBoardConfig( rbcspecs , wheel, (*sector_itr).first , rbcboard );
    
    if (!status) {
      std::cout << "TtuConfigRightFrame> board config not found" << std::endl;
    }
    
    std::ostringstream title;
    title << "RBC boards for sectors " << (*sector_itr).second;
    
    *out << cgicc::h4(title.str()) << std::endl;
    
    std::ostringstream maylev;
    maylev << "MayorityLevel." << wheel << "." << (*sector_itr).second;
    
    *out << "<p>" << std::endl;
    *out << "Mayority Level:" << std::endl;
    *out << "  <input type=\"text\" name=\"" << maylev.str() 
         << "\" value=" << (*rbcboard).m_MayorityLevel << ">" << std::endl;
    *out << "</p>" << std::endl;
    
    std::ostringstream pulsew;
    pulsew << "PulseWidth." << wheel << "." << (*sector_itr).second;
    
    *out << "<p>" << std::endl;
    *out << "Pulse Width:" << std::endl;
    *out << "  <input type=\"text\" name=\"" << pulsew.str() 
         << "\" value=" << (*rbcboard).m_Latency << ">" << std::endl;
    *out << "</p>" << std::endl;
    *out << "<p>" << std::endl;
    *out << "Mask:</p>" << std::endl;
    *out << "<p>" << std::endl;
    
    for( int i=0; i < 16; ++i ) {
      
      std::ostringstream masks;
      masks << "masks." << (i+1) << "." << wheel << "." << (*sector_itr).second;
      std::ostringstream checkon;
      if ( rbcboard->m_MaskedOrInput[i] ) checkon << "\"ON\" checked";
      else checkon << "\0FF\"";
      
      *out <<  "<input type=\"checkbox\" name=\"" << masks.str() 
           << "\" value=" << checkon.str() << " />" << std::endl;
      
    }
    
    *out << "</p>" << std::endl;
    *out << "<p>" << std::endl;
    *out << "Force:</p>" << std::endl;
    *out << "<p>" << std::endl;
    
    for( int i=0; i < 16; ++i ) {
      
      std::ostringstream force;
      force << "force." << (i+1) << "." << wheel << "." << (*sector_itr).second;
      std::ostringstream checkon;
      if ( rbcboard->m_ForcedOrInput[i] ) checkon << "\"ON\" checked";
      else checkon << "\"OFF\" ";
      
      *out <<  "<input type=\"checkbox\" name=\"" << force.str() 
           << "\" value=" << checkon.str() << " />" << std::endl;
      
    }
    
    *out << "</p>" << std::endl;
    
  }
  
  *out << "<input type=submit value=\"Update\" />" << std::endl;
  
  *out << "</form>" << std::endl;
  
  *out <<  "</div>" << std::endl;

  *out << cgicc::html() << std::endl;
  
}


bool TtuConfigRightFrame::findRbcBoardConfig( RBCBoardSpecs * inspecs , int wheel, int sectors, 
                                              RBCBoardSpecs::RBCBoardConfig * & outconfig ) 
{
  
  std::vector<RBCBoardSpecs::RBCBoardConfig>::iterator itr;
  
  for(itr  = inspecs->v_boardspecs.begin();
      itr != inspecs->v_boardspecs.end();
      ++itr ) {
    
    if ( (*itr).m_WheelId == wheel ) {
      // TODO: once the specs store the id of each RBC the find method should locate the board
      // for the moment just returning the first board for each wheel
      outconfig = &(*itr);
      return true;
    }
    
  }
  
  return true;
    
}
