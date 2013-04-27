#ifndef UTILITIES_H
#define UTILITIES_H


#include "CommonIncludes.h"

#include <TFile.h>
#include <TDirectory.h>
#include <TList.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TF2.h>
#include <TString.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TSystem.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TMath.h>
#include <TNamed.h>
#include <TSystem.h>
#include <TObject.h>
#include <TObjArray.h>
#include <TPaveLabel.h>
#include <TKey.h>
#include <TLegend.h>
#include <TLine.h>
#include <TError.h>
#include <TFrame.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <TPaveLabel.h>

//File utilities

void getListOfFiles(const char *, TList *);

void getListOfFiles(const char *, std::vector<std::ifstream*> &);

void getListOfFiles(const char *, TList *, std::vector<double> &, std::vector<double> &);

void readData(const char *source,
	      std::vector<double> &);

void readData(const char *source,
	      std::vector<double> &,
	      std::vector<double> &);

void readData(const char *source,
	      std::vector<double> &,
	      std::vector<double> &,
	      std::vector<double> &);

void readData(std::ifstream *,
	      std::vector<double> &,
	      std::vector<double> &,
	      std::vector<double> &);

//Data utilities

void transferResults(std::vector<double> &, 
		     std::vector<double> &);

//Graphics utilities

void setAxisOptions(TAxis *);

void setAxisOptions(TGaxis *);

void setHistogramsOptions(TH1D *);

void setHistogramsOptions(TH2D *,
			  const char *, 
			  const char *);

void setGraphOptions(TGraph     &);

void setGraphOptions(TGraph2D   &);

//void setGraphOptions(TGraph2D   &,
//		     const char *, 
//		     const char *);

void setGraphOptions(TF1        &, 
		     const char *, 
		     const char *);

void setGraphOptions(TF2        &, 
		     const char *, 
		     const char *);

void preparePlotArea(TCanvas *, TPad *);

void setLegendOptions(TLegend * );

void setStyleOptions(TStyle *);

void setFrameOptions( TPad *, char *, char *);

int  findBestQuadrant(TH1D *);

void createGIF(TString );

void plotDot( double, double , int , int , double);

void addText(TLatex &, const char *);

void drawValueBox(double , double , double , int);

void drawAxes(double , double );

//Text utilities

void print_message(const char *);

void print_values(const char *,double *, int );

void print_message(const char *, double );

///Log Likelihood
void getDistHistogram(TFile *, const char *, const char *, TH1D *);

void findHistogram(const char *, TH1D *, TKey *);

void getDistAttributes( TList *, const char *, double *);

void ReadParameters( std::vector<double> &,
		     std::vector<double> &,
		     std::vector<double> &,
		     std::vector<double> &,
		     std::vector<double> &,
		     std::vector<double> & );

void closeListOfFiles(std::vector<ifstream*> &);

void exportData( std::ofstream *, 
		 const std::vector<double> & ,
		 const std::vector<double> & ,
		 const std::vector<double> & );

void exportData( const char *, 
		 const std::vector<double> & );

void checkData(std::vector<double> &,
	       std::vector<double> &,
	       std::vector<double> &);

#endif
