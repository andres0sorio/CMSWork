/*
 * $Id: DOMTreeErrorReporter.cpp 568078 2007-08-21 11:43:25Z amassari $
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include "DOMTreeErrorReporter.hpp"

#include <xercesc/sax/SAXParseException.hpp>

void DOMTreeErrorReporter::warning(const SAXParseException&)
{
  //
  // Ignore all warnings.
  //
}

void DOMTreeErrorReporter::error(const SAXParseException& toCatch)
{
  fSawErrors = true;
  XERCES_STD_QUALIFIER cerr << "Error at file \"" << StrX(toCatch.getSystemId())
                            << "\", line " << toCatch.getLineNumber()
                            << ", column " << toCatch.getColumnNumber()
                            << "\n   Message: " << StrX(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void DOMTreeErrorReporter::fatalError(const SAXParseException& toCatch)
{
  fSawErrors = true;
  XERCES_STD_QUALIFIER cerr << "Fatal Error at file \"" << StrX(toCatch.getSystemId())
                            << "\", line " << toCatch.getLineNumber()
                            << ", column " << toCatch.getColumnNumber()
                            << "\n   Message: " << StrX(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void DOMTreeErrorReporter::resetErrors()
{
  fSawErrors = false;
}


