import FWCore.ParameterSet.Config as cms

maxevts   =  -1
globaltag = 'GR10_P_V4COS::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/133017C/TTUMergedSkim_bit25_133017C.root'

process = cms.Process("GoldebBit25")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )

process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

process.goldbit25 = cms.EDAnalyzer('GoldenBit25',
                                   GTReadoutRcd = cms.InputTag("gtDigis"),
                                   TechBitNumber = cms.untracked.int32(25),
                                   TechBitName = cms.untracked.string('L1_RPC'),
                                   Pattern = cms.untracked.int32(0x7) )

process.p = cms.Path(process.goldbit25)
