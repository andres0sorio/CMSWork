import FWCore.ParameterSet.Config as cms

maxevts = 1000

# 3_5_7: on real data
globaltag = 'GR10_P_V5COS::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/Bit25Test/ttu-skim-trackerCosmic-withCTF.root'

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
process.rpcTechnicalTrigger.RPCDigiLabel   = cms.InputTag("muonRPCDigis")
process.rpcTechnicalTrigger.ConfigFile     = cms.string("hardware-pseudoconfig.txt")

process.dqmttu = cms.EDAnalyzer('DQMTtuAnalyzer',
                                GTReadoutRcd     = cms.InputTag("gtDigis"),
                                GMTReadoutRcd    = cms.InputTag("gtDigis" ),
                                L1TTEmuBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                BitNumbers       = cms.vuint32(24,25,26,27,28,29,30) )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histo.root') )

process.p = cms.Path(process.rpcTechnicalTrigger * process.dqmttu)
