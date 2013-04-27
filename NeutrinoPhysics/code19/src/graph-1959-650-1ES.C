
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
  
  // 1. 6 columns data
  
  TGraphAsymmErrors * graphT1 =  readTypeOne("../data/1959-650-1ES-data/data-set-n6-MAGIC-uncorrected.txt");
  allgraphs->Add( graphT1 ); 
  ndataset++;
  
  graphT1 =  readTypeOne("../data/1959-650-1ES-data/data-set-n7-MAGIC-corrected-absorption-by-IR.txt");
  allgraphs->Add( graphT1 ); 
  ndataset++;
  
  graphT1 =  readTypeOne("../data/1959-650-1ES-data/data-set-n8-historical-TeV-region.txt"); 
  allgraphs->Add( graphT1 ); 
  ndataset++;
  
  // 1. 3 columns data
  
  TGraphErrors * graphT3 = readTypeThree("../data/1959-650-1ES-data/data-set-n2-optical-UV-swift.txt");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  
  graphT3 = readTypeThree("../data/1959-650-1ES-data/data-set-n3-may24-max.txt");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  
  graphT3 = readTypeThree("../data/1959-650-1ES-data/data-set-n4-may19-min.txt");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;

  graphT3 = readTypeThree("../data/1959-650-1ES-data/data-set-n5-avg-suzaku-swift-may24-29.txt");
  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;
  
  // 1. 2 columns data
  
  TGraph * graphT4 = readTypeFour("../data/1959-650-1ES-data/data-set-n1-historical-low-region.txt");
  allgraphs->Add( graphT4 ); //Append to your List this Graph
  ndataset++;
  
  graphT4 = readTypeFour("../data/1959-650-1ES-data/data-set-n9-optical-UV-ground.txt");
  allgraphs->Add( graphT4 ); //Append to your List this Graph
  ndataset++;

  graphT4 = readTypeFour("../data/1959-650-1ES-data/log-parabolas-fit-data-points-v4.txt.csv");
  allgraphs->Add( graphT4 ); //Append to your List this Graph
  ndataset++;
  
  std::cout << "Total dataset read " << ndataset << " " << std::endl;

  //. End of reading and creating Graphs from data files
  //.
  ////////////////////////////////////////////////////////////////////////////////////
  //. 
  //. Plot each Dataset on a sigle Canvas (all combined)
  
  TCanvas * canvas = new TCanvas("Plot1", "Canvas for plot 1", 94, 262,700, 502 );
  canvas->SetFillColor(10);
  
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
  
  //For dataset No1
  style[0] = 25;
  color[0] = 2;
  size[0]  = 1.0;
  
  //For dataset No2
  style[1] = 26;
  color[1] = 4;
  size[1]  = 1.0;
  
  //For dataset No3
  style[2] = 24;
  color[2] = 38;
  size[2]  = 1.0;
  
  //For dataset No4
  style[3] = 20;
  color[3] = 4;
  size[3]  = 0.5;

  //For dataset No5
  style[4] = 24;
  color[4] = 6;
  size[4]  = 0.8;

  //For dataset No6
  style[5] = 26;
  color[5] = 2;
  size[5]  = 0.8;

  //For dataset No7
  style[6] = 7;
  color[6] = 2;
  size[6]  = 1.0;
  
  //For dataset No8
  style[7] = 25;
  color[7] = 38;
  size[7]  = 1.0;

  //For dataset No9
  style[8] = 26;
  color[8] = 7;
  size[8]  = 1.0;

  //For dataset No10
  style[9] = 1;
  color[9] = 1;
  size[9]  = 1.0;

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
      ((TGraph*)allgraphs->At(k))->Draw("AP"); // Draw option AP A=draw axis P=draw a marker for the data

    }
    else {
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] ); 
      // since we have already plotted the axis on the first graph we only need option P
      ((TGraph*)allgraphs->At(k))->Draw("P"); 
      if( k == 9 ){
        ((TGraph*)allgraphs->At(k))->SetLineWidth(2);
        ((TGraph*)allgraphs->At(k))->Draw("L");
      }
      
    }
    
  }

  logpar_interp * fobj = new logpar_interp("../data/1959-650-1ES-data/log-parabolas-fit-data-points-v4.txt.csv");
  
  TF1 * f2 = new TF1("f", fobj, 11, 26, 0,"logpar_interp");
  f2->SetLineColor(1);
  f2->SetLineStyle(3);
  f2->Draw("SAME");

  /// All done!
  
}

