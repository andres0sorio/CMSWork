#ifndef ISTATISTICDIAGMANAGER_H_
#define ISTATISTICDIAGMANAGER_H_

#include "TTree.h"

/*
#include "TH1.h"
#include "TFile.h"
#include "TObjArray.h"

#include "TCanvas.h"
*/

#include <map>

namespace rpct {

class IStatisticDiagManager {

public:
    virtual void createBranches(TTree& tree) = 0;

    virtual void resetAndConfigHistos() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void readout(bool startAfterReadout) = 0;
    virtual void analyse() = 0;

    virtual void initialize(time_t startTime) = 0;
    virtual void finalize() = 0;

    virtual bool countingEnded(unsigned long long coutingPeriod) = 0;

    virtual std::string getHtml() = 0;

    virtual void setLogScale(bool logScale) = 0;
};

typedef std::map<std::string, IStatisticDiagManager*> StatisticDiagManagersMap;

}
#endif /*ISTATISTICDIAGMANAGER_H_*/
