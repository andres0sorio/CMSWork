import FWCore.ParameterSet.Config as cms

from CondCore.DBCommon.CondDBSetup_cfi import *

import EventFilter.DTTFRawToDigi.dttfunpacker_cfi
dttfDigis = EventFilter.DTTFRawToDigi.dttfunpacker_cfi.dttfunpacker.clone()

RawToDigi = cms.Sequence(dttfDigis)

dttfDigis.DTTF_FED_Source = 'rawDataCollector'

