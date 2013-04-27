import FWCore.ParameterSet.Config as cms

maxevts = 1000
globaltag = 'GR09_31X_V5P::all'
globaltag = 'GR09_P_V1:all'

inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/109/468/F2CDA89C-B57D-DE11-B2C9-000423D98DC4.root'
inputfile = '/store/data/Commissioning09/Cosmics/RECO/v7/000/111/664/468F19D9-C88E-DE11-8CD0-000423D987FC.root'
inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/110/958/9A4CE37D-988A-DE11-B723-000423D6CA6E.root'

globaltag = 'GR09_P_V7::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/123/596/FC5C3B0F-8AE2-DE11-A905-003048D37456.root'

# 3_5_7: on real data
globaltag = 'GR10_P_V5COS::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/Bit25Test/ttu-skim-trackerCosmic-withCTF.root'

process = cms.Process("EmulatorL1GtAnalysis")

process.load("Configuration.StandardSequences.Geometry_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

#.. Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

process.load("Geometry.RPCGeometry.rpcGeometry_cfi")

process.load("rpcTechnicalTrigger_cfi")

process.rpcTechnicalTrigger.UseEventSetup  = cms.untracked.int32(0)
process.rpcTechnicalTrigger.UseRPCSimLink  = cms.untracked.int32(0)
process.rpcTechnicalTrigger.ConfigFile     = cms.string("hardware-pseudoconfig.txt")

process.l1gtAnalyzer = cms.EDAnalyzer('L1GtTtuAnalyzer',
                                      RPCDigiLabel     = cms.InputTag("muonRPCDigis"),
                                      GTReadoutRcd     = cms.InputTag("gtDigis"),
                                      GMTReadoutRcd    = cms.InputTag("gtDigis"),
                                      RecoMuonLabel    = cms.InputTag("muons"),
                                      RecoCosmicsLabel = cms.InputTag("cosmicMuonsBarrelOnly"),
                                      RecoTracksLabel  = cms.InputTag("ctfWithMaterialTracksP5"),
                                      RecoSiStripLabel    = cms.InputTag("siStripClusters"),
                                      RecoPixelLabel      = cms.InputTag("siPixelClusters"),
                                      TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                                      CheckHLTPaths       = cms.vstring("HLT_Activity_DT"),
                                      ProcessName         = cms.untracked.string("HLT"),
                                      MuonPtCut        = cms.untracked.double(0.0),
                                      L1TTEmuBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                      BitNumbers       = cms.vuint32(24,25,26,27,28,29,30,31),
                                      BitCollisions    = cms.vuint32(3,4,9,40,41),
                                      ReadRpcTTEmuBits = cms.untracked.int32(1),
                                      SelectFilter     = cms.untracked.int32(1),
                                      MaxNBx           = cms.untracked.int32(0),
                                      MinBxNum         = cms.untracked.int32(111),
                                      MaxBxNum         = cms.untracked.int32(112),
                                      BxWindow         = cms.untracked.int32(0),
                                      EventWindow      = cms.untracked.int32(10),
                                      UseCompression   = cms.untracked.int32(1),
                                      WriteMode        = cms.untracked.int32(1), 
                                      Precision        = cms.untracked.int32(6),
                                      MaxRate          = cms.untracked.int32(250),
                                      MaxPt            = cms.untracked.double(250),
                                      TrackerLength    = cms.untracked.double(120.0),
                                      TrackerHeight    = cms.untracked.double(100.0),
                                      MakeCoincidenceTT   = cms.vuint32(40,41),
                                      MakeCoincidenceAlgo = cms.vuint32(124)
                                      )
                                      
process.TFileService = cms.Service("TFileService", fileName = cms.string('histo-emulator.root') )

process.load("FWCore.MessageService.MessageLogger_cfi")

process.p = cms.Path(process.rpcTechnicalTrigger*process.l1gtAnalyzer)
