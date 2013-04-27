from GangaCMS.Lib.CMSexe import *

app = cmsRun()
app.uselibs = 0
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_2_2_4/src/TrackStudies/TrackPATtuples/test/job_cfg.py')
app.version = 'CMSSW_2_2_5'

myjob = Job( application = app, backend = 'SimpleCrab' )

myjob.backend.scheduler  = 'glite'
myjob.backend.server     = 'cern'

ds = CMSDatasetPath()
ds.addPath('/SUSY_LM0-sftsht/Summer08_IDEAL_V11_v1/GEN-SIM-RECO')
myjob.inputdata = ds

bs = BasicCrabSplitter()
myjob.splitter = bs

out= CrabDataset()
out.names.append('PATLayer1_Output.fromAOD_genericTracks_full.root')
out.user_remote_dir = '/user/a/aosorio/gridfiles'
myjob.outputdata = out

myjob.submit()

