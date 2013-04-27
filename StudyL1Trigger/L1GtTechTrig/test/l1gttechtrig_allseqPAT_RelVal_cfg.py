import FWCore.ParameterSet.Config as cms

process = cms.Process("L1GtTechTriggerStudy")

maxevts   = 2000
globaltag = 'STARTUP31X_V1::All'

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

#.. if cosmics: reconstruction sequence for Cosmics
# process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

#.....................................................................................................................
#.RPC Technical Trigger Emulator
#.
process.load("L1Trigger.RPCTechnicalTrigger.rpcTechnicalTrigger_cfi")

#.. use the provided hardware configuration parameters
process.rpcTechnicalTrigger.UseDatabase  = cms.untracked.int32(0)
process.rpcTechnicalTrigger.ConfigFile   = cms.untracked.string("hardware-pseudoconfig.txt")

#.....................................................................................................................
#. PAT

# extraction of muon sequences

process.load("PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi")
process.allLayer1Muons.embedTrack = cms.bool(True)
process.makeAllLayer1Muons = cms.Sequence( process.allLayer1Muons )
process.load("PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi")
process.allLayer1Muons.addGenMatch = False

#.....................................................................................................................

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

process.p = cms.Path( process.makeAllLayer1Muons
                      * process.selectedLayer1Muons
                      * process.rpcTechnicalTrigger
                      * process.l1gtrpctt )

readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()

process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
       '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-RECO/STARTUP31X_V1-v2/0002/C8CEE598-CB6B-DE11-871F-001D09F2905B.root',
       '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-RECO/STARTUP31X_V1-v2/0002/642F8176-C96B-DE11-9D10-000423D98BE8.root',
       '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-RECO/STARTUP31X_V1-v2/0002/46AA6A11-D46B-DE11-A614-001D09F25438.root',
       '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-RECO/STARTUP31X_V1-v2/0002/443BC1DD-CC6B-DE11-804C-000423D98EC4.root' ] );


secFiles.extend( [
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/FCBE122E-D66B-DE11-9667-001D09F291D2.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/FA3440F0-D16B-DE11-8A23-001D09F2514F.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/ECBAA1B4-CA6B-DE11-8771-000423D99EEE.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/EAF2E62E-CB6B-DE11-9F7A-001D09F2905B.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/D8512187-C86B-DE11-AEF5-001D09F2545B.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/C885E4EC-CB6B-DE11-8482-0019B9F704D6.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/C6F1243F-CF6B-DE11-87E1-000423D991D4.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/ACFEE03F-CA6B-DE11-9599-000423D98B28.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/6812D500-CD6B-DE11-B51F-00304879FA4A.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/60D21982-CC6B-DE11-86CF-001D09F297EF.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/56E2C797-CB6B-DE11-A39F-001D09F25041.root',
    '/store/relval/CMSSW_3_1_1/RelValZMM/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP31X_V1-v2/0002/408C5A4A-C56B-DE11-9587-000423D991F0.root'] );
