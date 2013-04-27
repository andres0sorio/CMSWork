import FWCore.ParameterSet.Config as cms
import os

process   = cms.Process("RPCTechnicalTrigger")

mytag     = 'test5'

database  = 'sqlite'
site      = os.environ.get("SITE")
maxevts   = 100

#........................................................................................
if site == 'Local':
    inputfile = 'file:/opt/CMS/data/PrivateMC/Cosmic08/reco_CosmicMC_BOFF_2110.root'
else:
    inputfile = 'file:/afs/cern.ch/user/a/aosorio/scratch0/data/reco_CosmicMC_BOFF_2110.root'

if database == 'sqlite':
    dbconnection = 'sqlite_file:myrbconfig.db'
else:
    dbconnection = 'oracle://devdb10/CMS_RPC_COMMISSIONING'
#........................................................................................


process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories = ['*']
process.MessageLogger.destinations = ['cout']
process.MessageLogger.cout = cms.untracked.PSet(
    	threshold = cms.untracked.string('DEBUG'),
	INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(-1) ) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

#.. Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

#.. reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

#.. access database hardware configuration objects
process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                      loadAll = cms.bool(True),
                                      toGet = cms.VPSet(cms.PSet(
                                      record = cms.string('RBCBoardSpecsRcd'),
                                      tag = cms.string(mytag+'a')),
                                      cms.PSet( record = cms.string('TTUBoardSpecsRcd'),
                                      tag = cms.string(mytag+'b'))),
                                      DBParameters = cms.PSet(
                                      messageLevel = cms.untracked.int32(2),
                                      authenticationPath = cms.untracked.string('')),
                                      messagelevel = cms.untracked.uint32(2),
                                      connect = cms.string(dbconnection) )

process.CondDBCommon.connect = cms.string( dbconnection )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )


process.rpcTechnicalTrigger  = cms.EDProducer('RPCTechnicalTrigger',
                                              TriggerMode = cms.int32(1),
                                              RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                                              UseDatabase = cms.untracked.int32(0),
                                              ConfigFile = cms.untracked.string("hardware-pseudoconfig.txt"),
                                              BitNumbers=cms.vuint32(24,25,26,27,28),
                                              BitNames=cms.vstring('L1Tech_rpcBit1',
                                                                   'L1Tech_rpcBit2',
                                                                   'L1Tech_rpcBit3',
                                                                   'L1Tech_rpcBit4',
                                                                   'L1Tech_rpcBit5') )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('rpcttbits.root'),
                               outputCommands = cms.untracked.vstring('drop *','keep L1GtTechnicalTriggerRecord_*_*_*') )

process.p = cms.Path(process.rpcTechnicalTrigger)

process.e = cms.EndPath(process.out)

