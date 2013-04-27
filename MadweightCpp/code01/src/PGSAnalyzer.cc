// $Id: $
// Include files 



// local
#include "PGSAnalyzer.h"
#include "boost/bind.hpp"


//-----------------------------------------------------------------------------
// Implementation file for class : PGSAnalyzer
//
// 2012-08-08 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
PGSAnalyzer::PGSAnalyzer( const char * infile ) {

  m_debug = false;

  m_parser = new LHCOParser(infile);

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
  
  v_pgsObjects  = new TList();
  
  m_include_MET = true;

  m_histos = new Histograms();
    
}
//=============================================================================
// Destructor
//=============================================================================
PGSAnalyzer::~PGSAnalyzer() {

  delete m_parser;
  
} 

//=============================================================================
void PGSAnalyzer::Loop() 
{

  int nobjs = 0;
  
  std::vector<pgsObject*>::iterator itrData;
  
  m_histos->BookBasicHistograms();
  
  int event = 1;

  std::vector<int> v_types;
  std::vector<int> v_bjetPos;
  
  while ( nobjs >= 0 ) {
    
    int nJets  = 0;
    int nMuons = 0;
    int nbJets = 0;
    
    nobjs = m_parser->Next();
    
    itrData = m_parser->m_event->data.begin();

    v_types.clear();
    v_bjetPos.clear();

    int pos = 0;
            
    while (itrData != m_parser->m_event->data.end() ) {
      
      int   type = (*itrData)->type;
      float eta  = (*itrData)->eta;
      float phi  = (*itrData)->phi;
      float pt   = (*itrData)->pt;
      float btag = (*itrData)->btag;
      float mass = (*itrData)->jmas;
      
      //Calculate 4-momentum of the object
      TLorentzVector * v1 = new TLorentzVector();
      
      Set_4momentum( eta, phi, pt, mass, v1 );
      
      v1->Print();
            
      delete v1;
      
      //
      v_types.push_back( type );
      
      
      if ( type == m_pgsCodes["jet"] ) {
        
        m_histos->h_1DHistContainer["jetsPt"]->Fill( pt );
        ++nJets;
        
      }


      if ( type == m_pgsCodes["muon"] ) {
        m_histos->h_1DHistContainer["muonPt"]->Fill( pt );
        ++nMuons;
        
      }
      
      if ( type == m_pgsCodes["jet"] && btag != 0 ) {

        v_bjetPos.push_back( pos );
        m_histos->h_1DHistContainer["jetsBtag"]->Fill( btag );
        ++nbJets;
     
      }
      
      if ( type == m_pgsCodes["met"] ) {
        
        m_histos->h_1DHistContainer["metPt"]->Fill( pt );
        
      }
      
      ////Print information in terms of theta, phi, rho
      
      std::cout << event << '\t' << type << '\t' << phi << '\t' << pt << '\n';

      ++pos;
            
      ++itrData;
      
    }
    
    m_histos->h_1DHistContainer["jetsN"]->Fill( nJets );
    m_histos->h_1DHistContainer["bjetsN"]->Fill( nbJets );
    m_histos->h_1DHistContainer["muonsN"]->Fill( nMuons );
    
    ++event;

    std::cout << "type in order> " << event << " ";
    std::vector<int>::iterator typeItr;
    for( typeItr = v_types.begin(); typeItr != v_types.end(); ++typeItr) {
      std::cout << (*typeItr) << " ";
    }
    std::cout << '\n';

    std::cout << "bjet in order> " << event << " ";
    for( typeItr = v_bjetPos.begin(); typeItr != v_bjetPos.end(); ++typeItr) {
      std::cout << (*typeItr) << " ";
    }
    std::cout << '\n';
        
  }
  
  TCanvas * c1 = new TCanvas();
  
  TCanvas * c2 = new TCanvas();
  c1->SetFillColor(10);
  c1->Divide(2,2);
  c2->SetFillColor(10);
  c2->Divide(2,2);
  
  c1->cd(1);
  m_histos->h_1DHistContainer["jetsN"]->Draw();
  
  c1->cd(2);
  m_histos->h_1DHistContainer["bjetsN"]->Draw();
  
  c1->cd(3);
  m_histos->h_1DHistContainer["muonsN"]->Draw();
  
  c1->Print("results/basic_stats.eps");


  TStyle * sty = new TStyle();
  sty->SetOptStat(11111);
  sty->cd();
    
  c2->cd(1);
  m_histos->h_1DHistContainer["jetsPt"]->Draw();
  
  c2->cd(2);
  m_histos->h_1DHistContainer["jetsBtag"]->Draw();
  
  c2->cd(3);
  m_histos->h_1DHistContainer["metPt"]->Draw();

  c2->cd(4);
  m_histos->h_1DHistContainer["muonPt"]->Draw();
  
  c2->Print("results/basic_kinematics.eps");

  delete sty;

}

void PGSAnalyzer::Set_4momentum( double eta, 
                                 double phi, 
                                 double pt, 
                                 double mass, 
                                 TLorentzVector * vec ) {
  
  double px = pt * TMath::Cos( phi );
  double py = pt * TMath::Sin( phi );
  double pz = pt * TMath::SinH( eta );
  double e  = sqrt( (px*px) + (py*py) + (pz*pz) + (mass*mass) );
    
  vec->SetPxPyPzE( px, py, pz, e );
  
}

void PGSAnalyzer::SetPermutations( const char * infile ) 
{
  
  std::ifstream * in = new std::ifstream();

  in->open(infile);
  
  if (! in->good() ) std::cout << "PGSAnalyzer> could not open input file" << std::endl;
  
  int data[18];
  
  Permutation * permPtr;
  
  while(1) {
  
    if ( (*in).peek() == istream::traits_type::eof() ) break;
    
    permPtr = new Permutation();
    
    (*in) >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5]
          >> data[6] >> data[7]
          >> data[8] >> data[9]
          >> data[10] >> data[11]
          >> data[12] >> data[13]
          >> data[14] >> data[15]
          >> data[16] >> data[17];
      
    for(int i=0; i < 6; ++i)       
      permPtr->perm_id.push_back( data[i] );
    
    for(int i=6; i < 17; i=i+2)
      permPtr->assigment_map[ data[i] ] = data[i+1];
    
    v_perm.push_back( permPtr );
    
    if ( (*in).eof() ) break;
    
  }

  v_perm.pop_back();
  
  std::cout << "PGSAnalyzer> Total number of permutations: " << v_perm.size() << std::endl;
  
  std::vector<Permutation*>::iterator permItr;
  
  for( permItr = v_perm.begin(); permItr != v_perm.end(); ++permItr ) {
    
    for( int i=0; i < 6; ++i ) {
      if( m_debug) std::cout << (*permItr)->perm_id[i] << '\t';
    }
    if( m_debug) std::cout << '\n';
    
    for( int i=3; i < 9; ++i ) {
      if( m_debug) std::cout << " -> " << i << '\t' << (*permItr)->assigment_map[i] << '\n';
    }
        
  }
  
  in->close();

  std::cout << "PGSAnalyzer> SetPermutations: ready" << std::endl;
  
  delete in;
  
}

void PGSAnalyzer::SetWeights( const char * infile ) {

  m_weights = new WeightsAnalyzer( infile );
  
}

void PGSAnalyzer::AnalyzePermutations() 
{
  
  std::vector<pgsObject*>::iterator itrData;

  m_histos->BookPermutationHistograms();

  std::stringstream h_Top1;
  std::stringstream h_Top2;
  std::stringstream h_2dTop;
  
  int event = 0;
  int nobjs = 0;
  
  
  while ( nobjs >= 0 ) {
    
    nobjs = m_parser->Next();
    
    if( m_debug ) std::cout << "PGSAnalyzer> loaded next LHCO event" << std::endl;
    
    int output = m_weights->Next();
    
    if ( output == -2 )  { 
      if( m_debug ) std::cout << "PGSAnalyzer> skipping event" << std::endl;
      m_parser->Reset();
      m_weights->Reset();
      ++event;
      m_parser->Next();
      continue; 
    }
    
    std::cout << "PGSAnalyzer> pgs Event = "<< m_parser->m_event->nEvent << std::endl;
    std::cout << "PGSAnalyzer> weight Event = "<< m_weights->m_eventweight->m_event << std::endl;
        
    if( m_debug ) std::cout << "PGSAnalyzer> AnalyzePermutations> event and weights loaded @ " << event << std::endl;
        
    itrData = m_parser->m_event->data.begin();
    
    int pos = 0;
            
    while (itrData != m_parser->m_event->data.end() ) {
      
      //int   type = (*itrData)->type;
      //float btag = (*itrData)->btag;
      
      float eta  = (*itrData)->eta;
      float phi  = (*itrData)->phi;
      float pt   = (*itrData)->pt;
      float mass = (*itrData)->jmas;
      
      //Calculate 4-momentum of the object
      TLorentzVector * v1 = new TLorentzVector();
      
      Set_4momentum( eta, phi, pt, mass, v1 );
      
      if ( m_debug ) v1->Print();
      
      v_pgsObjects->Add( v1 );
      
      ++itrData;
      
    }
    
    if( m_debug ) std::cout << "PGSAnalyzer> pgsObjects ready @ " << event << std::endl;
    if( m_debug ) std::cout << "PGSAnalyzer> Total PGS objects: " << v_pgsObjects->GetSize() << std::endl;
    
    //Process here all possible permutations and weights
    std::vector<Permutation*>::iterator permItr;
    
    int perm_pos = 1;

    std::stringstream perm_id_str;
    
    
    for( permItr = v_perm.begin(); permItr != v_perm.end(); ++permItr ) {

      h_Top1  << "invMassOne_" << (perm_pos);
      h_Top2  << "invMassTwo_" << (perm_pos);
      h_2dTop << "invMasses_"  << (perm_pos);

      perm_id_str << " permutation " << perm_pos << ": ";
      
      for( int i=0; i < 6; ++i ) {
        perm_id_str << (*permItr)->perm_id[i] << " ";
        if( m_debug ) std::cout << "PGSAnalyzer> " << perm_pos << " " << (*permItr)->perm_id[i] << '\t';
      }
      
      if( m_debug ) std::cout << '\n';
      
      m_histos->h_1DHistContainer[h_Top1.str()]->SetTitle( perm_id_str.str().c_str() );
      m_histos->h_1DHistContainer[h_Top2.str()]->SetTitle( perm_id_str.str().c_str() );
      m_histos->h_2DHistContainer[h_2dTop.str()]->SetTitle( perm_id_str.str().c_str() );
      
      ///First: assign the permutation to the order in whichi the data appears
      
      m_pgsOrder[1]     = (*permItr)->perm_id[0];
      m_pgsOrder[2]     = (*permItr)->perm_id[1];
      m_pgsOrder[3]     = (*permItr)->perm_id[2];
      m_pgsOrder[4]     = (*permItr)->perm_id[3];
      m_pgsOrder[5]     = (*permItr)->perm_id[4];
      m_pgsOrder[6]     = (*permItr)->perm_id[5];
      
      //search for assingment of 3+5+6 = top 1
      int p3 = m_jetsMG["ujet"];
      int p4 = m_jetsMG["~djet"];
      int p5 = m_bjetsMG["bjet"];
      
      int p3lhco = (*permItr)->assigment_map[ p3 ];
      int p4lhco = (*permItr)->assigment_map[ p4 ];
      int p5lhco = (*permItr)->assigment_map[ p5 ];

      if( m_debug ) std::cout << p3 << "->" << p3lhco << '\t'
                              << p4 << "->" << p4lhco << '\t'
                              << p5 << "->" << p5lhco << '\n';
      
      TLorentzVector top1;
      
      pos = m_pgsOrder[p3lhco];
      if( m_debug ) std::cout << p3lhco << "->" << (pos) << '\n';
      top1 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      pos = m_pgsOrder[p4lhco];
      if( m_debug ) std::cout << p4lhco << "->" << (pos)  << '\n';
      top1 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      pos = m_pgsOrder[p5lhco];
      if( m_debug ) std::cout << p5lhco << "->" << (pos)  << '\n';
      top1 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      
      //search for assignment of 4+7+8 = top 2
      
      int p6 = m_muonsMG["muon"];
      int p7 = m_bjetsMG["~bjet"];
      int p8 = m_metMG["met"];
      
      int p6lhco = (*permItr)->assigment_map[ p6 ];
      int p7lhco = (*permItr)->assigment_map[ p7 ];
      int p8lhco = (*permItr)->assigment_map[ p8 ];
      
      if( m_debug )  std::cout << p6 << "->" << p6lhco << '\t'
                               << p7 << "->" << p7lhco << '\t'
                               << p8 << "->" << p8lhco << '\n';
      
      TLorentzVector top2;
      
      pos = m_pgsOrder[p6lhco];
      if( m_debug )  std::cout << p6lhco << "->" << (pos) << '\n';
      top2 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      pos = m_pgsOrder[p7lhco];
      if( m_debug ) std::cout << p7lhco << "->" << (pos) << '\n';
      top2 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      
      if( m_include_MET ) { 
        pos = m_pgsOrder[p8lhco];
        if( m_debug )  std::cout << (pos) << '\n';
        top2 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));

      }
      
      if( m_debug )  std::cout << "Top masses: " << top1.M() << " " << top2.M() << '\n';
      
      m_histos->h_1DHistContainer[h_Top1.str()]->Fill( top1.M() );
      m_histos->h_1DHistContainer[h_Top2.str()]->Fill( top2.M() );
      m_histos->h_2DHistContainer[h_2dTop.str()]->Fill( top1.M(), top2.M() );
      
      //Fill in the histogram of mass, vs permutation, vs weight

      std::map<int,double>::iterator wgtsItr;
      
      wgtsItr = m_weights->m_eventweight->m_perm_weight.find( perm_pos );
      
      if ( wgtsItr != m_weights->m_eventweight->m_perm_weight.end() ) {
        
        //std::cout << "found weight> " << wgtsItr->second << std::endl;
        double weight =  wgtsItr->second;
        m_histos->h_2DHistContainer["top1Weights"]->Fill( top1.M(), perm_pos, weight );
        m_histos->h_2DHistContainer["top2Weights"]->Fill( top2.M(), perm_pos, weight );
                
      }
      
      ++perm_pos;
      
      h_Top1.str("");
      h_Top2.str("");
      h_2dTop.str("");
      
      top1.SetPxPyPzE(0.0,0.0,0.0,0.0);
      top2.SetPxPyPzE(0.0,0.0,0.0,0.0);

      perm_id_str.str("");
      
    }

    /// Find the best and worst ranked Permutation
    ///

    if( m_debug ) std::cout << "PGSAnalyzer> find best&worst permutation" <<  std::endl;
    
    std::vector<double> v_weights_sorted;
    std::map<int,double>::iterator wgtsItr;
    
    for( wgtsItr = m_weights->m_eventweight->m_perm_weight.begin(); 
         wgtsItr != m_weights->m_eventweight->m_perm_weight.end(); ++wgtsItr ) {
      if(m_debug) std::cout << "PGSAnalyzer> " << (*wgtsItr).first << " w: " << (*wgtsItr).second << std::endl;
      v_weights_sorted.push_back ( (*wgtsItr).second ) ;
    }
    
    std::sort ( v_weights_sorted.begin(), v_weights_sorted.end() ); //sorted weights

    double highest_weight = (*v_weights_sorted.rbegin());
    double lowest_weight = (*v_weights_sorted.begin());
    
    // Find the corresponding weight 
    
    wgtsItr = std::find_if( m_weights->m_eventweight->m_perm_weight.begin(), 
                            m_weights->m_eventweight->m_perm_weight.end(),
                            boost::bind( & std::map<int,double>::value_type::second, _1 ) 
                            == (*v_weights_sorted.begin()) );
    
    if( wgtsItr == m_weights->m_eventweight->m_perm_weight.end() ) 
      std::cout << " we got a problem" << std::endl;
    
    int low_high_weight_perm_pos[2];
    
    low_high_weight_perm_pos[0] = (*wgtsItr).first;
    
    wgtsItr = std::find_if( m_weights->m_eventweight->m_perm_weight.begin(), 
                            m_weights->m_eventweight->m_perm_weight.end(),
                            boost::bind( & std::map<int,double>::value_type::second, _1 ) 
                            == (*v_weights_sorted.rbegin()) );
    
    if( wgtsItr == m_weights->m_eventweight->m_perm_weight.end() ) 
      std::cout << " we got a problem" << std::endl;
    
    low_high_weight_perm_pos[1] = (*wgtsItr).first;
    
    if( m_debug ) std::cout << low_high_weight_perm_pos[0]  << " " << lowest_weight << " " 
                            << low_high_weight_perm_pos[1]  << " " << highest_weight << '\n';
    
    // low_high_weight_perm_pos[1]  is the index of the best permutation
    
    perm_pos = low_high_weight_perm_pos[1];
    
    perm_id_str.str("");

    for( int i=0; i < 6; ++i ) {
      perm_id_str << v_perm[perm_pos-1]->perm_id[i] << " ";
    }
    
    std::cout << "PGSAnalyzer> best permutation: [" << perm_pos << "] " << perm_id_str.str() << '\n';
    m_histos->h_1DHistContainer["bestPerm"]->Fill( perm_pos );
    
    perm_id_str.str("");
    
    //// now make a plot of invariant mass of the best permutation and the worst permutation
    
    h_Top1.str("");
    h_Top2.str("");
    
    for( int k= 0; k < 2; ++k ) {
      
      perm_pos = low_high_weight_perm_pos[k];
      
      m_pgsOrder[1]     = v_perm[perm_pos-1]->perm_id[0];
      m_pgsOrder[2]     = v_perm[perm_pos-1]->perm_id[1];
      m_pgsOrder[3]     = v_perm[perm_pos-1]->perm_id[2];
      m_pgsOrder[4]     = v_perm[perm_pos-1]->perm_id[3];
      m_pgsOrder[5]     = v_perm[perm_pos-1]->perm_id[4];
      m_pgsOrder[6]     = v_perm[perm_pos-1]->perm_id[5];
      
      //search for assingment of 3+5+6 = top 1
      int p3 = m_jetsMG["ujet"];
      int p4 = m_jetsMG["~djet"];
      int p5 = m_bjetsMG["bjet"];
      
      int p3lhco = v_perm[perm_pos-1]->assigment_map[ p3 ];
      int p4lhco = v_perm[perm_pos-1]->assigment_map[ p4 ];
      int p5lhco = v_perm[perm_pos-1]->assigment_map[ p5 ];
            
      TLorentzVector top1;
      
      pos = m_pgsOrder[p3lhco];
      top1 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      pos = m_pgsOrder[p4lhco];
      top1 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      pos = m_pgsOrder[p5lhco];
      top1 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      
      //search for assignment of 4+7+8 = top 2
      
      int p6 = m_muonsMG["muon"];
      int p7 = m_bjetsMG["~bjet"];
      int p8 = m_metMG["met"];
      
      int p6lhco = v_perm[perm_pos-1]->assigment_map[ p6 ];
      int p7lhco = v_perm[perm_pos-1]->assigment_map[ p7 ];
      int p8lhco = v_perm[perm_pos-1]->assigment_map[ p8 ];
      
      TLorentzVector top2;
      
      pos = m_pgsOrder[p6lhco];
      top2 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      pos = m_pgsOrder[p7lhco];
      top2 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      
      if( m_include_MET ) { 
        pos = m_pgsOrder[p8lhco];
        top2 += (*(TLorentzVector*)v_pgsObjects->At(pos-1));
      }

      h_Top1  << "top1InvBestPermutation_" << k;
      h_Top2  << "top2InvBestPermutation_" << k;

      m_histos->h_1DHistContainer[h_Top1.str()]->Fill( top1.M() );
      m_histos->h_1DHistContainer[h_Top2.str()]->Fill( top2.M() );
      
      h_Top1.str("");
      h_Top2.str("");
      
    }
    
    v_weights_sorted.clear();

    v_pgsObjects->Delete();

    m_parser->Reset();
    m_weights->Reset();
    
    ++event;

    if ( event > m_max_events ) break;
    
    //break;

    if( m_debug )  std::cout << "PGSAnalyzer> Next event : " << event << '\n';
    
  }
  
  std::cout << "Total events: " << event << std::endl;

  TCanvas * c1 = new TCanvas();
  c1->SetFillColor(10);
  c1->Divide(6,4);

  TCanvas * c2 = new TCanvas();
  c2->SetFillColor(10);
  c2->Divide(6,4);

  h_Top1.str("");
  h_Top2.str("");
  h_2dTop.str("");
  
  for( int i=0; i < 24; ++i) {

    h_Top1  << "invMassOne_" << (i+1);
    h_Top2  << "invMassTwo_" << (i+1);
    h_2dTop << "invMasses_"  << (i+1);

    c1->cd(i+1);
    m_histos->h_1DHistContainer[h_Top1.str()]->Draw();
    m_histos->h_1DHistContainer[h_Top2.str()]->Draw("same");
    
    c2->cd(i+1);
    m_histos->h_2DHistContainer[h_2dTop.str()]->Draw("COLZ");

    h_Top1.str("");
    h_Top2.str("");
    h_2dTop.str("");
    
  }
  
  c1->Print("results/top-masses-perms.eps");
  c2->Print("results/top-masses-2d-perms.eps");
  
  TStyle * sty = new TStyle();
  sty->SetOptStat(0);
  sty->cd();
  sty->SetPalette(54);
  

  TCanvas * c3 = new TCanvas("c3","canvas_3",205,23,511,744);
  c3->SetFillColor(10);
  c3->Divide(1,2);
  
  c3->cd(1);
  gPad->Range(-44.5,-3.0,408.2,26.9);
  gPad->SetRightMargin(0.128668);

  m_histos->h_2DHistContainer["top1Weights"]->Draw("COLZ");
  
  c3->cd(2);
  gPad->SetRightMargin(0.128668);
  m_histos->h_2DHistContainer["top2Weights"]->Draw("COLZ");
  
  c3->Print("results/top12-masses-perms_weights.eps");
  
  TCanvas * c4 = new TCanvas("c4","canvas_4",205,23,511,744);
  c4->SetFillColor(10);
  c4->Divide(1,2);
  
  c4->cd(1);
  gPad->Range(-44.5,-3.0,408.2,26.9);
  gPad->SetRightMargin(0.128668);
  
  m_histos->h_1DHistContainer["top1InvBestPermutation_1"]->Draw();
  m_histos->h_1DHistContainer["top1InvBestPermutation_0"]->Draw("SAME");
  
  m_histos->h_legends["top1InvBestPermutation"]->Draw();

  c4->cd(2);
  gPad->SetRightMargin(0.128668);
  
  m_histos->h_1DHistContainer["top2InvBestPermutation_1"]->Draw();
  m_histos->h_1DHistContainer["top2InvBestPermutation_0"]->Draw("SAME");
  
  m_histos->h_legends["top2InvBestPermutation"]->Draw();
  
  c4->Print("results/top12-masses-best-permutations.eps");
  
  TCanvas * c5 = new TCanvas();
  c5->cd();
  
  m_histos->h_1DHistContainer["bestPerm"]->Draw();
  c5->Print("results/best-permutation-histo.eps");
    

  delete sty;
  
}

