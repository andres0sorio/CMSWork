// $Id: $
// Include files 



// local
#include "TTUBoardSpecsIO.h"

#include "StrX.hpp"
#define X(str) StrX(str).unicodeForm()


//-----------------------------------------------------------------------------
// Implementation file for class : TTUBoardSpecsIO
//
// 2008-12-16 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TTUBoardSpecsIO::TTUBoardSpecsIO(  ) {
  
  m_wheelttu[-2] = std::string("TTU_1");
  m_wheelttu[-1] = std::string("TTU_3");
  m_wheelttu[ 0] = std::string("TTU_2");
  m_wheelttu[ 1] = std::string("TTU_1");
  m_wheelttu[ 2] = std::string("TTU_3");
 
  m_wheelAssoc[ -2 ] = -1;
  m_wheelAssoc[ -1 ] = 1;
  m_wheelAssoc[  0 ] = 1;
  m_wheelAssoc[  1 ] = 1;
  m_wheelAssoc[  2 ] = -1;

  m_wheelTriggAssoc[ -2 ] = std::string("TTUTRIG9");
  m_wheelTriggAssoc[ -1 ] = std::string("TTUTRIG8");
  m_wheelTriggAssoc[  0 ] = std::string("TTUTRIG8");
  m_wheelTriggAssoc[  1 ] = std::string("TTUTRIG8");
  m_wheelTriggAssoc[  2 ] = std::string("TTUTRIG9");
   
}
//=============================================================================
// Destructor
//=============================================================================
TTUBoardSpecsIO::~TTUBoardSpecsIO() {} 

//=============================================================================
void TTUBoardSpecsIO::getWheelConfig(int wid, WheelConfig & wheelconf ) {
  
  std::vector<Board>::iterator    boardItr;
  std::vector<Device>::iterator   deviceItr;
  std::vector<Register>::iterator registerItr;

  bool m_debug = false;

  wheelconf.v_Optoregister.clear();
  wheelconf.v_Triggregister.clear();
  
  if ( m_debug ) std::cout << "ttuspecs: board size(): " << v_board.size() << std::endl;
  
  for ( boardItr = v_board.begin(); boardItr != v_board.end(); ++boardItr) {
    
    if ( (*boardItr).name == m_wheelttu[wid] ) {
      
      for ( deviceItr = (*boardItr).v_device.begin(); deviceItr != (*boardItr).v_device.end(); ++deviceItr) {
	
	std::string deviceName( (*deviceItr).name );
	
	removeWhite( deviceName );
	removeAllWhite( deviceName );
	
	if ( m_debug ) std::cout << deviceName << std::endl;
	
	if ( m_wheelAssoc[wid] > 0 && 
	     ( deviceName == std::string("TTUOPTO2") || 
	       deviceName == std::string("TTUOPTO3") ||
	       deviceName == std::string("TTUOPTO4")  ) ) {
	  
	  int counter(0);

	  for ( registerItr = (*deviceItr).v_register.begin(); registerItr != (*deviceItr).v_register.end(); ++registerItr) {
	    wheelconf.v_Optoregister.push_back( *registerItr );
	    ++counter;
	  }
	  
	  if ( m_debug ) std::cout << "found device for wheel: " << wid << " " << counter << std::endl;

	} else if ( m_wheelAssoc[wid] < 0 && 
		    ( deviceName == std::string("TTUOPTO5") || 
		      deviceName == std::string("TTUOPTO6") ||
		      deviceName == std::string("TTUOPTO7")  ) ) {
	  
	  int counter(0);

	  for ( registerItr = (*deviceItr).v_register.begin(); registerItr != (*deviceItr).v_register.end(); ++registerItr) {
	    wheelconf.v_Optoregister.push_back( *registerItr );
	    ++counter;
	  }
	  
	  if ( m_debug ) std::cout << "found device for wheel: " << wid << " " << counter << std::endl;
	  
	} else if (  deviceName == m_wheelTriggAssoc[wid] ) {
	  
	  int counter(0);
	  
	  for ( registerItr = (*deviceItr).v_register.begin(); registerItr != (*deviceItr).v_register.end(); ++registerItr) {
	    wheelconf.v_Triggregister.push_back( *registerItr );
	    ++counter;
	  }

	} else {
	  
	  if ( m_debug ) std::cout << "getWheelConfig> device not found " << deviceName << " " << m_wheelAssoc[wid] << std::endl;
	  
	}
      }
    }
  }
  
  std::cout << "getWheelConfig> total registers added for Wheel " 
	    <<  wid << " : " 
	    << wheelconf.v_Optoregister.size() << '\t' 
	    << wheelconf.v_Triggregister.size() << std::endl;
  
}

std::istream& operator>>(std::istream &istr, TTUBoardSpecsIO::TTUBoardConfig &rhs)
{
  
  std::string logitype;
  
  istr >> rhs.m_runId         ;
  istr >> rhs.m_runType       ;
  istr >> rhs.m_triggerMode   ;
  istr >> rhs.m_Firmware      ;
  istr >> rhs.m_LengthOfFiber ;
  istr >> rhs.m_Delay         ;
  istr >> rhs.m_MaxNumWheels  ;
  istr >> rhs.m_Wheel1Id      ;
  istr >> rhs.m_Wheel2Id      ;
  istr >> logitype            ;
  
  //...m_MaskedSectors is a vector of size 12
  for(int i=0; i < 12; ++i) {
    int mask(0);
    istr >> mask;
    rhs.m_MaskedSectors.push_back(mask);
  }
  
  //...m_ForcedSectors is a vector of size 12
  for(int i=0; i < 12; ++i) {
    int force(0);
    istr >> force;
    rhs.m_ForcedSectors.push_back(force);
  }
  
  rhs.m_LogicType = logitype;
  
  return istr;
  
}

DOMDocument& operator>>(DOMDocument &istr, TTUBoardSpecsIO &rhs) {

  bool m_debug = false;

  if ( m_debug ) std::cout << "------------------" << std::endl;

  DOMNodeList * boards = istr.getElementsByTagName( X("board") );
  
  int maxelements = (int) boards->getLength();
  
  if ( m_debug ) std::cout << "boards: " << maxelements << std::endl;
    
  for (int i=0; i< maxelements; ++i) {
    
    Board * br = new Board();
    
    DOMElement * elmboard = dynamic_cast<DOMElement *>( boards->item(i) );
    
    (*br).id = std::string( StrX( elmboard->getAttribute(X("id")) ).localForm() );
    (*br).name = std::string( StrX( elmboard->getAttribute(X("name")) ).localForm() );
    
    DOMNodeList * devices = elmboard->getElementsByTagName( X("device") );
    
    int maxdevices = devices->getLength();
    
    if ( m_debug ) std::cout << "devices: " << maxdevices << std::endl;
    
    for (int j=0; j < maxdevices; ++j) {
        
        DOMElement * elmdevices = dynamic_cast<DOMElement *>( devices->item(j) );
         
        Device * dv = new Device();
        
        (*dv).id = std::string( StrX( elmdevices->getAttribute(X("id")) ).localForm() );
        (*dv).name = std::string( StrX( elmdevices->getAttribute(X("name")) ).localForm() );
        
        //Loop here over Registers
        
        DOMNodeList * ttuRegist = elmdevices->getElementsByTagName( X("register") );
        
        int maxreg = ttuRegist->getLength();
        
        if ( m_debug ) std::cout << "max reg " << maxreg << std::endl;
        
        for (int k=0; k < maxreg; ++k ) {
          
          DOMElement * elmttuRegist = dynamic_cast<DOMElement *>( ttuRegist->item(k) );
          
          Register * rg = new Register();
           
           (*rg).regName  = std::string( StrX( elmttuRegist->getAttribute( X("regName") )).localForm() );
           (*rg).regValue = std::string( StrX( elmttuRegist->getAttribute( X("regValue") )).localForm() );
           (*dv).v_register.push_back( (*rg) );
           if ( m_debug ) std::cout << "done with registers" << std::endl;
         }
           
         //loop here over Tab Registers
         
         DOMNodeList * ttuTabRegist = elmdevices->getElementsByTagName( X("tabRegister") );
         
         int maxtabreg = (int)ttuTabRegist->getLength();
         
         for (int k=0; k < maxtabreg; ++k ) {
           
           DOMElement * elmTabRegist = dynamic_cast<DOMElement *>( ttuTabRegist->item(k) );
           DOMNodeList * ttuTabRegistValues = elmTabRegist->getElementsByTagName( X("valuesTab") );
           
           int maxtabval = ttuTabRegistValues->getLength();
           
           TabRegister * trg = new TabRegister();
           
           (*trg).regName = std::string( StrX( elmTabRegist->getAttribute( X("regName") )).localForm() );
           (*trg).size = std::string( StrX( elmTabRegist->getAttribute( X("size") )).localForm() );
                 
           for( int m=0; m < maxtabval; ++m) {
        
             DOMElement *value = dynamic_cast<DOMElement *>( ttuTabRegistValues->item(m) );
             
             TabRegister::ValuesTab * trgval = new TabRegister::ValuesTab();
             
             (*trgval).index = std::string( StrX(value->getAttribute( X("index")) ).localForm() );
             (*trgval).regValue = std::string( StrX(value->getAttribute( X("regValue")) ).localForm() );
             
             (*trg).v_valuesTab.push_back( (*trgval) );
           }
           
           (*dv).v_tabregister.push_back( (*trg) );
           if ( m_debug ) std::cout << "done with tab registers" << std::endl;
         
         }//

         (*br).v_device.push_back( (*dv) );
         
    }
       
    if ( m_debug ) std::cout << "done with devices" << std::endl;
  
    rhs.v_board.push_back(*br);
      
  }

  std::cout <<  "v board SIZE: " <<  rhs.v_board.size() << std::endl;

  return istr;
  
}

std::ostream& operator<<(std::ostream &ostr, TTUBoardSpecsIO &rhs ){

  ostr << "----------------------------------------------------------------" << std::endl;
  ostr << " Board registers: " << std::endl;
  
  std::vector<Board>::iterator itr;
  
  for ( itr = rhs.v_board.begin(); itr != rhs.v_board.end(); ++itr) {
    
    ostr << "board: " << (*itr).id << std::endl;
    ostr << (*itr) << std::endl;

  }
   
  ostr << "----------------------------------------------------------------" << std::endl;

  return ostr;
 
}

/*
 * Remove white spaces from std::string
 * Author: Danny Battison
 * Contact: gabehabe@hotmail.com
 */

void removeWhite (std::string &str)
{
    std::string temp;
    for (unsigned int i = 0; i < str.length(); i++)
        if (str[i] == ' ' && str[i-1] == ' ') {}
        else temp += str[i];
    str = temp;
}

void removeAllWhite (std::string &str)
{
    std::string temp;
    for (unsigned int i = 0; i < str.length(); i++)
        if (str[i] != ' ') temp += str[i];
    str = temp;
}
