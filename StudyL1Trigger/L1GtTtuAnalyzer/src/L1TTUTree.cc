// $Id: $
// Include files 



// local
#include "StudyL1Trigger/L1GtTtuAnalyzer/src/L1TTUTree.h"

//-----------------------------------------------------------------------------
// Implementation file for class : L1TTUTree
//
// 2010-02-03 : Andres Felipe Osorio Oliveros
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
L1TTUTree::L1TTUTree( edm::Service<TFileService> & fs ) {
  
  // set up output
  m_fs = fs;
  m_tree = m_fs->make<TTree>("L1TTUTree", "L1TTUTree");
  book();
  
}

//=============================================================================
// Destructor
//=============================================================================
L1TTUTree::~L1TTUTree() {} 

//=============================================================================
void L1TTUTree::book() 
{
  
  // GENERAL block branches
  m_tree->Branch("Run",&runn,"Run/I");
  m_tree->Branch("Event",&eventn,"Event/I");
  m_tree->Branch("Lumi",&lumi,"Lumi/I");
  m_tree->Branch("Time",&timest,"Time/l");
  m_tree->Branch("GTtt",&gttt,"GTtt/l");
  
  m_tree->Branch("HasRPCB", &hasRPCB,"HasRPCB/I");
  m_tree->Branch("HasDT",   &hasDT,"HasDT/I");
  m_tree->Branch("MaxBits", &maxBits,"MaxBits/I");
  
  // global muons quantities
  m_tree->Branch("PacTTU", pacTTU,"PacTTU[MaxBits]/F");
  m_tree->Branch("DtTTU" , dtTTU ,"DtTTU[MaxBits]/F");

  // RPC  RecHits
  m_tree->Branch("nRpcHits", &nRpcHits,      "nRpcHits/I" );
  m_tree->Branch("rpcHitBX", rpcHit_BX,      "rpcHitBX[nRpcHits]/I" );
  m_tree->Branch("rpcHitSt", rpcHit_Station, "rpcHitSt[nRpcHits]/I" );
  m_tree->Branch("rpcHitWh", rpcHit_Ring,    "rpcHitWh[nRpcHits]/I" );
  m_tree->Branch("rpcHitSe", rpcHit_Sector,  "rpcHitSe[nRpcHits]/I" );
  m_tree->Branch("rpcHitLa", rpcHit_Layer,   "rpcHitLa[nRpcHits]/I" );
  m_tree->Branch("rpcHitX" , rpcHit_X,       "rpcHitX[nRpcHits]/F" );
  m_tree->Branch("rpcHitY" , rpcHit_Y,       "rpcHitY[nRpcHits]/F" );
  m_tree->Branch("rpcHitZ" , rpcHit_Z,       "rpcHitZ[nRpcHits]/F" );

  // RPC  RecHits
  m_tree->Branch("nRpcHitsEndcap", &nRpcHitsEndcap,      "nRpcHitsEndcap/I" );
  m_tree->Branch("rpcHitBX_E", rpcHit_BX_E,      "rpcHitBX_E[nRpcHitsEndcap]/I" );
  m_tree->Branch("rpcHitSt_E", rpcHit_Station_E, "rpcHitSt_E[nRpcHitsEndcap]/I" );
  m_tree->Branch("rpcHitWh_E", rpcHit_Ring_E,    "rpcHitWh_E[nRpcHitsEndcap]/I" );
  m_tree->Branch("rpcHitSe_E", rpcHit_Sector_E,  "rpcHitSe_E[nRpcHitsEndcap]/I" );
  m_tree->Branch("rpcHitLa_E", rpcHit_Layer_E,   "rpcHitLa_E[nRpcHitsEndcap]/I" );
  m_tree->Branch("rpcHitX_E" , rpcHit_X_E,       "rpcHitX_E[nRpcHitsEndcap]/F" );
  m_tree->Branch("rpcHitY_E" , rpcHit_Y_E,       "rpcHitY_E[nRpcHitsEndcap]/F" );
  m_tree->Branch("rpcHitZ_E" , rpcHit_Z_E,       "rpcHitZ_E[nRpcHitsEndcap]/F" );
  
}

void L1TTUTree::reset() 
{
  hasRPCB = -99;
  hasDT = -99;
  nRpcHits = 0;
  nRpcHitsEndcap = 0;
  gttt = 0;
  maxBits = 0;
  
  for (int i=0; i < MAX_BITS; ++i) {
    pacTTU[i] = -99;
    dtTTU[i]  = -99;
  }
  
  for (int i=0; i < MAX_RHITS; ++i) {

    rpcHit_BX[i] = -99;
    rpcHit_Station[i] = -99;
    rpcHit_Ring[i] = -99;
    rpcHit_Sector[i] = -99;
    rpcHit_Layer[i] = -99;
    
    rpcHit_X[i] = -99.0;
    rpcHit_Y[i] = -99.0;
    rpcHit_Z[i] = -99.0;

    rpcHit_BX_E[i] = -99;
    rpcHit_Station_E[i] = -99;
    rpcHit_Ring_E[i] = -99;
    rpcHit_Sector_E[i] = -99;
    rpcHit_Layer_E[i] = -99;
    
    rpcHit_X_E[i] = -99.0;
    rpcHit_Y_E[i] = -99.0;
    rpcHit_Z_E[i] = -99.0;
    
  }
  
  
}

void L1TTUTree::fill()
{
  
  m_tree->Fill();
  
}

