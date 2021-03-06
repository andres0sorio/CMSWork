### Generated by ConfigEditor ###
import sys
import os.path
sys.path.append(os.path.abspath(os.path.expandvars(os.path.join('$CMSSW_BASE','src/SUSYAnalyzers/UTAnalyzer/test'))))
sys.path.append(os.path.abspath(os.path.expandvars(os.path.join('$CMSSW_RELEASE_BASE','src/SUSYAnalyzers/UTAnalyzer/test'))))
### ------------------------- ###

from patTuple_standard_cfg import *

### Generated by ConfigEditor ###
if hasattr(process,'resetHistory'): process.resetHistory()
### ------------------------- ###

from PhysicsTools.PatAlgos.tools.coreTools import *


from PhysicsTools.PatAlgos.tools.metTools import *


from PhysicsTools.PatAlgos.tools.trigTools import *


removeMCMatching(process , ['All'], '', True)

removeAllPATObjectsBut(process , ['Muons'], True)
process.patMuons.muonSource = cms.InputTag("muonsSkim")

removeCleaning(process , True, '')
process.patMuons.embedPickyMuon = cms.bool(False)
process.patMuons.embedPFCandidate = cms.bool(False)
process.patMuons.embedTcMETMuonCorrs = cms.bool(False)
process.patMuons.embedTpfmsMuon = cms.bool(False)
process.patMuons.embedCaloMETMuonCorrs = cms.bool(False)

addPfMET(process , 'PF')

switchOnTrigger(process , 'patTrigger', 'patTriggerEvent', 'patDefaultSequence', 'HLT', 'out')

#... CMSDataset
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend(['file:/scratch/aosorio/data/Skims/Run2011A/MET/FC87C9B2-BAC1-E011-B374-003048678FE4.root'] )

