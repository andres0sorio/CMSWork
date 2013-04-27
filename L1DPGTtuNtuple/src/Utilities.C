#include "Utilities.h"

void getListOfFiles(const char *source, TList *fileNames)
{
  
  ifstream in;
  in.open(source);
  
  if(!in) {
    print_message("could not open input file.");
    print_message(source);
    exit(1);
  }
  
  print_message("opening files:");
  
  char comment[256];
  in.getline (comment,256);
  print_message(comment);
  
  while (1) {
    char str[50];
    in >> str;
    if (!in.good()) break;
    TString name(str);
    print_message(name.Data());
    fileNames->Add( TFile::Open(name.Data()) );
  }    
  
  in.close();
  
}


void getListOfFiles(const char *source, std::vector<std::ifstream*> &fileNames)
{
  
  ifstream in;
  in.open(source);
  
  if(!in.good()) {
    print_message("could not open input file.");
    print_message(source);
    exit(1);
  }
  
  print_message("opening files:");
  
  char comment[256];
  in.getline (comment,256);
  print_message(comment);
  
  while (1) {
    char str[60];
    in >> str;
    if (!in.good()) break;
    print_message(str);
    std::ifstream *f1 = new std::ifstream();
    f1->open(str,std::ifstream::in);
    if (f1->good()) fileNames.push_back(f1);
   
  } 
  
  in.close();
  
}


void getListOfFiles(const char *source, TList *fileNames, 
		    std::vector<double> &v1, std::vector<double> &v2)
{
  
  gROOT->Reset();
  
  ifstream in;
  in.open(source);
  
  if(!in) {
    print_message("could not open input file.");
    print_message(source);
    exit(1);
  }
  
  print_message("opening files:");
  
  char comment[256];
  in.getline (comment,256);
  print_message(comment);
  
  while (1) {
    char str[60];
    double x1(0.);
    double x2(0.);
    in >> str >> x1 >> x2;
    if (!in.good()) break;
    TString name(str);
    print_message(name.Data());
    fileNames->Add( TFile::Open(name.Data()) );
    v1.push_back(x1);
    v2.push_back(x2);
  }    
  
  in.close();
  
}

void readData(const char *source, std::vector<double> &v1)
{
  
  v1.clear();
  
  ifstream in;
  in.open(source);
  
  if(!in) {
    print_message("could not open input file.");
    print_message(source);
    exit(1);
  }
  
  print_message("opening files:");
  
  char comment[256];
  in.getline (comment,256);
  print_message(comment);
  
  while (1) {
    double x(0.);
    in >> x;
    if (!in.good()) break;
    v1.push_back(x);
  }    
  
  in.close();
  
}

void readData(const char *source,
	      std::vector<double> &v1,
	      std::vector<double> &v2)
{
  
  v1.clear();
  v2.clear();
  
  ifstream in;
  in.open(source);
  
  if(!in) {
    print_message("could not open input file.");
    print_message(source);
    exit(1);
  }
  
  print_message("opening files:");
  
  char comment[256];
  in.getline (comment,256);
  print_message(comment);
  
  while (1) {
    double x(0.), y(0.);
    in >> x >> y;
    if (!in.good()) break;
    v1.push_back(x);
    v2.push_back(y);
  }    
  
  in.close();
  
}

void readData(const char *source,
	      std::vector<double> &v1,
	      std::vector<double> &v2,
	      std::vector<double> &v3)
{
  
  v1.clear();
  v2.clear();
  v3.clear();
  
  ifstream in;
  in.open(source);
  
  if(!in) {
    print_message("could not open input file.");
    print_message(source);
    exit(1);
  }
  
  print_message("opening files:");
  
  char comment[256];
  in.getline (comment,256);
  print_message(comment);
  
  while (1) {
    double x(0.), y(0.), z(0.);
    in >> x >> y >> z;
    if (!in.good()) break;
    v1.push_back(x);
    v2.push_back(y);
    v3.push_back(z);
  }    
  
  in.close();
  
}

void readData(std::ifstream *in,
	      std::vector<double> &v1,
	      std::vector<double> &v2,
	      std::vector<double> &v3)
{
  
  v1.clear();
  v2.clear();
  v3.clear();
  
  if(!in->good()) {
    print_message("could not open input file.");
    exit(1);
  }
  
  print_message("opening files:");
  
  char comment[256];
  in->getline (comment,256);
  print_message(comment);
  
  while (1) {
    double x(0.), y(0.), z(0.);
    (*in) >> x >> y >> z;
    if (!in->good()) break;
    v1.push_back(x);
    v2.push_back(y);
    v3.push_back(z);
  }    
  
  in->close();
  
}


///////////////
// Text options

void print_message(const char *message)
{
  std::cout << TString(message) << std::endl;
}

void print_message(const char *message, double val)
{
  std::cout << TString(message) << " " << val << std::endl;
}

void print_values(const char *message, double *val, int max)
{
  
  std::cout << TString(message) << '\t';
  for (int i=0; i < max; ++i) {
    std::cout << val[i] << " "; }
  std::cout << std::endl;
  
}

///////////////////
// Graph options

void preparePlotArea(TCanvas *c1, TPad *p1)
{
  c1->SetFillColor(44);
  gErrorIgnoreLevel = 1;
  p1->cd();
}

void setAxisOptions(TAxis * ax) 
{
  
  ax->SetLabelSize(0.031);
  ax->SetLabelFont(62);
  ax->SetLabelOffset(0.006);
  ax->SetTitleSize(0.035);
  ax->SetTitleFont(62);
  ax->SetTitleOffset(1.2);
  
}

void setAxisOptions(TGaxis * ax) 
{
  
  ax->SetLabelSize(0.031);
  ax->SetLabelFont(62);
  ax->SetLabelOffset(0.003);
  ax->SetTitleSize(0.031);
  ax->SetTitleOffset(0.004);
   
}


void setHistogramsOptions(TH1D *h) 
{
  TAxis::TAxis *axis1;
  TAxis::TAxis *axis2;
  h->SetMarkerStyle(6);
  h->SetMarkerSize(0.4);
  h->SetMarkerColor(2);
  h->SetLineColor(2);
  h->SetTitle("");
  axis1 = h->GetXaxis();
  axis2 = h->GetYaxis();
  axis1->SetTitle("m_WW [GeV]");
  axis2->SetTitle("Events");
  setAxisOptions(axis1);
  setAxisOptions(axis2);
}

void setHistogramsOptions(TH2D *h,
			  const char *xname, 
			  const char *yname) 
{
  TAxis::TAxis *axis1;
  TAxis::TAxis *axis2;
  h->SetMarkerStyle(6);
  h->SetMarkerSize(0.4);
  h->SetMarkerColor(2);
  h->SetLineColor(2);
  h->SetTitle("");
  axis1 = h->GetXaxis();
  axis2 = h->GetYaxis();
  axis1->SetTitle(xname);
  axis2->SetTitle(yname);
  setAxisOptions(axis1);
  setAxisOptions(axis2);
}


void setGraphOptions(TF1 &f, 
		     const char *xname, 
		     const char *yname)
{
  TAxis::TAxis *axis1;
  TAxis::TAxis *axis2;
  axis1 = f.GetXaxis();
  axis2 = f.GetYaxis();
  axis1->SetTitle(xname);
  axis2->SetTitle(yname);
  setAxisOptions(axis1);
  setAxisOptions(axis2);
}

void setGraphOptions(TF2 &f, 
		     const char *xname, 
		     const char *yname)
{
  TAxis::TAxis *axis1;
  TAxis::TAxis *axis2;
  axis1 = f.GetXaxis();
  axis2 = f.GetYaxis();
  axis1->SetTitle(xname);
  axis2->SetTitle(yname);
  setAxisOptions(axis1);
  setAxisOptions(axis2);
}

void setGraphOptions(TGraph &g)
{
  g.SetTitle("");
  g.SetMarkerColor(1);
  g.SetMarkerStyle(24);
  g.SetMarkerSize(.5);
}

void setGraphOptions(TGraph2D &g)
{
  g.SetTitle("");
  g.SetMarkerColor(1);
  g.SetMarkerStyle(24);
  g.SetMarkerSize(.5);
}

void setLegendOptions(TLegend * alegend) {
  
  alegend->SetFillColor(10);
  alegend->SetBorderSize(1);
  alegend->SetTextSize(0.03);
  
}

void setStyleOptions(TStyle * style) {
  
  style->SetCanvasColor(10);
  style->SetTextFont(22);
  style->SetStatFont(42);
  style->SetStatFontSize(0.030);
  style->SetStatColor(10);
  style->SetStatBorderSize(1);
  style->SetStatW(0.25);
  style->SetStatH(0.25);
  style->SetStatX(0.93);
  style->SetStatY(0.95);
  gErrorIgnoreLevel = 1;

}

void setFrameOptions(TPad *pad, char *option1, char *option2) {
  
  pad->GetFrame()->SetFillColor(10);
  TAxis *ax1 = ((TH1F*)pad->FindObject("hframe"))->GetXaxis();
  TAxis *ax2 = ((TH1F*)pad->FindObject("hframe"))->GetYaxis();
  
  setAxisOptions(ax1);
  setAxisOptions(ax2);
  
  ax1->SetTitle(option1);
  ax2->SetTitle(option2);
  
}


////////////////////
// Data utilities

void transferResults(std::vector<double> & from,std::vector<double> &to)
{
  to.clear();
  
  std::vector<double>::iterator itr;

  for(itr = from.begin(); itr != from.end(); ++itr)
    to.push_back((*itr));
  
  from.clear();
  
}

int findBestQuadrant(TH1D *ahisto) {
  
  Int_t quadrant(0);
  Float_t qarea(0.0);
  Float_t qqarea[4];
  Float_t max_x(0.0), min_x(0.0), tot_x(0.0);
  Float_t sfactor(0.0);
  Int_t max_bin(0), sep_bin(0), k;
  
  Float_t value = 0;
  Float_t maxvalue =0;
  Float_t maximum = ahisto->GetMaximum();

  max_x=(ahisto->GetXaxis())->GetXmax();
  min_x=(ahisto->GetXaxis())->GetXmin();
  tot_x= max_x - min_x;
  
  qarea=(tot_x*maximum)/4;
  
  max_bin=ahisto->GetNbinsX();
  sep_bin=max_bin/4;

  sfactor=tot_x/max_bin;

  qqarea[0]=qarea-sfactor*(ahisto->Integral(1,sep_bin));
  qqarea[1]=qarea-sfactor*(ahisto->Integral(sep_bin+1,2*sep_bin));
  qqarea[2]=qarea-sfactor*(ahisto->Integral(2*sep_bin+1,3*sep_bin));
  qqarea[3]=qarea-sfactor*(ahisto->Integral(3*sep_bin+1,max_bin));
  
  //printf("%d Areas: %f %f %f %f \n",i, qqarea[0],qqarea[1],qqarea[2],qqarea[3]);
  
  for(k=0; k<4 ; k++) {
    value=qqarea[k];
    if(value > maxvalue) {
      maxvalue = value;
      quadrant=k;
    }
  }
  
  return quadrant;
  
}

void createGIF(TString name) {
  
  TString firstcommand = TString ("pstopnm -ppm -xborder 0 -yborder 0 -xsize 450 -portrait ");
  TString secondcommand = TString ("ppmtogif ");
  
  TString execone = firstcommand + name + TString(".eps");
  TString exectwo = secondcommand + name + TString(".eps001.ppm > ") + name + TString(".gif");
  
  if (gROOT->IsBatch())  {
    
    gSystem->Exec(execone);
    gSystem->Exec(exectwo);
    gSystem->Exec("rm *.ppm");
  } 
  
  else std::cout << "createGIF> Cannot create gif file!" << std::endl;
  
  
}



void getDistHistogram(TFile *f1, const char *type, const char *dist, TH1D *h1)
{
  
  char dir[20];
  sprintf(dir,"%s/%s",dist,type);
  
  f1->cd(dir);
  
  char name[20];
  sprintf(name,"%s_%d",dist,1);
  
  TObject *obj = new TObject();
  TKey *key = gDirectory->FindKey(name);
  obj = key->ReadObj();
  
  if(obj != NULL) {
    h1 = (TH1D*)obj;
  }
  else { print_message("Error: histogram not found"); exit(1); }
  
  delete obj;
  
  ///

}

void ReadParameters( std::vector<double> &p1,
		     std::vector<double> &p2,
		     std::vector<double> &p3,
		     std::vector<double> &p4,
		     std::vector<double> &p5,
		     std::vector<double> &p6 )
{

  ifstream in;
  in.open("ScenariosParameters.dat");
  
  if(!in) {
    print_message("could not open Parameters input file.");
    exit(1);
  }
  
  print_message("reading values");
  
  double x1, x2, x3, x4, x5, x6 = 0.;
  //nu1,nu2 are not used parameters
  double nu1, nu2 = 0.;
  
  char comment[256];
  in.getline (comment,256);
  print_message(comment);
  in.getline (comment,256);
  print_message(comment);
  
  while (1) {
    
    in >> x1 >> x2 >> x3 >> nu1 >> x4 >> nu2 >> x5 >> x6;
    
    if (!in.good()) break;
    
    p1.push_back(x1);
    p2.push_back(x2);
    p3.push_back(x3);
    p4.push_back(x4);
    p5.push_back(x5);
    p6.push_back(x6);
  }    
  
  in.close();
  
}

void getDistAttributes(TList *files, const char *name, double *options)
{
  
  TFile *f1 = (TFile*)files->First();
  f1->cd("withCuts/Detector_Data/Background/");
  TObject *obj = new TObject();
  TKey *key = gDirectory->FindKey(name);
  obj = key->ReadObj();
  
  if(obj != NULL) {
    TH1D *h = (TH1D*)obj;
    options[0]  = h->GetNbinsX();
    options[1]  = h->GetXaxis()->GetXmin();
    options[2]  = h->GetXaxis()->GetXmax();
  }
  else { print_message("Error: histogram not found"); exit(1); }
  
  delete obj;
  
}



void findHistogram(const char *name, TH1D *hh, TKey *key)
{

  TObject *obj = new TObject();
  
  key = gDirectory->FindKey(name);
  
  obj = key->ReadObj();
  
  if(obj != NULL) {
    TH1D *h = (TH1D*)obj;
    hh->Add(h);
  }
  else { print_message("Error: histogram not found");}
  
  delete obj;
  
}

void closeListOfFiles(std::vector<ifstream*> &files)
{
  
  std::vector<ifstream*>::iterator itr;
  
  for(itr = files.begin(); itr != files.end(); ++itr)
    {
      (*itr)->close();
      delete (*itr);
    }
  
  files.clear();
  
}

void exportData( std::ofstream *out, 
		 const std::vector<double> & v1,
		 const std::vector<double> & v2,
		 const std::vector<double> & v3) {

  
  
  int max = v1.size();
  
  for (int i = 0; i < max; i++ ) {
    
    (*out) << v1[i] << '\t' 
	   << v2[i] << '\t' 
	   << v3[i] << '\n';
    
  }
  
}





void exportData( const char *filename , 
		 const std::vector<double> & v1 ) 
{
  
  int max = v1.size();
  
  std::ofstream os;
  os.open(filename);
  
  if(!os.good()) {
    print_message("could not open output file.");
    print_message(filename);
    exit(1);
  }
  
  print_message("Exporting data:");
  
  os << "//Data values" << '\n';
  
  for (int i = 0; i < max; i++ ) os << v1[i] << '\n'; 
  
  
}

void plotDot(double x1, double x2, int colour, int style,double size)
{
  
  double xp[1];
  double yp[1];
  
  xp[0] = x1;
  yp[0] = x2;
  
  TGraph *dots = new TGraph(1,xp,yp);
  dots->SetMarkerColor(colour);
  dots->SetMarkerStyle(style);
  dots->SetMarkerSize(size);
  dots->Draw("Psame"); 
  
}

void drawValueBox(double x1, double x2, double x3, int colour)
{

  char optionfile[60];
  std::vector<double> options;
  
  double delta1(0.), delta2(0.), delta3(0.), delta4(0.);
  double tsize(0.7);

  sprintf(optionfile,"./config/drawValueBox.dat");
  
  readData(optionfile,options);
  delta1 = options[0];
  delta2 = options[1];
  delta3 = options[2];
  delta4 = options[3];
  tsize  = options[4];
  
  double xmin = x1 + delta1;
  double xmax = x1 + delta2;
  double ymin = x2 + delta3;
  double ymax = x2 + delta4;

  if ( x1 < 0 && x2 > 0) {
    xmin = x1 - delta1;
    xmax = x1 - delta2;
  } 
  else if ( x1 < 0 && x2 < 0) {
    xmin = x1 - delta1;
    xmax = x1 - delta2;
    ymin = x2 - delta3;
    ymax = x2 - delta4;
  }
  else if ( x1 > 0 && x2 < 0) {
    ymin = x2 - delta3;
    ymax = x2 - delta4;
  }
  else if ( x1 == 0.0 ) {
    xmin = xmin - delta1;
    xmax = xmax ;
  }
  else if ( x2 == 0.0 ) {
    ymin = ymin - delta3;
    ymax = ymax ;
  }
  else {}


  char label[10];
  sprintf(label,"%.1f",float(x3));

  TPaveLabel *box = new TPaveLabel(xmin,ymin,xmax,ymax,label);
  box->SetBorderSize(0);
  box->SetTextFont(42);
  box->SetTextSize(tsize);
  box->SetTextAlign(22);
  box->SetTextColor(colour);
  if (colour == 1) box->SetFillStyle(4000);
  else {
    box->SetFillColor(10);
    box->SetTextColor(colour);
    box->SetBorderSize(1);
  }
  box->Draw("same");
  
  TLine * ln = new TLine(x1,x2,xmin,ymin);
  ln->SetLineWidth(1);
  ln->SetLineStyle(1);
  ln->SetLineColor(14);
  ln->Draw("same");
  
}

void drawAxes(double xmax, double ymax) {
  
  TLine * axe1 = new TLine(-xmax,0.0,xmax,0.0);
  axe1->SetLineWidth(1);
  axe1->SetLineStyle(2);
  axe1->SetLineColor(12);
  axe1->Draw("same");
  
  TLine * axe2 = new TLine(0.0,-ymax,0.0,ymax);
  axe2->SetLineWidth(1);
  axe2->SetLineStyle(2);
  axe2->SetLineColor(12);
  axe2->Draw("same");

}


void addText(TLatex &l, const char * filename)
{
  
  ifstream in;
  in.open(filename);
  
  if(!in) {
    print_message("could not open input file.");
    print_message(filename);
    exit(1);
  }
  
  char comment[256];
  in.getline (comment,256);
  
  double posx (0.), posy(0.);
  double delta(0.);
  int colour(1);
  int style(1);
  double size(0.5);
  
  in >> posx >> posy >> delta;
  in >> colour >> style >> size;

  l.SetTextColor(colour);
  l.SetTextFont(style);
  l.SetTextSize(size);

  while (1) {
    in.getline (comment,256);
    if (!in.good()) break;
    l.DrawLatex(posx,posy,comment);
    posx+=0.0;
    posy+=delta;
  }    
  
  in.close();
    
}

void checkData(std::vector<double> &v1,
	       std::vector<double> &v2,
	       std::vector<double> &v3)
{

  std::ofstream *os = new std::ofstream("checkdata.out",ofstream::out);

  int len1(0);
  int len2(0);
  int len3(0);

  len1 = v1.size();
  len2 = v2.size();
  len3 = v3.size();
  
  print_message("checkData>>>>");
  (*os) << "checkData> size of vectors: " << len1 << '\t' << len2 << '\t' << len3 << '\n';
  
  if ( len1 != len2 && len1 != len3 )
    {
      print_message("checkData> Incompatible data size!");
      exit(1);
    }
  
  print_message("checkData> a few operations on data ");

  for (int i=0; i < len1; i++) {
    
    (*os) << v1[i]+v2[i]+v3[i] << '\t'
	      << v1[i]-v2[i]+v3[i] << '\t'
	      << v1[i]+v2[i]-v3[i] << '\t'
	      << v1[i]-v2[i]-v3[i] << '\t'
	      << (v1[i]*v2[i])+v3[i] << '\t'
	      << v1[i]+(v2[i]*v3[i]) << '\n';
    
  }

  (*os) << "checkData> ckecking data:" << '\n';
  
  os->close();

  delete os;

}
