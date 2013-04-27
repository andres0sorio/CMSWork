/*
 * TTUStatisticDiagManager.cpp
 *
 *  Created on: Apr 27, 2010
 *
 *      Author: aosorio ( aosorio@cern.ch )
 */

#include "TTUStatisticDiagManager.h"

#include "TFrame.h"
#include "TROOT.h"
#include <sys/time.h>
#include <TRandom3.h>

using namespace std;

namespace rpct {

  TTUStatisticDiagManager::TTUStatisticDiagManager(std::string name,
						   std::string picturesDir, SorterCrate* sc, bool useLog) {
    
    name_ = name;
    picturesDir_ = picturesDir;
    m_SC = sc;
    m_useLogScale = useLog;
    m_useLogScale = false;
    m_maxWheels = 5;
    m_maxSectors = 12;
    
    barrelPaveText_ = new TPaveText(0.98, 0.1, 0.99, 0.9, "BRNDC");
    setAlarmOptions( barrelPaveText_ );
    
    for (unsigned int iK=0; iK < m_maxSectors; ++iK) {
      TPaveText * paveText = new TPaveText(0.98, 0.1, 0.99, 0.9, "BRNDC");
      setAlarmOptions( paveText );
      sectorPaveText_.push_back( paveText );
    }
    
    m_histogramRecords = new TTUHistogramRecord();
    
    initializeConstants();
    
    //... Wheel rates
    
    string canvasName("TtuWheelRatesGraphs");
    
    TCanvas * canvas1 = new TCanvas(canvasName.c_str(), canvasName.c_str(),
				    300, 10, 1000, 500);
    
    canvas1->cd()->SetFillColor(10);
    canvas1->cd()->SetGrid();
    canvas1->cd()->SetLeftMargin(0.05);
    canvas1->cd()->SetRightMargin(0.02);
    canvas1->cd()->SetTopMargin(0.15);
    
    canvases_.push_back(canvas1);
    
    picturesNames_.push_back(name_ + "_" + canvasName + ".png");
    picturesDirs_.push_back(picturesDir_ + "/" + picturesNames_.back());
    
    fsBarrelRateLegend1_ = new TLegend(0.40, 0.88, 0.60, 0.98);

    setLegendOptions( fsBarrelRateLegend1_ );

    for (unsigned int iHist = 0; iHist < m_maxWheels; ++iHist) {
      
      ostringstream nameH;
      nameH << "wheelRate_" << iHist;
      
      TGraph* graph = new TGraph();
      wheelRateGraphs_.push_back(graph);
      graph->SetLineColor(m_ttu_WheelColour[iHist]);
      graph->SetLineWidth(1);
      graph->SetMarkerColor(m_ttu_WheelColour[iHist]);
      graph->SetMarkerStyle(23);
      graph->SetMarkerSize(0.4);
      graph->GetXaxis()->SetTitle("time [s]");
      graph->GetYaxis()->SetTitle("rate [Hz]");
      graph->GetXaxis()->SetTimeDisplay(1);
      graph->GetXaxis()->SetTimeFormat("%H:%M:%S");
      
      ostringstream title;
      title << "Wheel_" << m_ttu_NWheel[iHist];
      graph->SetTitle(title.str().c_str());
      
      fsBarrelRateLegend1_->AddEntry(graph,"", "LP");
      
      canvas1->cd();
      
      if (m_useLogScale)
	canvas1->cd()->SetLogy();
      
      if (iHist == 0) {
	graph->GetXaxis()->SetTitle("time");
	graph->GetYaxis()->SetTitle("rate [Hz]");
	graph->GetYaxis()->SetTitleOffset(0.7);
	graph->GetXaxis()->SetLabelSize(0.06);
	graph->GetHistogram()->SetTitle("");
	graph->SetMinimum(0.);
	graph->Draw("APL");
      } else {
	graph->Draw("PL");
      }

    } // wheel rates
    
    rateGraphLegendEntries_.push_back( fsBarrelRateLegend1_ );

    fsBarrelRateLegend1_->Draw();

    //... Sector Rates: 12 sec x 5 wheels (each sector combined in same plot)
    
    canvasName = "TtuSectorRateGraphs";
    
    TCanvas* canvas2 = new TCanvas(canvasName.c_str(), canvasName.c_str(), 200,
				   10, 1000, 1000);
    canvas2->cd()->SetFillColor(10);
    canvas2->SetGrid();
    canvas2->Divide(3, 4);
    
    canvases_.push_back(canvas2);
    picturesNames_.push_back(name_ + "_" + canvasName + ".png");
    
    picturesDirs_.push_back(picturesDir_ + "/" + picturesNames_.back());
    
      for (unsigned int iHist = 0; iHist < m_maxSectors; ++iHist) {
	
	for (unsigned int jHist = 0; jHist < m_maxWheels; ++jHist) {
	  
	ostringstream nameH;
	nameH << "sectorRate_" << iHist << "_" << jHist;

	ostringstream sectorH;
	sectorH << "Sector: " << (iHist+1);

	if (m_useLogScale)
	  canvas2->cd()->SetLogy();
	
	canvas2->cd(iHist + 1);
		
	TGraph* graph = new TGraph();
	sectorRateGraphs_.push_back(graph);
	graph->SetLineColor(m_ttu_WheelColour[jHist]);
	graph->SetLineWidth(1);
	graph->SetMarkerColor(m_ttu_WheelColour[jHist]);
	graph->SetMarkerStyle(23);
	graph->SetMarkerSize(0.4);
	graph->GetXaxis()->SetTitle("time [s]");
	graph->GetYaxis()->SetTitle("rate [Hz]");
	graph->GetXaxis()->SetTimeDisplay(1);
	graph->GetXaxis()->SetTimeFormat("%H:%M:%S");
	
	if (jHist == 0) {
	  graph->GetXaxis()->SetTitle("time");
	  graph->GetYaxis()->SetTitle("rate [Hz]");
	  graph->GetYaxis()->SetTitleOffset(0.7);
	  graph->GetXaxis()->SetLabelSize(0.06);
	  graph->GetHistogram()->SetTitle(sectorH.str().c_str());
	  graph->SetMinimum(0.);
	  graph->Draw("APL");
	} else {
	  graph->Draw("PL");
	}
	
      }
      
    } // sector rates

    cout << "sectorRates: " << sectorRateGraphs_.size() << endl;
    
    
  }
  
  TTUStatisticDiagManager::~TTUStatisticDiagManager() {
    
    cout << " destructor starts now" << endl;

    // delete barrelPaveText_;

    for (unsigned int iC = 0; iC < canvases_.size(); iC++) {
      delete canvases_[iC];
    }
    canvases_.clear();
    
    for (unsigned int iH = 0; iH < wheelRateGraphs_.size(); iH++) {
      delete wheelRateGraphs_[iH];
    }
    
    wheelRateGraphs_.clear();
    
    for (unsigned int iH = 0; iH < sectorRateGraphs_.size(); iH++) {
      delete sectorRateGraphs_[iH];
    }

    for (unsigned int iH = 0; iH < rateGraphLegendEntries_.size(); iH++) {
      delete  rateGraphLegendEntries_[iH];
    }
    
    sectorRateGraphs_.clear();
    
    m_ttu_NWheel.clear();
    m_ttu_WheelColour.clear();
    m_ttu_WheelMarker.clear();
    
  }
  
  void TTUStatisticDiagManager::initializeConstants() {
    
    m_ttu_NWheel[0] = 1;
    m_ttu_NWheel[1] = 2;
    m_ttu_NWheel[2] = 0;
    m_ttu_NWheel[3] = -1;
    m_ttu_NWheel[4] = -2;
    
    m_ttu_WheelColour[0] = 2;
    m_ttu_WheelColour[1] = 3;
    m_ttu_WheelColour[2] = 4;
    m_ttu_WheelColour[3] = 6;
    m_ttu_WheelColour[4] = 8;
    
    m_ttu_WheelMarker[0] = 20;
    m_ttu_WheelMarker[1] = 21;
    m_ttu_WheelMarker[2] = 22;
    m_ttu_WheelMarker[3] = 23;
    m_ttu_WheelMarker[4] = 24;
    
    m_ttu_WheelTB[0] = std::string("TTU_1");
    m_ttu_WheelTB[1] = std::string("TTU_1");
    m_ttu_WheelTB[2] = std::string("TTU_2");
    m_ttu_WheelTB[3] = std::string("TTU_3");
    m_ttu_WheelTB[4] = std::string("TTU_3");
    
    m_ttu_WheelPAC[0] = std::string("TTUTRIG 8");
    m_ttu_WheelPAC[1] = std::string("TTUTRIG 9");
    m_ttu_WheelPAC[2] = std::string("TTUTRIG 8");
    m_ttu_WheelPAC[3] = std::string("TTUTRIG 8");
    m_ttu_WheelPAC[4] = std::string("TTUTRIG 9");
    
    m_useLogScale = false;
    
  }
  
  void TTUStatisticDiagManager::createBranches(TTree& tree) {
    
    std::string name("TTUStatistics");
    m_histogramRecords->createBranch(tree, name);
    
  }
  
  void TTUStatisticDiagManager::resetAndConfigHistos() {
    
    //... Reset counters: For TTU there is no need
    
  }
  
  void TTUStatisticDiagManager::start() {
    
    //... This happens just right before enter in external Loop()
        
    timeval timv;
    gettimeofday(&timv, 0);
    m_histogramRecords->setStartTimeBuf(timv.tv_sec);
        
  }

  void TTUStatisticDiagManager::stop() {
    
    //... end of external Loop()
    
  }
  
  void TTUStatisticDiagManager::readout(bool startAfterReadout) {
    
    time_t timer = 0;
    timer = time(NULL);
    m_histogramRecords->setStopTime(timer);
    
    if (startAfterReadout) {
      timer = time(NULL);
      m_histogramRecords->setStartTimeBuf(timer);
    }

    TRandom3 * rdn = new TRandom3(0);
    float wfactor=1.0;

    //TODO: read out the counters here and fill in the arrays with the data
    int maxSectors = 12;
    
    std::vector<int> sectorCntr;
    
    for ( int i=0; i < 3; ++i ) {

      for ( int k=0; k < 2; ++k ) {

	if ( i == 1 && k == 1) 
	  continue;

	for ( int iK=0; iK < 12; ++iK ) {

	  int tmp = (int) (k+5) + 10*wfactor*( (rdn->Rndm()) * ( .8 ));
	  if ( i == 0  && iK == 4 ) 
	    sectorCntr.push_back(tmp * 10000.00); //the order should be ttu_1,2,3 x TRIG1,2 x 12
	  else
	    sectorCntr.push_back(tmp); 
	}
	
      }
      
    }

    cout << "size of data: " << sectorCntr.size() << endl;

    float rate = 0.0;
    float sum = 0.0;
    float totSum = 0.0;
    int iSec = 0;
    
    for (int iK = 0; iK < maxSectors * 1; ++iK) {
      
      rate = sectorCntr[iK] / 2.0;
      cout << "filling branches>" << iK << " " << rate << endl;  
      m_histogramRecords->branchData_.sectorRateW0_[iSec] = rate;
      cout << "filling branches> sector: " << iSec << " ok done" << endl;  
      sum += rate;
      ++iSec;
    }
    
    totSum += sum;
    
    m_histogramRecords->branchData_.wheelRates_[0] = sum;
    
    sum = 0;
    iSec = 0;
    for (int iK = maxSectors * 1; iK < maxSectors * 2; ++iK) {
      rate = sectorCntr[iK] / 2.0;
      cout << "filling branches>" << iK << " " << rate << endl;  
      m_histogramRecords->branchData_.sectorRateW1_[iSec] = rate;
      cout << "filling branches> sector: " << iSec << " ok done" << endl;  
      sum += rate;
	  ++iSec;
    }
    
    totSum += sum;
    
    m_histogramRecords->branchData_.wheelRates_[1] = sum;
    
    sum = 0;
    iSec = 0;
    for (int iK = maxSectors * 2; iK < maxSectors * 3; ++iK) {
      rate = sectorCntr[iK] / 2.0;
      cout << "filling branches>" << iK << " " << rate << endl;  
      m_histogramRecords->branchData_.sectorRateW2_[iSec] = rate;
      cout << "filling branches> sector: " << iSec << " ok done" << endl;  
      sum += rate;
      ++iSec;
    }
    
    totSum += sum;
    
    m_histogramRecords->branchData_.wheelRates_[2] = sum;
    
    sum = 0;
    iSec = 0;
    for (int iK = maxSectors * 3; iK < maxSectors * 4; ++iK) {
      rate = sectorCntr[iK] / 2.0;
      cout << "filling branches>" << iK << " " << rate << endl;  
      m_histogramRecords->branchData_.sectorRateW3_[iSec] = rate;
      cout << "filling branches> sector: " << iSec << " ok done" << endl;  
      sum += rate;
      ++iSec;
    }
    
    totSum += sum;
    
    m_histogramRecords->branchData_.wheelRates_[3] = sum;
    
    sum = 0;
    iSec = 0;
    for (int iK = maxSectors * 4; iK < maxSectors * 5; ++iK) {
      rate = sectorCntr[iK] / 2.0;
      cout << "filling branches>" << iK << " " << rate << endl;  
      m_histogramRecords->branchData_.sectorRateW4_[iSec] = rate;
      cout << "filling branches>sector: " << iSec << " ok done" << endl;  
      sum += rate;
      ++iSec;
    }
    
    totSum += sum;
    
    m_histogramRecords->branchData_.wheelRates_[4] = sum;
    
    
    sum = 0;
    sectorCntr.clear();
    
  }
  
  void TTUStatisticDiagManager::analyse() {
    
    //TODO
    //... possibly try to extract max and avg rates
    //...
    
    bool counterOverflow = false;
    vector<int> wheelsInOverflow;
    vector<int>::iterator itr;
    unsigned int iHist = 0;
    ostringstream alarmH;
    
    //... Sector rates
    //... S1[w0],S1[W1],S1[W2],S1[W3],S1[W4] ... S12[W0],S12[W1], ...
    
    for (unsigned int iK = 0; iK < (m_maxWheels * m_maxSectors); iK += 5) {
      
      counterOverflow = false;
      
      unsigned int current_time = m_histogramRecords->getStopTime()
	- startTime_;
      
      sectorRateGraphs_[iK + 0]->SetPoint(iteration_, current_time,
					  m_histogramRecords->branchData_.sectorRateW0_[iHist]);
      sectorRateGraphs_[iK + 1]->SetPoint(iteration_, current_time,
					  m_histogramRecords->branchData_.sectorRateW1_[iHist]);
      sectorRateGraphs_[iK + 2]->SetPoint(iteration_, current_time,
					  m_histogramRecords->branchData_.sectorRateW2_[iHist]);
      sectorRateGraphs_[iK + 3]->SetPoint(iteration_, current_time,
					  m_histogramRecords->branchData_.sectorRateW3_[iHist]);
      sectorRateGraphs_[iK + 4]->SetPoint(iteration_, current_time,
					  m_histogramRecords->branchData_.sectorRateW4_[iHist]);
      
      ostringstream sectorH;
      sectorH << "Sector: " << (iHist+1);

      float  rate = m_histogramRecords->branchData_.sectorRateW0_[iHist];
      if ( rate > 10000.0 )
	wheelsInOverflow.push_back( m_ttu_NWheel[0] );
      
      rate = m_histogramRecords->branchData_.sectorRateW1_[iHist];
      if ( rate > 10000.0 )
	wheelsInOverflow.push_back( m_ttu_NWheel[1] );
      
      rate = m_histogramRecords->branchData_.sectorRateW2_[iHist];
      if ( rate > 10000.0 )
	wheelsInOverflow.push_back( m_ttu_NWheel[2] );
      
      rate = m_histogramRecords->branchData_.sectorRateW3_[iHist];
      if ( rate > 10000.0 )
	wheelsInOverflow.push_back( m_ttu_NWheel[3] );
      
      rate = m_histogramRecords->branchData_.sectorRateW4_[iHist];
      if ( rate > 10000.0 )
	wheelsInOverflow.push_back( m_ttu_NWheel[4] );


      for (int k = 0; k < 5; ++k) {
	
	sectorRateGraphs_[iK + k]->GetXaxis()->SetTitle("time");
	sectorRateGraphs_[iK + k]->GetYaxis()->SetTitle("rate [Hz]");
	sectorRateGraphs_[iK + k]->GetYaxis()->SetTitleOffset(0.5);
	sectorRateGraphs_[iK + k]->GetXaxis()->SetLabelSize(0.03);
	sectorRateGraphs_[iK + k]->GetHistogram()->SetTitle(sectorH.str().c_str());
	sectorRateGraphs_[iK + k]->SetMinimum(0.01);
	//sectorRateGraphs_[iK + k]->SetMaximum(500);
	sectorRateGraphs_[iK + k]->GetXaxis()->SetTimeDisplay(1);
	sectorRateGraphs_[iK + k]->GetXaxis()->SetTimeFormat("%H:%M:%S");
		
      }
      
      
      alarmH << "Rate Overflow !! Wheels: ";
      
      for ( itr = wheelsInOverflow.begin(); itr != wheelsInOverflow.end(); ++itr ) {
	alarmH << (*itr) << " ";
	counterOverflow = true;
      } 

      if ( ! counterOverflow )
	alarmH.str("");
      
      sectorPaveText_[iHist]->GetLine(1)->SetText(0, 0, alarmH.str().c_str() );
      canvases_[1]->cd(iHist+1);
      sectorPaveText_[iHist]->Draw();

      wheelsInOverflow.clear();

      ++iHist;
      
      cout << "Sector: " << iHist << endl;

    }
    
    //... Total Wheel Rates
    
    for (unsigned int iK = 0; iK < m_maxWheels; ++iK) {
      
      unsigned int current_time = m_histogramRecords->getStopTime()
	- startTime_;
      
      wheelRateGraphs_[iK]->SetPoint(iteration_, current_time,
				     m_histogramRecords->branchData_.wheelRates_[iK]);
      
      wheelRateGraphs_[iK]->GetXaxis()->SetTitle("time");
      wheelRateGraphs_[iK]->GetYaxis()->SetTitle("rate [Hz]");
      wheelRateGraphs_[iK]->GetYaxis()->SetTitleOffset(0.5);
      wheelRateGraphs_[iK]->GetXaxis()->SetLabelSize(0.03);
      wheelRateGraphs_[iK]->GetHistogram()->SetTitle("");
      wheelRateGraphs_[iK]->SetMinimum(0.01);
      //wheelRateGraphs_[iK]->SetMaximum(500);
      wheelRateGraphs_[iK]->GetXaxis()->SetTimeDisplay(1);
      wheelRateGraphs_[iK]->GetXaxis()->SetTimeFormat("%H:%M:%S");
      
      float rate = m_histogramRecords->branchData_.wheelRates_[iK];

      if ( rate > 10000.0 )
	wheelsInOverflow.push_back( m_ttu_NWheel[iK] );
      
    }

    counterOverflow = false;

    alarmH << "Rate Overflow !! Wheels: ";
      
    for ( itr = wheelsInOverflow.begin(); itr != wheelsInOverflow.end(); ++itr ) {
      alarmH << (*itr) << " ";
      counterOverflow = true;
    } 
    
    if ( ! counterOverflow )
      alarmH.str("");
    
    barrelPaveText_->GetLine(1)->SetText(0, 0, alarmH.str().c_str() );
    canvases_[0]->cd();
    barrelPaveText_->Draw();
    
    wheelsInOverflow.clear();
    
    ///----------making the pictures----------------
    
    for (unsigned int iC = 0; iC < canvases_.size(); iC++) {
      canvases_[iC]->Update();
      canvases_[iC]->Modified();
      canvases_[iC]->Print(picturesDirs_[iC].c_str(), "png");
    }
    
    iteration_++;
    
  }
  
  void TTUStatisticDiagManager::initialize(time_t startTime) {

    iteration_ = 0;
    startTime_ = startTime;
    m_histogramRecords->setStartTimeBuf(0); //Buffer for start of histograming time slice
    m_histogramRecords->setTimerValuePrev(0); //previous
    m_histogramRecords->setTimerValueIntegrated(0);
    
    //TODO check that we got on the x-axis time units
    
    for (unsigned int i = 0; i < wheelRateGraphs_.size(); i++) {
      wheelRateGraphs_[i]->Set(0);
    }

    for (unsigned int i = 0; i < sectorRateGraphs_.size(); i++) {
      sectorRateGraphs_[i]->Set(0);
    }
    
  }
  
  void TTUStatisticDiagManager::finalize() {
    
    for (unsigned int iC = 0; iC < canvases_.size(); iC++) {
      canvases_[iC]->Write();
    }
  }
  
  bool TTUStatisticDiagManager::countingEnded(unsigned long long coutingPeriod) {
    
    unsigned long long counterValue = 0;
    
    if (counterValue > coutingPeriod) {
      return true;
    }
    return false;
    
  }
  
  string TTUStatisticDiagManager::getHtml() {
    
    ostringstream ostr;
    ostr << "<br>\n";
    for (unsigned int i = 0; i < picturesNames_.size(); i++) {
      ostr << "<img src=\"" << "/monitor_pictures/" << picturesNames_[i]
	   << "\">";
      ostr << "<br>\n";
    }
    return ostr.str();
  }
  
  void TTUStatisticDiagManager::setLegendOptions(TLegend * alegend) {
    
    alegend->SetFillColor(10);
    alegend->SetBorderSize(1);
    alegend->SetTextSize(0.03);
    
  }

  void TTUStatisticDiagManager::setAlarmOptions( TPaveText * text) {
   
    text->AddText(" ")->SetTextAlign(32);
    text->AddText(" ")->SetTextAlign(32);
    text->GetLine(1)->SetTextColor(kRed);
    text->GetLine(1)->SetTextSize(0.07);
    text->SetBorderSize(0);
    text->SetFillStyle(0);
    
  }
  
}//rpct
