// $Id: $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/interface/RPCData.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RPCData
//
// 2008-11-18 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RPCData::RPCData(  ) {
  
  m_wheel = 10;
  m_sec1  = 50;
  m_sec2  = 50;
  
  m_orsignals = new RBCInput();
  
}
//=============================================================================
// Destructor
//=============================================================================
RPCData::~RPCData() {
  if(m_orsignals) delete m_orsignals;
} 

//=============================================================================

std::istream& operator>>(std::istream &istr , RPCData & rhs) 
{
  
  (istr) >> rhs.m_wheel;
  for(int k=0; k < 6; ++k)
  {
    (istr) >> rhs.m_sec1 >> rhs.m_sec2;
    (istr) >> *(rhs.m_orsignals);
  }

  return istr;
    
}

std::ostream& operator<<(std::ostream& ostr , RPCData & rhs) 
{
  
  ostr << rhs.m_wheel;
  for(int k=0; k < 6; ++k)
  {
    ostr << rhs.m_sec1 << '\t' <<  rhs.m_sec2 << '\n';
    ostr << *(rhs.m_orsignals);
  }

  return ostr;
  
}

