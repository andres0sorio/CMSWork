// $Id: 
// Include files 

#include <IntegralsPlots.h>
#include <sstream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

///////////////////////////////////////////////////////////////

int main(int iargv, char **argv) {

  int   integral = 1;
  int   method   = 1;
  int   subinter = 10000;
  float xmax     = 1.0e6;
  float par1     = 1.0e-4;
  float par2     = 1.0e-3;
  
  try {
    
    po::options_description desc("Allowed options");
    
    desc.add_options()
      ("help"     , "produce help message")
      ("method"   , po::value<int>()  , "Method 1: QAGS 2: GaussLegendre")
      ("point"    , po::value<float>(), "integral upper limit")
      ("par1"     , po::value<float>(), "abs error method 1/epsilon method 2")
      ("par2"     , po::value<float>(), "rel error method 1")
      ("subint"   , po::value<int>()  , "sub intervals")
      ("integral" , po::value<int>()  , "integral to evaluate (1,2,3,4,5)")
      ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(iargv, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help")) 
    {
      std::cout << desc << "\n";
      return 0;
    }
    
    if (vm.count("method")) 
      method = vm["method"].as<int>();
    else {
      std::cout << "please provide integration method \n";
      return 1; }
    
    if (vm.count("point")) 
      xmax = vm["point"].as<float>();
    else {
      std::cout << "please provide upper limit for integration \n";
      return 1; }
    
    if (vm.count("par1")) 
      par1 = vm["par1"].as<float>();
    else 
      std::cout << "no abs error/epsilon entered. using default \n";
    
    if (vm.count("par2")) 
      par2 = vm["par2"].as<float>();
    else {
      if( method == 1)
        std::cout << "no rel error entered. using default \n"; }
    
    if (vm.count("subint")) 
      subinter = vm["subint"].as<int>();
    else 
      std::cout << "no subintervals entered. using default \n";

    if (vm.count("integral")) 
      integral = vm["integral"].as<int>();
    else 
      std::cout << "no integral id selected. using default = 1 \n";
    
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
  
  std::cout << "-------------------------------------------------------" << '\n';
  
  ParameterList parlist;
  
  if (parlist.ParseFile("config.xml") == 0)
    std::cout << "Opened config.xml" << std::endl;
  
  std::cout << "-------------------------------------------------------" << '\n';
  
  IntegralsPlots * p1 = new IntegralsPlots("XSec_neut.dat", "XSec_anti.dat", parlist.GetParameters(0) );
  
  if ( method == 1 ) 
    {
    p1->ConfigMethodOne( subinter, par1, par2 );
    ROOT::Math::IGenFunction * f1 = p1->GetIntegral( integral );
    double result = p1->EvalIntegralMethodOne( f1 , xmax );
    //f1->DestroyInterpolator();
    //delete f1;
    std::cout << "xmax: " << xmax << " y: " << result << '\n';
  }
  else if ( method == 2 ) 
    {
    p1->ConfigMethodTwo( subinter, par1 );
    ROOT::Math::IGenFunction * f1 = p1->GetIntegral( integral );
    double result = p1->EvalIntegralMethodTwo( f1, xmax );
    //f1->DestroyInterpolator();
    //delete f1;
    std::cout << "xmax: " << xmax << " y: " << result << '\n';
  }
  else {}
  
  delete p1;
  
  return 0;
  
}
