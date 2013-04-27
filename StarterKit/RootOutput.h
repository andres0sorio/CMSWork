
// $Id: $
#ifndef YANIRA_ROOTOUTPUT_H 
#define YANIRA_ROOTOUTPUT_H 1

// Include files
#include "RootCommon.h"

#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TTree.h>

/** @class RootOutput RootOutput.h Yanira/RootOutput.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-12-26
 */
class RootOutput {
public: 
  /// Standard constructor
  RootOutput( ) {}; 
  
  RootOutput(const char *opt, int );

  virtual ~RootOutput( ); ///< Destructor

  std::map<int,std::string> m_types;
  
  TH1F * h_ZZinvMass;
  TH1F * h_ZPx;
  TH1F * h_ZPy;
  TH1F * h_ZPt;
  TH1F * h_ZEta;
  TH1F * h_ZPhi;
  TH1F * h_mumuInv;
  TH1F * h_mumuInv4;
  TH1F * h_muPx;
  TH1F * h_muPy;
  TH1F * h_muPt;
  TH1F * h_muEta;
  TH1F * h_nMuons;
  TH1F * h_nMuonsOrigin;
  TH1F * h_muPhi;
  TH1F * h_JetPt;

  TFile * m_fileout;
  
  void Draw();
  void Close();
  void FillTree();
  void Fit();
  
  TCanvas * c1;
  TCanvas * c2;
  TCanvas * c3;
  
  TTree * tree;
  
  void SetEvt( int evt)    { ev = evt;  };
  void SetType( int type ) { ty = type; };
  void SetVar1( float v1)  { var1 = v1; }
  void SetVar2( float v2)  { var2 = v2; };
  void SetVar3( float v3)  { var3 = v3; };
  void SetVar4( float v4)  { var4 = v4; };
  void SetVar5( float v5)  { var5 = v5; };
  void SetVar6( float v6)  { var6 = v6; };
  void SetVar7( float v7)  { var7 = v7; };
  void SetVar8( float v8)  { var8 = v8; };
  
protected:

private:

  int ev;
  int ty;
  float var1;
  float var2;
  float var3;
  float var4;
  float var5;
  float var6;
  float var7;
  float var8;
  
  std::string dataType;
  
  
};
#endif // YANIRA_ROOTOUTPUT_H
