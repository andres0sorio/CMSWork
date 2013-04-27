// $Id: $
#ifndef TDATASETS_H 
#define TDATASETS_H 1

// Include files

#include <RootCommon.h>
#include <TDOMParser.h>
#include <TXMLAttr.h>
#include <TXMLNode.h>
#include <TList.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>

#include <map>

/** @class TDataSets TDataSets.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-11-04
 */

class TDataSets : public TObject {
  
public:

  TDataSets();
  virtual ~TDataSets();

  TDataSets(int id, std::string &nm);

  TGraphAsymmErrors *  getGraph();
  
  void setMarker(int marker, int colour, float size );
    
  friend std::ostream & operator << (std::ostream &out, const TDataSets &p) {
    out << "Id: " << p.Id << std::endl;
    return out;
  }
  
private:
  
  int Id;
  std::string name;
  TGraphAsymmErrors *graph;
  
  ClassDef(TDataSets,1);

      
};

#endif // TDATASETS_H
