import FWCore.ParameterSet.Config as cms

process = cms.Process("LTCrun")

process.load("FWCore.MessageService.MessageLogger_cfi")

maxevts   = -1

inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107420/digis.107420.0001.00.0000.root'

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

#.. Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

process.load("Geometry.RPCGeometry.rpcGeometry_cfi")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.ltcana = cms.EDAnalyzer('LTCTtuAnalyzer',
                                RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                                LTCDigiLabel = cms.InputTag("ltcUnpack"),
                                L1TTBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                BitNumbers       = cms.vuint32(25),
                                ReadRpcTTbits = cms.untracked.int32(0),
                                SelectFilter = cms.untracked.int32(1),
                                MaxNBx       = cms.untracked.int32(1),
                                MinBxNum = cms.untracked.int32(134),
                                MaxBxNum = cms.untracked.int32(135),
                                EventWindow = cms.untracked.int32(10),
                                UseCompression = cms.untracked.int32(1),
                                WriteMode = cms.untracked.int32(1), 
                                Precision = cms.untracked.int32(10),
                                MaxRate = cms.untracked.int32(200) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.ltcana)

