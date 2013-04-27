// $Id: $
#ifndef DBOBJECT_RBCBOARDCONFIG_H 
#define DBOBJECT_RBCBOARDCONFIG_H 1

// Include files
#include <string>
#include <vector>

/** @class RBCBoardConfig RBCBoardConfig.h dbobject/RBCBoardConfig.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-12-08
 */

class RBCBoardConfig {
public: 
  /// Standard constructor
  RBCBoardConfig( );
  
  RBCBoardConfig( int );
  
  virtual ~RBCBoardConfig( ); ///< Destructor
  
  int m_PKey;
  int m_Firmware;
  int m_WheelId;
  int m_MaskedOrInput;
  int m_ForcedOrInput;
  int m_Latency;
  int m_MayorityLevel;
  
  std::string m_LogicType;
  
protected:
  
private:
  
};
#endif // DBOBJECT_RBCBOARDCONFIG_H
