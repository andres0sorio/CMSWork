import FWCore.ParameterSet.Config as cms

process = cms.Process("DTSeg2DAnalyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.CommonDetUnit.globalTrackingGeometry_cfi")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.load("RecoMuon.TrackingTools.MuonServiceProxy_cff")

process.GlobalTag.globaltag = 'START42_V11::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

filename ='file:/scratch/aosorio/data/HSCPs/stop800/step2_HSCP_DeltaRej_RECO.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( filename ) )

process.dtsegs = cms.EDAnalyzer('DTRecSeg2DAnalysis',
                                TrackLabel = cms.InputTag("globalMuons"),
                                MuonLabel = cms.InputTag("muons"),
                                DTsegmentsLabel = cms.InputTag("dt4DSegments"),
                                partLabel = cms.InputTag("generator"),
                                #muones
                                MCPartIds = cms.untracked.vint32(13),
				#HSCPs
				#MCPartIds = cms.untracked.vint32(1000612,1000632,1000652,1006211,1006213,1006223,1006321,1006323),
                                ServiceParameters = cms.PSet( Propagators = cms.untracked.vstring('SteppingHelixPropagatorAny', 
                                                                                                  'PropagatorWithMaterial', 
                                                                                                  'PropagatorWithMaterialOpposite'),
                                                              RPCLayers = cms.bool(True) ),
                                MatchParameters = cms.PSet( DTsegments = cms.InputTag("dt4DSegments"),
                                                            DTradius = cms.double(0.01),
                                                            CSCsegments = cms.InputTag("cscSegments"),
                                                            TightMatchDT = cms.bool(False),
                                                            TightMatchCSC = cms.bool(True) )
                                )


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('HSCP-stops-histos.root')  )

process.p = cms.Path( process.dtsegs )

