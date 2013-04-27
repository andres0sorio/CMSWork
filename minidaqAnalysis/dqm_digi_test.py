import FWCore.ParameterSet.Config as cms

maxevts = -1

process = cms.Process("TtuTest")

process.load("CondCore.DBCommon.CondDBSetup_cfi")

process.load("DQM.RPCMonitorDigi.RPCDigiMonitoring_cfi")

process.load("DQMServices.Core.DQM_cfg")

process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")

process.load("RecoLocalMuon.RPCRecHit.rpcRecHits_cfi")

process.load("Configuration.StandardSequences.MagneticField_cff")

process.source = cms.Source("PoolSource",moduleLogName = cms.untracked.string('RPCDigiDQM'),                            
                            fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/100330/digis.100330.0001.00.0000.root') )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

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


process.p = cms.Path(process.rpcRecHits*process.rpcdigidqm)


#.....


