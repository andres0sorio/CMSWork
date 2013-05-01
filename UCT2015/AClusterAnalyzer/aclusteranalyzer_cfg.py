import FWCore.ParameterSet.Config as cms

process = cms.Process("ClusterAnalysis")

maxEvents = -1
ecalCalib = 'CALIB_V4' #'Can be CALIB_V1, CALIB_V3, or CALIB_V4'
eicIsolationThreshold = 3

inputFiles = ['/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/FEFAB941-45FB-E111-A767-00261894392F.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/FE83CD5F-ADFB-E111-800A-002618943945.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/FCF9556D-3FFB-E111-91C6-0018F3D096D2.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/FCAA19FC-B8FB-E111-A027-003048678D52.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/F8C58B7E-3FFB-E111-8640-002618943978.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/F4730B9E-0EFC-E111-A883-00261894387A.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/F2AE2B2F-39FB-E111-93D9-0018F3D09628.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/F0976F04-B6FB-E111-83DD-001A928116F0.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/EED6477F-D604-E211-A255-003048679000.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/EC3A205E-3FFB-E111-AE0A-0018F3D09612.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/EAE46676-E5FD-E111-9839-00248C0BE018.root',
              '/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/EA18AA47-86FB-E111-9799-002618943924.root'  ]


process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_53_V21::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxEvents) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring( inputFiles ) )

process.load("UserCode.AClusterAnalyzer.aclusteranalyzer_cfi")
process.load("L1Trigger.UCT2015.recoObjects_cfi")

# Determine which calibration to use
from L1Trigger.UCT2015.emulation_cfi import \
     eg_calib_v1, eg_calib_v3, eg_calib_v4

calib_map = {
    'CALIB_V1': eg_calib_v1,
    'CALIB_V3': eg_calib_v3,
    'CALIB_V4': eg_calib_v4
    }

process.RCTConfigProducers.eGammaECalScaleFactors = calib_map[ecalCalib]
process.RCTConfigProducers.jetMETECalScaleFactors = calib_map[ecalCalib]
process.RCTConfigProducers.eicIsolationThreshold  = eicIsolationThreshold

process.clusterAna = cms.EDAnalyzer('AClusterAnalyzer',
                              debug = cms.bool(False),
                              eClusterSeed = cms.uint32(10),
                              ecalLSB = cms.double(0.5),
                              ecalDigis = cms.VInputTag(cms.InputTag("ecalDigis:EcalTriggerPrimitives") ) )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histo.root')
                                   )
process.p1 = cms.Path(
    process.recoObjects *
    process.emulationSequence *
    process.clusterAna )
