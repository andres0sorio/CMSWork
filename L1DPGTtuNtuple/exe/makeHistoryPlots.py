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
parser.add_option("-f", type = "string", dest="filename",
                  help="File name", metavar="FILENAME" )

(options, args) = parser.parse_args()

if options.filename is None:
        parser.error("please give a file name")

#-----------------------------------------------------
#-----------------------------------------------------
sys.argv = sys.argv[:1] + ['-b'] + sys.argv[1:]

from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TH1D, TFile, TLatex, TLegend
from ROOT import gROOT, gBenchmark, gDirectory, gStyle

from tdrstyle import *

def setCanvasStyle( canvas ):
    canvas.SetFillColor(0)
    canvas.SetFrameFillColor(0)
    canvas.SetFrameBorderMode(0)

def set1DHistoStyle( h1d ):
    h1d.SetLineWidth(2)

def setTextStyle( tx ):
    tx.SetTextSize(0.034)
    tx.SetLineWidth(2)

def setLegendStyle( lg ):
        lg.SetFillColor(10)
        lg.SetBorderSize(1)

gROOT.Reset()
gBenchmark.Start( 'exportPlots' )

rfilename = options.filename
craft     = 'CMS Preliminary '

if (os.path.isfile(rfilename)) == False:
	print 'exportPlots> root file not found'
	sys.exit(1)

rootfile = TFile(rfilename,'R')

rootfile.cd('/l1Analyzer')

ttbits = ['24','25','26','27','28','29','30','31']
prefix = ['PacTTU.Timing.vs.Run.Bit.']

outdir = './results-L2/'

#................

excode = os.path.isdir(outdir)
if excode == 0:
	cmd = 'mkdir ' + outdir
	os.system(cmd)

gStyle.SetPalette(1)

###############################

runlist = []
#runfile = open( 'runlist.txt','r')
runfile = open( 'list_of_mubkg_runs.txt','r')
for run in runfile:
	runlist.append( run[:-1] )
runfile.close()
print runlist


#................
for histoname in prefix:

	for bit in ttbits:
		
		cname = histoname + bit + '.L2'
		c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
		setCanvasStyle( c1 )
		setTDRStyle()
		hname = histoname + bit
		h1 = gDirectory.FindObjectAny( hname )

		if h1 != None:
			#h1.SetStats(False)
			set1DHistoStyle( h1 )

			h1.GetXaxis().SetLabelColor(10)
			h1.GetXaxis().SetNdivisions(199)
			h1.GetYaxis().SetTitle("Bx(Pac)-Bx(TTU)")
                        h1.SetStats(False)
			c1.cd()
                        c1.SetGridx()
                        
			h1.Draw("box")
			
			##Add the fucking run ids on the X axis
			x0=0.0
			offset=2.00
			runtext=[]
			for run in runlist:
				texa = TLatex(0.0+x0, -4.2, run )
				texa.SetTextSize(0.022)
				texa.SetTextAngle(80)
				texa.SetLineWidth(1);
				x0+=offset
				runtext.append(texa)
			for run in runtext:
				run.Draw()
						
			outname = outdir + histoname + bit + '.png'
			c1.Modified()
			c1.Print( outname )
			

print 'Okey. all done'

