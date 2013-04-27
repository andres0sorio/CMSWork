import FWCore.ParameterSet.Config as cms

process = cms.Process("Hoanalysis")

inputFile = 'file:particle_gun_test.root'
inputFile = 'file:ho2default-config.root'
maxEvents = 500

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Geometry.CaloEventSetup.CaloGeometry_cfi")
process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

# CMSSW 5 MC
process.GlobalTag.globaltag = 'START53_V18PR::All'
process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'
process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')
print "Using global tag for 53X data: %s" % process.GlobalTag.globaltag
    
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxEvents ) )

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring( inputFile ) )

process.hoanalysis = cms.EDAnalyzer('HcalAnalyzerAO',
                                    hoRechits = cms.InputTag("horeco"),
                                    hoDigis = cms.InputTag("horeco"),
                                    muon = cms.InputTag("muons"),
                                    rpctDigis = cms.InputTag("simRpcTriggerDigis","RPCb"),
                                    )

process.TFileService = cms.Service("TFileService",fileName = cms.string('histo.root') )

process.p = cms.Path(process.hoanalysis)

