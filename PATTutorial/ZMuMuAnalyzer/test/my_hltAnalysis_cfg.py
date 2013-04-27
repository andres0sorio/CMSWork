import FWCore.ParameterSet.Config as cms
process = cms.Process( "HLTPROV" )

path='/castor/cern.ch/user/a/aosorio/Summer08/'
infile= 'rfio:'+path+'Summer08_Zmumu_GEN-SIM-RECO_IDEAL_V11_redigi_v1_0012_xx.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( infile ) )

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))

process.load( "HLTrigger.HLTcore.hltEventAnalyzerAOD_cfi" )

process.hltEventAnalyzerAOD.triggerName = cms.string( '@' )

process.load( "HLTrigger.HLTcore.triggerSummaryAnalyzerAOD_cfi" )

process.p = cms.Path(
    process.hltEventAnalyzerAOD       +
    process.triggerSummaryAnalyzerAOD
    )
