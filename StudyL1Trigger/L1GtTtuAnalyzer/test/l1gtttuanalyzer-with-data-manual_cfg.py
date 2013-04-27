import FWCore.ParameterSet.Config as cms

maxevts = -1
globaltag = 'GR09_31X_V5P::all'
globaltag = 'GR09_E_V4::All'

inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/109/468/F2CDA89C-B57D-DE11-B2C9-000423D98DC4.root'
inputfile = '/store/data/Commissioning09/Cosmics/RECO/v7/000/111/664/468F19D9-C88E-DE11-8CD0-000423D987FC.root'
inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/110/958/9A4CE37D-988A-DE11-B723-000423D6CA6E.root'
inputfile = '/store/express/Commissioning09/StreamExpress/ALCARECO/v8/000/118/333/B0B8C428-5CC2-DE11-9DCB-001D09F276CF.root'
inputfile = '/store/express/Commissioning09/StreamExpress/ALCARECO/v8/000/118/344/9A85DBAF-66C2-DE11-BF4F-001D09F253C0.root'

globaltag = 'GR09_P_V6::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/121/993/ECA3C304-A0D6-DE11-8BCD-0030487A18F2.root'

process = cms.Process("L1GtAnalysis")

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

process.l1gtAnalyzer = cms.EDAnalyzer('L1GtTtuAnalyzer',
                                      RPCDigiLabel     = cms.InputTag("muonRPCDigis"),
                                      GTReadoutRcd     = cms.InputTag("l1GtUnpack"),
                                      GMTReadoutRcd    = cms.InputTag("l1GtUnpack"),
                                      IsStreamExpress  = cms.untracked.int32(1),
                                      L1TTEmuBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                      RecoMuonLabel    = cms.InputTag("muons"),
                                      RecoCosmicsLabel = cms.InputTag("cosmicMuonsBarrelOnly"),
                                      RecoTracksLabel  = cms.InputTag("ctfWithMaterialTracksP5"),
                                      MuonPtCut        = cms.untracked.double(4.0),
                                      BitNumbers       = cms.vuint32(24,25,26,27,28,29,30),
                                      ReadRpcTTEmuBits = cms.untracked.int32(0),
                                      SelectFilter = cms.untracked.int32(1),
                                      MaxNBx = cms.untracked.int32(0),
                                      MinBxNum = cms.untracked.int32(111),
                                      MaxBxNum = cms.untracked.int32(112),
                                      BxWindow = cms.untracked.int32(0),
                                      EventWindow = cms.untracked.int32(10),
                                      UseCompression = cms.untracked.int32(1),
                                      WriteMode = cms.untracked.int32(1), 
                                      Precision = cms.untracked.int32(6),
                                      MaxRate = cms.untracked.int32(250),
                                      MaxPt = cms.untracked.double(250))

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo-data.root') )

process.load("FWCore.MessageService.MessageLogger_cfi")

process.p = cms.Path(process.l1gtAnalyzer)

