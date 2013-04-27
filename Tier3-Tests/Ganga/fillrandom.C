void fillrandom() {
   //Fill a 1-D histogram from a parametric function
   // To see the output of this macro, click begin_html <a href="gif/fillrandom.gif">here</a>. end_html
   //Author: Rene Brun
   
   gBenchmark->Start("fillrandom");

   //
   // Create a one dimensional histogram (one float per bin)
   // and fill it following the distribution in function sqroot.
   //
   
   TFormula * form1 = new TFormula("form1","abs(sin(x)/x)");
   TF1 * sqroot = new TF1("sqroot","x*gaus(0) + [3]*form1",0,10);
   sqroot->SetParameters(10,4,1,20);

   TH1F * h1f = new TH1F("h1f","Test random numbers",200,0,10);
   h1f->SetFillColor(45);
   h1f->FillRandom("sqroot",10000);
   
   //
   // Open a ROOT file and save the formula, function and histogram
   //
   TFile myfile("fillrandom.root","RECREATE");
   sqroot->Write();
   h1f->Write();
   gBenchmark->Show("fillrandom");

}
