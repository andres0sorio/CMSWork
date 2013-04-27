import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="input",
                  help="Requested RelVal", metavar="TABLE" )

parser.add_option("-i", type = "string", dest="ignore",
                  help="Ignore the RelVal prefix", metavar="IGNORE" )


(options, args) = parser.parse_args()

if options.input is None:
        parser.error("Please give it an input file")

#-----------------------------------------------------
#-----------------------------------------------------
from GangaCMS.Lib.CMSexe import *

infileNm      = options.input
ignore_prefix = options.ignore
infileOp      = open( infileNm,'r' )
outfileNm     = 'list_of_files.txt'

dbs = DBSSearch()

outfileOp   = open( 'Run-Sites.txt', 'w')

success = 0

prefix = './RelVals-Datasets/'

for line in infileOp.readlines():
	data = line.split()

	sample  = data[0]
	version = data[1]
	tag     = data[2]
	step    = data[3]
	
	if ignore_prefix == 'yes':
		dbsquery = '/###SAMPLE###/###VERSION###-###TAG###*/###STEP###'
	else:
		dbsquery = '/RelVal###SAMPLE###/###VERSION###-###TAG###*/###STEP###'

	dbsquery= dbsquery.replace('###SAMPLE###',sample)
	dbsquery= dbsquery.replace('###VERSION###',version)
	dbsquery= dbsquery.replace('###TAG###',tag)
	dbsquery= dbsquery.replace('###STEP###',step)
	
	print dbsquery
	
	status = dbs.searchMCFiles( dbsquery )

	if status == False:
		print 'This run could not be found: ', sample
		continue
	#...

	target = prefix + version

	excode  = os.path.isdir( target )

	if excode == False:
		cmd = ('mkdir ' + target )
		os.system(cmd)

	if ignore_prefix == 'yes':
		target = prefix + version + '/' + sample + 'Data'
	else:
		target = prefix + version + '/' + sample
	
	excode  = os.path.isdir( target )

	if excode == False:
		cmd = ('mkdir ' + target )
		os.system(cmd)
		
	outfile = target + '/' + outfileNm

	dbs.exportFiles( outfile )

	status = dbs.searchSites( 1, dbsquery )
	sites = ('\t').join( dbs.getSites() )
	outfileOp.writelines( sample + '\t' + sites + '\n')
	success=success+1

outfileOp.close()



print "Total runs processed: ", success





