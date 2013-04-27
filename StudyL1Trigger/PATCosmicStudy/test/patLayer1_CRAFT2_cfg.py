import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

maxevts = -1
#globaltag = 'GR09_P_V1::all'
globaltag = 'GR09_31X_V5P::all'

#inputfile = '/store/data/Commissioning09/Cosmics/RECO/v7/000/111/664/F4524940-C58E-DE11-960C-001D09F27067.root'
inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/109/575/F80B08CE-8E7F-DE11-8763-001D09F291D2.root'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

##.....................................................................................................
# PAT Muons:

process.load("PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi")
process.allLayer1Muons.embedTrack = cms.bool(True)
process.makeAllLayer1Muons = cms.Sequence( process.allLayer1Muons )
process.load("PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi")

process.allLayer1Muons.addGenMatch = False

#. PAT Jets:

# extraction of jet sequences

# prepare reco information
process.load("PhysicsTools.PatAlgos.recoLayer0.jetTracksCharge_cff")
process.load("PhysicsTools.PatAlgos.recoLayer0.jetMETCorrections_cff")

# produce object

process.load("PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi")

# mc matching and other switches
process.allLayer1Jets.addBTagInfo         = cms.bool(False)
process.allLayer1Jets.addDiscriminators   = cms.bool(False)
process.allLayer1Jets.addJetCorrFactors   = cms.bool(True)
process.allLayer1Jets.addAssociatedTracks = cms.bool(False)
process.allLayer1Jets.addJetCharge        = cms.bool(False)
process.allLayer1Jets.addGenPartonMatch   = cms.bool(False)                 ## switch on/off matching to quarks from hard scatterin
process.allLayer1Jets.embedGenPartonMatch = cms.bool(False)                 ## switch on/off embedding of the GenParticle parton for this jet
process.allLayer1Jets.addGenJetMatch      = cms.bool(False)                 ## switch on/off matching to GenJet's
process.allLayer1Jets.addPartonJetMatch   = cms.bool(False)                 ## switch on/off matching to PartonJet's (not implemented yet)
process.allLayer1Jets.getJetMCFlavour     = cms.bool(False)

process.makeAllLayer1Jets = cms.Sequence( ##process.patJetCharge * 
                                          process.patJetCorrections *
                                          process.allLayer1Jets )

process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")



##.....................................................................................................

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('PATLayer1_Output.from.CRAFT2.root'),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_muonRPCDigis_*_*',
                                                                      'keep *_gtDigis_*_*',
                                                                      'keep *_selectedLayer1Muons_*_*',
                                                                      'keep *_selectedLayer1Jets_*_*'
                                                                      ) )

process.outpath = cms.EndPath(process.out)

##.....................................................................................................

## PAT Trigger

#process.load( "HLTrigger.HLTcore.hltEventAnalyzerAOD_cfi" )
#process.hltEventAnalyzerAOD.triggerName = cms.string( '@' )
#process.load( "HLTrigger.HLTcore.triggerSummaryAnalyzerAOD_cfi" )

##process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")
##process.patTrigger.onlyStandAlone = False
##patTriggerMatcher = cms.Sequence(
    ##patTriggerElectronMatcher +
##    patTriggerMuonMatcher
##    ## patTriggerTauMatcher
###)

##process.out.outputCommands += [
##    'keep patTriggerObjects_patTrigger_*_*',
##    'keep patTriggerFilters_patTrigger_*_*',
##    'keep patTriggerPaths_patTrigger_*_*',
##    'keep patTriggerEvent_patTriggerEvent_*_*'
##]

##for matchLabel in process.patTriggerEvent.patTriggerMatches:
##        process.out.outputCommands += [ 'keep patTriggerObjectsedmAssociation_patTriggerEvent_' + matchLabel + '_*' ]
        
##.....................................................................................................

# let it run

process.p = cms.Path(
    process.makeAllLayer1Muons *
    process.selectedLayer1Muons *
    process.makeAllLayer1Jets *
    process.selectedLayer1Jets
    #* process.hltEventAnalyzerAOD
    #+ process.triggerSummaryAnalyzerAOD
    #* process.patTriggerSequence
)

##.....................................................................................................
