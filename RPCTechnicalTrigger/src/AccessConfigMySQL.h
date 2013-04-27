// $Id: $
#ifndef ACCESSCONFIGMYSQL_H 
#define ACCESSCONFIGMYSQL_H 1

// Include files
#include "L1Trigger/RPCTechnicalTrigger/interface/RPCAccessConfig.h"
#include "L1Trigger/RPCTechnicalTrigger/src/ToyDB.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <cmath>
#include <sstream>

// From ROOT

#include <TROOT.h>
#include "TSQLServer.h"
#include "TSQLResult.h"
#include "TSQLRow.h"
#include "TList.h"
#include "TCollection.h"


/** @class AccessConfigMySQL AccessConfigMySQL.h
 *  
 *  Implements the AccessConfiguration interface
 * 
 *  With this implementation, we can access a Toy MySQL Database
 *  using ROOT interfaces
 *
 *  @author Andres Osorio
 *  @date   2008-10-25
 */
  
class AccessConfigMySQL : public RPCAccessConfig {
public: 

  /// Standard constructor
  AccessConfigMySQL( );

  AccessConfigMySQL( const char * );
  
  virtual ~AccessConfigMySQL( ); ///< Destructor

  enum iomode {recreate=0 , append=1, open=2};
  
  bool read();
  
  bool write();

  void setwritemode( iomode _mode ) { m_mode = _mode; };
  
protected:
  
private:
  
  long int m_nrecords;
  
  TSQLServer * m_db;
  TSQLResult * m_sqlres;
  TSQLRow    * m_row;
  
  int m_mode;
  
  std::ifstream *m_in;

  std::ostringstream *m_oss;
  
  //...
  
  ToyDB * m_data;
  
  //...
  
};
#endif // ACCESSCONFIGMYSQL_H
