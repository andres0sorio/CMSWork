import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

pathtodata='/afs/cern.ch/user/a/aosorio/scratch0/data/'
infile= 'file:'+pathtodata+'FullSimTTBar-2_2_X_2008-11-03-STARTUP_V7-AODSIM.100.root'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50000) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( infile ) )

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('IDEAL_V9::All')
process.load("Configuration.StandardSequences.MagneticField_cff")

# PAT Layer 0+1
process.load("PhysicsTools.PatAlgos.patLayer0_cff")
process.load("PhysicsTools.PatAlgos.patLayer1_cff")

## produce ttGenEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## select semi-leptonic ttbar events with an electron in the final state
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")

process.ttDecaySelection.channel_1  = [1, 0, 0]
process.ttDecaySelection.channel_2  = [0, 0, 0]
process.ttDecaySelection.tauDecays  = [0, 0, 0]

process.load("PATTutorial.JetsAnalyzer.jetsanalyzer_cfi")

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histo.root') )

##process.load("PhysicsTools.PatAlgos.cleaningLayer0.caloJetCleaner_cfi")
##process.caloJetCleaner.bitsToIgnore = ['Overlap/Electrons']

## add the two sequences to the process path
process.p = cms.Path(
    process.patLayer0 +
    process.patLayer1 +
    process.makeGenEvt *
    process.ttDecaySelection +
    process.demo)
