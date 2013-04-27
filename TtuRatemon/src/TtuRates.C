#include "TtuRates.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

TtuRates::TtuRates( TFile * file0 )
{

  m_iomode = 0;
  
  file0->cd();
  TTree * tree = (TTree*)gDirectory->Get("TtuRates");
  Init(tree);

  m_plots = new HistoRates();
  
  m_canvasW = new TCanvas("WheelRates","Wheel rates", 100, 50, 400, 315);
  m_canvasW->Divide(3,4);
  m_canvasW->SetFillColor(10);
  m_canvasW->Draw();

  m_canvasS = new TCanvas("SectorRates","Sector rates", 300, 50, 800, 715);
  m_canvasS->Divide(3,4);
  m_canvasS->SetFillColor(10);
  m_canvasS->Draw();

  m_canvasS1 = new TCanvas("WheelRatesSumarry","Wheel rates", 150, 300, 400, 460);
  m_canvasS1->SetFillColor(10);
  m_canvasS1->Draw();

  m_canvasP1 = new TCanvas("SectorRateSummary","Wheel rates", 150, 300, 400, 460);
  m_canvasP1->SetFillColor(10);
  m_canvasP1->Draw();

  m_factor = (1.0/2.0);
  m_factor = 1.0;

  m_debug = false;
      
}

TtuRates::TtuRates( const char * option )
{
  
  m_option = std::string(option);
  m_output = new TFile(option,"RECREATE");
  fChain   = new TTree("TtuRates","Ttu rates");
  
  Book();
  
  hasStop = false;

  m_iomode = 1;

  m_factor = (1.0/2.0);
      
}

TtuRates::~TtuRates()
{
  if( m_iomode == 1 ) 
  {
    m_output->Write();
    m_output->Close();
  }
  

  if (!fChain) return;
  delete fChain->GetCurrentFile();
  
}

Int_t TtuRates::GetEntry(Long64_t entry)
{
  
  if (!fChain) return 0;
  return fChain->GetEntry(entry);

}

Long64_t TtuRates::LoadTree(Long64_t entry)
{
  
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;

}

void TtuRates::Init(TTree *tree)
{

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("Run", &Run, &b_Run);
  fChain->SetBranchAddress("Lumi", &Lumi, &b_Lumi);
  fChain->SetBranchAddress("Orbit", &Orbit, &b_Orbit);
  fChain->SetBranchAddress("Time", &Time, &b_Time);
  fChain->SetBranchAddress("nWheels", &nWheels, &b_nWheels);
  fChain->SetBranchAddress("RateByWheel", RateByWheel, &b_RateByWheel);
  fChain->SetBranchAddress("nSectors", &nSectors, &b_nSectors);
  fChain->SetBranchAddress("RateBySectorWM2", RateBySectorWM2, &b_RateBySectorWM2);
  fChain->SetBranchAddress("RateBySectorWM1", RateBySectorWM1, &b_RateBySectorWM1);
  fChain->SetBranchAddress("RateBySectorW00", RateBySectorW00, &b_RateBySectorW00);
  fChain->SetBranchAddress("RateBySectorWP1", RateBySectorWP1, &b_RateBySectorWP1);
  fChain->SetBranchAddress("RateBySectorWP2", RateBySectorWP2, &b_RateBySectorWP2);
  Notify();
}

Bool_t TtuRates::Notify()
{
  return kTRUE;
}

void TtuRates::Show(Long64_t entry)
{
  if (!fChain) return;
  fChain->Show(entry);
}

void TtuRates::Loop()
{
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();

  //std::cout << " total " << nentries << std::endl;

  int counter = 0;
      
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    
    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    m_plots->addTime( Time );
  
    for( int i=0; i < 5; ++i) 
    {
      m_plots->addwheelRate( i, RateByWheel[i]);
    }    

    m_plots->addsectorRates( RateBySectorWM2,
                             RateBySectorWM1,
                             RateBySectorW00,
                             RateBySectorWP1,
                             RateBySectorWP2 );
    
    if ( m_debug ) 
      std::cout << jentry << " time: " << Time << '\t';
    else
      std::cout << jentry << '\t' << Time << '\t';
    
    float total=0.0;
    for(int i=0; i < 5; ++i)
    {
      if(m_debug) 
	std::cout  << "y: " << RateByWheel[i] << '\t';
      else
	std::cout  << RateByWheel[i] << '\t';
      total += RateByWheel[i];
    }
    
    if (m_debug)
      std::cout << " tot: " << total << std::endl;
    else 
      std::cout << total << std::endl;

    //if ( RateByWheel[0] == 0 )
    //  counter+=1;
    
    if (counter >= 5 )
      break;
        
  }

  
  TCanvas *fCanvas = m_canvasW;
  
  fCanvas->SetFillColor(10);
  fCanvas->Update();
  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetGridy();

  
  
  m_plots->DrawWheelRates( fCanvas );

  
  fCanvas = m_canvasS;
  fCanvas->SetFillColor(10);
  
  m_plots->DrawSectorRates( fCanvas , false);
    
  fCanvas->cd();
  fCanvas->Update();

  fCanvas = m_canvasS1;
  
  m_plots->DrawSectorSummary( fCanvas);

  fCanvas->cd();
  fCanvas->Update();

  fCanvas = m_canvasP1;
  
  m_plots->DrawSectorPie( fCanvas);

  fCanvas->cd();
  fCanvas->Update();
  

}

void TtuRates::Fill( TrigRates * p_rates)
{
  
  Run      = 123400;
  Lumi     = 50;
  Orbit    = 1000;

  nWheels  = 5;
  nSectors = 12;
  
  //read and fill the ntuple

  std::vector<int>::iterator itrdata; //DATA == COUNTS
  
  int wheel=0;
  int segment=0;
  
  //std::cout << '\n';
  //std::cout << p_rates->rates.size() << std::endl;
  //the order in which the rates are read is: W+1, W+2, W00, W-1, W-2
 
  for( itrdata = p_rates->rates.begin(); itrdata != p_rates->rates.end(); ++itrdata)
  {

    if ( (*itrdata) < 0 ) 
    {
      hasStop = true;
      break;
    }
    
    //std::cout << wheel << " " << segment << " " << (*itrdata) << std::endl;
    
    if ( segment > 12 ) 
    {
      segment = 0;
      ++wheel;
    }
    
    if ( segment == 0 ) {
      RateByWheel[wheel] = (*itrdata) * m_factor;
      ++segment;
      continue;
    }
    else if ( wheel == 4 ) //W-2
    {
      RateBySectorWM2[segment-1] = (*itrdata)* m_factor;
    }
    else if ( wheel == 3 ) //W-1
    {
      RateBySectorWM1[segment-1] = (*itrdata)* m_factor;
    }
    else if ( wheel == 2 ) //W00
    {
      RateBySectorW00[segment-1] = (*itrdata)* m_factor;
    }
    else if ( wheel == 0 ) //W+1
    {
      RateBySectorWP1[segment-1] = (*itrdata)* m_factor;
    }
    else if ( wheel == 1 ) //W+2
    {
      RateBySectorWP2[segment-1] = (*itrdata)* m_factor;
    }
    else 
    {
      std::cout << "There is a problem!" << std::endl;
    }
    ++segment;
  }

  if( !hasStop )
    fChain->Fill();
  
}

void TtuRates::Book()
{
  
  m_output->cd();
  
  // Set branch addresses and branch pointers
  
  fChain->Branch("Run"             , &Run             , "Run/I");
  fChain->Branch("Lumi"            , &Lumi            , "Lumi/I");
  fChain->Branch("Orbit"           , &Orbit           , "Orbit/l");
  fChain->Branch("Time"            , &Time            , "Time/l");
  fChain->Branch("nWheels"         , &nWheels         , "nWheels/I");
  fChain->Branch("RateByWheel"     , RateByWheel      , "RateByWheel[nWheels]/F");
  fChain->Branch("nSectors"        , &nSectors        , "nSectors/I");
  fChain->Branch("RateBySectorWM2" , RateBySectorWM2  , "RateBySectorWM2[nSectors]/F");
  fChain->Branch("RateBySectorWM1" , RateBySectorWM1  , "RateBySectorWM1[nSectors]/F");
  fChain->Branch("RateBySectorW00" , RateBySectorW00  , "RateBySectorW00[nSectors]/F");
  fChain->Branch("RateBySectorWP1" , RateBySectorWP1  , "RateBySectorWP1[nSectors]/F");
  fChain->Branch("RateBySectorWP2" , RateBySectorWP2  , "RateBySectorWP2[nSectors]/F");

}

