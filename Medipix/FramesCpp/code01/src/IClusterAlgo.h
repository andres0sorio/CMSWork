// $Id: $
#ifndef ICLUSTERALGO_H 
#define ICLUSTERALGO_H 1

// Include files
// from STL
#include <string>


/** @class IClusterAlgo IClusterAlgo.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-02-20
 */
class IClusterAlgo {
public: 
  
  IClusterAlgo() {};
  virtual ~IClusterAlgo() {};
  
  virtual void Run() = 0;
 
  virtual void Filter() = 0;

  virtual void Characterize() = 0;

protected:

private:

};
#endif // ICLUSTERALGO_H
