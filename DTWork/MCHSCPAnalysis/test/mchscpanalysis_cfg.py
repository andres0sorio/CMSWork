import FWCore.ParameterSet.Config as cms

process = cms.Process("HSCPAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = 'START42_V13::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# with delta rejection
inputfile = ['file:/scratch/aosorio/data/HSCPs/stau308-prod/RECO/step2_HSCP_DeltaRej_DT_RECO_0.root',
             'file:/scratch/aosorio/data/HSCPs/stau308-prod/RECO/step2_HSCP_DeltaRej_DT_RECO_1.root']


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.demo = cms.EDAnalyzer('MCHSCPAnalysis',
                              MCPartLabel = cms.InputTag("generator"),
                              G4SimLabel  = cms.InputTag("g4SimHits","MuonDTHits","HLT"),
                              HSCPId = cms.untracked.int32(1000015) )

##Segun archivo SLHA
## 1000015  == ~tau_1

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('mchscp-histos.root') )
                                   
process.p = cms.Path(process.demo)
