// $Id: $
#ifndef LOOPSELECTOR_H 
#define LOOPSELECTOR_H 1

// Include files
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


/** @class LoopSelector LoopSelector.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-02-14
 */
template< typename T > class LoopSelector {
public: 
  /// Standard constructor
  LoopSelector( ) {}; 
  
  LoopSelector( TTree *tree, const char * option  ) {
    m_rootTree = new T(tree, option);
  }; 

  ~LoopSelector( ) { delete m_rootTree; }; ///< Destructor
  
  void Initialize() {
    m_rootTree->Initialize();
  };

  void Loop( int maxevts ) {
    m_rootTree->Loop( maxevts );
  };

  void CheckConsistency( int maxevts ) {
    m_rootTree->CheckConsistency( maxevts );
  };
  
  T * m_rootTree;
  
};

#endif // LOOPSELECTOR_H
