import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-j", type = "string", dest="step2",
                  help="Job Id for step2" )

(options, args) = parser.parse_args()

if options.step2 is None:
        parser.error("please give a job ID")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

step2 = options.step2
dataset = open('step2-dataset-local.dat','w')

#--------------------------------------------------------
#--------------------------------------------------------

cfgpart = "#... CMSDataset \n"
cfgpart += "readFiles = cms.untracked.vstring() \n"
cfgpart += "secFiles = cms.untracked.vstring() \n"
cfgpart += "process.source = cms.Source (\"PoolSource\",fileNames = readFiles, secondaryFileNames = secFiles)\n"
cfgpart += "readFiles.extend( [ "

#Set the Splitter for this job
for js in jobs(step2).subjobs:
	if js.status == 'completed':
		outdir = js.outputdir
		data = js.outputsandbox[0]
		infile = outdir+data
		dataset.writelines( infile + '\n')
		cfgpart += "\'" + 'file:' + infile + "\',"
		
cfgpart = cfgpart[:-1] + "] )"

print cfgpart

dataset.close()

