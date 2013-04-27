// $Id: $
#ifndef XML_CSVTOXML_H 
#define XML_CSVTOXML_H 1

// Include files
#include <RootCommon.h>
#include <TDOMParser.h>
#include <TXMLAttr.h>
#include <TXMLNode.h>
#include <TXMLEngine.h>

#include <TList.h>

/** @class csvtoxml csvtoxml.h XML/csvtoxml.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2011-11-04
 */

class csvtoxml {
public: 
  /// Standard constructor
  csvtoxml( ); 
  
  csvtoxml(const char *); 

  virtual ~csvtoxml( ); ///< Destructor

  void run();
  

protected:

private:

  std::ifstream * m_in;
  
};
#endif // XML_CSVTOXML_H
