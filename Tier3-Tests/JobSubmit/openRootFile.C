void openRootFile( const char *in ) 
{
  
  TFile * f1 = TFile::Open( in );
  f1->ls();
  f1->Close();
  
}
