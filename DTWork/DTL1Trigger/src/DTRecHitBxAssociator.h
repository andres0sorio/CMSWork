// $Id: $
#ifndef AOSORIO_DTRECHITBXASSOCIATOR_H 
#define AOSORIO_DTRECHITBXASSOCIATOR_H 1

// Include files
#include <vector>

//...DT
#include <DataFormats/DTRecHit/interface/DTRecHit1D.h>

//...DT Trigger info
#include <DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h>
#include <DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h>

/** @class DTRecHitBxAssociator DTRecHitBxAssociator.h aosorio/DTRecHitBxAssociator.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-06-08
 */

class DTRecHitwBx {
 public:

  DTRecHitwBx( DTRecHit1D * hit,int bx, int qual ) { 
    m_hit = hit ; m_bx = bx; m_qual = qual; 
  };

  virtual ~DTRecHitwBx() {};

  DTRecHit1D * m_hit;
  int m_bx;
  int m_qual;
  
};

class DTRecHitBxAssociator {
 public: 
  /// Standard constructor
  DTRecHitBxAssociator( ); 
  
  //Necesitamos crear un constructor que tome dos(tres?) argumentos: 
  // a) un vector de DTRechits y b) un vector con objetos del trigger de DTs.
  void Run( const std::vector<DTRecHit1D*> &, const std::vector<L1MuDTChambPhDigi*> &);
  
  virtual ~DTRecHitBxAssociator( ); ///< Destructor
  
  bool hasIncrementalBx();
  
  //Declara el vector
  std::vector<DTRecHitwBx*> m_hitsWBx;
  
 protected:
  
 private:
  
    
};
#endif // AOSORIO_DTRECHITBXASSOCIATOR_H
