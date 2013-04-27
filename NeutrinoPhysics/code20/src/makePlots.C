//To run this code:
// root [0] .L makePlots.C
// root [1] makePlots()

// .q (quit)



TGraph * readData( const char * fname , int coly ) 
{

  ifstream in;
  in.open(fname); //
  
  double en;
  double p[9];
  double flux[3];

  TGraph * graph = new TGraph(); 

  int i = 0;
  
  while ( in.good() ) 
  {
    
    in >> en;
    
    for(int k=0; k < 9; ++k) {
      in >>  p[k];
    }
    
    for(int k=0; k < 3; ++k) {
      in >>  flux[k];
    }
    
    graph->SetPoint( i , en, flux[coly] );
    
    ++i;
    
  }

  std::cout << "Total points read: " << i << std::endl; 
    
  in.close();
  
  return graph;
  
}


void makePlots(const char *filename, const char * graph_title, const char * perfil ) {
 
  int ndataset = 0;

  TList * allgraphs = new TList(); //this is a ROOT container. It will store all of your Graphs
  // 1. data in Karla's format
  
  TGraph * graphT = readData( filename, 0 );
  allgraphs->Add( graphT ); //Append to your List this Graph
  ndataset++;
  
  //graphT = readData( filename, 1 );
  //allgraphs->Add( graphT ); //Append to your List this Graph
  //ndataset++;

  //graphT = readData( filename, 0 );
  //allgraphs->Add( graphT ); //Append to your List this Graph
  //ndataset++;

  //. End of reading and creating Graphs from data files
  //.
  ////////////////////////////////////////////////////////////////////////////////////
  //. 
  //. Plot each Dataset on a sigle Canvas (all combined)
  
  TCanvas * canvas = new TCanvas("Plot1", "Canvas for plot 1", 94, 262,700, 502 );
  canvas->SetFillColor(10);
  canvas->SetTickx(1);
  canvas->SetTicky(1);

  //If you need log scale on both axis - uncomment the following lines
  canvas->SetLogx();
  //canvas->SetLogy();
  
  //Set the minimum and maximum for the whole graph
  //Min a max for Axis
  float xmin =  3.0E10;
  float xmax =  1.0E14;
  float ymin =  0.0;
  float ymax =  1.0;
  
  //Datasets options (Markers: style, color, size) : You can also do it by hand using the interactive Editor
  int style[3];
  int color[3];
  float size[3];
  
  //For dataset No1
  style[0] = 1;
  color[0] = 4;
  size[0]  = 2.0;
  
  //For dataset No2
  style[1] = 5;
  color[1] = 2;
  size[1]  = 2.0;
  
  //For dataset No3
  style[2] = 9;
  color[2] = 1;
  size[2]  = 2.0;
  
  //Legends - titulos de cada graficaq
  TLegend * legend = new TLegend(0.66,0.68,0.86,0.87,NULL,"brNDC");
  //Legend optionsq
  legend->SetBorderSize(1);
  legend->SetTextFont(62);
  legend->SetLineColor(1);
  legend->SetLineStyle(1);
  legend->SetLineWidth(1);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  
    
  // Loop over all Graphs and draw them in the Canvas
  // Min,Max for X and Y axis are set on the first Graph that is plotted

  ndataset = allgraphs->GetSize(); //Get the ndatasets from the size of the List
    
  // Loop now over the List using the index k

  for(int k=0; k < ndataset; ++k) {
    
    if( k == 0 ) {
      //this is our first graph and it is special (to define axis min,max)
      ((TGraph*)allgraphs->At(k))->SetTitle(graph_title);
      ((TGraph*)allgraphs->At(k))->SetMinimum(ymin);
      ((TGraph*)allgraphs->At(k))->SetMaximum(ymax);
      ((TGraph*)allgraphs->At(k))->Draw("AL");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLimits(xmin, xmax);
      //set the color options
      ((TGraph*)allgraphs->At(k))->SetLineStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetLineWidth( size[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
      
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitle("E_{#bar{#nu}} [eV]");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->CenterTitle(true);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLabelFont(42);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleSize(0.05);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleOffset(0.9);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleFont(42);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitle("Normalized Flux");
      ((TGraph*)allgraphs->At(k))->GetYaxis()->CenterTitle(true);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetLabelFont(42);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetLabelSize(0.035);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleSize(0.05);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleFont(42);

      ((TGraph*)allgraphs->At(k))->Draw("AL"); 
      // Draw option AL A=draw axis L=draw a marker for the data

    }
    else {
      ((TGraph*)allgraphs->At(k))->SetLineStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetLineWidth( size[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
      ((TGraph*)allgraphs->At(k))->Draw("L"); 
      // since we have already plotted the axis on the first graph we only need option L
    }
         
  }

  legend->AddEntry((TGraph*)allgraphs->At(0),"#bar{#nu}_{#tau}","L");

  //legend->Draw();

  interpolator( graphT );
  
  
  
}

