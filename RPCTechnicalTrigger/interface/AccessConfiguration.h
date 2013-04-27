// $Id: $
#ifndef INTERFACE_ACCESSCONFIGURATION_H 
#define INTERFACE_ACCESSCONFIGURATION_H 1

// Include files

/** @class AccessConfiguration AccessConfiguration.h 
 *   interface/AccessConfiguration.h
 *  
 *   (naive approach on the configuration/database access)
 *
 *
 *
 *  @author Andres Osorio
 *  @date   2008-10-25
 */
class AccessConfiguration {
public: 

  virtual void read()  = 0;
  
  virtual void write() = 0;
  
protected:

private:

};
#endif // INTERFACE_ACCESSCONFIGURATION_H
