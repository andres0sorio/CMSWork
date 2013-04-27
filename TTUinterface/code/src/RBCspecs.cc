// $Id: $
// Include files 

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

// local
#include "RBCBoardSpecs.h"

//-----------------------------------------------------------------------------
// Implementation file for class : _RBCspecs (python wrapper)
//
// 2008-12-08 : Andres Osorio
//-----------------------------------------------------------------------------

using namespace boost::python;

BOOST_PYTHON_MODULE(_RBCspecs)
{
  
  class_<RBCBoardSpecs::RBCBoardConfig >("RBCBoardConfig")
    .def_readwrite("Firmware"      , &RBCBoardSpecs::RBCBoardConfig::m_Firmware)
    .def_readwrite("WheelId"       , &RBCBoardSpecs::RBCBoardConfig::m_WheelId)
    .def_readwrite("Latency"       , &RBCBoardSpecs::RBCBoardConfig::m_Latency)
    .def_readwrite("MayorityLevel" , &RBCBoardSpecs::RBCBoardConfig::m_MayorityLevel)
    .def_readwrite("LogicType"     , &RBCBoardSpecs::RBCBoardConfig::m_LogicType)
    .def_readwrite("MaskedOrInput" , &RBCBoardSpecs::RBCBoardConfig::m_MaskedOrInput)
    .def_readwrite("ForcedOrInput" , &RBCBoardSpecs::RBCBoardConfig::m_ForcedOrInput)
    ;
  
}

