import FWCore.ParameterSet.Config as cms

process = cms.Process("L1GtTechTriggerStudy")

maxevts   = -1

globaltag = 'STARTUP31X_V1::All'
inputfile = '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/FCBE122E-D66B-DE11-9667-001D09F291D2.root'

##
globaltag = 'STARTUP31X_V8::All'
inputfile = '/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V8-v1/0008/424A16F0-94B6-DE11-8EBF-001D09F290BF.root'
inputfile = '/store/relval/CMSSW_3_3_0/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V8-v2/0002/F41CADE9-E7BC-DE11-827A-0026189438F7.root'
inputfile = '/store/relval/CMSSW_3_3_0/RelValQCD_Pt_3000_3500/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V8-v2/0002/20208C35-EDBC-DE11-8AFA-0026189438BF.root'
inputfile = '/store/relval/CMSSW_3_3_0/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V8-v2/0002/62D51D5F-E0BC-DE11-8A85-0018F3D096AA.root'

globaltag = 'MC_31X_V9::All'
inputfile = '/store/relval/CMSSW_3_3_0/RelValSingleMuPt10/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_31X_V9-v2/0002/D2F8DD8E-DABC-DE11-AF68-0018F3D09676.root'

globaltag = 'STARTUP3X_V8D::All'
inputfile = '/store/mc/Summer09/MinBias/GEN-SIM-RECO/STARTUP3X_V8D_900GeV-v1/0005/E4590360-4CD7-DE11-8CB4-002618943896.root'

##Only works for 3.4.X
##globaltag = 'MC_3XY_V10::All'
##inputfile = '/store/relval/CMSSW_3_4_0_pre2/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_3XY_V10-v1/0003/E0D7EB2D-90BD-DE11-9BB6-0017312B5651.root'

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

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

process.TFileService = cms.Service("TFileService", fileName = cms.string('rpctt_results.root') )

process.l1gtrpctt = cms.EDAnalyzer( 'L1GtTechTrig',
                                    L1TTBitsLabel  = cms.InputTag("rpcTechnicalTrigger"),
                                    MuonLabel      = cms.InputTag("selectedLayer1Muons"),
                                    RecoMuonLabel  = cms.InputTag("muons"),
                                    MuonPtCut      = cms.untracked.double(4.0),
                                    SelectFilter   = cms.untracked.int32(1),
                                    MaxNBx         = cms.untracked.int32(1),
                                    MinBxNum       = cms.untracked.int32(1),
                                    MaxBxNum       = cms.untracked.int32(1),
                                    EventWindow    = cms.untracked.int32(10),
                                    Precision      = cms.untracked.int32(10),
                                    BitNumbers     = cms.vuint32(24,25,26,27,28,29,30),
                                    PATdata        = cms.untracked.bool(False),
                                    TrackParticles = cms.untracked.bool(False) )

process.p = cms.Path( process.rpcTechnicalTrigger*process.l1gtrpctt )


