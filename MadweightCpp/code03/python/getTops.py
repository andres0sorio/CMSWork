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

from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TH1F, TH2F, TFile, TLatex, TGraph, TLegend, TGraphErrors
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

def setGraphStyle( g ):
	gHist = g.GetHistogram()
	gHist.SetXTitle("m12")
	gHist.SetYTitle("#sigma [pb]") 
	gHist.SetTitle("")
	g.GetYaxis().SetLabelSize(0.03)

def setGraphStyleCol( g , col ):
	g.SetMarkerStyle(7)
	g.SetMarkerColor( col )
	setGraphStyle( g )

def setTextStyle( tx ):
	tx.SetTextSize(0.034)
	tx.SetLineWidth(1)

def setLegendStyle( lg ):
	lg.SetFillColor(10)
	lg.SetBorderSize(1)

#-----------------------------------------------------

c1 = TCanvas( 'C1', 'Top mass comparison', 526,216,650,500)
setCanvasStyle(c1)

c2 = TCanvas( 'C2', 'Top mass comparison', 526,216,650,500)
setCanvasStyle(c2)

infile = options.infile
inputfile = open(infile,'r')

outfile = open("tops_info.dat",'w')

#x = array('d')
#y1 = array('d')
#errorsInxsec = TH1F("h1","errors in xsec",50,0,15)
#m0init = 100.0

h1 = TH1F("h1","MC Top(6) mass", 100, 100, 210)
h2 = TH1F("h2","MC barTop(-6) mass", 100, 100, 210)

ntop = 0
natop = 0

for line in inputfile.readlines():
	pos  = line.find('6')
	if pos == 8:
		info = line.split()
		#print info
		if info[0] == '6':
			h1.Fill( float(info[10] ) )
			outfile.writelines(line)
			ntop += 1
		elif info[0] == '-6':
			h2.Fill( float(info[10] ) )
			outfile.writelines(line)
			natop += 1

			

outfile.close()

c1.cd()
h1.Draw()

c2.cd()
h2.Draw()

print 'Ok. all done', ntop, natop
