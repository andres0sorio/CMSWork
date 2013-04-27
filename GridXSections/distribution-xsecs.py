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
                  help="input file", metavar="INFILE" )

(options, args) = parser.parse_args()

if options.infile is None:
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

infile = options.infile
inputfile = open(infile,'r')

info = infile[:-4].split('_')
parvalue = info[-1][1:]

x = array('d')
y1 = array('d')

n = 0
sum = 0.0

for lines in inputfile.readlines():
	info = lines.split()
	xsec = float( info[2] ) * 10**9
	sum  = sum + xsec
	n = n + 1

avg = sum / n

xsecHisto = TH1F("h1","xsec Histogram", 100, avg - (avg * 0.20), avg + (avg * 0.20))

inputfile.seek(0)
	
for lines in inputfile.readlines():
	info = lines.split()
	xsec = float( info[2] ) * 10**9
	xsecErr = float( info[3] ) * 10**9
	#print xsec, ' \pm ', xsecErr
	xsecHisto.Fill(xsec)
	
mean = xsecHisto.GetMean()
rms = xsecHisto.GetRMS()

print 'xsec [pb]', float(parvalue), mean , '\pm' , rms


