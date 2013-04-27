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

infileName    = options.infile
infile = open(infileName,'r')


xxopts  = infileName.split('/')[1].split('-')
print xxopts
option  = '-' + xxopts[4] + '-' + xxopts[5]

outpath  = './TtuScan-Results-April28/'
outfname = 'ttu-hvscan-results-' + xxopts[4] + '-' + xxopts[5] + '.txt'
output   = outpath + outfname
outfile  = open(output,'w')


gStyle.SetPalette(1)

marker      = [21, 21, 20, 22, 23, 29, 21, 20, 21, 23]
colour      = [ 0, 4, 2, 2, 2, 2, 2, 3, 6, 7]

ttutrig     = ['TTU_1_Trig8','TTU_1_Trig9','TTU_2_Trig8','TTU_3_Trig8','TTU_3_Trig9','TOTAL']
wheels      = ['WP1','WP2','W00','WM1','WM2','AllW']
histograms  = []
hvpoints    = [8.8, 8.9, 9.0, 9.1, 9.2, 9.3, 9.4, 9.5]

isFirst     = True
line        = infile.readline()[:-1]
results     = []
histrograms = []

#book Histograms
hvindex = 0
for hv in hvpoints:
	histograms=[]
	for trig in ttutrig:
		hname = trig + '_' + str(hvpoints[ hvindex ])
		h1 = TH1D( hname, "rate histograms", 100, 0, 250)
		histograms.append( h1 )
	results.append( histograms )
	hvindex+=1
	
hvindex = -1
maxdata = 180 #seconds
np = 0
while line != '':
	
	if line.find('===') < 0:
		info   = line.split()
		time   = info.pop(0)

		if hvindex < 8:
			histos = results[hvindex]
			#.... fill the histograms
			k=0
			for h1 in histos:
				if np > maxdata:
					continue
				h1.Fill( float ( info[k] ) )
				k+=1
		
				
	else:
		hvindex += 1
		print 'adding new point', hvpoints[ hvindex ]
		np = 0
		
	np += 1			
	line = infile.readline()[:-1]

outfile.writelines('HV \t WP1 \t WP2 \t W00 \t WM1 \t WM2 \t Total' + '\n')

hvindex=0
for hv in hvpoints:

	histos = results[hvindex]
	hvval  = hvpoints[ hvindex ]
	outfile.writelines( str(hvval) + '\t')
	for h1 in histos:
		cname = h1.GetName()
		cnv = TCanvas( cname , 'TTU Analysis Plots', 100,30,650,500)
		setCanvasStyle( cnv )
                set1DHistoStyle( h1 )
                setTDRStyle()
		cnv.cd()
		h1.GetXaxis().SetTitle('Rate [Hz]')
		h1.Draw()
		cnv.Print( outpath + cname + option + '.png' )
		mean = h1.GetMean()
		rms =  h1.GetRMS()
		outfile.writelines( str(mean) + " " + str(rms) + " ")
		k+=1
	hvindex+=1
	outfile.writelines('\n')

infile.close()
outfile.close()

print 'Okey. all done'

