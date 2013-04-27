// $Id: $
// Include files 
// local
#include "Cluster.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Cluster
//
// 2012-03 : Andres Osorio/Iván Caicedo
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Cluster::Cluster( int id_ ) {

  mId = id_;
  
}
//=============================================================================
// Destructor
//=============================================================================
Cluster::~Cluster() {
  
  m_pixels.clear();
  
} 
//=============================================================================



//Compares two clusters received as parameters and returns true if they are coincident within a given range (ns).
bool compareCluster( Cluster * c1, Cluster * c2 ) {

  int range = 500;

  if( ( (*c1).Avg() <= ( (*c2).Avg() + range) ) && 
      ( (*c1).Avg() >= ( (*c2).Avg() - range) ) ) return true;
  else return false; 
}



//Returns the size of the Cluster.
int Cluster::GetSize() 
{
  return m_pixels.size();
}



//Adds a pixel to the Cluster.
void Cluster::AddPixel( Pixel * pix ) 
{
  m_pixels.push_back( pix );  
}



//
void Cluster::AddPixel( int id, int x, int y, int e) 
{
  Pixel * p1 = new Pixel( id, x, y, e);
  m_pixels.push_back( p1 );  
}



//Removes a pixel (If necessary) from the Cluster.
void Cluster::RmPixel( int x, int y)
{
  std::vector<Pixel*>::iterator itrPx;

  //Find pixel at pos (x,y)
  //Pixel * p1 = new Pixel( id, x, y);
  //
  //m_pixels.push_back( p1 );
  //remove that pixel for pixels
}



//Returns the sum of all the counts in the Cluster, their average, and the centroid (X,Y).
void Cluster::FindCentroid() 
{
  
  std::vector<Pixel*>::const_iterator itrPix;
  
  float sum   = 0.0;
  float wsumx = 0.0;
  float wsumy = 0.0;
  
  
  for( itrPix = m_pixels.begin(); itrPix != m_pixels.end(); ++itrPix ) 
  {
    
    sum   += float( (*itrPix)->E() );
    wsumx += float( (*itrPix)->E()*(*itrPix)->X() );
    wsumy += float( (*itrPix)->E()*(*itrPix)->Y() );
    
  }

  float npix = float(m_pixels.size());

  m_E = sum;
  m_avg = m_E / npix;
  m_centroidX = wsumx/sum;
  m_centroidY = wsumy/sum;
  
}
