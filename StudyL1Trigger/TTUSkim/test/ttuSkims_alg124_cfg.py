import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1
globaltag = 'GR09_P_V7::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/123/596/FC5C3B0F-8AE2-DE11-A905-003048D37456.root'
inputfile = '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/124/022/6A12F8BC-1AE7-DE11-9235-0030487C6090.root'

process   = cms.Process("TTUSkimStep2")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )


process.makeTtuSkim = cms.EDFilter('TTUSkim',
                                   GTReadoutRcd = cms.InputTag("gtDigis"),
                                   TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                                   LumiSection  = cms.untracked.int32(0),
                                   BitNumbers   = cms.vuint32(31),
                                   MakeCoincidenceTT = cms.vuint32(),
                                   MakeCoincidenceAlgo = cms.vuint32(124),
                                   MakeCoincidenceHLT = cms.vstring(),
                                   ProcessName  = cms.untracked.string("HLT"),
                                   DisableTTUBits = cms.untracked.bool(False) )

process.p = cms.Path(process.makeTtuSkim)

process.out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               fileName = cms.untracked.string('ttuskim.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

