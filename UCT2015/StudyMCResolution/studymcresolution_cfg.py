import FWCore.ParameterSet.Config as cms

process = cms.Process("GenLoop")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

inputFiles = ['/store/mc/Summer12/WH_ZH_HToTauTau_M-125_14TeV-pythia6-tauola/GEN-SIM-RAW-RECO/PU35_POSTLS161_V12-v1/10000/FEA21EDC-C24E-E211-A633-003048678B72.root']

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputFiles ) )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('mcstudy.root')
                                   )

process.tauVisContent = cms.EDProducer('RemoveInvisibleMCPart',
                                       simLabel = cms.InputTag("genParticles"), 
                                       genPdgId = cms.int32(15) )

process.genLoop = cms.EDAnalyzer('StudyMCResolution',
                                 genPdgId = cms.int32(15),
                                 partLabel = cms.InputTag("generator"),
                                 genpartLabel = cms.InputTag("genParticles")
                                 )

process.genLoopVisTaus = cms.EDAnalyzer('StudyMCResolution',
                                        genPdgId = cms.int32(15),
                                        partLabel = cms.InputTag("generator"),
                                        genpartLabel = cms.InputTag("tauVisContent")
                                        )

process.p = cms.Path(process.tauVisContent * process.genLoop * process.genLoopVisTaus)
