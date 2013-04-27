void rootlogon() 
{

  //Para el ejercicio 3: needCompilation = true
  bool needCompilation = false;

  if( needCompilation) {

  	gSystem->AddIncludePath(" -I$FASTJET/include ");
  	gSystem->AddLinkedLibs("-Wl,-rpath,$FASTJET/lib -lm -L$FASTJET/lib -lfastjet");

  	gROOT->LoadMacro("PythiaAnalysis.C++");
  	gROOT->LoadMacro("JetPythiaAnalysis.C++");

  }

}
