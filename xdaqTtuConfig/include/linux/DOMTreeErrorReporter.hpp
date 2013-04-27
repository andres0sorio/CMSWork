/*
 * $Id: DOMTreeErrorReporter.hpp 568078 2007-08-21 11:43:25Z amassari $
 */

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

#include "StrX.hpp"

XERCES_CPP_NAMESPACE_USE

class DOMTreeErrorReporter : public xercesc::ErrorHandler
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  DOMTreeErrorReporter() :
    fSawErrors(false)
  {
  }
  
  ~DOMTreeErrorReporter()
  {
  }
  
  
  // -----------------------------------------------------------------------
  //  Implementation of the error handler interface
  // -----------------------------------------------------------------------
  void warning(const SAXParseException& toCatch);
  void error(const SAXParseException& toCatch);
  void fatalError(const SAXParseException& toCatch);
  void resetErrors();
  
  // -----------------------------------------------------------------------
  //  Getter methods
  // -----------------------------------------------------------------------
  bool getSawErrors() const;
  
  // -----------------------------------------------------------------------
  //  Private data members
  //
  //  fSawErrors
  //      This is set if we get any errors, and is queryable via a getter
  //      method. Its used by the main code to suppress output if there are
  //      errors.
  // -----------------------------------------------------------------------
  bool    fSawErrors;

};

inline bool DOMTreeErrorReporter::getSawErrors() const
{
  return fSawErrors;
}

