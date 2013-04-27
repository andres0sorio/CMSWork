// $Id: $
// Include files 



// local
#include "SimpleClusterAlgo.h"

//-----------------------------------------------------------------------------
// Implementation file for class : SimpleClusterAlgo
//
// 2011-02-26 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
SimpleClusterAlgo::SimpleClusterAlgo( Data * data ) : IClusterAlgo() {

  m_threshold = 10;
  
  vposx.push_back(-1);
  vposx.push_back( 0);
  vposx.push_back( 1);
  vposx.push_back(-1);
  vposx.push_back( 1);
  vposx.push_back(-1);
  vposx.push_back( 0);
  vposx.push_back( 1);
  
  vposy.push_back( 1);
  vposy.push_back( 1);
  vposy.push_back( 1);
  vposy.push_back( 0);
  vposy.push_back( 0);
  vposy.push_back(-1);
  vposy.push_back(-1);
  vposy.push_back(-1);
  
  BuildPixelMatrix( data );
      
}
//=============================================================================
// Destructor
//=============================================================================
SimpleClusterAlgo::~SimpleClusterAlgo() {
  
  for (int i=0; i < 256; ++i) 
    for (int j=0; j < 256; ++j) 
      delete m_pixelmatrix[i][j];

  std::vector<Cluster*>::iterator itrClus;
  
  for( itrClus = m_clusters.begin(); itrClus != m_clusters.end();
       ++itrClus ) 
    delete (*itrClus);
  
  m_clusters.clear();
  
} 

//=============================================================================

void SimpleClusterAlgo::BuildPixelMatrix( Data * data )
{
  
  int pixId = 0;
  
  for (int i=0; i < 256; ++i) 
  {
    for (int j=0; j < 256; ++j) 
    {
      int reading = (*data).matrix[i][j];
      Pixel * pix = new Pixel( pixId, i, j, reading );
      m_pixelmatrix[i][j] = pix;
    }
  }
  
}

void SimpleClusterAlgo::Run()
{

  for (int i=0; i < 256; ++i) 
  {
    for (int j=0; j < 256; ++j) 
    {
      
      Pixel * pix = m_pixelmatrix[i][j];
      int reading = pix->E();
      
      if ( reading > m_threshold && pix->IsFree() ) 
      {
        pix->SetBusy();
        
        Cluster * cclu = new Cluster();
        cclu->AddPixel(pix);
        FindNeighbors( pix , cclu );
        
        m_clusters.push_back( cclu );
        
      }
      
    }
    
  }
  
  /* 
     std::vector<Cluster*>::const_iterator itrClus;
  
     for( itrClus = m_clusters.begin(); itrClus != m_clusters.end();
     ++itrClus )
     {
     (*itrClus)->FindCentroid();
     std::cout << (*itrClus)->X()
     << '\t'
     << (*itrClus)->Y()
     << '\n';
     }
  */

  

  std::cout << "total found " << m_clusters.size() << '\n';
  
}

void SimpleClusterAlgo::FindNeighbors( Pixel * seed , Cluster * cluster ) 
{
  
  //check neighbors
  for( int k=0; k < 9; ++k) 
  {
    
    int mposx = seed->X() + vposx[k];
    int mposy = seed->Y() + vposy[k];
    
    if ( mposx < 0 || mposy < 0) 
      continue;
    
    if ( mposx >= 256 || mposy >= 256 )
      continue;
        
    Pixel * pix = m_pixelmatrix[mposx][mposy];
    
    int reading = pix->E();
    
    if ( reading > m_threshold && pix->IsFree() ) 
    {
      pix->SetBusy();
      cluster->AddPixel(pix);
      FindNeighbors( pix, cluster );
    }
    
  }
  
}

void SimpleClusterAlgo::PlotClusters( TH2F * h2 ) 
{
  
  std::vector<Cluster*>::iterator itrClus;
  
  for( itrClus = m_clusters.begin(); itrClus != m_clusters.end();
       ++itrClus )
  {

    (*itrClus)->FindCentroid();
    h2->Fill( (*itrClus)->X(), (*itrClus)->Y() );
  
  }  
  

}


void SimpleClusterAlgo::PlotClusterCounts( TH1F * h1 ) 
{
  
  std::vector<Cluster*>::iterator itrClus;
  
  for( itrClus = m_clusters.begin(); itrClus != m_clusters.end();
       ++itrClus )
  {
    
    (*itrClus)->FindCentroid();
    h1->Fill( (*itrClus)->E());
    
  }  
  

}

void SimpleClusterAlgo::PlotClusterSize( TH1F * h1 ) 
{
  
  std::vector<Cluster*>::iterator itrClus;
  
  for( itrClus = m_clusters.begin(); itrClus != m_clusters.end();
       ++itrClus )
  {
    
    (*itrClus)->FindCentroid();
    h1->Fill( (*itrClus)->GetSize());
    
  }  

}
