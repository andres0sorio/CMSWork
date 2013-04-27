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

RbcControlQuickSync::RbcControlQuickSync( const std::map<std::string, int> & rbcInstances) {	
    
  m_RbcInstances = rbcInstances ;
  
  //... m_RegisterAddressFromName checked done by setRegisterMap
  
  int numReg = setRegisterMap("/nfshome0/rpcdev/TriDAS/rpct/xdaqTtuConfig/data/Registers.txt");
  
  std::cout << "RbcControlQuickSync> Total registers read from file: " << numReg << std::endl;
  
  m_isDone = false;
  m_sentTestCtrl = false;
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
  m_sectorid.push_back(9);
  m_sectorid.push_back(11);

  m_towerAssociation[1]  = std::string("near");
  m_towerAssociation[3]  = std::string("near");
  m_towerAssociation[11] = std::string("near");
  m_towerAssociation[5]  = std::string("far");
  m_towerAssociation[7]  = std::string("far");
  m_towerAssociation[9]  = std::string("far");
    
  m_sectors[1] = std::string("12-1");
  m_sectors[2] = std::string("2-3");
  m_sectors[3] = std::string("4-5");
  m_sectors[4] = std::string("6-7");
  m_sectors[5] = std::string("8-9");
  m_sectors[6] = std::string("10-11");
  
  int hasMask = readSectorMasks("/nfshome0/rpcdev/TriDAS/rpct/xdaqTtuConfig/data/RbcMasks.txt");
  
  std::cout << "RbcControlQuickSync> Number of RBCs to be masked: " << hasMask << std::endl; 
  
}

void RbcControlQuickSync::Default( xgi::Input * in, xgi::Output * out ,const std::string & method )
{
  
  //...Do quick syncronization
  
  *out << cgicc::h4("Select Wheel to send synchronization word (All=default)") << std::endl;
  
  *out << cgicc::form().set("name","wheelsel").set("method","GET").set("action", method) << std::endl;
  
  *out << "<p class=\"sectionA\">" << std::endl;
  *out << "<select name=\"Wheel\">" << std::endl;
  *out << "<option value=" << 100 << "> " << "all" << "</option>";
  
  for (int i=0; i < 5; ++i) {
    *out << "<option value=" << m_wheelid[i] << "> " << "W " << m_wheelid[i] << "</option>"
         << std::endl;
  }
  
  *out << "</select>" << std::endl;
  
  //...Tower selection
  *out << "<input type=\"radio\" name=\"tower\" value=\"all\" checked=\"checked\" />All" << std::endl;
  *out << "<input type=\"radio\" name=\"tower\" value=\"near\" />Near" << std::endl;
  *out << "<input type=\"radio\" name=\"tower\" value=\"far\" />Far" << std::endl;

  *out << "</p>";

  *out << "<p class=\"sectionA\">";
  
  if ( m_sentTestCtrl ) {
    *out << "<input type=\"checkbox\" name=\"testpat\" value=\"ON\" /> <span class=\"highlightWarning\"> TestPattern </span>" << std::endl;
    *out << "<input type=\"checkbox\" name=\"rmtestpat\" value=\"ON\" /> <span class=\"highlightWarning\"> Remove TestPattern </span>" << std::endl;
  }
  else 
    *out << "<input type=\"checkbox\" name=\"testpat\" value=\"ON\" /> TestPattern" << std::endl;
  
  *out << "<input type=submit value=\"Send\" />" << std::endl;
  *out << cgicc::form() << std::endl;
  
  *out << "</p>" << std::endl;
  
    
 
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

int RbcControlQuickSync::readSectorMasks( const char * infile )
{

  int hasMask = 0;
  std::bitset<6> mask;
  
  m_in = new std::ifstream();
  
  m_in->open(infile);
  
  if(!m_in->is_open()) {
    
    std::cout << "Data> cannot open file" << std::endl;
    return -1;
    
  } else {
    
    while(1) {
      
      int wheel;
      int rbcs[6];
      
      if ( m_in->fail()) break;
      (*m_in) >> wheel 
	      >> rbcs[0] 
	      >> rbcs[1] 
	      >> rbcs[2] 
	      >> rbcs[3] 
	      >> rbcs[4]
	      >> rbcs[5];
      //if ( name.size() <= 0 ) break;
      
      for(int i = 0; i < 6; ++i)
	mask.set( i, rbcs[i]);
      
      m_RbcMasks[ wheel ] = mask;
      
      if ( mask.any() ) ++hasMask;
      
    }
    
  }
  
#ifdef _AOTEST

  int counter(0);
  std::map<int, std::bitset<6> >::iterator itr;
  for(itr = m_RbcMasks.begin(); itr != m_RbcMasks.end(); ++itr) {
    std::cout << counter << " " 
              << (*itr).first << " ";
    for(int i = 0; i < 6; ++i)
      std::cout << (*itr).second[i] << " ";
    
    std::cout << std::endl;
    ++counter;
  }
  
#endif
  
  m_in->close();
  
  delete m_in;
  
  return hasMask;
  
}

bool RbcControlQuickSync::isSectorInTower( int sector, const std::string & tower ) 
{
  
  if ( m_towerAssociation[sector] == tower || tower == std::string("all") ) {
    return true;
  }
  else
    return false;
  
  return false;

}
