// $Id: $
// Include files 



// local
#include "RootOutput.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RootOutput
//
// 2010-12-26 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RootOutput::RootOutput(const char *opt, int type ) {

  m_types[0] = std::string("treeB");
  m_types[1] = std::string("treeS");
 
  dataType = std::string(opt);

  std::string filename = std::string("higgs_decay_analisis_") 
    + dataType + std::string(".root");
  
  m_fileout = new TFile( filename.c_str(),"RECREATE");
  
  m_fileout->cd();

  h_mumuInv      = new TH1F(( std::string("mumuInv")+dataType).c_str(), 
                            "mumu Invariant mass", 100, 0, 120);
  h_mumuInv4     = new TH1F(( std::string("mumuInv4")+dataType).c_str(),
                            "mumu Invariant4 mass", 100, 100, 300);
  h_muPt         = new TH1F(( std::string("MuPt")+dataType).c_str(),
                            "Mu Pt", 100, 0, 120);
  h_muPx         = new TH1F(( std::string("MuPx")+dataType).c_str(),
                            "Mu Px", 100, 0, 120);
  h_muPy         = new TH1F(( std::string("MuPy")+dataType).c_str(),
                            "Mu Py", 100, 0, 120);
  h_muEta        = new TH1F(( std::string("muEta")+dataType).c_str(),
                            "mu Eta", 100, -5, 5);
  h_nMuons       = new TH1F(( std::string("nMuons")+dataType).c_str(),
                            "Muons per event", 30, 0, 15);
  h_nMuonsOrigin = new TH1F(( std::string("nMuonsOrg")+dataType).c_str(),
                            "Muon origins", 500, 0, 500);
  h_muPhi        = new TH1F(( std::string("muPhi")+dataType).c_str(),
                            "mu Phi", 50, 0, 7.0);  
  h_ZZinvMass    = new TH1F(( std::string("mZZ")+dataType).c_str(),
                            "ZZ invariant mass", 100, 100, 300);
  h_ZPx          = new TH1F(( std::string("ZPx")+dataType).c_str(),
                            "Z Pt", 100, 0, 500);
  h_ZPy          = new TH1F(( std::string("ZPy")+dataType).c_str(),
                            "Z Px", 100, 0, 500);
  h_ZPt          = new TH1F(( std::string("ZPt")+dataType).c_str(),
                            "Z Pt", 100, 0, 500);
  h_ZEta         = new TH1F(( std::string("ZEta")+dataType).c_str(),
                            "Z Eta", 100, -5, 5); 
  h_ZPhi         = new TH1F(( std::string("ZPhi")+dataType).c_str(),
                            "Z Phi", 50, 0, 7.0);

  h_JetPt        = new TH1F(( std::string("JetPt")+dataType).c_str(),
                            "Jets Pt", 50, 0, 100.0);

  tree = new TTree(m_types[type].c_str(), "Higgs analysis tree - TMVA");
  
  tree->Branch("evt" ,&ev, "evt/I");
  tree->Branch("type",&ty, "type/I");
  tree->Branch("var1",&var1,"var1/F");
  tree->Branch("var2",&var2,"var2/F");
  tree->Branch("var3",&var3,"var3/F");
  tree->Branch("var4",&var4,"var4/F");
  tree->Branch("var5",&var5,"var5/F");
  tree->Branch("var6",&var6,"var6/F");
  tree->Branch("var7",&var7,"var7/F");
  tree->Branch("var8",&var8,"var8/F");
  
  ev = -1;
  ty = type;
  var1 = 1.0;
  var2 = 1.0;
  var3 = 1.0;
  var4 = 1.0;
  var5 = 1.0;
  var6 = 1.0;
  var7 = 1.0;
  var8 = 1.0;
    
}
//=============================================================================
// Destructor
//=============================================================================
RootOutput::~RootOutput() {

  
} 

//=============================================================================

void RootOutput::Draw() 
{
  

  c1 = new TCanvas((std::string("c1")+dataType).c_str(),"plots",25,140,1000,590);
  
  c1->Divide(3,2);
  
  c1->cd(1);
  h_ZZinvMass->Draw();
  c1->cd(2);
  h_ZPt->Draw();
  c1->cd(3);
  h_ZEta->Draw();
  c1->cd(4);
  h_nMuons->Draw();
  c1->cd(5);
  h_nMuonsOrigin->Draw();
  c1->cd(6);
  h_ZPhi->Draw();

  c2 = new TCanvas((std::string("c2")+dataType).c_str(),"plots",35,140,1000,590);

  c2->Divide(3,2);
  
  c2->cd(1);
  h_mumuInv->Draw();  
  c2->cd(2);
  h_muPt->Draw();
  c2->cd(3);
  h_muEta->Draw();
  c2->cd(4);
  h_mumuInv4->Draw();
  c2->cd(5);
  h_muPhi->Draw();
  c2->cd(6);
  // h_simposePt->Draw();

  c3 = new TCanvas((std::string("c3")+dataType).c_str(),"plots",45,140,1000,590);

  c3->Divide(3,2);

  c3->cd(1);

  h_ZPt->SetLineColor(2);
  h_ZPt->Draw();
  
  h_muPt->SetLineColor(1);
  h_muPt->Draw("SAME");

  c3->cd(2);
  h_JetPt->Draw();
  


}

void RootOutput::Close()
{

  m_fileout->Write();
  //m_fileout->Close();

}

void RootOutput::FillTree()
{

  tree->Fill();
    
}

void RootOutput::Fit()
{

  //... Fit a histogramas

  //h_mumuInv4->Fit();
  
      
}
