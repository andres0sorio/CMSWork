// $Id: 
// Include files 

#include <RootCommon.h>
#include <Data.h>

//From ROOT
#include <TCanvas.h>
#include <TH1F.h>

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

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {


  std::stringstream filename;

  std::vector<Data*> matrices;
    
  TH1F * histo = new TH1F("h1", "Pixeles con conteos", 300, 0, 300);
  
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
    
    //for(int i=0; i < 10; ++i) 
    //{
    // data01->Show(i);
    //}

    CountAndPlot( data01, histo );
        
    matrices.push_back(data01);
    
    filename.str("");
    
  }
  
  std::cout << matrices.size() << std::endl;

  TCanvas * c1 = new TCanvas("c1","Plots",100,50,600,400);
  
  c1->SetFillColor(10);
  c1->cd();
  c1->SetLogy();
  
  histo->Draw();

  c1->Print("results.eps");

  // Analisis

  std::vector<Data*>::cons_iterator itrData;
  
  InvMineSweeper * algo = new InvMineSweeper( );

  for( itrData = matrices.begin(); itrData != matrices.end(); ++itrData) 
  {
    
    algo->Analyse( (*itrData) );
    
    
  }

  //
  
  return 1;
    
}
