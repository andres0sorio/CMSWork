import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1
globaltag = 'GR10_P_V4COS::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/133016C/TTUMergedSkim_bit25_133016C.root'

gmtlabel  = 'gtDigis'
process   = cms.Process("TTUTimingSkim")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )


process.makeTtuSkim = cms.EDFilter('TTUTimingSkim',
                                   GTReadoutRcd = cms.InputTag("gtDigis"),
                                   GMTReadoutRcd = cms.InputTag(gmtlabel),
                                   LumiSection = cms.untracked.int32(0),
                                   SelectedBit = cms.untracked.int32(25),
                                   SelectedBX  = cms.untracked.int32(0),
                                   Detector    = cms.untracked.int32(1) )

process.p = cms.Path(process.makeTtuSkim)

process.out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               fileName = cms.untracked.string('ttuskim.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

