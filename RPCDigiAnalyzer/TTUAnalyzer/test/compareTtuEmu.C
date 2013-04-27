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
  
  TCanvas * allmaps = new TCanvas( "allMaps" ,"Wheel map distribution for digis per BX",200,100,850,700);
  allmaps->SetFillColor(10);
  allmaps->Divide(7,5);
  allmaps->Draw();
  
  //allmaps->SetBorderMode(0);
  //allmaps->SetBorderSize(2);
  //allmaps->SetRightMargin(0.1639344);
  //allmaps->SetFrameFillColor(19);
  //allmaps->SetFrameLineColor(17);
  //allmaps->SetFrameBorderMode(0);
  
  TCanvas * bx0maps[5];

  for(int k=0; k<5; ++k) 
  {
    char hbxname[50];
    sprintf(hbxname,"bx0.W.maps.%d",k);
    bx0maps[k]= new TCanvas( hbxname ,"Wheel map distribution for digis per BX",200,100,550,400);
    bx0maps[k]->SetFillColor(10);
    bx0maps[k]->SetBorderMode(0);
    bx0maps[k]->SetBorderSize(2);
    bx0maps[k]->SetRightMargin(0.1639344);
    bx0maps[k]->SetFrameFillColor(19);
    bx0maps[k]->SetFrameLineColor(17);
    bx0maps[k]->SetFrameBorderMode(0);
  
  }
  
  gStyle->SetOptStat(0);
  
  int ix(1);
  int iy(1);

  int atBx0[5]= {3,10,17,24,31};

  int k=0;
      
  for( int i=0; i < 35; ++i) {
    
    if ( fmod(double(i+1),double(7)) == 0 ) {
      ix =1;
      iy+=1;
    }
    
    allmaps->cd(i+1);
    
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    gPad->SetRightMargin(0.1639344);
    gPad->SetFrameFillColor(10);
    gPad->SetFrameLineColor(17);
    gPad->SetFrameBorderMode(0);
    gPad->SetFillColor(10);
    
    wheelmapdis[i]->GetXaxis()->SetLabelFont(42);
    wheelmapdis[i]->GetXaxis()->SetLabelOffset(0.02);
    wheelmapdis[i]->GetXaxis()->SetLabelSize(0.07);
    wheelmapdis[i]->GetYaxis()->SetLabelFont(42);
    wheelmapdis[i]->GetYaxis()->SetLabelSize(0.07);
    wheelmapdis[i]->SetTitle("");
    wheelmapdis[i]->Draw("COLZ");

    if ( i == atBx0[k] ) 
    {
      bx0maps[k]->cd();
      wheelmapdis[i]->Draw("COLZ");
      ++k;
    }
    
    
  }
  
  allmaps->cd();
  
  
}


