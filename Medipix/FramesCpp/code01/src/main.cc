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

//-----------------------------------------------------------------------------
// Main: This program finds time coincidences between clusters from acquisitions of two Timepix detectors
//
// 2012-03: Andres Osorio/Iván Caicedo
//-----------------------------------------------------------------------------



int main(int iargv, const char **argv) {

  std::stringstream filename;
  std::stringstream dscname;
  std::stringstream filenameB;
  std::stringstream dscnameB;
  std::stringstream path1;
  std::stringstream path2;
  

  //Paths for the two different detectors from the same Run
  path1 << "data/02_p_221_MeV/G09_TIM_t_1ms/0001/";
  path2 << "data/02_p_221_MeV/J06_TIM_t_1ms/0001/";
  
  //Creates the file where the information will be printed and saved
  std::ofstream * out = new std::ofstream("results_02_p_221MeV_0001.dat" );
  
  //Looks for coincidences in all the frames from the Run (Default: 1000 frames)
  for ( int k = 0; k < 10; ++k) {

    
    filename << path1.str() << "tim_00" << k << ".dat";
    dscname << path1.str() << "tim_00" << k << ".dat.dsc";
    
    filenameB << path2.str() << "tim_00" << k << ".dat";
    dscnameB << path2.str() << "tim_00" << k << ".dsc";
    
    Frame * f1 = new Frame( filename.str().c_str(), dscname.str().c_str(), 1);
    Frame * f2 = new Frame( filenameB.str().c_str(), dscnameB.str().c_str(), 2);
    
    bool check = f1->Compare( (*f2) );
    
    std::cout << "check: " << check << std::endl;
    
    f1->Clusterize();
    f2->Clusterize();
    
    f1->FindCoincidences( (*f2) );
    f1->ExportCoincidences( out );
    
    delete f1;
    delete f2;
    
    filename.str("");
    dscname.str("");
    filenameB.str("");
    dscnameB.str("");
    
  }

  for ( int k = 10; k < 100; ++k) {
  
    
    filename << path1.str() << "tim_0" << k << ".dat";
    dscname << path1.str() << "tim_0" << k << ".dat.dsc";
    
    filenameB << path2.str() << "tim_0" << k << ".dat";
    dscnameB << path2.str() << "tim_0" << k << ".dsc";
    
    Frame * f1 = new Frame( filename.str().c_str(), dscname.str().c_str(), 1);
    Frame * f2 = new Frame( filenameB.str().c_str(), dscnameB.str().c_str(), 2);
    
    bool check = f1->Compare( (*f2) );
    
    std::cout << "check: " << check << std::endl;
    
    f1->Clusterize();
    f2->Clusterize();
    
    f1->FindCoincidences( (*f2) );
    f1->ExportCoincidences( out );
    
    delete f1;
    delete f2;
    
    filename.str("");
    dscname.str("");
    filenameB.str("");
    dscnameB.str("");
    
  }

  for ( int k = 100; k < 1000; ++k) {
  
    
    filename << path1.str() << "tim_" << k << ".dat";
    dscname << path1.str() << "tim_" << k << ".dat.dsc";
    
    filenameB << path2.str() << "tim_" << k << ".dat";
    dscnameB << path2.str() << "tim_" << k << ".dsc";
    
    Frame * f1 = new Frame( filename.str().c_str(), dscname.str().c_str(), 1);
    Frame * f2 = new Frame( filenameB.str().c_str(), dscnameB.str().c_str(), 2);
    
    bool check = f1->Compare( (*f2) );
    
    std::cout << "check: " << check << std::endl;
    
    f1->Clusterize();
    f2->Clusterize();
    
    f1->FindCoincidences( (*f2) );
    f1->ExportCoincidences( out );
    
    delete f1;
    delete f2;
    
    filename.str("");
    dscname.str("");
    filenameB.str("");
    dscnameB.str("");
    
  }

  //f1->Display();
  //f2->Display();
  
  ///////////////////////////////////////////////////

  out->close();
  
  delete out;

  return 1;
    
}
