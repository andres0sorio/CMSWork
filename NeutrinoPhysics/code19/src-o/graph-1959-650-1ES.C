
//To run this code:
// root [0] .L graph-separate-data-v2.C
// root [1] makePlots()
// .q (quit)

TGraphAsymmErrors * readTypeOne( const char * fname) 
{
  
  ifstream in;
  in.open(fname); //
  
  double en, flux, enerr1, enerr2, fluxerr1, fluxerr2; //we read 6 columns of data
  
  TGraphAsymmErrors * graphT1 = new TGraphAsymmErrors(); 
  
  int i = 0;
  
  while ( in.good() ) 
  {
    
    in >> en >> flux >> enerr1 >> enerr2 >> fluxerr1 >> fluxerr2;
    
    graphT1->SetPoint( i , en, flux);
    graphT1->SetPointError( i, enerr1, enerr2, fluxerr1, fluxerr2);
    
    ++i;
    
  }
 
  std::cout << "Total points read: " << i << std::endl;
  
  in.close();
  
  return graphT1;
  
}

TGraphErrors * readTypeTwo( const char * fname) 
{

  ifstream in;
  in.open(fname); //
  
  double en, flux, enerr, fluxerr;
  
  TGraphErrors * graphT2 = new TGraphErrors(); 
 
  int i = 0;
  
  while ( in.good() ) 
  {
    
    in >> en >> flux >> enerr >> fluxerr; //we read 4 columns of data
    
    graphT2->SetPoint( i , en, flux);
    graphT2->SetPointError( i, enerr, fluxerr);
  
    ++i;
    
  }
  
  std::cout << "Total points read: " << i << std::endl;
  
  in.close();
  
  return graphT2;

}

TGraphErrors * readTypeThree( const char * fname) 
{

  ifstream in;
  in.open(fname); //
  
  double en, flux, fluxerr;

  TGraphErrors * graphT3 = new TGraphErrors(); 

  int i = 0;
  
  while ( in.good() ) 
  {
    
    in >> en >> flux >> fluxerr; //we read 3 columns of data
    
    graphT3->SetPoint( i , en, flux);
    graphT3->SetPointError( i,  0.0, fluxerr);
    
    ++i;
    
  }

  std::cout << "Total points read: " << i << std::endl;
  
  in.close();

  return graphT3;

}

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


void makePlots() {

  //. Plots of separate data and different data formats
  //.
  //. The available data formats and their matching Graph objects are:
  //. 6 columns data (x,y, x1, x2, y1, y2) == TGraphAsymmErrors
  //. 4 columns data (x,y, xerr, yerr) == TGraphErrors
  //. 3 columns data (x,y, yerr) == TGraphErros ( xerr = 0.0)
  //. 2 columns data (x,y) == TGraph
  //.
  //.... 
    

  int ndataset = 0;
  TList * allgraphs = new TList(); //this is a ROOT container. It will store all of your Graphs
  TList * allgraphsNames = new TList();

  bool addTaggliaferi = true;
  
  // 1. 6 columns data
  
  TGraphAsymmErrors * graphT1 =  readTypeOne("1959-650-1ES-data/data-set-n6-MAGIC-uncorrected.txt");
  allgraphs->Add( graphT1 ); 
  ndataset++;
  
  TString * s1 = new TString("MAGIC-uncorrected");
  allgraphsNames->Add( (TObject*)s1 );
  
  graphT1 =  readTypeOne("1959-650-1ES-data/data-set-n7-MAGIC-corrected-absorption-by-IR.txt");
  allgraphs->Add( graphT1 ); 
  ndataset++;
  s1 = new TString("MAGIC-corrected");
  allgraphsNames->Add( (TObject*)s1 );

  graphT1 =  readTypeOne("1959-650-1ES-data/data-set-n8-historical-TeV-region.txt"); 
  allgraphs->Add( graphT1 ); 
  ndataset++;
  s1 = new TString("TeV Flare");
  allgraphsNames->Add( (TObject*)s1 );

  // 1. 3 columns data

  TGraphErrors * graphT3 = readTypeThree("1959-650-1ES-data/data-set-n2-optical-UV-swift.txt");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  s1 =  new TString("UV-swift");
  allgraphsNames->Add( (TObject*)s1 );

  graphT3 = readTypeThree("1959-650-1ES-data/data-set-n3-may24-max.txt");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  s1 = new TString("May 24 2002");
  allgraphsNames->Add( (TObject*)s1 );

  graphT3 = readTypeThree("1959-650-1ES-data/data-set-n4-may19-min.txt");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  s1 = new TString("May 19 2002");
  allgraphsNames->Add( (TObject*)s1 );


  graphT3 = readTypeThree("1959-650-1ES-data/data-set-n5-avg-suzaku-swift-may24-29.txt");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  s1 = new TString("Avg. Suzaku+Swift 2002");
  allgraphsNames->Add( (TObject*)s1 );

  
  // 1. 2 columns data
  
  TGraph * graphT4 = readTypeFour("1959-650-1ES-data/data-set-n1-historical-low-region.txt");
  allgraphs->Add( graphT4 ); //Append to your List this Graph
  ndataset++;
  s1 = new TString("Historical Low Region");
  allgraphsNames->Add( (TObject*)s1 );
  
  graphT4 = readTypeFour("1959-650-1ES-data/data-set-n9-optical-UV-ground.txt");
  allgraphs->Add( graphT4 ); //Append to your List this Graph
  ndataset++;
  s1 = new TString("Optical-UV Ground");
  allgraphsNames->Add( (TObject*)s1 );

  if ( addTaggliaferi ) {
    
    graphT4 = readTypeFour("1959-650-1ES-data/log-parabolas-fit-data-points-v4.txt.csv");
    allgraphs->Add( graphT4 ); //Append to your List this Graph
    ndataset++;
    s1 = new TString("Synch. + SSC fit");
    allgraphsNames->Add( (TObject*)s1 );
    
  }

  //SARIRA's Results
  graphT4 = readTypeFour("1959-650-1ES-data/output7");
	allgraphs->Add( graphT4 ); //Append to your List this Graph
  ndataset++;	
  
  s1 = new TString("This paper");
  allgraphsNames->Add( (TObject*)s1 );


  std::cout << "Total dataset read " << ndataset << " " << std::endl;

  //. End of reading and creating Graphs from data files
  //.
  ////////////////////////////////////////////////////////////////////////////////////
  //. 
  //. Plot each Dataset on a sigle Canvas (all combined)
  
  TCanvas * canvas = new TCanvas("Plot1", "Canvas for plot 1", 46,83,833,738);
  canvas->SetFillColor(10);
  canvas->Range(6.027778,-13.51408,29.05556,-8.514085);
  canvas->SetFillColor(10);
  canvas->SetBorderMode(0);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.172497);
  //canvas->SetRightMargin(0.07936508);
  //canvas->SetTopMargin(0.06605223);
  canvas->SetFrameFillColor(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  
  //If you need log scale on both axis - uncomment the following lines
  //canvas->SetLogx();
  //canvas->SetLogy();
  
  //Set the minimum and maximum for the whole graph
  //Min a max for Axis
  float xmin =  10.0;
  float xmax =  28.0;
  float ymin = -13.0;
  float ymax =  -9.0;
  
  //Datasets options (Markers: style, color, size) : You can also do it by hand using the interactive Editor
  int style[15];
  int color[15];
  float size[15];
  
  Int_t gray = TColor::GetColor("#000099");

  //For dataset No1
  style[0] = 25;
  color[0] = 3;
  size[0]  = 1.0;
  
  //For dataset No2
  style[1] = 26;
  color[1] = 2;
  size[1]  = 1.0;
  
  //For dataset No3
  style[2] = 24;
  color[2] = 15;
  size[2]  = 1.0;
  
  //For dataset No4
  style[3] = 20;
  color[3] = 4;
  size[3]  = 0.5;

  //For dataset No5
  style[4] = 24;
  color[4] = 4;
  size[4]  = 0.8;

  //For dataset No6
  style[5] = 26;
  color[5] = 4;
  size[5]  = 0.8;

  //For dataset No7
  style[6] = 7;
  color[6] = 2;
  size[6]  = 1.0;
  
  //For dataset No8
  style[7] = 25;
  color[7] = 15;
  size[7]  = 1.0;

  //For dataset No9
  style[8] = 26;
  color[8] = 7;
  size[8]  = 1.0;

  //For dataset No10
  style[9] = 1;
  color[9] = 3;
  size[9]  = 1.0;

  
  //Add Legend here:

  //Add Legends:
  TLegend * legend = new TLegend(0.3039807,0.1422535,0.5138721,0.4366197,NULL,"brNDC");
  
  //Legend options
  legend->SetBorderSize(1);
  legend->SetTextFont(62);
  legend->SetLineColor(1);
  legend->SetLineStyle(1);
  legend->SetLineWidth(1);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
   
  TString yaxisLabel("Log E^{2}_{#gamma} #frac{dN_{#gamma}}{dE_{#gamma}} [ erg cm^{-2} s^{-1} ]");
  
  // Loop over all Graphs and draw them in the Canvas
  // Min,Max for X and Y axis are set on the first Graph that is plotted

  ndataset = allgraphs->GetSize(); //Get the ndatasets from the size of the List
    
  // Loop now over the List using the index k

  for(int k=0; k < ndataset; ++k) {
    
    if( k == 0 ) {
      //this is our first graph and it is special (to define axis min,max)
      ((TGraph*)allgraphs->At(k))->SetMinimum(ymin);
      ((TGraph*)allgraphs->At(k))->SetMaximum(ymax);
      ((TGraph*)allgraphs->At(k))->Draw("AP");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLimits(xmin, xmax);
      //set the color options
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );

      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitle("Log E_{#gamma} [ Hz ]");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->CenterTitle(true);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLabelFont(42);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleFont(42);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleSize(0.03);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLabelSize(0.035);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleOffset(1.46);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetNdivisions(508);
      
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitle(yaxisLabel.Data());
      ((TGraph*)allgraphs->At(k))->GetYaxis()->CenterTitle(true);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetLabelFont(42);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleFont(42);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetLabelOffset(0.012);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetLabelSize(0.035);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleSize(0.03);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleOffset(2.06);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetNdivisions(508);

      ((TGraph*)allgraphs->At(k))->Draw("AP"); // Draw option AP A=draw axis P=draw a marker for the data

      legend->AddEntry( ((TGraph*)allgraphs->At(k)), ((TString*)allgraphsNames->At(k))->Data() ,"P");
      
    }

    else {

      if( k == 9 || k == 10 ){
        ((TGraph*)allgraphs->At(k))->SetLineWidth(2);
        ((TGraph*)allgraphs->At(k))->Draw("L");

        //If you want your data to appear on the legend Box then uncomment this line
        //legend->AddEntry( ((TGraph*)allgraphs->At(k)), ((TString*)allgraphsNames->At(k))->Data() ,"L");

      } else {
        
        ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
        ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
        ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
        ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] ); 
        // since we have already plotted the axis on the first graph we only need option P
        ((TGraph*)allgraphs->At(k))->Draw("P"); 

        legend->AddEntry( ((TGraph*)allgraphs->At(k)), ((TString*)allgraphsNames->At(k))->Data() ,"P");
        
      }
        
    }
    
  }
  
  legend->Draw();

  bool secondaryAxis = false;
  
  if( secondaryAxis ) {
    
    double sec_xmin = -4.38;
    double sec_xmax = 13.61;
    double sec_ymin = 41.8;
    double sec_ymax = 45.6;
        
    // draw axis on the top side of the pad
    TGaxis *axisSupX = new TGaxis(xmin, ymax, xmax, ymax, sec_xmin, sec_xmax, 505,"-L");
    axisSupX->SetLabelColor(1);
    axisSupX->SetTitle("Log E [ eV ]");
    axisSupX->CenterTitle(true);
    axisSupX->SetLabelFont(42);
    axisSupX->SetTitleFont(42);
    axisSupX->SetTitleSize(0.04);
    axisSupX->SetLabelSize(0.035);
    axisSupX->SetTitleOffset(1.10);
    
    axisSupX->Draw();
    
    TGaxis *axisSupY = new TGaxis(xmax, ymin, xmax, ymax, sec_ymin, sec_ymax, 505,"+L");
    axisSupY->SetLabelColor(1);
    axisSupY->SetTitle("Log #nuL(#nu) [ erg/s ]");
    axisSupY->CenterTitle(true);
    axisSupY->SetLabelFont(42);
    axisSupY->SetTitleFont(42);
    axisSupY->SetTitleSize(0.04);
    axisSupY->SetLabelSize(0.035);
    axisSupY->SetTitleOffset(0.96);
    axisSupY->Draw();
    
  }
  

  /// All done!
  
}

double convertLognu2LogE( double lognu ) 
{
  
  double nu = pow( 10.0, lognu );
  double hplanck = 4.135667516E-15;
  double energy = nu * hplanck ;
  return log10(energy);
    
}
