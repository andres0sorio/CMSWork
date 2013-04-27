#include "L12015Analysis.h"

void makeRatePlots( TString XXbinning, float isoCut1, float PUCut );



void makePlots() {

  if( 1 ) {
    makeRatePlots( TString("15,0,75"), 0.2, 980004.0 );
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

  if ( 1 ) {
    
    PUopt = TString("withPUC");
    
    //input_data = TString("../L1Tree_ZeroBias_HF4_Test.root");
    //input_data = TString("../L1Tree_ZeroBias_HF4_Taus_Test.root"); // cut at 50
    //input_data = TString("../L1Tree_ZeroBias_HF4_Taus_Test_Cut2.root"); // no cut
    //input_data = TString("../L1Tree_ZeroBias_HF4_Taus_Test_Cut3.root"); // cut at 5
    //input_data = TString("../L1Tree_ZeroBias_HF4_Taus_Test_Cut4.root"); // cut at 20

  }
  
  char filenamePNG[100];
  char filenameEPS[100];
  
  TList * v_singleCMP = new TList();
  TList * v_singleCMPIso = new TList();
  
  RateHisto * ratehisto;
  
  // EG
  
  L12015Analysis * l1 = new L12015Analysis( input_data.Data() );
  
  l1->Loop();
  
  l1->RunL1RateTau("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"l1");
  l1->RunUCTRateTau("MaxIf$( pt , pt >0 )","", XXbinning.Data(),"tauSt2");
  
  l1->m_l1treeTau->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->m_l1treeTau->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: Tau20","L1 PT (GeV)","Current");
  v_singleCMP->Add( ratehisto );
  
  l1->m_upgradetreeTau->SetHistogramOptions( "tauSt2" , kBlack, 24, kBlue);
  ratehisto = new RateHisto( l1->m_upgradetreeTau->Get( "tauSt2" ) );
  ratehisto->SetText("Trigger Rate: Tau20","L1 PT (GeV)","Non Iso Stage 2");
  v_singleCMP->Add( ratehisto );
  
  sprintf(filenamePNG, "./slhc-plots/rate/Taus/%s/isoStudies/png/rlx_tau_Iso_CMP_V3_%0.2f_%0.2f.png" , PUopt.Data(), isoCut1, PUCut );
  sprintf(filenameEPS, "./slhc-plots/rate/Taus/%s/isoStudies/eps/rlx_tau_Iso_CMP_V3_%0.2f_%0.2f.eps" , PUopt.Data(), isoCut1, PUCut );
  
  l1->m_upgradetreeTau->ComparePlots( v_singleCMP, "", filenamePNG );
  l1->m_upgradetreeTau->ComparePlots( v_singleCMP, "", filenameEPS );
  
  std::cout << std::string( filenamePNG ) << std::endl;
  std::cout << std::string( filenameEPS ) << std::endl;
  
  //------------------------------------------------------------------------------------------

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
  
  sprintf(filenamePNG, "./slhc-plots/rate/Taus/%s/isoStudies/png/iso_tau_Iso_CMP_V3_%0.2f_%0.2f.png" , PUopt.Data(), isoCut1, PUCut );
  sprintf(filenameEPS, "./slhc-plots/rate/Taus/%s/isoStudies/eps/iso_tau_Iso_CMP_V3_%0.2f_%0.2f.eps" , PUopt.Data(), isoCut1, PUCut );

  l1->m_upgradetreeIsoTau->ComparePlots( v_singleCMPIso, "", filenamePNG );
  l1->m_upgradetreeIsoTau->ComparePlots( v_singleCMPIso, "", filenameEPS );

  std::cout << std::string( filenamePNG ) << std::endl;
  std::cout << std::string( filenameEPS ) << std::endl;

  //------------------------------------------------------------------------------------------
  
}

