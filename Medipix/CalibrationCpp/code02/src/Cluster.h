// $Id: $
#ifndef CLUSTER_H 
#define CLUSTER_H 1

// Include files
#include <vector>

/** @class Cluster Cluster.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-02-19
 */

class Pixel 
{
public:
  Pixel() { id = 0; mx = 0; my = 0;};
  Pixel(int id_, int x_, int y_ ) { id = id_; mx = x_; my = y_;};
  ~Pixel() {};
  
  int id;
  int mx;
  int my;
  
};

class Cluster {
public: 
  /// Standard constructor
  Cluster( ){}; 
  Cluster( int ); 

  virtual ~Cluster( ); ///< Destructor
  
  int  GetSize();
  void RmPixel(int, int);
  void AddPixel(int , int, int );
  
protected:

private:

  int mId;
  
  std::vector<Pixel*> m_pixels;
  

};
#endif // CLUSTER_H
