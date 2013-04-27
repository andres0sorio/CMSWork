import FWCore.ParameterSet.Config as cms

maxEvents  = 100
outputFile = "uct_rate_trees.root"
inputFiles = ['dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/288CC105-8E08-E211-AF35-001D09F251FE.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/2AEC9704-8E08-E211-BC9B-001D09F24399.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/481B120E-9008-E211-AA5F-001D09F2A690.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/50D31C04-8E08-E211-817C-001D09F23D1D.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/58811A38-8D08-E211-8729-001D09F241B9.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/82EA319F-8F08-E211-BF62-0019B9F581C9.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/9CE9BE09-8E08-E211-B1D9-001D09F242EF.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/B0AF0C05-8E08-E211-A3A3-001D09F27067.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/D69FFB04-8E08-E211-92AC-001D09F24EE3.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/DA1CF39E-8F08-E211-9B6C-001D09F2905B.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/F440FA05-8E08-E211-AC3C-0015C5FDE067.root']

#high pileup run 198609 - test file

inputFiles = ['dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/005B7D4F-75CA-E111-8A54-003048D2C16E.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/06AD7CD4-70CA-E111-95E1-003048F1C836.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/0A2C434F-75CA-E111-8B2B-003048D2BE08.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/0AEEDD2A-74CA-E111-AFDC-001D09F253D4.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/0C47552B-74CA-E111-A25B-001D09F24664.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/0C89AD2C-74CA-E111-BE25-001D09F2910A.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/101BDDD3-70CA-E111-B09F-003048F118DE.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/106511D8-70CA-E111-9A1A-002481E94C7E.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/14D14D93-72CA-E111-B6ED-5404A63886C1.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/16410923-74CA-E111-966C-001D09F26509.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/198/609/18A22AD4-70CA-E111-A8C5-002481E0D958.root']

process = cms.Process("L1UCTRates")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_H_V28::All'
process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'
process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')

# UNCOMMENT THIS LINE TO RUN ON SETTINGS FROM THE DATABASE
process.es_prefer_GlobalTag = cms.ESPrefer('PoolDBESSource', 'GlobalTag')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(maxEvents)
    )

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(inputFiles)
    )

process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(outputFile)
)

# Load emulation and RECO sequences
process.load("L1Trigger.UCT2015.emulation_cfi")

# Define the tree producers

#
# EG iso
#

process.isoEGL1Rate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("l1extraParticles", "Isolated")),
    isUCT = cms.bool(False),
)
process.isoEGUCTRate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("UCT2015Producer", "IsolatedEGUnpacked")),
    isUCT = cms.bool(True),
)

#
# EG rlx
#

process.rlxEGL1Rate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(
        cms.InputTag("l1extraParticles", "NonIsolated"),
        cms.InputTag("l1extraParticles", "Isolated")
    ),
    isUCT = cms.bool(False),
)
process.rlxEGUCTRate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("UCT2015Producer", "RelaxedEGUnpacked")),
    isUCT = cms.bool(True),
)

process.p1 = cms.Path(
    process.emulationSequence *
    process.isoEGL1Rate *
    process.isoEGUCTRate *
    process.rlxEGL1Rate *
    process.rlxEGUCTRate
)

# Make the framework shut up.
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Spit out filter efficiency at the end.
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
