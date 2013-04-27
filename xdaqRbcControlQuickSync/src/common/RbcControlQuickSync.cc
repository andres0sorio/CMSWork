// $Id: $
// Include files 



// local
#include "RbcControlQuickSync.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RbcControlQuickSync
//
// 2009-06-14 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
XDAQ_INSTANTIATOR_IMPL(RbcControlQuickSync)

RbcControlQuickSync::RbcControlQuickSync(xdaq::ApplicationStub * s)
	throw (xdaq::exception::Exception): xdaq::Application(s)
#ifndef _AOTEST
  ,dbServiceClient(this), lboxAccessClient(this)
#endif
{	
	
  xgi::bind(this,&RbcControlQuickSync::Default,   "Default");
  xgi::bind(this,&RbcControlQuickSync::writeData, "writeData");
  

#ifndef _AOTEST

  rbcs* myrbcs = dbServiceClient.getAllRbcsInfo();
  
  for (rbcs::iterator irbc = myrbcs->begin(); irbc != myrbcs->end(); ++irbc) {
    m_RbcInstances[(std::string)(irbc->bag.getLinkBoxName())] = irbc->bag.getXdaqAppInstance();
  }
  
#endif
  
  int numReg = setRegisterMap("/opt/CMS/XDAQ-SL5/TriDAS/xdaq-app/xdaqRbcControlQuickSync/data/Registers.txt");
  
  std::cout << "RbcControlQuickSync> Total registers read from file: " << numReg << std::endl;
  
  m_isDone = false;
  m_wheel  = -100;
  
  m_wheelid.push_back(-2);
  m_wheelid.push_back(-1);
  m_wheelid.push_back( 0);
  m_wheelid.push_back( 1);
  m_wheelid.push_back( 2);

  m_sectorid.push_back(1);
  m_sectorid.push_back(3);
  m_sectorid.push_back(5);
  m_sectorid.push_back(7);
  m_sectorid.push_back(8);
  m_sectorid.push_back(11);
  
}

void RbcControlQuickSync::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{

	out->getHTTPResponseHeader().addHeader("Content-Type", "text/html");
	*out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
	*out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::link().set("rel","stylesheet").
    set("href","/xdaq-app/xdaqRbcControlQuickSync/images/ttu_style.css").
    set("type","text/css") << std::endl;
	*out << cgicc::title("Simple Web Form") << std::endl;
	
	// This method can be invoked using Linux 'wget' command
	// e.g http://lxcmd101:1972/urn:xdaq-application:lid=23/setParameter?value=24
  
  //...Nice header:
  
  *out << "<div id=\"TopTitle\">" << std::endl;
  *out << cgicc::h1("RPC Technical Trigger") << std::endl;
  *out << "<p class=\"top\"" << std::endl;
  *out << cgicc::a("WikiDOC").set("href","https://twiki.cern.ch/twiki/bin/view/CMS/RPComm").set("target","_blank").
    set("class","top") << std::endl;
  *out << cgicc::a("Contact").set("href","http://www.cern.ch").set("target","_blank").
    set("class","top") << std::endl;
  *out << "v.1.0" << std::endl;
  *out << "</p></div>" << std::endl;
  
  //...Do quick syncronization

  std::string method = toolbox::toString("/%s/writeData",getApplicationDescriptor()->getURN().c_str());
  
  *out << cgicc::h4("Please select Wheel to send synchronization word (default=all): Gol_Reg[6]=1") << std::endl;
  
  *out << cgicc::form().set("name","wheelsel").set("method","GET").set("action", method).set("target","right") << std::endl;
  
  *out << "<p>" << std::endl;
  *out << "<select name=\"Wheel\">" << std::endl;
  *out << "<option value=" << 100 << "> " << "all" << "</option>";
  
  for (int i=0; i < 5; ++i) {
    *out << "<option value=" << m_wheelid[i] << "> " << "W " << m_wheelid[i] << "</option>"
         << std::endl;
  }
  
  *out << "</select>" << std::endl;
  *out << "<input type=submit value=\"Send!\" />" << std::endl;
  *out << cgicc::form() << std::endl;
  *out << "</p>" << std::endl;
 
}

void RbcControlQuickSync::writeData(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception)
{
  
  try
  {
    cgicc::Cgicc cgi(in);
    std::ostringstream secStr;
    std::ostringstream wheelStr;
		std::vector<int>::const_iterator secItr;
    std::vector<int>::const_iterator wheelItr;
    
    bool syncword[8];
    syncword[0] = 0;
    syncword[1] = 0;
    syncword[2] = 0;
    syncword[3] = 0;
    syncword[4] = 0;
    syncword[5] = 0;
    syncword[6] = 1;
    syncword[7] = 0;
    
		// retrieve value and update exported variable
    m_wheel = cgi["Wheel"]->getIntegerValue();
    
    std::cout << m_wheel << std::endl;
    
    if ( m_wheel == 100 ) {
      
      for( wheelItr = m_wheelid.begin(); wheelItr != m_wheelid.end(); ++wheelItr ){
        
        wheelStr << (*wheelItr);
        
        for ( secItr = m_sectorid.begin(); secItr != m_sectorid.end(); ++secItr) {
          
          secStr << (*secItr);
          WriteRegister( std::string ("Gol"), wheelStr.str(), secStr.str(), syncword );
          secStr.str("");
          
        }
        
        wheelStr.str("");
      } 
      
    } else {
      
      wheelStr << m_wheel;
      
      for ( secItr = m_sectorid.begin(); secItr != m_sectorid.end(); ++secItr) {
        
        secStr << (*secItr);
        WriteRegister( std::string ("Gol"), wheelStr.str(), secStr.str(), syncword );
        secStr.str("");
      }
      
    }
    
    m_isDone = true;
    
		//re-display form page 
		this->Default(in,out);		
  }
  catch (const std::exception & e)
  {
    m_isDone = false;
    XCEPT_RAISE(xgi::exception::Exception, e.what());
  }	
  
}

void RbcControlQuickSync::WriteRegister( std::string selRegister, std::string wheel, std::string sector, bool registerBool[8] )
{
  
  std::string linkBoxName = "LBB_RB" + wheel + "_S" + sector;         
  
  int address             = m_RegisterAddressFromName[selRegister];

  int registerInt         = IntFromBool( registerBool );
  
#ifndef _AOTEST
  int instanceNumber      = m_RbcInstances[linkBoxName];
#else
  int instanceNumber      = -101;
#endif
  
  std::cout << "==============================WRITING================================"  << std::endl;
  std::cout << "Register......................" << selRegister                          << std::endl;
  std::cout << "Wheel........................." << wheel                                << std::endl;
  std::cout << "Sector........................" << sector                               << std::endl;
  
  std::cout << "Instance Number..............." << instanceNumber                       << std::endl;
  std::cout << "Register Address.............." << address                              << std::endl;
  std::cout << "Integer Register Written......" << registerInt                          << std::endl;
  
  std::cout << "Operation.....................writeRbcRegister(\"" 
            << linkBoxName << "\"," 
            << address << ","
            << registerInt  <<"," 
            << instanceNumber <<")"<< std::endl;  
  
  std::cout << "Hexadecimal Register Written.." << std::hex << registerInt << std::dec <<std::endl; 
  
  std::cout << "Byte Written..................{";
  
  for( int i=0; i<8; ++i) {
    std::cout << registerBool[i]; 
    if(i!=7) std::cout << ",";
  }
  
  std::cout << "}" << std::endl;            
  
  //....send write message to lbbox
  
#ifndef _AOTEST
  lboxAccessClient.writeRbcRegister(linkBoxName,address,registerInt,instanceNumber);
#endif
  
}

int RbcControlQuickSync::IntFromBool( bool selRegister[8] )
{
  
  return ( selRegister[0]+
           selRegister[1]*2+
           selRegister[2]*4+
           selRegister[3]*8+
           selRegister[4]*16+
           selRegister[5]*32+
           selRegister[6]*64+
           selRegister[7]*128 ); 
}

bool RbcControlQuickSync::BoolFromInt( int integer, int i )
{
  
  for(int j=0; j<i ;j++){ integer = integer/2; }
  return integer%2;
  
}

int RbcControlQuickSync::setRegisterMap( const char * infile )
{

  int numReg = 0;

  m_in = new std::ifstream();
  
  m_in->open(infile);
  
  if(!m_in->is_open()) {
    
    std::cout << "Data> cannot open file" << std::endl;
    return -1;
    
  } else {
    
    while(1) {
      
      int value;
      std::string name;
      
      if ( m_in->fail()) break;
      (*m_in) >> name >> value ;
      if ( name.size() <= 0 ) break;
      m_RegisterAddressFromName[ name ] = value;
      
    }
        
  }

#ifdef _AOTEST
  int counter(0);
  std::map<std::string,int>::iterator itr;
  for(itr = m_RegisterAddressFromName.begin(); itr != m_RegisterAddressFromName.end(); ++itr) {
    std::cout << counter << " " 
              << (*itr).first << " " << (*itr).second 
              << std::endl;
    ++counter;
  }
#endif
 
  numReg = m_RegisterAddressFromName.size();
  
  m_in->close();

  delete m_in;
  
  return numReg;
  
}

