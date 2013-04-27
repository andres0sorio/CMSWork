import FWCore.ParameterSet.Config as cms

process = cms.Process("Rec")
process.load("Configuration.StandardSequences.Services_cff")

process.load("Configuration.StandardSequences.GeometryPilot2_cff")

process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("Configuration.StandardSequences.FakeConditions_cff")

process.load("FWCore.MessageService.MessageLogger_cfi")

# please note the IMPORTANT:
# in order to operate Digis, one needs to include Mixing module
# (pileup modeling), at least in the 0-pileup mode
#
# There're 3 possible configurations of the Mixing module :
# no-pileup, low luminosity pileup, and high luminosity pileup
#
# they come, respectively, through the 3 config fragments below
#
# *each* config returns label "mix"; thus you canNOT have them
# all together in the same configuration, but only one !!!
#
process.load("Configuration.StandardSequences.MixingNoPileUp_cff")

#include "Configuration/StandardSequences/data/MixingLowLumiPileUp.cff"
#include "Configuration/StandardSequences/data/MixingHighLumiPileUp.cff"
process.load("Configuration.StandardSequences.Simulation_cff")

process.load("Configuration.StandardSequences.L1Emulator_cff")

process.load("Configuration.StandardSequences.DigiToRaw_cff")

##process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

process.load("Configuration.EventContent.EventContent_cff")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)
process.source = cms.Source("PoolSource",
    catalog = cms.untracked.string('PoolFileCatalog.xml'),
    fileNames = cms.untracked.vstring('file:sim.root')
)

process.RECO = cms.OutputModule("PoolOutputModule",
    process.FEVTSIMEventContent,
    fileName = cms.untracked.string('reco.root')
)

process.p1 = cms.Path(process.pdigi*process.L1Emulator*process.DigiToRaw*process.reconstruction)
process.outpath = cms.EndPath(process.RECO)

