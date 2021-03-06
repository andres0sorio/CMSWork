// $Id: TTUConfigurator.cc,v 1.1 2009/06/04 11:52:59 aosorio Exp $
// Include files 



// local
#include "L1Trigger/RPCTechnicalTrigger/interface/TTUConfigurator.h"

//-----------------------------------------------------------------------------
// Implementation file for class : TTUConfigurator
//
// 2009-06-02 : Andres Felipe Osorio Oliveros
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TTUConfigurator::TTUConfigurator( const char * infile ) {
  
  m_in = new std::ifstream();
  m_in->open( infile );
  
  if(!m_in->is_open()) {
    std::cout << "TTUConfigurator> cannot open file" << std::endl;
    m_hasConfig = false;
  } else {
    std::cout << "TTUConfigurator> file is now open" << std::endl;
    m_hasConfig = true;
  }
  
  m_rbcspecs = new RBCBoardSpecs();
  m_ttuspecs = new TTUBoardSpecs();
  
}
//=============================================================================
// Destructor
//=============================================================================
TTUConfigurator::~TTUConfigurator() {
  
  if ( m_in ) {
    m_in->close();
    delete m_in;
  }
  
  if ( m_rbcspecs ) delete m_rbcspecs;
  if ( m_ttuspecs ) delete m_ttuspecs;
  
} 

//=============================================================================

void TTUConfigurator::process()
{
  
  addData( m_rbcspecs );
  addData( m_ttuspecs );
  
}

void TTUConfigurator::addData( RBCBoardSpecs * specs )
{
  
  RBCBoardSpecs::RBCBoardConfig * board;
  
  for( int i=0; i < 30; i++) {
    
    board = new RBCBoardSpecs::RBCBoardConfig();
    
    (*m_in) >> (*board);
    
    specs->v_boardspecs.push_back( *board );
    
  }
  
}

void TTUConfigurator::addData( TTUBoardSpecs * specs )
{
  
  TTUBoardSpecs::TTUBoardConfig * board;
  
  for(int i=0; i < 3; i++){
    
    board= new TTUBoardSpecs::TTUBoardConfig();
    
    (*m_in) >> (*board);
    
    specs->m_boardspecs.push_back( *board );
    
  }
  
}
