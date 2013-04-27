//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb  1 22:44:17 2010 by ROOT version 5.22/00
// from TTree L1Tree/L1Tree
// found on file: L1DPG-All.root
//////////////////////////////////////////////////////////

#ifndef L1Tree_h
#define L1Tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <bitset>

#include <BasicOutput.h>

class L1Tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Event;
   Int_t           Lumi;
   Int_t           Bx;
   ULong64_t       Orbit;
   ULong64_t       Time;
   Int_t           gmtEvBx;
   Int_t           gmtNdt;
   Int_t           gmtBxdt[11];   //[gmtNdt]
   Float_t         gmtPtdt[11];   //[gmtNdt]
   Int_t           gmtChdt[11];   //[gmtNdt]
   Float_t         gmtEtadt[11];   //[gmtNdt]
   Int_t           gmtFineEtadt[11];   //[gmtNdt]
   Float_t         gmtPhidt[11];   //[gmtNdt]
   Int_t           gmtQualdt[11];   //[gmtNdt]
   Int_t           gmtDwdt[11];   //[gmtNdt]
   Int_t           gmtNcsc;
   Int_t           gmtBxcsc[4];   //[gmtNcsc]
   Float_t         gmtPtcsc[4];   //[gmtNcsc]
   Int_t           gmtChcsc[4];   //[gmtNcsc]
   Float_t         gmtEtacsc[4];   //[gmtNcsc]
   Float_t         gmtPhicsc[4];   //[gmtNcsc]
   Int_t           gmtQualcsc[4];   //[gmtNcsc]
   Int_t           gmtDwcsc[4];   //[gmtNcsc]
   Int_t           gmtNrpcb;
   Int_t           gmtBxrpcb[12];   //[gmtNrpcb]
   Float_t         gmtPtrpcb[12];   //[gmtNrpcb]
   Int_t           gmtCharpcb[12];   //[gmtNrpcb]
   Float_t         gmtEtarpcb[12];   //[gmtNrpcb]
   Float_t         gmtPhirpcb[12];   //[gmtNrpcb]
   Int_t           gmtQualrpcb[12];   //[gmtNrpcb]
   Int_t           gmtDwrpcb[12];   //[gmtNrpcb]
   Int_t           gmtNrpcf;
   Int_t           gmtBxrpcf[3];   //[gmtNrpcf]
   Float_t         gmtPtrpcf[3];   //[gmtNrpcf]
   Int_t           gmtCharpcf[3];   //[gmtNrpcf]
   Float_t         gmtEtarpcf[3];   //[gmtNrpcf]
   Float_t         gmtPhirpcf[3];   //[gmtNrpcf]
   Int_t           gmtQualrpcf[3];   //[gmtNrpcf]
   Int_t           gmtDwrpcf[3];   //[gmtNrpcf]
   Int_t           gmtN;
   Int_t           gmtCandBx[12];   //[gmtN]
   Float_t         gmtPt[12];   //[gmtN]
   Int_t           gmtCha[12];   //[gmtN]
   Float_t         gmtEta[12];   //[gmtN]
   Float_t         gmtPhi[12];   //[gmtN]
   Int_t           gmtQual[12];   //[gmtN]
   Int_t           gmtDet[12];   //[gmtN]
   Int_t           gmtRank[12];   //[gmtN]
   Int_t           gmtIsol[12];   //[gmtN]
   Int_t           gmtMip[12];   //[gmtN]
   Int_t           gmtDw[12];   //[gmtN]
   Int_t           gmtIdxRPCb[12];   //[gmtN]
   Int_t           gmtIdxRPCf[12];   //[gmtN]
   Int_t           gmtIdxDTBX[12];   //[gmtN]
   Int_t           gmtIdxCSC[12];   //[gmtN]
   Int_t           gtPartrig_tcs;
   Int_t           gtgpsTimehi;
   Int_t           gtgpsTimelo;
   Int_t           gtbstMasterStatus;
   Int_t           gtbstturnCountNumber;
   Int_t           gtbstlhcFillNumber;
   Int_t           gtbstbeamMode;
   Int_t           gtbstparticleTypeBeam1;
   Int_t           gtbstparticleTypeBeam2;
   Int_t           gtbstbeamMomentum;
   Int_t           gtbsttotalIntensityBeam1;
   Int_t           gtbsttotalIntensityBeam2;
   ULong64_t       gttw1[5];
   ULong64_t       gttw2[5];
   ULong64_t       gttt[5];
   Int_t           gtNele;
   Int_t           gtBxel[6];   //[gtNele]
   Float_t         gtRankel[6];   //[gtNele]
   Float_t         gtPhiel[6];   //[gtNele]
   Float_t         gtEtael[6];   //[gtNele]
   Bool_t          gtIsoel[6];   //[gtNele]
   Int_t           gtNjet;
   Int_t           gtBxjet[11];   //[gtNjet]
   Float_t         gtRankjet[11];   //[gtNjet]
   Float_t         gtPhijet[11];   //[gtNjet]
   Float_t         gtEtajet[11];   //[gtNjet]
   Bool_t          gtTaujet[11];   //[gtNjet]
   Bool_t          gtFwdjet[11];   //[gtNjet]
   Int_t           gctIsoEmSize;
   Float_t         gctIsoEmEta[4];
   Float_t         gctIsoEmPhi[4];
   Float_t         gctIsoEmRnk[4];
   Int_t           gctNonIsoEmSize;
   Float_t         gctNonIsoEmEta[4];
   Float_t         gctNonIsoEmPhi[4];
   Float_t         gctNonIsoEmRnk[4];
   Int_t           gctCJetSize;
   Float_t         gctCJetEta[4];
   Float_t         gctCJetPhi[4];
   Float_t         gctCJetRnk[4];
   Int_t           gctFJetSize;
   Float_t         gctFJetEta[4];
   Float_t         gctFJetPhi[4];
   Float_t         gctFJetRnk[4];
   Int_t           gctTJetSize;
   Float_t         gctTJetEta[4];
   Float_t         gctTJetPhi[4];
   Float_t         gctTJetRnk[4];
   Float_t         gctEtMiss;
   Float_t         gctEtMissPhi;
   Float_t         gctHtMiss;
   Float_t         gctHtMissPhi;
   Float_t         gctEtHad;
   Float_t         gctEtTot;
   Int_t           gctHFRingEtSumSize;
   Float_t         gctHFRingEtSumEta[4];
   Int_t           gctHFBitCountsSize;
   Float_t         gctHFBitCountsEta[4];
   Int_t           rctRegSize;
   Float_t         rctRegEta[396];   //[rctRegSize]
   Float_t         rctRegPhi[396];   //[rctRegSize]
   Float_t         rctRegRnk[396];   //[rctRegSize]
   Int_t           rctRegVeto[396];   //[rctRegSize]
   Int_t           rctRegBx[396];   //[rctRegSize]
   Int_t           rctRegOverFlow[396];   //[rctRegSize]
   Int_t           rctRegMip[396];   //[rctRegSize]
   Int_t           rctRegFGrain[396];   //[rctRegSize]
   Int_t           rctEmSize;
   Int_t           rctIsIsoEm[144];   //[rctEmSize]
   Float_t         rctEmEta[144];   //[rctEmSize]
   Float_t         rctEmPhi[144];   //[rctEmSize]
   Float_t         rctEmRnk[144];   //[rctEmSize]
   Int_t           rctEmBx[144];   //[rctEmSize]
   Int_t           dttf_phSize;
   Int_t           dttf_phBx[64];   //[dttf_phSize]
   Int_t           dttf_phWh[64];   //[dttf_phSize]
   Int_t           dttf_phSe[64];   //[dttf_phSize]
   Int_t           dttf_phSt[64];   //[dttf_phSize]
   Float_t         dttf_phAng[64];   //[dttf_phSize]
   Float_t         dttf_phBandAng[64];   //[dttf_phSize]
   Int_t           dttf_phCode[64];   //[dttf_phSize]
   Float_t         dttf_phX[64];   //[dttf_phSize]
   Float_t         dttf_phY[64];   //[dttf_phSize]
   Int_t           dttf_thSize;
   Int_t           dttf_thBx[179];   //[dttf_thSize]
   Int_t           dttf_thWh[179];   //[dttf_thSize]
   Int_t           dttf_thSe[179];   //[dttf_thSize]
   Int_t           dttf_thSt[179];   //[dttf_thSize]
   Float_t         dttf_thX[179];   //[dttf_thSize]
   Float_t         dttf_thY[179];   //[dttf_thSize]
   Float_t         dttf_thTheta[179][7];   //[dttf_thSize]
   Int_t           dttf_thCode[179][7];   //[dttf_thSize]
   Int_t           dttf_trSize;
   Int_t           dttf_trBx[10];   //[dttf_trSize]
   Int_t           dttf_trQual[10];   //[dttf_trSize]
   Int_t           dttf_trTag[10];   //[dttf_trSize]
   Int_t           dttf_trPtPck[10];   //[dttf_trSize]
   Float_t         dttf_trPtVal[10];   //[dttf_trSize]
   Int_t           dttf_trPhiPck[10];   //[dttf_trSize]
   Float_t         dttf_trPhiVal[10];   //[dttf_trSize]
   Int_t           dttf_trPhiGlob[10];   //[dttf_trSize]
   Int_t           dttf_trChPck[10];   //[dttf_trSize]
   Int_t           dttf_trWh[10];   //[dttf_trSize]
   Int_t           dttf_trSc[10];   //[dttf_trSize]
   Int_t           csctf_trSize;
   Int_t           csctf_trEndcap[4];   //[csctf_trSize]
   Int_t           csctf_trSector[4];   //[csctf_trSize]
   Int_t           csctf_trBx[4];   //[csctf_trSize]
   Int_t           csctf_trME1ID[4];   //[csctf_trSize]
   Int_t           csctf_trME2ID[4];   //[csctf_trSize]
   Int_t           csctf_trME3ID[4];   //[csctf_trSize]
   Int_t           csctf_trME4ID[4];   //[csctf_trSize]
   Int_t           csctf_trMB1ID[4];   //[csctf_trSize]
   Int_t           csctf_trOutputLink[4];   //[csctf_trSize]
   Int_t           csctf_trCharge[4];   //[csctf_trSize]
   Int_t           csctf_trChargeValid[4];   //[csctf_trSize]
   Int_t           csctf_trForR[4];   //[csctf_trSize]
   Int_t           csctf_trPhi23[4];   //[csctf_trSize]
   Int_t           csctf_trPhi12[4];   //[csctf_trSize]
   Int_t           csctf_trPhiSign[4];   //[csctf_trSize]
   Int_t           csctf_trEtaBit[4];   //[csctf_trSize]
   Int_t           csctf_trPhiBit[4];   //[csctf_trSize]
   Int_t           csctf_trPtBit[4];   //[csctf_trSize]
   Float_t         csctf_trEta[4];   //[csctf_trSize]
   Float_t         csctf_trPhi[4];   //[csctf_trSize]
   Float_t         csctf_trPhi_02PI[4];   //[csctf_trSize]
   Float_t         csctf_trPt[4];   //[csctf_trSize]
   Int_t           csctf_trMode[4];   //[csctf_trSize]
   Int_t           csctf_trQuality[4];   //[csctf_trSize]
   Int_t           csctf_trNumLCTs[4];   //[csctf_trSize]
   Int_t           csctf_lctEndcap[4][4];   //[csctf_trSize]
   Int_t           csctf_lctSector[4][4];   //[csctf_trSize]
   Int_t           csctf_lctSubSector[4][4];   //[csctf_trSize]
   Int_t           csctf_lctBx[4][4];   //[csctf_trSize]
   Int_t           csctf_lctBx0[4][4];   //[csctf_trSize]
   Int_t           csctf_lctStation[4][4];   //[csctf_trSize]
   Int_t           csctf_lctRing[4][4];   //[csctf_trSize]
   Int_t           csctf_lctChamber[4][4];   //[csctf_trSize]
   Int_t           csctf_lctTriggerCSCID[4][4];   //[csctf_trSize]
   Int_t           csctf_lctFpga[4][4];   //[csctf_trSize]
   Int_t           csctf_lctlocalPhi[4][4];   //[csctf_trSize]
   Int_t           csctf_lctglobalPhi[4][4];   //[csctf_trSize]
   Int_t           csctf_lctglobalEta[4][4];   //[csctf_trSize]
   Int_t           csctf_lctstripNum[4][4];   //[csctf_trSize]
   Int_t           csctf_lctwireGroup[4][4];   //[csctf_trSize]
   Int_t           csctf_nsp;
   Int_t           csctf_stSPslot[8];   //[csctf_nsp]
   Int_t           csctf_stL1A_BXN[8];   //[csctf_nsp]
   Int_t           csctf_stTrkCounter[8];   //[csctf_nsp]
   Int_t           csctf_stOrbCounter[8];   //[csctf_nsp]

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Lumi;   //!
   TBranch        *b_Bx;   //!
   TBranch        *b_Orbit;   //!
   TBranch        *b_Time;   //!
   TBranch        *b_gmtEvBx;   //!
   TBranch        *b_gmtNdt;   //!
   TBranch        *b_gmtBxdt;   //!
   TBranch        *b_gmtPtdt;   //!
   TBranch        *b_gmtChdt;   //!
   TBranch        *b_gmtEtadt;   //!
   TBranch        *b_gmtFineEtadt;   //!
   TBranch        *b_gmtPhidt;   //!
   TBranch        *b_gmtQualdt;   //!
   TBranch        *b_gmtDwdt;   //!
   TBranch        *b_gmtNcsc;   //!
   TBranch        *b_gmtBxcsc;   //!
   TBranch        *b_gmtPtcsc;   //!
   TBranch        *b_gmtChcsc;   //!
   TBranch        *b_gmtEtacsc;   //!
   TBranch        *b_gmtPhicsc;   //!
   TBranch        *b_gmtQualcsc;   //!
   TBranch        *b_gmtDwcsc;   //!
   TBranch        *b_gmtNrpcb;   //!
   TBranch        *b_gmtBxrpcb;   //!
   TBranch        *b_gmtPtrpcb;   //!
   TBranch        *b_gmtCharpcb;   //!
   TBranch        *b_gmtEtarpcb;   //!
   TBranch        *b_gmtPhirpcb;   //!
   TBranch        *b_gmtQualrpcb;   //!
   TBranch        *b_gmtDwrpcb;   //!
   TBranch        *b_gmtNrpcf;   //!
   TBranch        *b_gmtBxrpcf;   //!
   TBranch        *b_gmtPtrpcf;   //!
   TBranch        *b_gmtCharpcf;   //!
   TBranch        *b_gmtEtarpcf;   //!
   TBranch        *b_gmtPhirpcf;   //!
   TBranch        *b_gmtQualrpcf;   //!
   TBranch        *b_gmtDwrpcf;   //!
   TBranch        *b_gmtN;   //!
   TBranch        *b_gmtCandBx;   //!
   TBranch        *b_gmtPt;   //!
   TBranch        *b_gmtCha;   //!
   TBranch        *b_gmtEta;   //!
   TBranch        *b_gmtPhi;   //!
   TBranch        *b_gmtQual;   //!
   TBranch        *b_gmtDet;   //!
   TBranch        *b_gmtRank;   //!
   TBranch        *b_gmtIsol;   //!
   TBranch        *b_gmtMip;   //!
   TBranch        *b_gmtDw;   //!
   TBranch        *b_gmtIdxRPCb;   //!
   TBranch        *b_gmtIdxRPCf;   //!
   TBranch        *b_gmtIdxDTBX;   //!
   TBranch        *b_gmtIdxCSC;   //!
   TBranch        *b_gtPartrig_tcs;   //!
   TBranch        *b_gtgpsTimehi;   //!
   TBranch        *b_gtgpsTimelo;   //!
   TBranch        *b_gtbstMasterStatus;   //!
   TBranch        *b_gtbstturnCountNumber;   //!
   TBranch        *b_gtbstlhcFillNumber;   //!
   TBranch        *b_gtbstbeamMode;   //!
   TBranch        *b_gtbstparticleTypeBeam1;   //!
   TBranch        *b_gtbstparticleTypeBeam2;   //!
   TBranch        *b_gtbstbeamMomentum;   //!
   TBranch        *b_gtbsttotalIntensityBeam1;   //!
   TBranch        *b_gtbsttotalIntensityBeam2;   //!
   TBranch        *b_gttw1;   //!
   TBranch        *b_gttw2;   //!
   TBranch        *b_gttt;   //!
   TBranch        *b_gtNele;   //!
   TBranch        *b_gtBxel;   //!
   TBranch        *b_gtRankel;   //!
   TBranch        *b_gtPhiel;   //!
   TBranch        *b_gtEtael;   //!
   TBranch        *b_gtIsoel;   //!
   TBranch        *b_gtNjet;   //!
   TBranch        *b_gtBxjet;   //!
   TBranch        *b_gtRankjet;   //!
   TBranch        *b_gtPhijet;   //!
   TBranch        *b_gtEtajet;   //!
   TBranch        *b_gtTaujet;   //!
   TBranch        *b_gtFwdjet;   //!
   TBranch        *b_gctIsoEmSize;   //!
   TBranch        *b_gctIsoEmEta;   //!
   TBranch        *b_gctIsoEmPhi;   //!
   TBranch        *b_gctIsoEmRnk;   //!
   TBranch        *b_gctNonIsoEmSize;   //!
   TBranch        *b_gctNonIsoEmEta;   //!
   TBranch        *b_gctNonIsoEmPhi;   //!
   TBranch        *b_gctNonIsoEmRnk;   //!
   TBranch        *b_gctCJetSize;   //!
   TBranch        *b_gctCJetEta;   //!
   TBranch        *b_gctCJetPhi;   //!
   TBranch        *b_gctCJetRnk;   //!
   TBranch        *b_gctFJetSize;   //!
   TBranch        *b_gctFJetEta;   //!
   TBranch        *b_gctFJetPhi;   //!
   TBranch        *b_gctFJetRnk;   //!
   TBranch        *b_gctTJetSize;   //!
   TBranch        *b_gctTJetEta;   //!
   TBranch        *b_gctTJetPhi;   //!
   TBranch        *b_gctTJetRnk;   //!
   TBranch        *b_gctEtMiss;   //!
   TBranch        *b_gctEtMissPhi;   //!
   TBranch        *b_gctHtMiss;   //!
   TBranch        *b_gctHtMissPhi;   //!
   TBranch        *b_gctEtHad;   //!
   TBranch        *b_gctEtTot;   //!
   TBranch        *b_gctHFRingEtSumSize;   //!
   TBranch        *b_gctHFRingEtSumEta;   //!
   TBranch        *b_gctHFBitCountsSize;   //!
   TBranch        *b_gctHFBitCountsEta;   //!
   TBranch        *b_rctRegSize;   //!
   TBranch        *b_rctRegEta;   //!
   TBranch        *b_rctRegPhi;   //!
   TBranch        *b_rctRegRnk;   //!
   TBranch        *b_rctRegVeto;   //!
   TBranch        *b_rctRegBx;   //!
   TBranch        *b_rctRegOverFlow;   //!
   TBranch        *b_rctRegMip;   //!
   TBranch        *b_rctRegFGrain;   //!
   TBranch        *b_rctEmSize;   //!
   TBranch        *b_rctIsIsoEm;   //!
   TBranch        *b_rctEmEta;   //!
   TBranch        *b_rctEmPhi;   //!
   TBranch        *b_rctEmRnk;   //!
   TBranch        *b_rctEmBx;   //!
   TBranch        *b_dttf_phSize;   //!
   TBranch        *b_dttf_phBx;   //!
   TBranch        *b_dttf_phWh;   //!
   TBranch        *b_dttf_phSe;   //!
   TBranch        *b_dttf_phSt;   //!
   TBranch        *b_dttf_phAng;   //!
   TBranch        *b_dttf_phBandAng;   //!
   TBranch        *b_dttf_phCode;   //!
   TBranch        *b_dttf_phX;   //!
   TBranch        *b_dttf_phY;   //!
   TBranch        *b_dttf_thSize;   //!
   TBranch        *b_dttf_thBx;   //!
   TBranch        *b_dttf_thWh;   //!
   TBranch        *b_dttf_thSe;   //!
   TBranch        *b_dttf_thSt;   //!
   TBranch        *b_dttf_thX;   //!
   TBranch        *b_dttf_thY;   //!
   TBranch        *b_dttf_thTheta;   //!
   TBranch        *b_dttf_thCode;   //!
   TBranch        *b_dttf_trSize;   //!
   TBranch        *b_dttf_trBx;   //!
   TBranch        *b_dttf_trQual;   //!
   TBranch        *b_dttf_trTag;   //!
   TBranch        *b_dttf_trPtPck;   //!
   TBranch        *b_dttf_trPtVal;   //!
   TBranch        *b_dttf_trPhiPck;   //!
   TBranch        *b_dttf_trPhiVal;   //!
   TBranch        *b_dttf_trPhiGlob;   //!
   TBranch        *b_dttf_trChPck;   //!
   TBranch        *b_dttf_trWh;   //!
   TBranch        *b_dttf_trSc;   //!
   TBranch        *b_csctf_trSize;   //!
   TBranch        *b_csctf_trEndcap;   //!
   TBranch        *b_csctf_trSector;   //!
   TBranch        *b_csctf_trBx;   //!
   TBranch        *b_csctf_trME1ID;   //!
   TBranch        *b_csctf_trME2ID;   //!
   TBranch        *b_csctf_trME3ID;   //!
   TBranch        *b_csctf_trME4ID;   //!
   TBranch        *b_csctf_trMB1ID;   //!
   TBranch        *b_csctf_trOutputLink;   //!
   TBranch        *b_csctf_trCharge;   //!
   TBranch        *b_csctf_trChargeValid;   //!
   TBranch        *b_csctf_trForR;   //!
   TBranch        *b_csctf_trPhi23;   //!
   TBranch        *b_csctf_trPhi12;   //!
   TBranch        *b_csctf_trPhiSign;   //!
   TBranch        *b_csctf_trEtaBit;   //!
   TBranch        *b_csctf_trPhiBit;   //!
   TBranch        *b_csctf_trPtBit;   //!
   TBranch        *b_csctf_trEta;   //!
   TBranch        *b_csctf_trPhi;   //!
   TBranch        *b_csctf_trPhi_02PI;   //!
   TBranch        *b_csctf_trPt;   //!
   TBranch        *b_csctf_trMode;   //!
   TBranch        *b_csctf_trQuality;   //!
   TBranch        *b_csctf_trNumLCTs;   //!
   TBranch        *b_csctf_lctEndcap;   //!
   TBranch        *b_csctf_lctSector;   //!
   TBranch        *b_csctf_lctSubSector;   //!
   TBranch        *b_csctf_lctBx;   //!
   TBranch        *b_csctf_lctBx0;   //!
   TBranch        *b_csctf_lctStation;   //!
   TBranch        *b_csctf_lctRing;   //!
   TBranch        *b_csctf_lctChamber;   //!
   TBranch        *b_csctf_lctTriggerCSCID;   //!
   TBranch        *b_csctf_lctFpga;   //!
   TBranch        *b_csctf_lctlocalPhi;   //!
   TBranch        *b_csctf_lctglobalPhi;   //!
   TBranch        *b_csctf_lctglobalEta;   //!
   TBranch        *b_csctf_lctstripNum;   //!
   TBranch        *b_csctf_lctwireGroup;   //!
   TBranch        *b_csctf_nsp;   //!
   TBranch        *b_csctf_stSPslot;   //!
   TBranch        *b_csctf_stL1A_BXN;   //!
   TBranch        *b_csctf_stTrkCounter;   //!
   TBranch        *b_csctf_stOrbCounter;   //!

  L1Tree(TTree *tree, const char * option);
  virtual ~L1Tree();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(Long64_t maxevts);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

  ////////////////////////////////

  void Initialize();

  std::string m_option;

  std::vector<int> m_ttbits;
  std::vector<int> m_singleMuBits;
  
  std::bitset<64>  TechBits[5];
  std::bitset<64> AlgBitsw1[5];
  std::bitset<64> AlgBitsw2[5];
  
  TFile * m_output;
  
  BasicOutput * m_histos;

  int m_totalevts;

  void makeStudyOne();

  void CheckConsistency(int);

  void Create(TTree *);
          
};

#endif

#ifdef L1Tree_cxx

L1Tree::L1Tree(TTree *tree, const char * option)
{
  
  Init(tree);
  m_option = std::string(option);
  
}

L1Tree::~L1Tree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
  
  if (m_output)
    delete m_output;

}

Int_t L1Tree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t L1Tree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void L1Tree::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("Run", &Run, &b_Run);
  fChain->SetBranchAddress("Event", &Event, &b_Event);
  fChain->SetBranchAddress("Lumi", &Lumi, &b_Lumi);
  fChain->SetBranchAddress("Bx", &Bx, &b_Bx);
  fChain->SetBranchAddress("Orbit", &Orbit, &b_Orbit);
  fChain->SetBranchAddress("Time", &Time, &b_Time);
  fChain->SetBranchAddress("gmtEvBx", &gmtEvBx, &b_gmtEvBx);
  fChain->SetBranchAddress("gmtNdt", &gmtNdt, &b_gmtNdt);
  fChain->SetBranchAddress("gmtBxdt", gmtBxdt, &b_gmtBxdt);
  fChain->SetBranchAddress("gmtPtdt", gmtPtdt, &b_gmtPtdt);
  fChain->SetBranchAddress("gmtChdt", gmtChdt, &b_gmtChdt);
  fChain->SetBranchAddress("gmtEtadt", gmtEtadt, &b_gmtEtadt);
  fChain->SetBranchAddress("gmtFineEtadt", gmtFineEtadt, &b_gmtFineEtadt);
  fChain->SetBranchAddress("gmtPhidt", gmtPhidt, &b_gmtPhidt);
  fChain->SetBranchAddress("gmtQualdt", gmtQualdt, &b_gmtQualdt);
  fChain->SetBranchAddress("gmtDwdt", gmtDwdt, &b_gmtDwdt);
  fChain->SetBranchAddress("gmtNcsc", &gmtNcsc, &b_gmtNcsc);
  fChain->SetBranchAddress("gmtBxcsc", gmtBxcsc, &b_gmtBxcsc);
  fChain->SetBranchAddress("gmtPtcsc", gmtPtcsc, &b_gmtPtcsc);
  fChain->SetBranchAddress("gmtChcsc", gmtChcsc, &b_gmtChcsc);
  fChain->SetBranchAddress("gmtEtacsc", gmtEtacsc, &b_gmtEtacsc);
  fChain->SetBranchAddress("gmtPhicsc", gmtPhicsc, &b_gmtPhicsc);
  fChain->SetBranchAddress("gmtQualcsc", gmtQualcsc, &b_gmtQualcsc);
  fChain->SetBranchAddress("gmtDwcsc", gmtDwcsc, &b_gmtDwcsc);
  fChain->SetBranchAddress("gmtNrpcb", &gmtNrpcb, &b_gmtNrpcb);
  fChain->SetBranchAddress("gmtBxrpcb", gmtBxrpcb, &b_gmtBxrpcb);
  fChain->SetBranchAddress("gmtPtrpcb", gmtPtrpcb, &b_gmtPtrpcb);
  fChain->SetBranchAddress("gmtCharpcb", gmtCharpcb, &b_gmtCharpcb);
  fChain->SetBranchAddress("gmtEtarpcb", gmtEtarpcb, &b_gmtEtarpcb);
  fChain->SetBranchAddress("gmtPhirpcb", gmtPhirpcb, &b_gmtPhirpcb);
  fChain->SetBranchAddress("gmtQualrpcb", gmtQualrpcb, &b_gmtQualrpcb);
  fChain->SetBranchAddress("gmtDwrpcb", gmtDwrpcb, &b_gmtDwrpcb);
  fChain->SetBranchAddress("gmtNrpcf", &gmtNrpcf, &b_gmtNrpcf);
  fChain->SetBranchAddress("gmtBxrpcf", gmtBxrpcf, &b_gmtBxrpcf);
  fChain->SetBranchAddress("gmtPtrpcf", gmtPtrpcf, &b_gmtPtrpcf);
  fChain->SetBranchAddress("gmtCharpcf", gmtCharpcf, &b_gmtCharpcf);
  fChain->SetBranchAddress("gmtEtarpcf", gmtEtarpcf, &b_gmtEtarpcf);
  fChain->SetBranchAddress("gmtPhirpcf", gmtPhirpcf, &b_gmtPhirpcf);
  fChain->SetBranchAddress("gmtQualrpcf", gmtQualrpcf, &b_gmtQualrpcf);
  fChain->SetBranchAddress("gmtDwrpcf", gmtDwrpcf, &b_gmtDwrpcf);
  fChain->SetBranchAddress("gmtN", &gmtN, &b_gmtN);
  fChain->SetBranchAddress("gmtCandBx", gmtCandBx, &b_gmtCandBx);
  fChain->SetBranchAddress("gmtPt", gmtPt, &b_gmtPt);
  fChain->SetBranchAddress("gmtCha", gmtCha, &b_gmtCha);
  fChain->SetBranchAddress("gmtEta", gmtEta, &b_gmtEta);
  fChain->SetBranchAddress("gmtPhi", gmtPhi, &b_gmtPhi);
  fChain->SetBranchAddress("gmtQual", gmtQual, &b_gmtQual);
  fChain->SetBranchAddress("gmtDet", gmtDet, &b_gmtDet);
  fChain->SetBranchAddress("gmtRank", gmtRank, &b_gmtRank);
  fChain->SetBranchAddress("gmtIsol", gmtIsol, &b_gmtIsol);
  fChain->SetBranchAddress("gmtMip", gmtMip, &b_gmtMip);
  fChain->SetBranchAddress("gmtDw", gmtDw, &b_gmtDw);
  fChain->SetBranchAddress("gmtIdxRPCb", gmtIdxRPCb, &b_gmtIdxRPCb);
  fChain->SetBranchAddress("gmtIdxRPCf", gmtIdxRPCf, &b_gmtIdxRPCf);
  fChain->SetBranchAddress("gmtIdxDTBX", gmtIdxDTBX, &b_gmtIdxDTBX);
  fChain->SetBranchAddress("gmtIdxCSC", gmtIdxCSC, &b_gmtIdxCSC);
  fChain->SetBranchAddress("gtPartrig_tcs", &gtPartrig_tcs, &b_gtPartrig_tcs);
  fChain->SetBranchAddress("gtgpsTimehi", &gtgpsTimehi, &b_gtgpsTimehi);
  fChain->SetBranchAddress("gtgpsTimelo", &gtgpsTimelo, &b_gtgpsTimelo);
  fChain->SetBranchAddress("gtbstMasterStatus", &gtbstMasterStatus, &b_gtbstMasterStatus);
  fChain->SetBranchAddress("gtbstturnCountNumber", &gtbstturnCountNumber, &b_gtbstturnCountNumber);
  fChain->SetBranchAddress("gtbstlhcFillNumber", &gtbstlhcFillNumber, &b_gtbstlhcFillNumber);
  fChain->SetBranchAddress("gtbstbeamMode", &gtbstbeamMode, &b_gtbstbeamMode);
  fChain->SetBranchAddress("gtbstparticleTypeBeam1", &gtbstparticleTypeBeam1, &b_gtbstparticleTypeBeam1);
  fChain->SetBranchAddress("gtbstparticleTypeBeam2", &gtbstparticleTypeBeam2, &b_gtbstparticleTypeBeam2);
  fChain->SetBranchAddress("gtbstbeamMomentum", &gtbstbeamMomentum, &b_gtbstbeamMomentum);
  fChain->SetBranchAddress("gtbsttotalIntensityBeam1", &gtbsttotalIntensityBeam1, &b_gtbsttotalIntensityBeam1);
  fChain->SetBranchAddress("gtbsttotalIntensityBeam2", &gtbsttotalIntensityBeam2, &b_gtbsttotalIntensityBeam2);
  fChain->SetBranchAddress("gttw1", gttw1, &b_gttw1);
  fChain->SetBranchAddress("gttw2", gttw2, &b_gttw2);
  fChain->SetBranchAddress("gttt", gttt, &b_gttt);
  fChain->SetBranchAddress("gtNele", &gtNele, &b_gtNele);
  fChain->SetBranchAddress("gtBxel", gtBxel, &b_gtBxel);
  fChain->SetBranchAddress("gtRankel", gtRankel, &b_gtRankel);
  fChain->SetBranchAddress("gtPhiel", gtPhiel, &b_gtPhiel);
  fChain->SetBranchAddress("gtEtael", gtEtael, &b_gtEtael);
  fChain->SetBranchAddress("gtIsoel", gtIsoel, &b_gtIsoel);
  fChain->SetBranchAddress("gtNjet", &gtNjet, &b_gtNjet);
  fChain->SetBranchAddress("gtBxjet", gtBxjet, &b_gtBxjet);
  fChain->SetBranchAddress("gtRankjet", gtRankjet, &b_gtRankjet);
  fChain->SetBranchAddress("gtPhijet", gtPhijet, &b_gtPhijet);
  fChain->SetBranchAddress("gtEtajet", gtEtajet, &b_gtEtajet);
  fChain->SetBranchAddress("gtTaujet", gtTaujet, &b_gtTaujet);
  fChain->SetBranchAddress("gtFwdjet", gtFwdjet, &b_gtFwdjet);

  /*

  fChain->SetBranchAddress("gctIsoEmSize", &gctIsoEmSize, &b_gctIsoEmSize);
  fChain->SetBranchAddress("gctIsoEmEta", gctIsoEmEta, &b_gctIsoEmEta);
  fChain->SetBranchAddress("gctIsoEmPhi", gctIsoEmPhi, &b_gctIsoEmPhi);
  fChain->SetBranchAddress("gctIsoEmRnk", gctIsoEmRnk, &b_gctIsoEmRnk);
  fChain->SetBranchAddress("gctNonIsoEmSize", &gctNonIsoEmSize, &b_gctNonIsoEmSize);
  fChain->SetBranchAddress("gctNonIsoEmEta", gctNonIsoEmEta, &b_gctNonIsoEmEta);
  fChain->SetBranchAddress("gctNonIsoEmPhi", gctNonIsoEmPhi, &b_gctNonIsoEmPhi);
  fChain->SetBranchAddress("gctNonIsoEmRnk", gctNonIsoEmRnk, &b_gctNonIsoEmRnk);
  fChain->SetBranchAddress("gctCJetSize", &gctCJetSize, &b_gctCJetSize);
  fChain->SetBranchAddress("gctCJetEta", gctCJetEta, &b_gctCJetEta);
  fChain->SetBranchAddress("gctCJetPhi", gctCJetPhi, &b_gctCJetPhi);
  fChain->SetBranchAddress("gctCJetRnk", gctCJetRnk, &b_gctCJetRnk);
  fChain->SetBranchAddress("gctFJetSize", &gctFJetSize, &b_gctFJetSize);
  fChain->SetBranchAddress("gctFJetEta", gctFJetEta, &b_gctFJetEta);
  fChain->SetBranchAddress("gctFJetPhi", gctFJetPhi, &b_gctFJetPhi);
  fChain->SetBranchAddress("gctFJetRnk", gctFJetRnk, &b_gctFJetRnk);
  fChain->SetBranchAddress("gctTJetSize", &gctTJetSize, &b_gctTJetSize);
  fChain->SetBranchAddress("gctTJetEta", gctTJetEta, &b_gctTJetEta);
  fChain->SetBranchAddress("gctTJetPhi", gctTJetPhi, &b_gctTJetPhi);
  fChain->SetBranchAddress("gctTJetRnk", gctTJetRnk, &b_gctTJetRnk);
  fChain->SetBranchAddress("gctEtMiss", &gctEtMiss, &b_gctEtMiss);
  fChain->SetBranchAddress("gctEtMissPhi", &gctEtMissPhi, &b_gctEtMissPhi);
  fChain->SetBranchAddress("gctHtMiss", &gctHtMiss, &b_gctHtMiss);
  fChain->SetBranchAddress("gctHtMissPhi", &gctHtMissPhi, &b_gctHtMissPhi);
  fChain->SetBranchAddress("gctEtHad", &gctEtHad, &b_gctEtHad);
  fChain->SetBranchAddress("gctEtTot", &gctEtTot, &b_gctEtTot);
  fChain->SetBranchAddress("gctHFRingEtSumSize", &gctHFRingEtSumSize, &b_gctHFRingEtSumSize);
  fChain->SetBranchAddress("gctHFRingEtSumEta", gctHFRingEtSumEta, &b_gctHFRingEtSumEta);
  fChain->SetBranchAddress("gctHFBitCountsSize", &gctHFBitCountsSize, &b_gctHFBitCountsSize);
  fChain->SetBranchAddress("gctHFBitCountsEta", gctHFBitCountsEta, &b_gctHFBitCountsEta);
  fChain->SetBranchAddress("rctRegSize", &rctRegSize, &b_rctRegSize);
  fChain->SetBranchAddress("rctRegEta", rctRegEta, &b_rctRegEta);
  fChain->SetBranchAddress("rctRegPhi", rctRegPhi, &b_rctRegPhi);
  fChain->SetBranchAddress("rctRegRnk", rctRegRnk, &b_rctRegRnk);
  fChain->SetBranchAddress("rctRegVeto", rctRegVeto, &b_rctRegVeto);
  fChain->SetBranchAddress("rctRegBx", rctRegBx, &b_rctRegBx);
  fChain->SetBranchAddress("rctRegOverFlow", rctRegOverFlow, &b_rctRegOverFlow);
  fChain->SetBranchAddress("rctRegMip", rctRegMip, &b_rctRegMip);
  fChain->SetBranchAddress("rctRegFGrain", rctRegFGrain, &b_rctRegFGrain);
  fChain->SetBranchAddress("rctEmSize", &rctEmSize, &b_rctEmSize);
  fChain->SetBranchAddress("rctIsIsoEm", rctIsIsoEm, &b_rctIsIsoEm);
  fChain->SetBranchAddress("rctEmEta", rctEmEta, &b_rctEmEta);
  fChain->SetBranchAddress("rctEmPhi", rctEmPhi, &b_rctEmPhi);
  fChain->SetBranchAddress("rctEmRnk", rctEmRnk, &b_rctEmRnk);
  fChain->SetBranchAddress("rctEmBx", rctEmBx, &b_rctEmBx);
  fChain->SetBranchAddress("dttf_phSize", &dttf_phSize, &b_dttf_phSize);
  fChain->SetBranchAddress("dttf_phBx", dttf_phBx, &b_dttf_phBx);
  fChain->SetBranchAddress("dttf_phWh", dttf_phWh, &b_dttf_phWh);
  fChain->SetBranchAddress("dttf_phSe", dttf_phSe, &b_dttf_phSe);
  fChain->SetBranchAddress("dttf_phSt", dttf_phSt, &b_dttf_phSt);
  fChain->SetBranchAddress("dttf_phAng", dttf_phAng, &b_dttf_phAng);
  fChain->SetBranchAddress("dttf_phBandAng", dttf_phBandAng, &b_dttf_phBandAng);
  fChain->SetBranchAddress("dttf_phCode", dttf_phCode, &b_dttf_phCode);
  fChain->SetBranchAddress("dttf_phX", dttf_phX, &b_dttf_phX);
  fChain->SetBranchAddress("dttf_phY", dttf_phY, &b_dttf_phY);
  fChain->SetBranchAddress("dttf_thSize", &dttf_thSize, &b_dttf_thSize);
  fChain->SetBranchAddress("dttf_thBx", dttf_thBx, &b_dttf_thBx);
  fChain->SetBranchAddress("dttf_thWh", dttf_thWh, &b_dttf_thWh);
  fChain->SetBranchAddress("dttf_thSe", dttf_thSe, &b_dttf_thSe);
  fChain->SetBranchAddress("dttf_thSt", dttf_thSt, &b_dttf_thSt);
  fChain->SetBranchAddress("dttf_thX", dttf_thX, &b_dttf_thX);
  fChain->SetBranchAddress("dttf_thY", dttf_thY, &b_dttf_thY);
  fChain->SetBranchAddress("dttf_thTheta", dttf_thTheta, &b_dttf_thTheta);
  fChain->SetBranchAddress("dttf_thCode", dttf_thCode, &b_dttf_thCode);
  fChain->SetBranchAddress("dttf_trSize", &dttf_trSize, &b_dttf_trSize);
  fChain->SetBranchAddress("dttf_trBx", dttf_trBx, &b_dttf_trBx);
  fChain->SetBranchAddress("dttf_trQual", dttf_trQual, &b_dttf_trQual);
  fChain->SetBranchAddress("dttf_trTag", dttf_trTag, &b_dttf_trTag);
  fChain->SetBranchAddress("dttf_trPtPck", dttf_trPtPck, &b_dttf_trPtPck);
  fChain->SetBranchAddress("dttf_trPtVal", dttf_trPtVal, &b_dttf_trPtVal);
  fChain->SetBranchAddress("dttf_trPhiPck", dttf_trPhiPck, &b_dttf_trPhiPck);
  fChain->SetBranchAddress("dttf_trPhiVal", dttf_trPhiVal, &b_dttf_trPhiVal);
  fChain->SetBranchAddress("dttf_trPhiGlob", dttf_trPhiGlob, &b_dttf_trPhiGlob);
  fChain->SetBranchAddress("dttf_trChPck", dttf_trChPck, &b_dttf_trChPck);
  fChain->SetBranchAddress("dttf_trWh", dttf_trWh, &b_dttf_trWh);
  fChain->SetBranchAddress("dttf_trSc", dttf_trSc, &b_dttf_trSc);
  fChain->SetBranchAddress("csctf_trSize", &csctf_trSize, &b_csctf_trSize);
  fChain->SetBranchAddress("csctf_trEndcap", csctf_trEndcap, &b_csctf_trEndcap);
  fChain->SetBranchAddress("csctf_trSector", csctf_trSector, &b_csctf_trSector);
  fChain->SetBranchAddress("csctf_trBx", csctf_trBx, &b_csctf_trBx);
  fChain->SetBranchAddress("csctf_trME1ID", csctf_trME1ID, &b_csctf_trME1ID);
  fChain->SetBranchAddress("csctf_trME2ID", csctf_trME2ID, &b_csctf_trME2ID);
  fChain->SetBranchAddress("csctf_trME3ID", csctf_trME3ID, &b_csctf_trME3ID);
  fChain->SetBranchAddress("csctf_trME4ID", csctf_trME4ID, &b_csctf_trME4ID);
  fChain->SetBranchAddress("csctf_trMB1ID", csctf_trMB1ID, &b_csctf_trMB1ID);
  fChain->SetBranchAddress("csctf_trOutputLink", csctf_trOutputLink, &b_csctf_trOutputLink);
  fChain->SetBranchAddress("csctf_trCharge", csctf_trCharge, &b_csctf_trCharge);
  fChain->SetBranchAddress("csctf_trChargeValid", csctf_trChargeValid, &b_csctf_trChargeValid);
  fChain->SetBranchAddress("csctf_trForR", csctf_trForR, &b_csctf_trForR);
  fChain->SetBranchAddress("csctf_trPhi23", csctf_trPhi23, &b_csctf_trPhi23);
  fChain->SetBranchAddress("csctf_trPhi12", csctf_trPhi12, &b_csctf_trPhi12);
  fChain->SetBranchAddress("csctf_trPhiSign", csctf_trPhiSign, &b_csctf_trPhiSign);
  fChain->SetBranchAddress("csctf_trEtaBit", csctf_trEtaBit, &b_csctf_trEtaBit);
  fChain->SetBranchAddress("csctf_trPhiBit", csctf_trPhiBit, &b_csctf_trPhiBit);
  fChain->SetBranchAddress("csctf_trPtBit", csctf_trPtBit, &b_csctf_trPtBit);
  fChain->SetBranchAddress("csctf_trEta", csctf_trEta, &b_csctf_trEta);
  fChain->SetBranchAddress("csctf_trPhi", csctf_trPhi, &b_csctf_trPhi);
  fChain->SetBranchAddress("csctf_trPhi_02PI", csctf_trPhi_02PI, &b_csctf_trPhi_02PI);
  fChain->SetBranchAddress("csctf_trPt", csctf_trPt, &b_csctf_trPt);
  fChain->SetBranchAddress("csctf_trMode", csctf_trMode, &b_csctf_trMode);
  fChain->SetBranchAddress("csctf_trQuality", csctf_trQuality, &b_csctf_trQuality);
  fChain->SetBranchAddress("csctf_trNumLCTs", csctf_trNumLCTs, &b_csctf_trNumLCTs);
  fChain->SetBranchAddress("csctf_lctEndcap", csctf_lctEndcap, &b_csctf_lctEndcap);
  fChain->SetBranchAddress("csctf_lctSector", csctf_lctSector, &b_csctf_lctSector);
  fChain->SetBranchAddress("csctf_lctSubSector", csctf_lctSubSector, &b_csctf_lctSubSector);
  fChain->SetBranchAddress("csctf_lctBx", csctf_lctBx, &b_csctf_lctBx);
  fChain->SetBranchAddress("csctf_lctBx0", csctf_lctBx0, &b_csctf_lctBx0);
  fChain->SetBranchAddress("csctf_lctStation", csctf_lctStation, &b_csctf_lctStation);
  fChain->SetBranchAddress("csctf_lctRing", csctf_lctRing, &b_csctf_lctRing);
  fChain->SetBranchAddress("csctf_lctChamber", csctf_lctChamber, &b_csctf_lctChamber);
  fChain->SetBranchAddress("csctf_lctTriggerCSCID", csctf_lctTriggerCSCID, &b_csctf_lctTriggerCSCID);
  fChain->SetBranchAddress("csctf_lctFpga", csctf_lctFpga, &b_csctf_lctFpga);
  fChain->SetBranchAddress("csctf_lctlocalPhi", csctf_lctlocalPhi, &b_csctf_lctlocalPhi);
  fChain->SetBranchAddress("csctf_lctglobalPhi", csctf_lctglobalPhi, &b_csctf_lctglobalPhi);
  fChain->SetBranchAddress("csctf_lctglobalEta", csctf_lctglobalEta, &b_csctf_lctglobalEta);
  fChain->SetBranchAddress("csctf_lctstripNum", csctf_lctstripNum, &b_csctf_lctstripNum);
  fChain->SetBranchAddress("csctf_lctwireGroup", csctf_lctwireGroup, &b_csctf_lctwireGroup);
  fChain->SetBranchAddress("csctf_nsp", &csctf_nsp, &b_csctf_nsp);
  fChain->SetBranchAddress("csctf_stSPslot", csctf_stSPslot, &b_csctf_stSPslot);
  fChain->SetBranchAddress("csctf_stL1A_BXN", csctf_stL1A_BXN, &b_csctf_stL1A_BXN);
  fChain->SetBranchAddress("csctf_stTrkCounter", csctf_stTrkCounter, &b_csctf_stTrkCounter);
  fChain->SetBranchAddress("csctf_stOrbCounter", csctf_stOrbCounter, &b_csctf_stOrbCounter);
  */

  Notify();
}

Bool_t L1Tree::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  //std::cout << "New File opened" << std::endl;
 
  return kTRUE;
}

void L1Tree::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
   fChain->Show(entry);
}

Int_t L1Tree::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef L1Tree_cxx
