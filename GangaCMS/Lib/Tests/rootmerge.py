from GangaCMS.Lib.CMSexe import *

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/opt/CMS/CMSSW_2_2_3/src/ForGangaTest/SimpleAnalyzer/simpleanalyzer_cfg.py')
app.version = 'CMSSW_2_2_3'

myjob = Job( application = app, backend = 'Local' )

myjob.outputsandbox.append('histo.root')

ff    = File(name='/opt/CMS/CMSSW_2_2_3/src/ForGangaTest/SimpleAnalyzer/files.txt')
fdata = CMSDataset( ff , 'local' )

myjob.inputdata = fdata

sp = SplitByFiles()
sp.filesPerJob = 2
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['histo.root']
rm.overwrite = True
rm.ignorefailed = True

myjob.splitter = sp
myjob.merger = rm

myjob.submit()

