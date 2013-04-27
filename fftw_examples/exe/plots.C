// $Id: $
// Include files 

void makeplots(int datalen) {
 
  const int MAXDATA = datalen;

  double fq[MAXDATA];
  double xx[MAXDATA];
  double yy[MAXDATA];
  double xr[MAXDATA];
  double yr[MAXDATA];
  double zr[MAXDATA];
  
  TCanvas *cv = new TCanvas("c1","FFTExample",500,500,1000,500);
  cv->SetFillColor(10);
  cv->Divide(2,1);
  
  ifstream in;
  in.open("rpcdata.dat");
  
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
  TGraph *g1 = new TGraph(MAXDATA, xx, yy);
  g1->SetMinimum(0.0);
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
  greal->SetMarkerColor(kRed);
  greal->SetMarkerStyle(7);
  greal->SetMarkerSize(1);
  greal->SetLineColor(kRed);
  
  greal->Draw("AL");
  
  TGraph *gimag = new TGraph(maxpoints, fq, yr);
  gimag->SetMarkerColor(kBlue);
  gimag->SetMarkerStyle(7);
  gimag->SetMarkerSize(1);
  gimag->SetLineColor(kBlue);
  gimag->Draw("LSAME");
  
  TGraph *gmod = new TGraph(maxpoints, fq, zr);
  gmod->SetMarkerColor(1);
  gmod->SetMarkerStyle(7);
  gmod->SetMarkerSize(1);
  gmod->SetLineColor(1);
  gmod->Draw("LSAME");
  
  cv->cd();
 
}
