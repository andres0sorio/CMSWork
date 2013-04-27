// $Id: $
// Include files 



// local
#include "RBCBoardConfig.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RBCBoardConfig
//
// 2008-12-08 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RBCBoardConfig::RBCBoardConfig(  ) {
  
  m_PKey          =  0;
  m_Firmware      = -1;
  m_WheelId       = -9;
  m_MaskedOrInput = -1;
  m_ForcedOrInput = -1;
  m_Latency       = -1;
  m_MayorityLevel = -1;
  
}

RBCBoardConfig::RBCBoardConfig( int key )
{
  m_PKey          =  key;
  m_Firmware      = -1;
  m_WheelId       = -9;
  m_MaskedOrInput = -1;
  m_ForcedOrInput = -1;
  m_Latency       = -1;
  m_MayorityLevel = -1;
  
}

//=============================================================================
// Destructor
//=============================================================================
RBCBoardConfig::~RBCBoardConfig() {} 

//=============================================================================
