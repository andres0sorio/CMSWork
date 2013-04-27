{

  //. Plots of separate data and different data formats
  //.
  //. The available data formats and their matching Graph objects are:
  //. 6 columns data (x,y, x1, x2, y1, y2) == TGraphAsymmErrors
  //. 4 columns data (x,y, xerr, yerr) == TGraphErrors
  //. 3 columns data (x,y, yerr) == TGraphErros ( xerr = 0.0)
  //. 2 columns data (x,y) == TGraph
  //.
  //.... 
  //. You will need to match your data with any of those objects
  

  //Examples:
  
  int i = 0;
  int ndataset = 0;
  TList * allgraphs = new TList(); //this is a ROOT container. It will store all of your Graphs
  
  // 1. 6 columns data
  
  ifstream in1;
  in1.open("test/data-6-columns.txt"); //
  
  double en, flux, enerr1, enerr2, fluxerr1, fluxerr2; //we read 6 columns of data
  
  TGraphAsymmErrors * graphT1 = new TGraphAsymmErrors(); 
  
  i = 0;
  
  while ( in1.good() ) 
  {
    
    in1 >> en >> flux >> enerr1 >> enerr2 >> fluxerr1 >> fluxerr2;
    
    graphT1->SetPoint( i , en, flux);
    graphT1->SetPointError( i, enerr1, enerr2, fluxerr1, fluxerr2);
  
    ++i;
    
  }
  
  allgraphs->Add( graphT1 ); //Append to your List this Graph
  ndataset++;
 
  // 1. 4 columns data
  
  ifstream in2;
  in2.open("test/data-4-columns.txt"); //
  
  double enerr, fluxerr; // variables en=x and flux=y are already declared 
  
  TGraphErrors * graphT2 = new TGraphErrors(); 
 
  i = 0;
  
  while ( in2.good() ) 
  {
    
    in2 >> en >> flux >> enerr >> fluxerr; //we read 4 columns of data
    
    graphT2->SetPoint( i , en, flux);
    graphT2->SetPointError( i, enerr, fluxerr);
  
    ++i;
    
  }

  allgraphs->Add( graphT2 ); //Append to your List this Graph
  ndataset++;

  // 1. 3 columns data
  
  ifstream in3;
  in3.open("test/data-3-columns.txt"); //
  
  ///double en, flux, enerr1, enerr2, fluxerr1, fluxerr2; //we can use the already declared variables 
  
  TGraphErrors * graphT3 = new TGraphErrors(); 

  i = 0;
  
  while ( in3.good() ) 
  {
    
    in3 >> en >> flux >> fluxerr; //we read 3 columns of data
    
    graphT3->SetPoint( i , en, flux);
    graphT3->SetPointError( i,  0.0, fluxerr);
    
    ++i;
    
  }

  allgraphs->Add( graphT3 ); //Append to your List this Graph
  ndataset++;

  // 1. 2 columns data
  
  ifstream in4;
  in4.open("test/data-2-columns.txt"); //
  
  /// double en, flux, enerr1, enerr2, fluxerr1, fluxerr2; //we can use the already declared variables 
  
  TGraph * graphT4 = new TGraph(); //we read 2 columns of data

  i = 0;
  
  while ( in4.good() ) 
  {
    
    in4 >> en >> flux;
    
    graphT4->SetPoint( i , en, flux);
    
    ++i;
    
  }

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
  float xmin = 0.0;
  float xmax = 30;
  float ymin = 0;
  float ymax = 8.0;
  
  //Datasets options (Markers: style, color, size) : You can also do it by hand using the interactive Editor
  int style[15];
  int color[15];
  float size[15];
  
  //For dataset No1
  style[0] = 22;
  color[0] = 2;
  size[0]  = 1.0;
  
  //For dataset No2
  style[1] = 25;
  color[1] = 4;
  size[1]  = 1.0;
  
  //For dataset No3
  style[2] = 24;
  color[2] = 3;
  size[2]  = 1.0;
  
  //For dataset No4
  style[3] = 26;
  color[3] = 6;
  size[3]  = 0.5;

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
      ((TGraph*)allgraphs->At(k))->Draw("P"); // since we have already plotted the axis on the first graph we only need option P
    }
    
  }

  /// Close all data files

  in1.close();
  in2.close();
  in3.close();
  in4.close();
  
  /// All done!
  
}

// .q (quit)
//.x graph-separate-data.C

