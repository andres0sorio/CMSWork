#if defined(__CINT__)
{
  
  _file0->cd();

  TTree * t1 = (TTree*)gDirectory->FindObjectAny("TtuRates");
  t1->MakeClass("TtuRates");
  
}
#endif
