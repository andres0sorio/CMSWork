from GangaCMS.Lib.CMSexe import *

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_2_1_9/src/RPCDigiAnalyzer/TTUAnalyzer/test/ttuanalyzer_mcdata.cfg.py')
app.version = 'CMSSW_2_1_9'

myjob = Job( application = app, backend = 'Local' )

myjob.outputsandbox.append('histo.root')
myjob.outputsandbox.append('checkdata.out')

ff    = File(name='files.txt')
fdata = CMSDataset( ff , 'local' )

myjob.inputdata = fdata

myjob.submit()

