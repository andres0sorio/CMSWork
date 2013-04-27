// $Id: $
// Include files 



// local
#include "RunAnalysis.h"
#include <bitset>

//-----------------------------------------------------------------------------
// Implementation file for class : RunAnalysis
//
// 2010-02-01 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RunAnalysis::RunAnalysis( const char * inputfile ) {
  
  m_infileA = new TFile(inputfile);
  
  if (m_infileA) {
    std::cout << "RunAnalysis> input file open. "
              << std::string(inputfile)
              << std::endl;
  } else {
    std::cout << "RunAnalysis> could not open input file> "
              << std::endl;
    exit(1);
  }

  //...............................................................

}

RunAnalysis::RunAnalysis( const char * inputfileA, const char * inputfileB) {

  ///
  m_inDataA = new std::ifstream( inputfileA , ifstream::in );
  m_inDataB = new std::ifstream( inputfileB , ifstream::in );
  
  m_noinputfile = false;
  
  if ( m_inDataA->bad() ) m_noinputfile = true;
  else m_noinputfile = false;
  
  if ( m_inDataB->bad() ) m_noinputfile |= true;
  else m_noinputfile = false;
  
  if ( m_noinputfile ) exit(1);

  m_l1tree  = new TChain("l1NtupleProducer/L1Tree");
  m_recomu  = new TChain("l1MuonRecoTreeProducer/MuonRecoTree" );
  m_l1extra = new TChain("l1ExtraTreeProducer/L1ExtraTree" ) ;
  m_l1ttu   = new TChain("l1gtAnalyzer/L1TTUTree" );
    
  while (1) {
    
    std::string dataA;
    
    if ( m_inDataA->fail()) break;
    (*m_inDataA) >> dataA;
    if ( m_inDataA->eof() ) break;
    
    m_l1tree->Add(  dataA.c_str() );
    m_recomu->Add(  dataA.c_str() );
    m_l1extra->Add( dataA.c_str() );
    
    std::cout << " RunAnalysis: adding file" << std::endl;
    
  }
  
  while (1) {
    
    std::string dataB;
    
    if ( m_inDataB->fail()) break;
    (*m_inDataB) >> dataB;
    if ( m_inDataB->eof() ) break;
    
    m_l1ttu->Add( dataB.c_str() );
  
    std::cout << " RunAnalysis: adding file" << std::endl;
  
  }
  
  m_inDataA->close();
  m_inDataB->close();
  
}

void RunAnalysis::Initialize( ) 
{
  
  ///////////////////////////////////////////////////////////////////////////////
  
  l1tree = new L1Tree(m_l1tree,"L1Analysis");
  
  recomuons = new MuonRecoTree(m_recomu,"MuonAnalysis");
  
  l1extra = new L1ExtraTree(m_l1extra,"L1ExtraAnalysis");
  
  l1ttu = new L1TTUTree(m_l1ttu,"L1TTUTree"); 
  
  ///////////////////////////////////////////////////////////////////////////////
  
  m_ttbits.push_back(24);
  m_ttbits.push_back(25);
  m_ttbits.push_back(31);

  m_NttuBits[24] = 0;
  m_NttuBits[25] = 0;
  m_NttuBits[31] = 0;
  
  m_info = false;
  
  m_output = new TFile("output.root","RECREATE");
  m_output->cd();
  m_histos = new BasicOutput("l1Analyzer");
  m_output->cd();
  
  m_info = false;
  
}

void RunAnalysis::Initialize( bool useTtuTree ) 
{

  ///////////////////////////////////////////////////////////////////////////////
  
  m_infileA->cd();
  m_infileA->cd("l1NtupleProducer");
  TTree *t1 = (TTree*)gDirectory->Get("L1Tree");
  if (t1) l1tree = new L1Tree(t1,"L1Analysis");
  
  m_infileA->cd();
  m_infileA->cd("l1MuonRecoTreeProducer");
  t1 = (TTree*)gDirectory->Get("MuonRecoTree");
  if (t1) recomuons = new MuonRecoTree(t1,"MuonAnalysis");
  
  m_infileA->cd();
  m_infileA->cd("l1ExtraTreeProducer");
  t1 = (TTree*)gDirectory->Get("L1ExtraTree");
  if (t1) l1extra = new L1ExtraTree(t1,"L1ExtraAnalysis");
  
  if ( useTtuTree == true ) 
  {
    m_infileB->cd();
    m_infileB->cd("l1gtAnalyzer");
    t1 = (TTree*)gDirectory->Get("L1TTUTree");
    if (t1) l1ttu = new L1TTUTree(t1,"L1TTUTree"); 
    
  } else l1ttu = NULL;

  ///////////////////////////////////////////////////////////////////////////////
  
  m_ttbits.push_back(24);
  m_ttbits.push_back(25);
  m_ttbits.push_back(31);

  m_NttuBits[24] = 0;
  m_NttuBits[25] = 0;
  m_NttuBits[31] = 0;
  
  m_info = false;
  
  m_output = new TFile("output.root","RECREATE");
  m_output->cd();
  m_histos = new BasicOutput("l1Analyzer");
  m_output->cd();
  
  m_info = false;
  
}

//=============================================================================
// Destructor
//=============================================================================

RunAnalysis::~RunAnalysis() {

  m_output->Write();
  m_output->Close();
  
  //delete m_histos;
    
  if ( l1tree )
    delete l1tree;
  
  if ( recomuons )
    delete recomuons;
  
  if ( l1extra )
    delete l1extra;
  
  if ( l1ttu )
    delete l1ttu;
  
} 

//=============================================================================
void RunAnalysis::Loop( Long64_t maxevts) 
{
  
  std::cout << "----------------------------------------------------------------" << std::endl;
  
  if (l1tree->fChain == 0) return;
  
  Long64_t nentries = l1tree->fChain->GetEntriesFast();
  
  if ( maxevts > 0 )
    nentries = maxevts;
  
  Long64_t nbytes = 0, nb = 0;
  
  int runId = 0;
  int n_GB_Muons = 0;
  int n_TR_Muons = 0;
  int n_SA_Muons = 0;
  int n_RpcBarrel = 0;
  int n_RpcForward = 0;
  
  bool has_GL_muon = false;
  bool has_TR_muon = false;
  bool has_SA_muon = false;
  
  int n_NRecHits = 0;
  int n_TR_MuonsEvt = 0;
  double beamSpot_x0 = 0.0;
  double beamSpot_y0 = 0.0;
      
  std::map<int,TH1D*>::iterator ttuDifItr;
  
  //m_info = true;
    
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    has_GL_muon = false;
    has_TR_muon = false;
    n_TR_MuonsEvt = 0;

    Long64_t ientry =l1tree-> LoadTree(jentry);
    if (ientry < 0) break;
    
    ientry = recomuons->LoadTree(jentry);
    ientry = l1ttu->LoadTree(jentry);
    ientry = l1extra->LoadTree(jentry);

    nb = l1tree->fChain->GetEntry(jentry);   nbytes += nb;
    nb = l1extra->fChain->GetEntry(jentry);   nbytes += nb;
    nb = recomuons->fChain->GetEntry(jentry);   nbytes += nb;
    nb = l1ttu->fChain->GetEntry(jentry);   nbytes += nb;

    ///... start the analysis
    
    if( m_info) std::cout << l1ttu->Run << '\t'
                          << l1ttu->Event << '\t'
                          << l1tree->Run << '\t'
                          << l1tree->Event << '\n';
    
    beamSpot_x0 = recomuons->BeamSpotX;
    beamSpot_y0 = recomuons->BeamSpotY;

    m_histos->h_beamSpot->Fill( beamSpot_x0, beamSpot_y0 );
            
    ///... Technical trigger bits information ...
    
    for( int i=0; i < 5; ++i) 
    {
      TechBits[i] = std::bitset<64>(l1tree->gttt[i]);
    }
    
    ///Cuts
    if ( Cut() )
      continue;
    
    for( m_bitItr = m_ttbits.begin(); m_bitItr !=  m_ttbits.end(); ++m_bitItr ) 
    {
      if ( TechBits[2][ (*m_bitItr) ] ) 
      {
        m_ttuItr = m_NttuBits.find( (*m_bitItr) );
        m_ttuItr->second++;
      }
      //... look at the Bx position of this Technical Trigger Bits
      for( int i = 0; i < 5; ++i )
      {
        if ( TechBits[i][ (*m_bitItr) ] )
          m_histos->TechTrigBx[ (*m_bitItr) ]->Fill(i-2, 1);
        
      }
            
    }
    
    bool has_RpcBarrelBx0 = false;
    int m_NRpcb  = l1tree->gmtNrpcb;
    int m_NRpcf  = l1tree->gmtNrpcf;
    
    n_RpcBarrel  +=m_NRpcb;
    n_RpcForward +=m_NRpcf;
       
    for( int i = 0; i < m_NRpcb; ++i )
    {
      
      if ( l1tree->gmtBxrpcb[0] == 0 )
        has_RpcBarrelBx0 = true;
      
      if( m_info ) std::cout << l1tree->gmtBxrpcb[i] << '\t'
                             << l1tree->gmtPtrpcb[i] << '\t'
                             << l1tree->gmtCharpcb[i] << '\t'
                             << l1tree->gmtEtarpcb[i] << '\t'
                             << l1tree->gmtPhirpcb[i] << '\n';
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //    
    //... Work out on the muons
    
    int Bx0Pos = 2;
    
    int maxmuons = recomuons->Nmuons;
    for (int i = 0; i < maxmuons; ++i) 
    {
      
      if ( recomuons->Muon_type[i] == 0 ) //... Global 205 
      {
        double correction = beamSpot_x0*sin( recomuons->Muons_phi[i] ) 
          + beamSpot_y0*cos(  recomuons->Muons_phi[i] );
        
        double d0 = recomuons->Muons_d0[i] + correction;
        
        m_histos->h_GB_muon_Pt->Fill(recomuons->Muons_pt[i]);
        m_histos->h_GB_muon_Phi->Fill(recomuons->Muons_phi[i]);
        m_histos->h_GB_muon_Eta->Fill(recomuons->Muons_eta[i]);
        m_histos->h_GB_caloComp->Fill(recomuons->Muons_calocomp[i]);
        m_histos->h_GB_chi2dof->Fill(recomuons->Muons_normchi2[i]);
        m_histos->h_GB_muon_d0->Fill(d0);
        m_histos->h_GB_muon_d0s->Fill(recomuons->Muons_d0s[i]);
        
        m_histos->hh_etaphi_GB->Fill( recomuons->Muons_eta[i], recomuons->Muons_phi[i] );
        
        has_GL_muon = true;
        
        for( int k=0; k < m_histos->SEL_BITS; ++k) 
        {
          int selbit = m_histos->m_selectedBits[k];
          //std::cout << "selbit " << selbit << " " << TechBits[2][ selbit ] << std::endl;
          
          if ( selbit == 25 ) Bx0Pos = 3;
          else Bx0Pos = 2;
          
          if ( TechBits[Bx0Pos][ selbit ] ) 
          {
            
            m_histos->hc_GB_muon_Pt[k]->Fill(recomuons->Muons_pt[i] );
            m_histos->hc_GB_muon_Eta[k]->Fill(recomuons->Muons_eta[i] );
            m_histos->hc_GB_muon_Phi[k]->Fill(recomuons->Muons_phi[i] );
            m_histos->hc_GB_muon_Calo[k]->Fill(recomuons->Muons_calocomp[i] );
            m_histos->hc_GB_muon_chi2dof[k]->Fill(recomuons->Muons_normchi2[i] );
            m_histos->hc_GB_muon_d0[k]->Fill( d0 );
            m_histos->hc_GB_muon_d0s[k]->Fill(recomuons->Muons_d0s[i] );

            m_histos->hh_etaphi_GB_Bit[k]->Fill( recomuons->Muons_eta[i], recomuons->Muons_phi[i]);
            
            //std::cout << "Global Muons> Filling run " << runId << " " << l1tree->Event << " bit " << (selbit) << std::endl;
            
          }
          
        }
              
        ++n_GB_Muons;
        
      } else if ( recomuons->Muon_type[i] == 2 ) { //Tracker Muons

        double correction = beamSpot_x0*sin( recomuons->Muons_phi[i] ) 
          + beamSpot_y0*cos(  recomuons->Muons_phi[i] );
        
        double d0 = recomuons->Muons_d0[i] + correction;
        
        m_histos->h_TR_muon_Pt->Fill(recomuons->Muons_tr_pt[i]);
        m_histos->h_TR_muon_Phi->Fill(recomuons->Muons_tr_phi[i]);
        m_histos->h_TR_muon_Eta->Fill(recomuons->Muons_tr_eta[i]);
        m_histos->h_TR_caloComp->Fill(recomuons->Muons_tr_calocomp[i]);
        m_histos->h_TR_chi2dof->Fill(recomuons->Muons_tr_normchi2[i]);
        m_histos->h_TR_muon_d0->Fill( d0 );
        m_histos->h_TR_muon_d0s->Fill(recomuons->Muons_tr_d0s[i]);
        
        m_histos->hh_etaphi_TR->Fill( recomuons->Muons_tr_eta[i], recomuons->Muons_tr_phi[i]);
        
        has_TR_muon = true;
        for( int k=0; k < m_histos->SEL_BITS; ++k) 
        {
          int selbit = m_histos->m_selectedBits[k];
          //std::cout << "selbit " << selbit << " " << TechBits[2][ selbit ] << std::endl;
          
          if ( selbit == 25 ) Bx0Pos = 3;
          else Bx0Pos = 2;
          
          if ( TechBits[Bx0Pos][ selbit ] ) 
          {
            
            //std::cout << "selbit " << selbit << " " 
            //          << TechBits[2][ selbit ] << " " 
            //          << recomuons->Muons_pt[i] << " " 
            //          << recomuons->Muons_eta[i] << std::endl;
            
            m_histos->hc_TR_muon_Pt[k]->Fill(recomuons->Muons_tr_pt[i] );
            m_histos->hc_TR_muon_Eta[k]->Fill(recomuons->Muons_tr_eta[i] );
            m_histos->hc_TR_muon_Phi[k]->Fill(recomuons->Muons_tr_phi[i] );
            m_histos->hc_TR_muon_Calo[k]->Fill(recomuons->Muons_tr_calocomp[i] );
            m_histos->hc_TR_muon_chi2dof[k]->Fill(recomuons->Muons_tr_normchi2[i] );
            m_histos->hc_TR_muon_d0[k]->Fill( d0 );
            m_histos->hc_TR_muon_d0s[k]->Fill(recomuons->Muons_tr_d0s[i] );
            
            m_histos->hh_etaphi_TR_Bit[k]->Fill( recomuons->Muons_tr_eta[i], recomuons->Muons_tr_phi[i]);
            
            //std::cout << "Tracker Muons> Filling run " << runId << " " << l1tree->Event << " bit " << (selbit) << std::endl;
            
          }
          
        }
        

        ++n_TR_Muons;
        ++n_TR_MuonsEvt;
        
        
        
      } else if ( recomuons->Muon_type[i] == 1 ) { 
        
        m_histos->h_SA_muon_Pt->Fill(recomuons->Muons_sa_pt[i]);
        m_histos->h_SA_muon_Phi->Fill(recomuons->Muons_sa_phi[i]);
        m_histos->h_SA_muon_Eta->Fill(recomuons->Muons_sa_eta[i]);
        
        m_histos->hh_etaphi_SA->Fill( recomuons->Muons_sa_eta[i], recomuons->Muons_sa_phi[i]);
        
        ++n_SA_Muons;
        has_SA_muon = true;

        for( int k=0; k < m_histos->SEL_BITS; ++k) 
        {
      
          int selbit = m_histos->m_selectedBits[k];
          //std::cout << "selbit " << selbit << " " << TechBits[2][ selbit ] << std::endl;
          
          if ( selbit == 25 ) Bx0Pos = 3;
          else Bx0Pos = 2;
          
          if ( TechBits[Bx0Pos][ selbit ] ) 
          {
            
            ///std::cout << "selbit " << selbit << " " 
            ///          << TechBits[2][ selbit ] << " " 
            //           << recomuons->Muons_pt[i] << " " 
            //           << recomuons->Muons_eta[i] << std::endl;
            
            m_histos->hc_SA_muon_Pt[k]->Fill(recomuons->Muons_sa_pt[i] );
            m_histos->hc_SA_muon_Eta[k]->Fill(recomuons->Muons_sa_eta[i] );
            m_histos->hc_SA_muon_Phi[k]->Fill(recomuons->Muons_sa_phi[i] );

            m_histos->hh_etaphi_SA_Bit[k]->Fill( recomuons->Muons_sa_eta[i] , recomuons->Muons_sa_phi[i] );
            
          }
          
        }
        
      } else {}
      ///std::cout << "--------------------------" << std::endl;
      
    }
    
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    /// Timing from L1GtTtuAnalyzer
    
    if ( l1ttu->Run != runId ) 
    {
      runId = l1ttu->Run;
      if ( m_info ) std::cout << runId << std::endl;
    }
    
    ttuDifItr = m_histos->pacTTUDiff[0].find( runId );
    
    if ( ttuDifItr == m_histos->pacTTUDiff[0].end() )
      m_histos->addRunToBXDiff( runId );

    if ( l1ttu->HasRPCB > 0 )  {
      
      for( int i = 0; i < m_histos->MAX_BITS; ++i) {
        
        ttuDifItr = m_histos->pacTTUDiff[i].find( runId );
      
        if ( ttuDifItr  == m_histos->pacTTUDiff[i].end() )
          std::cout << "HasRPCb: run " << runId << " not present" << std::endl;
      
        float diff = l1ttu->PacTTU[i] ;

        std::cout << "diff" << diff << std::endl;
        

        if ( ( diff <= 0.0 ) && (*m_bitItr) == 25 ) 
        {
          std::cout << "TTU diff: " 
                    << diff << '\t'
                    << l1ttu->Run << '\t'
                    << l1ttu->Event << '\n';
        }
        
        if ( diff != -99 ) 
        {
          //std::cout << "Values read: " << i << " " <<  l1ttu->PacTTU[i] << std::endl;
          (*ttuDifItr).second->Fill( diff );
          //std::cout << "PacTTU> Filling run " << runId << " " << l1tree->Event << " bit " << (i+24) 
          //        << " " << diff << " Rpcb" << std::endl;
        }
        
      }
            
    } else { 
      
      //This difference is not calculated for the RPC-endcap regions
      //std::cout << "HasRPCf: run " << l1tree->gmtNrpcf  << std::endl;
      
      if ( l1tree->gmtNrpcf > 0 ) 
      {
        
        int bxRpcf = l1tree->gmtBxrpcf[0];
        
        for( int i = 0; i < m_histos->MAX_BITS; ++i) {
          
          ttuDifItr = m_histos->pacTTUDiff[i].find( runId );
          
          if ( ttuDifItr  == m_histos->pacTTUDiff[i].end() )
            std::cout << "HasRPCf: run " << runId << " not present" << std::endl;
          
          //Loop over bits and get their bx:
        
          for( m_bitItr = m_ttbits.begin(); m_bitItr !=  m_ttbits.end(); ++m_bitItr ) 
          {
            //... look at the Bx position of this Technical Trigger Bits
            for( int k = 0; k < 5; ++k )
            {
              if ( TechBits[k][ (*m_bitItr) ] )  
              {
                int bxBit  = k-2;
                float diff = bxRpcf - bxBit;
                //std::cout << "PacTTU> Filling run " << runId << " " << l1tree->Event << " bit " 
                //         << (i+24) << " " << diff << " Rpcbf";
                //std::cout << "PacTTU> pac: " << bxRpcf << " tt" <<  bxBit << std::endl;
                (*ttuDifItr).second->Fill( diff );

                if ( ( diff == 0 || diff == -1 ) && (*m_bitItr) == 25 ) 
                {
                  std::cout << "TTU diff: " 
                            << diff << '\t'
                            << l1ttu->Run << '\t'
                            << l1ttu->Event << '\n';
                }
                

              }
            }
          }
        } //... MAX_BITS
      }
    }
    
    if ( l1ttu->HasDT > 0 )  {
    
      for( int i = 0; i < m_histos->MAX_BITS; ++i) {

        ttuDifItr = m_histos-> dtTTUDiff[i].find( runId );
              
        if ( ttuDifItr  == m_histos->dtTTUDiff[i].end() )
          std::cout << "HasDT: run " << runId << " not present" << std::endl;

        float diff = l1ttu->PacTTU[i] ;
        if ( diff != -99 ) 
        {
          (*ttuDifItr).second->Fill( diff );
          //std::cout << "PacTTU> Filling run " << runId << " " << l1tree->Event << " bit " 
          //         << (i+24) << " " << diff << " DT" << std::endl;
        }
        
      }
      
    }
    

    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    // RPC RecHits

    for (int i=0; i < l1ttu->nRpcHits; ++i )
    {
      
      ++n_NRecHits;
      
    }

    m_histos->h_NRecHit_Evt->Fill(n_NRecHits);
    
    m_histos->h_NTrTracks_Evt->Fill(n_TR_MuonsEvt);

    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    
    for( int i=0; i < 5; ++i) 
    {
      TechBits[i].reset();
    }
    n_NRecHits = 0;
    
    // if (Cut(ientry) < 0) continue;
    
  }
  
  
  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  m_histos->makeHistory();
    
  

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  
  std::cout << nentries << std::endl;
  std::cout << "GBL-Muons: " << n_GB_Muons << std::endl;
  std::cout << "TTBit 31: " 
            << m_NttuBits[24] << '\t'
            << m_NttuBits[25] << '\t'
            << m_NttuBits[31] << std::endl;
  std::cout << n_RpcBarrel << '\t'
            << n_RpcForward << '\n';
  
  m_output->Write();
  
}


bool RunAnalysis::Cut( )
{
  
  //filter on the AND of both BPTX triggers
  if ( TechBits[2][0] == 0 ) {
    //std::cout << "no collisions! TTbit[0] = 0" << std::endl;
    return true;
  }
  else {
    //std::cout << "we got collisions! TTbit[0] = 1" << std::endl;
    return false;
  }
  
  //Apply here some collision quality cuts
  int maxmuons = recomuons->Nmuons;
  int nTrTrck = 0;
  
  if ( maxmuons == 0 ) return false;
  
  //Confirm collision
  double beamSpot_x0 = recomuons->BeamSpotX;
  double beamSpot_y0 = recomuons->BeamSpotY;

  for (int i = 0; i < maxmuons; ++i) 
  {
    if ( recomuons->Muon_type[i] == 2 ) 
    {
      double correction = beamSpot_x0*sin( recomuons->Muons_phi[i] ) 
        + beamSpot_y0*cos(  recomuons->Muons_phi[i] );
      
      double d0 = recomuons->Muons_d0[i] + correction;
      
      if ( fabs(d0) < 0.20 ) 
      {
        ++nTrTrck; 
      }
      
    }
    
  }
  
  if ( nTrTrck >= 3 )
    return false; //keep this event as it confirms collision
  else return true;
  
  return false;
  
}
