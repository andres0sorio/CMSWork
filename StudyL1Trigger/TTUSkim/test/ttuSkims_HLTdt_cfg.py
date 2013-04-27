import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1

globaltag = 'GR09_P_V7::All'
inputfile = '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/124/022/6A12F8BC-1AE7-DE11-9235-0030487C6090.root'

globaltag = 'GR10_P_V2::All'
inputfile = '/store/data/Commissioning10/Cosmics/RECO/v7/000/132/422/72BDA05E-B43B-DF11-9C46-001D09F248F8.root'


process   = cms.Process("TTUSkim")

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
                                   LumiSection = cms.untracked.int32(0),
                                   BitNumbers  = cms.vuint32(31),
                                   MakeCoincidenceTT = cms.vuint32(),
                                   MakeCoincidenceAlgo = cms.vuint32(),
                                   MakeCoincidenceHLT = cms.vstring("HLT_Activity_DT"),
                                   ProcessName  = cms.untracked.string("HLT"),
                                   DisableTTUBits = cms.untracked.bool(True) )

process.p = cms.Path(process.makeTtuSkim)

process.out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               fileName = cms.untracked.string('ttuskim.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

