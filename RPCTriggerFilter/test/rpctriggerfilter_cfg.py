import FWCore.ParameterSet.Config as cms

process = cms.Process("RPCSegmentEff")

# Conditions (Global Tag is used here):
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.connect = "frontier://PromptProd/CMS_COND_21X_GLOBALTAG"
process.GlobalTag.globaltag = "CRUZET4_V5P::All"
process.prefer("GlobalTag")

#Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

# Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

# reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("Alignment.CommonAlignmentProducer.GlobalPosition_Frontier_cff")

process.load("Geometry.TrackerGeometryBuilder.idealForDigiTrackerGeometry_cff")
process.load("Geometry.CSCGeometry.cscGeometry_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.CommonDetUnit.globalTrackingGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.load("RecoLocalMuon.Configuration.RecoLocalMuon_cff")

process.load("CalibMuon.Configuration.CSC_FrontierDBConditions_cff")
process.load("CalibMuon.Configuration.DT_FrontierConditions_cff")

process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")

process.load("RecoMuon.DetLayers.muonDetLayerGeometry_cfi")
process.load("RecoMuon.MuonSeedGenerator.CosmicMuonSeedProducer_cfi")
process.load("RecoMuon.CosmicMuonProducer.cosmicMuons_cfi")
process.load("RecoMuon.CosmicMuonProducer.globalCosmicMuons_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(40000)
)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('/store/data/BeamCommissioning08/Cosmics/RECO/v1/000/062/815/003EA8C7-D583-DD11-A955-001617C3B6FE.root')
)

#... Append a CMS dataset from a file
fh = open("run62815.txt")
for ifile in fh.readlines():
    process.source.fileNames.append( ifile )
#...

process.MessageLogger = cms.Service("MessageLogger",
  destinations = cms.untracked.vstring('/tmp/aosorio/RPCTriggerFilter.log')
)

process.trigfil = cms.EDFilter("RPCTriggerFilter",
                               GMTInputTag = cms.untracked.InputTag("gtDigis"),
                               RPCBarrelTrigger = cms.untracked.bool(False),
                               RPCEndcapTrigger = cms.untracked.bool(False),
                               RPCTrigger = cms.untracked.bool(True),
                               DTTrigger = cms.untracked.bool(False),
                               CSCTrigger = cms.untracked.bool(False),
                               RPCAndDT = cms.untracked.bool(False),
                               RPCAndCSC = cms.untracked.bool(False),
                               DtAndCSC = cms.untracked.bool(False),
                               RPCAndDTAndCSC = cms.untracked.bool(False),
                               EnableTriggerFilter = cms.untracked.bool(True)
                               )

process.p = cms.Path(process.trigfil)

