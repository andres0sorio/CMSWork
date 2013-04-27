#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string
from bitstring import BitString #this package does not come by default in Python
from optparse import OptionParser

#-----------------------------------------------------
#-----------------------------------------------------

parser = OptionParser()
parser.add_option("-f", type = "string", dest="infile1",
                  help="input file with majority=4", metavar="INFILE1" )

parser.add_option("-l", type = "string", dest="uselog",
                  help="Use log scale", metavar="USELOG" )

parser.add_option("-o",  type = "string", dest="option",
		  help="An option", metavar="OPTION" )

(options, args) = parser.parse_args()

if options.infile1 is None:
        parser.error("please give file1, file2 is optional")

#-----------------------------------------------------
#-----------------------------------------------------

from TtuHVScan import *
from tdrstyle import *
#-----------------------------------------------------

gROOT.Reset()
gBenchmark.Start( 'exportPlots' )

#-----------------------------------------------------
infiles   = []
infiles = options.infile1.split(',')

#-----------------------------------------------------
if options.uselog == None:
	logScale = False
elif options.uselog == 1:
	logScale = True
else:
	logScale = False
#-----------------------------------------------------
if options.option == None:
	anoption = ''
else:
	anoption = '-' + options.option
#-----------------------------------------------------
#-----------------------------------------------------
#-----------------------------------------------------
outdir = './' 
marker = [20, 21, 22, 23, 29, 25, 23, 21]
colour = [ 2, 2, 2, 2, 2, 1, 2, 3, 6, 7]

graphs = []
graphsCorr = []

results = ScanResults()
results.readinfo( infiles[0] )
#results.setPandT( 972.96, 21.27 )
results.setPandT( 969.67, 21.27 )

prevresults = ScanResults()
prevresults.readinfo( infiles[1] )
#prevresults.setPandT( 973.2, 20.6 )
#prevresults.setPandT( 972.96, 21.27 )
prevresults.setPandT( 972.96, 21.27 )

#-----------------------------------------------------
yyLabel = []
xx     = array('d')
xxCorr = array('d')
xxErr  = array('d')

mask       = [1,1,1,1,1,0,1,1] #8 bits
maskPrev   = [1,1,1,1,1,0,1,1] #8 bits

maxhg = 220
scale = 1

lgxy = [0.12, 0.86, 0.80, 0.96]

labOpt = ': March 18 (Th=220 mV, p=972.96 mbar; T=21.27 C)'

results.getXArrays( xx, xxErr )
results.applyHVCorrection()
results.getXCArrays( xxCorr , xxErr )

for i in range(0, results.maxcols ):
	if mask[i] == 1:
		continue
	yy = array('d')
	yyErr = array('d')
	results.getYArrays( yy, yyErr, i )
	gg = TGraphErrors( len(xx), xx, yy , xxErr, yyErr)
	graphs.append(gg)
	yyLabel.append( results.labels[i] )

for i in range(0, results.maxcols ):
	if mask[i] == 1:
		continue
	yy = array('d')
	yyErr = array('d')
	results.getYArrays( yy, yyErr, i )
	gg = TGraphErrors( len(xx), xxCorr, yy , xxErr, yyErr)
	graphsCorr.append(gg)
	
#-----------------------------------------------------
yyLabelPrev = []
date = ': April 28 (Th=220 mV, p=969.67 mbar; T=21.27 C)'

xx     = array('d')
xxCorr = array('d')
xxErr  = array('d')

prevresults.getXArrays( xx, xxErr )
prevresults.applyHVCorrection()
prevresults.getXCArrays( xxCorr , xxErr )

prevgraphs = []
prevgraphsCorr = []

for i in range(0, prevresults.maxcols ):
	if maskPrev[i] == 1:
		continue
	yy = array('d')
	yyErr = array('d')
	prevresults.getYArrays( yy, yyErr, i )
	gg = TGraphErrors( len(xx), xx, yy , xxErr, yyErr)
	prevgraphs.append(gg)
	yyLabelPrev.append( prevresults.labels[i] )

for i in range(0, prevresults.maxcols ):
	if maskPrev[i] == 1:
		continue
	yy = array('d')
	yyErr = array('d')
	prevresults.getYArrays( yy, yyErr, i )
	gg = TGraphErrors( len(xx), xxCorr, yy , xxErr, yyErr)
	prevgraphsCorr.append(gg)

#-----------------------------------------------------

option    = infiles[0].split('-')

cname = 'hvscan-results' + '-' + option[4] + anoption
c1 = TCanvas( cname, 'HV Scan Plots', 100,30,680,520)
setCanvasStyle( c1 )
c1.cd()

#-----------------------------------------------------

setTDRStyle()
tdrStyle.SetTitleSize(0.04, "XYZ")
tdrStyle.SetLabelSize(0.04, "XYZ")
tdrStyle.SetTitleXOffset(1.01)
tdrStyle.SetTitleYOffset(1.07)

#-----------------------------------------------------

#legend = TLegend(0.12, 0.66, 0.80, 0.86)
legend = TLegend(lgxy[0], lgxy[1], lgxy[2], lgxy[3])

setLegendStyle(legend)
k=0

for g in graphs:
	
	if k == 0:
		g.SetMarkerStyle( marker[k] )
		g.SetMarkerColor( colour[k] )
		g.SetMinimum(-10)
		g.SetMaximum(maxhg)
		g.SetLineStyle(1)
		gHist = g.GetHistogram()            # get this explicity to access the axes
		gHist.SetXTitle("HV [kV]")
		gHist.SetYTitle("Rate [Hz]") 
		gHist.SetTitle("")
		nbins = gHist.GetNbinsX()
		legend.AddEntry(g,yyLabel[k] + labOpt,"p")
		gHist.Draw();
		g.Draw('ACP')

	else:
		
		g.SetMarkerStyle( marker[k] )
		g.SetMarkerColor( colour[k] )
		g.SetLineStyle(1)
		legend.AddEntry(g,yyLabel[k] + labOpt ,"p")
		g.Draw('CP')
		
		
	k=k+1
k=0
for pg in prevgraphs:
	pg.SetMarkerStyle( marker[-1] )
	pg.SetMarkerColor( 4 )
	pg.SetLineStyle(1)
	legend.AddEntry(pg,yyLabelPrev[k]+date,"p")
	pg.Draw('CP')
	k=k+1

legend.Draw()	
outname = outdir + cname + '.png'
c1.Modified()
c1.Print( outname )

#-----------------------------------------------------

c1.Clear()
cname = 'hvscan-corr-results' + '-' + option[4] + anoption

#legend = TLegend(0.12, 0.66, 0.36, 0.96)
legend = TLegend(lgxy[0], lgxy[1], lgxy[2], lgxy[3])

setLegendStyle(legend)
k=0

for g in graphsCorr:
		
	if k == 0:
		g.SetMarkerStyle( marker[k] )
		g.SetMarkerColor( colour[k] )
		g.SetMinimum(-10)
		g.SetMaximum(maxhg)
		g.SetLineStyle(1)
		gHist = g.GetHistogram()            # get this explicity to access the axes
		gHist.SetXTitle("HV [kV]")
		gHist.SetYTitle("Rate [Hz]") 
		gHist.SetTitle("")
		nbins = gHist.GetNbinsX()
		legend.AddEntry(g,yyLabel[k]+ labOpt,"p")
		gHist.Draw();
		g.Draw('ACP')

	else:
		g.SetMarkerStyle( marker[k] )
		g.SetMarkerColor( colour[k] )
		g.SetLineStyle(1)
		legend.AddEntry(g,yyLabel[k]+ labOpt,"p")
		g.Draw('CP')
		
	k=k+1
k=0
for pg in prevgraphsCorr:
	pg.SetMarkerStyle( marker[-1] )
	pg.SetMarkerColor( 4 )
	pg.SetLineStyle(1)
	legend.AddEntry(pg,yyLabelPrev[k]+date,"p")
	pg.Draw('CP')
	k=k+1

legend.Draw()
outname = outdir + cname + '.png'
c1.Modified()
c1.Print( outname )
