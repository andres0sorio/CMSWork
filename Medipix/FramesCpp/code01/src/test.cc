// $Id: 
// Include files 

#include <Data.h>
#include <DSCReader.h>
#include "Frame.h"
#include <SimpleClusterAlgo.h>

#include <sstream>

///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {


  std::stringstream filename;
  std::stringstream dscname;
  
  std::stringstream filenameB;
  std::stringstream dscnameB;

  filename << "tim_005.dat";
  dscname << "tim_005.dat.dsc";
  
  filenameB << "tim_005_b.dat";
  dscnameB << "tim_005_b.dat.dsc";

  Data * d1 = new Data( filename.str().c_str() );
  d1->Read();
  d1->SetTimestamp(1.0);
  //d1->Show();
  
  delete d1;

  DSCReader * dsc = new DSCReader( dscname.str().c_str() );
  dsc->Read();

  delete dsc;
    
  Frame * f1 = new Frame( filename.str().c_str(), dscname.str().c_str(), 1);
  Frame * f2 = new Frame( filenameB.str().c_str(), dscnameB.str().c_str(), 2);
  
  bool check = f1->Compare( (*f2) );
  
  std::cout << "check: " << check << std::endl;
  

  ///if( check ) ;
  //f1->Clusterize();
  //f2->Clusterize();
  
  return 1;
  
}
