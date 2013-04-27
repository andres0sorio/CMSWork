// $Id: $
#ifndef DIMENSION_H 
#define DIMENSION_H 1

// Include files
#include <string>
#include <sstream>
#include <iostream>

/** @class Dimension Dimension.h
 *  
 *  Base clase for any dimension to be included in DB
 *
 *
 *  @author Andres Osorio
 *  @date   2008-10-26
 */

class Dimension {
public: 
  /// Standard constructor
  Dimension( ) {  
    m_pkey=0; 
    m_name=std::string("Dim"); 
    m_oss = new std::ostringstream(std::ostringstream::app);
  };
  
  Dimension( const char * _name) {  
    m_pkey=0; 
    m_name=std::string(_name) ;
    m_oss = new std::ostringstream(std::ostringstream::app);
  };
  
  Dimension( const char * , long int );
  
  virtual ~Dimension()
  {
    if (m_oss) delete m_oss;
    m_oss = NULL;
  };
  
  virtual void SetQuery() = 0;

  virtual void SetSelectQuery() = 0;

  virtual void AddValue( int ) = 0;
  
  virtual void FillTable() = 0;

  virtual void PrintInfo() = 0;

  virtual void ClearTable() = 0;
    
  std::ostringstream * GetQuery() { return m_oss; };
  
  long int             m_pkey;
  std::string          m_name;
  std::ostringstream * m_oss;

protected:
  
private:
  
};

#endif // DIMENSION_H
