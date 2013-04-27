import FWCore.ParameterSet.Config as cms

mytag = 'test1'

process = cms.Process("Test")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("CondCore.DBCommon.CondDBCommon_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )
process.source = cms.Source("EmptySource")

process.CondDBCommon.connect = cms.string('oracle://devdb10/CMS_RPC_COMMISSIONING')

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                      loadAll = cms.bool(True),
                                      toGet = cms.VPSet(cms.PSet(
                                      record = cms.string('RBCBoardSpecsRcd'),
                                      tag = cms.string(mytag+'a')),
                                      cms.PSet( record = cms.string('TTUBoardSpecsRcd'),
                                      tag = cms.string(mytag+'b')) ),
                                      DBParameters = cms.PSet(
                                      messageLevel = cms.untracked.int32(1),
                                      authenticationPath = cms.untracked.string('')),
                                      connect = cms.string('oracle://devdb10/CMS_RPC_COMMISSIONING') )

process.get = cms.EDFilter("EventSetupRecordDataGetter",
    toGet = cms.VPSet( cms.PSet(
    record = cms.string('RBCBoardSpecsRcd'),
    data = cms.vstring('RBCBoardSpecs')),
    cms.PSet( record = cms.string('TTUBoardSpecsRcd'),
    data = cms.vstring('TTUBoardSpecs') ) ),
    verbose = cms.untracked.bool(True) )

process.p = cms.Path(process.get)

