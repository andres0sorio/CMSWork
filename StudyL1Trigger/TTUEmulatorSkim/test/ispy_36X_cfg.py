import FWCore.ParameterSet.Config as cms

process = cms.Process("IGUANA")
process.load("ISpy/Analyzers/ISpy_Producer_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# 3_6_X
globaltag = 'START36_V2::All'
inputfile  = '/store/relval/CMSSW_3_6_0_pre3/RelValCosmics/GEN-SIM-RECO/START36_V2-v2/0001/7CA0414B-1C31-DF11-B599-0030487A3232.root'


process.GlobalTag.globaltag = globaltag

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

from FWCore.MessageLogger.MessageLogger_cfi import *

process.add_(
    cms.Service("ISpyService",
    outputFileName = cms.untracked.string('RelValCosmics_36X.ig'),
    outputIg = cms.untracked.bool(True),
    outputMaxEvents = cms.untracked.int32 (1000),
    online = cms.untracked.bool(True),
    debug = cms.untracked.bool(True)

    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.p1 = cms.Path(process.iSpy_sequence)
