#!/usr/bin/python
import os,sys
import string
from optparse import OptionParser

#---------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-k", type = "string", dest="localkey",
                  help="Local key", metavar="LOCALKEY" )

(options, args) = parser.parse_args()

if options.localkey is None:
        parser.error("please give a local key name")

#---------------------------------------------------------------------------
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

configkey = options.localkey

cmd = ''

cmd += 'cd ~aosorio/Nikolay/rpct/test-xml/;'
cmd += 'java -cp target/test-xml-jar-with-dependencies.jar -Dlog4j.configuration=file:///$(pwd)/log4j.properties '
cmd += '-DlocalConfigKey=' + configkey + ' '
cmd += '-DsaveToDb=false '
cmd += '-Dxml=$(echo ~rpcdev/bin/config/ttuLhcCosmicMask.xml) test.xml.TtuXmlHandler'

print cmd

data = os.popen( cmd , 'r' ).readlines()

for lines in data:
    print lines[:-1]

