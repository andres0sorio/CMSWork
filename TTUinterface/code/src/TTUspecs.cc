// $Id: $
// Include files 

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

// local
#include "RPCTechTriggerConfig.h"
#include "TTUBoardSpecs.h"
#include "RBCBoardSpecs.h"

//-----------------------------------------------------------------------------
// Implementation file for class : PyDBObject (python wrapper)
//
// 2008-12-08 : Andres Osorio
//-----------------------------------------------------------------------------

using namespace boost::python;

BOOST_PYTHON_MODULE(_TTUspecs)
{
  
  class_<TTUBoardSpecs::TTUBoardConfig >("TTUBoardConfig")
    .def_readwrite("Firmware"      , &TTUBoardSpecs::TTUBoardConfig::m_Firmware)
    .def_readwrite("LengthOfFiber" , &TTUBoardSpecs::TTUBoardConfig::m_LengthOfFiber)
    .def_readwrite("MaxNumWheels"  , &TTUBoardSpecs::TTUBoardConfig::m_MaxNumWheels)
    .def_readwrite("Delay"         , &TTUBoardSpecs::TTUBoardConfig::m_Delay)
    .def_readwrite("Wheel1Id"      , &TTUBoardSpecs::TTUBoardConfig::m_Wheel1Id)
    .def_readwrite("Wheel2Id"      , &TTUBoardSpecs::TTUBoardConfig::m_Wheel2Id)
    .def_readwrite("LogicType"     , &TTUBoardSpecs::TTUBoardConfig::m_LogicType)
    .def_readwrite("MaskedSectors" , &TTUBoardSpecs::TTUBoardConfig::m_MaskedSectors)
    .def_readwrite("ForcedSectors" , &TTUBoardSpecs::TTUBoardConfig::m_ForcedSectors)
    ;
  

}

