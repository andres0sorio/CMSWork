{
  
  PythiaAnalysis * susy;

  susy = new PythiaAnalysis("/scratch/aosorio/data/Pythia8/SUSY/eventos_pythia8_SUSY_LM0_100kev.root","output_LM0.root");
  susy->SetInitialState(1000021);
  susy->Loop(-1);
  delete susy;
  
  susy = new PythiaAnalysis("/scratch/aosorio/data/Pythia8/SUSY/eventos_pythia8_SUSY_LM5_100kev.root","output_LM5.root");
  susy->SetInitialState(1000021);
  susy->Loop(-1);
  delete susy;

  susy = new PythiaAnalysis("/scratch/aosorio/data/Pythia8/SUSY/eventos_pythia8_SUSY_LM10_100kev.root","output_LM10.root");
  susy->SetInitialState(1000021);
  susy->Loop(-1);
  delete susy;

  susy = new PythiaAnalysis("/scratch/aosorio/data/Pythia8/SM/eventos_pythia8_HardQCD_100kev.root","output_QCD.root");
  susy->SetInitialState(-1);
  susy->Loop(-1);
  delete susy;

  susy = new PythiaAnalysis("/scratch/aosorio/data/Pythia8/SM/eventos_pythia8_TopAll_100kev.root","output_Top.root");
  susy->SetInitialState(6);
  susy->Loop(-1);
  delete susy;


}
