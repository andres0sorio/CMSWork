import FWCore.ParameterSet.Config as cms

process = cms.Process("R2D")

process.load("EventFilter.RPCRawToDigi.RPCSQLiteCabling_cfi")

maxevts   = 1000

inputfile = '/store/data/Commissioning10/Cosmics/RAW/v4/000/135/149/FE34B635-725B-DF11-A9A1-000423D98B5C.root'

process.muonRPCDigis = cms.EDFilter("RPCUnpackingModule",
                                    InputLabel = cms.InputTag("source"),
                                    doSynchro = cms.bool(False) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source ('PoolSource',
                             fileNames = cms.untracked.vstring(inputfile) )

process.MessageLogger = cms.Service("MessageLogger",
                                    debugModules = cms.untracked.vstring('muonRPCDigis'),
                                    destinations = cms.untracked.vstring('cout'),
                                    cout = cms.untracked.PSet( threshold = cms.untracked.string('INFO')))

#...L1
#...................................................................................................................................

# L1 EventSetup
#process.load("L1Trigger.Configuration.L1DummyConfig_cff")
#process.load("L1Trigger.Configuration.L1Trigger_EventContent_Cosmics_cff")

process.load("L1Trigger.Configuration.L1DummyConfig_cff")

# L1 GT/GMT unpack
process.load("EventFilter.L1GlobalTriggerRawToDigi.l1GtUnpack_cfi")

# input tag for GT readout collection: 
#     source        = hardware record
#     l1GtPack      = GT packer - DigiToRaw (default) 
#     l1GtTextToRaw = GT TextToRaw

process.l1GtUnpack.DaqGtInputTag = 'source'

#process.l1GtUnpack.DaqGtInputTag = 'l1GtTextToRaw'

# Active Boards Mask

# no board masked (default)
#process.l1GtUnpack.ActiveBoardsMask = 0xFFFF

# GTFE only in the record
#process.l1GtUnpack.ActiveBoardsMask = 0x0000

# GTFE + FDL 
#process.l1GtUnpack.ActiveBoardsMask = 0x0001
     
# GTFE + GMT 
#process.l1GtUnpack.ActiveBoardsMask = 0x0100

# GTFE + FDL + GMT 
#process.l1GtUnpack.ActiveBoardsMask = 0x0101

# BxInEvent to be unpacked
# all available BxInEvent (default)
#process.l1GtUnpack.UnpackBxInEvent = -1 

# BxInEvent = 0 (L1A)
#process.l1GtUnpack.UnpackBxInEvent = 1 

# 3 BxInEvent (F, 0, 1)  
#process.l1GtUnpack.UnpackBxInEvent = 3 

# services

# Message Logger
# uncomment / comment messages with DEBUG mode to run in DEBUG mode

process.MessageLogger = cms.Service("MessageLogger",
                                    testGt_Unpacker = cms.untracked.PSet(  threshold = cms.untracked.string('DEBUG'),      ## DEBUG mode 
                                                                           DEBUG = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),         ## DEBUG mode, all messages  
                                                                           INFO = cms.untracked.PSet(  limit = cms.untracked.int32(-1) ) ),
                                    debugModules = cms.untracked.vstring('l1GtUnpack'), ## DEBUG mode 
                                    destinations = cms.untracked.vstring('testGt_Unpacker')  )

#...................................................................................................................................

process.out = cms.OutputModule("PoolOutputModule",
                               fileName =  cms.untracked.string('file:digis.root'),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_muonRPCDigis_*_*',
                                                                      'keep *_l1GtUnpack_*_*' ) )

process.p = cms.Path( process.l1GtUnpack * process.muonRPCDigis )

process.ep = cms.EndPath(process.out)

