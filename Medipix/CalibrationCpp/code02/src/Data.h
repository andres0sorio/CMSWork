// $Id: $
#ifndef DATA_H 
#define DATA_H 1

// Include files
#include "RootCommon.h"

/** @class Data Data.h 3.7/Data.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-04-29
 */

class Data {
public: 

  /// Standard constructor
  Data( ) { }; 
  Data(const char*);
  
  virtual ~Data( ); ///< Destructor

  void Initialize();
  void Read();
  void Show( int );

  int matrix[256][256];
  
protected:
  
private:
  
  std::ifstream * m_in;
  
};
#endif // DATA_H

