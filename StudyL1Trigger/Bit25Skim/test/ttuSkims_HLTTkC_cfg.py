import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1

globaltag = 'GR10_P_V5COS::All'
inputfile = '/store/data/Commissioning10/Cosmics/RECO/v9/000/135/149/FA0C64B6-4C5B-DF11-BA63-003048D2BC30.root'

process   = cms.Process("Bit25Skim")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )


process.makeTtuSkim = cms.EDFilter('Bit25Skim',
                                   GTReadoutRcd = cms.InputTag("gtDigis"),
                                   TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                                   TrackerLabel = cms.InputTag("ctfWithMaterialTracksP5"),
                                   LumiSection = cms.untracked.int32(0),
                                   BitNumbers  = cms.vuint32(25),
                                   MakeCoincidenceTT = cms.vuint32(),
                                   MakeCoincidenceHLT = cms.vstring("HLT_TrackerCosmics"),
                                   ProcessName  = cms.untracked.string("HLT"),
                                   DisableTTUBits = cms.untracked.bool(True),
                                   RequireTrackerInfo = cms.untracked.bool(False) )

process.p = cms.Path(process.makeTtuSkim)

process.out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               fileName = cms.untracked.string('ttuskim.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

