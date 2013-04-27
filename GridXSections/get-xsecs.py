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
parser.add_option("-f", type = "string", dest="outdir",
                  help="input file", metavar="INFILE" )

(options, args) = parser.parse_args()

if options.outdir is None:
        parser.error("please give a file name")

#-----------------------------------------------------
#-----------------------------------------------------

from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel
from ROOT import TH1F, TH2F, TFile, TLatex, TGraph, TLegend, TGraphErrors
from ROOT import gROOT, gBenchmark, gDirectory, gStyle
from array import array

gROOT.Reset()
gStyle.SetPalette(1)

def setCanvasStyle( canvas ):
	canvas.SetFillColor(0)
	canvas.SetFrameFillColor(0)
	canvas.SetFrameBorderMode(0)
	canvas.SetGridx()
	canvas.SetGridy()
	
def set1DHistoStyle( h1d ):
	h1d.SetLineWidth(2)

def setTextStyle( tx ):
	tx.SetTextSize(0.034)
	tx.SetLineWidth(1)

def setLegendStyle( lg ):
	lg.SetFillColor(10)
	lg.SetBorderSize(1)

#-----------------------------------------------------

c1 = TCanvas( 'VarX', 'Xsec Variation', 526,216,650,500)
setCanvasStyle(c1)

outdir = options.outdir

find_cmd = 'find ' + outdir + ' -name \"pythia8_*\"'
files = os.popen(find_cmd ,'r').readlines()

data = []

for file in files:
	avg_xsec_cmd = './distribution-xsecs.py -f ' + file[:-1]
	results = os.popen(avg_xsec_cmd ,'r').readlines()

	for result in results:
		print result[:-1]
		list = result[:-1].split()
		
		data.append(list[2:])


data_sorted = sorted( data )

x1 = array('d')
y1 = array('d')

for info in data_sorted:

	x1.append( float(info[0]) )
        y1.append( float(info[1]) )

gg1 = TGraph( len(x1), x1, y1 )

c1.cd()

gg1.Draw("ACP")










