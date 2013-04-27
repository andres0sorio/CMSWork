#include <CommonIncludes.h>

#include <bitset>

int main(int iargv, const char **argv) {
  
 
  std::bitset<5> wheels;
  
  for(int k=2020; k <= 2070; ++k)
  {
    
    wheels.reset();
    wheels = k;
    std::cout << k << '\t' << wheels << '\n';
    
  }
    
  return 0;
  
}
