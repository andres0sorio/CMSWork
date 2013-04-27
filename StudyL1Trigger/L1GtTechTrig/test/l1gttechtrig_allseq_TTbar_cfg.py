import FWCore.ParameterSet.Config as cms

process = cms.Process("L1GtTechTriggerStudy")

maxevts   = 2000

globaltag = 'STARTUP31X_V1::All'
inputfile = '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/FCBE122E-D66B-DE11-9667-001D09F291D2.root'

globaltag = 'MC_3XY_V10::All'
inputfile = '/store/relval/CMSSW_3_4_0_pre2/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_3XY_V10-v1/0003/E0D7EB2D-90BD-DE11-9BB6-0017312B5651.root'

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring( inputfile ) )

readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ('PoolSource', fileNames=readFiles, secondaryFileNames=secFiles)

dataset = cms.untracked.vstring('/RelValTTbar/CMSSW_3_4_0_pre2-MC_3XY_V10-v1/GEN-SIM-DIGI-RAW-HLTDEBUG')       

readFiles.extend([
    '/store/relval/CMSSW_3_4_0_pre2/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_3XY_V10-v1/0003/F4AC0278-96BD-DE11-8687-00261894392D.root',
    '/store/relval/CMSSW_3_4_0_pre2/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_3XY_V10-v1/0003/E2E078D8-C0BD-DE11-A77B-0026189438E0.root',
    '/store/relval/CMSSW_3_4_0_pre2/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_3XY_V10-v1/0003/E0D7EB2D-90BD-DE11-9BB6-0017312B5651.root'
    ]);

secFiles.extend([ ])

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

#.. if cosmics: reconstruction sequence for Cosmics
# process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

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

process.load("L1Trigger.RPCTechnicalTrigger.rpcTechnicalTrigger_cfi")
process.rpcTechnicalTrigger.RPCDigiLabel = cms.InputTag("simMuonRPCDigis")

process.TFileService = cms.Service("TFileService", fileName = cms.string('rpctt_results.root') )

process.l1gtrpctt = cms.EDAnalyzer( 'L1GtTechTrig',
                                    L1TTBitsLabel = cms.InputTag("rpcTechnicalTrigger"),
                                    MuonLabel     = cms.InputTag("selectedLayer1Muons"),
                                    RecoMuonLabel = cms.InputTag("muons"),
                                    MuonPtCut     = cms.untracked.double(4.0),
                                    SelectFilter  = cms.untracked.int32(1),
                                    MaxNBx        = cms.untracked.int32(1),
                                    MinBxNum      = cms.untracked.int32(1),
                                    MaxBxNum      = cms.untracked.int32(1),
                                    EventWindow   = cms.untracked.int32(10),
                                    Precision     = cms.untracked.int32(10),
                                    BitNumbers    = cms.vuint32(24,25,26,27,28,29,30),
                                    PATdata        = cms.untracked.bool(False),
                                    TrackParticles = cms.untracked.bool(False) )

process.p = cms.Path( process.rpcTechnicalTrigger*process.l1gtrpctt )


