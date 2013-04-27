import FWCore.ParameterSet.Config as cms

process = cms.Process("L1GtTechTriggerStudy")

maxevts   = 1000

globaltag = 'STARTUP31X_V8::All'
inputfile = '/store/relval/CMSSW_3_3_3/RelValCosmics/GEN-SIM-RECO/STARTUP31X_V8-v2/0002/06554AFD-31D2-DE11-8D02-002618943910.root'

# 3_6_X
globaltag = 'START36_V2::All'
inputfile  = '/store/relval/CMSSW_3_6_0_pre3/RelValCosmics/GEN-SIM-RECO/START36_V2-v2/0001/7CA0414B-1C31-DF11-B599-0030487A3232.root'


process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

#.. if cosmics: reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

process.load("rpcTechnicalTrigger_cfi")
#..............................................................................................................
#.. EventSetup Configuration
#...

useEventSetup = 0
mytag         = 'test5'
database      = 'sqlite'

if database   == 'sqlite':
    dbconnection = 'sqlite_file:/afs/cern.ch/user/a/aosorio/public/rpcTechnicalTrigger/myrbconfig.db'
elif database == 'oraclerpc':
    dbconnection = 'oracle://devdb10/CMS_RPC_COMMISSIONING'
else:
    dbconnection = ''

if useEventSetup >= 1:

    from CondCore.DBCommon.CondDBCommon_cfi import *

    PoolDBESSource = cms.ESSource("PoolDBESSource",
                                  loadAll = cms.bool(True),
                                  toGet = cms.VPSet(cms.PSet( record = cms.string('RBCBoardSpecsRcd'),
                                                              tag = cms.string(mytag+'a')),
                                                    cms.PSet( record = cms.string('TTUBoardSpecsRcd'),
                                                              tag = cms.string(mytag+'b'))),
                                  DBParameters = cms.PSet( messageLevel = cms.untracked.int32(2),
                                                           authenticationPath = cms.untracked.string('')),
                                  messagelevel = cms.untracked.uint32(2),
                                  connect = cms.string(dbconnection) )

    CondDBCommon.connect = cms.string( dbconnection )

#..............................................................................................................

process.load("rpcTechnicalTrigger_cfi")

#.. use the provided hardware configuration parameters

process.rpcTechnicalTrigger.UseEventSetup  = cms.untracked.int32(0)
process.rpcTechnicalTrigger.UseRPCSimLink  = cms.untracked.int32(1)
process.rpcTechnicalTrigger.ConfigFile     = cms.string("hardware-pseudoconfig.txt")
##process.rpcTechnicalTrigger.ConfigFile     = cms.string("hardware-pseudoconfig-minbias.txt")
process.rpcTechnicalTrigger.Verbosity      = cms.untracked.int32(1)

process.TFileService = cms.Service("TFileService", fileName = cms.string('rpctt_results.root') )

process.l1gtrpctt = cms.EDAnalyzer( 'L1GtTechTrig',
                                    L1TTBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                    MuonLabel     = cms.InputTag("selectedLayer1Muons"),
                                    RecoMuonLabel = cms.InputTag("muons"),
                                    RecoTrackLabel = cms.InputTag("cosmicMuonsBarrelOnly"),
                                    MuonPtCut     = cms.untracked.double(4.0),
                                    SelectFilter  = cms.untracked.int32(1),
                                    MaxNBx        = cms.untracked.int32(1),
                                    MinBxNum      = cms.untracked.int32(1),
                                    MaxBxNum      = cms.untracked.int32(1),
                                    EventWindow   = cms.untracked.int32(10),
                                    Precision     = cms.untracked.int32(10),
                                    NoTrackerInfo = cms.untracked.bool(True),
                                    BitNumbers    = cms.vuint32(24,25,26,27,28,29,30,31),
                                    PATdata        = cms.untracked.bool(False),
                                    TrackParticles = cms.untracked.bool(False),
                                    GeneralTracks  = cms.untracked.bool(True) )


process.p = cms.Path( process.rpcTechnicalTrigger*process.l1gtrpctt )


