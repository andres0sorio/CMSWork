// $Id: $
#ifndef RBCLOGIC_H 
#define RBCLOGIC_H 1

// Include files
#include "RBCInput.h"

#include <bitset>

/** @class RBCLogic RBCLogic.h
 *  
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-11
 */

class RBCLogic {
public: 
  
  virtual ~RBCLogic() {};
  
  virtual void process ( const RBCInput & , std::bitset<2> & ) = 0;

  virtual std::bitset<6> * getlayersignal( int ) = 0;
  
protected:
  
private:
  
};
#endif // RBCLOGIC_H
