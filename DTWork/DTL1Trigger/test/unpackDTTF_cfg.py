import FWCore.ParameterSet.Config as cms
import os

maxevts   =  10
globaltag = 'XXXXX::All'
inputfile = 'file:/scratch/data/data/HSCP/RAW/stau-246-1_CMSSW_310.root'

process   = cms.Process("DTTFUnpacker")

#.. Geometry and Global Tags
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = cms.string( globaltag )

## L1
###process.load('Configuration.StandardSequences.L1Reco_cff')

## HLT Paths
###process.load('HLTrigger.Configuration.HLT_GRun_cff')


process.load("DTWork.DTL1Trigger.unpackDTTF_cff")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.output = cms.OutputModule("PoolOutputModule",
                                  fileName = cms.untracked.string('HSCP_7TeV_cfi_dttfDigis.root'),
                                  outputCommands = cms.untracked.vstring('keep *') )

## L1
### process.L1Reco_step = cms.Path(process.L1Reco)

process.raw2digi_step = cms.Path(process.RawToDigi)
process.output_step   = cms.EndPath(process.output)

## HLT Scheduler
###process.schedule = process.HLTSchedule

process.schedule = cms.Schedule(process.raw2digi_step, process.output_step )

# special treatment in case of production filter sequence
for path in process.paths: 
    getattr(process,path)._seq = getattr(process,path)._seq


