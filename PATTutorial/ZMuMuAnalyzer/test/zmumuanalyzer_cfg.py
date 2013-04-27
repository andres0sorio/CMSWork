import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories = ['*']
process.MessageLogger.destinations = ['cout']
process.MessageLogger.cout = cms.untracked.PSet(
    threshold = cms.untracked.string('INFO'),
    INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(-1) ) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

path='/castor/cern.ch/user/a/aosorio/Summer08/'
infile= 'rfio:'+path+'Summer08_Zmumu_GEN-SIM-RECO_IDEAL_V11_redigi_v1_0012_xx.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( infile ) )

#...
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('IDEAL_V11::All')
process.load("Configuration.StandardSequences.MagneticField_cff")

# PAT Layer 0+1
process.load("PhysicsTools.PatAlgos.patLayer0_cff")
process.load("PhysicsTools.PatAlgos.patLayer1_cff")

#add this:
process.allLayer1Electrons.addTrigMatch = True
process.allLayer1Electrons.trigPrimMatch = [cms.InputTag("electronTrigMatchHLT1ElectronRelaxed"),cms.InputTag("electronTrigMatchCandHLT1ElectronStartup")]
process.allLayer1Jets.addTrigMatch = True
process.allLayer1Jets.trigPrimMatch = [cms.InputTag("jetTrigMatchHLT1ElectronRelaxed"), cms.InputTag("jetTrigMatchHLT2jet")]
process.allLayer1METs.addTrigMatch = True
process.allLayer1METs.trigPrimMatch = [cms.InputTag("metTrigMatchHLT1MET65")]

process.allLayer1Muons.addTrigMatch = True
process.allLayer1Muons.trigPrimMatch = [cms.InputTag("muonTrigMatchHLT1MuonNonIso"), cms.InputTag("muonTrigMatchHLT1MET65")]
process.allLayer1Muons.trigPrimMatch = [cms.InputTag("muonTrigMatchHLT1MuonNonIso"), cms.InputTag("muonTrigMatchHLT1MET65"), cms.InputTag("myTrigMatches")]


process.allLayer1Photons.addTrigMatch = True
process.allLayer1Photons.trigPrimMatch = [cms.InputTag("photonTrigMatchHLT1PhotonRelaxed")]
process.allLayer1Taus.addTrigMatch = True
process.allLayer1Taus.trigPrimMatch = [cms.InputTag("tauTrigMatchHLT1Tau")]

# add myTriggerObjs: Label of path of interest hltZMML3Filtered
process.myTrigObjects = cms.EDProducer("PATTrigProducer",
                                       triggerEvent = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
	                               filterName = cms.InputTag("hltZMML3Filtered","","HLT")
                                       )

process.myTrigMatches = cms.EDFilter("PATTrigMatcher",
                                     src     = cms.InputTag("allLayer0Muons"),
                                     matched = cms.InputTag("myTrigObjects"),
                                     maxDPtRel = cms.double(0.5),
                                     maxDeltaR = cms.double(0.5),
                                     resolveAmbiguities    = cms.bool(True),
                                     resolveByMatchQuality = cms.bool(False),
                                     )

#...

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('histo.root') )

process.demo = cms.EDAnalyzer('ZMuMuAnalyzer')

process.myTrigMatchSequence = cms.Sequence(process.myTrigObjects * process.myTrigMatches)

patLayer0EventContentTriggerMatch = [
    'keep patTriggerPrimitivesOwned_*_*_*',
    'keep patTriggerPrimitivesOwnededmAssociation_*_*_*'
    ]

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('PATLayer1_Output.fromAOD_full.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('drop *')
                               )

process.outpath = cms.EndPath(process.out)

process.out.outputCommands += patLayer0EventContentTriggerMatch

# save PAT Layer 1 output
process.load("PhysicsTools.PatAlgos.patLayer1_EventContent_cff")
process.out.outputCommands.extend(process.patLayer1EventContent.outputCommands)

process.p = cms.Path(
    process.patLayer0 *
    process.myTrigMatchSequence *
    process.patLayer1 +
    process.demo )
