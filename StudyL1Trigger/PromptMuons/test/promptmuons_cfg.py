import FWCore.ParameterSet.Config as cms

process = cms.Process("L1GtTiming")

maxevts = -1
globaltag = 'GR09_E_V6::All'
inputfile = '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/122/314/CECE0A1C-60D8-DE11-8B50-001D09F26C5C.root'

globaltag = 'GR09_P_V6::All'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/122/314/6AECB986-87D8-DE11-A470-001D09F29169.root'
inputfile = '/store/data/BeamCommissioning09/Cosmics/RECO/v2/000/123/065/2CE7286C-8FDD-DE11-B798-00304879FA4A.root'

globaltag = 'FIRSTCOLL:All'


process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( globaltag )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxevts) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(inputfile) )

process.l1gttiming = cms.EDAnalyzer('L1GtTiming',
                                    GTReadoutRcd     = cms.InputTag("gtDigis"),
                                    BitNumbers       = cms.vuint32(24,25,26,27,28,29,30,31) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo-data.root') )

process.p = cms.Path(process.l1gttiming)

#... CMSDataset 

#readFiles = cms.untracked.vstring() 
#secFiles = cms.untracked.vstring() 
#process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles) 
 
#readFiles.extend( [ 
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/E2474ED6-84DD-DE11-B46E-001D09F232B9.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/DCB06E7E-86DD-DE11-9121-0030487A18A4.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/C829B6D8-84DD-DE11-BEFF-000423D6CA42.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/983519D6-84DD-DE11-9434-001D09F2A49C.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/84E269D8-84DD-DE11-82F7-0030487D0D3A.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/5290A6EC-85DD-DE11-BBB0-001D09F29114.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/402F4EEF-85DD-DE11-89FD-001D09F231C9.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/3C455843-84DD-DE11-808F-001D09F2423B.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/2C43B3DB-84DD-DE11-B5D2-0019B9F730D2.root',
#    '/store/express/BeamCommissioning09/OfflineMonitor/FEVTHLTALL/v2/000/123/065/108BC0D9-84DD-DE11-A395-001D09F24493.root'
#    ] ) 

readFiles = cms.untracked.vstring() 
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles) 
 
readFiles.extend( [ 
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/DA95AB4C-F7DD-DE11-B1D4-000423DD2F34.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/C6F6B54F-F7DD-DE11-B5C1-000423D6CA02.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/B4C44A4F-F7DD-DE11-8896-0019B9F709A4.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/A027B44B-F7DD-DE11-948A-000423D6B48C.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/7207EA6B-F4DD-DE11-9568-001D09F248F8.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/70DAA1AE-F6DD-DE11-8FC2-000423D99896.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/623BF14C-F7DD-DE11-81BF-000423D6CA42.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/3E6ADAAE-F6DD-DE11-87D6-000423D6B5C4.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/14BFD3B2-F6DD-DE11-BD02-0030487C5CFA.root',
    '/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/151/0E45A7CE-F5DD-DE11-9B2E-001617E30CC8.root'
    ] ) 
