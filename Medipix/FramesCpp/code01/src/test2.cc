// $Id: 
// Include files 

#include <RootCommon.h>
#include <Frame.h>
#include <SimpleClusterAlgo.h>

//From ROOT
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TStyle.h>

#include <sstream>

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {

  std::stringstream filename;
  std::stringstream dscname;
  std::stringstream filenameB;
  std::stringstream dscnameB;
  
  std::ofstream * out = new std::ofstream("results_0000.dat" );
  


  filename << "tim_005.dat";
  dscname << "tim_005.dat.dsc";
  
  filenameB << "tim_005_b.dat";
  dscnameB << "tim_005_b.dat.dsc";
  
  Frame * f1 = new Frame( filename.str().c_str(), dscname.str().c_str(), 1);
  Frame * f2 = new Frame( filenameB.str().c_str(), dscnameB.str().c_str(), 2);
  
  bool check = f1->Compare( (*f2) );
  
  std::cout << "check: " << check << std::endl;

  f1->Clusterize();
  f2->Clusterize();

  f1->FindCoincidences( (*f2) );
  f1->ExportCoincidences( out );


  //f1->Display();
  //f2->Display();
  
  ///////////////////////////////////////////////////

  return 1;
    
}
