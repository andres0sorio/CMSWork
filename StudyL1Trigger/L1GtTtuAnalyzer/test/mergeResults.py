import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id" )

parser.add_option("-t", type = "string", dest="type",
                  help="Type of job (dqm,ttu)", default='ttu' )

parser.add_option("-s", type = "string", dest="step",
                  help="Step in the analysis" )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a runid number")

if options.step is None:
        parser.error("please give a number")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

cmsconfig = Ganga.Utility.Config.getConfig('CMSSW')

type   = options.type
runid  = int( options.runid )
step   = options.step

prevstep =  type + '.' + step + '.' + options.runid
prevstep = 'ttugt.data.' + options.runid
print prevstep
seljobs = jobs.select(name=prevstep)
print len( seljobs )

if len( seljobs ) != 1:
	sys.exit

prevstepjob = seljobs[-1] #select only the most recent

jobid  = prevstepjob.id

jb = jobs( jobid )

joboutdir   = cmsconfig['dataOutput']

filelistA = []
filelistB = []

protocol = 'rfio:'

if len( jb.subjobs ) > 1:
	for jbs in jb.subjobs:
		outdir   = joboutdir + '/' + str(jb.id) + '/' + str(jbs.id) + '/outputdata/'
		rootFile = jbs.outputdata.names[0]
		fullpath = protocol + outdir + rootFile
		filelistA.append(fullpath)
		
#... hadd one file at a time to avoid unix argument limitation

firstfile = filelistA[0]
del filelistA[0] #and drop the first file from the list
lastfile = filelistA[ len(filelistA) - 1]
target = filelistA[0].split('/')[-1].replace('.','_merged_' + options.runid + '.')
tmpfile = 'temp.root'

for file in filelistA:

    haddcmd='hadd -f '+ target + ' ' + firstfile + ' ' + file
    print haddcmd
    os.system(haddcmd)
    #only do this until file == to last file on the list
    if file == lastfile:
        break
    mvcmd='mv ' + target + ' ' + tmpfile
    print mvcmd
    os.system(mvcmd)
    firstfile=tmpfile

rmcmd = 'rm ' + tmpfile
os.system(rmcmd)
