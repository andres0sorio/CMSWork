#include "BasicOutput.h"

BasicOutput::BasicOutput(const char *name) {
  
  dir_name = name;
  
  output = new TObjArray::TObjArray();

  //..........................................................
  
  for(int i=0; i < MAX_BITS; ++i)
    m_ttbits.push_back(i+24);
  
  gDirectory->mkdir(name)->cd();
  book();
  gDirectory->cd("../");
  gDirectory->mkdir("BXDiff");
  
}

void BasicOutput::book() 
{
  //..........................................................
  TH1D * h1;
  //TH2D * h2;
  
  m_selectedBits.push_back(24);
  m_selectedBits.push_back(25);
  m_selectedBits.push_back(31);

  m_singleMuBits.push_back(55); // L1_SingleMuOpen
  m_singleMuBits.push_back(56); // L1_SingleMu0
  m_singleMuBits.push_back(57); // L1_SingleMu3
  m_singleMuBits.push_back(58); // L1_SingleMu5
  m_singleMuBits.push_back(59); // L1_SingleMu7
  m_singleMuBits.push_back(60); // L1_SingleMu10
  m_singleMuBits.push_back(61); // L1_SingleMu14
  m_singleMuBits.push_back(62); // L1_SingleMu20

  
  std::ostringstream hname;
  
  for(int i=0; i < MAX_BITS; ++i) 
  {
    
    hname << "PacTTU.Timing.vs.Run.Bit." << m_ttbits[i];
    pacTTU[i] = new TH2D( hname.str().c_str(),"Pac - TTU Timing", 114, 0, 114, 7, -3.5, 3.5); 
    addObject(pacTTU[i]);
    hname.str("");
    
    hname << "DtTTU.Timing.vs.Run.Bit." << m_ttbits[i];
    dtTTU[i] = new TH2D( hname.str().c_str(),"DT - TTU Timing", 114, 0, 114, 7, -3.5, 3.5);
    addObject(dtTTU[i]);
    hname.str("");
    
    hname << "BX.TT.bit." << m_ttbits[i];
    h1 = new TH1D(hname.str().c_str(),
                  "BX ttechincal trigger bits",
                  7, -3.5, 3.5);
    TechTrigBx[i+24] = h1;
    hname.str("");

    hname << "BX.TTU.vs.Run.Bit." << m_ttbits[i];
    bxTTU[i] = new TH2D( hname.str().c_str(),"Bx TTU distribution", 114, 0, 114, 7, -3.5, 3.5);
    addObject(bxTTU[i]);
    hname.str("");
    

  }

  ttbitsVsAlgbits      = new TH2D( "Ttubits.vs.algotriggs" ,"TTU bits vs L1 triggers", 128, 0, 128, 10, 23, 33);
  
  ttbitsVsMuTriggers   = new TH2D( "Ttubits.vs.l1mutriggs" ,"TTU bits vs L1 mu triggers", 10, 55, 65, 10, 23, 33);

  ttbitsVsMuTriggers25 = new TH2D( "Ttubits.24.25.vs.l1mutriggs" ,"TTU bits 24/25 vs L1 mu triggers", 10, 55, 65, 4, 23, 27);
  
  int maxmutrigs = m_singleMuBits.size();
  
  for(int i=0; i < maxmutrigs; ++i) 
  {
    hname << "MuTriggs.BX.Bit." << m_singleMuBits[i];
    h_muTriggBx[i] = new TH1D( hname.str().c_str(),"Bx TTU distribution", 7, -3.5, 3.5 );
    hname.str("");
  }
    
  h_GB_muon_Pt  = new TH1D( "GB.muons.Pt","Global Pt muons", 50, 0, 40);
  h_GB_muon_Phi = new TH1D( "GB.muons.Phi","Global Phi muons", 50, -3.2, 3.2);
  h_GB_muon_Eta = new TH1D( "GB.muons.Eta","Global Eta muons", 50, -2.5, 2.5);
  h_GB_caloComp = new TH1D( "GB.muons.Calo","Global CaloComp muons", 50, 0.0, 1.0);
  h_GB_chi2dof  = new TH1D( "GB.muons.Chi2dof","Global Norm.chi2 muons", 50, 0.0, 10.0);
  h_GB_muon_d0  = new TH1D( "GB.muons.d0","Global d0 muons", 50, -1.0, 1.0);
  h_GB_muon_d0s = new TH1D( "GB.muons.d0s","Global d0s muons", 50, 0.0, 14.0);

  hh_etaphi_GB =  new TH2D("GB.eta.phi.All.","Global muon eta/phi",
                           50, -2.5, 2.5,  50, -3.2, 3.2 ) ;
  h_GB_muon_Pt->Sumw2();
  h_GB_muon_Eta->Sumw2();
  hh_etaphi_GB->Sumw2();

  h_TR_muon_Pt  = new TH1D( "TR.muons.Pt","Tracker Pt muons", 50, 0, 40);
  h_TR_muon_Phi = new TH1D( "TR.muons.Phi","Tracker Phi muons", 50, -3.2, 3.2);
  h_TR_muon_Eta = new TH1D( "TR.muons.Eta","Tracker Eta muons", 50, -2.5, 2.5);
  h_TR_caloComp = new TH1D( "TR.muons.Calo","Tracker CaloComp muons", 50, 0.0, 1.0);
  h_TR_chi2dof  = new TH1D( "TR.muons.Chi2dof","Global Norm.Chi2 muons", 50, 0.0, 10.0);
  h_TR_muon_d0  = new TH1D( "TR.muons.d0","Global d0 muons", 50, -1.0, 1.0);
  h_TR_muon_d0s = new TH1D( "TR.muons.d0s","Global d0s muons", 50, 0.0, 14.0);

  h_SA_muon_Pt  = new TH1D( "SA.muons.Pt","STA Pt muons", 50, 0, 40);
  h_SA_muon_Phi = new TH1D( "SA.muons.Phi","STA Phi muons", 50, -3.2, 3.2);
  h_SA_muon_Eta = new TH1D( "SA.muons.Eta","STA Eta muons", 50, -2.5, 2.5);

  hh_etaphi_SA =  new TH2D("SA.eta.phi.All.","STA muon eta/phi",
                           50, -2.5, 2.5,  50, -3.2, 3.2 ) ;
  
  hh_etaphi_SA->Sumw2();
  h_SA_muon_Pt->Sumw2();
  h_SA_muon_Eta->Sumw2();

  h_NRecHit_Evt = new TH1D( "NRecHits.Event","RecHits/event", 50, 0.0, 50.0);

  h_NTrTracks_Evt = new TH1D( "NTrTraks.Event","Tracker Tracks/event", 50, 0.0, 50.0);

  h_beamSpot = new TH2D( "BeamSpot","Beam Spot", 50, -0.05, 0.05, 50, -0.05, 0.05);

  hh_etaphi_TR =  new TH2D("TR.eta.phi.All.","Tracker muon eta/phi",
                           50, -2.5, 2.5,  50, -3.2, 3.2 ) ;

  
  h_TR_muon_Pt->Sumw2();
  h_TR_muon_Eta->Sumw2();
  hh_etaphi_TR->Sumw2();
  
  for(int i=0; i < SEL_BITS; ++i ) 
  {

    hname.str("");
    hname << "NRecHits.Event.Bit." << m_selectedBits[i];
    hc_NRecHit_Evt[i] = new TH1D( hname.str().c_str(),"RecHits/event", 50, 0, 50);
    hname.str("");
    
    hname.str("");
    hname << "SA.Pt.Bit." << m_selectedBits[i];
    hc_SA_muon_Pt[i] = new TH1D( hname.str().c_str(),"Muon pt", 50, 0, 40);
    hname.str("");
    
    hname << "TR.Pt.Bit." << m_selectedBits[i];
    hc_TR_muon_Pt[i]  = new TH1D( hname.str().c_str(),"Muon pt", 50, 0, 40);
    hname.str("");
    
    hname << "GB.Pt.Bit." << m_selectedBits[i];
    hc_GB_muon_Pt[i]  = new TH1D( hname.str().c_str(),"Muon pt", 50, 0, 40);
    hname.str("");

    hname << "SA.Eta.Bit." << m_selectedBits[i];
    hc_SA_muon_Eta[i]  = new TH1D( hname.str().c_str(),"Muon eta", 50, -2.5, 2.5);
    hname.str("");

    hname << "TR.Eta.Bit." << m_selectedBits[i];
    hc_TR_muon_Eta[i]  = new TH1D(hname.str().c_str(),"Muon eta", 50, -2.5, 2.5);
    hname.str("");

    hname << "GB.Eta.Bit." << m_selectedBits[i];
    hc_GB_muon_Eta[i]  = new TH1D(hname.str().c_str(),"Muon eta", 50, -2.5, 2.5);
    hname.str("");

    //Phi
    hname << "SA.Phi.Bit." << m_selectedBits[i];
    hc_SA_muon_Phi[i]  = new TH1D( hname.str().c_str(),"Muon phi", 50, -3.2, 3.2);
    hname.str("");

    hname << "TR.Phi.Bit." << m_selectedBits[i];
    hc_TR_muon_Phi[i]  = new TH1D(hname.str().c_str(),"Muon phi", 50, -3.2, 3.2);
    hname.str("");

    hname << "GB.Phi.Bit." << m_selectedBits[i];
    hc_GB_muon_Phi[i]  = new TH1D(hname.str().c_str(),"Muon phi", 50, -3.2, 3.2);
    hname.str("");

    //
    //hname << "SA.Calo.Bit." << m_selectedBits[i];
    //hc_SA_muon_Calo[i]  = new TH1D( hname.str().c_str(),"Muon calocomp", 50, 0.0, 1.0);
    //hname.str("");

    hname << "TR.Calo.Bit." << m_selectedBits[i];
    hc_TR_muon_Calo[i]  = new TH1D(hname.str().c_str(),"Muon calocomp", 50, 0.0, 1.0);
    hname.str("");

    hname << "GB.Calo.Bit." << m_selectedBits[i];
    hc_GB_muon_Calo[i]  = new TH1D(hname.str().c_str(),"Muon calocomp", 50, 0.0, 1.0);
    hname.str("");

    hname << "GB.eta.phi.Bit." << m_selectedBits[i];

    hh_etaphi_GB_Bit[i] = new TH2D(hname.str().c_str(),"Global muon eta/phi",
                                   50, -2.5, 2.5,  50, -3.2, 3.2 ) ;
    hh_etaphi_GB_Bit[i]->Sumw2();
    hname.str("");
    
    ///Tracker
    //////

    hname << "TR.chi2dof.Bit." << m_selectedBits[i];
    hc_TR_muon_chi2dof[i]  = new TH1D(hname.str().c_str(),"Muon chi2/dof", 50, 0.0, 10.0);
    hname.str("");
    
    hname << "GB.chi2dof.Bit." << m_selectedBits[i];
    hc_GB_muon_chi2dof[i]  = new TH1D(hname.str().c_str(),"Muon chi2/dof", 50, 0.0, 10.0);
    hname.str("");

    hname << "TR.d0.Bit." << m_selectedBits[i];
    hc_TR_muon_d0[i]  = new TH1D(hname.str().c_str(),"Muon d0", 50, -1.0, 1.0);
    hname.str("");
    
    hname << "GB.d0.Bit." << m_selectedBits[i];
    hc_GB_muon_d0[i]  = new TH1D(hname.str().c_str(),"Muon d0", 50, -1.0, 1.0);
    hname.str("");

    hname << "TR.d0s.Bit." << m_selectedBits[i];
    hc_TR_muon_d0s[i]  = new TH1D(hname.str().c_str(),"Muon d0s", 50, 0.0, 14.0);
    hname.str("");
    
    hname << "GB.d0s.Bit." << m_selectedBits[i];
    hc_GB_muon_d0s[i]  = new TH1D(hname.str().c_str(),"Muon d0s", 50, 0.0, 14.0);
    hname.str("");
    
    hname << "TR.eta.phi.Bit." << m_selectedBits[i];
    hh_etaphi_TR_Bit[i] = new TH2D(hname.str().c_str(),"Tracker muon eta/phi",
                                   50, -2.5, 2.5,  50, -3.2, 3.2 ) ;
    hh_etaphi_TR_Bit[i]->Sumw2();
    hname.str("");

    ///STA

    hname << "SA.eta.phi.Bit." << m_selectedBits[i];
    hh_etaphi_SA_Bit[i] = new TH2D(hname.str().c_str(),"STA muon eta/phi",
                                   50, -2.5, 2.5,  50, -3.2, 3.2 ) ;
    hh_etaphi_SA_Bit[i]->Sumw2();
    hname.str("");

        
  }
  
  
}


BasicOutput::~BasicOutput() {
  
  //if(dir_name) {delete dir_name;}
  //if(output) { output->Delete(); }
  
}

void BasicOutput::addObject(TObject *obj) {
  output->AddLast(obj);
}

void BasicOutput::addRunToBXDiff( int runid ) {
  
  gDirectory->cd("BXDiff");

  TH1D * h1;
  std::ostringstream hname;

  for(int i=0; i < MAX_BITS; ++i) 
  {
    
    hname << "BX.diff.PAC-TTU.bit." << m_ttbits[i] << ".run." << runid;
    h1 = new TH1D(hname.str().c_str(),
                  "Timing difference between PAC and TTU",
                  7, -3.5, 3.5);
    hname.str("");
    
    ///
    pacTTUDiff[i].insert ( pair<int, TH1D*>( runid , h1) );
    
    hname << "BX.diff.DT-TTU.bit." << m_ttbits[i] << ".run." << runid;
    h1 = new TH1D(hname.str().c_str(),
                  "Timing difference between DT and TTU",
                  7, -3.5, 3.5);
    hname.str("");
    
    dtTTUDiff[i].insert ( pair<int, TH1D*>( runid , h1) );
    
  }
  
  gDirectory->cd("../");
  
}

void BasicOutput::addRunToBXDist( int runid ) {
  
  gDirectory->cd("BXDiff");
  
  TH1D * h1;
  std::ostringstream hname;
  
  for(int i=0; i < MAX_BITS; ++i) 
  {
    
    hname << "BX.TTU.bit." << m_ttbits[i] << ".run." << runid;
    h1 = new TH1D(hname.str().c_str(),
                  "TTU Bx distribution",
                  7, -3.5, 3.5);
    hname.str("");
    //  
    ttuBx[i].insert ( pair<int, TH1D*>( runid , h1) );
    
  }
  
  
  gDirectory->cd("../");
  
}


void BasicOutput::makeHistory( ) {

  std::map< int, TH1D* >::iterator runItr;
  
  for (int i=0; i < 8; ++i ) 
  {

    //std::cout << "For Pac:" << std::endl;
    
    TH2D * hh2 = pacTTU[i];
    int runBin = 1;
    
    for( runItr = pacTTUDiff[i].begin(); runItr != pacTTUDiff[i].end(); ++runItr ) 
    {
      
      for( int k=1; k < 8; ++k) 
      {
        float value = (*runItr).second->GetBinContent(k);
        hh2->SetBinContent( runBin, k, value);
                
      }
      
      runBin+=2;
      
      //std::cout << "runId " <<  (*runItr).first << " h1 " << (*runItr).second << std::endl;
      
    }
    
    //std::cout << "For DT:" << std::endl;
    
    hh2 = dtTTU[i];
    runBin = 1;
    
    for( runItr = dtTTUDiff[i].begin(); runItr != dtTTUDiff[i].end(); ++runItr ) 
    {
      
      for( int k=1; k < 8; ++k) 
      {
        float value = (*runItr).second->GetBinContent(k);
        hh2->SetBinContent( runBin, k, value);
        
      }
      
      runBin+=2;

      //std::cout << "runId " <<  (*runItr).first << " h1 " << (*runItr).second << std::endl;
      
    }

    hh2 = bxTTU[i];
    runBin = 1;
    
    for( runItr = ttuBx[i].begin(); runItr != ttuBx[i].end(); ++runItr ) 
    {
      
      for( int k=1; k < 8; ++k) 
      {
        float value = (*runItr).second->GetBinContent(k);
        hh2->SetBinContent( runBin, k, value);
        
      }
      
      runBin+=2;
      
    }


  }
  
  

  
}

