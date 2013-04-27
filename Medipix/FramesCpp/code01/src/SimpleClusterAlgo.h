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
 *  @author Andres Osorio/Iván Caicedo
 *  @date   2012-03
 */
class SimpleClusterAlgo : public IClusterAlgo {
public: 
  /// Standard constructor
  SimpleClusterAlgo() {};
    
  SimpleClusterAlgo( Data * ); 

  virtual ~SimpleClusterAlgo( ); ///< Destructor

  virtual void Run();
  
  virtual void Filter();

  virtual void Characterize();
  
  virtual void FindNeighbors(Pixel *, Cluster*);
    
  virtual void BuildPixelMatrix( Data * );

  virtual void PlotClusters( TH2F * );
  virtual void PlotClusterCounts( TH1F * );
  virtual void PlotClusterSize( TH1F * );
  
  virtual void FindCoincidences();

  std::vector<Cluster*> m_clusters;

  std::vector<Cluster*> m_coincidences;

protected:

private:

  int m_threshold;
  
  Pixel *m_pixelmatrix[256][256];

  std::vector<int> vposx;
  std::vector<int> vposy;
    
  

  
};
#endif // SIMPLECLUSTERALGO_H
