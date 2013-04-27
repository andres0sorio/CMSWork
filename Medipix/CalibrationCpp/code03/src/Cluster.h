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
  Pixel() { 
    id = 0; 
    mx = 0; 
    my = 0;
    me = 0;
    mfree = true;
  };
  
  Pixel(int id_, int x_, int y_, int e_ ) { 
    id = id_; 
    mx = x_; 
    my = y_;
    me = e_;
    mfree = true;
  };
  
  ~Pixel() {};

  int X() { return mx; };
  int Y() { return my; };
  int E() { return me; };
  int Id() { return id; };
  
  bool IsFree() { return mfree; };
  void SetBusy() { mfree = false; };
  void SetFree() { mfree = true; };
  
private:
  
  int id;
  int mx;
  int my;
  int me;
  bool mfree;
  
};

class Cluster {
public: 
  /// Standard constructor
  Cluster( ){}; 
  Cluster( int ); 
  
  virtual ~Cluster( ); ///< Destructor
  
  int  GetSize();
  void RmPixel(int, int);
  void AddPixel(Pixel *);
  void AddPixel(int , int, int, int );
  void FindCentroid();
  
  float X() 
  {
    return m_centroidX;
  };

  float Y() 
  {
    return m_centroidY;
  };

  float E() 
  {
    return m_E;
  };
  
  
protected:
  
private:
  
  int mId;
  std::vector<Pixel*> m_pixels;

  float m_E;
  float m_centroidX;
  float m_centroidY;
  
  
};
#endif // CLUSTER_H
