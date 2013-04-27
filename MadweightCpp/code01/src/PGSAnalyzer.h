// $Id: $
#ifndef PGSANALYZER_H 
#define PGSANALYZER_H 1

// Include files
#include "RootCommon.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TStyle.h"

#include "Histograms.h"
#include "LHCOParser.h"
#include "WeightsAnalyzer.h"

#include <algorithm>

/** @class PGSAnalyzer PGSAnalyzer.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-08-08
 */

class Permutation {
public:
  
  Permutation( ) {};
  
  virtual ~Permutation( ) { 
    perm_id.clear(); 
    assigment_map.clear(); 
  };
  
  std::vector<int> perm_id;
  std::map<int,int> assigment_map;
  
};
  
class PGSAnalyzer {
public: 
  
  /// Standard constructor
  PGSAnalyzer( ) {}; 
  PGSAnalyzer(const char * ); 
  
  virtual ~PGSAnalyzer( ); ///< Destructor
  
  virtual void Loop();
  
  virtual void SetPermutations( const char * );
  
  virtual void SetWeights( const char* );

  virtual void AnalyzePermutations();
  
  void Set_4momentum( double, double, double, double, TLorentzVector * );
  
  void SetMaxEvents( int max ) { m_max_events = max; };
    
protected:
  
private:
  
  LHCOParser * m_parser;
  
  std::map<std::string, int> m_pgsCodes;

  std::map<int, int> m_pgsOrder;
  
  std::map<std::string, int> m_jetsMG;
  std::map<std::string, int> m_bjetsMG;
  std::map<std::string, int> m_muonsMG;
  std::map<std::string, int> m_metMG;
  
  TList * v_pgsObjects;

  WeightsAnalyzer * m_weights;
    
  std::vector<Permutation*> v_perm;
  
  bool m_debug;
  bool m_include_MET;
  
  Histograms * m_histos;

  int m_max_events;
  
};
#endif // PGSANALYZER_H
