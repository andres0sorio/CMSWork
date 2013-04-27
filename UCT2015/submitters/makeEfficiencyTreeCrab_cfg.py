'''

Generate trees for measuring and comparing L1 and UCT efficiencies with
respect to RECO objects.

Usage:

    ./makeEfficiencyTree_cfg.py

Optional arguments:

    inputFiles=myFile.root outputFile=outputFile.root maxEvents=-1

Authors: L. Dodd, N. Woods, I. Ojalvo, S. Dasu, M. Cepeda, E. Friis (UW Madison)

'''

import FWCore.ParameterSet.Config as cms

#default options
maxEvents  = -1
outputFile = "uct_efficiency_tree.root"

# ZElectron / DiTau samples

inputFiles = ['dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/FEFAB941-45FB-E111-A767-00261894392F.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/FE83CD5F-ADFB-E111-800A-002618943945.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/FCF9556D-3FFB-E111-91C6-0018F3D096D2.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/FCAA19FC-B8FB-E111-A027-003048678D52.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/F8C58B7E-3FFB-E111-8640-002618943978.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/F4730B9E-0EFC-E111-A883-00261894387A.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/F2AE2B2F-39FB-E111-93D9-0018F3D09628.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/F0976F04-B6FB-E111-83DD-001A928116F0.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/EED6477F-D604-E211-A255-003048679000.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/EC3A205E-3FFB-E111-AE0A-0018F3D09612.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/EAE46676-E5FD-E111-9839-00248C0BE018.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/EA18AA47-86FB-E111-9799-002618943924.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/E6BDA02C-22FC-E111-B56E-003048679046.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/DECDB5C3-3CFB-E111-91AB-002618943852.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/DECBC401-38FB-E111-A9B8-0026189438EF.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/DCC698AD-8CFB-E111-8E91-002618943809.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/D8524D5F-A3FB-E111-AC65-001A92971B94.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/ZElectron-24Aug2012-v1/00000/D6DFF9B3-8AFB-E111-B77A-00261894388F.root']


inputFiles = ['dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/913/00000/EA0352B8-FFCE-E111-B710-002618943986.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/910/00000/F676BB4A-94CE-E111-946D-002618943860.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/898/00000/8AD21B19-FECD-E111-A392-0026189438DC.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/860/00000/D846D0C4-AECD-E111-A99F-002618943959.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/859/00000/D6179E96-AECD-E111-AB16-0018F3D09702.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/856/00000/FC09367D-AECD-E111-A3F4-0018F3D09680.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/846/00000/BA5E3BDC-87CD-E111-8827-002618943922.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/791/00000/061B2035-1FCD-E111-8A5C-0026189438CB.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/765/00000/3645E79D-F4CC-E111-8C4C-0018F3D09676.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/748/00000/C0908038-F5CC-E111-B4B9-003048678B94.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/744/00000/BE28B9B5-EFCC-E111-990C-002618943905.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/722/00000/BEE15FC9-EFCC-E111-87BF-002618943905.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/720/00000/DC637D41-ECCC-E111-AF7E-003048678E8A.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/719/00000/F0E792D0-EBCC-E111-8B07-0030486791AA.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/713/00000/689ED013-D3CC-E111-932B-002618943981.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/523/00000/A8414D45-11CB-E111-8F66-0018F3D09620.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/522/00000/F0B2B688-AACB-E111-A24E-0026189438A7.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/522/00000/501B998D-AACB-E111-B8C2-002618FDA263.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/522/00000/4E927BB8-AACB-E111-B7BC-003048679084.root',
              'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/DoubleElectron/RAW-RECO/DiTau-PromptSkim-v2/000/198/522/00000/4A7D9B9D-AACB-E111-93E6-00248C55CC9D.root']

inputFiles = [ 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/755/00000/3CDA1DFB-9B0A-E211-BDEB-90E6BA442F21.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/754/00000/2A23F4B9-930A-E211-91DD-001EC9D7FF5F.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/742/00000/1E2ECBEB-1C0B-E211-B416-00259073E478.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/739/00000/866D5CC9-1A0B-E211-97D3-001EC9D2577D.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/739/00000/58094F11-1D0B-E211-90C8-485B39800BC8.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/738/00000/F27622A4-960A-E211-AD0A-20CF305B051B.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/724/00000/A0423213-AE09-E211-A7E1-00259073E4E6.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/718/00000/F2486A00-AE09-E211-8455-00259073E4E6.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/712/00000/18B12274-AD09-E211-B606-E0CB4E29C4F7.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/709/00000/B25B60BD-F509-E211-85AA-90E6BA0D09CA.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/682/00000/50BD5BF5-A909-E211-9B12-E0CB4E29C50E.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/648/00000/F814B3B6-AA09-E211-943E-485B39800BDE.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/599/00000/AEF1D3DB-A909-E211-874A-90E6BAE8CC18.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/597/00000/6432202A-AA09-E211-B8A2-0025907277A0.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/584/00000/A053B3BC-B408-E211-8D5F-E0CB4E29C502.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/560/00000/0A688BD7-AC08-E211-A18A-90E6BA19A25E.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/556/00000/704474FF-AE08-E211-867D-E0CB4EA0A904.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/545/00000/2660880A-AF08-E211-9108-001EC9D7F21F.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/542/00000/B20F5BF8-AD08-E211-937E-001EC9D7F21F.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/534/00000/08749653-AD08-E211-9B43-001EC9D2422F.root',
               'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/SingleMu/RAW-RECO/MuTau-PromptSkim-v3/000/203/530/00000/F89C436D-A508-E211-91EB-00259073E3FC.root' ]




eicIsolationThreshold = 3

#options.register(
#    'eicIsolationThreshold',
#    3,
#    VarParsing.multiplicity.singleton,
#    VarParsing.varType.int,
#    "EIC Isolation threshold")

process = cms.Process("L1UCTEfficiency")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_H_V28::All'
process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'
process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')

# UNCOMMENT THIS LINE TO RUN ON SETTINGS FROM THE DATABASE
# process.es_prefer_GlobalTag = cms.ESPrefer('PoolDBESSource', 'GlobalTag')

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
process.load("L1Trigger.UCT2015.recoObjects_cfi")

# Common branches to add to the ntuple
common_ntuple_branches = cms.PSet(
    index = cms.string("index"), # Index of reco object in the event
    nRecoObjects = cms.string("nTotalObjects"), # Number of reco objects in the event
    nPVs = cms.string("nPVs"), # number of reco'ed vertices in the event

    # Run, lumi, event number
    run = cms.string("id.run"),
    lumi = cms.string("id.luminosityBlock"),
    evt = cms.string("id.event"),

    recoPt = cms.string("reco.pt"),
    recoEta = cms.string("reco.eta"),
    recoPhi = cms.string("reco.phi"),

    # Whether there exists a L1/UCT object matched to reco
    l1Match = cms.string("l1Match"),
    l1gMatch = cms.string("l1gMatch"),

    l1Pt = cms.string("? l1Match ? l1.pt : 0"),
    l1Eta = cms.string("? l1Match ? l1.eta : 0"),
    l1Phi = cms.string("? l1Match ? l1.phi : 0"),


    # TODO add L1extra eta/phi indices

    l1DPhi = cms.string("? l1Match ? deltaPhi(l1.phi, reco.phi) : -1"),
    l1DR = cms.string("? l1Match ? deltaR(l1.eta, l1.phi, reco.eta, reco.phi) : -1"),

    l1gPt = cms.string("? l1gMatch ? l1g.pt : 0"),
    l1gEta = cms.string("? l1gMatch ? l1g.eta : 0"),
    l1gPhi = cms.string("? l1gMatch ? l1g.phi : 0"),

    # For tuning isolation and PU subtraction
    l1gPU = cms.string("? l1gMatch ? l1g.puLevel : -2"),
    l1gRegionEt = cms.string("? l1gMatch ? l1g.associatedRegionEt : -2"),
    l1gJetPt = cms.string("? l1gMatch ? l1g.associatedJetPt : -2"),
    l1gEllIso = cms.string("? l1gMatch ? l1g.ellIsolation : -2"),
    l1gTauVeto = cms.string("? l1gMatch ? l1g.tauVeto : -2"),
    l1gMIP = cms.string("? l1gMatch ? l1g.mipBit : -2"),

    l1gEtaCode = cms.vstring("? l1gMatch ? l1g.etaIndex : 0", "I"),
    l1gPhiCode = cms.vstring("? l1gMatch ? l1g.phiIndex : 0", "I"),

    l1gDPhi = cms.string("? l1gMatch ? deltaPhi(l1g.phi, reco.phi) : -1"),
    l1gDR = cms.string("? l1gMatch ? deltaR(l1g.eta, l1g.phi, reco.eta, reco.phi) : -1"),
)

# Keep track of electron isolation values
electron_branches = cms.PSet(
    dr03TkSumPt  = cms.string("reco.dr03TkSumPt"),
    dr03EcalRecHitSumEt  = cms.string("reco.dr03EcalRecHitSumEt"),
    dr03HcalTowerSumEt  = cms.string("reco.dr03HcalTowerSumEt"),
    dr03CombinedEt  = cms.string("reco.dr03TkSumPt + reco.dr03EcalRecHitSumEt + reco.dr03HcalTowerSumEt"),
)

# Keep track of information about the ECAL/HCAL composition of taus
tau_branches = cms.PSet(
    emFraction = cms.string("reco.emFraction"),
    decayMode = cms.string("reco.decayMode"),
    # EK - as far as I can tell, this does not use the lead track at all
    hcal = cms.string("reco.hcalTotOverPLead"),
)

# Define the tree producers
process.isoTauEfficiency = cms.EDAnalyzer(
    "EfficiencyTree",
    recoSrc = cms.VInputTag("recoTaus"),
    l1Src = cms.VInputTag(cms.InputTag("l1extraParticles", "Tau")),
    l1GSrc = cms.VInputTag(cms.InputTag("UCT2015Producer", "IsolatedTauUnpacked")),
    l1GPUSrc = cms.InputTag("UCT2015Producer", "PULevel"),
    # Max DR for RECO-trigger matching
    maxDR = cms.double(0.5),
    # Ntuple configuration
    ntuple = cms.PSet(
        common_ntuple_branches,
        tau_branches,
    )
)
# Define the tree producers
process.rlxTauEfficiency = cms.EDAnalyzer(
    "EfficiencyTree",
    recoSrc = cms.VInputTag("recoTaus"),
    l1Src = cms.VInputTag(cms.InputTag("l1extraParticles", "Tau")),
    l1GSrc = cms.VInputTag(cms.InputTag("UCT2015Producer", "RelaxedTauUnpacked")),
    l1GPUSrc = cms.InputTag("UCT2015Producer", "PULevel"),
    # Max DR for RECO-trigger matching
    maxDR = cms.double(0.5),
    # Ntuple configuration
    ntuple = cms.PSet(
        common_ntuple_branches,
        tau_branches,
    )
)

# Note that the input electron collection is not isolated, this needs to be done
# at the ntuple level.
process.isoEGEfficiency = cms.EDAnalyzer(
    "EfficiencyTree",
    recoSrc = cms.VInputTag("recoElecs"),
    l1Src = cms.VInputTag(cms.InputTag("l1extraParticles", "Isolated")),
    l1GSrc = cms.VInputTag(cms.InputTag("UCT2015Producer", "IsolatedEGUnpacked")),
    l1GPUSrc = cms.InputTag("UCT2015Producer", "PULevel"),
    # Max DR for RECO-trigger matching
    maxDR = cms.double(0.5),
    # Ntuple configuration
    ntuple = cms.PSet(
        common_ntuple_branches,
        electron_branches,
    )
)

process.rlxEGEfficiency = cms.EDAnalyzer(
    "EfficiencyTree",
    recoSrc = cms.VInputTag("recoElecs"),
    l1Src = cms.VInputTag(
        # These two collections
        cms.InputTag("l1extraParticles", "NonIsolated"),
        cms.InputTag("l1extraParticles", "Isolated"),
    ),
    l1GSrc = cms.VInputTag(cms.InputTag("UCT2015Producer", "RelaxedEGUnpacked")),
    l1GPUSrc = cms.InputTag("UCT2015Producer", "PULevel"),
    # Max DR for RECO-trigger matching
    maxDR = cms.double(0.5),
    # Ntuple configuration
    ntuple = cms.PSet(
        common_ntuple_branches,
        electron_branches,
    )
)

# So we can compare relaxed UCT + ntuple isolation cuts versus stock L1 IsoEG
process.rlxUCTisoL1EGEfficiency = cms.EDAnalyzer(
    "EfficiencyTree",
    recoSrc = cms.VInputTag("recoElecs"),
    l1Src = cms.VInputTag(
        cms.InputTag("l1extraParticles", "Isolated"),
    ),
    l1GSrc = cms.VInputTag(cms.InputTag("UCT2015Producer", "RelaxedEGUnpacked")),
    l1GPUSrc = cms.InputTag("UCT2015Producer", "PULevel"),
    # Max DR for RECO-trigger matching
    maxDR = cms.double(0.5),
    # Ntuple configuration
    ntuple = cms.PSet(
        common_ntuple_branches,
        electron_branches,
    )
)

process.jetEfficiency = cms.EDAnalyzer(
    "EfficiencyTree",
    recoSrc = cms.VInputTag("recoJets"),
    l1Src = cms.VInputTag(
        # Combine central jets + tau + forward jets
        cms.InputTag("l1extraParticles", "Central"),
        cms.InputTag("l1extraParticles", "Tau"),
        cms.InputTag("l1extraParticles", "Forward"),
    ),
    l1GSrc = cms.VInputTag(cms.InputTag("UCT2015Producer", "JetUnpacked")),
    l1GPUSrc = cms.InputTag("UCT2015Producer", "PULevel"),
    # Max DR for RECO-trigger matching
    maxDR = cms.double(0.5),
    # Ntuple configuration
    ntuple = cms.PSet(
        common_ntuple_branches,
    )
)
process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.p1 = cms.Path(
    process.recoObjects *
    process.emulationSequence *
    #process.dump *
    process.isoTauEfficiency *
    process.rlxTauEfficiency *
    process.isoEGEfficiency *
    process.rlxEGEfficiency *
    process.rlxUCTisoL1EGEfficiency *
    process.jetEfficiency
)

################################################################################
###  Semileptonic ttbar skim for sums ###########################################
################################################################################

process.oneMuon = cms.EDFilter(
    "CandViewCountFilter",
    src = cms.InputTag("tightMuons"),
    minNumber = cms.uint32(1),
)

process.jetsPt30 = cms.EDFilter(
    "PFJetSelector",
    src = cms.InputTag("ak5PFJetsNOMuons"),
    filter = cms.bool(True),
    cut = cms.string("pt > 30")
)

process.atLeastThreeJets = cms.EDFilter(
    "CandViewCountFilter",
    src = cms.InputTag("jetsPt30"),
    minNumber = cms.uint32(3),
)

# Computing CaloMET significance
process.load("RecoMET.METProducers.CaloMETSignif_cfi")
process.metsignificance.noHF = True

# Computing RECO level Sum ET and Sum HT
process.load("L1Trigger.UCT2015.PFSumET_cfi")

process.l1SumsEfficiency = cms.EDAnalyzer(
    "SumsEfficiencyTree",
    l1MHTSrc = cms.InputTag("l1extraParticles", "MHT"),
    l1METSrc = cms.InputTag("l1extraParticles", "MET"),
    l1METSigSrc = cms.InputTag("UCT2015Producer", "METSIGUnpacked"),
    # fixme
    l1SHTSrc = cms.InputTag("l1extraParticles", "MHT"),
    l1SETSrc = cms.InputTag("l1extraParticles", "MET"),
    recoMHTSrc = cms.InputTag("htMetAK5"),
    recoMETSrc = cms.InputTag("metNoHF"), # calomet
    recoMETSigSrc = cms.InputTag("metsignificance"), # calomet
    recoSHTSrc = cms.InputTag("pfSumET", "sht"),
    recoSETSrc = cms.InputTag("pfSumET", "set"),
)
process.uctSumsEfficiency = cms.EDAnalyzer(
    "SumsEfficiencyTree",
    l1MHTSrc = cms.InputTag("UCT2015Producer", "MHTUnpacked"),
    l1METSrc = cms.InputTag("UCT2015Producer", "METUnpacked"),
    l1METSigSrc = cms.InputTag("UCT2015Producer", "METSIGUnpacked"),
    l1SHTSrc = cms.InputTag("UCT2015Producer", "SHTUnpacked"),
    l1SETSrc = cms.InputTag("UCT2015Producer", "SETUnpacked"),

    recoMHTSrc = cms.InputTag("htMetAK5"),
    recoMETSrc = cms.InputTag("metNoHF"), # calomet
    recoMETSigSrc = cms.InputTag("metsignificance"), # calomet
    recoSHTSrc = cms.InputTag("pfSumET", "sht"),
    recoSETSrc = cms.InputTag("pfSumET", "set"),
)

# Make a version of UCT without PU corrections.
process.UCT2015ProducerNoPU = process.UCT2015Producer.clone(
    puCorrect = False
)
process.uctSumsNoPUEfficiency = process.uctSumsEfficiency.clone(
    l1MHTSrc = cms.InputTag("UCT2015ProducerNoPU", "MHTUnpacked"),
    l1METSrc = cms.InputTag("UCT2015ProducerNoPU", "METUnpacked"),
    l1METSigSrc = cms.InputTag("UCT2015ProducerNoPU", "METSIGUnpacked"),
    l1SHTSrc = cms.InputTag("UCT2015ProducerNoPU", "SHTUnpacked"),
    l1SETSrc = cms.InputTag("UCT2015ProducerNoPU", "SETUnpacked"),
)

process.semileptonicTTBarPath = cms.Path(
    process.cleanJets *
    process.oneMuon *
    process.jetsPt30 *
    process.atLeastThreeJets *
    process.pfSumET *
    process.metsignificance *
    process.l1SumsEfficiency *
    process.uctSumsEfficiency *
    # w/o PU corrections
    process.UCT2015ProducerNoPU *
    process.uctSumsNoPUEfficiency
)

process.schedule = cms.Schedule(
    process.p1,
    process.semileptonicTTBarPath
)

# Make the framework shut up.
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Spit out filter efficiency at the end.
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

eic = eicIsolationThreshold
print "Setting EIC threshold to %i" % eic
process.RCTConfigProducers.eicIsolationThreshold = eic
