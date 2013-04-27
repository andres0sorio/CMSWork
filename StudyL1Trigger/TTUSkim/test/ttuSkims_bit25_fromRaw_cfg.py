import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1
globaltag = 'GR10_P_V5COS::All'
inputfile = '/store/data/Commissioning10/Cosmics/RAW/v4/000/135/149/FE34B635-725B-DF11-A9A1-000423D98B5C.root'

process   = cms.Process("TTUSkim")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring( inputfile ) )

#...........................................................................................................................................

### RPC unpacker

process.muonRPCDigis = cms.EDFilter("RPCUnpackingModule",
                                    InputLabel = cms.InputTag("source"),
                                    doSynchro = cms.bool(False) )

process.MessageLogger = cms.Service("MessageLogger",
                                    debugModules = cms.untracked.vstring('muonRPCDigis'),
                                    destinations = cms.untracked.vstring('cout'),
                                    cout = cms.untracked.PSet( threshold = cms.untracked.string('INFO')))
## L1GT unpacker

process.load("L1Trigger.Configuration.L1DummyConfig_cff")

# L1 GT/GMT unpack
process.load("EventFilter.L1GlobalTriggerRawToDigi.l1GtUnpack_cfi")

process.l1GtUnpack.DaqGtInputTag = 'source'

process.MessageLogger = cms.Service("MessageLogger",
                                    testGt_Unpacker = cms.untracked.PSet(  threshold = cms.untracked.string('DEBUG'),
                                                                           DEBUG = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
                                                                           INFO = cms.untracked.PSet(  limit = cms.untracked.int32(-1) ) ),
                                    debugModules = cms.untracked.vstring('l1GtUnpack'),
                                    destinations = cms.untracked.vstring('testGt_Unpacker')  )

#...........................................................................................................................................

process.makeTtuSkim = cms.EDFilter('TTUSkim',
                                   GTReadoutRcd = cms.InputTag("l1GtUnpack"),
                                   TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                                   LumiSection = cms.untracked.int32(0),
                                   BitNumbers  = cms.vuint32(25),
                                   MakeCoincidenceTT = cms.vuint32(),
                                   MakeCoincidenceAlgo = cms.vuint32(),
                                   MakeCoincidenceHLT = cms.vstring(),
                                   ProcessName  = cms.untracked.string("HLT"),
                                   DisableTTUBits = cms.untracked.bool(False) )

process.p = cms.Path( process.l1GtUnpack * process.muonRPCDigis * process.makeTtuSkim)

process.out = cms.OutputModule("PoolOutputModule",
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               fileName = cms.untracked.string('ttuskim.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

