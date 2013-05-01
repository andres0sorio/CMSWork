import FWCore.ParameterSet.Config as cms

#from L1Trigger.UCT2015.emulation_cfi

#from Configuration.StandardSequences.Geometry_cff import *
from Configuration.Geometry.GeometryIdeal_cff import *
from Configuration.StandardSequences.RawToDigi_Data_cff import *
from L1Trigger.UCT2015.Lut import *

# Modify the HCAL TPGs according to the proposed HTR modification.  If the HCAL
# is above a given energy threshold, set the MIP bit.
hackHCALMIPs = cms.EDProducer(
    "HcalTpgMipEmbedder",
    src = cms.InputTag("hcalDigis"),
    threshold = cms.double(3), # In GeV
    rawThreshold = cms.uint32(3), # In TPG rank
    cutOnRawBits = cms.bool(False), # What to cut on
)

uctDigis = cms.EDProducer(
    "L1RCTProducer",
    #hcalDigis = cms.VInputTag(cms.InputTag("hcalDigis")),
    hcalDigis = cms.VInputTag(cms.InputTag("hackHCALMIPs")),
    useEcal = cms.bool(True),
    useHcal = cms.bool(True),
    ecalDigis = cms.VInputTag(cms.InputTag("ecalDigis:EcalTriggerPrimitives")),
    BunchCrossings = cms.vint32(0),
    getFedsFromOmds = cms.bool(False),
    queryDelayInLS = cms.uint32(10),
    queryIntervalInLS = cms.uint32(100)#,
)

uctDigiStep = cms.Sequence(
    # Only do the digitization of objects that we care about
    #RawToDigi
    gctDigis
    * gtDigis
    * ecalDigis
    * hcalDigis
)

uctEmulatorStep = cms.Sequence( hackHCALMIPs * uctDigis )

emulationSequence = cms.Sequence(uctDigiStep * uctEmulatorStep)
