#!/usr/bin/python 

import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-w", type = "string", dest="wheel",
                  help="Wheel id for synchronization" )

(options, args) = parser.parse_args()

if options.wheel is None:
        parser.error("please give wheel id ( if id > 4 then will do all wheels)")
#-----------------------------------------------------
#-----------------------------------------------------

app = 'lynx -dump '
writeDataURL='http://localhost.localdomain:1972/urn:xdaq-application:lid=10/writeData?'

wheelIds  = ['-2','-1','0','1','2']
sectorIds = ['1','3','5','7','9','11']

Arguments= {}

##Arguments['Wheel'] = options.wheel
##Arguments['sector'] = sectorIds[0]
##Arguments['Register'] = '7'
##GOLSYNCCYCLE=['0','0','0','0','0','0','1','0']

if int(options.wheel) >= 4:

	for wheel in wheelIds:
		Arguments['Wheel'] = wheel
		for k,v in Arguments.items():
			argument = k + '=' + str(v)
			cmd    = app + writeDataURL + argument
			status = os.system(cmd)
			print status


else:

	Arguments['Wheel'] = options.wheel
	for k,v in Arguments.items():
		argument = k + '=' + str(v)
		cmd    = app + writeDataURL + argument
		status = os.system(cmd)
		print status

