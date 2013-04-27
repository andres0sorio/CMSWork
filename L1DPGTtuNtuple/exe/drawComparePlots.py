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

from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TH1D, TFile, TLatex, TLegend, TMath, TPaveText
from ROOT import gROOT, gBenchmark, gDirectory, gStyle

def setCanvasStyle( canvas ):
    canvas.SetFillColor(0)
    canvas.SetFrameFillColor(0)
    canvas.SetFrameBorderMode(0)

def set1DHistoStyle( h1d ):
    h1d.SetLineWidth(1)

def setTextStyle( tx ):
    tx.SetTextSize(0.034)
    tx.SetLineWidth(1)

def setLegendStyle( lg ):
        lg.SetFillColor(10)
        lg.SetBorderSize(1)

gROOT.Reset()
gBenchmark.Start( 'exportPlots' )

rfilename = options.filename
runid     = rfilename.split('-')[2]

labels    = []
labels.append('1: bit31')
labels.append('2: bit31 & alg24')
labels.append('3: bit31 & alg24 & Trk')
labels.append('4: All prev. & STA')
labels.append('5: All prev. & GBL')
labels.append('-From here all in .and. bit 31')
labels.append('6: HLT_Activity_DT')
labels.append('7: HLT_Act_DT & alg24')
labels.append('8: HLT_Act_DT & alg24 & Trk')
labels.append('9: All prev. & STA')
labels.append('10: All prev.& GBL')
#labels.append('11: bit31 & DT_HLT')

if (os.path.isfile(rfilename)) == False:
	print 'exportPlots> root file not found'
	sys.exit(1)

rootfile = TFile(rfilename,'R')

rootfile.cd('l1Analyzer/')

outdir = 'ttu-plots-' + runid + '/'

#................

excode = os.path.isdir(outdir)
if excode == 0:
	cmd = 'mkdir ' + outdir
	os.system(cmd)

#................

##gStyle.SetPalette(1)

cname = 'Bit31.comparison.HLT_Activity_DT'
c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
setCanvasStyle( c1 )

hname = 'Bit.31.History.1'
h1 = gDirectory.FindObjectAny( hname )
hname = 'Bit.31.History.2'
h2 = gDirectory.FindObjectAny( hname )
c1.SetLogy()
c1.SetGridy()

if h1 != None:
	h1.SetStats(False)
	set1DHistoStyle( h1 )
	set1DHistoStyle( h2 )
	h1.SetTitle('From HLT_Act_DT Skim: comparison with HLT_Activity_DT')
	h1.SetFillColor(38)
	h2.SetFillColor(36)

	c1.cd()
	h1.Draw()
	h2.Draw('same')
	
	#add labels
	allLabels  = []
	xmin = 0.70
	ymax = h1.GetMaximum() * 0.90
	k=0
	scale = 1000
	pt = TPaveText(0.70,0.50,0.95,0.95,'NDC')
	pt.SetFillColor(0)
	pt.SetBorderSize(1)

	for label in labels:
		pt.AddText( label )
		k=k+1

	pt.Draw()

	#print out bin contents
	nbins = h1.GetNbinsX()
	for i in range(1,nbins+1):
		print h1.GetBinContent(i), ' ', h2.GetBinContent(i)
	
	outname = outdir + cname + '.png'
	c1.Modified()
	c1.Print( outname )

print 'Okey. all done'

