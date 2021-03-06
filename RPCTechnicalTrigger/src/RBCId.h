// $Id: $
#ifndef RBCID_H 
#define RBCID_H 1

// Include files
#include <iostream>

/** @class RBCId RBCId.h
 *  
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-12
 */
class RBCId {
public: 
  /// Standard constructor
  RBCId( ); 

  RBCId(int , int * );
  
  virtual ~RBCId( ); ///< Destructor
  
  int wheel() const { return m_wheel;};
  
  int * sector() { return m_sector;};
  
  void setid ( int _wh, int *_sec) { 
    m_wheel = _wh;
    m_sector[0] = _sec[0];
    m_sector[1] = _sec[1];
  };
  
  void printinfo();
    
protected:
  
private:
  
  int m_wheel;
  int m_sector[2];
  
};
#endif // RBCID_H
