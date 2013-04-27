import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1
globaltag = 'START42_V13::All'

# with delta rejection
filename  = ['file:/scratch/aosorio/data/HSCPs/stau308-prod/RECO/step2_HSCP_DeltaRej_RECO_425_10kevts_0.root']

process   = cms.Process("UniandesSkim")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring( filename ) )

process.applyFilter = cms.EDFilter('HSCPsUniandesSkim',
                                   TrackLabel = cms.InputTag("standAloneMuons") )

process.p = cms.Path(process.applyFilter)

process.out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               fileName = cms.untracked.string('HSCPUniandesSkim.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

