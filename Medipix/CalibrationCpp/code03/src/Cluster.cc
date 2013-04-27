// $Id: $
// Include files 



// local
#include "Cluster.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Cluster
//
// 2011-02-19 : Andres Osorio
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

int Cluster::GetSize() 
{
  return m_pixels.size();
}

void Cluster::AddPixel( Pixel * pix ) 
{
  
  m_pixels.push_back( pix );
  
}


void Cluster::AddPixel( int id, int x, int y, int e) 
{
  
  Pixel * p1 = new Pixel( id, x, y, e);
  m_pixels.push_back( p1 );
  
}


void Cluster::RmPixel( int x, int y)
{
  

  std::vector<Pixel*>::iterator itrPx;

  //Find pixel at pos (x,y)
  //Pixel * p1 = new Pixel( id, x, y);
  //
  //m_pixels.push_back( p1 );
  //remove that pixel for pixels

}

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
  
  m_E = sum;
  m_centroidX = wsumx/sum;
  m_centroidY = wsumy/sum;
  
}
