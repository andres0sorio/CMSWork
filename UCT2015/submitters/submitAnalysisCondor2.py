import sys, os
from optparse import OptionParser

#--------------------------------------------------------

def get_files( input , n):
	""" read the input file and return a list of files in n blocks """
	tmp_list = []
	for file in infile.readlines():
		tmp_list.append( file[:-1] )
	return [tmp_list[i:i+2] for i in range(0,len(tmp_list),n)]

def generate_cfg( template, vinput , index ):
	output = './tmp/' + template.name.split('.')[0] + str(index) + '_cfg.py'
	outfile = open( output, 'w')
	input_files = '[\'' + '\',\''.join(vinput) + '\']' + '\n'
	for script in template.readlines():
		new_line = script.replace('#####INPUT FILE(S)#####',input_files )
		outfile.writelines( new_line )
	outfile.close()
	template.seek(0)
	return output
	
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="files",
                  help="List of files" )

parser.add_option("-c", type = "string", dest="config",
                  help="List of files" )

(options, args) = parser.parse_args()

if options.files is None:
        parser.error("please give a job ID")

if options.config is None:
        parser.error("please give a config file")

#--------------------------------------------------------
k = 0
jobargs = []

infile = open( options.files, 'r' )
cfgfile = open( options.config, 'r' )
outfile = 'uct_rate_tree.root'
tmp_dir = './tmp'

if not os.path.isdir(tmp_dir):
	os.mkdir( tmp_dir )
		    
#--------------------------------------------------------

data = get_files( infile, 2 )

app = Executable(exe=File('./rates.csh') )

#... Job declaration and initialisation:
myjob = Job( application = app, backend = 'Condor' )
myjob.name = 'l1upg.analysis'

myjob.outputsandbox = [outfile]

#... Set the Splitter for this job

for block in data:
	out = generate_cfg(cfgfile, block, k)
	filename = out.split('/')[-1]
	jobargs.append( [ filename ] )
	myjob.inputsandbox.append( File( out ) )
	k+=1
	print out

myjob.splitter = ArgSplitter( args = jobargs )

#... create a Root Merger
rm = RootMerger()
rm.files = [outfile]         # Files to merge
rm.overwrite = True          # Overwrite output files
rm.ignorefailed = True       # ignore root files that failed to open

myjob.merger = rm
myjob.submit()

print "job submission done."

