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
Cluster::~Cluster() {} 

//=============================================================================

int Cluster::GetSize() 
{
  return m_pixels.size();
}

void Cluster::AddPixel( int id, int x, int y) 
{
  
  Pixel * p1 = new Pixel( id, x, y);
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

