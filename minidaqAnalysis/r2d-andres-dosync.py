import FWCore.ParameterSet.Config as cms

process = cms.Process("R2D")

process.load("EventFilter.RPCRawToDigi.RPCSQLiteCabling_cfi")

##process.load("EventFilter.RPCRawToDigi.rpcUnpacker_cfi")

#include "MagneticField/Engine/data/volumeBasedMagneticField.cfi"
#include "Geometry/MuonCommonData/data/muonIdealGeometryXML.cfi"
#include "Geometry/RPCGeometry/data/rpcGeometry.cfi"
##process.load("Geometry.MuonCommonData.data.muonIdealGeometryXML_cfi")
##process.load("Geometry.RPCGeometry.data.rpcGeometry_cfi")
##process.load("DQMServices.Core.DQM_cfg")

process.muonRPCDigis = cms.EDFilter("RPCUnpackingModule",
                                    InputLabel = cms.untracked.InputTag("source"),
                                    doSynchro = cms.bool(True)
                                    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source ('NewEventStreamFileReader',
                             fileNames = cms.untracked.vstring
                             ( 'file:/opt/CMS/data/TTUdata/76401/PrivMuon.00076401.2933.A.storageManager.00.0001.dat'   ) )

process.MessageLogger = cms.Service("MessageLogger",
                                    debugModules = cms.untracked.vstring('muonRPCDigis'),
                                    destinations = cms.untracked.vstring('cout'),
                                    cout = cms.untracked.PSet( threshold = cms.untracked.string('INFO'))
                                    )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName =  cms.untracked.string('file:digis.root'),
                               outputCommands = cms.untracked.vstring("keep *_muonRPCDigis_*_*")
                               )

process.p = cms.Path(process.muonRPCDigis)

process.ep = cms.EndPath(process.out)

