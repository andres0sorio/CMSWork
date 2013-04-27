// $Id: $
// Include files 

#include <csvtoxml.h>
#include <iostream>
#include <sstream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

///////////////////////////////////////////////////////////////

int main(int iargv, char **argv) {
  
  std::string infile;
  
  try {
    
    po::options_description desc("Allowed options");
    
    desc.add_options()
      ("help"     , "produce help message")
      ("file"     , po::value<std::string>(), "cvs input file")
      ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(iargv, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help")) 
    {
      std::cout << desc << "\n";
      return 0;
    }
    
    if (vm.count("file")) 
      infile = vm["file"].as<std::string>();
    else {
      std::cout << "please provide input file \n";
      return 1; 
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
  csvtoxml * converter = new csvtoxml( infile.c_str() );
  converter->run();
  delete converter;
  //............................................................................................
  
  return 0;
  
}
