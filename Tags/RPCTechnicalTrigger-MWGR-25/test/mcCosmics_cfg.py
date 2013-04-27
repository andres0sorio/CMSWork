import FWCore.ParameterSet.Config as cms
import os

process   = cms.Process("RPCTechnicalTrigger")

maxevts   = -1

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories = ['*']
process.MessageLogger.destinations = ['cout']
process.MessageLogger.cout = cms.untracked.PSet(
    	threshold = cms.untracked.string('DEBUG'),
	INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1) ) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

#.. Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

#.. reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.rpcTechnicalTrigger  = cms.EDProducer('RPCTechnicalTrigger',
                                              UseDatabase = cms.untracked.int32(0),
                                              RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                                              BitNumbers=cms.vuint32(24,25,26,27,28),
                                              BitNames=cms.vstring('L1Tech_rpcBit1',
                                                                   'L1Tech_rpcBit2',
                                                                   'L1Tech_rpcBit3',
                                                                   'L1Tech_rpcBit4',
                                                                   'L1Tech_rpcBit5') )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('rpcttbits.root'),
                               outputCommands = cms.untracked.vstring('drop *','keep L1GtTechnicalTriggerRecord_*_*_*') )

process.p = cms.Path(process.rpcTechnicalTrigger)

process.e = cms.EndPath(process.out)


