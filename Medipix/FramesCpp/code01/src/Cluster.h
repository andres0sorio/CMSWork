// $Id: $
#ifndef CLUSTER_H 
#define CLUSTER_H 1
// Include files
#include <vector>
#include <math.h>

/** @class Cluster Cluster.h
 *  
 *
 *  @author Andres Osorio/Iván Caicedo
 *  @date   2012-03
 */

//Initializes the Cluster Class
class Cluster;
bool compareCluster( Cluster * c1, Cluster * c2 );

//Initializes the Pixel Class
class Pixel 
{
public:
  //Constructor of the Pixel Class
  Pixel() { 
    id = 0; 
    mx = 0; 
    my = 0;
    me = 0;
    mfree = true;
  };
  //Assigns to every pixel its id, xy coordinates, counts, and indicates if the pixel is empty (Initialices as true) 
  Pixel(int id_, int x_, int y_, int e_ ) { 
    id = id_; 
    mx = x_; 
    my = y_;
    me = e_;
    mfree = true;
  };
  //Destructor of the Pixel class
  ~Pixel() {};

  //These methods return the id, xy coordinates and counts of every pixel
  int X() { return mx; };
  int Y() { return my; };
  int E() { return me; };
  int Id() { return id; };
  
  // Returns the current status of the pixel 
  bool IsFree() { return mfree; };

  //Set the pixel to empty or busy.
  void SetBusy() { mfree = false; };
  void SetFree() { mfree = true; };
  
private:
  
  //Private variables of every pixel
  int id;
  int mx;
  int my;
  int me;
  bool mfree;
  
};

class Cluster {
public: 
  //Constructor of the Cluster class
  Cluster( ){}; 
  Cluster( int ); 
  //Destructor of the Cluster class
  virtual ~Cluster( );
  //Returns the total size of the Cluster
  int  GetSize();
  //Removes a pixel from the Cluster
  void RmPixel(int, int);
  //Adds a pixel to the Cluster
  void AddPixel(Pixel *);
  void AddPixel(int , int, int, int );
  //Finds the centroid of the Cluster
  void FindCentroid();
  
  //This method returns the X coordinate (Approximating to the closest integer)
  int X() 
  {
    double intpart;
    float frcpart;
    frcpart = modf( m_centroidX, &intpart);
    if ( frcpart < 0.5 ) return int( floor( m_centroidX ) );
    else return int( ceil ( m_centroidX ) );
  };
  //This method returns the Y coordinate (Approximating to the closest integer)
  int Y() 
  {
    double intpart;
    float frcpart;
    frcpart = modf( m_centroidY, &intpart);
    if ( frcpart < 0.5 ) return int( floor( m_centroidY ) );
    else return int( ceil ( m_centroidY ) );
  };
  //Returns the sum of all the counts of all the pixels in the Cluster
  float E() 
  {
    return m_E;
  };
  //Returns the average of the sum of the counts of all the pixels in the Cluster
  float Avg() {
    return m_avg;
  };
  
protected:
  
private:
  
  //Variables of every Cluster
  int mId;
  std::vector<Pixel*> m_pixels;
  float m_E;
  float m_avg;
  float m_centroidX;
  float m_centroidY;
  
  
};
#endif // CLUSTER_H
