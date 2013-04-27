// $Id: $
#ifndef INTERFACE_RPCACCESSCONFIG_H 
#define INTERFACE_RPCACCESSCONFIG_H 1

// Include files

/** @class RPCAccessConfig RPCAccessConfig.h 
 *   interface/AccessConfiguration.h
 *  
 *   (naive approach on the configuration/database access)
 *
 *
 *
 *  @author Andres Osorio
 *  @date   2008-10-25
 */
class RPCAccessConfig {
public: 

  virtual bool read()  = 0;
  
  virtual bool write() = 0;
  
protected:
  
private:

};
#endif // INTERFACE_RPCACCESSCONFIG_H
