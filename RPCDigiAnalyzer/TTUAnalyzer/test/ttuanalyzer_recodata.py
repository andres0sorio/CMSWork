import FWCore.ParameterSet.Config as cms

mindigis = 0
maxevts = -1

# 3_5_7: on real data
globaltag = 'GR10_P_V5COS::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/Bit25Test/ttu-skim-trackerCosmic-withCTF.root'
inputfile = 'file:ttuskim-135149-fromRAW.root'

process = cms.Process("TTUAnalyzer")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = globaltag

# Magnetic fiuld: force mag field to be 3.8 tesla
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

#Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

#Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

#Reconstruction sequence for Cosmics
#process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

process.ttu = cms.EDAnalyzer('TTUAnalyzer',
                             RPCDigiLabel = cms.InputTag("muonRPCDigis"),
                             CutAtDigis = cms.untracked.int32( mindigis ) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.ttu)
