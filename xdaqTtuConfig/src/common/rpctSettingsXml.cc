// $Id: $
// Include files 



// local
#include "rpctSettingsXml.h"

//-----------------------------------------------------------------------------
// Implementation file for class : rpctSettingsXml
//
// 2008-12-16 : Andres Osorio
//-----------------------------------------------------------------------------



std::ostream& operator << (std::ostream &ostr, Board &rhs)
{
  
  std::vector<Device>::iterator itr;
  std::vector<Register>::iterator itr2;
  
  ostr << rhs.name << std::endl;
  
  for( itr = rhs.v_device.begin(); itr != rhs.v_device.end(); ++itr) {
    
    ostr << (*itr).name << std::endl;
    
    for( itr2 = ((*itr).v_register).begin(); itr2 != ((*itr).v_register).end(); ++itr2 ) {
      ostr << (*itr2).regName << " " << (*itr2).regValue << std::endl;
    }
  }
  
  return ostr;

}
