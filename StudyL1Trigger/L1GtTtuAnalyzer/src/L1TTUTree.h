// $Id: $
#ifndef L1TTUTREE_H 
#define L1TTUTREE_H 1

// Include files
// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"

/** @class L1TTUTree L1TTUTree.h
 *  
 *
 *  @author Andres Felipe Osorio Oliveros
 *  @date   2010-02-03
 */
class L1TTUTree {
public: 
  
  enum {
    MAX_BITS=8,
    MAX_RHITS=50
  };
  
  /// Standard constructor
  L1TTUTree( ) {};
  
  L1TTUTree( edm::Service<TFileService> & );
  
  virtual ~L1TTUTree( ); ///< Destructor
  
  //GENERAL block
  int             runn;
  int             eventn;
  int             lumi;
  boost::uint64_t timest;
  boost::uint64_t gttt;
  
  int hasRPCB;
  int hasDT;
  int maxBits;
  
  float pacTTU[MAX_BITS];
  float  dtTTU[MAX_BITS];
  
  //RPC RecHits
  int nRpcHits;
  int nRpcHitsEndcap;

  int      rpcHit_BX[MAX_RHITS];
  int rpcHit_Station[MAX_RHITS];
  int    rpcHit_Ring[MAX_RHITS];
  int  rpcHit_Sector[MAX_RHITS];
  int   rpcHit_Layer[MAX_RHITS];
  
  float     rpcHit_X[MAX_RHITS];
  float     rpcHit_Y[MAX_RHITS];
  float     rpcHit_Z[MAX_RHITS];

  int      rpcHit_BX_E[MAX_RHITS];
  int rpcHit_Station_E[MAX_RHITS];
  int    rpcHit_Ring_E[MAX_RHITS];
  int  rpcHit_Sector_E[MAX_RHITS];
  int   rpcHit_Layer_E[MAX_RHITS];
  
  float     rpcHit_X_E[MAX_RHITS];
  float     rpcHit_Y_E[MAX_RHITS];
  float     rpcHit_Z_E[MAX_RHITS];



  void reset();
  
  void fill();
  
protected:
  
private:
  
  
  void book();
  
  // output file
  edm::Service<TFileService> m_fs;
  
  // tree
  TTree * m_tree;
  
};
#endif // L1TTUTREE_H
