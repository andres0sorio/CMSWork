// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"

#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"
#include "DataFormats/FEDRawData/interface/FEDRawData.h"
 
#include "DataFormats/FEDRawData/interface/FEDNumbering.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <iostream>
#include <utility>
#include <string>

//
// class declaration
//

class RPCL1RateOverview : public edm::EDAnalyzer {
   public:
      explicit RPCL1RateOverview(const edm::ParameterSet&);
      ~RPCL1RateOverview();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
      TH1D* Bx_Per_Lumi_h;

      TH1D* RPC_Barrel_Triggers_Per_Lumi_h;
      TH1D* RPC_Endcap_Triggers_Per_Lumi_h;
      TH1D* DT_Triggers_Per_Lumi_h;
      TH1D* CSC_Triggers_Per_Lumi_h;

      TH1D* RPC_Barrel_Rates_Per_Lumi_h;
      TH1D* RPC_Endcap_Rates_Per_Lumi_h;
      TH1D* DT_Rates_Per_Lumi_h;
      TH1D* CSC_Rates_Per_Lumi_h;

//      std::pair<int, TH1D*> run_lumis;
//      std::vector< std::pair<int, TH1D*> > vector_run_lumi;
//
//      std::pair<int, TH1D*> Trigs_RPC_barrel;
//      std::vector< std::pair<int, TH1D*> > vector_Trigs_RPC_barrel;
//      std::pair<int, TH1D*> Trigs_RPC_endcap;
//      std::vector< std::pair<int, TH1D*> > vector_Trigs_RPC_endcap;
//      std::pair<int, TH1D*> Trigs_CSC;
//      std::vector< std::pair<int, TH1D*> > vector_Trigs_CSC;
//      std::pair<int, TH1D*> Trigs_DT;
//      std::vector< std::pair<int, TH1D*> > vector_Trigs_DT;
      
      int lumiblocks;
      int DT_Trigs_lumi;
      int CSC_Trigs_lumi;
      int RPC_Trigs_lumi;
      int RPCe_Trigs_lumi;
      int current_run;
      int current_lumi;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
