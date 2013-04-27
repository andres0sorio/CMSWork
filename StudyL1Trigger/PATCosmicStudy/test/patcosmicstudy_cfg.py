import FWCore.ParameterSet.Config as cms

maxevts = -1
inputfile = 'file:PATLayer1_Output.from.CRAFT2.root'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/PATOutput/109575/PATLayer1_Output.from.CRAFT2.root'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/PATOutput/111664/PATLayer1_Output.fromRECO_muons_10.root'

process = cms.Process("PatCosmics")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.demo = cms.EDAnalyzer('PATCosmicStudy',
                              MuonLabel     = cms.InputTag("selectedLayer1Muons"),
                              JetsLabel     = cms.InputTag("selectedLayer1Jets"),
                              RPCDigiLabel     = cms.InputTag("muonRPCDigis"),
                              GTReadoutRcd     = cms.InputTag("gtDigis"),
                              GMTReadoutRcd    = cms.InputTag("gtDigis"),
                              L1TTEmuBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                              BitNumbers       = cms.vuint32(24,25,26,27,28,29,30) )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histo.root') )

process.p = cms.Path(process.demo)



