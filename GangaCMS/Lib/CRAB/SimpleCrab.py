################################################################################
# Ganga Project. http://cern.ch/ganga                                          #
# cmsRun : Andres Osorio                                                       #
#                                                                              #
################################################################################
#__author__   = 'Andres Osorio'
#__date__     = 'March 2009'
#__revision__ =  0.1

"""
SimpleCrab.py: A Ganga simple backendhandler for the CRAB system
"""

import os
import sys
from os.path import join
import os.path, re, errno

#From Ganga
from Ganga.GPIDev.Adapters.IBackend import IBackend
from Ganga.GPIDev.Credentials import GridProxy
from Ganga.GPIDev.Lib.File import  FileBuffer, File
from Ganga.GPIDev.Schema import *
from Ganga.Utility.tempfile_compatibility import *
from Ganga.Utility.Config import makeConfig, getConfig, ConfigError
from Ganga.Core import BackendError

import Ganga.Utility.logging
logger = Ganga.Utility.logging.getLogger()

import subprocess

#... From GangaCMS
from GangaCMS.Lib.CMSDataset import *
from GangaCMS.Lib.CRAB.ConfigFile import *
##from GangaCMS.Lib.CRAB.SimpleCrabExtras import *


#-----------------------------------------------------
#... Get the environment
crabconfig  = Ganga.Utility.Config.getConfig('CRAB')
crabEnable  =  crabconfig['CrabEnable']

crabEnable    = False

_CrabImported = True

#.....................................................

if crabEnable == True:
    try:

        if os.environ['SITE'] == 'CERN':
            from Ganga.Utility.GridShell import getShell
            gShell=getShell()
            for k, v in gShell.env.items():
                os.environ[k]   = gShell.env[k]
        else:
            import Ganga.Utility.Shell
            fgShell = Ganga.Utility.Shell.Shell('/home/aosorio/bin/testing-ganga-shell.sh')
            for k, v in fgShell.env.items():
                os.environ[k]   = fgShell.env[k]
            
        _CrabImported = True
        logger.debug("Importing CRAB succeeded")
    
    except:

        _CrabImported = False
        logger.error("Importing CRAB failed")

#.....................................................
        
if _CrabImported:
    logger.debug("CRAB ready")

#-----------------------------------------------------


#-----------------------------------------------------

class SimpleCrab(IBackend):
    """A very simple backend that submits CMS jobs to the Grid via CRAB
    """
    comments=[]
    comments.append('The id number assigned to the job by CRAB.')
    comments.append('The detailed status as reported by CRAB')
    comments.append('CRAB server: bari, legnaro, CERN (default)')
    comments.append('The location where the job ran')
    comments.append('Aplication type')
    comments.append('Scheduler (glite,lsf)')
    comments.append('(internal) process id of the execution wrapper')
    comments.append('Working directory')
            
    schemadic={}
    schemadic['id']          = SimpleItem(defvalue = '0'       , protected=1, copyable = 1, doc = comments[0])
    schemadic['status']      = SimpleItem(defvalue = 'new'     , protected=1, copyable = 1, doc = comments[1])
    schemadic['server']      = SimpleItem(defvalue = 'CERN'    , protected=0, copyable=1, doc=comments[2])
    schemadic['actualCE']    = SimpleItem(defvalue = 'cern.ch' , protected=1, copyable=1, doc=comments[3])
    schemadic['apptype']     = SimpleItem(defvalue = 'cmssw'   , protected=1, copyable=1, doc=comments[4])
    schemadic['scheduler']   = SimpleItem(defvalue = 'glite'   , protected=0, copyable=1, doc=comments[5])
    schemadic['wrapper_pid'] = SimpleItem(defvalue = -1        , protected=1, copyable=1, hidden=1,doc=comments[6])
    schemadic['workdir']     = SimpleItem(defvalue = '.'       , protected=1, copyable=1, doc=comments[7])
    
    _schema = Schema(Version(1, 4), schemadic )

    ##_exportmethods = ['getOutput','getOutputData']

    _packed_input_sandbox = True

    _category = 'backends'

    _name  = 'SimpleCrab'

    ###extras = SimpleCrabExtras()
    
    def __init__(self):
        super(SimpleCrab, self).__init__()

    def submit(self, jobconfig, master_input_sandbox):
        """Submit a CRAB job in the simplest mode possible i.e. prepare a cfg file and run crab on it"""
        ##self.handleGridProxy()
        self.run(self.preparejob(jobconfig,master_input_sandbox))
        return 1
    
    def run(self,scriptpath):
        """Run the Crab job wrapper"""
        try:
            process=subprocess.Popen(["python",scriptpath,'subprocess'])
        except OSError,x:
            logger.error('cannot start a job process: %s',str(x))
            return 0
        self.wrapper_pid=process.pid
        self.actualCE = Ganga.Utility.util.hostname()
        return 1
    
    def preparejob(self,jobconfig,master_input_sandbox):
        """Prepare the job to submit"""
        
        job = self.getJobObject()

        subjob_input_sandbox  = job.createPackedInputSandbox(jobconfig.getSandboxFiles())
        appscriptpath         = [jobconfig.getExeString()]+jobconfig.getArgStrings()
        sharedoutputpath      = job.getOutputWorkspace().getPath()
        outputpatterns        = jobconfig.outputbox
        environment           = jobconfig.env

        workdir = job.outputdir
        
        scriptlines=[]
        scriptlines.append('#!/usr/bin/env python')
        scriptlines.append('import os,os.path,shutil,tempfile')
        scriptlines.append('import sys,popen2,time')
        scriptlines.append('import sys')
        scriptlines.append('if len(sys.argv)>1 and sys.argv[1] == \'subprocess\':')
        scriptlines.append('   os.setsid()')
        scriptlines.append('############################################################################################')
        scriptlines.append(' ')
        scriptlines.append('###INLINEMODULES###')
        scriptlines.append(' ')
        scriptlines.append('############################################################################################')
        scriptlines.append(' ')
        scriptlines.append('input_sandbox = ###INPUT_SANDBOX###')
        scriptlines.append('sharedoutputpath= ###SHAREDOUTPUTPATH###')
        scriptlines.append('outputpatterns = ###OUTPUTPATTERNS###')
        scriptlines.append('appscriptpath = ###APPSCRIPTPATH###')
        scriptlines.append('environment = ###ENVIRONMENT###')
        scriptlines.append('workdir = ###WORKDIR###')
        scriptlines.append('statusfilename = os.path.join(sharedoutputpath,\'__jobstatus__\' )')
        scriptlines.append(' ')
        scriptlines.append('try:')
        scriptlines.append('   statusfile=file(statusfilename,\'w\')')
        scriptlines.append('except IOError,x:')
        scriptlines.append('   print \'ERROR: not able to write a status file: \', statusfilename')
        scriptlines.append('   print \'ERROR: \',x')
        scriptlines.append('   raise')
        scriptlines.append('  ')
        scriptlines.append('line=\'START: \'+ time.strftime(\'%a %b %d %H:%M:%S %Y\',time.gmtime(time.time())) + os.linesep')
        scriptlines.append('statusfile.writelines(line)')
        scriptlines.append('statusfile.flush()')
        scriptlines.append(' ')
        scriptlines.append('os.chdir(workdir)')
        scriptlines.append(' ')
        scriptlines.append('import sys')
        scriptlines.append('sys.path.insert(0, ###GANGADIR###)')
        scriptlines.append('try:')
        scriptlines.append('    import subprocess')
        scriptlines.append('except ImportError,x:')
        scriptlines.append('    sys.path.insert(0,###SUBPROCESS_PYTHONPATH###) ')
        scriptlines.append('    import subprocess')
        scriptlines.append('try:')
        scriptlines.append('    import tarfile')
        scriptlines.append('except ImportError,x:')
        scriptlines.append('    sys.path.insert(0,###TARFILE_PYTHONPATH###)')
        scriptlines.append('    import tarfile')
        scriptlines.append(' ')
        scriptlines.append('for f in input_sandbox:')
        scriptlines.append('  getPackedInputSandbox(f)')
        scriptlines.append(' ')
        scriptlines.append('for key,value in environment.iteritems():')
        scriptlines.append('   os.environ[key] = value')
        scriptlines.append(' ')
        scriptlines.append('outfile=file(\'stdout\',\'w\') ')
        scriptlines.append('errorfile=file(\'stderr\',\'w\') ')
        scriptlines.append(' ')
        scriptlines.append('sys.stdout=file(\'./__syslog__\',\'w\') ')
        scriptlines.append('sys.stderr=sys.stdout')
        scriptlines.append(' ')
        scriptlines.append('###MONITORING_SERVICE###')
        scriptlines.append('monitor = createMonitoringObject()')
        scriptlines.append('monitor.start()')
        scriptlines.append(' ')
        scriptlines.append('import subprocess')
        scriptlines.append(' ')
        scriptlines.append('try:')
        scriptlines.append('  child = subprocess.Popen(appscriptpath, shell=True, stdout=outfile, stderr=errorfile)')
        scriptlines.append('except OSError,x:')
        scriptlines.append('  file(\'tt\',\'w\').close()')
        scriptlines.append('  print >> statusfile, \'EXITCODE: %d\'%-9999')
        scriptlines.append('  print >> statusfile, \'PROBLEM STARTING THE APPLICATION SCRIPT: %s %s\'%(appscriptpath,str(x))')
        scriptlines.append('  statusfile.close()')
        scriptlines.append('  sys.exit()')
        scriptlines.append(' ')
        scriptlines.append('print >> statusfile, \'PID: %d\'%child.pid')
        scriptlines.append('statusfile.flush()')
        scriptlines.append(' ')
        scriptlines.append('result = -1')
        scriptlines.append(' ')
        scriptlines.append('try: ')
        scriptlines.append('  while 1:')
        scriptlines.append('    result = child.poll()')
        scriptlines.append('    if result is not None:')
        scriptlines.append('        break')
        scriptlines.append('    outfile.flush()')
        scriptlines.append('    errorfile.flush()')
        scriptlines.append('    monitor.progress()')
        scriptlines.append('    time.sleep(0.3)')
        scriptlines.append('finally:')
        scriptlines.append('    monitor.progress()')
        scriptlines.append('    sys.stdout=sys.__stdout__')
        scriptlines.append('    sys.stderr=sys.__stderr__')
        scriptlines.append(' ')
        scriptlines.append('monitor.stop(result)')
        scriptlines.append(' ')
        scriptlines.append('outfile.flush()')
        scriptlines.append('errorfile.flush()')
        scriptlines.append(' ')
        scriptlines.append('createOutputSandbox(outputpatterns,None,sharedoutputpath)')
        scriptlines.append(' ')
        scriptlines.append('outfile.close()')
        scriptlines.append('errorfile.close()')
        scriptlines.append(' ')
        scriptlines.append('line=\"EXITCODE: \" + repr(result) + os.linesep')
        scriptlines.append('line+=\'STOP: \'+time.strftime(\'%a %b %d %H:%M:%S %Y\',time.gmtime(time.time())) + os.linesep')
        scriptlines.append('statusfile.writelines(line)')
        scriptlines.append('sys.exit()')

        script = '\n'.join(scriptlines)
        
        import inspect
        import Ganga.Core.Sandbox as Sandbox

        #These are Ganga specific modules
        script = script.replace('###INLINEMODULES###',inspect.getsource(Sandbox.WNSandbox))
        
        script = script.replace('###APPLICATION_NAME###',repr(job.application._name))
        script = script.replace('###INPUT_SANDBOX###',repr(subjob_input_sandbox+master_input_sandbox))
        script = script.replace('###SHAREDOUTPUTPATH###',repr(sharedoutputpath))
        script = script.replace('###APPSCRIPTPATH###',repr(appscriptpath))
        script = script.replace('###OUTPUTPATTERNS###',repr(outputpatterns))
        script = script.replace('###JOBID###',repr(job.getFQID('.')))
        script = script.replace('###ENVIRONMENT###',repr(environment))
        script = script.replace('###WORKDIR###',repr(workdir))
        script = script.replace('###MONITORING_SERVICE###',job.getMonitoringService().getWrapperScriptConstructorText())
      
        self.workdir = workdir
        
        ####from Ganga.Utility.Config import getConfig
        
        script = script.replace('###GANGADIR###',repr(getConfig('System')['GANGA_PYTHONPATH']))
        
        import Ganga.PACKAGE
        script = script.replace('###SUBPROCESS_PYTHONPATH###',repr(Ganga.PACKAGE.setup.getPackagePath2('subprocess','syspath',force=True)))
        script = script.replace('###TARFILE_PYTHONPATH###',repr(Ganga.PACKAGE.setup.getPackagePath2('tarfile','syspath',force=True)))
        
        return job.getInputWorkspace().writefile(FileBuffer('__jobscript__',script),executable=1)

#..............................................................

    def resubmit(self):
        job = self.getJobObject()
        import shutil
        
        try:
            shutil.rmtree(self.workdir)
        except OSError,x:
            import errno
            if x.errno != errno.ENOENT:
                logger.error('problem cleaning the workdir %s, %s',self.workdir,str(x))
                return 0
        try:
            os.mkdir(self.workdir)
        except Exception,x:
            logger.error('cannot make the workdir %s, %s',self.workdir,str(x))
            return 0
        return self.run(job.getInputWorkspace().getPath('__jobscript__'))

    def kill(self):
        import os,signal

        job = self.getJobObject()        
        ok = True
        self.remove_workdir()
        return 1

    def remove_workdir(self):
        if crabconfig['remove_workdir']:
            import shutil
            try:
                shutil.rmtree(self.workdir)
            except OSError,x:
                logger.warning('problem removing the workdir %s: %s',str(self.id),str(x))

    def updateMonitoringInformation(jobs):

        def get_exit_code(f):
            import re
            statusfile=file(f)
            stat = statusfile.read()
            m = re.compile(r'^EXITCODE: (?P<exitcode>-?\d*)',re.M).search(stat)
            
            if m is None:
                return None
            else:
                return int(m.group('exitcode'))

        def get_pid(f):
            import re
            statusfile=file(f)
            stat = statusfile.read()
            m = re.compile(r'^PID: (?P<pid>\d*)',re.M).search(stat)

            if m is None:
                return None
            else:
                return int(m.group('pid'))          

        logger.debug('local ping: %s',str(jobs))
      
        for j in jobs:
            outw=j.getOutputWorkspace()

            # try to get the application exit code from the status file
            try:
                statusfile = os.path.join(outw.getPath(),'__jobstatus__')
                if j.status == 'submitted':
                    pid = get_pid(statusfile)
                    if pid:
                        j.backend.id = pid
                        #logger.info('Local job %d status changed to running, pid=%d',j.id,pid)
                        j.updateStatus('running') # bugfix: 12194
                exitcode = get_exit_code(statusfile)
                logger.debug('status file: %s %s',statusfile,file(statusfile).read())
            except IOError,x:
                logger.debug('problem reading status file: %s (%s)',statusfile,str(x))
                exitcode=None
            except Exception,x:
                logger.critical('problem during monitoring: %s',str(x))
                import traceback
                traceback.print_exc()
                raise x

            # check if the exit code of the wrapper script is available (non-blocking check)
            # if the wrapper script exited with non zero this is an error
            try:
                ws = os.waitpid(j.backend.wrapper_pid,os.WNOHANG)
                if not Ganga.Utility.logic.implies(ws[0]!=0,ws[1]==0):
                    #FIXME: for some strange reason the logger DOES NOT LOG (checked in python 2.3 and 2.5)
                    ##print 'logger problem', logger.name
                    ##print 'logger',logger.getEffectiveLevel()
                    logger.critical('wrapper script for job %s exit with code %d',str(j.id),ws[1])
                    logger.critical('report this as a bug at http://savannah.cern.ch/bugs/?group=ganga')
                    j.updateStatus('failed')
            except OSError,x:
                if x.errno != errno.ECHILD:
                    logger.warning('cannot do waitpid for %d: %s',j.backend.wrapper_pid,str(x))

            if not exitcode is None:
                # status file indicates that the application finished
                j.backend.exitcode = exitcode

                if exitcode == 0:
                    j.updateStatus('completed')
                else:
                    j.updateStatus('failed')
              
    updateMonitoringInformation = staticmethod(updateMonitoringInformation)

#..............................................................
#Grid related

    def handleGridProxy(self):
        """Check the Grid Proxy validity"""
        proxy = GridProxy()
        mintime = float(7600)
        try:
            timeleft = float(proxy.timeleft("hours"))*3600
        except ValueError:
            timeleft = 0.0

        if timeleft < mintime:
            logger.warning("Failed to submit job. Grid proxy validity %s s, while %s s required" % (str(timeleft),str(mintime)))
            raise BackendError("SimpleCrab", "Failed to submit job. Grid proxy validity %s s, while %s s required" % (str(timeleft),str(mintime)))
        
#..............................................................


    #def getOutput(self,dir=os.curdir):
    #    """Retrieve the outputsandbox from the DIRAC WMS. The dir argument gives the directory the the sandbox will be retrieved into"""

    ##def getOutputData(self,dir='',names=[]):
    ##    """Retrieve data created by job and stored on SE
    ##
    ##    dir   Copy the output to this directory. The output workspace of the job
    ##          is the default.
    ##    names The list of files to retrieve. If empty all files registered as
    ##          outputdata will be retrieved. If names are simple file names the default
    ##          LFN will be prepended. If names start with a / it is assumed to be the
    ##          complete path. Do never add an "LFN:" to the name.
    ##    """

#..............................................................

