// $Id: $
// Include files 

#include "CommonIncludes.h"
#include "TFile.h"
#include "TH1D.h"


int main(int iargv, const char **argv) {
  
  if(iargv < 2 ) {
    std::cout << "usage : extract> [infile]" << std::endl;
    return 0;
  }
  
  const char *infile  = argv[1];

  std::ofstream *m_out = new std::ofstream("rpcdata.dat",ofstream::out);
  
  TFile * f1 = new TFile(infile,"READ");
  f1->cd();
  TH1D * h1 = (TH1D*)gDirectory->FindObjectAny("Occtot");
  int maxbins=0;
  
  if (  h1 ) {
    
    maxbins = h1->GetNbinsX();
    
    for ( int k=1; k <= maxbins; ++k ) 
    {
      double x = k + 0.0;
      double y = h1->GetBinContent(k);
      if ( k < 5 ) std::cout << x << '\t' << y << std::endl;
      (*m_out) << x << '\t' << y << '\n';
    }
    
  } else return 0;

  std::cout << "max points: " << maxbins << std::endl;
  
  m_out->close();
  delete m_out;
  
  return 1;
  
}

