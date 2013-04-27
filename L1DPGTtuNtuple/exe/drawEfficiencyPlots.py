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

from tdrstyle import *

def setCanvasStyle( canvas ):
    canvas.SetFillColor(0)
    canvas.SetFrameFillColor(0)
    canvas.SetFrameBorderMode(0)

def set1DHistoStyle( h1d ):
    h1d.SetLineWidth(1)
    h1d.SetMarkerStyle(7)
    h1d.SetMarkerSize(0.8)
        
def setTextStyle( tx ):
    tx.SetTextSize(0.034)
    tx.SetLineWidth(1)

def setLegendStyle( lg ):
        lg.SetFillColor(10)
        lg.SetBorderSize(1)

gROOT.Reset()
gBenchmark.Start( 'exportPlots' )

rfilename = options.filename

# 
# .....................................................................................
# Efficiency plots
#

mutype   = ['SA','GB','TR']
variable = ['Pt','Eta']
plotname = 'Efficiency-vs-Bit31'
bitname  = 'Bit.31'
bitnames = ['Bit.24','Bit.25','Bit.31']

outpath  = './efficiencies/'

if (os.path.isfile(rfilename)) == False:
	print 'exportPlots> root file not found'
	sys.exit(1)

rootfile = TFile(rfilename,'R')
rootfile.cd('l1Analyzer/')

#.........................................................................................

daxisLabels = ['Pt [Gev]','#eta']

for type in mutype:
        k=0
        for var in variable:

                ax1 = daxisLabels[k]

                for bitname in bitnames:
                
                        hname    = type + '.muons.' + var
                        h1 = gDirectory.FindObjectAny( hname )
                        hname    = type + '.' + var + '.Bit.31'
                        h2 = gDirectory.FindObjectAny( hname )
                
                        cname = 'Rough-Efficiencies-' + type + '-' + var + '-' + bitname
                
                        c1 = TCanvas( cname, 'L1Tree-Analysis', 100,30,650,500)
                        c1.SetFillColor(10)
                
                        setTDRStyle()
                        tdrStyle.cd()
                        tdrStyle.SetPalette(1)
                
                        if h1 != None:
                                set1DHistoStyle(h1)
                                set1DHistoStyle(h2)
                                c1.cd()
                                h2.GetXaxis().SetTitle(ax1)
                                h2.Divide(h2,h1,1,1,"B")
                                h2.Draw()
                                c1.Modified()
                                outname = outpath + cname + '.png'
                                c1.Print( outname )

                k=k+1
#.........................................................................................

draw2D = True

ddaxisLabels = ['#eta','#phi [rad]']

ax1 = ddaxisLabels[0]
ax2 = ddaxisLabels[1]

if draw2D: 

        for type in mutype:

                for bit in bitnames:
        
                        hname    = type + '.eta.phi' + '.All.'
                        h1 = gDirectory.FindObjectAny( hname )
                        hname    = type + '.eta.phi' + '.' + bit
                        h2 = gDirectory.FindObjectAny( hname )
                        
                        cname = 'Rough-Efficiencies-' + type + '-' + 'eta.phi' + '-' + bit
                        
                        c1 = TCanvas( cname, 'L1Tree-Analysis', 100,30,750,500)
                        c1.SetFillColor(10)
                        
                        #setTDRStyle()
                        #tdrStyle.SetPalette(1)
                        
                        gStyle.cd()
                        gStyle.SetPalette(1)
                        setCanvasStyle(c1)
                        c1.SetRightMargin(0.13);
                        
                        if h1 != None:
                                c1.cd()
                                h2.Divide(h2,h1,1,1,"B")
                                h2.Draw('COLZ')
                                h2.GetXaxis().SetTitle(ax1)
                                h2.GetYaxis().SetTitle(ax2)
                                c1.Modified()
                                outname = outpath + cname + '.png'
                                c1.Print( outname )
                                
#.........................................................................................

theme  = ' -theme=KDE_Style'
target = os.environ['PWD'] + '/efficiencies/'
cmd    = 'album -index index.html -columns 2 ' + target + theme
os.system(cmd)



print 'Okey. all done'

