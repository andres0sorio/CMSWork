import FWCore.ParameterSet.Config as cms

maxevts = 100
inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/109/578/FA582E2E-AF7F-DE11-92C6-000423D94494.root'
inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/109/131/B68E147D-C27C-DE11-B561-0019B9F72CC2.root'
globaltag = 'GR09_31X_V4P::All'

process = cms.Process("DQMTtu")

process.load("FWCore.MessageService.MessageLogger_cfi")

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")

#.. Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.load("rpcTechnicalTrigger_cfi")

#.. use the provided hardware configuration parameters
process.rpcTechnicalTrigger.UseDatabase  = cms.untracked.int32(0)
process.rpcTechnicalTrigger.RPCDigiLabel = cms.InputTag("muonRPCDigis")
process.rpcTechnicalTrigger.ConfigFile   = cms.untracked.string("hardware-pseudoconfig.txt")

process.dqmttu = cms.EDAnalyzer('DQMTtuAnalyzer',
                                GTReadoutRcd     = cms.InputTag("gtDigis"),
                                GMTReadoutRcd    = cms.InputTag("gtDigis" ),
                                L1TTEmuBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                BitNumbers       = cms.vuint32(24,25,26,27,28,29,30) )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histo.root') )

process.p = cms.Path(process.rpcTechnicalTrigger * process.dqmttu)
