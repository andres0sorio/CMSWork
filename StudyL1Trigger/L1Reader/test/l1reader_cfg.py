import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

site      = os.environ.get("SITE")

#........................................................................................
if site == 'Local':
    inputfile = 'file:/opt/CMS/data/PrivateMC/Cosmic08/reco_CosmicMC_BOFF_2110.root'
else:
    inputfile = 'file:/afs/cern.ch/user/a/aosorio/scratch0/data/reco_CosmicMC_BOFF_2110.root'

#........................................................................................

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

process.load("L1Trigger.Configuration.L1Config_cff")

import L1Trigger.GlobalTrigger.gtDigis_cfi
process.l1GtEmulDigis = L1Trigger.GlobalTrigger.gtDigis_cfi.gtDigis.clone()

#.. Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

#.. reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

# L1 menu
process.load("L1TriggerConfig.L1GtConfigProducers.Luminosity.lumi1x1032.L1Menu_CRUZET200805_gr7_muon_cff")

# block GCT input and the technical triggers (only FDL and GMT active) 0x0101
process.l1GtParameters.DaqActiveBoards = 0x010d

# input tag for GMT readout collection: 
process.l1GtEmulDigis.GmtInputTag = 'gtDigis'

# Global Trigger report

import L1Trigger.GlobalTriggerAnalyzer.l1GtTrigReport_cfi
process.l1GtTrigReportData = L1Trigger.GlobalTriggerAnalyzer.l1GtTrigReport_cfi.l1GtTrigReport.clone()

process.l1GtTrigReportData.L1GtRecordInputTag = 'gtDigis'

#
import L1Trigger.GlobalTriggerAnalyzer.l1GtTrigReport_cfi
process.l1GtTrigReportEmul = L1Trigger.GlobalTriggerAnalyzer.l1GtTrigReport_cfi.l1GtTrigReport.clone()

process.l1GtTrigReportEmul.L1GtRecordInputTag = 'l1GtEmulDigis'





process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring( inputfile )
)

process.demo = cms.EDAnalyzer('L1Reader')


process.p = cms.Path(process.demo)
