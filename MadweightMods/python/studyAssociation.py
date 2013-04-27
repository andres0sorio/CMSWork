#!/usr/bin/python
import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()

parser.add_option("-f", type = "string", dest="infile",
		  help="Input file")


(options, args) = parser.parse_args()

if options.infile is None:
        parser.error("Input file")

#--------------------------------------------------------
#--------------------------------------------------------
infile  = open( options.infile, 'r' )
outfile = open( 'permutations.out', 'w' )

k = 0
maxextern = 6

perm_id     = []
inv_match   = []
perm_match  = []
		
for ff in infile.readlines():
	line = ff[:-1]
	info = line.split()
	print info
	
	if k < maxextern:
		inv_match.append( info [-3] )
		perm_match.append( info [-2] )
		perm_id.append( info [-1] )
		k=k+1
	
	if k == maxextern:
		
		print perm_id

		maxp = len( perm_id )
		
		full_info = " ".join(perm_id)
		
		for i in range (0,maxp):
			id2 = inv_match[i]
			id3 = perm_match[i]
			full_info += '\t' + id2 + ' ' + id3
			
		outfile.writelines( full_info + '\n' )
		
		inv_match = []
		perm_match = []
		perm_id = []
		k=0

infile.close()
outfile.close()


