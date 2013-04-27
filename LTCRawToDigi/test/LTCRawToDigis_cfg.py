#
# cfg file to unpack FED LTC DAQ record
#

import FWCore.ParameterSet.Config as cms

# process
process = cms.Process("TestLTCUnpacker")

# number of events to be processed and source file
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

inputfile = 'rfio:/castor/cern.ch/cms/store/data/PrivMuon/A/000/099/645/PrivMuon.00099645.0001.A.storageManager.00.0000.dat'

process.source = cms.Source ('NewEventStreamFileReader', fileNames = cms.untracked.vstring ( inputfile ) )

# load and configure modules

process.ltcUnpack = cms.EDProducer("LTCRawToDigi")

# output 

process.outputL1GtUnpack = cms.OutputModule("PoolOutputModule",
                                            fileName = cms.untracked.string('testLTC_Unpacker_output.root'),
                                            outputCommands = cms.untracked.vstring('drop *', 'keep *_ltcUnpack_*_*') )
   
process.p = cms.Path(process.ltcUnpack)

process.outpath = cms.EndPath(process.outputL1GtUnpack)

