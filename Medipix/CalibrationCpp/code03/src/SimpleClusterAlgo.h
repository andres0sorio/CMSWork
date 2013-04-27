// $Id: $
#ifndef SIMPLECLUSTERALGO_H 
#define SIMPLECLUSTERALGO_H 1

// Include files
#include <IClusterAlgo.h>
#include <Cluster.h>
#include <Data.h>
#include <TH2F.h>

/** @class SimpleClusterAlgo SimpleClusterAlgo.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-02-20
 */
class SimpleClusterAlgo : public IClusterAlgo {
public: 
  /// Standard constructor
  SimpleClusterAlgo() {};
    
  SimpleClusterAlgo( Data * ); 

  virtual ~SimpleClusterAlgo( ); ///< Destructor

  virtual void Run();

  virtual void FindNeighbors(Pixel *, Cluster*);
    
  virtual void BuildPixelMatrix( Data * );

  virtual void PlotClusters( TH2F * );
  virtual void PlotClusterCounts( TH1F * );
  virtual void PlotClusterSize( TH1F * );
  
protected:

private:

  int m_threshold;
  
  Pixel *m_pixelmatrix[256][256];

  std::vector<int> vposx;
  std::vector<int> vposy;
    
  std::vector<Cluster*> m_clusters;

  
};
#endif // SIMPLECLUSTERALGO_H
