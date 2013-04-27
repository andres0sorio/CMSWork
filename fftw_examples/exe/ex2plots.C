// $Id: $
// Include files 

{
 
  double fq[100];
  double xx[100];
  double yy[100];
  double xr[100];
  double yr[100];
  double zr[100];
  
  TCanvas *cv = new TCanvas("c1","FFTExample",500,500,1000,500);
  cv->SetFillColor(10);
  cv->Divide(2,1);
  
  ifstream in;
  in.open("simdata-sinewave.dat");
  
  if(!in) {
    exit(1);
  }
  
  int i(0);
  
  while (1) {
    double x;
    double y;
    in >> x >> y;
    if (!in.good()) break;
    
    if ( i < 5 ) std::cout << x << '\t' 
                           << y << '\n';
    
    xx[i] = x;
    yy[i] = y;
    ++i;
  
  }    
  
  in.close();
  
  cv->cd(1);
  TGraph *g1 = new TGraph(100, xx, yy);
  g1->SetLineColor(2);
  g1->Draw("AL");
  cv->cd();
  
  in.open("fftwresults.dat");
  
  if(!in) {
    exit(1);
  }
  
  i = 0;
  
  while (1) {
    double x;
    double y;
    in >> x >> y;
    if (!in.good()) break;

    fq[i] = i;
    xr[i] = x;
    yr[i] = y;
    zr[i] = TMath::Sqrt( x*x + y*y );
    
    if ( x == 0.0 && y == 0.0 ) break;
    
    if ( i < 5 ) std::cout << x << '\t' 
                           << y << '\n';
    
    ++i;
  
  }    

  int maxpoints = i-1; //half complex
  
  in.close();
  
  cv->cd(2);

  TGraph *greal = new TGraph(maxpoints, fq, xr);
  greal->SetMaximum( 15);
  greal->SetMinimum(-15);
  greal->SetMarkerColor(kRed);
  greal->SetMarkerStyle(7);
  greal->SetMarkerSize(1);
  greal->Draw("AP");
  
  TGraph *gimag = new TGraph(maxpoints, fq, yr);
  gimag->SetMarkerColor(kBlue);
  gimag->SetMarkerStyle(7);
  gimag->SetMarkerSize(1);
  gimag->Draw("PSAME");
  
  TGraph *gmod = new TGraph(maxpoints, fq, zr);
  gmod->SetMarkerColor(1);
  gmod->SetMarkerStyle(7);
  gmod->SetMarkerSize(1);
  gmod->Draw("LSAME");

  cv->cd();
  
}
