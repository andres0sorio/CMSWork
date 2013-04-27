from GangaCMS.Lib.CMSexe import *

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_2_2_4/src/ForGangaTest/SimpleAnalyzer/simpleanalyzer_cfg.py')
app.version = 'CMSSW_2_2_4'

myjob = Job( application = app, backend = 'Local' )

myjob.outputsandbox.append('histo.root')

myjob.submit()

