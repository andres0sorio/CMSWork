// $Id: $
// Include files 

// local
#include "RBCBoardSpecsIO.h"

#include "StrX.hpp"
#define X(str) StrX(str).unicodeForm()

//-----------------------------------------------------------------------------
// Implementation file for class : RBCBoardSpecsIO
//
// 2008-12-16 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RBCBoardSpecsIO::RBCBoardSpecsIO( ) {

}
//=============================================================================
// Destructor
//=============================================================================
RBCBoardSpecsIO::~RBCBoardSpecsIO() {} 

//=============================================================================
std::istream& operator>>(std::istream & istr, RBCBoardSpecsIO::RBCBoardConfig & rhs)
{
  
  std::string logitype;
  
  istr >> rhs.m_Firmware      ;
  istr >> rhs.m_WheelId       ;
  istr >> rhs.m_Latency       ;
  istr >> rhs.m_MayorityLevel ;
  istr >> logitype ;
  
  //...m_MaskedOrInput is a vector of size 30
  for(int i=0; i < 30; ++i) {
    int mask(0);
    istr >> mask;
    rhs.m_MaskedOrInput.push_back(mask);
  }
  
  //...m_ForcedOrInput is a vector of size 30
  for(int i=0; i < 30; ++i) {
    int force(0);
    istr >> force;
    rhs.m_ForcedOrInput.push_back(force);
  }
  
  rhs.m_LogicType = logitype;
  
  return istr;
  
}

//=============================================================================
DOMDocument& operator>>(DOMDocument &istr, RBCBoardSpecsIO &rhs){
  
  DOMNodeList * boards = istr.getElementsByTagName( X("device") );
  
  int maxelements = (int) boards->getLength();
  
  std::cout << "device: " << maxelements << std::endl;
  
  for (int i=0; i< maxelements; ++i) {
    
    DOMElement * elmboard = dynamic_cast<DOMElement *>( boards->item(i) );
    
    //rhs.m_Firmware       = 1000;
    //rhs.m_WheelId        = -2;
    //rhs.m_Latency        = 25;
    //rhs.m_MayorityLevel  = 3;
    //rhs.m_LogicType      = std::string( StrX( elmboard->getAttribute(X("id")) ).localForm() );
    
    //loop here over Tab Registers
    DOMNodeList * ttuTabRegist = elmboard->getElementsByTagName( X("tabRegister") );
    
    int maxtabreg = (int)ttuTabRegist->getLength();
    
    for (int k=0; k < maxtabreg; ++k ) {
      
      DOMElement * elmTabRegist = dynamic_cast<DOMElement *>( ttuTabRegist->item(k) );
      DOMNodeList * ttuTabRegistValues = elmTabRegist->getElementsByTagName( X("valuesTab") );
      
      int maxtabval = ttuTabRegistValues->getLength();
      
      std::cout << std::string( StrX( elmTabRegist->getAttribute( X("regName") )).localForm() ) << '\n';
      std::cout << std::string( StrX( elmTabRegist->getAttribute( X("size") )).localForm() ) << '\n';
      std::cout << std::string( StrX( elmTabRegist->getAttribute( X("sector") )).localForm() ) << '\n';

      for( int m=0; m < maxtabval; ++m) {
        
        DOMElement *value = dynamic_cast<DOMElement *>( ttuTabRegistValues->item(m) );
        
        std::cout <<  std::string( StrX(value->getAttribute( X("index")) ).localForm() ) << '\n';
        std::cout << std::string( StrX(value->getAttribute( X("regValue")) ).localForm() ) << '\n';
        
      }
      
      std::cout << "done with tab registers" << std::endl;
      
    }//
    
  }
  
  return istr;
  
}
