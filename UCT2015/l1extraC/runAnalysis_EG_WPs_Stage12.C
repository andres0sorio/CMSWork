#include "L12015Analysis.h"

void makeRatePlots( TString XXbinning, float isoCut1, float PUCut );



void makePlots() {

  if( 1 ) {
    makeRatePlots( TString("15,0,75"), 0.2, 20980.0 );
  }
  
}

void makeRatePlots( TString XXbinning, float isoCut1, float PUCut ) {
  
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
  
  TString PUopt;
  TString input_data;
  TString stage1_ntuple;
  TString stage2_ntuple;

  if ( 1 ) {
    
    PUopt = TString("withPUC");
    
    input_data = TString("../L1Tree_ZeroBias_HF4_Test_Stg_12.root");
    
    stage2_ntuple = TString("l1ExtraUpgradeTreeProducer/L1ExtraUpgradeTree");

    stage1_ntuple = TString("l1ExtraUpgradeTreeProducerStageOne/L1ExtraUpgradeTree");

  }
  
  char filenamePNG[100];
  char filenameEPS[100];
  
  TList * v_singleCMP = new TList();
  TList * v_singleCMPIso = new TList();
  
  RateHisto * ratehisto;
  
  // EG
  
  L12015Analysis * l1 = new L12015Analysis( input_data.Data(), stage2_ntuple.Data() );

  L12015Analysis * uct = new L12015Analysis( input_data.Data(), stage1_ntuple.Data() );

  l1->Loop();
  uct->Loop();

  l1->RunL1RateEG("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"l1");
  l1->RunUCTRateEG("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"egSt2");
  
  l1->m_l1treeEG->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->m_l1treeEG->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Current");
  v_singleCMP->Add( ratehisto );
  
  l1->m_upgradetreeEG->SetHistogramOptions( "egSt2" , kBlack, 24, kBlue);
  ratehisto = new RateHisto( l1->m_upgradetreeEG->Get( "egSt2" ) );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Non Iso Stage 2");
  v_singleCMP->Add( ratehisto );
  
  
  uct->RunUCTRateEG("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"egSt1");
  
  uct->m_upgradetreeEG->SetHistogramOptions( "egSt1" , kBlack, 25, kBlue);
  ratehisto = new RateHisto( uct->m_upgradetreeEG->Get( "egSt1" ) );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","rlx Stage 1 (2x1 E+H with regional ID)");
  v_singleCMP->Add( ratehisto );

  sprintf(filenamePNG, "./slhc-plots/rate/EG/%s/isoStudies/png/rlx_eg_Iso_CMP_V3_%0.2f_%0.2f.png" , PUopt.Data(), isoCut1, PUCut );
  sprintf(filenameEPS, "./slhc-plots/rate/EG/%s/isoStudies/eps/rlx_eg_Iso_CMP_V3_%0.2f_%0.2f.eps" , PUopt.Data(), isoCut1, PUCut );
  
  l1->m_upgradetreeEG->ComparePlots( v_singleCMP, "", filenamePNG );
  l1->m_upgradetreeEG->ComparePlots( v_singleCMP, "", filenameEPS );
  
  std::cout << std::string( filenamePNG ) << std::endl;
  std::cout << std::string( filenameEPS ) << std::endl;
  
  //------------------------------------------------------------------------------------------

  l1->RunL1RateEGIso("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"l1");
  l1->RunUCTRateEGIso("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"egIsoSt2");
  
  l1->m_l1treeEGIso->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->m_l1treeEGIso->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: EGIso20","L1 PT (GeV)","Current");
  v_singleCMPIso->Add( ratehisto );
  
  l1->m_upgradetreeEGIso->SetHistogramOptions( "egIsoSt2" , kBlack, 24, kBlue);
  ratehisto = new RateHisto( l1->m_upgradetreeEGIso->Get( "egIsoSt2" ) );
  ratehisto->SetText("Trigger Rate: EGIso20","L1 PT (GeV)","Iso Stage 2");
  v_singleCMPIso->Add( ratehisto );
  
  sprintf(filenamePNG, "./slhc-plots/rate/EG/%s/isoStudies/png/iso_eg_Iso_CMP_V3_%0.2f_%0.2f.png" , PUopt.Data(), isoCut1, PUCut );
  sprintf(filenameEPS, "./slhc-plots/rate/EG/%s/isoStudies/eps/iso_eg_Iso_CMP_V3_%0.2f_%0.2f.eps" , PUopt.Data(), isoCut1, PUCut );

  l1->m_upgradetreeEGIso->ComparePlots( v_singleCMPIso, "", filenamePNG );
  l1->m_upgradetreeEGIso->ComparePlots( v_singleCMPIso, "", filenameEPS );

  std::cout << std::string( filenamePNG ) << std::endl;
  std::cout << std::string( filenameEPS ) << std::endl;

  //------------------------------------------------------------------------------------------
  






}

