import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/opt/CMS/data/PrivateMC/Cosmic08/reco_CosmicMC_BOFF_2110.root'
    )
)

process.demo = cms.EDAnalyzer('SimpleAnalyzer'
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo.root')
)

process.p = cms.Path(process.demo)
