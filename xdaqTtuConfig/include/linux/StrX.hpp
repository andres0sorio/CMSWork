#ifndef STRX_HPP 
#define STRX_HPP 1

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// ---------------------------------------------------------------------------
//  Includes for all the program files to see
// ---------------------------------------------------------------------------

#include <string.h>
#include <stdlib.h>

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/XMLString.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------

class StrX {

public :
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------

  StrX(const char* const toTranscode)
  {
    // Call the private transcoding method
    fLocalForm = NULL;
    fUnicodeForm = XMLString::transcode(toTranscode);
  }

  StrX(const XMLCh* const toTranscode)
  {
    // Call the private transcoding method
    fUnicodeForm = NULL;
    fLocalForm = XMLString::transcode(toTranscode);
  }
  
  ~StrX()
  {
    if (fUnicodeForm) XMLString::release(&fUnicodeForm);
    if (fLocalForm)   XMLString::release(&fLocalForm);
  }
  
  // -----------------------------------------------------------------------
  //  Getter methods
  // -----------------------------------------------------------------------
  const char* localForm() const
  {
    return fLocalForm;
  }
  
  const XMLCh* unicodeForm() const
  {
    return fUnicodeForm;
  }

private :
  // -----------------------------------------------------------------------
  //  Private data members
  //
  //  fLocalForm
  //      This is the local code page form of the string.
  // -----------------------------------------------------------------------
  
  char*    fLocalForm;
  XMLCh*   fUnicodeForm;

};

inline XERCES_STD_QUALIFIER ostream& operator<<(XERCES_STD_QUALIFIER ostream& target, const StrX& toDump)
{
  target << toDump.localForm();
  return target;
}

#endif // STRX_HPP
