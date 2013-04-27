// $Id: $
#ifndef DBOBJECT_TTUBOARDCONFIG_H 
#define DBOBJECT_TTUBOARDCONFIG_H 1

// Include files
#include "RPCTechTriggerConfig.h"
#include <vector>

/** @class TTUBoardConfig TTUBoardConfig.h dbobject/TTUBoardConfig.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-12-08
 */
class TTUBoardConfig : public RPCTechTriggerConfig {
public: 
  /// Standard constructor
  TTUBoardConfig( ); 

  TTUBoardConfig( int, int, int, int ); 
  
  virtual ~TTUBoardConfig( ); ///< Destructor

  void addfkey( const int & );
    
  int m_PKey;
  int m_Firmware;
  int m_LengthOfFiber;
  int m_Delay;
  int m_MaxNumWheels;
  int m_Wheel1Id;
  int m_Wheel2Id;
  int m_MaskedSector;
  int m_ForcedSector;
  
  std::vector<int> m_RBCFKey;
  
  std::string m_LogicType;
  
protected:
  
private:

};
#endif // DBOBJECT_TTUBOARDCONFIG_H
