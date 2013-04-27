// $Id: $
#ifndef RUNANALYSIS_H 
#define RUNANALYSIS_H 1

// Include files

#include "CommonIncludes.h"
#include "Utilities.h"

#include "TFile.h"
#include "TTree.h"

#include "L1Tree.h"
#include "TChain.h"
#include "L1TTUTree.h"
#include "MuonRecoTree.h"
#include "L1ExtraTree.h"
#include "BasicOutput.h"
#include <bitset>

/** @class RunAnalysis RunAnalysis.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-02-01
 */

class RunAnalysis {
public: 
  /// Standard constructor
  RunAnalysis( ) {}; 
  
  RunAnalysis( const char * );

  RunAnalysis( const char * , const char * );
  
  virtual ~RunAnalysis( ); ///< Destructor
  
  L1Tree * l1tree;
  MuonRecoTree * recomuons;
  L1ExtraTree * l1extra;
  L1TTUTree *l1ttu;
  
  void Loop( Long64_t );

  void Initialize( );

  void Initialize( bool );

  bool Cut();
      
protected:
  
private:
  
  TFile * m_infileA;
  TFile * m_infileB;

  TChain * m_l1tree;
  TChain * m_recomu;
  TChain * m_l1extra;
  TChain * m_l1ttu;
    
  TFile * m_output;
  
  //.................................................

  BasicOutput * m_histos;

  std::vector<int> m_ttbits;
  std::vector<int>::iterator m_bitItr;

  std::map<int,int> m_NttuBits;
  std::map<int,int>::iterator m_ttuItr;
  std::bitset<64> TechBits[5];

  bool m_info;
  
  std::ifstream * m_inDataA;
  std::ifstream * m_inDataB;
  
  std::vector<std::string> m_DataVecA;
  std::vector<std::string> m_DataVecB;
  
  bool m_noinputfile;
  
    
};
#endif // RUNANALYSIS_H
