// $Id: Histograms.C,v 1.1 2013/01/10 03:29:13 aosorio Exp $
// Include files 

// local
#include "Histograms.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Histograms
//
// All histograms can go here
//
// 2012-11-14 : Andres Osorio
//-----------------------------------------------------------------------------

//#include "tdrStyle.C"

//=============================================================================
// Standard constructor, initializes variables

//=============================================================================

Histograms::Histograms() 
{
 
  //Better Use the TDR style
  
}

//=============================================================================
// Destructor
//=============================================================================
Histograms::~Histograms() {} 

//=============================================================================
void Histograms::BookHistograms(int mbins, float minx, float maxx ) {

  //... Book histograms
  m_histograms1D["pt"]           =  new TH1F("Pt","Pt plot", mbins, minx, maxx);
  
  m_histograms1D["jetpt"]        =  new TH1F("jetPt","jetPt plot", mbins, (minx - 5), maxx);

  m_histograms1D["regionEt"]     =  new TH1F("regionEt","regionEt plot", 10, 0.0, 10.0);

  m_histograms2D["etaphi"]       =  new TH2F("etaphi","Eta - phi", 22, 0, 22, 17, 0, 17);

  m_histograms2D["etaphiEt"]     =  new TH2F("etaphiEt","Eta - phi Et", 22, 0, 22, 17, 0, 17);
  
  m_histograms2D["etaEt"]        =  new TH2F("etaEt","Eta - Et", 22, 0, 22, 20, 0, 5.0);
  
  m_histogramsPf["etaEt"]        =  new TProfile("hprof"," Et as a fucntion of Eta", 22, 0, 22, 0, 10.0);

  m_histograms2D["jetetaEt"]     =  new TH2F("jet_etaEt","Eta - Et", 22, 0, 22, 50, 0, 100.0);

  // Resolutions
  
  
  ////

}

TH1F * Histograms::MakePlot( const char * var, const char * selection, const char * binning, 
			     const char * xaxis, const char * title, const char *histoname) {
  
  TString draw_string = TString(var)+ TString(">>") + TString(histoname) + TString("(") + TString(binning) + TString(")");
  fChain->Draw(draw_string, selection, "goff");
  std::cout << "Histograms::MakePlot 1: " << std::string(draw_string) << " sel " << std::string(selection) << std::endl;
  TH1F * output_histo = (TH1F*)gDirectory->Get(histoname)->Clone();
  output_histo->GetXaxis()->SetTitle(xaxis);
  output_histo->SetTitle(title);
  return output_histo;
  
}

TH1F * Histograms::MakePlot( const char * treename, const char * var, const char * selection, const char * binning, 
			     const char * xaxis, const char * title, const char *histoname) {
  
  TString draw_string = TString(var)+ TString(">>") + TString(histoname) + TString("(") + TString(binning) + TString(")");
  TTree * tree = (TTree*)gDirectory->Get(treename);
  tree->Draw(draw_string, selection, "goff");
  std::cout << "Histograms::MakePlot 2: " << std::string(draw_string) << " sel " << std::string(selection) << std::endl;
  TH1F * output_histo = (TH1F*)gDirectory->Get(histoname)->Clone();
  output_histo->GetXaxis()->SetTitle(xaxis);
  output_histo->SetTitle(title);
  return output_histo;
  
}

TH1F * Histograms::Make_Th_Integral(TH1F * h_in) {
  
  // This is same as it is done in the Wisconsin scripts
  
  int numBins = h_in->GetNbinsX();
  TH1F * h_out = (TH1F*)h_in->Clone();
  
  for (int i = 0; i < numBins; ++i)
    h_out->SetBinContent(i+1, h_in->Integral(i+1, numBins)); 

  // keep in mind: i = 0  underflow bin; i = numBins is the overflow bin
  
  return h_out;
  
}

void Histograms::MakeL1Efficiency(TH1F * num, TH1F * denom, const char * hname) {
  // Make an efficiency graph with the "L1" style
  TGraphAsymmErrors * eff = new TGraphAsymmErrors( num, denom);
  eff->SetMarkerStyle(20);
  eff->SetMarkerColor(kRed);
  eff->SetMarkerSize(1.5);
  eff->SetLineColor(kBlack);
  m_efficiencies[std::string( hname )] = eff;

}

void Histograms::MakeL1GEfficiency(TH1F * num, TH1F * denom, const char * hname) {
  // Make an efficiency graph with the "L1G" style
  TGraphAsymmErrors * eff = new TGraphAsymmErrors( num, denom);
  eff->SetMarkerStyle(24);
  eff->SetMarkerColor(kBlue);
  eff->SetMarkerSize(1.5);
  eff->SetLineColor(kBlack);
  m_efficiencies[std::string( hname )] = eff;
  
}

void Histograms::SetHistogramOptions( const char *name, int color1, int marker, int color2 ) {
  
  std::map<std::string,TH1F*>::iterator it1;
  std::map<std::string,TH2F*>::iterator it2;
  std::map<std::string,TGraphAsymmErrors*>::iterator it3;
    
  it1 = m_histograms1D.find(name);

  if( it1 != m_histograms1D.end() ) {
    m_histograms1D[std::string(name)]->SetLineColor(color1);
    m_histograms1D[std::string(name)]->SetMarkerStyle(marker);
    m_histograms1D[std::string(name)]->SetMarkerColor(color2);
  } else {

    it2 = m_histograms2D.find(name);
    if( it2 != m_histograms2D.end() ) {
      m_histograms2D[std::string(name)]->SetLineColor(color1);
      m_histograms2D[std::string(name)]->SetMarkerStyle(marker);
      m_histograms2D[std::string(name)]->SetMarkerColor(color2);
    } else {

      it3 = m_efficiencies.find(name);
      if( it3 != m_efficiencies.end() ) {
	m_efficiencies[std::string(name)]->SetLineColor(color1);
	m_efficiencies[std::string(name)]->SetMarkerStyle(marker);
	m_efficiencies[std::string(name)]->SetMarkerColor(color2);
      } else {

	std::cout << "SetHistogramOptions> Histogram not found!" << std::endl;
	
      }
    
    }
    
  }
  
}


////CMS Preliminary label and lumu - Thanks to Kalanand
void Histograms::cmsPrelim()
{

  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"#sqrt{s} = 8 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96,"CMS preliminary 2012");

}
