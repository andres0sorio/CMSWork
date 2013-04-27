// $Id: $
// Include files 
void makeplots(const char *fname , int runid ){

  gStyle->SetPalette(1);	
  gStyle->SetOptStat(0);
  
  TCanvas *wheelsOcc =  new TCanvas( "wheelsOcc" ,"Wheels Occupancy", 80,52,970,728);
  wheelsOcc->SetFillColor(10);
  wheelsOcc->SetBorderMode(0);

  TCanvas *wheelBx =  new TCanvas( "wheelBx" ,"Wheel BX distribution", 100,30,300,700);
  wheelBx->SetFillColor(10);
  wheelBx->SetBorderMode(0);  
  wheelBx->Divide(1,5);
  wheelBx->Draw();

  TCanvas *wheelBxSector =  new TCanvas( "wheelBxSector" ,"Wheel BX distribution in all sectors", 350,30,350,700);
  wheelBxSector->SetFillColor(10);
  wheelBxSector->SetBorderMode(0);  
  wheelBxSector->Divide(1,5);
  wheelBxSector->Draw();
    
  TPad *wheelPads[5];
  
  wheelPads[0] = new TPad("p1", "",0.33 , 0.66, 0.68  ,0.99);
  wheelPads[1] = new TPad("p2", "",0.01 , 0.33, 0.37  ,0.66);
  wheelPads[2] = new TPad("p3", "",0.64 , 0.33, 0.99  ,0.66);
  wheelPads[3] = new TPad("p4", "",0.16 , 0.01, 0.5   ,0.35);
  wheelPads[4] = new TPad("p5", "",0.50 , 0.01, 0.87  ,0.35);
  
  wheelsOcc->cd();
  
  for(int i=0; i<5; ++i) {
    wheelPads[i]->SetFillColor(10);
    wheelPads[i]->SetFrameFillColor(10);
    wheelPads[i]->SetLogz();
    wheelPads[i]->SetFrameLineColor(0);
    wheelPads[i]->SetRightMargin(0.14);
    wheelPads[i]->Draw();
  }
  
  char runID[30];
  sprintf(runID,"Run id=%d",runid);
  
  char outname[80];
  
  TFile * f1 = new TFile(fname,"READ");
  f1->cd("DQMData/RPC/RecHits/SummaryHistograms/");
  
  int WhId[5] = { 0 , -1 , 1, -2, 2 };
  
  int k = 0;
  char runIdChar[20];
  sprintf(runIdChar,"%d",runid );
  
  TH2D * wheelmapdis[5];
  TLatex * tex;
  TPaveText *pt;


  //... find the relative occupancy factors
  
  int curr_max = 0;
  for( int wh = -2; wh < 3; ++wh ) {
    
    char hname[50];
    sprintf(hname,"OccupancyXY_Wheel_%d",WhId[wh+2]);
    
    f1->cd("DQMData/RPC/RecHits/SummaryHistograms/");
    TH2D * h1 = (TH2D*)gDirectory->FindObjectAny(hname);
    
    if ( ! h1 ) continue;
    int max =  h1->GetMaximum();
    if ( max >= curr_max ) curr_max = max;
    
  }
  
  std::cout << curr_max << std::endl;
  
  for( int wh = -2; wh < 3; ++wh ) {
    
    char hname[50];
    sprintf(hname,"OccupancyXY_Wheel_%d",WhId[wh+2]);
    
    f1->cd("DQMData/RPC/RecHits/SummaryHistograms/");
    TH2D * h1 = (TH2D*)gDirectory->FindObjectAny(hname);

    if ( ! h1 ) continue;
    
    wheelsOcc->cd();
    wheelPads[wh+2]->cd();
    
    if ( (wh+2) != 0 ) {
      
      h1->GetXaxis()->SetAxisColor(0);
      h1->GetXaxis()->SetLabelColor(0);
      h1->GetYaxis()->SetAxisColor(0);
      h1->GetYaxis()->SetLabelColor(0);
      
    }
    
    sprintf(hname,"Wheel %d",WhId[wh+2]);
    h1->SetTitle(hname);
    
    h1->Draw("COLZ");
    
    wheelPads[wh+2]->Update();
    
    TPaletteAxis *palette = (TPaletteAxis*)h1->GetListOfFunctions()->FindObject("palette");
        
    palette->SetLabelSize(0.06);
    palette->SetLabelOffset(0.00);

    
    //int max = h1->GetMaximum();
    //float scaleFactor =  curr_max / (max+0.0);
    //h1->Scale ( scaleFactor );
    
    wheelsOcc->Update();
    
    pt = new TPaveText(0.4236311,0.4709271,0.5706051,0.5523265,"blNDC");
    pt->SetName("title");
    pt->SetBorderSize(0);
    pt->SetFillColor(10);
    pt->SetTextFont(42);
    pt->SetTextSize(0.08);
    text = pt->AddText(hname);
    pt->Draw();
    p1->Modified();
    
    //...............
    
    sprintf(hname,"BxDistribution_Wheel_%d",WhId[wh+2]);
    TH1D * h2 = (TH1D*)gDirectory->FindObjectAny(hname);
    
    if ( ! h2 ) continue;
    
    wheelBx->cd(wh+3);
    gPad->SetFrameFillColor(10);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(1);
    gPad->SetGridx();
    h2->SetFillColor(kBlue-6);
    h2->GetXaxis()->SetTitle("BX");
    h2->GetXaxis()->SetLabelFont(42);
    h2->GetXaxis()->SetLabelSize(0.09);
    h2->GetXaxis()->SetTitleSize(0.07);
    h2->GetXaxis()->SetTitleOffset(0.4);
    h2->GetXaxis()->SetTitleFont(42);
    h2->GetYaxis()->SetLabelFont(42);
    h2->GetYaxis()->SetLabelSize(0.09);
    h2->GetYaxis()->SetLabelColor(1);
    
    sprintf(hname,"Wheel %d",WhId[wh+2]);
    h2->SetTitle(hname);
    h2->Draw();

    pt = new TPaveText(0.1546392,0.6694215,0.371134,0.8429752,"blNDC");
    pt->SetName("title");
    pt->SetBorderSize(1);
    pt->SetFillStyle(0);
    pt->SetTextFont(42);
    pt->SetTextSize(0.1157407);
    pt->AddText("W");
    pt->Draw();
    
    gPad->Modified();
    
    if (wh <= -2 ) {
      
      tex = new TLatex(4.08508,3075241,"Run:");
      tex->SetTextSize(0.11);
      tex->SetTextColor(1);
      tex->SetLineWidth(2);
      tex->Draw();
      gPad->Modified();
      
      tex = new TLatex(4.1885,2541814,runIdChar);
      tex->SetTextSize(0.1138767);
      tex->SetLineWidth(2);
      tex->Draw();
      gPad->Modified();
      
    }
    
    
    //...............
    sprintf(hname,"bx_map_%d",WhId[wh+2]);
    wheelmapdis[wh+2] = new TH2D(hname, "Bx distribution in all Sectors",
                                 11, -5, 5,  13, 0, 13);
    
    char path[100];
    sprintf(path,"DQMData/RPC/RecHits/Barrel/Wheel_%d/SummaryBySectors",WhId[wh+2]);
    f1->cd(path);
    
    for( int sector = 1; sector < 13; ++sector ) {
      
      char hbxname[50];
      sprintf(hbxname,"BxDistribution_Wheel_%d_Sector_%d",WhId[wh+2], sector);
      
      TH1D * h3 = (TH1D*)gDirectory->FindObjectAny(hbxname);
      
      if ( ! h3 ) continue;
      
      int maxbx = h3->GetNbinsX();
      
      for(int j=1; j < maxbx; ++j) {
        int _val = h3->GetBinContent(j);
        int _bxpos = j;
        wheelmapdis[wh+2]->SetBinContent(_bxpos, sector, _val);
      }
    
    }
    
    wheelBxSector->cd(wh+3);
   
    gPad->SetFrameFillColor(10);
    
    sprintf(hname,"Wheel %d",WhId[wh+2]);
    wheelmapdis[wh+2]->SetTitle(hname);
    wheelmapdis[wh+2]->GetXaxis()->SetTitle("BX   ");
    wheelmapdis[wh+2]->GetXaxis()->SetLabelFont(42);
    wheelmapdis[wh+2]->GetXaxis()->SetLabelSize(0.09);
    wheelmapdis[wh+2]->GetXaxis()->SetTitleSize(0.08);
    wheelmapdis[wh+2]->GetXaxis()->SetTitleOffset(0.47);
    wheelmapdis[wh+2]->GetXaxis()->SetTitleFont(42);

    wheelmapdis[wh+2]->GetYaxis()->SetTitleColor(1);
    wheelmapdis[wh+2]->GetYaxis()->SetLabelColor(1);
    wheelmapdis[wh+2]->GetYaxis()->SetLabelSize(0.08);
    wheelmapdis[wh+2]->GetYaxis()->SetLabelOffset(0.02);
    wheelmapdis[wh+2]->GetYaxis()->SetTitle("Sectors");
    wheelmapdis[wh+2]->GetYaxis()->SetTitleSize(0.08);
    wheelmapdis[wh+2]->GetYaxis()->SetTitleOffset(0.65);
    wheelmapdis[wh+2]->Draw("COLZ");
    
    pt = new TPaveText(0.122508,0.8240741,0.3259998,0.989418,"blNDC");
    pt->SetName("title");
    pt->SetBorderSize(1);
    pt->SetFillColor(10);
    pt->SetFillStyle(1);
    pt->SetTextFont(42);
    pt->SetTextSize(0.1157407);
    pt->AddText("W");
    pt->Draw();
    
    tex = new TLatex(3.642436,11.313,"Run:");
    tex->SetTextSize(0.1171352);
    tex->SetLineWidth(2);
    tex->Draw();
    tex = new TLatex(3.721334,9.545515, runIdChar );
    tex->SetTextSize(0.1171352);
    tex->SetLineWidth(2);
    tex->Draw();
    
    gPad->Modified();
    
  }
  
  
  sprintf(runIdChar,"Run: %d", runid);
    
  wheelsOcc->cd();
  tex = new TLatex(0.059,0.91,runIdChar);
  tex->SetTextSize(0.03);
  tex->SetLineWidth(2);
  tex->Draw();
  wheelsOcc->Modified();
  wheelsOcc->cd();
  
  
}


