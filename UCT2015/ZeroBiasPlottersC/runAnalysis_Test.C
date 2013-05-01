{

  ////////////////////////////////////
  ////
  //// Pequeno script para correr programas en root
  ////
  ////////////////////////////////////

  L1RateTree * l1data = new L1RateTree("/uscms/home/aosorio/nobackup/scratch0/UCT2015_BKP/root_files/uct_rates_zerob3_198609_HEAD_v16.root","rlxEGUCTRate/Ntuple");

  L1RateTree * recodata = new L1RateTree("/uscms/home/aosorio/nobackup/scratch0/UCT2015_BKP/root_files/uct_rates_zerob3_198609_HEAD_v16.root","rlxEGUCTRate/Ntuple");

  L1UCTEfficiency * eff = new L1UCTEfficiency( l1data, recodata, "output.root" );
  
  eff->Loop( (38371-2), (38371+2) );

}
