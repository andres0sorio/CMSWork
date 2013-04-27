import FWCore.ParameterSet.Config as cms

mindigis = 0
maxevts = 100

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.Geometry_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.demo = cms.EDAnalyzer('TTUAnalyzer',
                              RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                              CutAtDigis = cms.untracked.int32( mindigis ) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.demo)

inputfile = 'file:/opt/CMS/data/PrivateMC/Cosmic08/reco_CosmicMC_BOFF_2110.root'
process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring( inputfile ) )




