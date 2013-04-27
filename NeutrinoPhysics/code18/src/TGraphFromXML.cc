// $Id: $
// Include files 



// local
#include "TGraphFromXML.h"
#include <TAxis.h>

//-----------------------------------------------------------------------------
// Implementation file for class : TGraphFromXML
//
// 2011-11-04 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
TGraphFromXML::TGraphFromXML(  ) {
  
  listOfDataSets = new TList();
  m_iter = new TIter(listOfDataSets);
  numberOfDataSets = 0;
  
  canvas = new TCanvas("Plot1", "Canvas for plot 1", 94, 262,700, 502 );
  canvas->SetFillColor(10);

  xmin = 0.0;
  xmax = 0.0;
  ymin = 0.0;
  ymax = 0.0;
    
}
//=============================================================================
// Destructor
//=============================================================================
TGraphFromXML::~TGraphFromXML() {} 

//=============================================================================

int TGraphFromXML::ParseFile(TString filename) {
  
  TDOMParser *domParser = new TDOMParser();
  
  int parsecode = domParser->ParseFile(filename);
  
  if (parsecode < 0) {
    std::cerr << domParser->GetParseCodeMessage(parsecode) << std::endl;
    return -1;
  }
  
  TXMLNode * node = domParser->GetXMLDocument()->GetRootNode();
  
  ParseDataSetsList(node);
  
  return 0;
  
}

void TGraphFromXML::ParseDataSetsList(TXMLNode *node) {
  
  for (; node; node = node->GetNextNode()) {
    
    if (node->GetNodeType() == TXMLNode::kXMLElementNode) { // Element Node

      if (strcmp(node->GetNodeName(), "DataSets") == 0) {
        
        int id=0;
        int marker=22;
        int colour=2;
        float size=1.0;
        std::string name;
        
        if (node->HasAttributes()) {
          TList *attrList = node->GetAttributes();
          TXMLAttr *attr = 0;
          TIter next(attrList);
          
          while ((attr=(TXMLAttr*)next())) {
            
            if (strcmp(attr->GetName(), "Id") == 0) {
              id = atoi(attr->GetValue());
            }
            
            if (strcmp(attr->GetName(), "Name") == 0) {
              name = std::string(attr->GetValue());
            }
            
            if (strcmp(attr->GetName(), "Marker") == 0) {
              marker = atoi(attr->GetValue());
            }
            
            if (strcmp(attr->GetName(), "Colour") == 0) {
              colour = atoi(attr->GetValue());
            }

            if (strcmp(attr->GetName(), "Size") == 0) {
              size = atof(attr->GetValue());
            }
            
          }
          
        }
        
        listOfDataSets->Add( ParseDataSets(node->GetChildren(), id, name, marker, colour, size ) );
        ++numberOfDataSets;
        
      }
      
    }
    
    ParseDataSetsList(node->GetChildren());
  
  }

}

TDataSets* TGraphFromXML::ParseDataSets(TXMLNode *node, int Id, std::string &name, int marker, int colour, float size) {
  
  TDataSets * p1 = new TDataSets( Id, name );
  p1->setMarker( marker, colour, size );
  
  int npoint = 0;
  
  for ( ; node; node = node->GetNextNode()) {
    
    if ( node->GetNodeType() == TXMLNode::kXMLElementNode) { // Element Node

      if (strcmp(node->GetNodeName(), "Point") == 0) {
        
        double x(0.0);
        double y(0.0);
        double xel(0.0);
        double xeu(0.0);
        double yel(0.0);
        double yeu(0.0);
        
        if (node->HasAttributes()) {
          
          TList *attrList = node->GetAttributes();
          TXMLAttr *attr = 0;
          TIter next(attrList);
          
          while ((attr=(TXMLAttr*)next())) {
            
            if (strcmp(attr->GetName(), "x") == 0) {
              x = atof(attr->GetValue());
            }

            if (strcmp(attr->GetName(), "y") == 0) {
              y = atof(attr->GetValue());
            }

            if (strcmp(attr->GetName(), "xelow") == 0) {
              xel = atof(attr->GetValue());
            }

            if (strcmp(attr->GetName(), "xeup") == 0) {
              xeu = atof(attr->GetValue());
            }

            if (strcmp(attr->GetName(), "yelow") == 0) {
              yel = atof(attr->GetValue());
            }

            if (strcmp(attr->GetName(), "yeup") == 0) {
              yeu = atof(attr->GetValue());
            }
            
          }
          
          p1->getGraph()->SetPoint(npoint, x, y);
          p1->getGraph()->SetPointError(npoint, xel, xeu, yel, yeu);
          
          ++npoint;
          
        }
        
      }
      
    }
        
  }
  
  return p1;
}

void TGraphFromXML::SetRange(double x1, double x2, double y1, double y2)
{

  xmin = x1;
  xmax = x2;
  
  ymin = y1;
  ymax = y2;
    
}


void TGraphFromXML::MakePlots()
{
  
  int k = 0;
  
  canvas->cd();
  canvas->SetLogx();
  canvas->SetLogy();
  
  TIter next(listOfDataSets);
  TDataSets *p;
  while ((p =(TDataSets*)next())) {
    
    if ( k < 1 ) {
      p->getGraph()->SetMinimum(ymin);
      p->getGraph()->SetMaximum(ymax);
      p->getGraph()->Draw("AP");
      p->getGraph()->GetXaxis()->SetLimits(xmin, xmax);
      p->getGraph()->Draw("AP");
    }
    else
      p->getGraph()->Draw("P");
   
    ++k;
    
  }
    
}
