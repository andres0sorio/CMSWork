# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

basedir = os.environ['HOME']+'/scratch0/RelVals/RelVals-Results/'

cpmethod   = ['cp ','rfcp ']

sampleList = ['MinBias',
	      'QCD_Pt_3000_3500',
	      'QCD_Pt_80_120',
	      'SingleMuPt10',
	      'SingleMuPt100',
	      'SingleMuPt1000',
	      'ZMM',
	      'TTbar',
	      'Cosmics',
	      'CosmicsData']

nfiles = 0
njobs = 0

for sample in sampleList:
	
	jobname = 'rpctt.relval.' + sample
	seljobs = jobs.select(name=jobname)
	
	if len( seljobs ) < 1:
		continue

	useIndex = False
	if len( seljobs ) > 1:
		useIndex = True
	indx = 0
	for job in seljobs:
		outputdir = job.outputdir
		rootfile  = job.outputsandbox[0]
		rpos = rootfile.find(sample)-1
		cmsswver = rootfile[14:rpos]

		source = outputdir + rootfile
		excode  = os.path.isfile( source )
		target = basedir + cmsswver + '/'

		if useIndex:
			base = rootfile.split('.')
			rootfile = base[0] + str(indx) + '.root'
			

		excode_2  = os.path.isdir( target )

		if excode_2 == False:
			cmd = ('mkdir ' + target )
			os.system(cmd)

		if excode == True:
			cmd = 'cp ' + source + ' ' + target + rootfile
			os.system( cmd )		
			nfiles=nfiles+1

		indx  = indx  + 1
		njobs = njobs + 1

print njobs, nfiles
