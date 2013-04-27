void makePlots() {
  
  //Pt
  if( 1 ) {
    makePlots("recoPt", "recoPt > 0.0", "20,0,70", 0.0, 100);
  }
    
  //Eta
  if ( 1 ) { 
    makePlots("recoEta", "recoPt > 0.0 && abs(recoEta) < 3.0", "20,-3.0, 3.0", 0.0, 100);
  }
  
  //Same now but with different PU levels
  //PU selection
  
  if( 1 ) {
    
    //makePlots("recoPt", "recoPt > 0.0", "20,0,70", 0.0, 10.0);
    //makePlots("recoPt", "recoPt > 0.0", "20,0,70", 10.0, 25.0);
    makePlots("recoPt", "recoPt > 0.0", "20,0,70", 25.0, 50.0);
    
    //makePlots("recoEta", "abs(recoEta) < 3.0", "20,-3.0, 3.0", 0.0, 10.0);
    //makePlots("recoEta", "abs(recoEta) < 3.0", "20,-3.0, 3.0", 10.0, 25.0);

    makePlots("recoEta", "recoPt > 0.0 && abs(recoEta) < 3.0", "20,-3.0, 3.0", 25.0, 50.0);
    
  }

}

void makePlots( const char * varname, const char * varSel, const char * binning, float minPU, float maxPU ) {

  gROOT->SetBatch(false);

  std::stringstream path;
  
  TString input_data;

  float PUcut = 0.3;

  if ( 1 ) { 
    
    input_data = TString("../uct_eff_trees_dielec_BC.root");
    path << "./uct15-plots/efficiency/EG/withPUC/isoStudies";
    
  } else {
    
    input_data = TString("../uct_eff_trees_dielec_HEAD_NoPUC_BC.root");
    path << "./uct15-plots/efficiency/EG/noPUC/isoStudies";
    
  }
  
  ////////////////////////////////////////////////////////////////////////////////
  // read the same selection used for the Rate plots
  //
  
  //std::ifstream *m_in = new std::ifstream("efficiency_EG_WP_J1orJ2_Selection.dat");

  std::ifstream *m_in = new std::ifstream("config/efficiency_EG_WP2_J1orJ2_Selection.dat");
  
  if ( !m_in->is_open() ) {
    std::cout << " I could not open this file" << std::endl;
    exit(1);
  }
  
  TList * v_Selection = new TList();
  
  char line[256];
  while(1) {
    
    m_in->getline( line, 256 );
    TObjString *selection = new TObjString( line );
    v_Selection->Add( selection );
    if ( m_in->eof() ) break;
    
  }
  
  v_Selection->RemoveLast();

  ////////////////////////////////////////////////////////////////////////////////
  
  //####################################
  //####### GET PLOTS #########
  //####################################
  
  // --- Use the CMS TDR style
  gROOT->ProcessLine(".L tdrStyle.C");
  setTDRStyle();
  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetPadRightMargin(0.08);
  tdrStyle->SetLegendBorderSize(0);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetOptStat(0);
  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->cd();
  
  std::stringstream dSel;
  std::stringstream l1Sel;
  std::stringstream l1gSel;
  std::stringstream saveAs;
  std::stringstream L1GSelection;
  
  float l1PtCut   = 20.0;
  
  EffGraph *effgraph;
  
  TList * v_efficiencies = new TList();
  TList * v_effcompareIso = new TList();

  //...
  
  TString XaxisLabel;
  if ( TString(varname) == TString("recoPt") )
    XaxisLabel = TString("RECO p_{T} (GeV)");
  else if ( TString(varname) == TString("recoEta") )
    XaxisLabel = TString("RECO #eta");
  else
    XaxisLabel = TString("Fix me");
  
  L1UCTEfficiency * eg1   = new L1UCTEfficiency(input_data.Data(),"rlxEGEfficiency/Ntuple");
    
  // EG - ok
  
  dSel << "(" << varSel << ") && dr03CombinedEt < 0.2";
  l1Sel << "(" << varSel << ") && dr03CombinedEt < 0.2 && l1Match  && l1Pt >= " << l1PtCut;
  l1gSel << "(" << varSel << ") && dr03CombinedEt < 0.2  && l1gMatch && l1gPt >= " << l1PtCut;
  
  dSel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";
  l1Sel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";
  l1gSel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";

  ///Here the fun starts
  
  int max = v_Selection->GetEntries();
  
  for( int k = 0; k < max; ++k ) {
    
    L1GSelection  << l1gSel.str() << " && " << ((TObjString*)v_Selection->At(k))->GetString().Data();
    
    std::cout << " * " << L1GSelection.str() << std::endl;
        
    eg1->SetSelection(dSel,l1Sel,L1GSelection);
    eg1->Loop(varname, binning, "EG Efficiency","eg1");
    
    effgraph = new EffGraph(eg1->GetEff("l1Eff"));
    effgraph->SetText("Trigger Efficiency: EG20", XaxisLabel.Data(),"Current");
    v_efficiencies->Add( effgraph );

    //v_effcompareIso->Add( effgraph );
    
    effgraph = new EffGraph(eg1->GetEff("l1gEff"));
    effgraph->SetText("Trigger Efficiency: EG20",XaxisLabel.Data(),"2x1 E+H Cluster & regional Id & JetRelIso 1or2");
    v_efficiencies->Add( effgraph );
    
    //Compare current vs Selection
    saveAs << path.str() << "/png/rlx_eg_eff_trg20_WP2J1J2_" << varname  << "_" << minPU << "_" << maxPU << "_" << k << "_" << PUcut << ".png";
    eg1->ComparePlots(v_efficiencies,"EG Efficiency", saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path.str() << "/eps/rlx_eg_eff_trg20_WP2J1J2_" << varname  << "_" << minPU << "_" << maxPU << "_" << k << "_" << PUcut << ".eps";
    eg1->ComparePlots(v_efficiencies,"EG Efficiency", saveAs.str().c_str() );
    
    std::cout << saveAs.str() << std::endl;

    saveAs.str("");
    L1GSelection.str("");

    v_efficiencies->Clear();
    //v_efficiencies.Delete();
    
  }
  
  
  /*
    //
    //Compare all in a single plot (?)
    //
    v_effcompareIso->Add( effgraph );
    ((EffGraph*)v_effcompareIso->At(1))->m_eff->SetMarkerStyle(20);
    ((EffGraph*)v_effcompareIso->At(1))->m_eff->SetMarkerColor(6);
    ((EffGraph*)v_effcompareIso->At(2))->m_eff->SetMarkerStyle(23);
    ((EffGraph*)v_effcompareIso->At(2))->m_eff->SetMarkerStyle(8);
    ((EffGraph*)v_effcompareIso->At(3))->m_eff->SetMarkerStyle(23);
    ((EffGraph*)v_effcompareIso->At(3))->m_eff->SetMarkerColor(9);
    runAnalysis_EG_WP_Selection.log
    //Do a final comparison of all the three types of isolation
    
    std::cout << " Plots to combine " << v_effcompareIso->GetSize() << std::endl;
    
    saveAs.str("");
    saveAs << "./png/rlx_eg_eff_trg20_with_jet_iso_All_" << varname << "_" << minPU << "_" << maxPU << ".png";
    eg4->ComparePlots(v_effcompareIso,"EG Efficiency", saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << "./eps/rlx_eg_eff_trg20_with_jet_iso_All_" << varname << "_" << minPU << "_" << maxPU << ".eps";
    eg4->ComparePlots(v_effcompareIso,"EG Efficiency", saveAs.str().c_str() );
    
  */
  
  m_in->close();
  
  delete m_in;
  
}
