// $Id: $
#ifndef INTERFACE_PROCESSINPUTSIGNAL_H 
#define INTERFACE_PROCESSINPUTSIGNAL_H 1

// Include files

/** @class ProcessInputSignal ProcessInputSignal.h interface/ProcessInputSignal.h
 *  
 *
 *  @author Andres Osorio
 *
 *  email: aosorio@uniandes.edu.co
 *
 *  @date   2008-10-10
 */
class ProcessInputSignal {
public: 
  
  virtual int  next()  = 0;
  
  virtual void mask()  = 0;
  
  virtual void force() = 0;
  
protected:
  
private:
  
};
#endif // INTERFACE_PROCESSINPUTSIGNAL_H
