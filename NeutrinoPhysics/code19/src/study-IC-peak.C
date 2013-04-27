//To run this code:
// root [0] .L study-IC-peak.C
// root [1] runStudy()
//
// .q (quit)
//

const double deg2rad = TMath::Pi() / 180.0;
const double hplanck = 4.135E-15; // eV s

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

TGraph * readTypeFour( const char * fname, double xmin, double xmax, double ymin, double ymax)
{
  
  ifstream in;
  in.open(fname); //
  
  double en, flux;
  
  TGraph * graphT4 = new TGraph(); 
  
  int i = 0;
  
  while ( in.good() ) 
  {
    
    in >> en >> flux; //we read 2 columns of data
    if( (en > xmin && en < xmax) && (flux > ymin && flux < ymax) ) {
      graphT4->SetPoint( i , en, flux);
      ++i;
    }
    
    
  }

  std::cout << "Total points read: " << i << std::endl; 
    
  in.close();
  
  return graphT4;
  
}


void runStudy() {

  int ndataset = 0;
  TList * allgraphs = new TList(); //this is a ROOT container. It will store all of your Graphs
  
  // 1. 2 columns data
  
  TGraph * graphT4 = readTypeFour("../data/1959-650-1ES-data/log-parabolas-fit-data-points-v2.txt.csv");
  allgraphs->Add( graphT4 ); //Append to your List this Graph
  ndataset++;
  
  graphT4 = readTypeFour("../data/1959-650-1ES-data/log-parabolas-fit-data-points-v3.txt.csv", 
                         //15.0, 20.0, -10.5, -9.0 );
                         //22.0, 27.0, -11.5, -10.5 );
                         19.0, 21.0, -12.5, -10.5);
  
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
  style[0] = 1;
  color[0] = 1;
  size[0]  = 1.0;
  
  //For dataset No2
  style[1] = 2;
  color[1] = 2;
  size[1]  = 1.0;
  
  // Loop over all Graphs and draw them in the Canvas
  // Min,Max for X and Y axis are set on the first Graph that is plotted

  ndataset = allgraphs->GetSize(); //Get the ndatasets from the size of the List
    
  // Loop now over the List using the index k

  for(int k=0; k < ndataset; ++k) {
    
    if( k == 0 ) {
      //this is our first graph and it is special (to define axis min,max)
      ((TGraph*)allgraphs->At(k))->SetMinimum(ymin);
      ((TGraph*)allgraphs->At(k))->SetMaximum(ymax);
      ((TGraph*)allgraphs->At(k))->Draw("AL");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLimits(xmin, xmax);

      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitle("log_{10} #nu [Hz]");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->CenterTitle(true);
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetTitleFont(42);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitle("Log_{10} #nuF(#nu) [erg cm^{-2}s^{-1}]");
      ((TGraph*)allgraphs->At(k))->GetYaxis()->CenterTitle(true);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleOffset(1.24);
      ((TGraph*)allgraphs->At(k))->GetYaxis()->SetTitleFont(42);

      //set the color options
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
      ((TGraph*)allgraphs->At(k))->Draw("AL"); 

    }
    else {
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
      ((TGraph*)allgraphs->At(k))->Draw("P"); 
    }
    
  }

  graphT4 = ((TGraph*)allgraphs->At(1));

  int npoints = graphT4->GetN();
    
  std::vector<double> v_freq;
  std::vector<double> v_energy;
  std::vector<double> v_eGamma;
    
  double Ddoppler = 20.0;
  double theta = 45.0 * deg2rad;
    
  double K1 = 0.3187 * 1.0E18 / ( 10.0 * ( 1.0 - cos( theta )) ); //eV2
  double K2 = 0.0159 * 1.0E18; //eV2

  std::cout << "K1 " << K1 << " K2 " << K2 << std::endl;
  
  double K  = K1;
    
  for(int i=0; i < npoints; ++i) {
    
    double x1 (0.0);
    double y1 (0.0);
    
    int code = graphT4->GetPoint(i, x1, y1);
    
    if ( code > 0 ) {
      
      double nuHz = pow( 10.0, x1 );
      double eEv = nuHz * hplanck;
      double eGamma = K * Ddoppler * Ddoppler / ( eEv ); 

      v_freq.push_back( nuHz ); //Hz
      v_energy.push_back( eEv ); //eV
      v_eGamma.push_back( eGamma ); //eV
              
      double eGammaHz = eGamma / hplanck;
            
      std::cout << i << " " << nuHz << " " << eEv << " -> " 
                << eGamma << " [eV] " 
                << (eGamma / 1.0E9) << " [GeV] " 
                << eGammaHz << " Hz " << std::endl;
      

    }
    
  }
  
}

