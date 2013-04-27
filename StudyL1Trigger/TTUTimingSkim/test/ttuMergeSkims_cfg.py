import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1
globaltag = 'GR09_P_V7::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/123/596/FC5C3B0F-8AE2-DE11-A905-003048D37456.root'

process   = cms.Process("TTUSkim")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('ttuskim_merged.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

