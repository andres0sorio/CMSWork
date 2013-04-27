// $Id: 
// Include files 

#include <RootCommon.h>
#include <DensityModels.h>
#include <sstream>
#include "sys/stat.h"
#include <map>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TList.h>
#include <TAxis.h>
#include <TLegend.h>

TGraph * readTypeFour( const char * fname);

TGraph * readTypeFour( const char * fname) 
{

  ifstream in;
  in.open(fname); //
  
  double en, flux;
  
  TGraph * graphT4 = new TGraph(); 

  int i = 0;
  
  while ( in.good() ) 
  {
    
    in >> en >> flux; //we read 2 columns of data
    
    graphT4->SetPoint( i , en, flux);
    
    ++i;
    
  }

  std::cout << "Total points read: " << i << std::endl; 
    
  in.close();
  
  return graphT4;
  
}

int intplot() {
  
  //.........................................................................................
  
  TCanvas *c1 = new TCanvas("c1","Graphics canvas",370,109,723,620);
  
  c1->SetFillColor(10);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->Draw();
  c1->cd();

  bool convert = false;
  bool add_datapoints = false;
  
  double cm2ev = 5.076e+4;
  double gcm3  = 4.2951E+18 * 8.79e-33;
  
  double LMAX  = 0.0;
  double LMIN  = 0.0;
  
  double k0 = 4.0e-6; // g / cm^3
  double kB = 3.4e-5; // g / cm^3
  double kC = 6.3e-6; // g / cm^3

  //Model A specific
  
  double lmax =  0.0;

  //Model B specific
  
  //double RstarCM = pow(10.0,12.5); //cm
  double RstarCM = 3.0e12; //cm
  double RbCM = 1.0e12; // cm
  double Rmin = pow(10.0, 10.8); //cm
  
  double cfact = 0.0;

  //Model C specific
  double RcCM = 1.0e11; // cm
  double A1 = 20.0;
  double neff1 = 2.1;
  double A2 = 1.0;
  double neff2 = 2.5;
  
  if( convert )
  {
    
    k0 = k0 * gcm3;
    kB = kB * gcm3;
    kC = kC * gcm3;
    
    //Model A
    
    lmax = RstarCM * cm2ev;
    
    //Model B
    
    RstarCM = RstarCM;
    RbCM = RbCM;
    Rmin = Rmin;
    cfact = cm2ev;
    
    //Model C

    RcCM = RcCM;
    
    LMIN = Rmin * cm2ev;
    LMAX = RstarCM * cm2ev;
    
    //sprintf(xLabel,"L [1/eV]");
    //sprintf(yLabel,"A [eV]");
    
  } else {
    
    k0 = k0;
    kB = kB;
    
    //Model A

    lmax = RstarCM;
    
    //Model B
    
    RstarCM = RstarCM;
    RbCM = RbCM;
    Rmin = Rmin;
    cfact = 1.0;
    
    //Model C

    RcCM = RcCM;

    LMIN = Rmin;
    LMAX = RstarCM; 
        
    //sprintf(xLabel,"L [m]");
    //sprintf(yLabel,"#rho [g/cm^{3}]");
    
  }

  std::map<std::string,DensityModels*> m_Models;

  m_Models["ModelA"] = (DensityModels*) new rhoModelA();
  m_Models["ModelB"] = (DensityModels*) new rhoModelB();
  m_Models["ModelC"] = (DensityModels*) new rhoModelC();
  
  DensityModels * density_Mod = m_Models["ModelA"];
  
  int maxpars = 2;
  
  TF1 * profA = new TF1("profA", density_Mod, LMIN, LMAX + 1.0e12, maxpars);
  
  profA->SetParameter( 0 ,   k0);
  profA->SetParameter( 1 ,   lmax);
  
  density_Mod = m_Models["ModelB"];

  maxpars = 5;
  
  TF1 * profB = new TF1("profB", density_Mod, LMIN, LMAX, maxpars);
  
  profB->SetParameter( 0 , kB );
  profB->SetParameter( 1 , RstarCM );
  profB->SetParameter( 2 , RbCM );
  profB->SetParameter( 3 , Rmin );
  profB->SetParameter( 4 , cfact );
  
  density_Mod = m_Models["ModelC"];

  maxpars = 9;

  TF1 * profC = new TF1("profC", density_Mod, LMIN, LMAX, maxpars);
  
  profC->SetParameter( 0 ,   kC);
  profC->SetParameter( 1 ,   RstarCM);
  profC->SetParameter( 2 ,   RcCM);
  profC->SetParameter( 3 ,   Rmin);
  profC->SetParameter( 4 ,   A1);
  profC->SetParameter( 5 ,   neff1);
  profC->SetParameter( 6 ,   A2);
  profC->SetParameter( 7 ,   neff2);
  profC->SetParameter( 8 ,   cfact);
  
  c1->cd();
  c1->SetLogx();
  c1->SetLogy();

  profA->SetLineColor(1);
  profA->SetLineWidth(2);

  if(convert)
    profA->GetXaxis()->SetTitle("r (1/eV)");
  else
    profA->GetXaxis()->SetTitle("r (cm)");
  
  profA->GetXaxis()->CenterTitle(true);
  profA->GetXaxis()->SetLabelFont(42);
  profA->GetXaxis()->SetLabelSize(0.035);
  profA->GetXaxis()->SetTitleSize(0.035);
  profA->GetXaxis()->SetTitleFont(42);

  if(convert) 
    profA->GetYaxis()->SetTitle("A (eV)");
  else
    profA->GetYaxis()->SetTitle("#rho ( g/cm^{3} )");
  

  profA->GetYaxis()->CenterTitle(true);
  profA->GetYaxis()->SetLabelFont(42);
  profA->GetYaxis()->SetLabelSize(0.035);
  profA->GetYaxis()->SetTitleSize(0.035);
  profA->GetYaxis()->SetTitleFont(42);
  profA->GetYaxis()->SetTitleOffset(1.35);

  if(!convert) 
  {
    profA->SetMaximum(1.0);
    profA->SetMinimum(1.0e-10);
  }
  
  profA->Draw();

  profB->SetLineColor(1);
  profB->SetLineStyle(2);
  profB->SetLineWidth(2);
  profB->Draw("same");
  
  profC->SetLineColor(1);
  profC->SetFillColor(10);
  profC->SetLineStyle(5);
  profC->SetLineWidth(2);
  profC->Draw("same");
  
    
  TLegend * leg = new TLegend(0.18,0.36,0.47,0.55);
  leg->SetBorderSize(0);
  leg->AddEntry( profA,"A","L");
  leg->AddEntry( profB,"B","L");
  leg->AddEntry( profC,"C","L");
  leg->SetFillColor(10);
  leg->Draw();
  
  //.........................................................................................

  TList * allgraphs = new TList(); //this is a ROOT container. It will store all of your Graphs
  
  int ndataset = 0;
  
  TGraph * graphT1;
  
  graphT1 =  readTypeFour("../data/mena_01.csv");
  if ( add_datapoints ) { 
    allgraphs->Add( graphT1 ); 
    ndataset++;
  }
  
  
  graphT1 =  readTypeFour("../data/mena_02.csv");
  if ( add_datapoints ) { 
    allgraphs->Add( graphT1 ); 
    ndataset++;
  }
  

  graphT1 =  readTypeFour("../data/mena_03.csv");
  if ( add_datapoints ) { 
    allgraphs->Add( graphT1 ); 
    ndataset++;
  }
  

  ///
  
   ndataset = allgraphs->GetSize(); //Get the ndatasets from the size of the List

  // Loop now over the List using the index k

   //Datasets options (Markers: style, color, size) : You can also do it by hand using the interactive Editor
  int style[5];
  int color[5];
  float size[5];
  
  //For dataset No1
  style[0] = 25;
  color[0] = 1;
  size[0]  = 0.6;

  //For dataset No1
  style[1] = 26;
  color[1] = 1;
  size[1]  = 0.6;
  
  //For dataset No1
  style[2] = 21;
  color[2] = 4;
  size[2]  = 0.6;
  
  for(int k=0; k < ndataset; ++k) {
    
    ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
    ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
    ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
    ((TGraph*)allgraphs->At(k))->Draw("P");
    
  }
  
  c1->Print("supernova_model_ABC.pdf");
  c1->Print("supernova_model_ABC.eps");

  return 0;
  
}
