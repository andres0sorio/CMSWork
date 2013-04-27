## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

## let it run
process.p = cms.Path( process.patDefaultSequence  )

process.GlobalTag.globaltag = 'START38_V12::All'

process.maxEvents.input = -1         ##  (e.g. -1 to run on all events)

process.out.fileName = 'susy_patTuple.root'

