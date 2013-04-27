// $Id: $
// Include files 

//-----------------------------------------------------------------------------
// Implementation file for class : muondigisreader
//
// 2008-11-10 : Andres Osorio
//-----------------------------------------------------------------------------
{
  
  TFile* f = new TFile("reco_CosmicMC_BOFF_2110.root") ;
   
  TTree* tevt = f->Get("Events") ;
  int nevt = tevt->GetEntries() ;

  std::cout << " Number of Events = " << nevt << std::endl ;
  cout << " We will print out some information for the 1st event" << endl ;
  
  // Get the RPC Geometry
  edm::ESHandle<RPCGeometry> rpcGeom;
  eventSetup.get<MuonGeometryRecord>().get(rpcGeom);
  
  // Get the digi collection from the event
  Handle<RPCDigiCollection> digi;
  event.getByLabel("muonRPCDigis", digi);
  

  
}
