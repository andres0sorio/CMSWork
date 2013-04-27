import FWCore.ParameterSet.Config as cms

process = cms.Process("L1GtRpcTTVal")

maxevts = -1

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts ) )

inputfile = 'file:rpcttbits.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

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

process.TFileService = cms.Service("TFileService", fileName = cms.string('rpctt_results.root') )

process.p = cms.Path( process.l1gtrpctt )
