import sys,os

from GangaCMS.Lib.CMSexe import *

search='Closed file rfio:'

jb = jobs(334)

sum = 0
haserror=[]

if len( jb.subjobs ) > 1:
	for jbs in jb.subjobs:
		outdir = jbs.outputdir
		stdout = outdir + 'stdout.gz'
		stderr = outdir + 'stderr.gz'
		fs = os.path.isfile(stdout)
		hasline = []
		if fs and (jbs.status == 'completed'):
			unzip = 'gunzip ' + stdout
			os.system(unzip)
			unzip = 'gunzip ' + stderr
			os.system(unzip)
			
