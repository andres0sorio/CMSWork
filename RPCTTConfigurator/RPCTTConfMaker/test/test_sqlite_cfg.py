import FWCore.ParameterSet.Config as cms

mytag = 'test5'

process = cms.Process("Test")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
process.source = cms.Source("EmptySource")

process.CondDBCommon.connect = "sqlite_file:myrbconfig.db"
process.CondDBCommon.catalog = cms.string('file:test.xml')

process.PoolDBOutputService = cms.Service("PoolDBOutputService", process.CondDBCommon,
    toPut = cms.VPSet(cms.PSet(
    record = cms.string('RBCBoardSpecsRcd'),
    tag = cms.string(mytag+'a')),
    cms.PSet( record = cms.string('TTUBoardSpecsRcd'),
    tag = cms.string(mytag+'b') )) )

process.test = cms.EDAnalyzer('RPCTTConfMaker',
                              DataFile = cms.untracked.string("hardware-pseudoconfig.txt") )

process.p = cms.Path(process.test)

