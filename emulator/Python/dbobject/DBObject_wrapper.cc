// $Id: $
// Include files 

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

// local
#include "RPCTechTriggerConfig.h"
#include "TTUBoardConfig.h"
#include "RBCBoardConfig.h"

//-----------------------------------------------------------------------------
// Implementation file for class : DBObject_wrapper
//
// 2008-12-08 : Andres Osorio
//-----------------------------------------------------------------------------

using namespace boost::python;

BOOST_PYTHON_MODULE(DBObject_wrapper)
{
  
  class_<RPCTechTriggerConfig> ("RPCTechTriggerConfig")
    .def_readonly("runId", &RPCTechTriggerConfig::m_runId)
    .def_readonly("runType", &RPCTechTriggerConfig::m_runType)
    .def_readonly("triggerMode", &RPCTechTriggerConfig::m_triggerMode)
    ;
  
  class_<TTUBoardConfig, bases<RPCTechTriggerConfig> >("TTUBoardConfig", init<int,int,int,int>())
    .def("addfkey", &TTUBoardConfig::addfkey)
    .def_readonly("PKey", &TTUBoardConfig::m_PKey)
    .def_readwrite("Firmware", &TTUBoardConfig::m_Firmware)
    .def_readwrite("LengthOfFiber", &TTUBoardConfig::m_LengthOfFiber)
    .def_readwrite("MaxNumWheels", &TTUBoardConfig::m_MaxNumWheels)
    .def_readwrite("Delay", &TTUBoardConfig::m_Delay)
    .def_readwrite("Wheel1", &TTUBoardConfig::m_Wheel1Id)
    .def_readwrite("Wheel2", &TTUBoardConfig::m_Wheel2Id)
    .def_readwrite("LogicType", &TTUBoardConfig::m_LogicType)
    .def_readwrite("MaskedSector", &TTUBoardConfig::m_MaskedSector)
    .def_readwrite("ForcedSector", &TTUBoardConfig::m_ForcedSector)
    ;
  
  class_<RBCBoardConfig>("RBCBoardConfig", init<int>())
    .def_readonly("PKey", &RBCBoardConfig::m_PKey)
    .def_readwrite("Firmware", &RBCBoardConfig::m_Firmware)
    .def_readwrite("WheelId", &RBCBoardConfig::m_WheelId)
    .def_readwrite("Latency", &RBCBoardConfig::m_Latency)
    .def_readwrite("MayorityLevel", &RBCBoardConfig::m_MayorityLevel)
    .def_readwrite("LogicType", &RBCBoardConfig::m_LogicType)
    .def_readwrite("MaskedOrInput", &RBCBoardConfig::m_MaskedOrInput)
    .def_readwrite("ForcedOrInput", &RBCBoardConfig::m_ForcedOrInput)
    ;

}

