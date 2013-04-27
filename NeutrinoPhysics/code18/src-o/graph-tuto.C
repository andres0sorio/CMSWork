{
  ifstream in;
  in.open("EGRETplusModels.csv"); //this file contains all of your data
  
  std::string header[6]; //each data set has a header part (x, y, xelow, xeup, yelow, yeup)
  
  double en, flux, enerr1, enerr2, fluxerr1, fluxerr2; //this we keep
  
  int np = 0; //good np is going to be the number of points per dataset
  int ndataset = 0;
  
  TGraphAsymmErrors * graph[15]; //we need approx. 15 TGraphs (1 per dataset)
  
  while ( in.good() ) 
  {

    //First line of data set:
    //... apart from np, we don´t really need this (but has to be read)
    
    in >> np >> header[0] >> header[1] >> header[2] >> header[3] >> header[4] >> header[5];
    
    //... np contains the number of points
    std::cout << "Dataset has " << np << " points." << std::endl;
    
    //First lets create the TGraphAsymErrors:
    graph[ndataset] = new TGraphAsymmErrors();
    
    int pindex = 0;
    
    for(int k = 0; k < np; ++k) {
      
      in >> pindex >> en >> flux >> enerr1 >> enerr2 >> fluxerr1 >> fluxerr2;
      
      graph[ndataset]->SetPoint( k , en, flux);
      graph[ndataset]->SetPointError( k, enerr1, enerr2, fluxerr1, fluxerr2);
      
    }
    
    ndataset++;
 
    if ( ndataset >= 15 ) break; //for safety as we have fixed a maximum of 15 TGraphs
 
  }
  
  std::cout << "Total dataset read " << ndataset << " " << std::endl;
  
  //Plot each Dataset on a sigle Canvas (all combined)
  
  TCanvas * canvas = new TCanvas("Plot1", "Canvas for plot 1", 94, 262,700, 502 );
  canvas->SetFillColor(10);

  //Important set log scale on both axis
  canvas->SetLogx();
  canvas->SetLogy();

  
  //Min a max for Axis
  float xmin = 1.0E-11;
  float xmax = 1.0E25;
  float ymin = 1E-14;
  float ymax = 1E2;
  
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

  for(int k=0; k < ndataset; ++k) {
    
    if( k == 0 ) {
      //this is our first graph and it is special (to define axis min,max)
      graph[k]->SetMinimum(ymin);
      graph[k]->SetMaximum(ymax);
      graph[k]->Draw("AP");
      graph[k]->GetXaxis()->SetLimits(xmin, xmax);
      //set the color options
      graph[k]->SetMarkerStyle( style[k] );
      graph[k]->SetMarkerSize( size[k] );
      graph[k]->SetMarkerColor( color[k] );
      graph[k]->SetLineColor( color[k] );
      graph[k]->Draw("AP");

    }
    else {
      graph[k]->SetMarkerStyle( style[k] );
      graph[k]->SetMarkerSize( size[k] );
      graph[k]->SetMarkerColor( color[k] );
      graph[k]->SetLineColor( color[k] );
      graph[k]->Draw("P");
    }
    
  }

  in.close();
  
}

// .q (quit)
//.x graph-tuto.C
