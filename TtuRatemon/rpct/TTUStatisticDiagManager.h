/*
 * TTUStatisticDiagManager.h
 *
 *  Created on: Apr 27, 2010
 *      Author: aosorio
 */

#ifndef TTUSTATISTICDIAGMANAGER_H_
#define TTUSTATISTICDIAGMANAGER_H_

#include "IStatisticDiagManager.h"

#include "TH1.h"
#include "TFile.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegendEntry.h"
#include "TLegend.h"
#include "TPaveText.h"

#include <sys/time.h>
#include <map>
#include <iostream>
#include <sstream>

namespace rpct {


  class SorterCrate {
  public:
    SorterCrate() {};
    ~SorterCrate() {};
  private:
    
  };
  
  class TTUStatisticDiagManager: public IStatisticDiagManager {
  private:
    
    //................................................................................
    //... Time utilities + Tree data structure
    
    class TTUHistogramRecord {
      
    protected:
      time_t startTimeBuf_; //Buffer for start of histograming time slice
      unsigned long long timerValuePrev_; //previous
      unsigned long long timerValueIntegrated_;
      
      
    public:
      
      TTUHistogramRecord() {
      }
      
      virtual ~TTUHistogramRecord() {
      }
      
      struct TTUBranchData {
	unsigned long long timerValue_;
	unsigned int startTime_; // time_t start of histograming time slice
	unsigned int stopTime_; // time_t start of histograming time slice
	unsigned int runNumber_;
	float wheelRates_[5];
	float sectorRateW0_[12];
	float sectorRateW1_[12];
	float sectorRateW2_[12];
	float sectorRateW3_[12];
	float sectorRateW4_[12];
      };
      
      TTUBranchData branchData_;
      
      TTUBranchData& getBranchData() {
	return branchData_;
      }
      
      void createBranch(TTree& tree, std::string& name) {
	tree.Branch(
		    name.c_str(),
		    &(branchData_.timerValue_),
		    "timerValue/l:startTime_/i:stopTime_/i:runNumber_/i:wheelRates_[5]/f:sectorRateW0_[12]/f:sectorRateW1_[12]/f:sectorRateW2_[12]/f:sectorRateW3_[12]/f:sectorRateW4_[12]/f");
      }
      
      unsigned long long getTimerValue() {
	return branchData_.timerValue_;
      }
      
      void setTimerValue(unsigned long long timerValue) {
	branchData_.timerValue_ = timerValue;
      }
      
      unsigned int getStartTime() {
	return branchData_.startTime_;
      }
      
      void setStartTime(unsigned int startTime) {
	branchData_.startTime_ = startTime;
      }
      
      unsigned int getStopTime() {
	return branchData_.stopTime_;
      }
      
      void setStopTime(unsigned int stopTime) {
	branchData_.stopTime_ = stopTime;
      }
      
      time_t getStartTimeBuf() {
	return startTimeBuf_;
      }
      
      void setStartTimeBuf(time_t startTimeBuf) {
	startTimeBuf_ = startTimeBuf;
      }
      
      unsigned long long getTimerValuePrev() {//previous
	return timerValuePrev_;
      }
      
      void setTimerValuePrev(unsigned long long timerValuePrev) { //previous
	timerValuePrev_ = timerValuePrev;
      }
      
      unsigned long long getTimerValueIntegrated() {
	return timerValueIntegrated_;
      }
      
      void setTimerValueIntegrated(unsigned long long timerValueIntegrated) {
	timerValueIntegrated_ = timerValueIntegrated;
      }
      
    };
    
    //................................................................................
    
  protected:
    
    std::string name_;
    std::string picturesDir_;
    unsigned int iteration_;
    time_t startTime_; //start time of the monitoring job
    
    std::vector<std::string> picturesDirs_;
    std::vector<std::string> picturesNames_;
    
    TFile outFile;
    TObjArray histosArray_;
    TLegend * fsBarrelRateLegend1_;
    TPaveText * barrelPaveText_;
    std::vector<TPaveText *> sectorPaveText_;

    //static log4cplus::Logger logger;
    
    std::vector<TCanvas*> canvases_;
    std::vector<TGraph*> wheelRateGraphs_;
    std::vector<TGraph*> sectorRateGraphs_;
    std::vector<TLegend*> rateGraphLegendEntries_;
    
    TTUHistogramRecord* m_histogramRecords;
    
  public:
    
    TTUStatisticDiagManager(std::string name, std::string picturesDir,
			    SorterCrate*, bool);
    
    virtual ~TTUStatisticDiagManager();
    
    virtual void createBranches(TTree& tree);
    
    virtual void resetAndConfigHistos();
    virtual void start();
    virtual void stop();
    virtual void readout(bool startAfterReadout);
    virtual void analyse();
    
    virtual void initialize(time_t startTime);
    virtual void finalize();
    
    virtual bool countingEnded(unsigned long long countingPeriod);
    
    virtual std::string getHtml();
    
    
    //log scale ofor selected
    virtual void setLogScale(bool logScale) {
      m_useLogScale = logScale;
    }
    
  private:
    
    SorterCrate* m_SC;
    
    void initializeConstants();

    void setLegendOptions(TLegend * );

    void setAlarmOptions(TPaveText * );

    unsigned int m_maxWheels;
    unsigned int m_maxSectors;
    bool m_useLogScale;
    
    std::map<int, int> m_ttu_NWheel;
    std::map<int, int> m_ttu_WheelColour;
    std::map<int, int> m_ttu_WheelMarker;
    std::map<int, std::string> m_ttu_WheelTB;
    std::map<int, std::string> m_ttu_WheelPAC;
    
  };
  
}

#endif /* TTUSTATISTICDIAGMANAGER_H_ */
