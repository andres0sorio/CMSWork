#!/usr/bin/python
import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()

parser.add_option("-i", type = "string", dest="baseid",
		  help="Base id")

(options, args) = parser.parse_args()

if options.baseid is None:
	parser.error("Base Id")
#--------------------------------------------------------
#--------------------------------------------------------

baseid = options.baseid

info = baseid.split('/')

if len(info) > 4:
	info = info[:-1]

outfile_name = info[0] + '_' + info[-1] + '.out'
weight_val_name = 'perm_values_AO.out'

outfile = open(outfile_name,'w')

baseid = baseid + '/card_1'

event_dir = []

for file in os.listdir(baseid):
	if not os.path.isfile( os.path.join( baseid, file ) ):
		event_dir.append( file )

max_events = len(event_dir)

for k in range(0,max_events):
	event_weight_dir = 'event_' + str(k)
	event_weight_file_name = event_weight_dir + '/' + weight_val_name
	if os.path.isfile( os.path.join( baseid, event_weight_file_name ) ):
		event_weight_file = open( os.path.join( baseid, event_weight_file_name ), 'r' )
		for data in event_weight_file.readlines():
			info = data.split()
			outfile.writelines( str(k) + '\t' + info[1] + '\t' + info[2] + '\t' + info[-2] +'\t' + info[-1] + '\n' )
		outfile.writelines('*' + '\n')
		event_weight_file.close()

outfile.close()


