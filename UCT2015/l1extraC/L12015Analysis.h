//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Dec 17 11:47:49 2012 by ROOT version 5.32/00
// from TTree L12015Analysis/L12015Analysis
// found on file: L1Tree-short.root
//////////////////////////////////////////////////////////

#ifndef L12015Analysis_h
#define L12015Analysis_h

#include <L1UpgradeNtuple.h>
#include <L1RateTree.h>
#include <UCTRateTree.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class L12015Analysis : public L1UpgradeNtuple {
  
 public :
  
  L12015Analysis() {};
  
  L12015Analysis(const char * infile);

  L12015Analysis(const char * infile, const char *ntuple);

  virtual ~L12015Analysis();

  virtual void Loop();

  L1RateTree * m_l1treeEG;
  UCTRateTree *m_upgradetreeEG;

  L1RateTree * m_l1treeEGIso;
  UCTRateTree *m_upgradetreeEGIso;
  
  L1RateTree * m_l1treeTau;
  UCTRateTree *m_upgradetreeTau;

  L1RateTree * m_l1treeIsoTau;
  UCTRateTree *m_upgradetreeIsoTau;
  
  void RunL1RateEG( const char * var, const char * selec, const char * binning, const char *name );
  
  void RunUCTRateEG( const char * var, const char * selec, const char * binning, const char *name );

  void RunL1RateEGIso( const char * var, const char * selec, const char * binning, const char *name );
  
  void RunUCTRateEGIso( const char * var, const char * selec, const char * binning, const char *name );

  void RunL1RateTau( const char * var, const char * selec, const char * binning, const char *name );
  
  void RunUCTRateTau( const char * var, const char * selec, const char * binning, const char *name );

  void RunL1RateIsoTau( const char * var, const char * selec, const char * binning, const char *name );
  
  void RunUCTRateIsoTau( const char * var, const char * selec, const char * binning, const char *name );

 private:
  
  bool m_debug;

};

#endif

#ifdef L12015Analysis_cxx

L12015Analysis::L12015Analysis(const char * infile) : L1UpgradeNtuple( std::string( infile ) )
{
  
  std::cout << " Ready to make plots!: fChain " << fChain << std::endl;
  
}

L12015Analysis::L12015Analysis(const char * infile, const char * ntuples) : L1UpgradeNtuple( std::string( infile ), std::string( ntuples ) )
{
  
  std::cout << " Ready to make plots!: fChain " << fChain << std::endl;
  std::cout << " L12015Analysis will use: " << std::string( ntuples ) << std::endl;
  
}

L12015Analysis::~L12015Analysis()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

#endif // #ifdef L12015Analysis_cxx
