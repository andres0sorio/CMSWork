import FWCore.ParameterSet.Config as cms

process = cms.Process("LTCtest")

process.load("FWCore.MessageService.MessageLogger_cfi")

maxevts = -1

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevts) )

inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/105071/digis.105071.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/105088/digis.105088.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106298/digis.106298.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106301/digis.106301.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106320/digis.106320.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106374/digis.106374.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106378/digis.106378.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106390/digis.106390.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106395/digis.106395.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106399/digis.106399.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106403/digis.106403.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106409/digis.106409.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106460/digis.106460.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106474/digis.106474.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106480/digis.106480.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106485/digis.106485.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106496/digis.106496.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106599/digis.106599.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/106858/digis.106858.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107416/digis.107416.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107420/digis.107420.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107708/digis.107708.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107925/digis.107925.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107946/digis.107946.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107994/digis.107994.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/108001/digis.108001.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/107938/digis.107938.0001.00.0000.root'
inputfile = 'rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/117777/digis.117777.0001.00.0000.root'

#SLC5 files
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129547/digis.129547.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129550/digis.129550.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129551/digis.129551.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129552/digis.129552.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129553/digis.129553.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129554/digis.129554.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129558/digis.129558.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129568/digis.129568.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129575/digis.129575.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129579/digis.129579.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129585/digis.129585.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129587/digis.129587.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129589/digis.129589.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129590/digis.129590.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129592/digis.129592.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129597/digis.129597.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129602/digis.129602.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129606/digis.129606.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129608/digis.129608.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129612/digis.129612.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129613/digis.129613.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129619/digis.129619.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129622/digis.129622.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129625/digis.129625.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129627/digis.129627.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129629/digis.129629.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129631/digis.129631.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129636/digis.129636.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129638/digis.129638.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129639/digis.129639.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129640/digis.129640.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129641/digis.129641.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129642/digis.129642.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129643/digis.129643.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129644/digis.129644.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129645/digis.129645.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129646/digis.129646.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129647/digis.129647.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129648/digis.129648.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129649/digis.129649.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129651/digis.129651.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129652/digis.129652.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129654/digis.129654.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129656/digis.129656.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129660/digis.129660.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129666/digis.129666.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129667/digis.129667.0001.00.0000.root'

#March 02-2010
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129683/digis.129683.0001.00.0000.root'
inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129685/digis.129685.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129688/digis.129688.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129691/digis.129691.0001.00.0000.root'
#inputfile='rfio:/castor/cern.ch/user/c/ccmuon/RPC/minidaq/129693/digis.129693.0001.00.0000.root'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( inputfile ) )

#.. Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

process.demo = cms.EDAnalyzer('LTCTtuAnalyzer',
                              RPCDigiLabel     = cms.InputTag("muonRPCDigis"),
                              LTCDigiLabel     = cms.InputTag("ltcUnpack"),
                              L1TTBitsLabel    = cms.InputTag("rpcTechnicalTrigger"),
                              BitNumbers       = cms.vuint32(24,25,26,27,28),
                              ReadRpcTTbits    = cms.untracked.int32(0),
                              SelectFilter     = cms.untracked.int32(1),
                              MaxNBx           = cms.untracked.int32(1),
                              MinBxNum         = cms.untracked.int32(134),
                              MaxBxNum         = cms.untracked.int32(135),
                              EventWindow      = cms.untracked.int32(10),
                              UseCompression   = cms.untracked.int32(1),
                              WriteMode        = cms.untracked.int32(1), 
                              Precision        = cms.untracked.int32(10),
                              MaxRate          = cms.untracked.int32(200) )

process.TFileService = cms.Service("TFileService", fileName = cms.string('histo.root') )

process.p = cms.Path(process.demo)
