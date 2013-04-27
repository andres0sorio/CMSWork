// $Id: $
#ifndef INTERFACE_PAC_H 
#define INTERFACE_PAC_H 1

// Include files

/** @class PaC PaC.h interface/PaC.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2008-10-25
 */
class PaC {
public: 
  /// Standard constructor
  PaC( ) {};
  
  PaC( int, int, int );
    
  virtual ~PaC( ); ///< Destructor
  
  int m_propA;
  int m_propB;
  int m_propC;
  
protected:
  
private:
  
};
#endif // INTERFACE_PAC_H
