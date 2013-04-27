#define L1TTUTree_cxx
#include "L1TTUTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "CommonIncludes.h"

void L1TTUTree::Initialize( )
{
  
  m_ttbits.push_back(24);
  m_ttbits.push_back(25);
  m_ttbits.push_back(31);

  m_output = new TFile("ttu-output.root","RECREATE");
  m_output->cd();
  m_histos = new BasicOutput("l1Analyzer");
  m_output->cd();

  m_totalevts = 0;

}


void L1TTUTree::Loop(Long64_t maxevts)
{
  
  if (fChain == 0) return;
  
  int runId = 0;
  bool m_info = false;
  int counter = 0;
  
  std::map<int,TH1D*>::iterator ttuDifItr;

  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  
  if ( maxevts > 0 )
    nentries = maxevts;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //////////////////////////////////////////////////////////////////////////////
    ///... start the analysis
    
    if( m_info) std::cout << Run << '\t'
                          << Event << '\n';

    if ( Run != runId )
    {
      runId = Run;
      std::cout << runId << std::endl;
      counter = 0;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    /// Timing from L1GtTtuAnalyzer
    
    runId = Run;
    
    ttuDifItr = m_histos->pacTTUDiff[0].find( runId );
    
    if ( ttuDifItr == m_histos->pacTTUDiff[0].end() )
      m_histos->addRunToBXDiff( runId );
    
    if ( HasRPCB > 0 )  {
      
      for( int i = 0; i < m_histos->MAX_BITS; ++i) {
        
        ttuDifItr = m_histos->pacTTUDiff[i].find( runId );
        
        if ( ttuDifItr  == m_histos->pacTTUDiff[i].end() )
          std::cout << "HasRPCb: run " << runId << " not present" << std::endl;
        
        float diff = PacTTU[i] ;

        
        if ( ( diff <= 0.0 && diff > -2) && i == 1 ) //i = 1 = 25
        {
          
          if ( counter < 20 ) 
          {
            
            std::cout << "TTU diff: " 
                      << diff << '\t'
                      << Run << '\t'
                      << Event << '\n';
            counter+=1;
          }                     
        }
        
        if ( diff != -99 ) 
        {
          (*ttuDifItr).second->Fill( diff );
        }
        
      }
      
    } else { 
      //This difference is not calculated for the RPC-endcap regions
      //std::cout << "HasRPCf: run " << l1tree->gmtNrpcf  << std::endl;
    }
    
    if ( HasDT > 0 )  {
      
      for( int i = 0; i < m_histos->MAX_BITS; ++i) {
        
        ttuDifItr = m_histos-> dtTTUDiff[i].find( runId );
        
        if ( ttuDifItr  == m_histos->dtTTUDiff[i].end() )
          std::cout << "HasDT: run " << runId << " not present" << std::endl;
        
        float diff = PacTTU[i] ;
        if ( diff != -99 ) 
        {
          (*ttuDifItr).second->Fill( diff );
        }
        
      }
      
    }
    
  }
  
  for( int i=0; i < 5; ++i) 
  {
    AlgBitsw1[i].reset();
    AlgBitsw2[i].reset();
    TechBits[i].reset();
  }
  
  std::cout << "total events: " << m_totalevts << std::endl;
  
  m_histos->makeHistory();
  
  m_output->Write();
  
}

void L1TTUTree::CheckConsistency(int maxevts ) 
{





}

void L1TTUTree::makeStudyOne() 
{






}

void L1TTUTree::Create(TTree *tree)
{
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  
  /*
    fChain->Branch("propertime"     , &propertime   , "propertime/D");
    fChain->Branch("triggerdec"     , &triggerdec   , "triggerdec/I");
  */
  
  Notify();

}
