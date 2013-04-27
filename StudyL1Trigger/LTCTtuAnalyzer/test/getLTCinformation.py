import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID")

parser.add_option("-t", type = "string", dest="type",
                  help="Type of job (data,emu)", default='ltcdata' )

parser.add_option("-c", type = "string", dest="cpmethod",
                  help="copy method (0=cp,1=rfcp)", default='0' )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *
cmsconfig = Ganga.Utility.Config.getConfig('CMSSW')

joboutdir   = cmsconfig['dataOutput']
type        = options.type
runid       = int( options.runid )
cpmethod    = int( options.cpmethod )
jobtype     = ''

if type == 'data' or type == 'ltcdata':
	jobtype  = type
	prevstep = 'ttultc.' + jobtype + '.' + options.runid
	
else:
	jobtype  = type + '.data'
	prevstep = 'ttultc.' + jobtype + '.' + options.runid
	
nfiles=0

seljobs = jobs.select(name=prevstep)

if len( seljobs ) < 1:
	sys.exit(0)

prevstepjob = seljobs[-1]
jobid  = prevstepjob.id
filename = 'ltcinformation.txt.gz'
cpcmd = ['cp -v ','rfcp ']
targetdir = './' + jobtype + '.' + options.runid + '/'
listoffiles = targetdir +'list_of_files.txt'

excode = os.path.isdir(targetdir)
if excode != True:
        os.mkdir(targetdir)

outfile = open(listoffiles,'w')

for jb in jobs(jobid).subjobs:
	jbs  = jb.status
	jbid = jb.id

	if jbs == 'completed':

		if cpmethod == 0:
			outputdir  = jb.outputdir
		else:
			outputdir  = joboutdir + '/' + str(jobid) + '/' + str(jbid) + '/outputdata/'
		
		source     = outputdir + filename
		targetname = filename.split('.')[0] + '.' + jobtype + '.' +  str(jobid) + '.' + str(jbid) + '.txt.tgz'
		target     = targetdir + targetname
		cmd = cpcmd[cpmethod] + source + ' ' + target
		print cmd
		os.system(cmd)
		outfile.writelines(targetdir + targetname + '\n')
		nfiles=nfiles+1

outfile.close()

print nfiles

