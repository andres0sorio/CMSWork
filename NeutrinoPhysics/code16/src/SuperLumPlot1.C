//-----------------------------------------------------------------------------
// ROOT Macro: execute like this:
// start ROOT
// root
// inside ROOT type:
// .L SuperLumPlot1.C
// makePlot()
//-----------------------------------------------------------------------------

// Equation 22

// Note
// first argument is the variable x ; second argument is for each parameter

double testfunction(double *x, double *par)
{
  return 0.04E-3;
}


double myfunction(double *x, double *par)
{
 
  double xx = x[0]; // Enu (our x)
  
  //parameters just as needed
  double A = par[0];
  double Enu0 = par[1];
  double alpha = par[2];
  
  double f1 = ( (0.5 - alpha) * log ( xx / Enu0 ) - 1.0 );
  double f2 = (( A*A ) / ( xx*xx )) * pow ( (xx / Enu0) , 2.0*alpha ) * log ( xx / Enu0 ) * f1;
  
  //std::cout << A << " " << Enu0 << " " << alpha << std::endl;
  //std::cout << xx << " " << f1 << " " << f2 << std::endl;
  
  return f2;

}


void makePlot() {
  
  TCanvas * canvas = new TCanvas("Plot1", "Canvas for plot 1", 94, 262,700, 502 );
  canvas->SetFillColor(10);
  canvas->SetLogx();
  canvas->SetLogy();
  
  TGraphErrors *dataPoints = new TGraphErrors();
  
  // X-axis in GeV
  
  dataPoints->SetPoint(0, 17.0, 2.48E-5);
  dataPoints->SetPoint(1, 13.9, 2.18E-5);
  dataPoints->SetPoint(2, 42.9, 2.76E-5);
  dataPoints->SetPoint(3, 0.01, 2.00E-9);
  dataPoints->SetPoint(4, 3.00, 5.10E-5);
  
  //Error for point_0 (ex,ey) - I put here for the moment the stat error
  dataPoints->SetPointError( 0, 0.0, 0.28E-5 ); 
  dataPoints->SetPointError( 1, 0.0, 0.77E-5 ); //Error for point_1
  dataPoints->SetPointError( 2, 0.0, 0.75E-5 ); //Error for point_2 ...
  dataPoints->SetPointError( 3, 0.0, 0.00000 );
  dataPoints->SetPointError( 4, 0.0, 0.29E-5 );
  
  canvas->cd();

  dataPoints->SetMarkerColor(2); // to change the color of the marker
  dataPoints->SetMarkerStyle(25); //to change the style of the marker
  
  //... now the function
  

  //TF1 * f1 = new TF1("EQ22", testfunction, 0, 45, 3);//this is just for testing
  // myfunction is the above formula, then 0 = xmin ; 50 = xmax ; 3 the number of parameters
  
  TF1 * f1 = new TF1("EQ22", myfunction, 5, 10000, 3);
  
  //Fix here the parameters of your function
  
  f1->SetParameter(0, 0.001); // A = 1.0 / 0.001
  f1->SetParameter(1, 1.0); // Enu0 = 1.0 / 1.0
  f1->SetParameter(2, 0.0); // alpha = 0.0 
  
  //Draw both
  
  dataPoints->Draw("AP");
  dataPoints->GetXaxis()->SetLimits(5.0, 10000.0);
  dataPoints->Draw("AP");
  
  canvas->Update();

  dataPoints->Fit(f1,"R");
  
  //f1->Draw("L");
  
}
