import FWCore.ParameterSet.Config as cms

process = cms.Process("IGUANA")
process.load("ISpy/Analyzers/ISpy_Producer_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR09_P_V7::All'

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/124275/TTUSkim_Bit25-MuBkg_124275_0.root'))

from FWCore.MessageLogger.MessageLogger_cfi import *

process.add_(
    cms.Service("ISpyService",
    outputFileName = cms.untracked.string('bit25-skims.ig'),
    outputMaxEvents = cms.untracked.int32(1000),
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.p1 = cms.Path(process.iSpy_sequence)
