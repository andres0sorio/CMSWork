// $Id: 
// Include files 

#include <RootCommon.h>
#include <Analyze.h>

///////////////////////////////////////////////////////////////

int main(int iargv, const char **argv) {

  ///
  Analyze* d1 = new Analyze("input1.out","input2.out");
  d1->Run();
  delete d1;
    
  ///////////////////////////////////////////////////

  return 1;
    
}
