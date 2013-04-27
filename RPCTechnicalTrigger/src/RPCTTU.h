// $Id: $
#ifndef RPCTTU_H 
#define RPCTTU_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/src/RPCWheel.h"
#include "L1Trigger/RPCTechnicalTrigger/interface/TTUConfiguration.h"

#include <map>

/** @class RPCTTU RPCTTU.h
 *  
 *  This class performs the following tasks [ref 2]:
 *
 *
 *    - find a single or multiple muon tracks
 *    - find length of each track
 *    - produce a wheel level trigger
 *
 *  The default algorithm is implemented is TrackingAlg [ref 2].
 *
 *  ref 2: <EM>"A configurable Tracking Algorithm to detect cosmic muon
 *          tracks for the CMS-RPC based Technical Trigger", R.T.Rajan et al</EM>
 *
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-15
 */
class RPCTTU {
public: 
  /// Standard constructor
  RPCTTU( ) { }; 
  
  RPCTTU( int, const char *, const char *, int );
  
  RPCTTU( int, const char *, const char * , const char *, int );
  
  virtual ~RPCTTU( ); ///< Destructor
  
  bool initialise();
  
  void emulate();
  
  void process( const std::map<int,RBCInput*> & );
  
  void printinfo();
  
  RPCWheel * m_Wheels[2];

protected:
  
private:
  
  int m_id;
  int m_maxwheels;
  int m_wheelids[5];
  int m_bx;
  
  TTUInput * m_ttuin[2];
  
  TTUConfiguration * m_ttuconf;
  
  //TTUPaC * m_ttupac;
  
  std::string m_logtype;
  
};
#endif // RPCTTU_H
