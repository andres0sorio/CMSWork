import FWCore.ParameterSet.Config as cms

mindigis  = 0
maxevts   = 1000

globaltag = 'START36_V2::All'
inputfile  = '/store/relval/CMSSW_3_6_0_pre3/RelValCosmics/GEN-SIM-RECO/START36_V2-v2/0001/7CA0414B-1C31-DF11-B599-0030487A3232.root'

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring( inputfile ) )

process.demo = cms.EDAnalyzer('TTUAnalyzer',
                              RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                              CutAtDigis = cms.untracked.int32( mindigis ) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.demo)
