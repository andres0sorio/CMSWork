// $Id: $
// Include files 

{
  
  TH1F     *h1;
  TH2F     *h2;
  TProfile *h3;
  
  TFile * f1 = new TFile("control_histograms.root");
  f1->cd();
  
  TCanvas * c1 = new TCanvas("c1", "c1",12,36,984,661);
  c1->Divide(4,2);
  c1->cd();
  
  c1->cd(1);
  h1 = (TH1F*)gDirectory->FindObjectAny("Px");
  h1->Draw();
  
  c1->cd(2);
  h1 = (TH1F*)gDirectory->FindObjectAny("Py");
  h1->Draw();
  
  c1->cd(3);
  h1 = (TH1F*)gDirectory->FindObjectAny("Pz");
  h1->Draw();

  c1->cd(4);
  h1 = (TH1F*)gDirectory->FindObjectAny("EE");
  h1->Draw();

  c1->cd(5);
  h1 = (TH1F*)gDirectory->FindObjectAny("topMass1");
  h1->Draw();

  c1->cd(6);
  h1 = (TH1F*)gDirectory->FindObjectAny("topMass2");
  h1->Draw();
  
  c1->cd(7);
  h1 = (TH1F*)gDirectory->FindObjectAny("topMassRe1");
  h1->Draw();
  
  c1->cd(8);
  h1 = (TH1F*)gDirectory->FindObjectAny("topMassRe2");
  h1->Draw();

  c1->Print("results/control_histos_kine.eps");
  
  TCanvas * c2 = new TCanvas("c2", "c2",12,36,984,661);
  c2->Divide(4,2);
  c2->cd();

  TCanvas * c3 = new TCanvas("c3", "c3",12,36,984,661);
  c3->Divide(4,2);
  c3->cd();

  c2->cd(1);
  h2 = (TH2F*)gDirectory->FindObjectAny("PtEta_bquark");
  h2->Draw("COL");

  
  c2->cd(1);
  h2 = (TH2F*)gDirectory->FindObjectAny("PtEta_bquark");
  h2->Draw("COL");

  c2->cd(2);
  h2 = (TH2F*)gDirectory->FindObjectAny("PtEta_abquark");
  h2->Draw("COL");

  c2->cd(3);
  h2 = (TH2F*)gDirectory->FindObjectAny("PtEta_uquark");
  h2->Draw("COL");

  c2->cd(4);
  h2 = (TH2F*)gDirectory->FindObjectAny("PtEta_adquark");
  h2->Draw("COL");

  c2->cd(5);
  h2 = (TH2F*)gDirectory->FindObjectAny("Eta_bu_quarks");
  h2->Draw("COL");
  
  c3->cd(1);
  h2->Draw("COL");
  c3->cd(5);
  h3 = (TProfile*)gDirectory->FindObjectAny("Eta_bu_quark_prof");
  h3->Draw();
        
  c2->cd(6);
  h2 = (TH2F*)gDirectory->FindObjectAny("Pt_bu_quarks");
  h2->Draw("COL");
  
  c2->Print("results/control_histos_kine_2d.eps");

  c3->cd(6);
  h3 = (TProfile*)gDirectory->FindObjectAny("Eta_bd_quark_prof");
  h3->Draw();

  c3->cd(7);
  h3 = (TProfile*)gDirectory->FindObjectAny("Pt_bu_quark_prof");
  h3->Draw();

  c3->cd(8);
  h3 = (TProfile*)gDirectory->FindObjectAny("Pt_bd_quark_prof");
  h3->Draw();
        


  c3->Print("results/control_histos_kine_2d_prof.eps");

  

  
            

  
}
