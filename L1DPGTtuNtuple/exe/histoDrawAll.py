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
sys.argv = sys.argv[:1] + ['-b'] + sys.argv[1:]

from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TH1D, TFile, TLatex, TKey
from ROOT import gROOT, gBenchmark, gDirectory, gStyle

from tdrstyle import *

gROOT.Reset()
gBenchmark.Start( 'exportPlots' )

def setCanvasStyle( canvas ):
    canvas.SetFillColor(0)
    canvas.SetFrameFillColor(0)
    canvas.SetFrameBorderMode(0)

def set1DHistoStyle( h1d ):
    h1d.SetLineWidth(2)

def set2DHistoStyle( h2d ):
    h2d.SetLineWidth(2)

infile    = options.infile
outfile   = 'histograms_names.txt'
output    = open(outfile,'w')

rootfile = TFile( infile ,'R')

outdir = './results/'

path = ''
rootfile.cd(path)

#... Loop over all keys in this directory
current_sourcedir = gDirectory
h1numb=0
h1disp=[]
h1dispstr=''

directories = ['/l1Analyzer']

gStyle.SetPalette(1)
    
for dir in directories:
	rootfile.cd(path + dir)
	for nextkey in current_sourcedir.GetListOfKeys():
		output.writelines( nextkey.GetName() + '\n')
		obj = nextkey.ReadObj()
		if obj.IsA().InheritsFrom("TH1D"):
			cname = nextkey.GetName()
			c1 = TCanvas( cname, 'TTU Analysis Plots', 100,30,650,500)
			setCanvasStyle( c1 )
			set1DHistoStyle(obj)
			setTDRStyle()
			obj.Draw()
			c1.Print( outdir + cname + '.png' )
		if obj.IsA().InheritsFrom("TH2D"):
			cname = nextkey.GetName()
			c1 = TCanvas( cname, 'TTU Analysis Plots', 100,30,650,500)
			setCanvasStyle( c1 )
			set2DHistoStyle(obj)
			setTDRStyle()
			obj.Draw("COL")
			c1.Print( outdir + cname + '.png' )


output.close()
rootfile.Close()

print 'Okey. all done'

