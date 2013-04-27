// $Id: $
#ifndef LHEANALYZER_H 
#define LHEANALYZER_H 1

// Include files
#include "RootCommon.h"

#include "TChain.h"
#include "TString.h"
#include "TClonesArray.h"
#include "TList.h"

#include <TLorentzVector.h>
#include <TParticle.h>
#include <TDatabasePDG.h>

#include "ExRootAnalysis/ExRootClasses.h"
#include "ExRootAnalysis/ExRootConfReader.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include "ExRootAnalysis/ExRootTreeWriter.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"
#include "ExRootAnalysis/ExRootClassifier.h"
#include "ExRootAnalysis/ExRootUtilities.h"
#include "ExRootAnalysis/ExRootFilter.h"
#include "ExRootAnalysis/ExRootResult.h"

#include "Histograms.h"

/** @class LHEAnalyzer LHEAnalyzer.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-09-19
 */
class LHEAnalyzer {
public: 
  /// Standard constructor
  LHEAnalyzer( ) { };
  
  LHEAnalyzer( const char * );

  virtual void Loop( );
  
  virtual ~LHEAnalyzer( ); ///< Destructor

protected:

private:

  TChain * m_chain;
  
  ExRootTreeReader * m_treeReader;
  
  std::map< std::string, int> m_pgsCodes;
  std::map< std::string, int> m_jetsMG;
  std::map< std::string, int> m_bjetsMG;
  std::map< std::string, int> m_muonsMG;
  std::map< std::string, int> m_metMG;

  std::map< int, int > m_pgsOrder;
  std::map< int, int > m_trueOrder;
  
  bool m_debug;

  std::ofstream *m_lhco_output;

  Histograms * m_histos;
  

};
#endif // LHEANALYZER_H
