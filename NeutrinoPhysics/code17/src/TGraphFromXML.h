// $Id: $
#ifndef TGRAPHFROMXML_H 
#define TGRAPHFROMXML_H 1

// Include files

#include <RootCommon.h>
#include <TDOMParser.h>
#include <TXMLAttr.h>
#include <TXMLNode.h>
#include <TList.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>

#include <map>

#include <TDataSets.h>

/** @class TGraphFromXML TGraphFromXML.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-11-04
 */

class TGraphFromXML {

public: 
  
  /// Standard constructor
  TGraphFromXML( );
  
  virtual ~TGraphFromXML( ) ; ///< Destructor
  
  //..................................................................................
  
  int ParseFile( TString );
  
  void ParseDataSetsList( TXMLNode *);
  
  TDataSets* ParseDataSets( TXMLNode *, int , std::string &, int, int, float );
  
  //..................................................................................
  
  friend std::ostream& operator << (std::ostream& out, const  TGraphFromXML & pl) {
    TIter next(pl.listOfDataSets);
    TDataSets *p;
    while ((p =(TDataSets*)next())){
      out << *p << std::endl;
    }
    return out;
  }

  void PrintDataSets() {
    TIter next(listOfDataSets);
    TDataSets *p;
    while ((p =(TDataSets*)next())) {
      std::cout << *p << std::endl;
    }
  }

  TDataSets* GetDataSets( int idx ) 
  {
    return ( TDataSets*)listOfDataSets->At( idx );
  }
  
  Int_t GetNDataSets() 
  {
    return numberOfDataSets;
  }
  
  TDataSets * Next() 
  {
    return (TDataSets*)(*m_iter)();
  }
  void SetRange(double xmin, double xmax, double ymin, double ymax);

  void MakePlots();
  
protected:

private:
  
  TIter * m_iter;
  Int_t   numberOfDataSets;
  TList * listOfDataSets;
  
  //////
  TCanvas * canvas;
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  
  
};
#endif // TGRAPHFROMXML_H
