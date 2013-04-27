#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string

from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="infile",
                  help="File name", metavar="RUNID" )

(options, args) = parser.parse_args()

if options.infile is None:
        parser.error("please give an input file")

#-----------------------------------------------------
#-----------------------------------------------------

from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TH1D, TFile, TLatex, TKey
from ROOT import gROOT, gBenchmark, gDirectory

gROOT.Reset()
gBenchmark.Start( 'exportPlots' )

infile    = options.infile
outfile   = 'histograms_names.txt'
output    = open(outfile,'w')

rootfile = TFile( infile ,'R')

path = ''
rootfile.cd(path)

#... Loop over all keys in this directory
current_sourcedir = gDirectory
h1numb=0
h1disp=[]
h1dispstr=''

directories = ['/l1Analyzer']

for dir in directories:
	rootfile.cd(path + dir)
	for nextkey in current_sourcedir.GetListOfKeys():
		output.writelines( nextkey.GetName() + '\n')
		obj = nextkey.ReadObj()
		if obj.IsA().InheritsFrom("TH1D"):
			

			
			h1disp.append('.')
			h1numb=h1numb+1
			if h1numb == 30:
				h1dispstr = ''.join(h1disp)
				print h1dispstr
				h1disp=[]
		if obj.IsA().InheritsFrom("TH2D"):


			
			h1disp.append('.')
			h1numb=h1numb+1
			if h1numb == 30:
				h1dispstr = ''.join(h1disp)
				print h1dispstr
				h1disp=[]

print h1numb

output.close()
rootfile.Close()



print 'Okey. all done'

