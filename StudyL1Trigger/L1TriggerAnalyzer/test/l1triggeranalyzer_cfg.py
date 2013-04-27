import FWCore.ParameterSet.Config as cms

#HEP Server : Local

#filename = 'file:/scratch/aosorio/data/NanoDST/Run2011B/L1Accept/RAW/2205F3F2-2BDA-E011-A412-BCAEC532971B.root'
filename = 'file:/scratch/aosorio/data/Skims/Run2011A/MET/A8C82365-57C7-E011-B38E-002618943906.root'
#filename = 'file:/scratch/aosorio/data/RECO/SingleMu/Run2011B/1CBF8B37-7707-E111-BC6E-1CC1DE1D1452.root'

#RelVal : CERN
#Just for testing purposes

#filename = '/store/relval/CMSSW_4_4_2/RelValTTbar/GEN-SIM-RECO/START44_V7-v1/0059/4C4717CE-FC01-E111-92DE-0018F3D096C6.root'

maxevts = 5

process = cms.Process("L1Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.CommonDetUnit.globalTrackingGeometry_cfi")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.GlobalTag.globaltag = 'START44_V13::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( filename ) )

process.l1analyzer = cms.EDAnalyzer('L1TriggerAnalyzer',
                                    DebugMode = cms.bool(True),
                                    GTReadoutRcd = cms.InputTag("gtDigis"),
                                    GMTReadoutRcd = cms.InputTag("gtDigis"),
                                    PhysicsTBits = cms.vint32(55,56,57,58)
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('l1analyzer-histograms.root')  )


process.p = cms.Path(process.l1analyzer)


