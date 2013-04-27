import FWCore.ParameterSet.Config as cms

isexpress = False
maxevts   = -1

if isexpress:
    express = 1
    gmtlabel    = 'gtDigis'
    tracklabel  = 'generalTracks'
else:
    express = 0
    gmtlabel    = 'gtDigis'
    tracklabel  = 'generalTracks'

globaltag = 'GR10_E_V4::all'
inputfile = 'rfio:/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/RAW-RECO/Apr1Skim_Muon_skim-v1/0139/047E236C-B03E-DF11-8A23-002618FDA204.root'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/132601/TTUMergedSkim_bit31-40_132601.root'

process = cms.Process("L1TTUStudies")

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

process.l1gtAnalyzer = cms.EDFilter('L1TTUStudies',
                                    LumiSection          = cms.untracked.int32(0),
                                    RPCDigiLabel         = cms.InputTag("muonRPCDigis"),
                                    GTReadoutRcd         = cms.InputTag("gtDigis"),
                                    GMTReadoutRcd        = cms.InputTag(gmtlabel),
                                    RecoMuonLabel        = cms.InputTag("muons"),
                                    RecoTracksLabel      = cms.InputTag(tracklabel),
                                    RecoSiStripLabel     = cms.InputTag("siStripClusters"),
                                    RecoPixelLabel       = cms.InputTag("siPixelClusters"),
                                    TriggerResultsLabel  = cms.InputTag("TriggerResults","","HLT"),
                                    MuonPtCut            = cms.untracked.double(0.0),
                                    BitNumbers           = cms.vuint32(24,25,26,27,28,29,30,31),
                                    BitCollisions        = cms.vuint32(3,4,9,40,41),
                                    CheckHLTPaths        = cms.vstring("HLT_Activity_DT"),
                                    ProcessName          = cms.untracked.string("HLT"),
                                    MaxPt                = cms.untracked.double(40.0),
                                    TrackerLength        = cms.untracked.double(120.0),
                                    TrackerHeight        = cms.untracked.double(100.0),
                                    MakeCoincidenceTT    = cms.vuint32(3),
                                    MakeCoincidenceAlgo  = cms.vuint32(124),
                                    MuonTypeSelection    = cms.untracked.int32(4),
                                    TrackerMuonSelection = cms.untracked.int32(19),
                                    SelectedBxWindow     = cms.vint32(-2,-1,0,1,2) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo-data.root') )

process.load("FWCore.MessageService.MessageLogger_cfi")

# filter on good vertex
process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                           vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                           minimumNDOF = cms.uint32(4),
                                           maxAbsZ = cms.double(15),	
                                           maxd0 = cms.double(2)	
                                           )

process.p = cms.Path(process.primaryVertexFilter * process.l1gtAnalyzer)

#process.p.remove( process.primaryVertexFilter )

