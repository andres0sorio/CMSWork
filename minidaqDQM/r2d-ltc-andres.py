import FWCore.ParameterSet.Config as cms

maxevts   = -1
prefix    = 'rfio:/castor/cern.ch/cms/store/streamer/Minidaq/A/000/'
inputfile = prefix + '129/547/' + 'Minidaq.00129547.0001.A.storageManager.00.0000.dat'

process = cms.Process("R2D")

process.load("EventFilter.RPCRawToDigi.RPCSQLiteCabling_cfi")

process.muonRPCDigis = cms.EDFilter("RPCUnpackingModule",
                                    InputLabel = cms.InputTag("source"),
                                    doSynchro = cms.bool(False)
                                    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )


process.source = cms.Source ('NewEventStreamFileReader',
                             fileNames = cms.untracked.vstring(inputfile) )

process.MessageLogger = cms.Service("MessageLogger",
                                    debugModules = cms.untracked.vstring('muonRPCDigis'),
                                    destinations = cms.untracked.vstring('cout'),
                                    cout = cms.untracked.PSet( threshold = cms.untracked.string('INFO'))
                                    )
#...................................................................................................................................

## LTC

process.ltcUnpack = cms.EDProducer("LTCRawToDigi")


#...................................................................................................................................

process.out = cms.OutputModule("PoolOutputModule",
                               fileName =  cms.untracked.string('file:digis.root'),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_muonRPCDigis_*_*',
                                                                      'keep *_ltcUnpack_*_*' )
                               )

process.p = cms.Path( process.ltcUnpack * process.muonRPCDigis )

process.ep = cms.EndPath(process.out)

