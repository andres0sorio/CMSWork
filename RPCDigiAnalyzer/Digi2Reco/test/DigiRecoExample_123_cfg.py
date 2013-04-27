# The following comments couldn't be translated into the new config version:

#
#  drop all the INPUT stuff, BUT simulation
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("DR")
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.load("Configuration.StandardSequences.Simulation_cff")

process.load("Configuration.StandardSequences.MixingNoPileUp_cff")

process.load("Configuration.StandardSequences.FakeConditions_cff")

process.load("Configuration.EventContent.EventContent_cff")

process.source = cms.Source("PoolSource",
    maxEvents = cms.untracked.int32(-1),
    catalog = cms.untracked.string('PoolFileCatalog.xml'),
    fileNames = cms.untracked.vstring('file:sim.root')
)

process.RECO = cms.OutputModule("PoolOutputModule",
    process.FEVTSIMEventContent,
    fileName = cms.untracked.string('reco.root')
)

process.p1 = cms.Path(process.pdigi*process.reconstruction)
process.outpath = cms.EndPath(process.RECO)
process.RECO.outputCommands.append('drop *_*_*_T')
process.RECO.outputCommands.extend(process.SimG4CoreFEVT.outputCommands)
process.RECO.outputCommands.extend(process.SimTrackerFEVT.outputCommands)
process.RECO.outputCommands.extend(process.SimMuonFEVT.outputCommands)
process.RECO.outputCommands.extend(process.SimCalorimetryFEVT.outputCommands)
process.RECO.outputCommands.extend(process.RecoGenJetsFEVT.outputCommands)

