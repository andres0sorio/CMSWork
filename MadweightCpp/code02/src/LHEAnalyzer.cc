// $Id: $
// Include files 



// local
#include "LHEAnalyzer.h"
#include "boost/bind.hpp"
#include "LHCOParser.h"

//-----------------------------------------------------------------------------
// Implementation file for class : LHEAnalyzer
//
// 2012-09-19 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
LHEAnalyzer::LHEAnalyzer(  const char * infile ) {

  m_chain = new TChain("LHEF");
  m_chain->Add(infile);
  m_treeReader = new ExRootTreeReader(m_chain);
  m_lhco_output = new std::ofstream("verif.lhco");
  
  //PGS codes
  m_pgsCodes["photon"]   = 0;
  m_pgsCodes["electron"] = 1;
  m_pgsCodes["muon"]     = 2;
  m_pgsCodes["htau"]     = 3;
  m_pgsCodes["jet"]      = 4;
  m_pgsCodes["met"]      = 6;
  
  // MG order - external legs
  m_jetsMG  ["ujet"]    = 4;
  m_jetsMG  ["~djet"]   = 5;
  m_bjetsMG ["bjet"]    = 3;
  m_bjetsMG ["~bjet"]   = 6;
  m_muonsMG ["muon"]    = 8;
  m_metMG   ["met"]     = 7;

  //Order by with the data is present 1,2,3,4,5,6
  //initialy set to first permutation

  m_pgsOrder[1]     = 1;
  m_pgsOrder[2]     = 2;
  m_pgsOrder[3]     = 3;
  m_pgsOrder[4]     = 4;
  m_pgsOrder[5]     = 5;
  m_pgsOrder[6]     = 6;

  ///
  m_trueOrder[1] =   2; //  u
  m_trueOrder[2] =  -1; // ~d
  m_trueOrder[3] =   5; //  b
  m_trueOrder[4] =  -5; // ~b
  m_trueOrder[5] =  13; // mu
  m_trueOrder[6] = -14; // nu
  
  m_debug = false;

  m_histos = new Histograms("control_histograms.root");
  
  m_histos->SetOptions();
  


}

//=============================================================================
// Destructor
//=============================================================================

LHEAnalyzer::~LHEAnalyzer() { 


} 

//=============================================================================

void LHEAnalyzer::Loop() 
{
  
  Long64_t numberOfEntries = m_treeReader->GetEntries();
  
  // Get pointers to branches used in this analysis
  TClonesArray *branchGenParticle = m_treeReader->UseBranch("Particle");

  TIter particleItr( branchGenParticle );

  TList * v_Particles = new TList();
  
  Double_t vxTmp = 1.0;
  
  TParticle * p1;
  
  // Loop over all events
  for(Long64_t entry = 0; entry < numberOfEntries; ++entry)
  {
    
    if ( entry > 999) break;

    // Load selected branches with data from specified event
    m_treeReader->ReadEntry(entry);
    
    particleItr.Reset();

    TRootLHEFParticle * particle;

    int finalState = 0;

    std::stringstream h_Top;

    std::map<int,float> eta_quarks;
    std::map<int,float> pt_quarks;
    
    while(( particle = (TRootLHEFParticle*) particleItr.Next()))
    {

      if ( particle->PID  == 6 ) {
        
        m_histos->h_1DHistograms["E"]->Fill( particle->E );
        m_histos->h_1DHistograms["Px"]->Fill( particle->Px );
        m_histos->h_1DHistograms["Py"]->Fill( particle->Py );
        m_histos->h_1DHistograms["Pz"]->Fill( particle->Pz );
        
        h_Top << "topMass" << 1;
        
        float invmass = particle->M;
                
        m_histos->h_1DHistograms[h_Top.str()]->Fill ( invmass );
        
        h_Top.str("");
        
      }
      
      if ( particle->PID  == -6 ) {
        
        m_histos->h_1DHistograms["E"]->Fill( particle->E );
        m_histos->h_1DHistograms["Px"]->Fill( particle->Px );
        m_histos->h_1DHistograms["Py"]->Fill( particle->Py );
        m_histos->h_1DHistograms["Pz"]->Fill( particle->Pz );
        
        h_Top << "topMass" << 2;

        float invmass = particle->M;
        
        m_histos->h_1DHistograms[h_Top.str()]->Fill ( invmass );
                  
        h_Top.str("");
        
      }
      
      if ( particle->Status == 1 ) {
        
        ++finalState;
        
        p1 = new TParticle( Int_t( particle->PID ), 
                            Int_t( particle->Status ),
                            Int_t( particle->Mother1 ),
                            Int_t( particle->Mother2 ),
                            Int_t( -1 ),
                            Int_t( -1 ),
                            Double_t( particle->Px ),
                            Double_t( particle->Py ),
                            Double_t( particle->Pz ),
                            Double_t( particle->E  ),
                            vxTmp, vxTmp, vxTmp, vxTmp );
        
        v_Particles->Add( p1 );
        
        if ( m_debug ) std::cout << "new particle found " << particle->PID << " status " << particle->Status << std::endl;
        
      }
      
    }
    
    if ( m_debug ) std::cout << "total final states n " << finalState << " " << v_Particles->GetSize() << std::endl;
        
    /////Run analysis on Pythia final states - Export to LHCO format
    
    int max_fs = v_Particles->GetSize();
    int truepos = 0;
    std::map<int,TParticle*> v_pos_part;
    std::map<int,int>::iterator trueposItr;
    
    for(int i = 0; i < max_fs; ++i ) {
      
      p1 = (TParticle*)v_Particles->At(i);
      
      int pid = p1->GetPdgCode();
      
      trueposItr = std::find_if( m_trueOrder.begin(), 
                                 m_trueOrder.end(),
                                 boost::bind( & std::map<int,int>::value_type::second, _1 ) 
                                 == pid );
      
      if( trueposItr == m_trueOrder.end() ) 
        std::cout << " we got a problem" << std::endl;
      else 
        truepos = m_pgsOrder[ (*trueposItr).first ];
      
      if ( m_debug ) std::cout << i << " this " << pid << " goes in " << truepos << std::endl;
      
      v_pos_part[ truepos ] = p1;
      
    }
    
    std::map<int,TParticle*>::iterator posItr;

    /// Reconstruct top inv. mass from its final states
    TLorentzVector partvec(0.0, 0.0, 0.0, 0.0);
    
    for( int k = 0; k < 3; ++k ) {
      
      partvec += TLorentzVector( v_pos_part[k+1]->Px(),
                                 v_pos_part[k+1]->Py(),
                                 v_pos_part[k+1]->Pz(),
                                 v_pos_part[k+1]->Energy() );
      
    }

    m_histos->h_1DHistograms["topMassRec1"]->Fill( partvec.M() );
    
    partvec.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );
    
    for( int k = 3; k < 6; ++k ) {
      
      partvec += TLorentzVector( v_pos_part[k+1]->Px(),
                                 v_pos_part[k+1]->Py(),
                                 v_pos_part[k+1]->Pz(),
                                 v_pos_part[k+1]->Energy() );
      
    }
    
    m_histos->h_1DHistograms["topMassRec2"]->Fill( partvec.M() );
    
    partvec.SetPxPyPzE( 0.0, 0.0, 0.0, 0.0 );

      
    // save data in the specified LHCO format

    pgsEvent * event = new pgsEvent;
    
    event->nEvent = entry;
    event->triggWord = 1000;
        
    int idpart = 2;
    int type = 0;
    
    for( posItr = v_pos_part.begin(); posItr != v_pos_part.end(); ++posItr ) {
      
      pgsObject * pgs = new pgsObject();
      pgs->idpart = idpart;

      if ( abs((*posItr).second->GetPdgCode()) <= 6 ) type =  m_pgsCodes["jet"];
      else if ( abs((*posItr).second->GetPdgCode()) == 11 ) 
        type =  m_pgsCodes["electron"];
      else if ( abs((*posItr).second->GetPdgCode()) == 13 ) 
        type =  m_pgsCodes["muon"];
      else if ( abs((*posItr).second->GetPdgCode()) == 15 ) 
        type =  m_pgsCodes["htau"];
      else if ( abs((*posItr).second->GetPdgCode()) == 12 ||
                abs((*posItr).second->GetPdgCode()) == 14 ||
                abs((*posItr).second->GetPdgCode()) == 16  )
        type =  m_pgsCodes["met"];
      else if ( abs((*posItr).second->GetPdgCode()) == 22 )
        type =  m_pgsCodes["photon"];
      else 
        std::cout << " we have a problem " << std::endl;
      
      pgs->type   = type;

      pgs->eta    = (*posItr).second->Eta();
      pgs->phi    = (*posItr).second->Phi();
      pgs->pt     = (*posItr).second->Pt();
      pgs->jmas   = (*posItr).second->GetMass();

      if ( abs((*posItr).second->GetPdgCode()) == 11 ||
           abs((*posItr).second->GetPdgCode()) == 13 ||
           abs((*posItr).second->GetPdgCode()) == 15  ) {
        
        if ( (*posItr).second->GetPdgCode() > 0 ) 
          pgs->ntrk   = -1.0;
        else 
          pgs->ntrk   =  1.0;
        
      } else 
        pgs->ntrk   =  0.0;

      if ( abs((*posItr).second->GetPdgCode()) == 5 ) {
        pgs->btag   = 2.0;
      } else pgs->btag = 0.0;
            
      pgs->hadem  = 0.0;
      pgs->dum1   = 0.0;
      pgs->dum2   = 0.0;

      ///Fill in control histograms

      float eta = (*posItr).second->Eta();
      float pt = (*posItr).second->Pt();
      
      if( (*posItr).second->GetPdgCode() == 5 ) {
        m_histos->h_2DHistograms["PtEta_bquark"]->Fill(eta, pt);
        eta_quarks[5] = eta;
        pt_quarks[5] = pt;
      }
      else if ( (*posItr).second->GetPdgCode() == -5 ) {
        m_histos->h_2DHistograms["PtEta_abquark"]->Fill( eta, pt);
        eta_quarks[-1] = eta;
        pt_quarks[-1] = pt;
      }
      else if ( (*posItr).second->GetPdgCode() == 2 ) {
        m_histos->h_2DHistograms["PtEta_uquark"]->Fill( eta, pt);
        eta_quarks[2] = eta;
        pt_quarks[2] = pt;
      }
      else if ( (*posItr).second->GetPdgCode() == -1 ) {
        m_histos->h_2DHistograms["PtEta_adquark"]->Fill(eta, pt);
        eta_quarks[-1] = eta;
        pt_quarks[-1] = pt;
        
      }
      else {}
      
      if ( m_debug ) std::cout << (*posItr).first << " " << (*posItr).second->GetPdgCode() << std::endl;
      
      event->data.push_back( pgs );
           
      ++idpart;
      
    }
     
    (*m_lhco_output) << (*event);

    m_histos->h_2DHistograms["Eta_bu_quark"]->Fill( eta_quarks[5], eta_quarks[2] );
    m_histos->h_2DHistograms["Pt_bu_quark"]->Fill( pt_quarks[5], pt_quarks[2] );

    m_histos->h_ProfileHistograms["Eta_bu_quark_prof"]->Fill( eta_quarks[5], eta_quarks[2], 1);
    m_histos->h_ProfileHistograms["Eta_bd_quark_prof"]->Fill( eta_quarks[5], eta_quarks[-1], 1);
    m_histos->h_ProfileHistograms["Pt_bu_quark_prof"]->Fill( pt_quarks[5], pt_quarks[2], 1);
    m_histos->h_ProfileHistograms["Pt_bd_quark_prof"]->Fill( pt_quarks[5], pt_quarks[-1], 1);

    eta_quarks.clear();
    pt_quarks.clear();
        
    delete event;

    //break;


    //.......

    v_Particles->Delete();
    v_pos_part.clear();
    
  }
  
  m_lhco_output->close();


  // 
  delete m_histos;
      
  
}


