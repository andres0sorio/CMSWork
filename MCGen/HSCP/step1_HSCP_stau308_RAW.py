# Auto generated configuration file
# using: 
# Revision: 1.194 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/PYTHIA6_Exotica_HSCP_stau308_paironly_cfg.py -s GEN,SIM,DIGI,L1,DIGI2RAW,HLT:GRun --conditions START38_V12::All --datatier GEN-SIM-RAW --eventcontent RAWSIM --no_exec --customise Configuration/GenProduction/Exotica_HSCP_SIM_cfi.py
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('Configuration.StandardSequences.VtxSmearedRealistic7TeVCollision_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.194 $'),
    annotation = cms.untracked.string('Configuration/GenProduction/python/PYTHIA6_Exotica_HSCP_stau308_paironly_cfg.py nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)
process.options = cms.untracked.PSet(

)
# Input source
process.source = cms.Source("EmptySource")

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('step1_HSCP_RAW.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RAW'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'START38_V12::All'
process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    stopHadrons = cms.bool(False),
    filterEfficiency = cms.untracked.double(1.0),
    comEnergy = cms.double(7000.0),
    crossSection = cms.untracked.double(-1),
    maxEventsToPrint = cms.untracked.int32(0),
    gluinoHadrons = cms.bool(False),
    PythiaParameters = cms.PSet(
        pythiaUESettings = cms.vstring('MSTU(21)=1     ! Check on possible errors during program execution', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'PARP(82)=1.832 ! pt cutoff for multiparton interactions', 
            'PARP(89)=1800. ! sqrts for which PARP82 is set', 
            'PARP(90)=0.275 ! Multiple interactions: rescaling power', 
            'MSTP(95)=6     ! CR (color reconnection parameters)', 
            'PARP(77)=1.016 ! CR', 
            'PARP(78)=0.538 ! CR', 
            'PARP(80)=0.1   ! Prob. colored parton from BBR', 
            'PARP(83)=0.356 ! Multiple interactions: matter distribution parameter', 
            'PARP(84)=0.651 ! Multiple interactions: matter distribution parameter', 
            'PARP(62)=1.025 ! ISR cutoff', 
            'MSTP(91)=1     ! Gaussian primordial kT', 
            'PARP(93)=10.0  ! primordial kT-max', 
            'MSTP(81)=21    ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model'),
        processParameters = cms.vstring('MSEL=0                  ! full user control ', 
            'MSUB(207)=1             ! stau-staubar', 
            'IMSS(1) = 11             ! Spectrum from external SLHA file', 
            'IMSS(21) = 33            ! LUN number for SLHA File (must be 33)', 
            'IMSS(22) = 33            ! Read-in SLHA decay table ', 
            'MDCY(C1000015,1)=0       ! set the stau stable.'),
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters', 
            'SLHAParameters'),
        SLHAParameters = cms.vstring('SLHAFILE = SimG4Core/CustomPhysics/data/isa-slha308GeV.out')
    ),
    hscpFlavor = cms.untracked.string('stau'),
    massPoint = cms.untracked.int32(308),
    slhaFile = cms.untracked.string('SimG4Core/CustomPhysics/data/isa-slha308GeV.out'),
    processFile = cms.untracked.string('SimG4Core/CustomPhysics/data/RhadronProcessList.txt'),
    particleFile = cms.untracked.string('SimG4Core/CustomPhysics/data/particles_stau_308_GeV.txt')
)
process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.out_step])
# special treatment in case of production filter sequence  
for path in process.paths: 
    getattr(process,path)._seq = process.ProductionFilterSequence*getattr(process,path)._seq


# Automatic addition of the customisation function

def customise(process):
    
	FLAVOR = process.generator.hscpFlavor.value()
	MASS_POINT = process.generator.massPoint.value()
	SLHA_FILE = process.generator.slhaFile.value()
	PROCESS_FILE = process.generator.processFile.value()
	PARTICLE_FILE = process.generator.particleFile.value()
	

	process.load("SimG4Core.CustomPhysics.CustomPhysics_cfi")
	process.customPhysicsSetup.particlesDef = PARTICLE_FILE

        process.g4SimHits.Watchers = cms.VPSet (
            cms.PSet(
            type = cms.string('RHStopTracer'),
            RHStopTracer = cms.PSet(
            verbose = cms.untracked.bool (False),
            traceParticle = cms.string ("(~|tau1).*"),
            stopRegularParticles = cms.untracked.bool (False)
            )        
            )
            )

	
	if FLAVOR=="gluino" or FLAVOR=="stop":
		process.customPhysicsSetup.processesDef = PROCESS_FILE
		process.g4SimHits.Physics = cms.PSet(
        process.customPhysicsSetup,
        DummyEMPhysics = cms.bool(True),
        G4BremsstrahlungThreshold = cms.double(0.5), ## cut in GeV    
        DefaultCutValue = cms.double(1.), ## cuts in cm,default 1cm    
        CutsPerRegion = cms.bool(True),
        Verbosity = cms.untracked.int32(0),
        type = cms.string('SimG4Core/Physics/CustomPhysics'),
        EMPhysics   = cms.untracked.bool(True),  ##G4 default true
        HadPhysics  = cms.untracked.bool(True),  ##G4 default true
        FlagBERT    = cms.untracked.bool(False),
        FlagCHIPS   = cms.untracked.bool(False),
        FlagFTF     = cms.untracked.bool(False),
        FlagGlauber = cms.untracked.bool(False),
        FlagHP      = cms.untracked.bool(False),
        GFlash = cms.PSet(
        GflashHistogram = cms.bool(False),
        GflashEMShowerModel = cms.bool(False),
        GflashHadronPhysics = cms.string('QGSP_BERT_EMV'),
        GflashHadronShowerModel = cms.bool(False)
        )
        )
		process.g4SimHits.G4Commands = cms.vstring('/tracking/verbose 1')

	elif FLAVOR =="stau":
		process.g4SimHits.Physics = cms.PSet(
        process.customPhysicsSetup,
        DummyEMPhysics = cms.bool(True),
        G4BremsstrahlungThreshold = cms.double(0.5), ## cut in GeV    
        DefaultCutValue = cms.double(1.), ## cuts in cm,default 1cm    
        CutsPerRegion = cms.bool(True),
        Verbosity = cms.untracked.int32(0),
        type = cms.string('SimG4Core/Physics/CustomPhysics'),
        )
		process.g4SimHits.G4Commands = cms.vstring('/tracking/verbose 1')
	
	else:
		print "Wrong flavor %s. Only accepted are gluino, stau, stop." % FLAVOR

	return process
	


# End of customisation function definition

process = customise(process)
