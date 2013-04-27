#include "BasicOutput.h"

BasicOutput::BasicOutput(const char *name) {
  
  dir_name = name;

  histograms = new TObjArray::TObjArray();
  
  gDirectory->mkdir(name)->cd();
  
  /////////////////////////////////////////////////
  // create histograms
  
  njets  = new TH1D("nJets","Number of jets",50,0,50);
  addObject(njets);

  jets_energy = new TH1D("jets.E","Jets energetic jet energy",100,0,1000);
  addObject(jets_energy);

  jets_high_energy = new TH1D("jets.highest.E","Highest 2 energetic jet energy",100,0,1000);
  addObject(jets_high_energy);

  nv  = new TH1D("NV","New Variable",50,-5,5);
  addObject(nv);
  
  nv2 = new TH1D("NV2","New Varible 2",50,-1,5);
  addObject(nv2);
  
  nv4 = new TH1D("NV4","New Variable 4",50,-0.5,0.5); 
  addObject(nv4);
  
  etjetratio[0] = new TH1D("EtJetRatio21","Et of Jets ratio",50, 0, 1);
  addObject(etjetratio[0]);
  
  etjetratio[1] = new TH1D("EtJetRatio31","Et of Jets ratio",50, 0, 1);
  addObject(etjetratio[1]);

  etjetratio[2] = new TH1D("EtJetRatio41","Et of Jets ratio",50, 0, 1);
  addObject(etjetratio[2]);
  
  etmiss_nv = new TH2D("EtMiss.vs.NV","Et missing vs NV",100, -5, 5, 100, 0, 700);
  addObject(etmiss_nv);
  
  dphi1_nv = new TH2D("Dphi.jet12.vs.NV","Dphi(jet1,jet2) vs NV",100,-5,5,100,0,1); 
  addObject(dphi1_nv);

  dphi2_nv = new TH2D("Dphi.jet13.vs.NV","Dphi(jet1,jet3) vs NV",100,-5,5,100,0,1); 
  addObject(dphi2_nv);

  dphi3_nv = new TH2D("Dphi.jet1MET.vs.NV","Dphi(jet1,MET) vs NV",100,-5,5,100,0,1); 
  addObject(dphi3_nv);

  dphi4_nv = new TH2D("Dphi.jet2MET.vs.NV","Dphi(jet2,MET) vs NV",100,-5,5,100,0,1); 
  addObject(dphi4_nv);
  
  etjet_dphi1 = new TH2D("EtJet.vs.Dphi.jetMET","EtJet vs Dphi(jet,MET)",100,0,1,100,0,200); 
  addObject(etjet_dphi1);

  jets_phieta = new TH2D("Jet.phi.eta","Jets phi vs eta",50, -6.0,6.0,50,0,1); 
  addObject(jets_phieta);
  
  /////////////////////////////////////////////////////////////////////////////
  
  gDirectory->cd("../");
  
}

BasicOutput::~BasicOutput() {
  
  if(dir_name) {delete dir_name;}
  if(histograms) { histograms->Delete(); }
  
  return;

}

void BasicOutput::addObject(TObject * obj)
{

  histograms->AddLast(obj);
  return;
  
}
