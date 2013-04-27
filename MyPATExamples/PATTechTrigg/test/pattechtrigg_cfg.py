import FWCore.ParameterSet.Config as cms

maxevts = 2
inputfile = 'file:reco_7TeV_firstdata_361_pat_All.root'

process = cms.Process("PATtechBits")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring( inputfile ) )

process.demo = cms.EDAnalyzer('PATTechTrigg',
                              triggerEvent = cms.InputTag( "patTriggerEvent" ),
                              l1techBit = cms.uint32(40),
                              l1techBitName = cms.string("L1Tech_BSC_minBias_threshold1.v0"))

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo.root') )

process.p = cms.Path(process.demo)
