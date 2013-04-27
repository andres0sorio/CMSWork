// $Id: $
// Include files 



// local
#include "TTUBoardConfig.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TTUBoardConfig
//
// 2008-12-08 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TTUBoardConfig::TTUBoardConfig(  ) : RPCTechTriggerConfig() {

  m_Firmware      = -1;
  m_LengthOfFiber = -1;
  m_Delay         = -1;
  m_Wheel1Id      = -1;
  m_Wheel2Id      = -1;
  m_MaskedSector  = -1;
  m_ForcedSector  = -1;
  
}

TTUBoardConfig::TTUBoardConfig( int key, 
                                int run, 
                                int runtype, 
                                int trigmode ) 
  : RPCTechTriggerConfig( run, runtype, trigmode ) {
  
  m_PKey          = key;
  m_Firmware      = -1;
  m_LengthOfFiber = -1;
  m_Delay         = -1;
  m_Wheel1Id      = -1;
  m_Wheel2Id      = -1;
  m_MaskedSector  = -1;
  m_ForcedSector  = -1;
  
}

//=============================================================================
// Destructor
//=============================================================================
TTUBoardConfig::~TTUBoardConfig() {
  
  m_RBCFKey.clear();
  
} 

//=============================================================================
void TTUBoardConfig::addfkey( const int & key )
{
  m_RBCFKey.push_back( key );
}
