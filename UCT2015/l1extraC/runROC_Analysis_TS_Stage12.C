#include "L12015Analysis.h"
#include "L1UCTEfficiency.h"

void makeRatePlots( TString XXbinning );



void makePlots() {

  if( 1 ) {
    makeRatePlots( TString("15,0,75") );
  }
  
}

void makeRatePlots( TString XXbinning ) {
  
  gROOT->SetBatch(false);
  
  //####################################
  //####### GET PLOTS #########
  //####################################
  
  // --- Use the CMS TDR style
  //gROOT->ProcessLine(".L tdrStyle.C");
  //setTDRStyle();
  //tdrStyle->SetErrorX(0.5);
  //tdrStyle->SetPadLeftMargin(0.18);
  //tdrStyle->SetPadRightMargin(0.08);
  //tdrStyle->SetLegendBorderSize(0);
  //tdrStyle->SetTitleYOffset(1.3);
  //tdrStyle->SetOptStat(0);
  //tdrStyle->SetTitleFontSize(0.05);
  //bool debug = false;
  
  TString input_data;
  TString input_rawreco_data;

  TString stage1_ntuple;
  TString stage2_ntuple;

  if ( 1 ) {
    
    input_data = TString("../L1Tree_ZeroBias_HF_Test.root");

    input_rawreco_data = TString("../L1Tree_DiTau_2012B_RAWRECO.root");

    stage2_ntuple = TString("l1ExtraUpgradeTreeProducer/L1ExtraUpgradeTree");
    
    stage1_ntuple = TString("l1ExtraUpgradeTreeProducerStageOne/L1ExtraUpgradeTree");
    
  }
  
  //char filenamePNG[100];
  //char filenameEPS[100];
  
  RateHisto * ratehisto;
  
  //------------------------------------------------------------------------------------------
  // TAUS - Rates
  
  L12015Analysis * l1 = new L12015Analysis( input_data.Data(), stage2_ntuple.Data() );

  L12015Analysis * uct = new L12015Analysis( input_data.Data(), stage1_ntuple.Data() );

  l1->Loop();
  uct->Loop();

  l1->RunL1RateTau("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"l1");
  l1->RunUCTRateTau("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"tauSt2");
  
  // Current
  l1->m_l1treeTau->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->m_l1treeTau->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: Tau20","L1 PT (GeV)","Current");
  
  TH1F * m_rate_current = ratehisto->m_rate;

  // Stage 2
  
  l1->m_upgradetreeTau->SetHistogramOptions( "tauSt2" , kBlack, 24, kBlue);
  ratehisto = new RateHisto( l1->m_upgradetreeTau->Get( "tauSt2" ) );
  ratehisto->SetText("Trigger Rate: Tau20","L1 PT (GeV)","Non Iso Stage 2");
   
  TH1F * m_rate_stage2 = ratehisto->m_rate;

  // Stage 1

  uct->RunUCTRateTau("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"tauSt1");

  uct->m_upgradetreeTau->SetHistogramOptions( "tauSt1" , kBlack, 21, kBlue);
  ratehisto = new RateHisto( uct->m_upgradetreeTau->Get( "tauSt1" ) );
  ratehisto->SetText("Trigger Rate: Tau20","L1 PT (GeV)","Stage 1 (2x1 E+H cluster)");
  
  TH1F * m_rate_stage1 = ratehisto->m_rate;
  
  //------------------------------------------------------------------------------------------
  // Efficiency
  
  EffGraph * effgraph;

  L1UCTEfficiency * tausSt1   = new L1UCTEfficiency(input_rawreco_data.Data(),"rlxTauSt1Efficiency/Ntuple","Tau");

  L1UCTEfficiency * tausSt2   = new L1UCTEfficiency(input_rawreco_data.Data(),"rlxTauSt2Efficiency/Ntuple","Tau");

  Int_t minPU = 0;
  
  Int_t maxPU = 100;
  
  Float_t l1PtCut = 20.0;

  std::stringstream dSel;
  std::stringstream l1Sel;
  std::stringstream l1gSel;
  std::stringstream L1GSelection;
 
  //////////////////////////////////////
  
  // Tau - ok
  dSel << "(" << "recoPt > 0.0" << ") ";
  l1Sel << "(" << "recoPt > 0.0" << ") && l1Match  && l1Pt >= " << l1PtCut;
  l1gSel << "(" << "recoPt > 0.0" << ") && l1gMatch && l1gPt >= " << l1PtCut;
  
  // PU Level selection
  dSel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";
  l1Sel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";
  l1gSel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";
  
  L1GSelection  << l1gSel.str();
  
  std::cout << " * " << L1GSelection.str() << std::endl;
  
  // The Stage 1 efficiency
  
  tausSt1->SetSelection(dSel,l1Sel,L1GSelection);
  tausSt1->Loop("recoPt", "15,0,75", "Tau Efficiency","Stage1");
  
  effgraph = new EffGraph(tausSt1->GetEff("l1gEff"));
  effgraph->SetText("Trigger Efficiency: Tau20","RECO p_{T} (GeV)", "2x1 E+H Cluster");
  
  TGraphAsymmErrors * stage1_eff = effgraph->m_eff;
  
  // The Stage 2 efficiency
  tausSt2->SetSelection(dSel,l1Sel,L1GSelection);
  tausSt2->Loop("recoPt", "15,0,75", "Tau Efficiency","Stage2");
  
  effgraph = new EffGraph(tausSt2->GetEff("l1gEff"));
  effgraph->SetText("Trigger Efficiency: Tau20","RECO p_{T} (GeV)", "2x2 E+H Cluster");
  
  TGraphAsymmErrors * stage2_eff = effgraph->m_eff;


  TCanvas * single_plots = new TCanvas();
 
  single_plots->Divide(2,2);
 
  single_plots->cd(1);
  m_rate_stage1->SetLineColor(2);
  m_rate_stage1->Draw();
  m_rate_current->Draw("same");

  single_plots->cd(2);
  m_rate_stage2->SetLineColor(4);
  m_rate_stage2->Draw();
  m_rate_current->Draw("same");

  single_plots->cd(3);
  stage1_eff->Draw("ape");

  single_plots->cd(4);
  stage2_eff->Draw("ape");
  
  

  //------------------------------------------------------------------------------------------
  
  //Make ROC Curve

  //roc

  TGraph * roc_1 = new TGraph();
  TGraph * roc_2 = new TGraph();

  int maxX = m_rate_stage1->GetNbinsX();
  int np = 0;
  for( int k=1; k <= maxX; ++ k ) {

    Double_t x = 0.0;
    Double_t y1 = 0.0;

    float x1 = m_rate_stage1->GetBinContent(k);
    stage1_eff->GetPoint( k-1, x, y1) ;

    if( y1 > 0.0 ) {
      roc_1->SetPoint( np, x1, y1 );
      np+=1;
    }

  }

  np = 0;

  for( int k=1; k <= maxX; ++ k ) {

    Double_t x = 0.0;
    Double_t y1 = 0.0;

    float x1 = m_rate_stage2->GetBinContent(k);
    stage2_eff->GetPoint( k-1, x, y1) ;

    if( y1 > 0.0 ) {
      roc_2->SetPoint( np, x1, y1 );
      np+=1;
    }

  }

  
  TCanvas * roc_plots = new TCanvas();
  roc_plots->Divide(2,2);
  
  roc_plots->cd(1);
  roc_1->SetMarkerStyle(23);
  roc_1->SetMarkerColor(2);
  roc_1->Draw("ap");

  roc_2->SetMarkerStyle(24);
  roc_2->SetMarkerColor(4);
  roc_2->Draw("psame");












  //------------------------------------------------------------------------------------------
  // Isolation
  
  /*
  l1->RunL1RateIsoTau("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"l1");
  l1->RunUCTRateIsoTau("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"tauIsoSt2");
  
  l1->m_l1treeIsoTau->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->m_l1treeIsoTau->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: IsoTau20","L1 PT (GeV)","Current");
  v_singleCMPIso->Add( ratehisto );
  
  l1->m_upgradetreeIsoTau->SetHistogramOptions( "tauIsoSt2" , kBlack, 24, kBlue);
  ratehisto = new RateHisto( l1->m_upgradetreeIsoTau->Get( "tauIsoSt2" ) );
  ratehisto->SetText("Trigger Rate: IsoTau20","L1 PT (GeV)","Iso Stage 2");
  v_singleCMPIso->Add( ratehisto );

  uct->RunUCTRateIsoTau("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"isotauSt1");

  uct->m_upgradetreeIsoTau->SetHistogramOptions( "isotauSt1" , kBlack, 21, kBlue);
  ratehisto = new RateHisto( uct->m_upgradetreeIsoTau->Get( "isotauSt1" ) );
  ratehisto->SetText("Trigger Rate: Tau20","L1 PT (GeV)","Stage 1 (2x1 E+H cluster && JetIso )");
  v_singleCMPIso->Add( ratehisto );
  */

  //------------------------------------------------------------------------------------------
  
}

