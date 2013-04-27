import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="input",
                  help="All CRAFT2 runs", metavar="TABLE" )

(options, args) = parser.parse_args()

if options.input is None:
        parser.error("Please give it an input file")

#-----------------------------------------------------
#-----------------------------------------------------
from GangaCMS.Lib.CMSexe import *

infileNm    = options.input
infileOp    = open( infileNm,'r' )
outfileNm   = 'list_of_files.txt'

dbs = DBSSearch()

outfileOp   = open( 'Run-Sites.txt', 'w')

success = 0

for line in infileOp.readlines():
	data = line.split()
	runid = data[0]
	dttype = data[5]
	status = dbs.searchFiles( int(runid), dttype )

	if status == False:
		print 'This run could not be found: ', runid
		continue
	#...
	excode  = os.path.isdir( runid )

	if excode == False:
		cmd = ('mkdir '+  runid)
		os.system(cmd)

	outfile = runid + '/' + outfileNm
	dbs.exportFiles( outfile )
	
	status = dbs.searchSites( int(runid), dttype )
	sites = ('\t').join( dbs.getSites() )
	outfileOp.writelines( runid + '\t' + sites + '\n')
	success=success+1

outfileOp.close()


print "Total runs processed: ", success





