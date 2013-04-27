// $Id: $
#ifndef FRAME_H 
#define FRAME_H 1

// Include files
#include "Data.h"
#include "DSCReader.h"
#include <SimpleClusterAlgo.h>

//From ROOT
#include <RootCommon.h>
#include <TCanvas.h>
#include <TH2F.h>
#include <TStyle.h>

/** @class Frame Frame.h
 *  
 *
 *  @author Andres Osorio/Iván Caicedo
 *  @date   2012-03
 */

//Initializes the Frame Class
class Frame {
public: 
  //Constructor of the Frame Class
  Frame( ) {}; 
  Frame( const char *, const char *, int );
  //Destructor of the DSCReader Class
  virtual ~Frame( );

  bool Compare( const Frame & );

  void FindCoincidences( const Frame &  );
  
  void Clusterize( );
  
  void ExportCoincidences( std::ofstream * );

 protected:

 private:

  int m_frameId;
  Data * m_data;
  DSCReader * m_dscreader;
  SimpleClusterAlgo * m_algo;

  const Frame * m_otherFrame;

  std::vector<Cluster*> m_coincidences;

  std::string m_fname;

  ///Plots - ROOT
  TH2F * m_clusters;
  TH2F * m_readings;
  
};
#endif // FRAME_H
