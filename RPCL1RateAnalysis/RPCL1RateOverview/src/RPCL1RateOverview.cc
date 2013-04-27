// -*- C++ -*-
//
// Package:    RPCL1RateOverview
// Class:      RPCL1RateOverview
// 
/**\class RPCL1RateOverview RPCL1RateOverview.cc RPCL1RateAnalysis/RPCL1RateOverview/src/RPCL1RateOverview.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  
//         Created:  Thu Mar 15 11:21:16 CET 2012
// $Id$
//
//

#include "RPCL1RateAnalysis/RPCL1RateOverview/interface/RPCL1RateOverview.h"

RPCL1RateOverview::RPCL1RateOverview(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


RPCL1RateOverview::~RPCL1RateOverview()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
RPCL1RateOverview::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   lumiblocks++;

   if( (unsigned)current_lumi != iEvent.id().luminosityBlock() ){
     Bx_Per_Lumi_h->Fill(current_lumi, lumiblocks);
     RPC_Barrel_Triggers_Per_Lumi_h->Fill(current_lumi, RPC_Trigs_lumi);
     RPC_Endcap_Triggers_Per_Lumi_h->Fill(current_lumi, RPCe_Trigs_lumi);
     DT_Triggers_Per_Lumi_h->Fill(current_lumi, DT_Trigs_lumi);
     CSC_Triggers_Per_Lumi_h->Fill(current_lumi, CSC_Trigs_lumi);
     
     current_lumi = iEvent.id().luminosityBlock();
     lumiblocks = 0;
     DT_Trigs_lumi =0;
     CSC_Trigs_lumi = 0;
     RPC_Trigs_lumi = 0;
     RPCe_Trigs_lumi = 0;
     if( (unsigned)current_run != iEvent.id().run()){
       //	 run_lumis = make_pair(current_run,Bx_Per_Lumi_h);
       //	 vector_run_lumi.push_back(run_lumis);
       current_run = iEvent.id().run();
     }
   }

   edm::Handle<L1MuGMTReadoutCollection> L1Mu;
   iEvent.getByLabel("hltGtDigis",L1Mu);

   std::vector<L1MuGMTReadoutRecord> gmt_records = L1Mu->getRecords();
   std::vector<L1MuGMTReadoutRecord>::const_iterator igmtrr;
   for(igmtrr=gmt_records.begin(); igmtrr!=gmt_records.end(); igmtrr++) {

     //     run_lumis = make_pair(iEvent.id().run(),Bx_Per_Lumi_h);

     
     std::vector<L1MuRegionalCand>::const_iterator iter1;
     std::vector<L1MuRegionalCand> rmc;

     if(igmtrr->getBxInEvent()==0) {
       //cout << " bx numero " <<  igmtrr->getBxNr() << endl;
     }

     rmc = igmtrr->getDTBXCands();
     for(iter1=rmc.begin(); iter1!=rmc.end(); iter1++) {
       //if ( (unsigned) gmt_.Nrpcb < maxRPC && !(*iter1).empty() ) {
       DT_Trigs_lumi++;
       //cout << "DT Bx " << iter1->bx() << endl;
       //	 if(physVal) {    
       //cout << "DT Eta value " << (*iter1).etaValue() << endl;
       //cout << "DT Phi Value " << (*iter1).phiValue() << endl;
       //cout << "DT Pt Value " << (*iter1).ptValue() << endl;
       //	 } else {
       //cout << "DT packed Eta " << (*iter1).eta_packed() << endl;
       //cout << "DT packed Phi " << (*iter1).phi_packed() << endl;
       //cout << "DT packed Pt " << (*iter1).pt_packed() << endl;
       //	 }
       //       if(!(*iter1).chargeValid()) 	 
	 //cout << "DT charge " << (*iter1).chargeValue() << endl; 
       //cout << "DT Quality " << (*iter1).quality() << endl;
	 //}
     }

     rmc = igmtrr->getCSCCands();
     for(iter1=rmc.begin(); iter1!=rmc.end(); iter1++) {
       //if ( (unsigned) gmt_.Nrpcb < maxRPC && !(*iter1).empty() ) {
       CSC_Trigs_lumi++;
       //cout << "CSC Bx " << iter1->bx() << endl;
       //	 if(physVal) {    
       //cout << "CSC Eta value " << (*iter1).etaValue() << endl;
       //cout << "CSC Phi Value " << (*iter1).phiValue() << endl;
       //cout << "CSC Pt Value " << (*iter1).ptValue() << endl;
       //	 } else {
       //cout << "CSC packed Eta " << (*iter1).eta_packed() << endl;
       //cout << "CSC packed Phi " << (*iter1).phi_packed() << endl;
       //cout << "CSC packed Pt " << (*iter1).pt_packed() << endl;
       //	 }
       //       if(!(*iter1).chargeValid()) 	 
	 //cout << "CSC charge " << (*iter1).chargeValue() << endl; 
       //cout << "CSC Quality " << (*iter1).quality() << endl;
	 //}
     }

     rmc = igmtrr->getBrlRPCCands();
     for(iter1=rmc.begin(); iter1!=rmc.end(); iter1++) {
       //if ( (unsigned) gmt_.Nrpcb < maxRPC && !(*iter1).empty() ) {
       RPC_Trigs_lumi++;
       //cout << "RPC Bx " << iter1->bx() << endl;
       //	 if(physVal) {    
       //cout << "RPC Eta value " << (*iter1).etaValue() << endl;
       //cout << "RPC Phi Value " << (*iter1).phiValue() << endl;
       //cout << "RPC Pt Value " << (*iter1).ptValue() << endl;
       //	 } else {
       //cout << "RPC packed Eta " << (*iter1).eta_packed() << endl;
       //cout << "RPC packed Phi " << (*iter1).phi_packed() << endl;
       //cout << "RPC packed Pt " << (*iter1).pt_packed() << endl;
       //	 }
       //       if(!(*iter1).chargeValid()) 	 
	 //cout << "RPC charge " << (*iter1).chargeValue() << endl; 
       //cout << "RPC Quality " << (*iter1).quality() << endl;
	 //}
     }

     rmc = igmtrr->getFwdRPCCands();
     for(iter1=rmc.begin(); iter1!=rmc.end(); iter1++) {
       //       if ( (unsigned) gmt_.Nrpcb < maxRPC && !(*iter1).empty() ) {
       RPCe_Trigs_lumi++;
       //cout << "RPC Bx " << iter1->bx() << endl;
       //	 if(physVal) {    
       //cout << "RPC End Eta value " << (*iter1).etaValue() << endl;
       //cout << "RPC End Phi Value " << (*iter1).phiValue() << endl;
       //cout << "RPC End Pt Value " << (*iter1).ptValue() << endl;
       //	 } else {
       //cout << "RPC End packed Eta " << (*iter1).eta_packed() << endl;
       //cout << "RPC End packed Phi " << (*iter1).phi_packed() << endl;
       //cout << "RPC End packed Pt " << (*iter1).pt_packed() << endl;
       //	 }
       //       if(!(*iter1).chargeValid()) 	 
	 //cout << "RPC End charge " << (*iter1).chargeValue() << endl; 
       //cout << "RPC End Quality " << (*iter1).quality() << endl;
       //     }
     }
     
     
   }



   edm::Handle<FEDRawDataCollection> buffers;
   iEvent.getByLabel("hltFEDSelector",buffers);

   Handle<TriggerResults> trig;
   iEvent.getByLabel("TriggerResults",trig);

   std::vector<std::string> vec_names = trig->getTriggerNames();
   ////cout << "there are  " << vec_names.size() << " triggers " << endl;
   for(unsigned i = 0; i < vec_names.size(); i++){
     //cout << "name " << i+1 << " " << vec_names[i] << endl;
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
RPCL1RateOverview::beginJob()
{

  edm::Service<TFileService> fs;

  Bx_Per_Lumi_h = fs->make<TH1D>("Bunch_Crossing_Per_Lumi","",1000,0,1000);

  RPC_Barrel_Triggers_Per_Lumi_h = fs->make<TH1D>("RPC_Barrel_Triggers_Per_Lumi","",1000,0,1000);
  RPC_Endcap_Triggers_Per_Lumi_h = fs->make<TH1D>("RPC_Endcap_Triggers_Per_Lumi","",1000,0,1000);
  DT_Triggers_Per_Lumi_h = fs->make<TH1D>("DT_Triggers_Per_Lumi","",1000,0,1000);
  CSC_Triggers_Per_Lumi_h = fs->make<TH1D>("CSC_Triggers_Per_Lumi","",1000,0,1000);

  RPC_Barrel_Rates_Per_Lumi_h = fs->make<TH1D>("RPC_Barrel_Rates_Per_Lumi","",1000,0,1000);
  RPC_Endcap_Rates_Per_Lumi_h = fs->make<TH1D>("RPC_Endcap_Rates_Per_Lumi","",1000,0,1000);
  DT_Rates_Per_Lumi_h = fs->make<TH1D>("DT_Rates_Per_Lumi","",1000,0,1000);
  CSC_Rates_Per_Lumi_h = fs->make<TH1D>("CSC_Rates_Per_Lumi","",1000,0,1000);

  lumiblocks = 0;
  DT_Trigs_lumi = 0;
  CSC_Trigs_lumi = 0;
  RPC_Trigs_lumi = 0;
  RPCe_Trigs_lumi = 0;
  current_run = 0;
  current_lumi = 0;

//  vector_run_lumi.clear();
//  vector_Trigs_RPC_barrel.clear();
//  vector_Trigs_RPC_endcap.clear();
//  vector_Trigs_CSC.clear();
//  vector_Trigs_DT.clear();

}

// ------------ method called once each job just after ending the event loop  ------------
void 
RPCL1RateOverview::endJob() 
{
  RPC_Barrel_Rates_Per_Lumi_h->Divide(RPC_Barrel_Triggers_Per_Lumi_h,Bx_Per_Lumi_h,1.,25.e-9);
  RPC_Endcap_Rates_Per_Lumi_h->Divide(RPC_Endcap_Triggers_Per_Lumi_h,Bx_Per_Lumi_h,1.,25.e-9);
  DT_Rates_Per_Lumi_h->Divide(DT_Triggers_Per_Lumi_h,Bx_Per_Lumi_h,1.,25.e-9);
  CSC_Rates_Per_Lumi_h->Divide(CSC_Triggers_Per_Lumi_h,Bx_Per_Lumi_h,1.,25.e-9);
}

// ------------ method called when starting to processes a run  ------------
void 
RPCL1RateOverview::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
RPCL1RateOverview::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
RPCL1RateOverview::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
RPCL1RateOverview::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RPCL1RateOverview::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RPCL1RateOverview);
