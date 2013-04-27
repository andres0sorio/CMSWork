# Auto generated configuration file
# using: 
# Revision: 1.381.2.13 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/Generator/python/SingleMuPt100_cfi.py -s GEN,SIM,DIGI,L1,DIGI2RAW,RAW2DIGI,RECO --conditions START53_V18PR::All -n 100 --no_exec --eventcontent FEVT
import FWCore.ParameterSet.Config as cms

## Input parameters

seed = 1
maxEvents = 500
outputFile = "particle_gun_test.root"

pdgId  =  13
minEt  =  100.0
maxEt  =  105.0

#minEta = 0.000
#maxEta = 0.087
#minPhi = 0.742
#maxPhi = 0.829

minEta = -1.2
maxEta = 1.2

minPhi = -3.1415
maxPhi = 3.1415

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( maxEvents ) )

# Random Seed
process.RandomNumberGeneratorService.generator.initialSeed = seed

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('Configuration/Generator/python/SingleMuPt100_cfi.py nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.FEVToutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.FEVTEventContent.outputCommands,
    fileName = cms.untracked.string( outputFile ),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V18PR::All', '')

process.generator = cms.EDProducer("FlatRandomPtGunProducer",
    PGunParameters = cms.PSet(
        MaxPt = cms.double(maxEt),
        MinPt = cms.double(minEt),
        PartID = cms.vint32(pdgId),
        MaxEta = cms.double(maxEta),
        MaxPhi = cms.double(maxPhi),
        MinEta = cms.double(minEta),
        MinPhi = cms.double(minPhi)
    ),
    Verbosity = cms.untracked.int32(0),
    psethack = cms.string('single mu pt 100'),
    AddAntiParticle = cms.bool(False),
    firstRun = cms.untracked.uint32(1)
)

## HO Specific
process.simHcalUnsuppressedDigis.useOldHO = cms.bool(False)
process.simHcalUnsuppressedDigis.ho.siPMCode = cms.int32(1)
process.simHcalUnsuppressedDigis.ho.pixels = cms.int32(2500)
process.simHcalUnsuppressedDigis.ho.photoelectronsToAnalog = cms.vdouble([3.0]*16)

# turn off zero suppression
process.simHcalDigis.HBlevel = -1000
process.simHcalDigis.HElevel = -1000
process.simHcalDigis.HOlevel = -1000

#use hardcoded gains
process.es_hardcode.toGet.extend(['Gains', 'Pedestals', 'PedestalWidths'])
process.es_prefer_hcalHardcode = cms.ESPrefer("HcalHardcodeCalibrations", "es_hardcode")


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)

process.FEVToutput.outputCommands += cms.untracked.vstring('keep *_*_RPCb_*')

process.FEVToutput_step = cms.EndPath(process.FEVToutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step,process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.FEVToutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

