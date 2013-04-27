// $Id: $
// Include files 



// local
#include "csvtoxml.h"

//-----------------------------------------------------------------------------
// Implementation file for class : csvtoxml
//
// 2011-11-04 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
csvtoxml::csvtoxml(  ) {

}

csvtoxml::csvtoxml( const char * filename ) {
  
  m_in = new std::ifstream();
  m_in->open(filename);
  
  if(!m_in->is_open()) {
    std::cout << "Data> cannot open file" << std::endl;
  } else { 
    std::cout << "Data> file is now open" << std::endl;
  }
   
}
//=============================================================================
// Destructor
//=============================================================================
csvtoxml::~csvtoxml() {} 

//=============================================================================

void csvtoxml::run() 
{
  
  // First create engine
  TXMLEngine* xml = new TXMLEngine;

  // Create main node of document tree
  XMLNodePointer_t mainnode = xml->NewChild(0, 0, "TGraphFromXML");
  
  int nset = 0;
  int npoints = 0;
  std::string attr[7];
  float x = 0.0;
  
  while ( 1 ) 
  {

    if ( m_in->eof() ) break;
    if ( m_in->fail()) break;

    XMLNodePointer_t dataset = xml->NewChild(mainnode, 0, "DataSets");
    
    std::stringstream ndata (stringstream::in | stringstream::out);
    std::stringstream dataname (stringstream::in | stringstream::out);
    ndata << nset;
    dataname << "set" << nset;
    
    xml->NewAttr(dataset, 0, "Id", ndata.str().c_str() );
    xml->NewAttr(dataset, 0, "Name", dataname.str().c_str());
    xml->NewAttr(dataset, 0, "Marker", "22");
    xml->NewAttr(dataset, 0, "Colour", "1");
    xml->NewAttr(dataset, 0, "Size", "1.0");
    
    attr[0] = std::string("Id");
    (*m_in) >> npoints >> attr[1] >> attr[2] >> attr[3] >> attr[4] >> attr[5] >> attr[6];
    
    int n = 0;
    
    for(int k = 0; k < npoints; ++k ) 
    {

      std::stringstream value;
            
      XMLNodePointer_t point = xml->NewChild(dataset, 0, "Point");

      (*m_in) >> n;
      value << n;
      xml->NewAttr(point, 0, attr[0].c_str(), value.str().c_str() );
      value.str("");
      
      for ( int i=1; i < 7; ++i ) 
      {
        (*m_in) >> x;
        value << x;
        xml->NewAttr(point, 0, attr[i].c_str(), value.str().c_str() );
        value.str("");
      }
            
    }
    
    ndata.str("");
    dataname.str("");
    
    ++nset;

    if ( m_in->fail()) break;

  }
  
  XMLDocPointer_t xmldoc = xml->NewDoc();
  xml->DocSetRootElement(xmldoc, mainnode);
  xml->SaveDoc(xmldoc, "test.xml");
  xml->FreeDoc(xmldoc);
  delete xml;
  
}
