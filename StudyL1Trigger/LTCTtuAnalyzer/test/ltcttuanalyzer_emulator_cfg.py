import FWCore.ParameterSet.Config as cms

process = cms.Process("LTCTriggerStudy")

process.load("FWCore.MessageService.MessageLogger_cfi")

maxevts = -1

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/99607/digis.99607.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107420/digis.107420.0001.00.0000.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

#.. Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

process.load("Geometry.RPCGeometry.rpcGeometry_cfi")

process.load("rpcTechnicalTrigger_cfi")

process.rpcTechnicalTrigger.RPCDigiLabel = cms.InputTag("muonRPCDigis")
process.rpcTechnicalTrigger.UseDatabase  = cms.untracked.int32(0)
process.rpcTechnicalTrigger.ConfigFile   = cms.untracked.string("hardware-pseudoconfig-TTU-5.txt")

process.ltcttu = cms.EDAnalyzer('LTCTtuAnalyzer',
                                RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                                LTCDigiLabel = cms.InputTag("ltcUnpack"),
                                L1TTBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                BitNumbers       = cms.vuint32(24),
                                ReadRpcTTbits = cms.untracked.int32(1),
                                SelectFilter = cms.untracked.int32(1),
                                MaxNBx       = cms.untracked.int32(1),
                                MinBxNum = cms.untracked.int32(134),
                                MaxBxNum = cms.untracked.int32(135),
                                EventWindow = cms.untracked.int32(10),
                                UseCompression = cms.untracked.int32(1),
                                WriteMode = cms.untracked.int32(1), 
                                Precision = cms.untracked.int32(10),
                                MaxRate = cms.untracked.int32(300) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.rpcTechnicalTrigger*process.ltcttu)

