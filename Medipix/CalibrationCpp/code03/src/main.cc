// $Id: 
// Include files 

#include <RootCommon.h>
#include <Data.h>
#include <SimpleClusterAlgo.h>

//From ROOT
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TStyle.h>

#include <sstream>

///////////////////////////////////////////////////////////////

void CountAndPlot( Data * data, TH1F * h1) 
{

  for(int i=0; i < 256; ++i) 
  {
    for(int j=0; j < 256; ++j) 
    {
      int counts = data->matrix[i][j];
      if ( counts != 0 )
        h1->Fill(counts);
    }
    
  }
  
}

void PlotMatrix( Data * data, TH2F * hh)
{

  for(int i=0; i < 256; ++i)
  {
    for(int j=0; j < 256; ++j)
    {
      int counts = data->matrix[i][j];
      hh->SetBinContent(i+1,j+1, float(counts));
    }
    
  }
  
}

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {


  std::stringstream filename;

  std::vector<Data*> matrices;
    
  TH1F * histo = new TH1F("h1", "Pixeles con conteos", 300, 0, 300);
  TH1F * clushits = new TH1F("clushits", "Clusters con conteos", 1000, 0, 10000);
  TH1F * clussize = new TH1F("clussize", "Clusters size", 100, 0, 100);
  
  for( int k = 0; k < 500; ++k) 
  {
    
    if ( k < 10 )
      filename << "CalibracionTmpx/Cal00" << k << ".txt";
    else if ( k < 100 )
      filename << "CalibracionTmpx/Cal0" << k << ".txt";
    else 
      filename << "CalibracionTmpx/Cal" << k << ".txt";

    Data * data01 = new Data( filename.str().c_str() );
    
    data01->Read();

    CountAndPlot( data01, histo );
        
    matrices.push_back(data01);
    
    filename.str("");
    
  }
  
  std::cout << matrices.size() << std::endl;

  TCanvas * c1 = new TCanvas("c1","Plots",100,50,600,400);
  TCanvas * c2 = new TCanvas("c2","Plots",100,50,600,400);
  TCanvas * c3 = new TCanvas("c3","Plots",100,50,600,400);
    
  c1->SetFillColor(10);
  c1->cd();
  c1->SetLogy();
  histo->Draw();

  c1->Print("results.eps");
  delete histo;
  
  // Analisis
  
  std::stringstream hname;
  std::stringstream clusters;
  
  std::vector<Data*>::const_iterator itrData;
  
  int k=0;
  c2->SetFillColor(10);
  TStyle * sty =  new TStyle();
  sty->SetPalette(1);
  sty->cd();
  
  for( itrData = matrices.begin(); itrData != matrices.end(); ++itrData) 
  {

    SimpleClusterAlgo * algo = new SimpleClusterAlgo( (*itrData) );
    algo->Run();

    c2->cd();
    hname << "mat0" << k;
    hname << "clusters0" << k;
    
    TH2F * h1 = new TH2F(hname.str().c_str(),"Hit Display",257,0,257,257,0,257);
    TH2F * h2 = new TH2F(clusters.str().c_str(),"Clusters Display",257,0,257,257,0,257);

    h1->SetStats(0);
    h2->SetStats(0);
    
    h2->SetMarkerStyle(24);
    h2->SetMarkerSize(1.2);
    
    algo->PlotClusters( h2 );
    algo->PlotClusterCounts( clushits );
    algo->PlotClusterSize( clussize );
    
    PlotMatrix( (*itrData), h1 );
    
    h1->Draw("COLZ");
    h2->Draw("SAME");
    
    c2->Print( ( std::string("matrices/") + hname.str() + std::string(".png") ).c_str() );
    
    delete h1;
    delete algo;
    
    hname.str("");
    clusters.str("");
    
    ++k;
    //if ( k > 2 ) break;
    
  }

  c3->SetFillColor(10);
  c3->cd();
  clushits->Draw();
  c3->Print("results_clusinfo.png");

  delete clushits;

  c3->cd();
  clussize->Draw();
  c3->Print("results_clussize.png");
  
  delete clussize;
    
  //
  
  return 1;
    
}
