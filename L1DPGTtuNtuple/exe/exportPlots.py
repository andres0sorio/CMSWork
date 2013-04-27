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
runid     = rfilename.split('-')[2]
craft     = 'First Collisions: ' + runid
ttname    = 'tt bit: '

if (os.path.isfile(rfilename)) == False:
	print 'exportPlots> root file not found'
	sys.exit(1)

rootfile = TFile(rfilename,'R')

rootfile.cd('l1gtAnalyzer/')

ttbits = ['24','25','26','27','28','29','30','31']
prefix = ['BX.diff.DT-TTU.bit.',
	  'BX.diff.PAC-TTU.bit.',
	  'Dist.of.bx.Number.TT.Bit.',
	  'BX.diff.DT-TTU.bit.In.Coincidence.',
	  'BX.diff.PAC-TTU.bit.In.Coincidence.']


ttbitsInTrigger = ['3','4','9','40']

algbitsInTrigger = ['124']

selrange = [50, 250, 1370, 1900, 2300, 2800]

outdir = 'ttu-plots-' + runid + '/'

#................

excode = os.path.isdir(outdir)
if excode == 0:
	cmd = 'mkdir ' + outdir
	os.system(cmd)

#................

gStyle.SetPalette(1)

for bit in ttbits:

    cname = 'DTTtu.Diff.' + bit
    c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
    setCanvasStyle( c1 )
    hname = prefix[0] + bit
    h1 = gDirectory.FindObjectAny( hname )

    if h1 != None:
	    h1.SetStats(False)
	    set1DHistoStyle( h1 )
	    ax1 = h1.GetXaxis().SetTitle("Bx(DT)-Bx(Rpc-TTU)");
	    c1.cd()
	    h1.Draw()
	    texa = TLatex( -2.6, ( h1.GetMaximum() * 0.90 ), craft )
	    setTextStyle( texa )
	    texa.Draw()
	    texb = TLatex( -2.6, ( h1.GetMaximum() * 0.85 ), ttname + str(bit) )
	    setTextStyle( texb )
	    texb.Draw()
	    outname = outdir + prefix[0] + bit + '.png'
	    c1.Modified()
	    c1.Print( outname )

    cname = 'PacTtu.Diff.' + bit
    c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
    setCanvasStyle( c1 )
    h1 = gDirectory.FindObjectAny( prefix[1] + bit )

    if h1 != None:
	    
	    set1DHistoStyle( h1 )
	    ax1 = h1.GetXaxis().SetTitle("Bx(Rpc-Pac)-Bx(Rpc-TTU)");
	    c1.cd()
	    h1.Draw()
	    texa = TLatex( -2.6, ( h1.GetMaximum() * 0.90 ), craft )
	    setTextStyle( texa )
	    texa.Draw()
	    texb = TLatex( -2.6, ( h1.GetMaximum() * 0.85 ), ttname + str(bit) )
	    setTextStyle( texb )
	    texb.Draw()
	    outname = outdir + prefix[1] + bit + '.png'
	    c1.Modified()
	    c1.Print( outname )

    cname = 'Bx.Number.Dist.' + bit
    c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
    setCanvasStyle( c1 )
    h1 = gDirectory.FindObjectAny( prefix[2] + bit )

    if  h1 != None:
    
	    ax1 = h1.GetXaxis().SetTitle("Bx number");
	    c1.cd()
	    h1.Draw()
	    texa = TLatex( 50, ( h1.GetMaximum() * 0.95 ), craft )
	    setTextStyle( texa )
	    texa.Draw()
	    texb = TLatex( 50, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
	    setTextStyle( texb )
	    texb.Draw()
	    outname = outdir + prefix[2] + bit + '.png'
	    c1.Modified()
	    c1.Print( outname )

#.......................
plotCoincidence = False

if plotCoincidence:
	
	cname = 'Bx.Number.Dist.RPC.In.Coincidence' + bit
	c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
	setCanvasStyle( c1 )
	h1 = gDirectory.FindObjectAny( prefix[3] + bit )

	if  h1 != None:
    
		ax1 = h1.GetXaxis().SetTitle("Bx number");
		c1.cd()
		h1.Draw()
		texa = TLatex( 50, ( h1.GetMaximum() * 0.95 ), craft )
		setTextStyle( texa )
		texa.Draw()
		texb = TLatex( 50, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
		setTextStyle( texb )
		texb.Draw()
		outname = outdir + prefix[3] + bit + '.png'
		c1.Modified()
		c1.Print( outname )

	cname = 'Bx.Number.Dist.DT.In.Coincidence' + bit
	c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
	setCanvasStyle( c1 )
	h1 = gDirectory.FindObjectAny( prefix[4] + bit )

	if  h1 != None:
    
		ax1 = h1.GetXaxis().SetTitle("Bx number");
		c1.cd()
		h1.Draw()
		texa = TLatex( 50, ( h1.GetMaximum() * 0.95 ), craft )
		setTextStyle( texa )
		texa.Draw()
		texb = TLatex( 50, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
		setTextStyle( texb )
		texb.Draw()
		outname = outdir + prefix[4] + bit + '.png'
		c1.Modified()
		c1.Print( outname )

    #.....................................................................................................

ignore = True

for selbit in ttbitsInTrigger:

	if ignore != True:
		    
		for midpoint in selrange:
			    
			xmin = float(midpoint) - 20.0
			xmax = float(midpoint) + 20.0
			
			cname = 'Dist.of.bx.Number.Comparison.TTBit.' + selbit + '.and.TTU.' + bit + '.in.range.'  +str(midpoint)
			c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
			setCanvasStyle( c1 )
			
			h1 = gDirectory.FindObjectAny('Dist.of.bx.Number')
			h2 = gDirectory.FindObjectAny('Dist.of.bx.Number.TT.Bits.In.Trigger.' + selbit)
			h3 = gDirectory.FindObjectAny('Dist.of.bx.Number.TT.Bit.' + bit)
			
			if ( h1.GetMaximum() > 0  ):
				c1.SetLogy()
				
			legend = TLegend(0.12, 0.66, 0.40, 0.80)
			setLegendStyle(legend)
		    
			if  h1 != None:
    
				ax1 = h1.GetXaxis().SetTitle("Bx number")
				h1.GetXaxis().SetRangeUser(xmin,xmax)
				h1.ShowPeaks()
				
				h1.SetLineColor(1)
				h2.SetLineColor(4)
				h3.SetFillColor(33)
				
				legend.AddEntry(h1,"all events","l")
				legend.AddEntry(h2,"TT bit in trigger: " + selbit,"l")
				legend.AddEntry(h3,"TTU bit: " + bit,"f")
				
				c1.cd()
				h1.Draw()
				texa = TLatex( xmin+5, ( h1.GetMaximum() * 0.95 ), craft )
				setTextStyle( texa )
				texa.Draw()
				#texb = TLatex( xmin+5, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
				#setTextStyle( texb )
				#texb.Draw()
				
				h2.Draw("same")
				h3.Draw("same")
				
				legend.Draw()
				
				outname = outdir + cname  + '.png'
				c1.Modified()
				c1.Print( outname )
				
for selbit in algbitsInTrigger:

	if ignore != True:
		
		for midpoint in selrange:
			
			xmin = float(midpoint) - 20.0
			xmax = float(midpoint) + 20.0
			
			cname = 'Dist.of.bx.Number.Comparison.AlgBit.' + selbit + '.and.TTU.bit.' + bit + '.in.range.'  +str(midpoint)
			c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
			setCanvasStyle( c1 )
			
			h1 = gDirectory.FindObjectAny('Dist.of.bx.Number')
			h2 = gDirectory.FindObjectAny('Dist.of.bx.Number.Alg.Bit.In.Trigger.' + selbit)
			h3 = gDirectory.FindObjectAny('Dist.of.bx.Number.TT.Bit.' + bit)
			
			if ( h1.GetMaximum() > 0  ):
				c1.SetLogy()
				    
			legend = TLegend(0.12, 0.66, 0.40, 0.80)
			setLegendStyle(legend)
			
			if  h1 != None:
				
				ax1 = h1.GetXaxis().SetTitle("Bx number")
				h1.GetXaxis().SetRangeUser(xmin,xmax)
				h1.ShowPeaks()
				
				h1.SetLineColor(1)
				h2.SetLineColor(4)
				h3.SetFillColor(33)
				
				legend.AddEntry(h1,"all events","l")
				legend.AddEntry(h2,"Algo bit in trigger: " + selbit,"l")
				legend.AddEntry(h3,"TTU bit: " + bit,"f")
				
				c1.cd()
				h1.Draw()
				texa = TLatex( xmin+5, ( h1.GetMaximum() * 0.95 ), craft )
				setTextStyle( texa )
				texa.Draw()
				#texb = TLatex( xmin+5, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
				#setTextStyle( texb )
				#texb.Draw()
				
				h2.Draw("same")
				h3.Draw("same")
				
				legend.Draw()
				
				outname = outdir + cname  + '.png'
				c1.Modified()
				c1.Print( outname )
				
#.....................................................................................................

cname = 'Dist.of.bx.Number.TT.Bits'
c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
setCanvasStyle( c1 )
h1 = gDirectory.FindObjectAny( cname )
 
if  h1 != None:
	 
	ax1 = h1.GetXaxis().SetTitle("Bx")
	h1.SetFillColor(33)
	c1.cd()
	h1.Draw("COLZ")
	texa = TLatex( 50, ( h1.GetMaximum() * 0.95 ), craft )
	setTextStyle( texa )
	texa.Draw()
	texb = TLatex( 50, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
	setTextStyle( texb )
	texb.Draw()
	outname = outdir + cname + '.png'
	c1.Modified()
	c1.Print( outname )

cname = 'TechTrigger.Bits'
c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
setCanvasStyle( c1 )
h1 = gDirectory.FindObjectAny( cname )
 
if  h1 != None:
	 
	ax1 = h1.GetXaxis().SetTitle("TT Bit numbers")
	h1.SetFillColor(33)
	c1.cd()
	h1.Draw()
	texa = TLatex( 50, ( h1.GetMaximum() * 0.95 ), craft )
	setTextStyle( texa )
	texa.Draw()
	texb = TLatex( 50, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
	setTextStyle( texb )
	texb.Draw()
	outname = outdir + cname + '.png'
	c1.Modified()
	c1.Print( outname )

cname = 'BX.diff.DT-PAC'
c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
setCanvasStyle( c1 )
h1 = gDirectory.FindObjectAny( cname )
 
if  h1 != None:
	 
	ax1 = h1.GetXaxis().SetTitle("Bx(DT)-Bx(PAC)")
	h1.SetFillColor(33)
	c1.cd()
	h1.Draw()
	texa = TLatex( 50, ( h1.GetMaximum() * 0.95 ), craft )
	setTextStyle( texa )
	texa.Draw()
	texb = TLatex( 50, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
	setTextStyle( texb )
	texb.Draw()
	outname = outdir + cname + '.png'
	c1.Modified()
	c1.Print( outname )

cname = 'BX.diff.DT-PAC.In.Coincidence'
c1 = TCanvas( cname, 'L1GtTtuAnalyzer Plots', 100,30,650,500)
setCanvasStyle( c1 )
h1 = gDirectory.FindObjectAny( cname )
 
if  h1 != None:
	 
	ax1 = h1.GetXaxis().SetTitle("Bx(DT)-Bx(PAC)")
	h1.SetFillColor(33)
	c1.cd()
	h1.Draw()
	texa = TLatex( 50, ( h1.GetMaximum() * 0.95 ), craft )
	setTextStyle( texa )
	texa.Draw()
	texb = TLatex( 50, ( h1.GetMaximum() * 0.90 ), ttname + str(bit) )
	setTextStyle( texb )
	texb.Draw()
	outname = outdir + cname + '.png'
	c1.Modified()
	c1.Print( outname )

#...Produce a nice html page using 'album'
theme = ' -theme=KDE_Style'

target = os.environ['PWD'] + '/' + outdir
cmd = 'album -index index.html -columns 2 ' + target + theme
os.system(cmd)

print 'Okey. all done'

