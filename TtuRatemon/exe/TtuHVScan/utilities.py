from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TH1D, TFile, TLatex, TGraph, TLegend, TGraphErrors
from ROOT import gROOT, gBenchmark, gDirectory
from array import array

logScale = False

def setCanvasStyle( canvas ):
	canvas.SetFillColor(0)
	canvas.SetFrameFillColor(0)
	canvas.SetFrameBorderMode(0)
	if logScale:
		canvas.SetLogy()
	canvas.SetGridy()
	
def set1DHistoStyle( h1d ):
	h1d.SetLineWidth(2)

def setTextStyle( tx ):
	tx.SetTextSize(0.034)
	tx.SetLineWidth(1)

def setLegendStyle( lg ):
	lg.SetFillColor(10)
	lg.SetBorderSize(1)


def exportGraph( out, xval, yval):
	outfile = open(out,'w')
	k=0
	for xv in xval:
		#print xv, yval[k]
		outfile.writelines( str(xv) + ' ' + str(yval[k]) + '\n')
		k=k+1
	outfile.close()

def getGraphFrom( datain ):
	indata = open( datain, 'r')
	xd = array('d')
	yd = array('d')
	for line in indata.readlines():
		data = line.split()
		xd.append( float( data[0]) )
		yd.append( float( data[1]) )
	gg = TGraph( len(xd), xd, yd )
	return gg

