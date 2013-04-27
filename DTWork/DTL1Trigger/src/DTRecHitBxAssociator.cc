// $Id: $
// Include files 



// local
#include "DTRecHitBxAssociator.h"

//-----------------------------------------------------------------------------
// Implementation file for class : DTRecHitBxAssociator
//
// 2011-06-08 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
DTRecHitBxAssociator::DTRecHitBxAssociator(  ) {
  ///este el constructor basico
}

//=============================================================================
// Destructor
//=============================================================================

DTRecHitBxAssociator::~DTRecHitBxAssociator() {
  m_hitsWBx.clear();
} 

//=============================================================================

void DTRecHitBxAssociator::Run( const std::vector<DTRecHit1D*> & vecDtHits, 
				const std::vector<L1MuDTChambPhDigi*> & vecL1DTPhDigi) {
  
  
  std::vector<L1MuDTChambPhDigi*>::const_iterator digisItr;

  int counter = 0;
  
  for( digisItr = vecL1DTPhDigi.begin(); digisItr != vecL1DTPhDigi.end(); ++digisItr) {
    
    int station = (*digisItr)->stNum();
    int sector  = (*digisItr)->scNum() + 1;
    int wheel   = (*digisItr)->whNum();
    int bx      = (*digisItr)->bxNum();
    int qual    = (*digisItr)->code();

    std::vector<DTRecHit1D*>::const_iterator hitsItr;
    for ( hitsItr = vecDtHits.begin(); hitsItr != vecDtHits.end(); ++hitsItr ) {
      
      int hit_station = (*hitsItr)->wireId().station();
      int hit_sector  = (*hitsItr)->wireId().sector();
      int hit_wheel   = (*hitsItr)->wireId().wheel();
      
      if( station == hit_station &&
	  sector  == hit_sector  &&
	  wheel   == hit_wheel ) {
	
	std::cout << "Match found " 
		  << station << " " << hit_station << " " 
		  << sector  << ":" << hit_sector  << " " 
		  << wheel   << ":" << hit_wheel   << " "
		  << "@bx: " << bx  << std::endl; 
	
	//Se crea un objeto DTRecHitwbx, se llena con hit y el bx asociado a cada hit
	// hitwbx es un apuntador
	
	DTRecHitwBx * hitwbx  = new DTRecHitwBx((DTRecHit1D*)&*(*hitsItr), bx, qual);
	
	m_hitsWBx.push_back( hitwbx );
	
	// llena el objeto DTRecHitwBx con la info de hitwbx, y guarda info a media q corre el loop
	// (DTrechits + bx) 

	++counter;
	
      }
      
    }
    
  }
  
  std::cout << "counter " <<  counter << " vs " << m_hitsWBx.size() << std::endl;
  
}

bool DTRecHitBxAssociator::hasIncrementalBx() {
  
  int bx_0 = 0;
  int bx;
  
  std::vector<DTRecHitwBx*>::const_iterator itrwbx;
  
  for(itrwbx = m_hitsWBx.begin(); itrwbx != m_hitsWBx.end(); itrwbx++){   
    
    bx = (*itrwbx)->m_bx;
    int diff = bx - bx_0;
    if( diff > 0 ){
      std::cout << "Increment found! In bx " 
		<< bx_0 << " " << bx << " " 
		<< diff << std::endl; 
      
      return true;
    }
    
    bx_0 = bx;
  }
  
  return false;
 
}
