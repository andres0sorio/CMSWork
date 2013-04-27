import FWCore.ParameterSet.Config as cms

maxevts = -1

process = cms.Process("SimpleL1GtAnalysis")

process.load("Configuration.StandardSequences.Geometry_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.l1gtAnalyzer = cms.EDAnalyzer('L1GtTtuAnalyzer',
                                      RPCDigiLabel  = cms.InputTag("muonRPCDigis"),
                                      GTReadoutRcd     = cms.InputTag("l1GtUnpack"),
                                      GMTReadoutRcd    = cms.InputTag("l1GtUnpack"),
                                      L1TTEmuBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                      BitNumbers       = cms.vuint32(24,25,26,27,28),
                                      ReadRpcTTEmuBits = cms.untracked.int32(0),
                                      SelectFilter = cms.untracked.int32(1),
                                      MaxNBx = cms.untracked.int32(1),
                                      MinBxNum = cms.untracked.int32(111),
                                      MaxBxNum = cms.untracked.int32(112),
                                      EventWindow = cms.untracked.int32(10),
                                      UseCompression = cms.untracked.int32(1),
                                      WriteMode = cms.untracked.int32(1), 
                                      Precision = cms.untracked.int32(10),
                                      MaxRate = cms.untracked.int32(150) )


process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger = cms.Service("MessageLogger",
                                    destinations = cms.untracked.vstring('L1GtAnalyzer'),
                                    L1GtAnalyzer = cms.untracked.PSet(
    threshold = cms.untracked.string('DEBUG'),	
    DEBUG = cms.untracked.PSet( 
    limit = cms.untracked.int32(-1) ),#limit = cms.untracked.int32(10) 
    INFO  = cms.untracked.PSet(
    limit = cms.untracked.int32(-1) ),
    debugModules = cms.untracked.vstring('l1GtAnalyz') ) )

process.p = cms.Path(process.l1gtAnalyzer)
