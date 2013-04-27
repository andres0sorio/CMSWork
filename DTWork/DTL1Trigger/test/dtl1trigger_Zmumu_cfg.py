import FWCore.ParameterSet.Config as cms

process = cms.Process("DTL1Studies")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START38_V12::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

filename = 'file:/scratch/aosorio/data/HSCPs/stau308-prod/HSCPsRPCIncBX.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(filename) )

process.l1dtstudy = cms.EDAnalyzer('DTL1Trigger',
                                   GTReadoutRcd        = cms.InputTag("gtDigis"),
                                   GMTReadoutRcd       = cms.InputTag("gtDigis"),
                                   TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                                   TrackLabel          = cms.InputTag("standAloneMuons"),
                                   DTChamPhLabel       = cms.InputTag("dttfDigis"),
                                   DTLocalTrigLabel    = cms.InputTag("hltMuonDTDigis"))

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histo.root')  )

process.p = cms.Path(process.l1dtstudy)

#... CMSDataset 
readFiles = cms.untracked.vstring() 
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [ 'file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_0_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_1_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_2_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_3_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_4_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_5_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_6_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_7_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_8_root','file:/scratch/aosorio/data/Zmumu/step2_RAW2DIGI_L1Reco_RECO_9_root'] )
