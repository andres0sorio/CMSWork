// $Id: $
// Include files 



// local
#include "Histograms.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Histograms
//
// 2012-09-21 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Histograms::Histograms( const char * outfile ) {

  m_output = new TFile( outfile , "RECREATE");
  
  m_output->cd();
  
  h_1DHistograms["Px"]  = new TH1F("Px","Generated kinematics",100, -100.0, 100.0);
  h_1DHistograms["Py"]  = new TH1F("Py","Generated kinematics",100, -100.0, 100.0);
  h_1DHistograms["Pz"]  = new TH1F("Pz","Generated kinematics",100, -100.0, 100.0);
  h_1DHistograms["E"]   = new TH1F("EE","Generated kinematics",100, 0.0, 1000.0);

  h_1DHistograms["topMass1"]  = new TH1F("topMass1","Generated top masses",100, 0.0, 350.0);
  h_1DHistograms["topMass2"]  = new TH1F("topMass2","Generated top masses",100, 0.0, 350.0);
  h_1DHistograms["topMassRec1"]  = new TH1F("topMassRe1","Combined 4momenta inv. mass",100, 0.0, 350.0);
  h_1DHistograms["topMassRec2"]  = new TH1F("topMassRe2","Combined 4momenta inv. mass",100, 0.0, 350.0);
  
  h_2DHistograms["PtEta_bquark"]   = new TH2F("PtEta_bquark","Pt vs #eta - bquark", 50, -4.5, 4.5, 100, 0.0, 150.0);
  h_2DHistograms["PtEta_abquark"]  = new TH2F("PtEta_abquark","Pt vs #eta - ~b quark", 50, -4.5, 4.5, 100, 0.0, 150.0);
  h_2DHistograms["PtEta_uquark"]   = new TH2F("PtEta_uquark","Pt vs #eta - u quark", 50, -4.5, 4.5, 100, 0.0, 150.0);
  h_2DHistograms["PtEta_adquark"]  = new TH2F("PtEta_adquark","Pt vs #eta - ~d quark", 50, -4.5, 4.5, 100, 0.0, 150.0);
  h_2DHistograms["Eta_bu_quark"]   = new TH2F("Eta_bu_quarks","#eta - b vs u", 50, -4.5, 4.5, 50, -4.5, 4.5);
  h_2DHistograms["Pt_bu_quark"]    = new TH2F("Pt_bu_quarks","Pt - b vs u", 100, 0.0, 150.0, 100, 0.0, 150.0);

  h_ProfileHistograms["Eta_bu_quark_prof"] = new TProfile("Eta_bu_quark_prof", 
                                                          "#eta Profile: #eta - b vs u", 50, -4.5, 4.5, -4.5, 4.5);
  
  h_ProfileHistograms["Eta_bd_quark_prof"] = new TProfile("Eta_bd_quark_prof", 
                                                          "#eta Profile: b vs ~d", 50, -4.5, 4.5, -4.5, 4.5);
  
  
  h_ProfileHistograms["Pt_bu_quark_prof"] = new TProfile("Pt_bu_quark_prof", 
                                                          "Pt Profile: b vs u", 100, 0.0, 150.0, 0, 150.0);


   h_ProfileHistograms["Pt_bd_quark_prof"] = new TProfile("Pt_bd_quark_prof", 
                                                          "Pt Profile: b vs ~d", 100, 0.0, 150.0, 0, 150.0);
   


}
//=============================================================================
// Destructor
//=============================================================================
Histograms::~Histograms() {
  
  
  m_output->Write();
  m_output->Close();

} 

//=============================================================================
void Histograms::SetOptions() {

  std::map<std::string,TH1F*>::iterator th1Itr;
  std::map<std::string,TH2F*>::iterator th2Itr;
  std::map<std::string,TProfile*>::iterator profileItr;

  for ( th1Itr = h_1DHistograms.begin(); th1Itr != h_1DHistograms.end(); ++th1Itr ) {
    
    (*th1Itr).second->GetXaxis()->CenterTitle(true);
    (*th1Itr).second->GetYaxis()->CenterTitle(true);
    

  }

  for ( th2Itr = h_2DHistograms.begin(); th2Itr != h_2DHistograms.end(); ++th2Itr ) {

    (*th2Itr).second->GetXaxis()->CenterTitle(true);
    (*th2Itr).second->GetYaxis()->CenterTitle(true);
    
  }

  for ( profileItr = h_ProfileHistograms.begin(); profileItr != h_ProfileHistograms.end(); ++profileItr) {

    (*profileItr).second->GetXaxis()->CenterTitle(true);
    (*profileItr).second->GetYaxis()->CenterTitle(true);
    
  }

  h_1DHistograms["Px"]->GetXaxis()->SetTitle("Px [GeV/c]");

  h_1DHistograms["Py"]->GetXaxis()->SetTitle("Py [GeV/c]");
  h_1DHistograms["Pz"]->GetXaxis()->SetTitle("Pz [GeV/c]");
  h_1DHistograms["E"]->GetXaxis()->SetTitle("E [GeV/c]");

  h_1DHistograms["topMass1"]->GetXaxis()->SetTitle("Mass [GeV/c2]"); 
  h_1DHistograms["topMass2"]->GetXaxis()->SetTitle("Mass [GeV/c2]"); 
  h_1DHistograms["topMassRec1"]->GetXaxis()->SetTitle("Mass [GeV/c2]");  
  h_1DHistograms["topMassRec2"]->GetXaxis()->SetTitle("Mass [GeV/c2]");  
  
  h_2DHistograms["PtEta_bquark"]->GetXaxis()->SetTitle("#eta");  
  h_2DHistograms["PtEta_abquark"]->GetXaxis()->SetTitle("#eta"); 
  h_2DHistograms["PtEta_uquark"]->GetXaxis()->SetTitle("#eta");
  h_2DHistograms["PtEta_adquark"]->GetXaxis()->SetTitle("#eta"); 
  h_2DHistograms["Eta_bu_quark"]->GetXaxis()->SetTitle("#eta"); 
  h_2DHistograms["Pt_bu_quark"]->GetXaxis()->SetTitle("Pt [GeV/c]");  

  h_2DHistograms["PtEta_bquark"]->GetYaxis()->SetTitle("Pt [GeV/c]");  
  h_2DHistograms["PtEta_abquark"]->GetYaxis()->SetTitle("Pt [GeV/c]"); 
  h_2DHistograms["PtEta_uquark"]->GetYaxis()->SetTitle("Pt [GeV/c]");
  h_2DHistograms["PtEta_adquark"]->GetYaxis()->SetTitle("Pt [GeV/c]"); 
  h_2DHistograms["Eta_bu_quark"]->GetYaxis()->SetTitle("#eta"); 
  h_2DHistograms["Pt_bu_quark"]->GetYaxis()->SetTitle("Pt [GeV/c]");  
  
  
  h_ProfileHistograms["Eta_bu_quark_prof"]->GetXaxis()->SetTitle("#eta");  
  h_ProfileHistograms["Eta_bd_quark_prof"]->GetXaxis()->SetTitle("#eta");  
  h_ProfileHistograms["Pt_bu_quark_prof"]->GetXaxis()->SetTitle("Pt [GeV/c]"); 
  h_ProfileHistograms["Pt_bd_quark_prof"]->GetXaxis()->SetTitle("Pt [GeV/c]");  

  h_ProfileHistograms["Eta_bu_quark_prof"]->GetYaxis()->SetTitle("#eta");  
  h_ProfileHistograms["Eta_bd_quark_prof"]->GetYaxis()->SetTitle("#eta");  
  h_ProfileHistograms["Pt_bu_quark_prof"]->GetYaxis()->SetTitle("Pt [GeV/c]"); 
  h_ProfileHistograms["Pt_bd_quark_prof"]->GetYaxis()->SetTitle("Pt [GeV/c]");  

} 
