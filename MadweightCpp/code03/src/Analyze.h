// $Id: $
#ifndef ANALYZE_H 
#define ANALYZE_H 1

// Include files
#include "RootCommon.h"
#include "TH1F.h"
#include "TGraph.h"
#include <map>
#include "Data.h"

/** @class Analyze Analyze.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-08-08
 */
class Analyze {
public: 
  /// Standard constructor
  Analyze( ) { };
  Analyze( const char * );
  Analyze( const char *, const char * );
  
  virtual ~Analyze( ); ///< Destructor
  
  void Run( );
  
  
protected:
  
private:
  
  Data * m_d1;

  Data * m_d2;

  int m_maxEvts;
  
  bool m_debug;
  
  std::map< std::string, TH1F * > h_1DHistContainer;
  
  
  
};
#endif // ANALYZE_H
