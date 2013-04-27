// $Id: $
#ifndef DATA_H 
#define DATA_H 1

// Include files
#include "CommonIncludes.h"

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
  
  int  next();
  
  void rewind() { 
    m_in->clear();
    m_in->seekg(0,ios::beg); 
  }
  
  
  void showfirst();
  
  double X1(){ return m_x1;};
  double X2(){ return m_x2;};
  
protected:
  
private:
  
  std::ifstream * m_in;
  
  double m_x1;
  double m_x2;
    
};
#endif // DATA_H
