import FWCore.ParameterSet.Config as cms

iscosmics = False
isexpress = False
maxevts   = -1

if isexpress:
    express = 1
    gmtlabel    = 'gtDigis'
    tracklabel  = 'generalTracks'
    cosmiclabel = 'cosmicMuons'
else:
    express = 0
    gmtlabel    = 'gtDigis'
    tracklabel  = 'generalTracks'
    cosmiclabel = 'cosmicMuons'

if iscosmics:
    tracklabel  = 'ctfWithMaterialTracksP5'
    cosmiclabel = 'cosmicMuonsBarrelOnly'

globaltag = 'GR09_31X_V5P::all'
inputfile = '/store/data/Commissioning09/Cosmics/RECO/v7/000/111/664/468F19D9-C88E-DE11-8CD0-000423D987FC.root'
inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/110/958/9A4CE37D-988A-DE11-B723-000423D6CA6E.root'

globaltag = 'GR09_P_V4::All'
inputfile = '/store/data/Commissioning09/Cosmics/RECO/v9/000/119/094/FC1C2D72-C7C7-DE11-9A25-001D09F251BD.root'

globaltag = 'GR09_E_V6::All'
inputfile = '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v1/000/121/847/2AA57C7A-ABD5-DE11-A897-000423D998BA.root'

globaltag = 'GR09_P_V6::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/121/993/ECA3C304-A0D6-DE11-8BCD-0030487A18F2.root'

globaltag = 'GR09_E_V6::All'
inputfile = '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/122/294/DAC10004-33D8-DE11-BAC3-001D09F34488.root'

globaltag = 'GR09_P_V6::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/122/314/6AECB986-87D8-DE11-A470-001D09F29169.root'

globaltag = 'GR09_E_V6::All'
inputfile = '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/122/314/CECE0A1C-60D8-DE11-8B50-001D09F26C5C.root'

globaltag = 'GR09_E_V6::All'
inputfile = '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/122/498/FC2CB0C4-4DD9-DE11-88C3-000423D992DC.root'

globaltag = 'GR09_E_V7::All'
inputfile = '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/552/0A88A6E8-FEE0-DE11-BD99-000423D6C8E6.root'

globaltag = 'GR09_P_V7::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/123/552/D2A5F0AE-08E1-DE11-8E09-003048D2BE08.root'

globaltag = 'GR09_E_V7::All'
inputfile = '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/586/72D26FDF-EAE1-DE11-83AE-000423D8F63C.root'

globaltag = 'GR09_E_V7::All'
inputfile = '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/592/2A6381E7-1EE2-DE11-BECF-001D09F24664.root'

globaltag = 'GR09_E_V7::All'
inputfile = '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/596/522E8AAF-3CE2-DE11-A7A6-001D09F29114.root'

globaltag = 'GR09_P_V7::All'
inputfile = '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/123/596/7E34865F-45E2-DE11-896A-000423D98F98.root'

globaltag = 'GR09_P_V7::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/123/596/FC5C3B0F-8AE2-DE11-A905-003048D37456.root'

globaltag = 'GR09_E_V7::All'
inputfile = '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/910/4265A643-6CE5-DE11-8691-001D09F24259.root'

globaltag = 'GR09_E_V7::All'
inputfile = '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/985/44A86151-26E6-DE11-B5F2-0019B9F7312C.root'

globaltag = 'GR09_P_V7::All'
inputfile = '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/123/970/08A35B4D-1CE6-DE11-9658-000423D94A04.root'

globaltag = 'GR09_P_V7::All'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/GlobalRuns/FirstCollisions/TTUSkims/TTUMergedSkim_bit31_124024.root'

globaltag = 'GR09_31X_V5P::all'
inputfile = '/store/data/CRAFT09/Cosmics/RECO/v1/000/110/958/9A4CE37D-988A-DE11-B723-000423D6CA6E.root'

globaltag = 'GR09_31X_V5P::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/109586/TTUSkim_bit24-Bx-1_109586_0.root'

globaltag = 'GR09_P_V7::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/122294/TTUSkim_Bit25-MuBkg_122294_0.root'

globaltag = 'GR09_P_V7::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/122294/TTUSkim_Bit25-MuBkg_122294_0.root'

globaltag = 'GR10_E_V2::All'
inputfile = '/store/express/Commissioning10/ExpressMuon/FEVT/v3/000/127/476/D09095C5-1917-DF11-8F54-0030487C5CE2.root'

globaltag = 'GR10_E_V2::All'
inputfile = '/store/express/Commissioning10/OfflineMonitor/FEVTHLTALL/v3/000/128/899/06FA7555-4220-DF11-B33F-001617E30D0A.root'

globaltag = 'GR10_E_V2::All'
inputfile = '/store/express/Commissioning10/OfflineMonitor/FEVTHLTALL/v4/000/131/065/30A1BECE-8030-DF11-B631-001D09F2841C.root'

globaltag = 'GR10_E_V2::All'
inputfile = '/store/express/Commissioning10/OfflineMonitor/FEVTHLTALL/v4/000/131/300/08E20400-5332-DF11-A90F-000423D98868.root'

globaltag = 'GR10_P_V2::All'
inputfile = '/store/data/Commissioning10/Cosmics/RECO/v4/000/131/300/02369E90-8032-DF11-9CF2-001D09F2A465.root'

globaltag = 'GR10_P_V2::All'
inputfile = '/store/data/Commissioning10/Cosmics/RECO/v7/000/132/422/72BDA05E-B43B-DF11-9C46-001D09F248F8.root'

globaltag = 'GR10_P_V2::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/132440/TTUMergedSkim_bit24-31-124_132440.root'

globaltag = 'GR10_P_V2::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/132442/TTUMergedSkim_bit24-31-124_132442.root'

runid = str( 132478 )
globaltag = 'GR10_E_V4::All'
path = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/'
inputfile = path + runid + '/TTUMergedSkim_bit31-40_' + runid + '.root'

globaltag = 'GR10_P_V4::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/132601/TTUMergedSkim_bit31-40_132601.root'

globaltag = 'GR10_P_V4COS::All'
inputfile = 'rfio:/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/Apr1Skim_Muon_skim-v1/TTUMergedSkim_Inefbit31_Apr1Skim_Muon_skim-v1.root'

globaltag = 'GR10_P_V5::All'
inputfile = '/store/data/Commissioning10/MinimumBias/RECO/v9/000/135/070/A03D6655-EA59-DF11-AE13-0030487CD7B4.root'

process = cms.Process("L1GtAnalysis")

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

process.l1gtAnalyzer = cms.EDAnalyzer('L1GtTtuAnalyzer',
                                      LumiSectionA        = cms.untracked.int32(20),
                                      LumiSectionB        = cms.untracked.int32(0),
                                      RPCDigiLabel        = cms.InputTag("muonRPCDigis"),
                                      GTReadoutRcd        = cms.InputTag("gtDigis"),
                                      GMTReadoutRcd       = cms.InputTag(gmtlabel),
                                      IsStreamExpress     = cms.untracked.int32(express),
                                      L1TTEmuBitsLabel    = cms.InputTag("rpcTechnicalTrigger"),
                                      RecoMuonLabel       = cms.InputTag("muons"),
                                      RecoCosmicsLabel    = cms.InputTag(cosmiclabel),
                                      RecoTracksLabel     = cms.InputTag(tracklabel),
                                      RecoSiStripLabel    = cms.InputTag("siStripClusters"),
                                      RecoPixelLabel      = cms.InputTag("siPixelClusters"),
                                      TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                                      MuonPtCut           = cms.untracked.double(0.0),
                                      BitNumbers          = cms.vuint32(24,25,26,27,28,29,30,31),
                                      BitCollisions       = cms.vuint32(3,4,9,40,41),
                                      CheckHLTPaths       = cms.vstring("HLT_Activity_DT"),
                                      ProcessName         = cms.untracked.string("HLT"),
                                      ReadRpcTTEmuBits    = cms.untracked.int32(0),
                                      SelectFilter        = cms.untracked.int32(1),
                                      MaxNBx              = cms.untracked.int32(0),
                                      MinBxNum            = cms.untracked.int32(110),
                                      MaxBxNum            = cms.untracked.int32(160),
                                      BxWindow            = cms.untracked.int32(0),
                                      EventWindow         = cms.untracked.int32(10),
                                      UseCompression      = cms.untracked.int32(1),
                                      WriteMode           = cms.untracked.int32(1), 
                                      Precision           = cms.untracked.int32(6),
                                      MaxRate             = cms.untracked.int32(250),
                                      MaxPt               = cms.untracked.double(40.0),
                                      TrackerLength       = cms.untracked.double(120.0),
                                      TrackerHeight       = cms.untracked.double(100.0),
                                      MakeCoincidenceTT   = cms.vuint32(40,41),
                                      MakeCoincidenceAlgo = cms.vuint32(124) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo-data.root') )

process.load("FWCore.MessageService.MessageLogger_cfi")

process.p = cms.Path(process.l1gtAnalyzer)

