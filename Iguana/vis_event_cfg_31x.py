import FWCore.ParameterSet.Config as cms

process = cms.Process("IGUANA") 
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff") 
process.load("Configuration.StandardSequences.Geometry_cff") 
process.load("Configuration.StandardSequences.MagneticField_cff") 
process.load("Configuration.StandardSequences.Reconstruction_cff") 
 
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/relval/CMSSW_3_1_0/RelValSingleMuPt10/ALCARECO/MC_31X_V1_StreamALCARECORpcCalHLT-v1/0002/32FEE565-E266-DE11-8F9F-001D09F251CC.root')
)

from FWCore.MessageLogger.MessageLogger_cfi import * 
 
process.prefer("GlobalTag") 

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'IDEAL_31X::All'
process.GlobalTag.globaltag = 'MC_31X_V1::All'

process.load("VisFramework.VisFrameworkBase.VisConfigurationService_cff") 
process.VisConfigurationService.VisAutoStart = False
process.VisConfigurationService.VisCaloAnnotation = False 
process.VisConfigurationService.Views = ('RPhi Window', 'RZ Window') 
process.VisConfigurationService.EnabledTwigs = ('/Objects/CMS Event and Detector/Muon DT Event/DT 4DSegment', 
                                                '/Objects/CMS Event and Detector/Muon RPC Event/RPC RecHit', 
                                                '/Objects/CMS Event and Detector/Muon/Barrel/Drift Tubes', 
                                                '/Objects/CMS Event and Detector/Muon/Endcap/CSCs', 
                                                '/Objects/CMS Event and Detector/Magnet', 
                                                '/Objects/Event Collections/Run and Event Number' 
                                                ) 
process.VisConfigurationService.ContentProxies = ('Framework/EventSetup', 
                                                  'Reco/MuonDT', 
                                                  'Reco/MuonCSC', 
                                                  'Reco/MuonRPC', 
                                                  'Reco/Muon') 
