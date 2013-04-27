// $Id: $
// Include files 

//=============================================================================

double log_nuFnu(double *x, double *par)
{
  
  double  k     = par[0];
  double  a     = par[1];
  double  b     = par[2];
  double nup    = par[3];
  double npFnp  = par[4];
  
  //double nuFnup = (1.60E-9) * k 
  //  * pow( E1, 2.0 ) * pow(10.0, (2.0 - a)*(2.0 - a)/(4.0*b) ); // ( erg / cm^2 s)
  
  return exp( log(npFnp) - ( b * pow( log( x[0]/nup ) , 2.0 ) ) );
  
}

void plotLogParabola() 
{
  
  TCanvas * canvas = new TCanvas("Plot1", "Canvas for plot 1", 94, 262,700, 502 );
  canvas->SetFillColor(10);
  canvas->SetLogx();
  canvas->SetLogy();

  TF1 * f1 = new TF1("SEDf1", log_nuFnu, 1.0E16, 2.0E19, 5);
  
  //Fix here the parameters of your function
  double hplanck = 4.13E-15; // eV x s
  double Ep = 0.53E3; //eV
  double nup = Ep / hplanck;
  double npFnp = 1.25E-10;
  
  f1->SetParameter(0, 7.21E-2 ); // k
  f1->SetParameter(1, 2.25    ); // a
  f1->SetParameter(2, 0.45    ); // b
  f1->SetParameter(3, nup     ); // nup
  f1->SetParameter(4, npFnp   ); // nupFnup
  



  //dataPoints->Fit(f1,"R");
  
  f1->Draw("L");

  
}
