import FWCore.ParameterSet.Config as cms

process = cms.Process("HSCPAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

inputfile = 'file:/scratch/aosorio/data/HSCPs/stau308-prod/HSCPsRPCIncBX.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.demo = cms.EDAnalyzer('MCHSCPAnalysis',
                              MCPartLabel = cms.InputTag("generator"),
                              HSCPId = cms.untracked.int32(1000015) )

##Segun archivo SLHA
## 1000015  == ~tau_1

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('mchscp-histos.root') )
                                   
process.p = cms.Path(process.demo)
