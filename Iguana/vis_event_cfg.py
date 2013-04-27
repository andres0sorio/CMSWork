import FWCore.ParameterSet.Config as cms

process = cms.Process("IGUANA") 
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff") 
process.load("Configuration.StandardSequences.Geometry_cff") 
process.load("Configuration.StandardSequences.Reconstruction_cff") 

#... Magnetic field: force mag field to be 3.8 tesla

#process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.MagneticField_0T_cff")

inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/105076/digis.105076.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106374/digis.106374.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107420/digis.107420.0001.00.0000.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile)
                            #eventsToProcess = cms.untracked.VEventID('107420:203')
                            )


from FWCore.MessageLogger.MessageLogger_cfi import * 
 
useGlobalTag = 'GR09_31X_V4P::All'
process.GlobalTag.globaltag = useGlobalTag

process.load("VisFramework.VisFrameworkBase.VisConfigurationService_cff") 
process.VisConfigurationService.VisAutoStart = False
process.VisConfigurationService.VisCaloAnnotation = False 
process.VisConfigurationService.Views = ('RPhi Window', 'RZ Window') 
process.VisConfigurationService.EnabledTwigs = ('/Objects/CMS Event and Detector/Muon RPC Event/RPC Digis', 
                                                '/Objects/CMS Event and Detector/Magnet', 
                                                '/Objects/Event Collections/Run and Event Number' 
                                                ) 
process.VisConfigurationService.ContentProxies = ('Framework/EventSetup', 
                                                  'Reco/MuonDT', 
                                                  'Reco/MuonCSC', 
                                                  'Reco/MuonRPC', 
                                                  'Reco/Muon') 

