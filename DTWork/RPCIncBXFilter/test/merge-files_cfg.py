import FWCore.ParameterSet.Config as cms
import os

maxevts   =  -1
globaltag = 'START38_V12::All'
inputfile = 'file:/scratch/aosorio/data/HSCPs/stau308/step2_RAW2DIGI_L1Reco_RECO_VALIDATION.root'

process   = cms.Process("Merger")

#.. Geometry and Global Tags
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring( inputfile ) )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('HSCPsEvents.root'),
                               outputCommands = cms.untracked.vstring('keep *') )

process.e = cms.EndPath(process.out)

#... CMSDataset
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [ 'file:/scratch/aosorio/gangadir/workspace/aosorio/LocalXML/10/0/output/step2_RAW2DIGI_L1Reco_RECO.root','file:/scratch/aosorio/gangadir/workspace/aosorio/LocalXML/10/1/output/step2_RAW2DIGI_L1Reco_RECO.root','file:/scratch/aosorio/gangadir/workspace/aosorio/LocalXML/10/2/output/step2_RAW2DIGI_L1Reco_RECO.root','file:/scratch/aosorio/gangadir/workspace/aosorio/LocalXML/10/3/output/step2_RAW2DIGI_L1Reco_RECO.root','file:/scratch/aosorio/gangadir/workspace/aosorio/LocalXML/10/4/output/step2_RAW2DIGI_L1Reco_RECO.root'] )
