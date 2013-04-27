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
parser.add_option("-v", type = "string", dest="cmsswver",
                  help="CMSSW version", metavar="CMSSW" )

parser.add_option("-a", type = "string", dest="add",
                  help="add to album (yes,no)", metavar="ADD" )

parser.add_option("-i", type = "string", dest="ignore",
                  help="Ignore this sample type", metavar="IGNORE" )

parser.add_option("-c", type = "string", dest="combine",
                  help="Combine plots (yes,no)", metavar="COMBINE" )

parser.add_option("-o", type = "string", dest="comblabel",
                  help="Combine plots label", metavar="COMBINELAB" )

parser.add_option("-d", type = "string", dest="draw",
                  help="Draw single plots", metavar="DRAWSINGLE" )

parser.add_option("-t", type = "string", dest="type",
                  help="Type of data (Private,RelVals,Data)", metavar="TYPE" )

(options, args) = parser.parse_args()

if options.cmsswver is None:
        parser.error("please give a CMSSW version")
	

#-----------------------------------------------------
#-----------------------------------------------------
sys.argv = sys.argv[:1] + ['-b'] + sys.argv[1:]

import ROOT
from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TH1F, TH1D, TFile, TLatex, TLegend, TPaveStats
from ROOT import gROOT, gBenchmark, gDirectory

def setCanvasStyle( canvas ):
	canvas.SetFillColor(0)
	canvas.SetFrameFillColor(0)
	canvas.SetFrameBorderMode(0)

def set1DHistoStyle( h1d ):
	h1d.SetLineWidth(1)
	h1d.SetMarkerStyle(7)

def setTextStyle( tx ):
	tx.SetTextSize(0.034)
	tx.SetLineWidth(1)

def findMaximum( i, j, a_Hlist):
	maxlist=[]
	for subList in a_Hlist:
		hmax = subList[j][i][0].GetMaximum()
		maxlist.append(hmax)
	print maxlist
	i=0
	cmax=0
	pos=0
	for max in maxlist:
		if cmax < max:
			cmax=max
			pos = i
		i=i+1
	return maxlist[pos]

#....................................................................................

gROOT.Reset()
gBenchmark.Start( 'exportPlots' )

#....................................................................................
comblabel = ''
ignoreSamples = []

cmsswverList  = options.cmsswver.split(',')

if options.ignore != None:
	ignoreSamples = options.ignore.split(',')
	
if options.comblabel != None:
	comblabel = options.comblabel
else:
	comblabel = ''

theme = ' -theme=KDE_Style'
all_Histos=[]
rootfileList=[]
samplesList=[]

plotnames = [['TechTrigger.Bits','','1','','Bit number'],
	     ['TrackParticle.Eta.Phi','box','0','','#phi vs #eta'],
	     ['TrackParticle.Pt','','1','L','Pt [GeV/c]'],
	     ['TrackParticle.Pt.TOB','','1','0','Pt [GeV/c]'],
	     ['TrackParticle.Pt.TEC','','1','0','Pt [GeV/c]'],
	     ['TrackParticle.Pt.TOBTEC','','1','0','Pt [GeV/c]'],
	     ['SimTracksPDG','','0','',''],
	     ['SimTracksPDG.Muons','','0','',''],
	     ['TrackParticle.Eta.Phi.TOB','box','0','','#phi vs #eta'],
	     ['TrackParticle.Eta.Phi.TEC','box','0','','#phi vs #eta'],
	     ['TrackParticle.Eta.Phi.TOBTEC','box','0','','#phi vs #eta']]

tobprefix='TrackParticle.Pt.TOB'
tecprefix='TrackParticle.Pt.TEC'
toeprefix='TrackParticle.Pt.TOE'

tt_Bits = [24,25]

for k in tt_Bits:
	plotnames.append( [ tobprefix+'.' + str(k), '','1','0','Pt [GeV/c]' ] )
	plotnames.append( [ tecprefix+'.' + str(k), '','1','0','Pt [GeV/c]' ] )
	plotnames.append( [ toeprefix+'.' + str(k), '','1','0','Pt [GeV/c]' ] )


colourTable = [ROOT.kBlack,
	       ROOT.kRed,
	       ROOT.kBlue,
	       ROOT.kGreen,
	       ROOT.kOrange,
	       ROOT.kPink+4,
	       ROOT.kGreen+4,
	       ROOT.kCyan,
	       ROOT.kOrange+1]

type = ''
if options.type != None:
	type = '/' + options.type + '-'
else:
	type = '/RelVals-'

for cmsswver in cmsswverList:

	target = os.environ['PWD'] + type + 'Results/' + cmsswver + '/'
	
	target_plots = os.environ['PWD'] + type + 'Plots/' + cmsswver + '/'

	excode  = os.path.isdir( target_plots )

        if excode == False:
                cmd = ('mkdir ' + target_plots )
                os.system(cmd)

	cmd = 'ls ' + target + '*.root'
	raw_result = os.popen(cmd,'r').readlines()

	k = 0
	
	this_version_histos=[]
	this_version_samples=[]
	
	for item in raw_result:

		file = item[:-1]
		if (os.path.isfile(file)) == False:
			continue

		rpos_i = file.rfind(cmsswver)+len(cmsswver)+1
		rpos_f = file.rfind('.')
		sample = file[rpos_i:rpos_f]

		skipThis = False
		for ignoreThis in ignoreSamples:
			if sample == ignoreThis:
				skipThis = True

		if skipThis == True:
			continue
		
		rootfile = TFile(file,'R')
		rootfileList.append( rootfile )
		rootfile.cd('l1gtrpctt/')

		outdir = target_plots + 'validation-plots-' + sample + '/'

		this_version_samples.append( sample )
		
                #....................................................................................
	
		excode = os.path.isdir(outdir)
		if excode == 0:
			cmd = 'mkdir ' + outdir
			os.system(cmd)

		this_sample_histos=[]

		for plotname in plotnames:

			cname = 'RelVal-' + sample + '-' + plotname[0]
			c1 = TCanvas( cname, 'L1GtTechTrig Plots', 100,30,650,500)
			setCanvasStyle( c1 )
			hname = plotname[0]
			h1 = gDirectory.FindObjectAny( hname )

	                #....................................................................................
		
			if h1 != None:
				c1.cd()
				set1DHistoStyle( h1 )
				ax1 = h1.GetXaxis().SetTitle(plotname[4]);
				if plotname[3] == 'L':
					c1.SetLogy()
				h1.Draw(plotname[1])
				texa = TLatex( 26, ( h1.GetMaximum() * 0.90 ), sample )
				setTextStyle( texa )
				texa.Draw()
				outname = outdir + plotname[0]  + '.png'
				c1.Modified()
				c1.Print( outname )
				if plotname[2] == '1':
					this_sample_histos.append( ( h1, plotname[3] ) )
          		#....................................................................................

		this_version_histos.append( this_sample_histos )
		
	all_Histos.append( this_version_histos )

	samplesList.append( this_version_samples )
	
#....................................................................................
# ... Combine histograms of different versions

if options.combine != 'yes':
	target = os.environ['PWD'] + type + 'Plots/'
	cmd = 'album -index index.html -columns 2 ' + target + theme
	os.system(cmd)
	sys.exit(1)
	
canvas  = []
legends = []
indx1   = 0
indx2   = 0
setHistos = all_Histos[0] #take first version on the list
maxHistos = len(plotnames)

#print len(all_Histos[0]),len(all_Histos[1])

maxsamp = len(all_Histos[0])
for i in range(1,len(all_Histos)):
	lgth = len ( all_Histos[i] )
	if maxsamp != lgth:
		print 'different sample size: check ignore option'
		sys.exit()


for ithsample in setHistos:
	i=0
	print ithsample
	for hh in ithsample:
		cname = 'RelVal-CMSSW-Combined-'+ comblabel +'.' + str(i) + '.' + samplesList[indx1][indx2]
		c2 = TCanvas( cname , 'L1GtTechTrig Plots', 100,30,650,500)
		setCanvasStyle( c2 )
		c2.cd()
		hmax = findMaximum( i , indx2, all_Histos )
		if hmax != 0:
			hh[0].SetMaximum( hmax + hmax*0.5)
		if hh[1] == 'L':
			c2.SetLogy()
		hh[0].Draw()
		leg = TLegend(0.6, 0.7, 0.85, 0.95);
		leg.AddEntry(hh[0], cmsswverList[indx1], "l");
		canvas.append( c2 )
		legends.append( leg )
		i=i+1
	
	indx2 = indx2 + 1

i=0
if len(all_Histos) > 1:
	for indx1 in range(1, len(all_Histos)):
		i=0
		setHistos = all_Histos[indx1]
		for ithsample in setHistos:
			for hh in ithsample:
				canvas[i].cd()
				legends[i].AddEntry(hh[0], cmsswverList[indx1], "l");
				hh[0].SetLineColor( colourTable[indx1] )
				hh[0].SetMarkerColor( colourTable[indx1] )
				stats =  hh[0].FindObject("stats")
			##stats.SetX1NDC(0.5)
			##stats.SetX2NDC(0.7)
				hh[0].Draw('sames')
				i=i+1


outdir = os.environ['PWD'] + type + 'Plots/' + 'Combined-' + comblabel +  '/'

excode  = os.path.isdir( outdir )

if excode == False:
	cmd = ('mkdir ' + outdir )
	os.system(cmd)

i=0
for c1 in canvas:
	c1.cd()
	legends[i].Draw()
	cname = c1.GetName()
	outname = outdir + cname  + '.png'
	c1.Modified()
	c1.Print( outname )
	i=i+1
	
#....................................................................................
#... Produce a nice html page using 'album'


target = os.environ['PWD'] + type + 'Plots/'
cmd = 'album -index index.html -columns 2 ' + target + theme
os.system(cmd)

	

