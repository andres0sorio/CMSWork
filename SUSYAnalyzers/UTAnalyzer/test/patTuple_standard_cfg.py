from PhysicsTools.PatAlgos.patTemplate_cfg import *

## let it run
process.p = cms.Path( process.patDefaultSequence  )



process.maxEvents.input = -1         ##  (e.g. -1 to run on all events)

#... CMSDataset
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend(['file:/scratch/aosorio/data/Skims/Run2011A/MET/FC87C9B2-BAC1-E011-B374-003048678FE4.root'] )



