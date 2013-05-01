import FWCore.ParameterSet.Config as cms

process = cms.Process("OWNPARTICLES")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

inputFiles = ['/store/mc/Summer12/WH_ZH_HToTauTau_M-125_14TeV-pythia6-tauola/GEN-SIM-RAW-RECO/PU35_POSTLS161_V12-v1/10000/FEA21EDC-C24E-E211-A633-003048678B72.root']

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(  inputFiles  )  )

process.myProducerLabel = cms.EDProducer('RemoveInvisibleMCPart',
                                         simLabel = cms.InputTag("genParticles"), 
                                         genPdgId = cms.int32(15) )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root')
)

  
process.p = cms.Path(process.myProducerLabel)

process.e = cms.EndPath(process.out)
