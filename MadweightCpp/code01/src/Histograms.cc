// $Id: $
// Include files 



// local
#include "Histograms.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Histograms
//
// 2012-09-21 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Histograms::Histograms(  ) {

}
//=============================================================================
// Destructor
//=============================================================================
Histograms::~Histograms() {} 

//=============================================================================
void Histograms::BookBasicHistograms( ) 
{
  
  h_1DHistContainer["jetsN"] = new TH1F("jetsN",
                                        "PGS N jets", 15, 0.0, 15.0 );

  h_1DHistContainer["bjetsN"] = new TH1F("bjetsN",
                                        "PGS N bjets", 15, 0.0, 15.0 );

  h_1DHistContainer["muonsN"] = new TH1F("muonsN",
                                        "PGS N muons", 15, 0.0, 15.0 );
  
  h_1DHistContainer["jetsPt"] = new TH1F("jetsPt",
                                         "PGS Pt of Jets", 50, 0.0, 200.0 );

  h_1DHistContainer["muonPt"] = new TH1F("muonPt",
                                         "PGS Pt of muons", 50, 0.0, 200.0 );
  
  h_1DHistContainer["metPt"] = new TH1F("metPt",
                                         "PGS MET Pt infor", 50, 0.0, 200.0 );
  
  h_1DHistContainer["jetsBtag"] = new TH1F("jetsBtag",
                                           "PGS Btag assignment for jets", 10, 0.0, 10.0 );
  
  h_1DHistContainer["jetsPt"]->SetTitle("");
  h_1DHistContainer["jetsPt"]->GetXaxis()->CenterTitle(true);
  h_1DHistContainer["jetsPt"]->GetXaxis()->SetTitle("Jet Pt [GeV/c]");
  h_1DHistContainer["jetsPt"]->SetLineColor(2);
  
  h_1DHistContainer["jetsBtag"]->SetTitle("");
  h_1DHistContainer["jetsBtag"]->GetXaxis()->CenterTitle(true);
  h_1DHistContainer["jetsBtag"]->GetXaxis()->SetTitle("PGS B-tag assignment");
  h_1DHistContainer["jetsBtag"]->SetLineColor(2);
  
  h_1DHistContainer["metPt"]->SetTitle("");
  h_1DHistContainer["metPt"]->GetXaxis()->CenterTitle(true);
  h_1DHistContainer["metPt"]->GetXaxis()->SetTitle("MET Pt [GeV/c]");
  h_1DHistContainer["metPt"]->SetLineColor(2);
  
  h_1DHistContainer["muonPt"]->SetTitle("");
  h_1DHistContainer["muonPt"]->GetXaxis()->CenterTitle(true);
  h_1DHistContainer["muonPt"]->GetXaxis()->SetTitle("#mu Pt [GeV/c]");
  h_1DHistContainer["muonPt"]->SetLineColor(2);
  
}

void Histograms::BookPermutationHistograms() 
{
  
  std::stringstream h_Top1;
  std::stringstream h_Top2;
  std::stringstream h_2dTop;
  
  for( int i=0; i < 24; ++i) {
    
    h_Top1  << "invMassOne_" << (i+1);
    h_Top2  << "invMassTwo_" << (i+1);
    h_2dTop << "invMasses_"  << (i+1);
    
    h_1DHistContainer[h_Top1.str()] = new TH1F(h_Top1.str().c_str(),
                                               "Invariant mass object 1", 100, 0.0, 350.0 );
    
    h_1DHistContainer[h_Top2.str()] = new TH1F(h_Top2.str().c_str(),
                                               "Invariant mass object 2", 100, 0.0, 350.0 );
    
    h_2DHistContainer[h_2dTop.str()] = new TH2F(h_2dTop.str().c_str(),
                                                "Invariant masses of both objects", 
                                                100, 0.0, 350.0,
                                                100, 0.0, 350.0);
    
    h_1DHistContainer[h_Top1.str()]->GetXaxis()->CenterTitle(true);
    h_1DHistContainer[h_Top2.str()]->GetXaxis()->CenterTitle(true);
    h_2DHistContainer[h_2dTop.str()]->GetXaxis()->CenterTitle(true);
    h_2DHistContainer[h_2dTop.str()]->GetYaxis()->CenterTitle(true);
    
    h_1DHistContainer[h_Top1.str()]->GetXaxis()->SetTitle("Inv Mass [GeV/c2]");
    h_1DHistContainer[h_Top2.str()]->GetXaxis()->SetTitle("Inv Mass [GeV/c2]");
    
    h_2DHistContainer[h_2dTop.str()]->GetXaxis()->SetTitle("Inv Mass 1 [GeV/c2]");
    h_2DHistContainer[h_2dTop.str()]->GetYaxis()->SetTitle("Inv Mass 2 [GeV/c2]");
    
    h_Top1.str("");
    h_Top2.str("");
    h_2dTop.str("");
    
  }
    
  h_2DHistContainer["top1Weights"] = new TH2F( "top1Weights",
                                               "Inv. mass of top / permutation / weight",
                                               100, 0.0, 350.0, 25, 0.0, 25);
  
  h_2DHistContainer["top1Weights"]->SetTitle("");
  h_2DHistContainer["top1Weights"]->GetXaxis()->SetTitle("Inv Mass [GeV/c2]");
  h_2DHistContainer["top1Weights"]->GetYaxis()->SetTitle("Permutation");
  
  h_2DHistContainer["top2Weights"] = new TH2F( "top2Weights",
                                               "Inv. mass of top / permutation / weight",
                                               100, 0.0, 350.0, 25, 0.0, 25);
  
  h_2DHistContainer["top2Weights"]->SetTitle("");
  h_2DHistContainer["top2Weights"]->GetXaxis()->SetTitle("Inv Mass [GeV/c2]");
  h_2DHistContainer["top2Weights"]->GetYaxis()->SetTitle("Permutation");
  
  /////
  
  for (int k = 0; k < 2; ++k) {
    
    h_Top1  << "top1InvBestPermutation_" << k;
    h_Top2  << "top2InvBestPermutation_" << k;
    
    h_1DHistContainer[h_Top1.str()] = new TH1F(h_Top1.str().c_str(),
                                               "Invariant mass object 1", 100, 0.0, 350.0 );
    
    h_1DHistContainer[h_Top2.str()] = new TH1F(h_Top2.str().c_str(),
                                               "Invariant mass object 2", 100, 0.0, 350.0 );
    
    
    h_1DHistContainer[h_Top1.str()]->GetXaxis()->SetTitle("Inv Mass [GeV/c2]");
    h_1DHistContainer[h_Top2.str()]->GetXaxis()->SetTitle("Inv Mass [GeV/c2]");
    
    h_Top1.str("");
    h_Top2.str("");
    
  }
  
  for( int i=0; i < 24; ++i) {
    
    h_Top1  << "invMassOne_" << (i+1);
    h_Top2  << "invMassTwo_" << (i+1);
    h_2dTop << "invMasses_"  << (i+1);

    h_1DHistContainer[h_Top1.str()]->SetLineColor(1);
    h_1DHistContainer[h_Top2.str()]->SetLineColor(2);

    h_Top1.str("");
    h_Top2.str("");
    h_2dTop.str("");
        
  }
  
  h_1DHistContainer["top1InvBestPermutation_1"]->SetLineColor(1);
  h_1DHistContainer["top1InvBestPermutation_0"]->SetLineColor(2);
  h_1DHistContainer["top2InvBestPermutation_1"]->SetLineColor(1);
  h_1DHistContainer["top2InvBestPermutation_0"]->SetLineColor(2);


  TLegend * leg1 = new TLegend(0.59,0.75,0.86,0.86);
  leg1->SetBorderSize(1);
  leg1->SetTextFont(62);
  leg1->SetLineColor(1);
  leg1->SetLineStyle(1);
  leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(1001);
  
  leg1->AddEntry( h_1DHistContainer["top1InvBestPermutation_0"], "lowest P - permutation", "l" );
  leg1->AddEntry( h_1DHistContainer["top1InvBestPermutation_1"], "highest P - permutation", "l" );
  
  h_legends["top1InvBestPermutation"] = leg1;
  
  TLegend * leg2 = new TLegend(0.59,0.75,0.86,0.86);
  leg2->SetBorderSize(1);
  leg2->SetTextFont(62);
  leg2->SetLineColor(1);
  leg2->SetLineStyle(1);
  leg2->SetLineWidth(1);
  leg2->SetFillColor(0);
  leg2->SetFillStyle(1001);

  leg2->AddEntry( h_1DHistContainer["top2InvBestPermutation_0"], "lowest P - permutation", "l" );
  leg2->AddEntry( h_1DHistContainer["top2InvBestPermutation_1"], "highest P - permutation", "l" );
  
  h_legends["top2InvBestPermutation"] = leg2;


  h_1DHistContainer["bestPerm"] = new TH1F("bestPerm",
                                           "Best permutation", 25, 0.0, 25);

  h_1DHistContainer["bestPerm"]->SetTitle("");
  h_1DHistContainer["bestPerm"]->GetXaxis()->CenterTitle(true);
  h_1DHistContainer["bestPerm"]->GetXaxis()->SetTitle("Permutation Id");
  h_1DHistContainer["bestPerm"]->SetLineColor(2);

}
