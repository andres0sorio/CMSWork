import FWCore.ParameterSet.Config as cms

iscosmics = True
isexpress = False
maxevts   = -1

if isexpress:
    express = 1
    gmtlabel    = 'gtDigis'
    tracklabel  = 'generalTracks'
    cosmiclabel = 'cosmicMuons'
else:
    express = 0
    gmtlabel    = 'gtDigis'
    tracklabel  = 'generalTracks'
    cosmiclabel = 'cosmicMuons'

if iscosmics:
    tracklabel  = 'ctfWithMaterialTracksP5'
    cosmiclabel = 'cosmicMuonsBarrelOnly'

globaltag = 'GR10_P_V2::All'
inputfile = '/store/data/Commissioning10/Cosmics/RECO/v4/000/131/300/02369E90-8032-DF11-9CF2-001D09F2A465.root'

globaltag = 'GR10_P_V4COS::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/133017C/TTUMergedSkim_bit25_133017C.root'

globaltag = 'GR10_P_V5COS::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/133899/TTUMergedSkim_bit31-p2bxdiff_133899.root'

process = cms.Process("L1GtAnalysis")

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

process.l1gtAnalyzer = cms.EDAnalyzer('L1GtTtuAnalyzer',
                                      LumiSectionA        = cms.untracked.int32(0),
                                      LumiSectionB        = cms.untracked.int32(-1),
                                      RPCDigiLabel        = cms.InputTag("muonRPCDigis"),
                                      GTReadoutRcd        = cms.InputTag("gtDigis"),
                                      GMTReadoutRcd       = cms.InputTag(gmtlabel),
                                      IsStreamExpress     = cms.untracked.int32(express),
                                      L1TTEmuBitsLabel    = cms.InputTag("rpcTechnicalTrigger"),
                                      RecoMuonLabel       = cms.InputTag("muons"),
                                      RecoCosmicsLabel    = cms.InputTag(cosmiclabel),
                                      RecoTracksLabel     = cms.InputTag(tracklabel),
                                      RecoSiStripLabel    = cms.InputTag("siStripClusters"),
                                      RecoPixelLabel      = cms.InputTag("siPixelClusters"),
                                      TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                                      MuonPtCut           = cms.untracked.double(0.0),
                                      BitNumbers          = cms.vuint32(24,25,26,27,28,29,30,31),
                                      BitCollisions       = cms.vuint32(3,4,9,40,41),
                                      CheckHLTPaths       = cms.vstring("HLT_Activity_DT"),
                                      ProcessName         = cms.untracked.string("HLT"),
                                      ReadRpcTTEmuBits    = cms.untracked.int32(0),
                                      SelectFilter        = cms.untracked.int32(1),
                                      MaxNBx              = cms.untracked.int32(0),
                                      MinBxNum            = cms.untracked.int32(110),
                                      MaxBxNum            = cms.untracked.int32(160),
                                      BxWindow            = cms.untracked.int32(0),
                                      EventWindow         = cms.untracked.int32(10),
                                      UseCompression      = cms.untracked.int32(1),
                                      WriteMode           = cms.untracked.int32(1), 
                                      Precision           = cms.untracked.int32(6),
                                      MaxRate             = cms.untracked.int32(250),
                                      MaxPt               = cms.untracked.double(40.0),
                                      TrackerLength       = cms.untracked.double(120.0),
                                      TrackerHeight       = cms.untracked.double(100.0),
                                      MakeCoincidenceTT   = cms.vuint32(3),
                                      MakeCoincidenceAlgo = cms.vuint32(124) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo-data.root') )

process.load("FWCore.MessageService.MessageLogger_cfi")

process.p = cms.Path(process.l1gtAnalyzer)

