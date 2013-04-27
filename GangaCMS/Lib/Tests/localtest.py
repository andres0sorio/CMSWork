from GangaCMS.Lib.CMSexe import *

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/opt/CMS/CMSSW_2_2_3/src/ForGangaTest/SimpleAnalyzer/simpleanalyzer_cfg.py')
app.version = 'CMSSW_2_2_3'

myjob = Job( application = app, backend = 'Local' )

myjob.outputsandbox.append('histo.root')

myjob.submit()

