import FWCore.ParameterSet.Config as cms

mindigis = 0
maxevts = 10000

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.Geometry_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

#EvtSelType = 0: reject event in list
#EvtSelType = 1: keep event in list

process.demo = cms.EDAnalyzer('TTUAnalyzer',
                              RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                              CutAtDigis = cms.untracked.int32( mindigis ),
                              EvtSelection = cms.untracked.int32( 1 ),
                              EvtSelType   = cms.untracked.int32( 1 ),
                              EvtSelInput  = cms.untracked.string("list_of_events_100282.txt")
                              )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.demo)

##inputfile = 'file:/opt/CMS/data/PrivateMC/Cosmic08/reco_CosmicMC_BOFF_2110.root'
##inputfile = 'file:/afs/cern.ch/user/a/aosorio/scratch0/data/reco_CosmicMC_BOFF_2110.root'
##inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/100237/digis.100237.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/100282/digis.100282.0001.00.0000.root'
process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring( inputfile ) )

