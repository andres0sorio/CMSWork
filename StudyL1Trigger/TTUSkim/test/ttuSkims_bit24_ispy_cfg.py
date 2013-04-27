import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1

globaltag = 'GR10_P_V2::All'
inputfile = '/store/data/Commissioning10/Cosmics/RECO/v4/000/131/300/10D0844D-8A32-DF11-A483-0030487A1884.root'

globaltag = 'GR10_P_V2::All'
inputfile = '/store/data/Commissioning10/Cosmics/RECO/v7/000/132/422/72BDA05E-B43B-DF11-9C46-001D09F248F8.root'

process   = cms.Process("TTUSkim")

#.. Geometry and Global Tags
process.load("ISpy/Analyzers/ISpy_Producer_cff")

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = cms.string( globaltag )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

## iSpy ig generation

from FWCore.MessageLogger.MessageLogger_cfi import *
process.add_(
    cms.Service("ISpyService",
    outputFileName = cms.untracked.string('bit31-skims.ig'),
    outputMaxEvents = cms.untracked.int32(1000),
    )
)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )


process.makeTtuSkim = cms.EDFilter('TTUSkim',
                                   GTReadoutRcd = cms.InputTag("gtDigis"),
                                   TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                                   LumiSection = cms.untracked.int32(0),
                                   BitNumbers  = cms.vuint32(24,31),
                                   MakeCoincidenceTT = cms.vuint32(),
                                   MakeCoincidenceAlgo = cms.vuint32(124),
                                   MakeCoincidenceHLT = cms.vstring(),
                                   ProcessName  = cms.untracked.string("HLT"),
                                   DisableTTUBits = cms.untracked.bool(True) )

process.p = cms.Path(process.makeTtuSkim + process.iSpy_sequence )

process.out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               fileName = cms.untracked.string('ttuskim.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

