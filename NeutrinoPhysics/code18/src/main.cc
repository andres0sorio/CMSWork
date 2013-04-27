// $Id: $
// Include files 

#include <TGraphFromXML.h>
#include <iostream>
#include <sstream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

///////////////////////////////////////////////////////////////

int main(int iargv, char **argv) {
  
  try {
    
    po::options_description desc("Allowed options");
    
    desc.add_options()
      ("help"     , "produce help message")
      ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(iargv, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help")) 
    {
      std::cout << desc << "\n";
      return 0;
    }
    
  }
  catch(std::exception& e) 
  {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch(...)  {
    std::cerr << "Exception of unknown type!\n";
    return 1;
  }
  
  //............................................................................................
  
  TGraphFromXML graphinfo;
  
  if (graphinfo.ParseFile("graph_config.xml") == 0)
    std::cout << graphinfo;
  std::cout << "-------------------------------------------------" << '\n';
  
  //............................................................................................
  
  return 0;
  
}
