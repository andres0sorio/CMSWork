// $Id: $
#ifndef HISTORATES_H 
#define HISTORATES_H 1

// Include files
#include "CommonIncludes.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1D.h"

#include <sstream>
#include <map>
#include <bitset>

/** @class HistoRates HistoRates.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2010-03-01
 */
class HistoRates {
public: 
  /// Standard constructor
  HistoRates( ); 

  virtual ~HistoRates( ); ///< Destructor

  TH1D   *secRatesSummary[5];
  TGraph *wheelRates[5];

  TGraph *sectorRatesWM2[12];
  TGraph *sectorRatesWM1[12];
  TGraph *sectorRatesW00[12];
  TGraph *sectorRatesWP1[12];
  TGraph *sectorRatesWP2[12];
  
  std::vector<float> buff_time;
  std::vector<float> buff_wheelrates[5];
  std::vector<float> buff_sectorRatesWM2[12];
  std::vector<float> buff_sectorRatesWM1[12];
  std::vector<float> buff_sectorRatesW00[12];
  std::vector<float> buff_sectorRatesWP1[12];
  std::vector<float> buff_sectorRatesWP2[12];
  
  bool isfirst;
  int max_buff_size;
  std::vector<int> m_wcolour;
  std::map<string,int> m_colour;
  std::bitset<5> m_selectedWheel;
  bool m_hotSector;
  int m_YLimit;
  
  void addTime( int );
  
  //void addwheelRate( int , int );
  //void addsectorRates( int *, int *, int *, int *, int * );

  void addwheelRate( int , float );
  void addsectorRates( float *, float *, float *, float *, float * );

  int copyToArray( const std::vector<float> & , float * );

  void DrawWheelRates( TCanvas * );

  void DrawSectorRates( TCanvas *, Bool_t );

  void DrawSectorSummary( TCanvas * );

   void DrawSectorPie( TCanvas * );
  
  void setGraphOptions(TGraph * , int );
    
protected:

private:

};
#endif // HISTORATES_H
