import FWCore.ParameterSet.Config as cms
import os

maxevts   = -1

# 3_6_X
globaltag = 'START36_V2::All'
inputfile  = '/store/relval/CMSSW_3_6_0_pre3/RelValCosmics/GEN-SIM-RECO/START36_V2-v2/0001/7CA0414B-1C31-DF11-B599-0030487A3232.root'

process   = cms.Process("TTUEmulatorSkim")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.load("rpcTechnicalTrigger_cfi")

#.. use the provided hardware configuration parameters

process.rpcTechnicalTrigger.UseEventSetup  = cms.untracked.int32(0)
process.rpcTechnicalTrigger.UseRPCSimLink  = cms.untracked.int32(1)
process.rpcTechnicalTrigger.ConfigFile     = cms.string("hardware-pseudoconfig.txt")

process.makeTtuSkim = cms.EDFilter('TTUEmulatorSkim',
                                   GTReadoutRcd      = cms.InputTag("rpcTechnicalTrigger"),
                                   BitNumbers        = cms.vuint32(25),
                                   MakeCoincidenceTT = cms.vuint32(25) )

process.p = cms.Path(process.rpcTechnicalTrigger*process.makeTtuSkim)

process.out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               fileName = cms.untracked.string('ttuemuskim.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

