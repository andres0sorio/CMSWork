#!/usr/bin/python
import os,sys
import string
import datetime
from optparse import OptionParser

#---------------------------------------------------------------------------
#---------------------------------------------------------------------------
# Andres Osorio - aosorio@uniandes.edu.co
# 
prefix = '~rpcdev/bin/config/'

lhccosmic = 'ttuLhcCosmic.xml'
cosmic    = 'ttuCosmic.xml' 
bottom    = 'ttuLhcCosmicBit25.xml'

allconfigs = [ ['DEFAULT',            prefix + lhccosmic ],
	       ['COSMIC',             prefix + cosmic ],
	       ['COSMIC1',            prefix + cosmic ],
	       ['COSMIC_TIGHT',       prefix + cosmic ],
	       ['LHC_COSMIC_BOTTOM1', prefix + bottom ],
	       ['LHC_COSMIC1',        prefix + lhccosmic ],
	       ['LHC_COSMIC1_2BX',    prefix + lhccosmic ],
	       ['LHC_COSMIC1_3BX',    prefix + lhccosmic ],
	       ['LHC_COSMIC2',        prefix + lhccosmic ],
	       ['LHC_COSMIC2_3BX',    prefix + lhccosmic ],
	       ['LHC_COSMIC2_BOTTOM', prefix + bottom ],
	       ['LHC3',               prefix + lhccosmic ],
	       ['LHC3_2BX',           prefix + lhccosmic ],
	       ['LHC3_3BX',           prefix + lhccosmic ],
	       ['LHC3_BOTTOM',        prefix + bottom ] ]

#cmd += 'cd ~dnikolay/rpct/test-xml/;'

now = datetime.datetime.now()
date = str(now.date().year) + '-' + str(now.date().month) + '-' + str(now.date().day) + '-' + str( now.time().hour )

filename = 'ttuDB-configuration-' + date + '.txt'
outfile = open( filename,'w')

for config in allconfigs:

	configkey  = config[0]
	configfile = config[1]

	cmd = ''
	cmd += 'cd ~aosorio/Nikolay/rpct/test-xml/;'
	cmd += 'java -cp target/test-xml-jar-with-dependencies.jar -Dlog4j.configuration=file:///$(pwd)/log4j.properties '
	cmd += '-DlocalConfigKey=' + configkey + ' '
	cmd += '-DsaveToDb=false '
	cmd += '-Dxml=$(echo ' + configfile + ') test.xml.TtuXmlHandler'

	print cmd
	data = os.popen( cmd , 'r' ).readlines()
	
	for lines in data:
		outfile.writelines( lines )

	
outfile.close()

