{
  
  PythiaAnalysis * higgs = new PythiaAnalysis("eventos_pythia8_HZZ.root", "HZZ", 1 );
  
  higgs->Loop();
  higgs->m_root_out->Draw();
  higgs->m_root_out->Close();


  JetPythiaAnalysis * jets = new JetPythiaAnalysis("eventos_pythia8_HZZ.root", "HZZJets", 1 );
  
  jets->Loop();
  jets->m_root_out->Draw();
  jets->m_root_out->Close();

  
  //TCanvas
  //TCanvas *c1 = new TCanvas("higgsmasses",""....);
  //higgs->m_root_out->mZZinv->Draw();
  //higgs200->m_root_out->mZZinv->Draw("same");
  //
  
    
}




