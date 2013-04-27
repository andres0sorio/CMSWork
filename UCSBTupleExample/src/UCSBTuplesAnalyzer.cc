// $Id: $
// Include files 



// local
#include "UCSBTuplesAnalyzer.h"

//-----------------------------------------------------------------------------
// Implementation file for class : UCSBTuplesAnalyzer
//
// 2008-12-20 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
UCSBTuplesAnalyzer::UCSBTuplesAnalyzer( TFile * infile , const char * option ) : 
  eventB(infile), eventV(infile) {
  
  TString Opt(option);
  TString outfile = Opt + TString("Histograms.root");
  
  fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();
  histograms = new BasicOutput(option);
  
  std::cout << "UCSBTuplesAnalyzer: initialized" << std::endl;
  
}

UCSBTuplesAnalyzer::UCSBTuplesAnalyzer( TChain * inchainB, 
                                        TChain * inchainV,
                                        const char * option ) :
  eventB(inchainB), eventV(inchainV) {
  
  TString Opt(option);
  TString outfile = Opt + TString("-Histograms.root");
  
  fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();
  histograms = new BasicOutput(option);
  
  std::cout << "UCSBTuplesAnalyzer: initialized" << std::endl;
  
}

//=============================================================================
// Destructor
//=============================================================================
UCSBTuplesAnalyzer::~UCSBTuplesAnalyzer() {

  fout->Write();
  fout->Close();
  fout->Delete();
  
} 

//=============================================================================
void UCSBTuplesAnalyzer::Loop()
{
  
  /*       
           To read only selected branches, Insert statements like:
           METHOD1:
           fChain->SetBranchStatus("*",0);  // disable all branches
           fChain->SetBranchStatus("branchname",1);  // activate branchname
           METHOD2: replace line
           fChain->GetEntry(jentry);       //read all branches
           by  b_branchname->GetEntry(ientry); //read only this branch
  */
  
  if (eventB::fChain == 0) return;
  
  Long64_t nentries = eventB::fChain->GetEntriesFast();
  Long64_t nbytes   = 0;
  Long64_t nb       = 0;
  
  //nentries = 1000;

  bool IsSelected (false);
  int maxjets(0);
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    IsSelected = false;
    
    Long64_t ientry = eventB::LoadTree(jentry);
    
    if (ientry < 0) break;
    
    nb = eventB::fChain->GetEntry(jentry);   nbytes += nb;
    
    histograms->njets->Fill(Njets);
    
    maxjets = int(Njets);
    if ( maxjets <= 1) continue;

    findOrder();
    
    IsSelected = applyPreselection();
    if ( ! IsSelected ) continue;
    
    for(int i=0; i < maxjets; ++i)
      histograms->jets_energy->Fill( (*jets_Energy)[i] );

    int pos = jet_order[0];
    histograms->jets_phieta->Fill( (*jets_eta)[pos],(*jets_phi)[pos] );
    histograms->jets_high_energy->Fill( (*jets_Energy)[pos] );
    
    pos = jet_order[1];
    histograms->jets_phieta->Fill( (*jets_eta)[pos],(*jets_phi)[pos] );
    histograms->jets_high_energy->Fill( (*jets_Energy)[pos] );
    
    
    

    //IsSelected = applySelection();
    //if ( ! IsSelected ) continue;
    
    
  }
  
   
}

bool UCSBTuplesAnalyzer::applyPreselection()
{
  
  return true;
  
}

void UCSBTuplesAnalyzer::findOrder()
{
  
  jet_order.clear();
  jet_energy_cp.clear();
  
  int maxjets = int(Njets);
      
  jet_energy_cp.assign((*jets_Energy).begin(),(*jets_Energy).end());
  sort( jet_energy_cp.begin(),jet_energy_cp.end() );
  reverse( jet_energy_cp.begin(),jet_energy_cp.end() );
  
  //...
  
  for( int k=0; k < 2; k++) {
    for ( int i=0; i < maxjets; ++i) {
      if ( jet_energy_cp[k] == (*jets_Energy)[i] )
        jet_order.push_back(i);
    }
  }
  
  //...
     
}
