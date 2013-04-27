#!/usr/bin/python
import os,sys
import string
from optparse import OptionParser

#---------------------------------------------------------------------------

parser = OptionParser()
parser.add_option("-k", type = "string", dest="localkey",
                  help="Local key", metavar="LOCALKEY" )

parser.add_option("-f", type = "string", dest="configfile",
                  help="Local config file", metavar="CONFIGFILE" )

(options, args) = parser.parse_args()

if options.localkey is None:
        parser.error("please give a local key name")

if options.configfile is None:
        parser.error("please give a full path to config file")

#---------------------------------------------------------------------------
#---------------------------------------------------------------------------
# Andres Osorio - aosorio@uniandes.edu.co
# .

configkey  = options.localkey     #configkey = 'LHC_COSMIC2_BOTTOM'
configfile = options.configfile   #'~dnikolay/tmp/ttu-xml/ttuLhcCosmic.xml'

cmd = ''

#cmd += 'cd ~dnikolay/rpct/test-xml/;'
cmd += 'cd ~aosorio/Nikolay/rpct/test-xml/;'
cmd += 'java -cp target/test-xml-jar-with-dependencies.jar -Dlog4j.configuration=file:///$(pwd)/log4j.properties '
cmd += '-DlocalConfigKey=' + configkey + ' '
cmd += '-DsaveToDb=true '
cmd += '-Dxml=$(echo ' + configfile + ') test.xml.TtuXmlHandler < ~aosorio/TTU/answer.txt'

print cmd

data = os.popen( cmd , 'r' ).readlines()

for lines in data:
    print lines[:-1]



