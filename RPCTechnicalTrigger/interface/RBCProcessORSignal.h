// $Id: $
#ifndef INTERFACE_RBCPROCESSORSIGNAL_H 
#define INTERFACE_RBCPROCESSORSIGNAL_H 1

// Include files

/** @class RBCProcessORSignal RBCProcessORSignal.h interface/RBCProcessORSignal.h
 *  
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-10
 */
class RBCProcessORSignal {
public: 
  
  virtual int  next()  = 0;
  
  virtual void mask()  = 0;
  
  virtual void force() = 0;
  
protected:
  
private:

};
#endif // INTERFACE_RBCPROCESSORSIGNAL_H
