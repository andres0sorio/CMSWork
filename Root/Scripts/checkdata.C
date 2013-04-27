#include <iostream>
#include <fstream>
#include <string>

#include "Riostream.h"
#include <TROOT.h>
#include <TFile.h>

int main(int iargv, const char **argv) {
  
  if(iargv < 2 ) {
    std::cout << "usage : checkdata [input file]" << std::endl;
    return 0;
  }
  
  const char *in  = argv[1];
  
  TFile *_f1 = new TFile(in);
  int status = _f1->IsZombie();
  _f1->Close();
  delete _f1;
  std::cout << status << std::endl;
  
  return status;
  
}
