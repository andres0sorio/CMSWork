import FWCore.ParameterSet.Config as cms

process = cms.Process("UTAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#archivo de prueba:
inputfile = 'file:patTuple.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.utanalysis = cms.EDAnalyzer('UTAnalyzer',
                                    muonSrc     = cms.untracked.InputTag("cleanPatMuons"),
                                    jetSrc      = cms.untracked.InputTag("cleanPatJets"),
                                    metSrc      = cms.untracked.InputTag("patMETs") )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histo.root') )

process.p = cms.Path(process.utanalysis)
