#define L1Tree_cxx
#include "L1Tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "CommonIncludes.h"


void L1Tree::Initialize( )
{

  m_ttbits.push_back(24);
  m_ttbits.push_back(25);
  m_ttbits.push_back(31);
  
  m_singleMuBits.push_back(55); // L1_SingleMuOpen
  m_singleMuBits.push_back(56); // L1_SingleMu0
  m_singleMuBits.push_back(57); // L1_SingleMu3
  m_singleMuBits.push_back(58); // L1_SingleMu5
  m_singleMuBits.push_back(59); // L1_SingleMu7
  m_singleMuBits.push_back(60); // L1_SingleMu10
  m_singleMuBits.push_back(61); // L1_SingleMu14
  m_singleMuBits.push_back(62); // L1_SingleMu20
  
  m_output = new TFile("l1gt-output.root","RECREATE");
  m_output->cd();
  m_histos = new BasicOutput("l1Analyzer");
  m_output->cd();
  
  m_totalevts = 0;
  
}

void L1Tree::Loop(Long64_t maxevts)
{
  
  if (fChain == 0) return;

  int runId = 0;
  bool m_info = false;
  
  std::map<int,TH1D*>::iterator ttuDifItr;
  
  //std::vector<int>::iterator m_bitItr;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  
  if ( maxevts > 0 )
    nentries = maxevts;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    
    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if( m_info) std::cout << Run << '\t'
                          << Event << '\t'
                          << Run << '\t'
                          << Event << '\n';
  
    std::vector<int>::iterator itrMu;
          
    for( int i=0; i < 5; ++i) 
    {
      
      AlgBitsw1[i] = std::bitset<64>(gttw1[i] >> 50 ); //bitset is taking only the first 32 bit (64 bit)
      AlgBitsw2[i] = std::bitset<64>(gttw2[i]);
      TechBits[i]  = std::bitset<64>(gttt[i] );
      
      int k=0;
      for( itrMu = m_singleMuBits.begin(); itrMu != m_singleMuBits.end(); ++itrMu) 
      {
        bool trigDec = AlgBitsw1[i][(*itrMu) - 50 ];
                
        if( trigDec ) m_histos->h_muTriggBx[k]->Fill( i-2 );
        k+=1;
      }
      
    }

    for( itrMu = m_singleMuBits.begin(); itrMu != m_singleMuBits.end(); ++itrMu) 
    {
      bool trigDecW1 = AlgBitsw1[2][ ( (*itrMu) - 50 ) ];
      
      for( int i = 0; i < m_histos->MAX_BITS; ++i) {
        
        bool ttuTrig = false;
        
        for( int k=0; k <5; ++k) 
        {
          ttuTrig |= TechBits[k][ (i+24) ];
        }
                
        if( trigDecW1 && ttuTrig ) {
          m_histos->ttbitsVsAlgbits->Fill((*itrMu) , (i+24) );
          m_histos->ttbitsVsMuTriggers->Fill((*itrMu) , (i+24) );
          if ( i != 2 )  
            m_histos->ttbitsVsMuTriggers25->Fill((*itrMu) , (i+24) );
        }
                      
      }
                
    }
    
        
    if ( Run != runId )
    {
      runId = Run;
      if ( m_info ) std::cout << runId << std::endl;
    }
    
    ttuDifItr = m_histos->ttuBx[0].find( runId );
    
    if ( ttuDifItr == m_histos->ttuBx[0].end() )
      m_histos->addRunToBXDist( runId );
    
    for( int i = 0; i < m_histos->MAX_BITS; ++i) {
      
      ttuDifItr = m_histos->ttuBx[i].find( runId );
      
      //... look at the Bx position of this Technical Trigger Bits
      for( int k = 0; k < 5; ++k )
      {
        if ( TechBits[k][ (i+24) ] )
          (*ttuDifItr).second->Fill(k-2, 1);
      }
      
    }
    
    makeStudyOne();
    
    ++m_totalevts;
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

void L1Tree::CheckConsistency(int maxevts ) 
{

  if (fChain == 0) return;

  int runId = 0;
  int checkRunId = 0;
  std::string prev_file = std::string( fChain->GetDirectory()->GetPath() );
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nb = 0;

  if ( maxevts > 0 )
    nentries = maxevts;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    
    std::string current_file = std::string( fChain->GetDirectory()->GetPath() );
    
    if ( b_gmtEvBx != 0 && gmtEvBx != -99 ) {
    
      if ( prev_file != current_file || (Run != checkRunId ) ) 
      {
        
        std::cout << "Contains GMT: " << Run << '\t'
                  << "file: "         << current_file << '\n';
        
        checkRunId = Run;
        prev_file = current_file;
        
      }
      
    }

    if ( Run != runId )
      runId = Run;
          
  }
  
}

void L1Tree::makeStudyOne() 
{

  //Study 1: suggested by Luigi:
  //-check first the MuOpen events triggered at Bx=0
  //-check for TTU bits in vecinity (not necesarily at Bx=0
  //-check for the muon triggers having 

  //Mu triggers at bx=0;
  int pos=2;
  bool ttuDec=false;
  
  std::vector<int>::iterator itrMu;
  std::vector<int>::iterator itrTtu;
  

  for( itrMu = m_singleMuBits.begin(); itrMu != m_singleMuBits.end(); ++itrMu) 
  {
    
    bool trigDec = AlgBitsw1[pos][(*itrMu)];

    for( itrTtu = m_ttbits.begin(); itrTtu != m_ttbits.end(); ++itrTtu) 
    {
      
      ttuDec = false;
      
      for(int k=0; k < 5; ++k) 
      {
        ttuDec |= TechBits[k][ (*itrTtu) ]; //make the or; any bx for the moment
      }
      
      // 
      //std::cout << (*itrMu) << " " << trigDec << " " << (*itrTtu) << " " << ttuDec << std::endl;
      
      if ( trigDec && ttuDec) 
        m_histos->ttbitsVsMuTriggers->Fill( (*itrMu),(*itrTtu) );
      //
      
    }
    
  }
    
}

void L1Tree::Create(TTree *tree)
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



