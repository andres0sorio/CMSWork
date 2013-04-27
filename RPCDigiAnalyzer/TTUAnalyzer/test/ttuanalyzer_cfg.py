import FWCore.ParameterSet.Config as cms

process = cms.Process("WheelMaps")

mindigis = 3
maxevts  = -1
globaltag = 'GR09_31X_V5P::All'

#inputfile = 'file:digis.root'
#inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/100282/digis.100282.0004.07.0000.root'

inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/109586/TTUSkim_bit24-Bx-1_109586_1.root'

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = globaltag

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.Geometry_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.wheelmaps = cms.EDAnalyzer('TTUAnalyzer',
                                   RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                                   CutAtDigis = cms.untracked.int32( mindigis ) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.wheelmaps)

