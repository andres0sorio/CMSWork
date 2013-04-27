import FWCore.ParameterSet.Config as cms

maxevts = -1

inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129685/digis.129685.0001.00.0000.root'

process = cms.Process("TtuMiniDQM")

#Unpacker

process.load("EventFilter.RPCRawToDigi.RPCSQLiteCabling_cfi")

process.muonRPCDigis = cms.EDFilter("RPCUnpackingModule",
                                    InputLabel = cms.InputTag("source"),
                                    doSynchro = cms.bool(False) )

process.ltcUnpack = cms.EDProducer("LTCRawToDigi")

process.MessageLogger = cms.Service("MessageLogger",
                                    debugModules = cms.untracked.vstring('muonRPCDigis'),
                                    destinations = cms.untracked.vstring('cout'),
                                    cout = cms.untracked.PSet( threshold = cms.untracked.string('INFO')) )

#end of unpacker.
#............................................................................................................

process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.load("DQM.RPCMonitorDigi.RPCDigiMonitoring_cfi")
process.load("DQMServices.Core.DQM_cfg")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")

process.load("RecoLocalMuon.RPCRecHit.rpcRecHits_cfi")

process.load("Configuration.StandardSequences.MagneticField_cff")

process.ModuleWebRegistry = cms.Service("ModuleWebRegistry")

process.LockService = cms.Service("LockService",
                                  labels = cms.untracked.vstring('source') )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('RPCDQM.root') )

process.rpcRecHits.rpcDigiLabel = 'muonRPCDigis'

process.rpcdigidqm.DigiEventsInterval = 100
process.rpcdigidqm.DigiDQMSaveRootFile = True
process.rpcdigidqm.dqmshifter = True
process.rpcdigidqm.dqmexpert = True
process.rpcdigidqm.dqmsuperexpert = True
process.rpcdigidqm.RootFileNameDigi = 'RPCDQM.root'

process.DQM.collectorHost = ''
process.DQM.collectorPort = 9090
process.DQM.debug = False

# LTC-ttu DQM

#.. Geometry
#process.load("Configuration.StandardSequences.Geometry_cff")

process.ltcdqm = cms.EDAnalyzer('LTCTtuAnalyzer',
                                RPCDigiLabel     = cms.InputTag("muonRPCDigis"),
                                LTCDigiLabel     = cms.InputTag("ltcUnpack"),
                                L1TTBitsLabel    = cms.InputTag("rpcTechnicalTrigger"),
                                BitNumbers       = cms.vuint32(24,25,26,27,28),
                                ReadRpcTTbits    = cms.untracked.int32(0),
                                SelectFilter     = cms.untracked.int32(1),
                                MaxNBx           = cms.untracked.int32(1),
                                MinBxNum         = cms.untracked.int32(110),
                                MaxBxNum         = cms.untracked.int32(160),
                                EventWindow      = cms.untracked.int32(10),
                                UseCompression   = cms.untracked.int32(1),
                                WriteMode        = cms.untracked.int32(1), 
                                Precision        = cms.untracked.int32(10),
                                MaxRate          = cms.untracked.int32(220) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.ltcUnpack*process.muonRPCDigis*process.rpcRecHits*process.rpcdigidqm*process.ltcdqm)

######process.ep = cms.EndPath(process.out)

#.....
