// $Id: $
// Include files 
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

// local


//-----------------------------------------------------------------------------
// Implementation file for class : STLVector_wrapper
//
// 2008-12-09 : Andres Osorio
//-----------------------------------------------------------------------------
using namespace boost::python;

BOOST_PYTHON_MODULE(STLvector)
{
  
  //! python access to stl integer vectors
  class_< std::vector<int> >("vectorInt")
    .def(vector_indexing_suite<std::vector<int> >())
    ;
  
}

