import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

pathtodata='/afs/cern.ch/user/a/aosorio/scratch0/data/'

infile= 'file:'+pathtodata+'TauolaTTbar-Summer08_IDEAL_V9_v1-GEN-SIM-RECO-10ev.root'

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring( infile )
)

process.demo = cms.EDAnalyzer('ZPlotsAnalyzer'
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo.root')
)

process.p = cms.Path(process.demo)
