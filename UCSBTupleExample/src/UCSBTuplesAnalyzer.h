// $Id: $
#ifndef UCSBTUPLESANALYZER_H 
#define UCSBTUPLESANALYZER_H 1

// Include files
#include "CommonIncludes.h"
#include "eventB.h"
#include "eventV.h"
#include "BasicOutput.h"
#include "TFile.h"

#include <algorithm>


/** @class UCSBTuplesAnalyzer UCSBTuplesAnalyzer.h
 *   
 *  
 *
 *
 *  @author Andres Osorio
 *  @date   2008-12-20
 */
class UCSBTuplesAnalyzer : public eventB, public eventV {
public: 
  /// Standard constructor
  UCSBTuplesAnalyzer( ) { }; 

  UCSBTuplesAnalyzer( const char *) { }; 
  
  UCSBTuplesAnalyzer( TFile *, const char *);
  
  UCSBTuplesAnalyzer( TChain *, TChain *, const char *);
  
  ~UCSBTuplesAnalyzer( ); ///< Destructor
  
  void Loop( );
  
  void findOrder();
  
  bool applyPreselection();
  
protected:
  
private:
  
  TFile       * fout;
  BasicOutput * histograms;
  
  //...copies of vectors
  std::vector<int>   jet_order;
  std::vector<float> jet_energy_cp;
  
};
#endif // UCSBTUPLESANALYZER_H
