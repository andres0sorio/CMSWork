# Read a list of files, get their corresponding TURL and copy them to Uniandes
# Andres Osorio : aosorio@uniandes.edu.co
import string
import os,sys
from optparse import OptionParser

#--------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", "--file", dest="filelist",
                  help="Ascii file containing list of files to replicate",
                  metavar="FILE")

(options, args) = parser.parse_args()

if options.filelist is None:
        parser.error("please provide a file list")
#--------------------------------------------------------------------------

counter     = 1
filelist    =  options.filelist
SRMlocation = 'srm://grid-srm.physik.rwth-aachen.de:8443/srm/managerv2\?SFN='
Pathprefix  = '/pnfs/physik.rwth-aachen.de/cms'
Tprotocol   = 'gsiftp'
lfnprefix   = 'lfn:/grid/cms/'
SRMserver   = 'moboro.uniandes.edu.co'

def setEnv():
    #make sure these env. variables are present
    os.environ['LFC_HOST']='prod-lfc-cms-central.cern.ch'
    os.environ['LCG_GFAL_INFOSYS']='exp-bdii.cern.ch:2170'
    os.environ['LCG_CATALOG_TYPE']='lfc'
    return True

def getTURL(inSURL):
    lcgcmd = 'lcg-gt'
    target = SRMlocation + Pathprefix + inSURL
    cmd    = lcgcmd + ' ' + target + ' ' + Tprotocol
    pipe = os.popen( cmd , 'r' )
    rettxt = pipe.read()
    sts = pipe.close()
    turl = rettxt.split('\n')
    return turl[0]

#--------------------------------------------------------------------------

dataset   = []
fh = open(filelist)
outfile = open('files_mapping.csv','w')

for line in fh.readlines():
    dataset.append(line[:-1])

#.
status  = setEnv()

lcgcmd  = 'lcg-cr'
lcgopt  = '--vo cms'

for lfn in dataset:

    pipe = os.popen( 'date', 'r')
    rettxt = pipe.read()
    datetxt = rettxt.split('\n')
    print datetxt[0]
    
    turl      = getTURL(lfn)
    targetlfn = lfnprefix + 'SUSY_LM0_sftsht_RECO_V11_' + str(counter)

    outfile.write( lfn + '\t' + targetlfn + '\t' + datetxt[0] )

    cmd       = lcgcmd + ' ' + lcgopt + ' -l ' + targetlfn + ' -d ' + SRMserver + ' ' + turl

    pipe = os.popen( cmd , 'r' )
    rettxt = pipe.read()

    counter += 1
    if counter > 2:
	    break
    
pipe = os.popen( 'date', 'r')
rettxt = pipe.read()
datetxt = rettxt.split('\n')
print datetxt[0]

outfile.close()

