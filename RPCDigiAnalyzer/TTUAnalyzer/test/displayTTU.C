// $Id: $
// Include files 
void makeplots(const char *fname , int runid ){

  char runID[30];
  char outname[80];
  const int maxBx = 7;
  const int maxWh = 5;
  
  int k = 0;
  TH2D * wheelmapdis[ maxBx * maxWh ];
  
  gStyle->SetPalette(1);	
  
  TFile * f1 = TFile::Open(fname,"READ");
  
  sprintf(runID,"Run id=%d",runid);
    
  for( int wheel = -2; wheel < 3; ++wheel ) {
    
    for( int bx = -3; bx < 4; ++bx ) {
      
      char _hbxname[50];
      sprintf(_hbxname,"WheelMapDist.W%d.BX.%d", wheel, bx);
      
      wheelmapdis[k] = new TH2D(_hbxname,
                                "This is the total distribution for wheel maps",
                                13,0,13,6,1,7);
      int mxlayers = 7;
      
      for(int i=0; i < 12; ++i) {
        
        char hname[50];
        sprintf(hname,"LayerHits.wheel.%d.sec.%d.BX.%d",wheel,i,bx);
        
        TH1D * h1 = (TH1D*)gDirectory->FindObjectAny(hname);
        
        if ( ! h1 ) continue;
        
        for(int j=1; j < mxlayers; ++j) {
          int _val = h1->GetBinContent(j);
          int _layerpos = (j); //... inverted so 0 is 6 from top to down
          wheelmapdis[k]->SetBinContent(i+1, _layerpos, _val);
          
        }
        
      }
            
      ++k;
      
    }
    
    
  }
  
  
  
  TCanvas * c1[7];
  
  TCanvas * allmaps = new TCanvas( "allMaps" ,"Wheel map distribution for digis per BX",200,100,850,700);
  allmaps->SetFillColor(10);
  allMaps->Divide(7,5);
  allMaps->Draw();
  
  gStyle->SetOptStat(0);
  
  for( int bx = 0; bx < 7; ++bx ) {
    
    char ff[30];
    sprintf(ff,"c.%d",bx);
    
    c1[bx] = new TCanvas( ff ,"Wheel map distribution for digis per BX",238,143,583,415);
    c1[bx]->SetFillColor(10);
    c1[bx]->SetFrameFillColor(10);
    c1[bx]->Draw();
    c1[bx]->cd();
    c1[bx]->SetGridx();
    c1[bx]->SetGridy();
    
    wheelmapdis[bx]->GetXaxis()->SetTitle("Sector");
    wheelmapdis[bx]->GetYaxis()->SetTitle("Layer");
    wheelmapdis[bx]->Draw("COLZ");
    
    char bxid[10];
    sprintf(bxid,"BX=%d",bx-3);
    TLatex * tex = new TLatex(2.16386,1.762605,bxid);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(2.16386,2.22479,"Wheel 0");
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(1.311111,3.291801,runID);
    tex->SetLineWidth(2);
    tex->Draw();
    c1[bx]->Modified();        
    
    sprintf(outname,"results/WheelMapDist.W0.BX.%d.%d.eps", bx-3, runid);
    c1[bx]->Print(outname);
      
  }

  int ix(1);
  int iy(1);
  
  for( int i=0; i < 35; ++i) {
    
    //std::cout << i << " " << ix << " " << iy << " ";
    
    if ( fmod(double(i+1),double(7)) == 0 ) {
      ix =1;
      iy+=1;
      //std::cout << '\n';
    }
    allmaps->cd(i+1);
    wheelmapdis[i]->Draw("COLZ");
    
  }
  
  allmaps->cd();
  
  TH2D *wheelbxdist = new TH2D("Wheel.BX.distribution",
                               "Distribution of BX accross the wheels",
                               7, -4, 4, 7, -3, 3);
  
  for( int wh = -2; wh < 3; ++wh ) {
    
    char hname[50];
    sprintf(hname,"Avg.BX.Event.Wheel.%d",wh);
    
    TH1D * h1 = (TH1D*)gDirectory->FindObjectAny(hname);
    
    if ( ! h1 ) continue;
    
    for( int xbin = 1; xbin <= h1->GetNbinsX(); ++xbin) {
      int _val = h1->GetBinContent(xbin);
      wheelbxdist->SetBinContent( xbin , wh+4 , _val );
    }
    
  }
  
  TCanvas * cc = new TCanvas( "CC" ,"Wheel BX distribution",238,143,583,415);
  cc->SetFillColor(10);
  cc->SetFrameFillColor(10);
  cc->Draw();
  cc->cd();
  cc->SetGridx();
  
  wheelbxdist->GetXaxis()->SetTitle("BX");
  wheelbxdist->GetYaxis()->SetTitle("Wheel");
  wheelbxdist->Draw("COLZ");

  TLatex *tex = new TLatex(1.311111,3.291801,runID);
  tex->SetLineWidth(2);
  tex->Draw();
  cc->Modified();
  
  sprintf(outname,"results/Avg.BX.Event.Wheel.%d.eps",runid);
  cc->Print(outname);
    

}

